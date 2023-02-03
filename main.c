#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include <conio.h>

int gameMechanics();

// Konstanter för MIN och MAX
const int MINROLL = 1;
const int MAXROLL = 100;

int main()
{
    // Variabler för gissningar, svaret, huvudmenyn och om spelet är igång
    
    bool gameIsRunning = true;
    int mainMenuSelection = 0;    
    char pauseBuffer;

    while(gameIsRunning)
    {
        char mainMenuInput[5];
        int numberOfGuesses;
    
        while(mainMenuSelection == 0)
            {
                printf("\t*** GISSA ETT TAL ***\n");
                printf("\tHuvudmeny\n\n");
                printf("Välj ett alternativ med 1, 2 eller 3.\n");
                printf("1. Spela\n2. Lowscorelistan\n3. Avsluta\nVal: ");
                scanf(" %s", &mainMenuInput);
                mainMenuSelection = atoi(mainMenuInput);
            }
            
        switch(mainMenuSelection)
        {
        case 1:
        numberOfGuesses = gameMechanics();
        printf("%d\n", numberOfGuesses);
        mainMenuSelection = 0;
        break;

        case 2:
        break;

        case 3:
        printf("Tack för att du spelade!\n");
        gameIsRunning = false;
        break;
        }
    }
    
    return 0;
}

int gameMechanics()
{
    int randomNumber;
    char playerInput[5];
    int playerGuess;
    int numberOfGuesses = 1;
    // Generera random seed och sätt ett slumptal mellan 1 och 100 i randomNumber
    srand(time(0));
    randomNumber = (rand() % MAXROLL) + MINROLL;
    system("cls");

    do
    {
        printf("Skriv in din gissning.\nGissning: ");
        scanf(" %s", &playerInput);
        playerGuess = atoi(playerInput);
                
        if(playerGuess < 1 || playerGuess > 100)
        {
            printf("Gissa på ett nummer från 1 till 100.\n");
        }
        else if(playerGuess < randomNumber)
        {
            printf("Talet är högre!\n");
        }
        else if (playerGuess > randomNumber)
        {
            printf("Talet är lägre!\n");
        }
        else
        {
            printf("Rätt! Bra gissat.\nDu gissade rätt på %d försök.\nTryck Enter för att fortsätta.\n", numberOfGuesses);
        }
        numberOfGuesses++;
    } while (playerGuess != randomNumber);

    return numberOfGuesses - 1;
}