#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

//this function changes the functionality of the terminal
char readChar() {
    char ch;
    struct termios old, newt;   //used for terminal I/O control & configuration

    tcgetattr(STDIN_FILENO, &old);  //gets current terminal settings for input and stores into 'old' structure
    newt = old; //copy of old terminal settings stored here
    newt.c_lflag &= ~(ICANON);   //modification to terminal
                                        //ICANON - keyboard input immediately read
                                        //without having to press enter key
                                        
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);    //sets changes inmmediately

    ch = getchar(); //takes in user input, the character entered will not be echoed
                    //and is read immediately 

   
    tcsetattr(STDIN_FILENO, TCSANOW, &old);  //ensures terminal goes back to original behavior after user input

    return ch;
}


int main() {
    char input = ' ';   //user input
    char content[999];  //holds keyed info
    int dataIndex = 0;  //
    char flag[8] = "01111110";
    int flagCount = 0;
    int flagIndex = 0;  //used to iterate through flag
    int printCount = 0; 
    int skipFlag = 0;   //used for edge-case 00 inputs
    int dataCount = 1;  //used when printing to output file

    //output file creation
    FILE *outputFile = fopen("results.txt", "w");
    if (outputFile == NULL) {
        perror("Error opening results.txt");
        return 1;
    }

    printf("Begin information input: ");

    //loop that does main functionality until '!' is entered
    while(input != 27){ //as long as the user does not enter the 'esc' key
        input = readChar();

        //checks if user inputted flag sequence
        if(input == flag[flagIndex]){
            flagIndex++;
            if(flagIndex ==8){
                flagIndex = 0;
                flagCount++;
            }
        }else if(flagIndex == 1 && input == '0'){   //deals with 00 user input 
            flagIndex = 1;
        } else if(flagIndex == 6 && input == '0'){  //deals with 01 user input
            flagIndex = 1;
        } else{
            flagIndex = 0;
        }


        //prevents the last 0 from the first flag to be part of the keyed information
        if(flagCount == 1 && printCount == 0){
            printf("\n1st start Sequence '01111110' detected!\n");
            printf("\nInput information to be stored: ");
            printCount++;
            skipFlag = 1;
        }

        //store information after first flag sequence found
        if(flagCount == 1 && printCount == 1 && skipFlag == 0){
            content[dataIndex] = input;
            dataIndex++;
        }

        skipFlag = 0;

        //print out information keyed between the two flags
        //store keyed info into output file
        //restart the loop 
        //clear content array 
        if(flagCount == 2){
            printf("\n2nd time Sequence '01111110' detected! End of sequence.\n");
            
            printf("\nInformation keyed in between the two flags: ");
            for(int i = 0; i < dataIndex - 7; i++){
                printf("%c", content[i]);
            }

            fprintf(outputFile, "Data for flag set #%d: ", dataCount);
            
            for (int i = 0; i < dataIndex - 7; i++) {
                // Write the characters to the file
                fputc(content[i], outputFile);
            }
            // Write a newline character to separate data sets in the file
            fputc('\n', outputFile);
            printf("\n\nBegin information input: ");

        flagCount = 0;
        printCount = 0;
        dataIndex = 0;
        dataCount++;

        memset(content, 0, sizeof(content));
        fflush(outputFile);

        }
    }

    fclose(outputFile);
    printf("\nE");
    printf("\nEscape key was pressed. Exiting the program.\n");
    
    return 0;
}