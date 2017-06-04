/****************** CLIENT CODE ****************/
/*
   The base code used in this program is property of programminglogic.com
source: Example of Client-Server Program in C (Using Sockets and TCP)
I, Travis Allan, do not claim the base code as my own, only the modifications made to it.
 */

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int main(){
    
    short int source;
    short int destination;
    int sequenceNum;
    int ackNum; //acknowledgement number
    short int receive;
    short int checkSum;
    short int datPo; //data pointer
    int options;
    char data[1024];
    
	int returnSocket, requestSocket, retrieveSocket, requestSocket2;
	char buffer[1024];
	char newbuffer[1024];
	struct sockaddr_in serverAddr;
	socklen_t addr_size;

    
	/*---- Create the socket. The three arguments are: ----*/
	/* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
	requestSocket = socket(PF_INET, SOCK_STREAM, 0);
    requestSocket2 = socket(PF_INET, SOCK_STREAM, 0);
	retrieveSocket = socket(PF_INET, SOCK_STREAM, 0);

	/*---- Configure settings of the server address struct ----*/
	/* Address family = Internet */
	serverAddr.sin_family = AF_INET;
	/* Set port number, using htons function to use proper byte order */
	serverAddr.sin_port = htons(1110);
	/* Set IP address to localhost or cse */
	//serverAddr.sin_addr.s_addr = inet_addr("71.10.216.1"); //cse
	serverAddr.sin_addr.s_addr = inet_addr("192.168.0.111"); //home
	/* Set all bits of the padding field to 0 */
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

	/*---- Connect the socket to the server using the address struct ----*/
	addr_size = sizeof serverAddr;
    printf("SYSNSENT\n");
    if (connect(requestSocket, (struct sockaddr *) &serverAddr, addr_size) == 1) {
        printf("ESTABLISHED CONNECTION\n");
        connect(requestSocket2, (struct sockaddr *) &serverAddr, addr_size);
    }
    else printf("ERROR CONNECTION FAILED\n");
    close(requestSocket);
    printf("FIN_WAIT_1\n");

	/*---- Read the message from the server into the buffer ----*/
	//recv(retrieveSocket, buffer, 1024, 0);

	/*---- Print the received message ----*/
	//printf("Data received: %s\n", buffer);

	return 0;
}
