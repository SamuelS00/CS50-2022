from cs50 import get_float


def main():
    while True:
        cents = get_float("Change owed: ")
        if cents > 0:
            break

    cents = round(cents * 100)
    coins = 0

    quarters = int(cents / 25)
    dimes = int((cents % 25) / 10)
    nickels = int(((cents % 25) % 10) / 5)
    pennies = int(((cents % 25) % 10) % 5)

    coins += quarters + dimes + nickels + pennies

    print(coins)


if __name__ == "__main__":
    main()
