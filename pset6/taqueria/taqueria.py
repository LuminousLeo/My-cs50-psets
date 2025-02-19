def main():
    menu = {
        "Baja Taco": 4.00,
        "Burrito": 7.50,
        "Bowl": 8.50,
        "Nachos": 11.00,
        "Quesadilla": 8.50,
        "Super Burrito": 8.50,
        "Super Quesadilla": 9.50,
        "Taco": 3.00,
        "Tortilla Salad": 8.00
    }

    items = list()
    price = 0
    while True:
        try:
            user_input = input('Item: ')
        except EOFError:
            print()
            break

        if user_input.title() in menu:
            items.append(user_input.title())

    for i in range(len(items)):
        try:
            price += menu[items[i]]
        except KeyError:
            print(f'The price of {items[i]} is not in the dictionary')

    print('Total: $%.2f' %price)


main()