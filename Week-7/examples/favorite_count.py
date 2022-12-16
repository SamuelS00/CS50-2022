import csv

titles = {}

with open("favorites.csv", "r") as file:
    reader = csv.DictReader(file)

    for row in reader:
        title = row["title"].strip().upper()
        # if the key does not exist in the dict titles, 1 is added to the key
        # if it exists, it is incremented.
        if title in titles:
            titles[title] += 1
        else:
            titles[title] = 1


# lambda to return values
def get_value(title):
    return titles[title]


# reverse=true is used to sort the values from highest to lowest
# is lambda, or anonymous function
# in key I pass the auxiliary function
for title in sorted(titles, key=lambda title: titles[title], reverse=True):
    print(title, titles[title])
