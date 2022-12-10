import csv
import sys


def main():
    # TODO: Check for command-line usage
    if (len(sys.argv) != 3):
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    profiles = []
    STRs = []
    check = []
    sequence_dna = ""
    match = "No match"

    # TODO: Read database file into a variable
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)

        for row in reader:
            profiles.append(row)

        for STR in profiles[0].keys():
            if STR != "name":
                STRs.append(STR)

    # TODO: Read DNA sequence file into a
    with open(sys.argv[2], "r") as file:
        for row in file:
            sequence_dna = row

    # TODO: Find longest match of each S in DNA sequence
    for STR in STRs:
        check.append((STR, longest_match(sequence_dna, STR)))

    # TODO: Check database for matching profiles
    for profile in profiles:
        is_match = True

        for STR, times in check:
            if int(profile[STR]) != int(times):
                is_match = False

        if is_match is True:
            match = profile["name"]
            break

    return match


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


if __name__ == "__main__":
    print(main())
