import sys
from pyfiglet import Figlet
from random import choice

def main():
    figlet = Figlet()
    fonts = figlet.getFonts()
    if len(sys.argv) == 3 and (sys.argv[1] == '-f' or sys.argv[1] == '--font') and sys.argv[2] in fonts:
        word = input('Input: ')
        figlet.setFont(font=sys.argv[2])
        print('')
        print(figlet.renderText(word))
    elif len(sys.argv) == 1:
        word = input('Input: ')
        figlet.setFont(font=choice(fonts))
        print('')
        print(figlet.renderText(word))
    else:
        sys.exit(1)


main()