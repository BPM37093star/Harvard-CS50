#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(char bit);

int main(void)
{
    // TODO
    string message = get_string("Input: ");
    int length = strlen(message);
    char messageArray[length];
    strcpy(messageArray, message);
    for (int i = 0; i < length; i++)
    {
        int decimalNumber = (int)(messageArray[i]);
        char binaryNumbers[BITS_IN_BYTE + 1] = "00000000"; // 为了存储终止符 '\0'
        int b = BITS_IN_BYTE - 1;
        for (int j = decimalNumber; j > 0; j = j / 2)
        {
            char changedBit = j % 2;
            binaryNumbers[b] = changedBit + '0';
            b--;
        }
        binaryNumbers[BITS_IN_BYTE] = '\0'; // 添加终止符
        for (int x = 0; x < BITS_IN_BYTE; x++)
        {
            print_bulb(binaryNumbers[x]);
        }
        printf("\n");
    }
}

void print_bulb(char bit)
{
    if (bit == '0')
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == '1')
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
