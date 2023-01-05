#include <stdio.h>  // For user input and output
#include <string.h> // To compare strings

void displayScenario(int scenario);
void printFile(char fileName[]);
int getScenario(int scenario);
int getDecision();

int main()
{
    // We tell the story until its finished or the user doesn't want to play anymore
    int scenario = 0;

    // While they dont want to finish playing (decision = 0), the games keeps on
    while (scenario >= 0)
    {
        // Prints the story from the file for the user
        displayScenario(scenario);

        // Gets the user decision and switches scenarios based on that. Also may end the game or restart.
        scenario = getScenario(scenario);
    }

    // Tells the user they stopped playing and app closes
    printf("\nYou left the game. Thanks for playing!");

    return 0;
}

/**
 * @brief Gets the right filename based on the current scenario and displays the text
 * 
 * @param scenario situation in which the player is currently in
 */
void displayScenario(int scenario)
{
    // We get the correct text file
    FILE *f;

    char n[] = {scenario + '0', '\0'};
    char fileName[14] = "./text/";
    char extension[] = ".txt\0";

    // We try to open in read only
    strcat(fileName, n);
    strcat(fileName, extension);

    printFile(fileName);
}

/**
 * @brief Displays the text of the file passed as argument
 * 
 * @param fileName name of the file to be printed
 */
void printFile(char fileName[])
{
    FILE* f = fopen(fileName, "r");

    if (f)
    {
        char c;

        // We display the text
        printf("\n");
        do
        {
            c = fgetc(f);
            printf("%c", c);
        } while (c != EOF);

        fclose(f);
    }
    else // If it couldn't be opened we display a message to the user
    {
        printf("\n\n !!!!! ERROR !!!!! ");
        printf("\nOUPS, it looks like the story files are not where they should...\n Make sure you have a \"text\" folder in the app directory.\n If you deleted anything, pls redownload text folder.\n\nType -1 to leave or 0 to restart:");
    }
}

/**
 * @brief Gets the next scenario to be displayed
 * 
 * @param scenario actual scenario
 * @return int next scenario
 */
int getScenario(int scenario)
{
    // Gets the player input
    int decision = getDecision();

    // Depending on the actual scenario and the decision both condition the next scenario
    switch (scenario)
    {
    // Scenarios are not lineal advancing
    case 0:
        decision ? (scenario = 1) : (scenario = 2);
        break;
    case 1:
        decision ? (scenario = 5) : (scenario = 3);
        break;
    case 2:
        decision ? (scenario = 1) : (scenario = 4);
        break;
    case 3:
        decision ? (scenario = 0) : (scenario = -1);
        break;
    case 4:
        decision ? (scenario = 0) : (scenario = -1);
        break;
    case 5:
        decision ? (scenario = 6) : (scenario = 7);
        break;
    case 6:
        decision ? (scenario = 0) : (scenario = -1);
        break;
    case 7:
        decision ? (scenario = 0) : (scenario = -1);
        break;
    }

    return scenario;
}

/**
 * @brief Retrieves the decision made by the player
 * 
 * @return int
 */
int getDecision(){
    int decision;

    do 
    {
        scanf("%d", &decision);

        // If they choose -1, they leave the game
        if (decision == -1)
        {
            printf("\nYou pressed -1, leaving the game...\n");
            return -1;
        }

        // If they pick a different decision than expect it is told.
        if (decision != 0 && decision != 1)
        {
            printf("\nOUPS, you didn't enter '0' or '1'. Try again or exit with '-1' or CTRL + C.\n");
        }
    } while (decision != 0 && decision != 1);

    return decision;
}