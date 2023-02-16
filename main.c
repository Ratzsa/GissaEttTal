#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <locale.h>
// �verdrivet m�nga headerfiler

// Konstanter f�r MIN och MAX
const int MINROLL = 1;
const int MAXROLL = 100;
const int MAXSTRING = 30;
const int MAXELEMENTS = 5;
const char fileName[] = "scores.low";

// Struct f�r att spara spelarens lowscore
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
void writeToFile(char *p, size_t size);
void readFromFile(char *p, size_t size);
void hitEnter();

int main()
{
    // TODO
    // *KLAR* L�gg till fr�ga om spelaren vill spela igen efter varje omg�ng och
    // *KLAR* g�r bara vidare om anv�ndaren svarar "ja" eller "nej".
    // *KLAR* L�gg till funktion f�r att j�mf�ra spelarens po�ng med lowscorelistan.
    // *KLAR* Om funktionen ovan ser att spelarens po�ng �r l�gre �n n�gon/n�gra
    // *KLAR* i lowscorelistan, l�gg in spelaren p� r�tt plats och skriv in listan
    // *KLAR* i filen.
    // L�gg till tid i lowscore!
    // VID TID �VER
    // Ordna listan p� f�rst lowscore och sedan tid spenderat p� gissningar.
    // Hitta funktioner f�r tidsm�tning i C.

    

    /*
    // Filhantering, skapa fil f�r lowscore om den inte finns
    FILE *pScores = fopen("score.low", "r");
    if(pScores == NULL) // Om filen inte finns, skapa den och skriv in en (tom) topplista
    {
        pScores = fopen("score.low", "w");
        fprintf(pScores, "\n\n\n\n\n\n\n\n\n\nBREAK");
    }
    fclose(pScores);

    // Skapa fil för att spara tider om den inte finns
    FILE *pTimes = fopen("time.low", "r");
    if(pTimes == NULL) // Om filen inte finns, skapa den och skriv in en (tom) tidslista
    {
        pTimes = fopen("time.low", "w");
        fprintf(pTimes, "\n\n\n\n\nBREAK");
    }
    fclose(pTimes);
    */

    // Variabler för gissningar, svaret, huvudmenyn och om spelet är igång
    
    
    /*
    char lowScoreValues[10][MAXSTRING];
    char lowScoreTimeBuffer[10][MAXSTRING];
    char lowScoreNames[MAXELEMENTS][MAXSTRING];
    int lowScoreScores[MAXELEMENTS];
    int lowScoreTimes[MAXELEMENTS];
    int lineCount = 0;

    pScores = fopen("score.low", "r"); // Öppna filen för att läsa topplistan
    while(!feof(pScores) && !ferror(pScores))
    {
        // Lägg över innehållet i filen i en string-array (char[][])
        // Skulle behöva lära mig hur man lägger över innehållet i rätt sorts array direkt
        if(fgets(lowScoreValues[lineCount], MAXSTRING, pScores) != NULL)
        {
            lineCount++; // Öka indexnumret
        }
    }
    fclose(pScores);

    lineCount = 0;
    pTimes = fopen("time.low", "r"); // Öppna filen för att läsa tidslistan
    while(!feof(pTimes) && !ferror(pTimes))
    {
        if(fgets(lowScoreTimeBuffer[lineCount], MAXSTRING, pTimes) != NULL)
        {
            lineCount++;
        }
    }
    fclose(pScores);

    for(int i = 0; i < 10; i++)
    {
        lowScoreValues[i][strlen(lowScoreValues[i])-1] = '\0'; // Tar bort \n från varje element
    }

    for(int i = 0; i < MAXELEMENTS; i++)
    {
        lowScoreTimeBuffer[i][strlen(lowScoreTimeBuffer[i])-1] = '\0';
    }

    for(int i = 0; i < 5; i++)
    {
        strcpy(lowScoreNames[i], lowScoreValues[i * 2 + 0]); // Kopierar namnen till rätt array...    
        lowScoreScores[i] = atoi(lowScoreValues[i * 2 + 1]); // ... och poängen till rätt array
    }

    for(int i = 0; i < 5; i++)
    {
        lowScoreTimes[i] = atoi(lowScoreTimeBuffer[i]); // Lägger in tider som int i rätt array
    }

    */

    // F�r att skriva ut svenska tecken, ���
    SetConsoleOutputCP(28605);
    SetConsoleCP(28605);

    bool gameIsRunning = true;
    int mainMenuSelection = 0;
    
    // Nollar scores s� det inte kommer in n�n eventuell skr�pdata
    memset(scores, 0, sizeof(scores));

    // L�ser in lowscore-listan om den finns sparad
    readFromFile(scores, sizeof(scores));

    // Huvudmenyn, v�lj en funktion med switch-satser
    while(gameIsRunning)
    {
        char mainMenuInput[5];
        mainMenuSelection = 0;
    
        while(mainMenuSelection == 0)
            {
                // system("cls");
                clearConsole();
                printf("\t*** GISSA ETT TAL ***\n");
                printf("\tHuvudmeny\n\n");
                printf("V�lj ett alternativ med 1, 2 eller 3.\n");
                printf("1. Spela\n2. Lowscorelistan\n3. Avsluta\nVal: ");
                scanf(" %s", &mainMenuInput);
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
                // system("cls");
                clearConsole();
                printf("Tack f�r att du spelade!\n");
                gameIsRunning = false;
                break;

            default:
                break;
        }
    }    
    return 0;
}

