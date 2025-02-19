def main():
    greeting = input('Greeting: ')
    dollar_amount = get_dollar(greeting)
    print(f'${dollar_amount}')


def get_dollar(i):
    words = i.split()
    first_word = words[0].lower()
    if 'hello' in first_word:
        return 0
    elif first_word.startswith('h'):
        return 20
    else:
        return 100


main()
