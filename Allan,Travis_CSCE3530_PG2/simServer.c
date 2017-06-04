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

//the function below is property of linux questions.org

//location: http://wiki.linuxquestions.org/wiki/Connecting_a_socket_in_C
int webCall(char* host, int i) {
    return 0;
}

int socket_connect(char *host, in_port_t port){
        struct hostent *hp;
        struct sockaddr_in addr;
        int on = 1, sock;

        if((hp = gethostbyname(host)) == NULL){
            herror("gethostbyname");
            exit(1);
        }
        bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
        addr.sin_port = htons(port);
        addr.sin_family = AF_INET;
        sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        //setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (const char *)&on, sizeof(int));
        if(sock == -1){
            perror("setsockopt");
            exit(1);
        }
        if(connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1){
            perror("connect");
            exit(1);
        }
        return sock;
} //end of function

int main(){
    int welcomeSocket, newSocket, ipSocket, i, array[5][20];
    char request[50];
    char buffer[1024];
    char cmpr[100];
    time_t currentTime;
    char black[50] = "Denied: the website you requested is blacklisted";
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
    /* Set IP address to localhost */
    //serverAddr.sin_addr.s_addr = inet_addr("71.10.216.1"); //cse
    serverAddr.sin_addr.s_addr = inet_addr("192.168.0.111"); //home
    /* Set all bits of the padding field to 0 */
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    
    /*---- Bind the address struct to the socket ----*/
    bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    
    /*---- Listen on the socket, with 5 max connection requests queued ----*/
    if(listen(welcomeSocket,5)==0)
        printf("Listening\n");
    else
        printf("Error\n");
    
    /*---- Accept call creates a new socket for the incoming connection ----*/
    addr_size = sizeof serverStorage;
    newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
    
    
    /*---- Send message to the socket of the incoming connection ----*/
    //strcpy(buffer,"Connection Established\n");
    //send(newSocket,buffer,13,0);
    
    //recieve request
    recv(welcomeSocket, request, 50, 0);
    //printf("%s", request);
    fp = fopen( "blacklist.txt", "r");
    fscanf(fp, "%s", cmpr);
    if (strcmp(cmpr, request) == 0) {
        printf("error blacklist request\n");
        send(newSocket,black,50,0);
        int fclose( FILE *fp);
    }
    else {
        int fclose( FILE *fp);
        
        //connect to the requested website
        strcpy (buffer, socket_connect(request, 80));
        printf("%s", buffer);
    
        //return the requested webpage
        send(newSocket,buffer,1024,0);
    
        time (&currentTime);
        //open a file to save the last 5 requests
        fp = fopen( ctime (&currentTime), "w");
    
        //do stuff
        fprintf(fp, "%s",buffer);
        //close the file
        int fclose( FILE *fp);
    }
    return 0;
}


