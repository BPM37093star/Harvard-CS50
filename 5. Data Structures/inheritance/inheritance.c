#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file %s\n", argv[1]);
        return 1;
    }
    int blockSize = 512;
    uint8_t buffer[blockSize];
    FILE *jpeg = NULL;
    int jpegCount = 0;
    while (fread(buffer, 1, 512, card) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (jpeg != NULL)
            {
                fclose(jpeg);
            }
            char filename[8];
            sprintf(filename, "%03d.jpg", jpegCount);
            jpeg = fopen(filename, "w");
            jpegCount++;
        }
        if (jpeg != NULL)
        {
            fwrite(buffer, 1, 512, jpeg);
        }
    }
    if (jpeg != NULL)
    {
        fclose(jpeg);
    }
    fclose(card);

    return 0;
}
