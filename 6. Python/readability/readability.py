from cs50 import get_string

Text = get_string("Text: ")

def count_letters():
    letters_num = 0
    for c in Text:
        if c.isalpha():
            letters_num += 1
    return letters_num

def count_words():
    words = Text.split()
    words_num = len(words)
    return words_num

def count_sentences():
    sentences_num = 0
    for c in Text:
        if c == '.' or c == '?' or c == '!':
            sentences_num += 1
    return sentences_num

L = count_letters() / count_words() * 100
S = count_sentences() / count_words() * 100
index = 0.0588 * L - 0.296 * S - 15.8

if index > 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print(f"Grade {round(index)}")
