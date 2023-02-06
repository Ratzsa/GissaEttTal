#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>

int gameMechanics();
void showScores();

// Konstanter för MIN och MAX
const int MINROLL = 1;
const int MAXROLL = 100;

int main()
{
    // Filhantering, skapa fil för lowscore om den inte finns
    FILE *pScores = fopen("score.low", "r");
    char buffer[255];
    if(pScores == NULL)
    {
        FILE *pScores = fopen("score.low", "w");
        fprintf(pScores, "Bettan\n50\nCharlie\n60\nTomtom\n70\nFrank\n80\nMona\n90");
    }
    fclose(pScores);


    // Variabler för gissningar, svaret, huvudmenyn och om spelet är igång
        
    bool gameIsRunning = true;
    int mainMenuSelection = 0;    
    char pauseBuffer;


    
    //////////////////////////////////////////////////////
    // TEST //////////////////////////////////////////////
    
    pScores = fopen("score.low", "r");
    char lowScoreValues[10][30];
    char lowScoreNames[5][30];
    int lowScoreScores[5];
    int lineCount = 0;
    // char buffer[255];
    
    while (fgets(lowScoreValues[lineCount], 30, pScores))
    {
        lowScoreValues[lineCount][strlen(lowScoreValues[lineCount]) - 1] = '\0';
        lineCount++;
    }
    fclose(pScores);

    int scoreMarker = 0;
    for(int i = 0; i < 10; i++)
    {
        if(i % 2 == 0)
        {
            strcpy(&lowScoreNames[i][30], lowScoreValues[i]);
        }
        else
        {
            lowScoreScores[i] = atoi(&lowScoreValues[i][30]);
        }
        
    }


    printf("\n");
    
    for(int j = 0; j < 10; j++)
    {
        printf("Values: %s\n", lowScoreValues[j]);
        printf("Names: %s\n", lowScoreNames[j]);
        printf("Scores: %d\n", lowScoreScores[j]);
    }

    /*
    // fscanf(ftpr, "r%d=%d\n", &n, &var);
    for (int i = 0; i < 10; i++)
    {
        fscanf(pScoresInGame, "%s\n", &lowScoreNames[i]);
        i++;
        fscanf(pScoresInGame, "%d\n", &lowScoreScores[i]);
    }

    for(int j = 0; j < 5; j++)
    {
        printf("%s\t%d\n", lowScoreNames[j], lowScoreScores[j]);
    }
    fclose(pScores);

    */
    //////////////////////////////////////////////////////
    // TEST //////////////////////////////////////////////

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
        showScores();
        mainMenuSelection = 0;
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

void showScores()
{
    char scoreNames[5];
    int scoreScores[5];
    FILE *pScores = fopen("score.low", "r");
    char buffer[255];
    // fscanf(ftpr, "r%d=%d\n", &n, &var);
    for (int i = 0; i < 5; i++)
    {
        fscanf(pScores, "%s", &scoreNames[i]);
        fscanf(pScores, "%d", &scoreScores[i]);
    }

    for(int j = 0; j < 5; j++)
    {
        printf("%s\t%d\n", scoreNames[j], scoreScores[j]);
    }
    fclose(pScores);
    return;
    
}