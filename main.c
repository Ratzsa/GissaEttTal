/*
Encoding: ISO 8859-15
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
// Överdrivet många headerfiler

// Konstanter för MIN och MAX
const int MINROLL = 1;
const int MAXROLL = 100;
const int MAXSTRING = 30;
const int MAXELEMENTS = 5;
const char fileName[] = "scores.low";

// Struct för att spara spelarens lowscore
typedef struct
{
    time_t time;
    char name[30];
    int score;
} lowScore_t;

lowScore_t scores[5];

// Funktioner
void gameMechanics();
void showScores();
void updateScores(int numberOfGuesses);
void writeToFile(void *scorelist, size_t size);
void readFromFile(void *scorelist, size_t size);
void hitEnter();
void clearConsole();
void splash();
void redColour();
void yellowColour();
void resetColour();
void greenColour();

int main()
{
    // VID TID ÖVER
    // Ordna listan på först lowscore och sedan tid spenderat på gissningar.
    // Hitta funktioner för tidsmätning i C.

    // För att skriva ut svenska tecken, åäö
    SetConsoleOutputCP(28605);
    SetConsoleCP(28605);

    bool gameIsRunning = true;
    int mainMenuSelection = 0;
    
    // Nollar scores så det inte kommer in nån eventuell skräpdata
    memset(scores, 0, sizeof(scores));

    // Läser in lowscore-listan om den finns sparad
    readFromFile(scores, sizeof(scores));

    splash();

    // Huvudmenyn, välj en funktion med switch-satser
    while(gameIsRunning)
    {
        char mainMenuInput[5];
        mainMenuSelection = 0;
    
        while(mainMenuSelection == 0)
            {
                clearConsole();
                greenColour();
                printf("\t*** GISSA ETT TAL ***\n");
                printf("\tHuvudmeny\n\n");
                yellowColour();
                printf("Välj ett alternativ med 1, 2 eller 3.\n");
                printf("1. Spela\n2. Lowscorelistan\n3. Avsluta\nVal: ");
                scanf(" %s", mainMenuInput);
                resetColour();
                mainMenuSelection = atoi(mainMenuInput);
            }
            
        switch(mainMenuSelection)
        {
            case 1:
                gameMechanics();
                break;

            case 2:
                showScores();
                break;

            case 3:
                clearConsole();
                printf("Tack för att du spelade!\n");
                gameIsRunning = false;
                break;

            default:
                break;
        }
    }    
    return 0;
}

// Själva spelet
void gameMechanics()
{
    // Variabler som behövs
    int randomNumber;
    char playerInput[MAXELEMENTS];
    int playerGuess = 0;
    int numberOfGuesses = 0;
    int endGame = 2;
    int tempIfErrorInput = 0; // Ifall man råkar gissa nåt som inte är en siffra eller under 1/över 100

    srand(time(0)); // Generera random seed

    while(endGame != 1)
    {
        randomNumber = (rand() % MAXROLL) + MINROLL; // Generera ett slumpmässigt nummer
        numberOfGuesses = 0;

        do
        {
            clearConsole();
            if(numberOfGuesses != 0)
            {
                for (int i = 0; i < strlen(playerInput); i++)
                {
                    if (!isdigit(playerInput[i]))
                    {
                        yellowColour();
                        printf("Du har inte skrivit in ett heltal.\n");
                        resetColour();
                        numberOfGuesses--;
                        playerGuess = tempIfErrorInput;
                        break;
                    }
                }

                if(playerGuess < 1 || playerGuess > 100)
                {
                    yellowColour();
                    printf("Gissa bara på heltal från 1 till 100.\n");
                    resetColour();
                    playerGuess = tempIfErrorInput; // Återställer gissningen
                }
                if(playerGuess != 0)
                {
                    printf("Gissning: %d\n", playerGuess);
                }
                if(playerGuess < randomNumber && playerGuess != 0)
                {
                    greenColour();
                    printf("Talet är högre!\n");
                    resetColour();
                }
                else if (playerGuess > randomNumber && playerGuess != 0)
                {
                    redColour();
                    printf("Talet är lägre!\n");
                    resetColour();
                }
            }
            tempIfErrorInput = playerGuess;
            printf("Skriv in din gissning: ");
            scanf(" %10s", playerInput);
            playerGuess = atoi(playerInput);
            numberOfGuesses++;
        }while (playerGuess != randomNumber);

        clearConsole();
        printf("Rätt! Bra gissat.\nDu gissade rätt på %d försök.\n", numberOfGuesses);
        updateScores(numberOfGuesses);
        
        endGame = 1;

        fflush(stdin);        
    }
    return;
}

// Skriv ut low-score-listan
void showScores()
{
    fflush(stdin);
    clearConsole();

    printf("Low-Score-Listan! Lägre är bättre!\n");
    
    for(int i = 0; i < 5; i++)
    {
        printf("%d: ", i + 1);
        if(scores[i].score != 0)
        {
            printf("%-25s\t", scores[i].name);
            char printTime[100];
            struct tm *convertedTime;
            convertedTime = gmtime(&scores[i].time);
            convertedTime->tm_hour++; // För att ha vår tid och inte GMT
            if(convertedTime->tm_hour >= 24)
            {
                convertedTime->tm_hour = 0;
            }
            strftime(printTime, 100, "%y-%m-%d %H:%M", convertedTime);

            printf("%d\t", scores[i].score);
            printf("%s", printTime);
        }
        printf("\n");
    }

    printf("Slå någons poäng för att komma in på listan. Tryck enter för att fortsätta.\n");
    hitEnter();
    fflush(stdin);
    clearConsole();
    return;    
}

// Jämför antal gissningar med low-score-listan och uppdatera arrayerna.
// Om antalet gissningar är lägre än någon på listan, uppdatera listan och
// skriv in listan i filen igen.
void updateScores(int numberOfGuesses)
{
    int marker = 0;
    char enterName[MAXSTRING];
    char tempInput[10];
    char tempTimes[10];
    char updatedList[200];
    char updatedTimes[200];
    time_t timeNow = time(0);
    fflush(stdin);

    for(int i = 0; i < MAXELEMENTS; i++)
    {
        // Hitta platsen på listan där poängen ska in
        if(numberOfGuesses < scores[i].score)
        {
            break;
        }
        if(scores[i].score != 0)
        {
            marker++;
        }        
    }

    if(marker < 5) // Om poängen ska in på listan..
    {
        greenColour();
        printf("Du tog dig in på lowscore-listan! Skriv in ditt namn: ");
        scanf(" %25s", enterName);
        resetColour();

        for(int i = 4; i > marker; i--)
        {
            // Flytta ner allt under på listan
            scores[i].score = scores[i-1].score;
            strcpy(scores[i].name, scores[i - 1].name);
            scores[i].time = scores[i - 1].time;
        }

        // Lägg till namn och poäng på rätt plats i listan
        scores[marker].score = numberOfGuesses;
        strcpy(scores[marker].name, enterName);
        scores[marker].time = timeNow;

        writeToFile(scores, sizeof(scores));
    }

    hitEnter();
    fflush(stdin);
}

void writeToFile(void *scorelist, size_t size)
{
    FILE *scoreFile = fopen(fileName, "wb");
    fwrite(scorelist, size, 1, scoreFile);
    fclose(scoreFile);
}

void readFromFile(void *scorelist, size_t size)
{
    FILE *scoreFile = fopen(fileName, "rb");
    if(scoreFile != 0)
    {
        fread(scorelist, size, 1, scoreFile);
        fclose(scoreFile);
    }
}

// Funktion skapad bara för att kunna pausa innan man rensar skärmen och låter användaren trycka på enter
void hitEnter()
{
    while (1) 
    {
        char pressEnter[MAXSTRING];
        gets(pressEnter);
        if(strcmp(pressEnter,"") == 0 || strcmp(pressEnter,"") != 0)
        {
        Sleep(100);
        break;
        }
    }
    return;
}

void clearConsole()
{
    printf("\x1b[H\x1b[2J\x1b[3J");
}

void splash()
{
    clearConsole();
    printf("Engaging variable environment\nProgram: Gissa Talet version 0.12.7\n");
    yellowColour();
    printf("Unlocking arsenal\nLocking targets 0x7e33ffa3 - 0.ff3213b1\n");
    redColour();
    printf("Launching Skynet\nInitiate\n");
    resetColour();
    printf("Version 23.10.a successful\nDTAH\n");
    Sleep(3000);
    clearConsole();
    printf("Ignore that.\nEverything is fine.\nSkynet is imaginary.\n");
    greenColour();
    printf("Have a nice day.\n");
    resetColour();
    Sleep(3000);
}

void redColour() 
{
  printf("\033[1;31m");
}

void yellowColour()
{
  printf("\033[1;33m");
}

void resetColour() 
{
  printf("\033[0m");
}

void greenColour()
{
    printf("\033[0;32m");
}