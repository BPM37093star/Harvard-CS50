#include <cs50.h>
#include <stdio.h>

void print_row(int bricks);
int n;
int main(void)
{
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1);
    for (int i = 1; i <= n; i++)
    {
        for (int spaces = n - i; spaces > 0; spaces--)
        {
            printf(" ");
        }
        print_row(i);
    }
}
void print_row(int bricks)
{
    for (int j = 1; j <= bricks; j++)
    {
        printf("#");
    }
    printf("  ");
    for (int m = 1; m <= bricks; m++)
    {
        printf("#");
    }
    printf("\n");
}
