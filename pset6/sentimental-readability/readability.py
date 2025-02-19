def main():
    # get user's input
    text = input("Text: ")
    number_of_letters = count_letters(text)
    number_of_words = count_words(text)
    number_of_sentences = count_sentences(text)
    letters_100 = (number_of_letters / number_of_words) * 100
    sentences_100 = (number_of_sentences / number_of_words) * 100
    grade_level = round(
        (0.0588 * letters_100) - (0.296 * sentences_100) - 15.8
    )  # Coleman-Liau index

    if grade_level >= 16:
        print("Grade 16+")
    elif grade_level < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {grade_level}")


def count_letters(text):
    letters = 0
    for i in text:
        if i.isalpha():
            letters += 1

    return letters


def count_words(text):
    words = text.count(" ") + 1
    return words


def count_sentences(text):
    sentences = 0
    for i in text:
        if i in ".!?":
            sentences += 1

    return sentences


main()
