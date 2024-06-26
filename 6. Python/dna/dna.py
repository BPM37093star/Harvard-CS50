import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python script.py <argv1> <argv2>")
        sys.exit(1)

    # TODO: Read database file into a variable
    csv_file = sys.argv[1]
    rows = []
    with open(csv_file) as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            rows.append(row)
        str_sequences = reader.fieldnames[1:]

    # TODO: Read DNA sequence file into a variable
    dna_file = sys.argv[2]
    with open(dna_file) as dnafile:
        dna_sequence = dnafile.read()

    # TODO: Find longest match of each STR in DNA sequence
    matches = {}
    for str_sequence in str_sequences:
        repeat_time = longest_match(dna_sequence, str_sequence)
        matches[str_sequence] = repeat_time

    # TODO: Check database for matching profiles
    with open(csv_file) as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            if all(int(row[str_sequence]) == matches[str_sequence] for str_sequence in str_sequences):
                print(f"{row['name']}")
                sys.exit(0)
    print("No match")


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


main()
