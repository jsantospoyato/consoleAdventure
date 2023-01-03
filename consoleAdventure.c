#include <stdio.h>  // For user input and output
#include <stdlib.h> // For malloc use
#include <dirent.h> // For directory management
#include <string.h> // To compare strings

#define folder "./text" // The folder where the story is placed

void displayScenario(int *scenario);
void getDecision(int *scenario);

int main()
{
    // We tell the story until its finished or the user doesn't want to play anymore
    int *scenario;
    int decision = 0;
    scenario = &decision;

    // While they dont want to finish playing (decision = 0), the games keeps on
    while (!(*scenario))
    {
        printf("%d", *scenario);
        printf("%c", *scenario);
        // Prints the story from the file for the user
        displayScenario(scenario);

        // Gets the user decision and switches scenarios based on that. Also may end the game or restart.
        getDecision(scenario);
    }

    // Tells the user they stopped playing and app closes
    printf("You left the game. Thanks for playing!");

    return 0;
}

void displayScenario(int *scenario)
{
    // We try to open the file for reading only
    FILE *f;
    const char* n = 0;
    f = fopen(strcat(strcat(folder, n), ".txt"), "r");
    
    if (f){
        char c;

        // We display the text
        do {
            c = fgetc(f);
            printf("%c", c);
        } while (c != EOF);
    }
    else // If it couldn't be opened we display a message to the user
    {
        printf("OUPS, it looks like the story files are not where they should...\n Make sure you have a \"text\" folder in the app directory.\n If you deleted anything, pls redownload text folder.");
    }
}

/**
 * Shows a the texts based on the decision made and makes the user choose a decision that will lead to the next sceneario
 */
void getDecision(int *scenario)
{
    // Retrives the decision made by the player, if its an ending, it just continues to restart or not
    int decision;
    scanf("%d", &decision);

    // Depending on the actual scenario and the decision both condition the next scenario
    switch (*scenario)
    {
        // For cases, only the exceptions, else the story advances with the decision naturally on default
    case 1:
        decision ? (decision = 5) : (decision = 3);
        break;
    case 2:
        decision ? (decision = 4) : (decision = 1);
        break;
    default:
        decision += 1; // Decision are 0 or 1 so to change with 0 needs a +1
        break;
    }

    *scenario = decision;
}
