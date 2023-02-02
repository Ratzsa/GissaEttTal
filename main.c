#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include <conio.h>

void gameMechanics();
int mainMenu(int mainMenuSelection);

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
        mainMenu(mainMenuSelection);
            
        switch(mainMenuSelection)
        {
        case 1:
        gameMechanics();
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

void gameMechanics()
{
    int numberOfGuesses = 0;
    int playerGuess = 101;
    int randomNumber;
    char playerInput[5];
    // Generera random seed och sätt ett slumptal mellan 1 och 100 i randomNumber
    srand(time(0));
    randomNumber = (rand() % MAXROLL) + MINROLL;

    do
    {
        printf("Skriv in din gissning.\nGissning: ");
        scanf(" %4s", &playerInput);
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
            fflush(stdin);
        }
        numberOfGuesses++;
        fflush(stdin);
    } while (playerGuess != randomNumber);

    return;
}

int mainMenu(int mainMenuSelection)
{
    char mainMenuInput[5];
    
    while(mainMenuSelection == 0)
        {
            printf("\t*** GISSA ETT TAL ***\n");
            printf("\tHuvudmeny\n\n");
            printf("Välj ett alternativ med 1, 2 eller 3.\n");
            printf("1. Spela\n2. Lowscorelistan\n3. Avsluta\nVal: ");
            scanf(" %4s", &mainMenuInput);
            mainMenuSelection = atoi(mainMenuInput);
        }    

    return mainMenuSelection;
}