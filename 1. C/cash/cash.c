#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int cents;
    int total;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);
    int quarters = 0, dimes = 0, nickels = 0, pennies = 0;
    if (cents >= 25)
    {
        quarters += cents / 25;
        cents = cents - quarters * 25;
        if (cents >= 10)
        {
            dimes += cents / 10;
            cents = cents - dimes * 10;
            if (cents >= 5)
            {
                nickels += cents / 5;
                cents -= nickels * 5;
                if (cents >= 1)
                {
                    pennies += cents;
                }
            }
            else{
                pennies += cents;
            }
        }
        else if (cents >=5)
        {
            nickels += cents / 5;
            cents = cents - nickels * 5;
            if (cents >= 1)
            {
                pennies += cents;
            }
        }
        else {
            pennies += cents;
        }
    }
    else if (cents >= 10)
    {
        dimes += cents / 10;
        cents = cents - dimes * 10;
        if (cents >= 5)
        {
            nickels += cents / 5;
            cents = cents - nickels * 5;
            if (cents >= 1)
            {
                pennies += cents;
            }
        }
        else {
            pennies += cents;
        }
    }
    else if (cents >= 5)
    {
        nickels += cents / 5;
        cents = cents - nickels * 5;
        if (cents >= 1)
        {
            pennies += cents;
        }
    }
    else{
        pennies += cents / 1;
    }
    printf("%d\n", quarters + dimes + nickels + pennies);
}
