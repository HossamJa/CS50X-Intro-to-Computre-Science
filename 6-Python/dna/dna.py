import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: pyhon3 dna.py file.csv file.txt")
        return
    else:
        if sys.argv[1][-4:] != ".csv" and sys.argv[2][-4:] != ".txt":
            print("Not a valid csv or txt file")
            return
    
    # Read database file into a variable
    rows = []
    headr = []
    with open(sys.argv[1]) as db:
        reader = csv.DictReader(db)
        headr = reader.fieldnames
        for row in reader:
            rows.append(row)

    # Read DNA sequence file into a variable
    sequence = ""
    with open(sys.argv[2]) as dna:
        sequence = dna.read()

    # Check database for matching profiles
    matches = 0
    for person in rows:
        # Find longest match of each STR in DNA sequence
        for STR in headr[1:]:
            if person[STR] == longest_match(sequence, STR):
                matches += 1
        # Check if the person's STRs are mactching
        if matches == len(headr[1:]):
            print(person["name"])
            return
        # Set the matches to 0 for the next person
        matches = 0

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
    return str(longest_run)


main()
