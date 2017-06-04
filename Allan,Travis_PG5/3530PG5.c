
/*
 Travis Allan
 12/3/15
 CSCE 3530
 Program 5
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 1000
#define SAMPLE_SIZE 6

struct TwoDarray {

    int Matrix[27][27];
    char active[SAMPLE_SIZE];

};
struct Vertex {
    int distTo;
    char prev;
};

//Dijkstra's Algorithm
int dijkstra(int Matrix[27][27], int source, char nodeList[SAMPLE_SIZE], char sourceChar) {
    int i, count, shortestV, alt;
    char nameV[SAMPLE_SIZE];
    char retVal, arg;
    struct Vertex vertices[SAMPLE_SIZE * SAMPLE_SIZE];
    for (i=0; i<=(SAMPLE_SIZE * SAMPLE_SIZE); i++) {
        vertices[i].distTo = 99;
        vertices[i].prev = 15;
    }
    
    //printing
    FILE * fp;
    
    fp = fopen ("LS.txt", "a+");
    
    shortestV = 99;
    while (count < SAMPLE_SIZE) {
        for (i=0; i<=25; i++) {
            arg = Matrix[source][i];
            if ((Matrix[source][i] < shortestV) && (strchr(nameV, arg) == NULL)) {
                shortestV = Matrix[source][i];
                switch (i) {
                    case 0 :
                        retVal = 'a';
                    case 1 :
                        retVal = 'b';
                    case 2 :
                        retVal = 'c';
                    case 3 :
                        retVal = 'd';
                    case 4 :
                        retVal = 'e';
                    case 5 :
                        retVal = 'f';
                    case 6 :
                        retVal = 'g';
                    case 7 :
                        retVal = 'h';
                    case 8 :
                        retVal = 'i';
                    case 9 :
                        retVal = 'j';
                    case 10 :
                        retVal = 'k';
                    case 11 :
                        retVal = 'l';
                    case 12 :
                        retVal = 'm';
                    case 13 :
                        retVal = 'n';
                    case 14 :
                        retVal = 'o';
                    case 15 :
                        retVal = 'p';
                    case 16 :
                        retVal = 'q';
                    case 17 :
                        retVal = 'r';
                    case 18 :
                        retVal = 's';
                    case 19 :
                        retVal = 't';
                    case 20 :
                        retVal = 'u';
                    case 21 :
                        retVal = 'v';
                    case 22 :
                        retVal = 'w';
                    case 23 :
                        retVal = 'x';
                    case 24 :
                        retVal = 'y';
                    case 25 :
                        retVal = 'z';
                }
                
            }
            fprintf(fp, "%c (%c,%c)\n", nodeList[i], sourceChar, retVal);
            printf("%c (%c,%c)\n", nodeList[i], sourceChar, retVal);
        }
        nameV[count] = i;
        count++;
        shortestV = 99;
        

    }
    fclose(fp);

    return 0;
}
//switcher(int)
int switcher(char sub) {
    int retVal;
    switch (sub) {
        case 'a' :
            retVal = 0;
            return retVal;
        case 'b' :
            retVal = 1;
            return retVal;
        case 'c' :
            retVal = 2;
            return retVal;
        case 'd' :
            retVal = 3;
            return retVal;
        case 'e' :
            retVal = 4;
            return retVal;
        case 'f' :
            retVal = 5;
            return retVal;
        case 'g' :
            retVal = 6;
            return retVal;
        case 'h' :
            retVal = 7;
            return retVal;
        case 'i' :
            retVal = 8;
            return retVal;
        case 'j' :
            retVal = 9;
            return retVal;
        case 'k' :
            retVal = 10;
            return retVal;
        case 'l' :
            retVal = 11;
            return retVal;
        case 'm' :
            retVal = 12;
            return retVal;
        case 'n' :
            retVal = 13;
            return retVal;
        case 'o' :
            retVal = 14;
            return retVal;
        case 'p' :
            retVal = 15;
            return retVal;
        case 'q' :
            retVal = 16;
            return retVal;
        case 'r' :
            retVal = 17;
            return retVal;
        case 's' :
            retVal = 18;
            return retVal;
        case 't' :
            retVal = 19;
            return retVal;
        case 'u' :
            retVal = 20;
            return retVal;
        case 'v' :
            retVal = 21;
            return retVal;
        case 'w' :
            retVal = 22;
            return retVal;
        case 'x' :
            retVal = 23;
            return retVal;
        case 'y' :
            retVal = 24;
            return retVal;
        case 'z' :
            retVal = 25;
            return retVal;
    }
    return 99;
}

//switcher(char)
char decToChar(int sub) {
    char retVal;
    switch (sub) {
        case 0 :
            retVal = 'a';
            return retVal;
        case 1 :
            retVal = 'b';
            return retVal;
        case 2 :
            retVal = 'c';
            return retVal;
        case 3 :
            retVal = 'd';
            return retVal;
        case 4 :
            retVal = 'e';
            return retVal;
        case 5 :
            retVal = 'f';
            return retVal;
        case 6 :
            retVal = 'g';
            return retVal;
        case 7 :
            retVal = 'h';
            return retVal;
        case 8 :
            retVal = 'i';
            return retVal;
        case 9 :
            retVal = 'j';
            return retVal;
        case 10 :
            retVal = 'k';
            return retVal;
        case 11 :
            retVal = 'l';
            return retVal;
        case 12 :
            retVal = 'm';
            return retVal;
        case 13 :
            retVal = 'n';
            return retVal;
        case 14 :
            retVal = 'o';
            return retVal;
        case 15 :
            retVal = 'p';
            return retVal;
        case 16 :
            retVal = 'q';
            return retVal;
        case 17 :
            retVal = 'r';
            return retVal;
        case 18 :
            retVal = 's';
            return retVal;
        case 19 :
            retVal = 't';
            return retVal;
        case 20 :
            retVal = 'u';
            return retVal;
        case 21 :
            retVal = 'v';
            return retVal;
        case 22 :
            retVal = 'w';
            return retVal;
        case 23 :
            retVal = 'x';
            return retVal;
        case 24 :
            retVal = 'y';
            return retVal;
        case 25 :
            retVal = 'z';
            return retVal;
            
    }
    return 99;
}

int main() {

    //declarations
    int inputnum, i, j, k, x, y, def, activeCount;
    char sourceChar;
    FILE *file1;
    FILE *file2;
    int* cost;
    char* source;
    char* dest;
    
    def= 99;
    //initiallizing the matrix
    struct TwoDarray Graph;
    
    for (i = 0; i <= 26; i++) {
        for (j = 0; j <= 26; j++) {
            Graph.Matrix[i][j] = def;
        }
    }
    /*test for graph
    for (i = 0; i <= 25; i++) {
        //printf("%d ", i); //line numbers
        
        for (j = 0; j <= 25; j++) {
            printf("%d ", Graph.Matrix[i][j]);
        }
        printf("\n");
    }*/

    //parsing the input
    file1 = fopen("router.txt", "r");
    inputnum = 0;
    source = (char *) malloc(INPUT_SIZE);
    dest = (char *) malloc(INPUT_SIZE);
    cost = (int *) malloc(INPUT_SIZE);
    activeCount = 0;
    
    while(1) {
        fscanf(file1, "%c %c %d\n", &source[inputnum], &dest[inputnum], &cost[inputnum]);
        inputnum++;
        if ((strchr(Graph.active, source[inputnum]) != NULL) && (activeCount < SAMPLE_SIZE)) {
            Graph.active[activeCount] = source[inputnum];
            activeCount++;
        }
        else if ((strchr(Graph.active, dest[inputnum]) != NULL) && (activeCount < SAMPLE_SIZE)) {
            Graph.active[activeCount] = dest[inputnum];
            activeCount++;
        }
        if( feof(file1) ) {
            break;
        }
    }
    fclose(file1);
    
    
    //build the graph
    for (i=0; i < inputnum; i++) {
        
        //test input
        //printf("source: %c\n", source[i]);
        //printf("destination: %c\n", dest[i]);
        //printf("cost %d\n", cost[i]);
        
        //call to switcher
        x = switcher(source[i]);
        y = switcher(dest[i]);
        
        Graph.Matrix[x][y] = cost[i];
        Graph.Matrix[y][x] = cost[i];

    }
    
    free(source);
    free(dest);
    free(cost);
    
    /*test for graph
    for (i = 0; i <= 25; i++) {
        //printf("%d ", i); //line numbers
        
        for (j = 0; j <= 25; j++) {
            printf("%d ", Graph.Matrix[i][j]);
        }
        printf("\n");
    }*/
    
    
    //Dijkstra's function
    printf("Dijkstra's Algorithm\n");
    for (i=0; i < SAMPLE_SIZE; i++) {
        sourceChar = decToChar(Graph.active[i]);
        dijkstra(Graph.Matrix, Graph.active[i], Graph.active, sourceChar);
    }
    printf("--------\n");
    return 0;
}
