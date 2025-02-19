def main():
    # had to multiply by 100 to get the correct number of coins
    # but no problem, real change owed is divided by 100
    change_owed = get_change() * 100
    quarters = int(get_quarters(change_owed))
    change_owed -= quarters * 25
    dimes = int(get_dimes(change_owed))
    change_owed -= dimes * 10
    nickels = int(get_nickels(change_owed))
    change_owed -= nickels * 5
    pennies = int(get_pennies(change_owed))
    change_owed -= pennies * 1
    coins = int(round(quarters + dimes + nickels + pennies))
    print(coins)


def get_change():
    while True:
        try:
            # staying with float just in case in the future i wanna print the real change owed
            change = float(input("Change Owed: $"))
            if type(change) is float:
                if change > 0:
                    return change
        except ValueError:
            print("Needs to be a number")


def get_quarters(change_owed):
    return change_owed / 25


def get_dimes(change_owed):
    return change_owed / 10


def get_nickels(change_owed):
    return change_owed / 5


def get_pennies(change_owed):
    return change_owed / 1


main()
