coins = 0
while True:
    try:
        # Prompt the user for change
        change = float(input("Change: ").strip())
    except ValueError:
        continue

    # Check if the change is a positive intiger otherwise reprompt the user 
    if change < 0:
        continue
    else:
        break
# covernt dollar to cents
cents = change * 100

# iterate and check what coin to return 
while cents > 0:
    if cents >= 25:
        cents -= 25
        coins += 1
    elif 10 <= cents < 25:
        cents -= 10
        coins += 1
    elif 5 <= cents < 10:
        cents -= 5
        coins += 1
    else:
        cents -= 1
        coins += 1

print(coins)
