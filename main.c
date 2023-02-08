#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>

int gameMechanics();
void showScores(int lowScoreScores[], char lowScoreNames[][30]);

// Konstanter för MIN och MAX
const int MINROLL = 1;
const int MAXROLL = 100;

int main()
{
    // TODO
    // Lägg till fråga om spelaren vill spela igen efter varje omgång och
    // gå bara vidare om användaren svarar "ja" eller "nej".
    // Lägg till funktion för att jämföra spelarens poäng med lowscorelistan.
    // Om funktionen ovan ser att spelarens poäng är lägre än någon/några
    // i lowscorelistan, lägg in spelaren på rätt plats och skriv in listan
    // i filen.
    // VID TID ÖVER
    // Ordna listan på först lowscore och sedan tid spenderat på gissningar.
    // Hitta funktioner för tidsmätning i C.


    // Filhantering, skapa fil för lowscore om den inte finns
    FILE *pScores = fopen("score.low", "r");
    char buffer[255];
    if(pScores == NULL)
    {
        pScores = fopen("score.low", "w");
        fprintf(pScores, "Bettan\n50\nCharlie\n60\nTomtom\n70\nFrank\n80\nMona\n90\nBREAK");
    }
    fclose(pScores);


    // Variabler för gissningar, svaret, huvudmenyn och om spelet är igång
        
    bool gameIsRunning = true;
    int mainMenuSelection = 0;    
    char pauseBuffer;
    
    pScores = fopen("score.low", "r");
    char lowScoreValues[10][30];
    char lowScoreNames[5][30];
    int lowScoreScores[5];
    int lineCount = 0;

    while(!feof(pScores) && !ferror(pScores))
    {
        if(fgets(lowScoreValues[lineCount], 30, pScores) != NULL)
        {
            lineCount++;
        }
    }
    fclose(pScores);

    for(int i = 0; i < 10; i++)
    {
        lowScoreValues[i][strlen(lowScoreValues[i])-1] = '\0';
    }

    for(int i = 0; i < 5; i++)
    {
        strcpy(lowScoreNames[i], lowScoreValues[i * 2 + 0]);    
        lowScoreScores[i] = atoi(&lowScoreValues[i * 2 + 1]);
    }
    

    printf("\n");
    
    for(int i = 0; i < 5; i++)
    {
        printf("Names: %s\n", lowScoreNames[i]);
        printf("Scores: %d\n", lowScoreScores[i]);
    }

    // Huvudmenyn, välj en funktion med switch-satser
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
        showScores(lowScoreScores, lowScoreNames);
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

void showScores(int lowScoreScores[], char lowScoreNames[][30])
{
    printf("Low-Score-Listan! Lägre är bättre!\n");
    for(int i = 0; i < 5; i++)
    {
        printf("%d: %s\t%d\n", i+1, lowScoreNames[i], lowScoreScores[i]);
    }
    printf("Slå någons poäng för att komma in på listan.\n");
    scanf(" %c");

    return;    
}