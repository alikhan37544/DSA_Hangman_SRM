#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct HangmanGame {
    char word[20]; // Word to be guessed
    bool guessedLetters[26]; // Array to track guessed letters (using boolean values)
    int attempts; // Number of attempts left
};

void displayWord(struct HangmanGame *game) {
    for (int i = 0; game->word[i] != '\0'; ++i) {
        if (game->guessedLetters[game->word[i] - 'a']) {
            printf("%c ", game->word[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

int main() {
    struct HangmanGame game;

    // List of words for the game
    char *words[] = {"hangman", "programming", "computer", "science", "learning"};

    // Seed for random word selection
    srand(time(NULL));

    // Select a random word from the list
    strcpy(game.word, words[rand() % (sizeof(words) / sizeof(words[0]))]);

    // Initialize guessed letters to false
    for (int i = 0; i < 26; ++i) {
        game.guessedLetters[i] = false;
    }

    game.attempts = 6; // Set the number of attempts

    printf("Welcome to Hangman!\n");

    while (game.attempts > 0) {
        printf("Current word: ");
        displayWord(&game);
        printf("Attempts left: %d\n", game.attempts);
        
        char guess;
        printf("Enter a letter: ");
        scanf(" %c", &guess);

        if (game.guessedLetters[guess - 'a']) {
            printf("You already guessed that letter.\n");
        } else {
            game.guessedLetters[guess - 'a'] = true;

            // Check if the guessed letter is in the word
            bool found = false;
            for (int i = 0; game.word[i] != '\0'; ++i) {
                if (game.word[i] == guess) {
                    found = true;
                    break;
                }
            }

            if (found) {
                printf("Correct guess!\n");
            } else {
                printf("Incorrect guess.\n");
                game.attempts--;
            }
        }

        // Check if the word is guessed completely
        bool guessedCompletely = true;
        for (int i = 0; game.word[i] != '\0'; ++i) {
            if (!game.guessedLetters[game.word[i] - 'a']) {
                guessedCompletely = false;
                break;
            }
        }

        if (guessedCompletely) {
            printf("Congratulations! You guessed the word: %s\n", game.word);
            break;
        }
    }

    if (game.attempts == 0) {
        printf("Sorry, you ran out of attempts. The correct word was: %s\n", game.word);
    }

    return 0;
}