// Sj�lva spelet
void gameMechanics()
{
    // Variabler som beh�vs
    int randomNumber;
    char playerInput[MAXELEMENTS];
    int playerGuess = 0;
    int numberOfGuesses = 0;
    int endGame = 2;
    int answerQuestion;
    char endGameAnswer[100];
    int tempIfErrorInput = 0; // Ifall man r�kar gissa n�t som inte �r en siffra eller under 1/�ver 100

    srand(time(0)); // Generera random seed

    while(endGame != 1)
    {
        randomNumber = (rand() % MAXROLL) + MINROLL; // Generera ett slumpm�ssigt nummer
        numberOfGuesses = 0;
        answerQuestion = 1;

        do
        {
            // system("cls");
            clearConsole();
            if(numberOfGuesses != 0)
            {
                if(playerGuess < 1 || playerGuess > 100)
                {
                    for (int i = 0; i < strlen(playerInput); i++)
                    {
                        if (!isdigit(playerInput[i]))
                        {
                            printf("Du har inte skrivit in ett heltal. ");
                            numberOfGuesses--;
                            break;
                        }
                    }
                    
                    printf("Gissa bara p� heltal fr�n 1 till 100.\n");
                    playerGuess = tempIfErrorInput; // �terst�ller gissningen
                }
                printf("Gissning: %d\n", playerGuess);
                
                if(playerGuess < randomNumber)
                {
                    printf("Talet �r h�gre!\n");
                }
                else if (playerGuess > randomNumber)
                {
                    printf("Talet �r l�gre!\n");
                }
            }
            tempIfErrorInput = playerGuess;
            printf("Skriv in din gissning: ");
            scanf(" %10s", &playerInput);
            playerGuess = atoi(playerInput);
            numberOfGuesses++;
        }while (playerGuess != randomNumber);

        clearConsole();
        // system("cls");
        printf("R�tt! Bra gissat.\nDu gissade r�tt p� %d f�rs�k.\n", numberOfGuesses);
        updateScores(numberOfGuesses);
        
        endGame = 1;

        fflush(stdin);        
    }
    return;
}

// Skriv ut low-score-listan
void showScores()
{
    //system("cls");
    fflush(stdin);
    clearConsole();

    printf("Low-Score-Listan! L�gre �r b�ttre!\n");
    
    for(int i = 0; i < 5; i++)
    {
        printf("%d: ", i + 1);
        if(scores[i].score != 0)
        {
            printf("%-25s\t", scores[i].name);
            char printTime[100];
            struct tm *convertedTime;
            // time_t timeInt = scores[i].times;
            // time(&timeInt);
            convertedTime = gmtime(&scores[i].time);
            convertedTime->tm_hour++; // F�r att ha v�r tid och inte GMT
            if(convertedTime->tm_hour >= 24)
            {
                convertedTime->tm_hour = 0;
            }
            strftime(printTime, 100, "%y-%m-%d %H:%M", convertedTime);

            printf("%d\t", scores[i].score);
            printf("%s", &printTime);
        }
        printf("\n");
    }

    /*
    for(int i = 0; i < 5; i++)
    {
        printf("%d: %-30s\t", i+1, lowScoreNames[i]);
        if(lowScoreScores[i] != 0)
        {
            char printTime[100];
            struct tm *convertedTime;
            time_t timeInt = lowScoreTimes[i];
            time(&timeInt);
            convertedTime = localtime(&timeInt);
            strftime(printTime, 100, "%y-%m-%d %H:%M", convertedTime);

            printf("%d\t", lowScoreScores[i]);
            printf("%s", &printTime);
        }
        printf("\n");
    }
    */
    printf("Sl� n�gons po�ng f�r att komma in p� listan. Tryck enter f�r att forts�tta.\n");
    hitEnter();
    fflush(stdin);
    // system("cls");
    clearConsole();
    return;    
}

