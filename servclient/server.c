//Group 1
//Names: Shaddy Zayour, Alex Adamcik, Travis Allan, Dustin Roberts
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int randomTicketNum()  // randomly generates the tickets from 10000 to 99999
{
    return rand()%90000 + 10000 ;
}

struct Ticket
{
    int ticketNum ;
    int status; //  -1: not bought; 0: bought; 1: cancelled
};
struct Ticket tickets[10];

void doprocessing (int sock)
{
    srand(time(NULL));
    int n;
    char buffer[256];

    bzero(buffer,256);

    n = read(sock,buffer,255);
    if (n < 0)
    {
        perror("ERROR reading from socket");
        exit(1);
    }
    //printf("testing\n\n");
    /*Logic for tickets*/
    int i,z,t;
     for(i=0;i<10;i++){
        t = rand()%9 + 0 ; //Determines Ticket number
        z=0;
            if(i>1){ 
                int z = rand()%9 + 0 ; //Buy or Cancel
            } 
            
            if(z>-1 && z<9 && tickets[t].status==-1) //Ticket available
                tickets[t].status=0; //Ticket was bought
            else if(z>-1 && z<9 && tickets[t].status==0) //Not able to buy
                printf("Ticket unavailable: %i\n",tickets[t].ticketNum);
            else if(z==9 && tickets[t].status==0) //Ticket is cancelable
                tickets[t].status = 1;
            else if(z==9 && tickets[t].status==-1) //Not Cancelable
                printf("Cannot cancel unpurchased ticket: %i\n",tickets[t].ticketNum);       

     }
    /*Logic complete*/
    int b, a;
    for (b=0;b<10;b++)
    {
        a = b + 1;
        printf("Ticket %i: %i , Status:%i\n", a,tickets[b].ticketNum,tickets[b].status);
    } 
    printf("Client Complete: %s\n",buffer);
    if (n < 0) 
    {
        perror("ERROR writing to socket");
        exit(1);
    }
}

int main( int argc, char *argv[] )
{
    
    /*Random Ticket Generator*/
    srand(time(NULL));
    int b, i;
    
    
    for (b=0;b<10;b++)
    {
        tickets[b].ticketNum=randomTicketNum();
        tickets[b].status=-1;
    }

    printf("Showing Database:\n");
    //for (b=0;b<9;b++)
    b = 0;
    while (b < 10)
    {
        i = b + 1;
        printf("Ticket %i: %i , Status:%i\n", i,tickets[b].ticketNum,tickets[b].status);
        b++;
    }
    printf("\n\n");
    /*Finished creating database*/

    int sockfd, newsockfd, portno, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int  n;

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
    {
        perror("ERROR opening socket");
        exit(1);
    }
    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
 
    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
                          sizeof(serv_addr)) < 0)
    {
         perror("ERROR on binding");
         exit(1);
    }
    /* Listen for clients*/
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    while (1) 
    {
        newsockfd = accept(sockfd, 
                (struct sockaddr *) &cli_addr,(socklen_t *) &clilen);
        if (newsockfd < 0)
        {
            perror("ERROR on accept");
            exit(1);
        }
        /* Create child process */
        pid_t pid;
        pid = fork();
        if (pid < 0)
        {
            perror("ERROR on fork");
        exit(1);
        }
        if (pid == 0)  
        {
            /* This is the client process */
            close(sockfd);
            doprocessing(newsockfd);
            exit(0);
        }
        else
        {
            close(newsockfd);
        }
    } 
}