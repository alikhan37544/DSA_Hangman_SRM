#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void displayHangman(int attempts) {
    // Implement code to display the hangman figure based on the number of attempts left
    // (You can find hangman ASCII art online and print different parts based on the attempts)
}

void displayWord(char *word, char *guessedLetters) {
    // Implement code to display the current state of the word with guessed letters filled in
    // (Display underscores for unguessed letters and reveal correct guesses)
}

int main() {
    char *words[] = {"programming", "hangman", "computer", "science", "developer", "learning", "challenge", "victory", "knowledge"};
    srand(time(NULL));
    int randomIndex = rand() % (sizeof(words) / sizeof(words[0]));
    char *word = words[randomIndex];
    int wordLength = strlen(word);
    int attempts = 6;
    char guessedLetters[wordLength];
    memset(guessedLetters, 0, sizeof(guessedLetters));

    while (attempts > 0) {
        printf("Current word: ");
        displayWord(word, guessedLetters);
        printf("Attempts left: %d\n", attempts);
        char guess;
        printf("Enter a letter: ");
        scanf(" %c", &guess);

        // Check if the guessed letter is in the word
        int found = 0;
        for (int i = 0; i < wordLength; ++i) {
            if (word[i] == guess) {
                guessedLetters[i] = guess;
                found = 1;
            }
        }

        if (!found) {
            attempts--;
        }

        // Check if the word is guessed completely
        int guessedCompletely = 1;
        for (int i = 0; i < wordLength; ++i) {
            if (guessedLetters[i] == 0) {
                guessedCompletely = 0;
                break;
            }
        }

        if (guessedCompletely) {
            printf("Congratulations! You guessed the word: %s\n", word);
            break;
        }

        displayHangman(attempts);
    }

    if (attempts == 0) {
        printf("Sorry, you ran out of attempts. The correct word was: %s\n", word);
    }

    return 0;
}
