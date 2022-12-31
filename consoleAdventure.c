#include <stdio.h>  // For user input and output
#include <stdlib.h> // For malloc use
#include <dirent.h> // For directory management
#include <string.h> // To compare strings

#define FILES 8   // There's 7 text files
#define SIZE 1000 // 6 letter per 300 words

void fetchStory(DIR *d, char story[][SIZE]); // In C, char** is the pointer of array, there's no & reference passing
void getScenario(char story[][SIZE], int *decision);

int main()
{

    // Try to open the directory and warn the user if something goes wrong
    DIR *d;
    d = opendir("./text");

    if (d)
    {
        // We fetch the story text and close the dir. We need to initializate the dynamic mem
        char story[FILES][SIZE];

        fetchStory(d, story);
        closedir(d);

        // We tell the story until its finished or the user doesn't want to play anymore
        int *decision;
        int dec = 0;
        decision = &dec;

        while (!(*decision))
        {
            // Tells the scenario and makes the player choose a decision, the story advances given the decision the user made.
            getScenario(story, decision);
        }

        // free the memory allocation and leave the game
        printf("You left the game. Thanks for playing!");
    }
    else
    {
        printf("It looks like the files needed don't exist, make sure there's a folder called 'text' inside this folder");
    }

    return 0;
}

/**
 * Fetchs the entire story text as an array of texts
 */
void fetchStory(DIR *d, char story[][SIZE])
{
    // Using an struct dirent and the dir name
    struct dirent *dir;
    char di[] = "./text/";

    // Gets the text of each file of the dir
    int cont = 0;
    while ((dir = readdir(d)) != NULL && cont < FILES)
    {
        // Uses the file if its not the parent or actual directory
        if (strcmp(dir->d_name, ".") && strcmp(dir->d_name, ".."))
        {
            // Opens the file and saves the content
            FILE *f = fopen(strcat(di, dir->d_name), "r");
            
            for (size_t i = 0; i < SIZE; i++)
            {
                // intentar cambiar para que scanee hasta que pueda
                fscanf(f, "%s", story[cont]);
                printf("%s", story[cont][i]);
            }
            
            

            // Close the files and go next
            fclose(f);
            cont++;
        }
    }
}

/**
 * Shows a the texts based on the decision made and makes the user choose a decision that will lead to the next sceneario
 */
void getScenario(char story[][SIZE], int *scenario)
{
    // Shows the story text and requires a decision
    int decision;
    for (int i = 0; i < SIZE; i++)
    {
        printf("\n%s", story[*scenario][i]);
    }
    scanf("%d", &decision); // if its 1 goes next (can be final), else goes no next situation

    // Depending on the value, it can go to next scene or other
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