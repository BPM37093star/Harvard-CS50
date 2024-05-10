from cs50 import get_int

while True:
    bricks = get_int("Height: ")
    if bricks >= 1 and bricks <= 8:
        break
def print_row(num):
    print("#" * num)
for i in range(1, bricks + 1, 1):
    print(" " * (bricks - i), end="")
    print_row(i)
