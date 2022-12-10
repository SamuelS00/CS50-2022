from cs50 import get_string


def calculates_coleman_liau_index(l, s):
    return round(0.0588 * l - 0.296 * s - 15.8)


def calculates_avgr_letters(text: str):
    letters = 0

    for c in text:
        if c.isalpha():
            letters += 1

    return letters


def calculates_avgr_words(text: str):
    words = 1

    for c in text:
        if c.isspace():
            words += 1

    return words


def calculates_avgr_sentences(text: str):
    sentences = 0

    for c in text:
        if c in (".", "!", "?"):
            sentences += 1

    return sentences


def main():
    text = get_string("Text: ")

    avgr_letters = calculates_avgr_letters(text)
    avgr_words = calculates_avgr_words(text)
    avgr_sentences = calculates_avgr_sentences(text)

    l = avgr_letters / avgr_words * 100
    s = avgr_sentences / avgr_words * 100

    index = calculates_coleman_liau_index(l, s)

    if (index < 1):
        print("Before Grade 1")

    if (index > 15):
        print("Grade 16+")

    if (index > 1 and index < 16):
        print(f"Grade {index}")


if __name__ == "__main__":
    main()
