#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct SwapData {
    int cardId;
    int newPlace;
};

void swap(int arr[], int a, int b) {
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

void skipLine() {
    char *line = NULL;
    size_t buffSize = 0;
    getline(&line, &buffSize, stdin);
    free(line);
}

int readNumber() {
    int val;
    char *line = NULL;
    size_t buffSize = 0;
    getline(&line, &buffSize, stdin);
    sscanf(line, "%d", &val);
    free(line);
    return val;
}

char *readLine() {
    char *line = NULL;
    size_t buffSize = 0;
    if(getline(&line, &buffSize, stdin) < 0) {
        char *empty = (char *) malloc(1);
        empty[0] = '\0';
        return empty;
    } else {
        return line;
    }
}

int main() {

    char *values[] = {" ", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
    char *colors[] = {"Clubs", "Diamonds", "Hearts", "Spades"};

    int numOfSets = readNumber();
    skipLine();

    for (int i = 0; i < numOfSets; ++i) {
        int numOfSwaps = readNumber();
        struct SwapData *arrayOfSwaps = (struct SwapData *) malloc(numOfSwaps * sizeof(struct SwapData));

        for (int j = 0; j < numOfSwaps; ++j) {
            char *line = readLine();
            char *ptr = line;
            int charsRead = 0;
            for (int place = 1; place < 53; ++place) {
                int card;
                sscanf(ptr, "%d%n", &card, &charsRead);
                ptr += charsRead;

                if(card != place) {
                    arrayOfSwaps[j].cardId = card;
                    arrayOfSwaps[j].newPlace = place;
                    break;
                }
            }
            free(line);
        }

        int deck[53];
        for (int j = 1; j < 53; ++j) {
            deck[j] = j;
        }

        while(1) {
            char *line = readLine();
            if(strlen(line) == 0 || (strlen(line) == 1 && line[0] == '\n')) {
                free(line);
                break;
            }
            int swapId;
            sscanf(line, "%d", &swapId);
            swap(deck, arrayOfSwaps[swapId - 1].cardId, arrayOfSwaps[swapId - 1].newPlace);
            free(line);
        }

        for (int j = 1; j < 53; ++j) {
            int id = deck[j];
            int color = 0, value = 0;
            if(id % 13) {
                color = id / 13;
                value = id - color * 13;
            } else {
                color = id / 13 - 1;
                value = id - color * 13;
            }
            printf("%s of %s\n", values[value], colors[color]);
        }
        printf("\n");

        free(arrayOfSwaps);
    }

    return 0;
}
