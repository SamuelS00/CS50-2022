from cs50 import get_int


def main():
    height = 0
    while True:
        height = get_int("Height: ")

        if height > 0 and height <= 8:
            break

    # create a range from 1 to the height plus 1
    for i in range(1, height + 1):
        # calculate the whitespace of each line at each iteration of the for
        blank_space = " " * (height - i)
        # calculate the blocks of each line
        block = "#" * i

        pyramid_left = blank_space + block
        pyramid_right = block

        print(pyramid_left + "  " + pyramid_right)



if __name__ == "__main__":
    main()