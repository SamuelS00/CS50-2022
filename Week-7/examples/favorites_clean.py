import csv

titles = set()  # data structure that does not allow duplicates

with open("favorites.csv", "r") as file:
    reader = csv.DictReader(
        file
    )  # open data in key-value dictionary format making it easy to access
    # data by key

    for row in reader:
        # remove spaces from titles and change everything to uppercase
        title = row["title"].strip().upper()
        titles.add(title)

# print in alphabetical order
for title in sorted(titles):
    print(title)
