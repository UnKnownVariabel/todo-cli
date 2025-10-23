#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMUM_LINE_LENGTH 200
#define MAX_INT_LEN 10
#define LIST_FILE "/home/otten/Documents/programming/bin/todo_list.txt"

int add_item(char *item)
{
    FILE *filePointer;
    char line[MAXIMUM_LINE_LENGTH]; 
    int lineCount = 0; 

    filePointer = fopen(LIST_FILE, "r");
    while (fgets(line, MAXIMUM_LINE_LENGTH, filePointer) != NULL) 
    {
        lineCount++;
    }
    filePointer = fopen(LIST_FILE, "a");
    fprintf(filePointer, "%d. %s\n", lineCount + 1, item);
}

int open_file()
{
    FILE *filePointer;
    char line[MAXIMUM_LINE_LENGTH]; 

    filePointer = fopen(LIST_FILE, "r");
    while (fgets(line, MAXIMUM_LINE_LENGTH, filePointer) != NULL) 
    {
        printf("%s", line);
    }
    printf("\n");
}

int set_index(char *line, int number)
{
    int i;
    char temp[MAXIMUM_LINE_LENGTH];
    for(i = 0; line[i] >= '0' && line[i] <= '9'; i++)
        ;
    sprintf(temp, "%d", number);
    strcat(temp, line + i);
    strcpy(line, temp);
}

int remove_item(int line_to_remove)
{
    FILE *inputFile, *outputFile;
    char line[MAXIMUM_LINE_LENGTH]; // Adjust the buffer size as needed
    char number_str[MAX_INT_LEN];
    int number;
    // Open the input file for reading
    inputFile = fopen(LIST_FILE, "r");
    if (inputFile == NULL) {
        printf("Failed to open the input file in remove item\n");
        return 1; // Exit the program indicating failure
    }

    // Open a temporary output file for writing
    outputFile = fopen("temp.txt", "w");
    if (outputFile == NULL) {
        printf("Failed to open the output file in remove item\n");
        fclose(inputFile);
        return 1; // Exit the program indicating failure
    }

    // Read each line from the input file
    int currentLine = 1;
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        // Skip the line to be removed
        if (currentLine != line_to_remove) {
            if(currentLine > line_to_remove)
            {
                set_index(line, currentLine - 1);
                /*int i;
                for(i = 0; line[i] >= '0' && line[i] <= '9'; i++)
                    ;
                sprintf(temp, "%d", currentLine - 1);
                strcat(temp, line + i);
                strcpy(line, temp);*/
            }
            fputs(line, outputFile); // Write the line to the output file
        }
        currentLine++;
    }

    // Close the files
    fclose(inputFile);
    fclose(outputFile);

    // Rename the temporary file to the original file
    rename("temp.txt", LIST_FILE);
}

int clear_file()
{
    FILE *todoFile;
    char answer[5];
    printf("are you shure that you whant to do clear the entire file [Y/n]:");
    scanf("%5s", answer);
    if(answer[0] == 'y' || answer[0] == 'Y')
    {
        todoFile = fopen(LIST_FILE, "w");
        fclose(todoFile);
        printf("\ncleared the list\n");
        return 0;
    }
    printf("\ndid not clear the list char:%s\n", answer);
}
int insert_item(int lineToAdd, char *item)
{
    FILE *inputFile, *outputFile;
    char line[MAXIMUM_LINE_LENGTH]; // Adjust the buffer size as needed
    char number_str[MAX_INT_LEN];
    int number;
    // Open the input file for reading
    inputFile = fopen(LIST_FILE, "r");
    if (inputFile == NULL) {
        printf("Failed to open the input file in remove item\n");
        return 1; // Exit the program indicating failure
    }

    // Open a temporary output file for writing
    outputFile = fopen("temp.txt", "w");
    if (outputFile == NULL) {
        printf("Failed to open the output file in remove item\n");
        fclose(inputFile);
        return 1; // Exit the program indicating failure
    }

    // Read each line from the input file
    int currentLine = 1;
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        // Skip the line to be removed
        if (currentLine < lineToAdd)
        {
            fputs(line, outputFile); // Write the line to the output file
        }
        else if (currentLine == lineToAdd) {

            fprintf(outputFile, "%d. %s\n", lineToAdd, item);
        }
        if (currentLine >= lineToAdd)
        {
            set_index(line, currentLine + 1);
            fputs(line, outputFile);
        }
        currentLine++;
    }

    // Close the files
    fclose(inputFile);
    fclose(outputFile);

    // Rename the temporary file to the original file
    rename("temp.txt", LIST_FILE);
}

int help () 
{
    printf("-a      adds new item \"todo -a <item>\"\n");
    printf("-i      inserts item \"todo -i <index> <item>\n");
    printf("-r      removes item \"todo -r <index>\"\n");
    printf("-c      clears all items \"todo -c\"\n");
}

int main(int argc, char *argv[])
{
    if (argc == 4)
    {
        if (argv[1][0] == '-')
        {
            switch(argv[1][1])
            {
                case 'i':
                    insert_item(atoi(argv[2]), argv[3]);
                    break;
                default:
                    printf("wrong argument\n");
                    break;
            }
        }
        else
        {
            printf("wrong format for argument\n");
        }
    }
    else if (argc == 3)
    {
        if (argv[1][0] == '-')
        {
            switch(argv[1][1])
            {
                case 'h':
                    printf("There is no help to be had here.\n");
                    break;
                case 'a':
                    add_item(argv[2]);
                    break;
                case 'r':
                    remove_item(atoi(argv[2]));
                    break;
                default:
                    printf("wrong argument\n");
                    break;
            }
        }
        else
        {
            printf("wrong format for argument\n");
        }
    }
    else if (argc == 2)
    {
        if (argv[1][0] == '-')
        {
            switch(argv[1][1])
            {
                case 'c':
                    clear_file();
                    break;
                case 'h':
                    help();
                    break;
                default:
                    printf("wrong argument\n");
                    break;
            }
        }
        else
        {
            printf("wrong format for argument\n");
        }
    }
    else if (argc == 1) 
    {
        open_file();
    } 
    else 
    {
        printf("Wrong amount of arguments\n");
    }

    return 0;
}

