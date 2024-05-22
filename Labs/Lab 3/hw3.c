#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define size 100

char graph[size][size]; // graph data
char nodes[size][size];
int distance = 0;
int path[size]; // shortest path array
char temp[2];
int shortPath = 0; // shortest path value
char nextNode, findNode, input[1], output[1];


// Reading file for the graph
int fileReader(){
    int i = 0;
    char lines[size];
    char file[size];

    printf("Enter file.txt name: ");
    scanf("%s", &file);

    FILE* pointer = fopen(file, "r");

    if(pointer != NULL){
        while(fgets(lines, sizeof(lines), pointer)){
            strcpy(graph[i], lines);
            i++;
        }
        fclose(pointer);
        return i;
    } else{
        printf("File not found... try again.\n");
        fileReader();
    }
}


// Getting the graph data and storing it into nodes
int getNodes(int x){
    int y = 1;
    nextNode = graph[0][0];
    nodes[0][0] = nextNode;
    nodes[0][1] = ' ';
    nodes[0][2] = 'x';

    for(int i = 0; i < x; i++){
        if(graph[i][0] != nextNode){
            nextNode = graph[i][0];
            nodes[y][0] = nextNode;
            nodes[y][1] = ' ';
            nodes[y][2] = 'x';
            y++;
        }
    }
    return y;
}


// Converts lowercase to uppercase for user's input
int upperCaseConvert(char character[]){
    int i = 0;
    while (character[i] != '\0') {
        if (character[i] >= 'a' && character[i] <= 'z') {
            character[i] = character[i] - 32;
        }
        i++;    
    }
}


int main(){
    int shortPath = 0;
    int x = 0;
    int pathSize = 2;
    int f = fileReader();
    const int node = getNodes(f);
    int length[node][node]; // Array for the shortest path
    int pointer[node][node]; // Array for the intermediate nodes 

    // Get starting and ending point from user
    printf("\nEnter starting point: ");
    scanf("%s", input);
    upperCaseConvert(input);
    nextNode = input[0];

    printf("\nEnter ending point: ");
    scanf("%s", output);
    upperCaseConvert(output);

    // Converting the nodes into ASCII value (Ex: A - 65 = index 0)
    findNode = output[0];
    path[0] = ((int)nextNode) - 65;
    path[1] = ((int)findNode) - 65;
    printf("\n");

    // Initialize the path array
    for(int i = 0; i < node; i++){
        for(int j = 0; j < node; j++){
            pointer[i][j] = -1;
            length[i][j] = size;
        }
    }

    // Initial conditions of edge length of Dijkstra's algorithm
    for(int i = 0; i < f; i++){
        length[((int)graph[i][0]) - 65][((int)graph[i][1]) - 65] = ((int)graph[i][3]) - 48;
    }

    // Finding the shortest path and comparing
    for(int i = 0; i < node; i++){
        for(int j = 0; j < node; j++){
            for(int k = 0; k < node; k++){
                if((length[j][i] + length[i][k]) < length[j][k]){
                    length[j][k] = (length[j][i] + length[i][k]);
                    pointer[j][k] = i;
                }
            }
        }
    }

    // Recreates the shortest path given the pointer array
    while(1){
        if(pointer[path[x+0]][path[x+1]] > -1){
            for(int i = pathSize - 1; i >= x + 1; i--){
                path[i + 1] = path[i];
            }
            path[x + 1] = pointer[path[x+0]][path[x+1]];
            pathSize++;
        }else {
            shortPath += length[path[x+0]][path[x+1]];
            if(pathSize == 2){
                break;
            }
            x++;
        }

        if(path[x+1] == 0){
            break;
        }
    }

    printf("Shortest path: ");
    for (int i = 0; i < pathSize; i++) { 
        printf("%c ", (char)(path[i] + 65));
    }

    printf(" \n\nShortest path length: %d units\n\n", shortPath);

}