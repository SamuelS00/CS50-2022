import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Rescue the user id registered in the session
    user_id = session["user_id"]

    if user_id:
        # It uses the session id to redeem the amount of money from the user.
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0][
            "cash"
        ]

        quotes = db.execute(
            """SELECT
                symbol,
                name,
                SUM(shares) as total_shares
            FROM transactions
                WHERE user_id = ?
                GROUP BY symbol
                HAVING total_shares > 0""",
            user_id,
        )

        total = 0

        # Get the current share price and calculates the total price based on the number of shares the user has and the current value of the share
        for quote in quotes:
            current_price = lookup(quote["symbol"])["price"]

            quote["current_price"] = current_price
            quote["total_price"] = (
                quote["current_price"] * quote["total_shares"]
            )

            total += quote["total_price"]

        return render_template(
            "index.html", quotes=quotes, cash=cash, total=(total + cash)
        )
    else:
        return render_template("login.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Ensure symbol was submitted
        if not symbol:
            return apology("must provide symbol", 400)

        # Ensures that shares is an integer
        if not shares.isdigit() or int(shares) <= 0:
            return apology("shares must be an integer", 400)

        # Receives the quotation of the symbol sent
        quote = lookup(symbol)

        if quote == None:
            return apology("must provide valid symbol")

        current_price = quote["price"]
        name = quote["name"]
        symbol = quote["symbol"]

        # Rescue the user id registered in the session
        user_id = session["user_id"]

        # It uses the session id to redeem the amount of money from the user.
        rows = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        cash = rows[0]["cash"]

        # Calculates the total purchase price of the shares
        total_price = current_price * float(shares)

        # Ensures that the customer's balance is sufficient
        if cash < total_price:
            return apology("Your balance is insufficient", 403)

        db.execute("BEGIN")

        # Puts the purchase information in a table of transactions made
        db.execute(
            "INSERT INTO transactions (name, symbol, user_id, price, shares, operation) VALUES (?, ?, ?, ?, ?, ?)",
            name,
            symbol,
            user_id,
            current_price,
            shares,
            "purchase",
        )

        # Update user balance
        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?",
            cash - total_price,
            user_id,
        )

        db.execute("COMMIT")

        return redirect("/")
    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Rescue the user id registered in the session
    user_id = session["user_id"]

    quotes = db.execute(
        "SELECT * FROM transactions WHERE user_id = ?", user_id
    )

    return render_template("history.html", quotes=quotes)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?",
            request.form.get("username"),
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("must provide symbol", 400)

        # Receives the quotation of the symbol sent
        quote = lookup(symbol)

        if quote is None:
            return apology("must provide valid symbol")

        return render_template("quote.html", quote=quote)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quoted.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure username was submitted
        if not username:
            return apology("must provide name", 400)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 400)

        # Ensure confirmation was submitted
        elif not confirmation:
            return apology("must provide confirmation", 400)

        # Ensures passwords are the same
        elif confirmation != password:
            return apology("passwords do not match", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        if len(rows) != 0:
            return apology("username already exists", 400)

        # Add a new user to the database
        id = db.execute(
            "INSERT INTO users (username, hash) VALUES (?, ?)",
            username,
            generate_password_hash(password),
        )

        # Remember which user has logged in
        session["user_id"] = id

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Rescue the user id registered in the session
    user_id = session["user_id"]

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Ensure symbol was submitted
        if not symbol:
            return apology("must provide symbol", 400)

        # Ensures that shares is an integer
        if not shares.isdigit() or int(shares) <= 0:
            return apology("shares must be an integer", 400)

        shares = int(shares)

        # Receives the quotation of the symbol sent
        quote = lookup(symbol)

        if quote == None:
            return apology("must provide valid symbol")

        current_price = quote["price"]
        name = quote["name"]

        quotes = db.execute(
            "SELECT id, shares, symbol FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol",
            user_id,
            symbol,
        )

        if (
            not quotes
            or quotes[0]["shares"] < shares
            or quotes[0]["shares"] <= 0
        ):
            return apology(
                "The amount of shares requested is incompatible with what you have"
            )

        # It uses the session id to redeem the amount of money from the user.
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0][
            "cash"
        ]

        db.execute("BEGIN")

        # Puts the transaction information in a table of transactions made
        db.execute(
            "INSERT INTO transactions (name, symbol, user_id, price, shares, operation) VALUES (?, ?, ?, ?, ?, ?)",
            name,
            symbol,
            user_id,
            current_price,
            (-shares),
            "sell",
        )

        # Update user balance
        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?",
            cash + current_price * shares,
            user_id,
        )

        db.execute("COMMIT")

        # Redirect user to home page
        return redirect("/")
    else:
        symbols = db.execute(
            "SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol",
            user_id,
        )

        return render_template(
            "sell.html", symbols=[s["symbol"] for s in symbols]
        )


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
