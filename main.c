#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

int gameMechanics(int lowScoreScores[], char lowScoreNames[][30]);
void showScores(int lowScoreScores[], char lowScoreNames[][30]);
void updateScores(int lowScoreScores[], char lowScoreNames[][30], int numberOfGuesses);
void hitEnter();

// Konstanter för MIN och MAX
const int MINROLL = 1;
const int MAXROLL = 100;
const int MAXSTRING = 30;
const int MAXELEMENTS = 5;

int main()
{
    // TODO
    // *KLAR* Lägg till fråga om spelaren vill spela igen efter varje omgång och
    // *KLAR* gå bara vidare om användaren svarar "ja" eller "nej".
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
    char lowScoreValues[10][MAXSTRING];
    char lowScoreNames[MAXELEMENTS][MAXSTRING];
    int lowScoreScores[MAXELEMENTS];
    int lineCount = 0;

    while(!feof(pScores) && !ferror(pScores))
    {
        if(fgets(lowScoreValues[lineCount], MAXSTRING, pScores) != NULL)
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
        lowScoreScores[i] = atoi(lowScoreValues[i * 2 + 1]);
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
                numberOfGuesses = gameMechanics(lowScoreScores, lowScoreNames);
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

// Själva spelet
int gameMechanics(int lowScoreScores[], char lowScoreNames[][MAXSTRING])
{
    // Variabler som behövs
    int randomNumber;
    char playerInput[MAXELEMENTS];
    int playerGuess;
    int numberOfGuesses;
    int endGame = 2;
    int answerQuestion;
    char endGameAnswer[100];

    while(endGame != 1)
    {
        // Generera random seed och sätt ett slumptal mellan 1 och 100 i randomNumber
        srand(time(0));
        randomNumber = (rand() % MAXROLL) + MINROLL;
        system("cls");
        numberOfGuesses = 0;
        answerQuestion = 1;

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
            numberOfGuesses++;
        }while (playerGuess != randomNumber);

        printf("Rätt! Bra gissat.\nDu gissade rätt på %d försök.\n", numberOfGuesses);
        updateScores(lowScoreScores, lowScoreNames, numberOfGuesses);

        while(answerQuestion != 0)
        {
            printf("Vill du spela igen? (Ja/Nej): ");
            scanf(" %s", endGameAnswer);
            for (int i = 0; i < strlen(endGameAnswer); i++)
            {
                endGameAnswer[i] = tolower(endGameAnswer[i]);
            }
            printf("%s\n", endGameAnswer);

            if(!strcmp(endGameAnswer, "ja"))
            {
                answerQuestion = 0;
            }
            else if(!strcmp(endGameAnswer, "nej"))
            {
                answerQuestion = 0;
                endGame = 1;
            }
        }
    }

    

    return numberOfGuesses;
}

// Skriv ut low-score-listan
void showScores(int lowScoreScores[], char lowScoreNames[][30])
{
    printf("Low-Score-Listan! Lägre är bättre!\n");
    for(int i = 0; i < 5; i++)
    {
        printf("%d: %-30s\t%d\n", i+1, lowScoreNames[i], lowScoreScores[i]);
    }
    printf("Slå någons poäng för att komma in på listan.\n");
    scanf(" %c");

    return;    
}

// Jämför antal gissningar med low-score-listan och uppdatera arrayerna.
// Om antalet gissningar är lägre än någon på listan, uppdatera listan och
// skriv in listan i filen igen.
void updateScores(int lowScoreScores[], char lowScoreNames[][MAXSTRING], int numberOfGuesses)
{
    int marker = 0;
    char enterName[MAXSTRING];
    char tempInput[10];

    for(int i = 0; i < MAXELEMENTS; i++)
    {
        if(numberOfGuesses < lowScoreScores[i]);
        {
            break;
        }
        marker++;
    }

    if(marker < 5)
    {
        printf("Du tog dig in på lowscore-listan! Skriv in ditt namn: ");
        scanf(" %s", enterName);

        for(int i = 4; i > marker; i--)
        {
            lowScoreScores[i] = lowScoreScores[i-1];
            strcpy(lowScoreNames[i], lowScoreNames[i-1]);
        }
        lowScoreScores[marker] = numberOfGuesses;
        strcpy(lowScoreNames[marker], enterName);
    }
    showScores(lowScoreScores, lowScoreNames);
    fflush(stdin);
    return;
}
