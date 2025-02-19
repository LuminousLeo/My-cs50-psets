while True:
    try:
        height = int(input("Height: "))
        if height > 0 and height < 9:
            break
    except ValueError:
        print("Height needs to be a number in between 1 and 8")

for column in range(height):
    for space in range(height - column - 1):
        print(" ", end="")
    for row in range(column + 1):
        print("#", end="")
    print("")
