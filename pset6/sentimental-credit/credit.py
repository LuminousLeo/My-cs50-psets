def main():
    # get user input and card length
    card_number = int(input("Number: "))
    card_length = len(str(card_number))

    # check card length
    if card_length != 13 and card_length != 15 and card_length != 16:
        print("INVALID")
        return

    tmp = card_number
    ndouble_sum = 0
    double_sum = 0

    # lunh's algorithm
    while tmp > 0:
        last = tmp % 10
        tmp = int(tmp / 10)
        ndouble_sum += last

        s_last = tmp % 10
        tmp = int(tmp / 10)
        i = doubled_sum(s_last)
        double_sum += i

    total = ndouble_sum + double_sum

    if total % 10 != 0:  # validity of the card
        print("INVALID")
        return
    elif card_length == 13:  # visa validity
        print("VISA")
        return
    elif s_last == 4 and card_length == 16:  # visa validaty again
        print("VISA")
        return
    elif card_length == 15:  # AMEX validity
        Amex(card_number)
        return
    elif card_length == 16:  # MASTERCARD validity
        Mastercard(card_number)


def doubled_sum(s_last):
    s_last = s_last * 2

    if s_last >= 10:
        k = s_last % 10
        s_last = int(s_last / 10)
        l = s_last % 10
        total = k + l
        return total

    return s_last


def Amex(card_number):
    while card_number > 38:
        card_number = int(card_number / 10)

    if card_number == 34 or card_number == 37:
        print("AMEX")
        return
    else:
        print("INVALID")

    return


def Mastercard(card_number):
    while card_number > 55:
        card_number = int(card_number / 10)

    if card_number in range(51, 56):
        print("MASTERCARD")
        return
    else:
        print("INVALID")

    return


main()
