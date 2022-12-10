from cs50 import get_string


def main():
    digits = get_string("Number: ")
    card_length = len(digits)

    if card_length < 13 or card_length > 16:
        return "INVALID"

    last_digit_sum = check_luhn_digit(digits, card_length)

    if last_digit_sum != "0":
        return "INVALID"

    card_flag = check_card_length(digits)

    return card_flag


def check_card_length(digits):
    first_digits = digits[0:2]

    if first_digits[0] in ("4"):
        return "VISA"
    elif first_digits in ("34", "37"):
        return "AMEX"
    elif first_digits in ("51", "52", "53", "54", "55"):
        return "MASTERCARD"
    else:
        return "INVALID"


def check_luhn_digit(digits, length):
    arr_digits = []
    sum_all_digits = 0

    # condition starts at False to not get the last number of the array
    condition = False

    # adds each number from the string number into an array
    for i in range(length, 0, -1):
        digit = int(digits[i - 1])

        # if the condition is true multiply the number by 2 and add it to the array
        if condition is True:
            arr_digits.append(digit * 2)
            # set to false to not get the next digit
            condition = False
        else:
            arr_digits.append(digit)
            # set to false to get the next digit
            condition = True

    # checks if there is a composite number, if it exists, digits of that number are added
    for i in range(0, len(arr_digits)):
        digit = int(arr_digits[i])

        if digit > 9:
            d = str(arr_digits[i])
            sum_digits = int(d[0]) + int(d[1])
            arr_digits[i] = sum_digits

    # sum all the digits of the array of digits
    for num in arr_digits:
        sum_all_digits += int(num)

    # returns the last character of the string
    return str(sum_all_digits)[-1]


if __name__ == "__main__":
    print(main())
