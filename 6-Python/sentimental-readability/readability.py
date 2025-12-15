# Prmpt the user for text
text = input("Text: ")
lttrs_count = 0
word_count = 0
sntcs_count = 0

for char in text:
    if char.isalpha():
        lttrs_count += 1
    if lttrs_count > 0:

        if word_count == 0:
            word_count = 1  # This for the last word

        if char == " ":
            word_count += 1
        elif char in [".", "?", "!"]:
            sntcs_count += 1
# Calculating the averge of letters and sentences 
avg_lttrs = (lttrs_count / word_count) * 100
avg_sntcs = (sntcs_count / word_count) * 100

# Calculate the Coleman-Liau index
index = round(0.0588 * avg_lttrs - 0.296 * avg_sntcs - 15.8) 

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {int(index)}")