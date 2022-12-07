from cs50 import get_string
import sys

names = ["Bill", "Charlie", "Fred", "George", "Ginny", "Percy", "Ron"]

if "Ron" in names:
    print("Found")
    sys.exit(0)

print("Not found")
sys.exit(1)


people = {"Carter": "+1-617-495-1000", "David": "+1-949-468-2750"}

name = get_string("Name: ")
if name in people:
    number = people[name]
    print(f"Number: {number}")
