/****************** SERVER CODE ****************/
/*
 The base code used in this program is property of programminglogic.com
 source: Example of Client-Server Program in C (Using Sockets and TCP)
 I, Travis Allan, do not claim the base code as my own, only the modifications made to it.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>


int main(){
    int welcomeSocket, newSocket, ipSocket, i, array[5][20];
    char request[50];
    char buffer[1024];
    char cmpr[100];
    time_t currentTime;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    FILE *fp;
    
    /*---- Create the socket. The three arguments are: ----*/
    /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
    welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
    
    /*---- Configure settings of the server address struct ----*/
    /* Address family = Internet */
    serverAddr.sin_family = AF_INET;
    /* Set port number, using htons function to use proper byte order */
    serverAddr.sin_port = htons(1110);
    /* Set IP address to localhost or cse*/
    //serverAddr.sin_addr.s_addr = inet_addr("71.10.216.1"); //cse
    serverAddr.sin_addr.s_addr = inet_addr("192.168.0.111"); //home
    /* Set all bits of the padding field to 0 */
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    
    /*---- Bind the address struct to the socket ----*/
    bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    
    /*---- Listen on the socket ----*/
    
    while (1 > 0) {
        if(listen(welcomeSocket,2)==0)
            //printf("Listening\n");
            bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
        else if (listen(welcomeSocket,2)==1) {
            printf("SYNRCVD\n");
        }
        else if (listen(welcomeSocket,2)==2) {
            printf("ESTABLISHED CONNECTION\n");
            break;
        }
        else
            printf("Error\n");
    }
    
    /*---- Accept call creates a new socket for the incoming connection ----*/
    addr_size = sizeof serverStorage;
    newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
    
    
    /*---- Send message to the socket of the incoming connection ----*/
    //strcpy(buffer,"Connection Established\n");
    //send(newSocket,buffer,13,0);
    

    return 0;
}


