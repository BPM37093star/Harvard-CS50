
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    int countLetters = count_letters(text);
    int countWords = count_words(text);
    int countSentences = count_sentences(text);
    float L = (float)countLetters / (float)countWords * 100;
    float S = (float)countSentences / (float)countWords * 100;
    int grade = round(0.0588 * L - 0.296 * S - 15.8);
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }

}
int count_letters(string text)
{
    int countLetters = 0;
    char originalText[strlen(text)];
    strcpy(originalText, text);
    int length = strlen(text);
    for (int i = 0; i < length; i++)
    {
        if ((int)(originalText[i]) >= 65 && (int)(originalText[i]) <= 122)
        {
            countLetters += 1;
        }
    }
    return countLetters;
}


int count_words(string text)
{
    int countWords = 1;
    char originalText[strlen(text)];
    strcpy(originalText, text);
    int length = strlen(text);
    for (int i = 0; i < length; i++)
    {
        if (isspace(originalText[i]))
        {
            countWords++;
        }
    }
    return countWords;
}

int count_sentences(string text)
{
    int countSentences = 0;
    char originalText[strlen(text)];
    strcpy(originalText, text);
    int length = strlen(text);
    for (int i = 0; i < length; i++)
    {
        if (originalText[i] == '.' || originalText[i] == '?' || originalText[i] == '!')
        {
            countSentences++;
        }
    }
    return countSentences;
}
