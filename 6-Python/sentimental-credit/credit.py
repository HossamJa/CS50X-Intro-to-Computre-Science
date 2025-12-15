
def main():
    # Prompt the user for a cridit card number
    number = input("Number: ").strip()
    if cheksum(number):
        card_name(number)
    else:
        print("INVALID")

def cheksum(number):
    mult_sum = 0
    non_mult_sum = 0

    # convert the strng number into a reversed list of digits
    digits = [int(d) for d in reversed(number)]
    # get the digit second to the last digit and so on
    for i, digit in enumerate(digits):
        if i % 2 == 0:
            # Add sum of these digits to the sum of digits that weren't multiplied by 2
            non_mult_sum += digit
        else:
            # multiply it by 2
            mult_num = digit * 2

            # Adding those products’ digits together in sum1
            if mult_num > 9:
                for digit in str(mult_num):
                    mult_sum += int(digit)
            else:
                mult_sum += mult_num

    # Check if the total is 0, otherwise invalid
    if (mult_sum + non_mult_sum) % 10 == 0:
        return True
    return False

def card_name(number):
    # get the number of digits in that credit card number
    digit_count = len(number)

    # check which credit card is that number belongs to.
    # American Express uses 15 | start with 34 or 37
    if digit_count == 15 and number[:2] in ["34", "37"]:
        print("AMEX")
    # MasterCard uses 16 | start with 51, 52, 53, 54, or 55
    elif digit_count == 16 and number[:2] in ["51", "52", "53", "54", "55"]:
        print("MASTERCARD")
    # Visa uses 13 and 16 | start with 4
    elif digit_count in [13, 16] and number[0] == "4":
        print("VISA")
    else:
        print("INVALID")


main()