// J�mf�r antal gissningar med low-score-listan och uppdatera arrayerna.
// Om antalet gissningar �r l�gre �n n�gon p� listan, uppdatera listan och
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
        // Hitta platsen p� listan d�r po�ngen ska in
        if(numberOfGuesses < scores[i].score)
        {
            break;
        }
        if(scores[i].score != 0)
        {
            marker++;
        }        
    }

    if(marker < 5) // Om po�ngen ska in p� listan..
    {
        printf("Du tog dig in p� lowscore-listan! Skriv in ditt namn: ");
        scanf(" %25s", enterName);
        // fgets(name, sizeof(name), stdin);
        // fgets(enterName, sizeof(enterName), stdin);

        for(int i = 4; i > marker; i--)
        {
            // Flytta ner allt under p� listan
            scores[i].score = scores[i-1].score;
            strcpy(scores[i].name, scores[i - 1].name);
            scores[i].time = scores[i - 1].time;

            /*
            lowScoreScores[i] = lowScoreScores[i - 1];
            strcpy(lowScoreNames[i], lowScoreNames[i - 1]);
            lowScoreTimes[i] = lowScoreTimes[i - 1];
            */
        }
        // L�gg till namn och po�ng p� r�tt plats i listan
        scores[marker].score = numberOfGuesses;
        strcpy(scores[marker].name, enterName);
        scores[marker].time = timeNow;

        writeToFile(scores, sizeof(scores));

        /*
        for(int i = 0; i < 5; i++)
        {    
            strcat(updatedList, lowScoreNames[i]);
            strcat(updatedList, "\n");
            sprintf(tempInput, "%d", lowScoreScores[i]);
            strcat(updatedList, tempInput);
            strcat(updatedList, "\n");       
        // snprintf(prefix, sizeof(prefix), "%s: %s: %s", argv[0], cmd_argv[0], cmd_argv[1]); // Försök få till för att få mindre kod
        }
        strcat(updatedList, "BREAK"); // Lägger till för att lösa problem med inläsningen

        for(int i = 0; i < 5; i++)
        {
            sprintf(tempTimes, "%d", lowScoreTimes[i]); 
            strcat(updatedTimes, tempTimes);
            strcat(updatedTimes, "\n");
        }
        strcat(updatedTimes, "BREAK");

        // Skriver in den nya listan i filen
        FILE *pScores = fopen("score.low", "r");
        pScores = fopen("score.low", "w");
        fprintf(pScores, updatedList);
        fclose(pScores);

        FILE *pTimes = fopen("time.low", "r");
        pTimes = fopen("time.low", "w");
        fprintf(pTimes, updatedTimes);
        fclose(pTimes);
        */
    }

    hitEnter();
    fflush(stdin);
}

void writeToFile(char *p, size_t size)
{
    FILE *scoreFile = fopen(fileName, "wb");
    fwrite(p, size, 1, scoreFile);
    fclose(scoreFile);
}

void readFromFile(char *p, size_t size)
{
    FILE *scoreFile = fopen(fileName, "rb");
    if(scoreFile != 0)
    {
        fread(p, size, 1, scoreFile);
        fclose(scoreFile);
    }
}

// Funktion skapad bara f�r att kunna pausa innan man rensar sk�rmen och l�ter anv�ndaren trycka p� enter
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

void clearConsole(void)
{
    printf("\x1b[H\x1b[2J\x1b[3J");
}