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

struct TCP{
    short int source;
    short int destination; //
    int seq; //sequence number
    int ack; //acknowledgement number
    short int reserved;
    short int offset; //offset and header length
    short int receive;
    short int checkSum;
    short int datPo; //data pointer
    short int flag;
    short int synbit;
    short int ackbit;
    short int finbit;
    int options;
    char data[1024];
    
};

int main(){
    struct TCP Segment;
    struct TCP Segment2;
    struct TCP Segment3;
    struct TCP Segment4;
    struct TCP Received;
    struct TCP Received4;
    unsigned short int cksum_arr[12]; //code provided by Dr. Pottathuparrambil
    unsigned int i,sum=0, cksum; //code provided by Dr. Pottathuparrambil
    
    
    int welcomeSocket, newSocket, ipSocket, j, array[5][20];
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
    newSocket = socket(PF_INET, SOCK_STREAM, 0);
    /*---- Configure settings of the server address struct ----*/
    /* Address family = Internet */
    serverAddr.sin_family = AF_INET;
    /* Set port number, using htons function to use proper byte order */
    serverAddr.sin_port = htons(1110);
    /* Set IP address to localhost */
    serverAddr.sin_addr.s_addr = inet_addr("129.120.151.94"); //cse
    //serverAddr.sin_addr.s_addr = inet_addr("192.168.0.146"); //home
    
    //set variables
    Segment.receive = 0;
    Segment.datPo = 0;
    Segment.options = 0;
    //Segment.destination = 71.10.216.1
    //Segment.source = 71.10.216.1
    
    
    //handshake with checksum
    Segment.seq = 0;
    Segment.synbit = 1;
    
    /*---- Bind the address struct to the socket ----*/
    bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    listen(welcomeSocket,1);

    //receive initial connection
    recv(welcomeSocket, (char*)&Segment, addr_size, 0);
    memcpy(&Received, (char*)&Segment, sizeof(Received));
    printf("Received\n");
    printf("Source: %d\n", Received.source);
    printf("Destination: %d\n", Received.destination);
    printf("seq: %d\n", Received.seq);
    printf("acknowledgemnt: %d\n", Received.ack);
    printf("reserved: %d\n", Received.reserved);
    printf("offset: %d\n", Received.offset);
    printf("Receive: %d\n", Received.receive);
    printf("check sum: %d\n", Received.checkSum);
    printf("data pointer: %d\n", Received.datPo);
    printf("flag: %d\n", Received.flag);
    printf("SYN: %d\n", Received.synbit);
    printf("ACK: %d\n\n", Received.ackbit);    //acknowledgement segment
    printf("FIN: %d\n\n", Received.finbit);

    //change variables
    Segment.seq = Received.seq + 1;
    Segment.synbit = 1;
    Segment.ackbit = 1;
    
    //lines xx - xx provided by Dr. Pottathuparrambil for checksum
    memcpy(cksum_arr, &Segment, 24); //Copying 24 bytes
    for (i=0;i<12;i++)               // Compute sum
        sum = sum + cksum_arr[i];
    cksum = sum >> 16;              // Fold once
    sum = sum & 0x0000FFFF;
    sum = cksum + sum;
    cksum = sum >> 16;             // Fold once more
    sum = sum & 0x0000FFFF;
    cksum = cksum + sum;
    Segment.checkSum = cksum;
    
    addr_size = sizeof Segment;
    send(newSocket, (char *)&Segment, addr_size, 0);
    printf("Sent\n");
    printf("Source: %d\n", Segment.source);
    printf("Destination: %d\n", Segment.destination);
    printf("seq: %d\n", Segment.seq);
    printf("acknowledgemnt: %d\n", Segment.ack);
    printf("reserved: %d\n", Segment.reserved);
    printf("offset: %d\n", Segment.offset);
    printf("Receive: %d\n", Segment.receive);
    printf("check sum: %d\n", Segment.checkSum);
    printf("data pointer: %d\n", Segment.datPo);
    printf("flag: %d\n", Segment.flag);
    printf("SYN: %d\n", Segment.synbit);
    printf("ACK: %d\n\n", Segment.ackbit);
    printf("FIN: %d\n\n", Segment.finbit);

    
    //file receive segment
    while (total > 0) {
        listen(retrieveSocket, 1);
        recv(retrieveSocket, (char*)&Segment, addr_size, 0);
        memcpy(&Received, (char*)&Segment, sizeof(Received));
        printf("Received\n");
        printf("Source: %d\n", Received.source);
        printf("Destination: %d\n", Received.destination);
        printf("seq: %d\n", Received.seq);
        printf("acknowledgemnt: %d\n", Received.ack);
        printf("reserved: %d\n", Received.reserved);
        printf("offset: %d\n", Received.offset);
        printf("Receive: %d\n", Received.receive);
        printf("check sum: %d\n", Received.checkSum);
        printf("data pointer: %d\n", Received.datPo);
        printf("flag: %d\n", Received.flag);
        printf("SYN: %d\n", Received.synbit);
        printf("ACK: %d\n\n", Received.ackbit);    //acknowledgement segment
        printf("FIN: %d\n\n", Received.finbit);
        
        //lines xx - xx provided by Dr. Pottathuparrambil for checksum
        memcpy(cksum_arr, &Segment3, 24); //Copying 24 bytes
        for (i=0;i<12;i++)               // Compute sum
            sum = sum + cksum_arr[i];
        cksum = sum >> 16;              // Fold once
        sum = sum & 0x0000FFFF;
        sum = cksum + sum;
        cksum = sum >> 16;             // Fold once more
        sum = sum & 0x0000FFFF;
        cksum = cksum + sum;
        Segment3.checkSum = cksum;
        
        addr_size = sizeof Segment2;
        send(requestSocket, (struct TCP*)&Segment2, addr_size, 0);
        printf("Sent\n");
        printf("Source: %d\n", Segment2.source);
        printf("Destination: %d\n", Segment2.destination);
        printf("seq: %d\n", Segment2.seq);
        printf("acknowledgemnt: %d\n", Segment2.ack);
        printf("reserved: %d\n", Segment2.reserved);
        printf("offset: %d\n", Segment2.offset);
        printf("Receive: %d\n", Segment2.receive);
        printf("check sum: %d\n", Segment2.checkSum);
        printf("data pointer: %d\n", Segment2.datPo);
        printf("flag: %d\n", Segment2.flag);
        printf("SYN: %d\n", Segment2.synbit);
        printf("ACK: %d\n\n", Segment2.ackbit);
        printf("FIN: %d\n\n", Segment2.finbit);
        
        total = total - 128;
    }
    
    
    //close connection segment
    
    listen(welcomeSocket,1);
    
    recv(welcomeSocket, (char*)&Segment, addr_size, 0);
    memcpy(&Received4, (char*)&Segment, sizeof(Received4));
    printf("Received\n");
    printf("Source: %d\n", Received4.source);
    printf("Destination: %d\n", Received4.destination);
    printf("seq: %d\n", Received4.seq);
    printf("acknowledgemnt: %d\n", Received4.ack);
    printf("reserved: %d\n", Received4.reserved);
    printf("offset: %d\n", Received4.offset);
    printf("Receive: %d\n", Received4.receive);
    printf("check sum: %d\n", Received4.checkSum);
    printf("data pointer: %d\n", Received4.datPo);
    printf("flag: %d\n", Received4.flag);
    printf("SYN: %d\n", Received4.synbit);
    printf("ACK: %d\n\n", Received4.ackbit);    //acknowledgement segment
    printf("FIN: %d\n\n", Received4.finbit);
    
    Segment3.seq = Received.seq + 1;
    Segment3.ackbit = 1;
    
    //lines xx - xx provided by Dr. Pottathuparrambil for checksum
    memcpy(cksum_arr, &Segment3, 24); //Copying 24 bytes
    for (i=0;i<12;i++)               // Compute sum
        sum = sum + cksum_arr[i];
    cksum = sum >> 16;              // Fold once
    sum = sum & 0x0000FFFF;
    sum = cksum + sum;
    cksum = sum >> 16;             // Fold once more
    sum = sum & 0x0000FFFF;
    cksum = cksum + sum;
    Segment3.checkSum = cksum;
    
    addr_size = sizeof Segment3;
    send(newSocket, (char *)&Segment3, addr_size, 0);
    printf("Sent\n");
    printf("Source: %d\n", Segment3.source);
    printf("Destination: %d\n", Segment3.destination);
    printf("seq: %d\n", Segment3.seq);
    printf("acknowledgemnt: %d\n", Segment3.ack);
    printf("reserved: %d\n", Segment3.reserved);
    printf("offset: %d\n", Segment3.offset);
    printf("Receive: %d\n", Segment3.receive);
    printf("check sum: %d\n", Segment3.checkSum);
    printf("data pointer: %d\n", Segment3.datPo);
    printf("flag: %d\n", Segment3.flag);
    printf("SYN: %d\n", Segment3.synbit);
    printf("ACK: %d\n\n", Segment3.ackbit);
    printf("FIN: %d\n\n", Segment3.finbit);
    
    Segment4.seq = Received.seq + 1;
    Segment4.finbit = 1;
    
    //lines xx - xx provided by Dr. Pottathuparrambil for checksum
    memcpy(cksum_arr, &Segment4, 24); //Copying 24 bytes
    for (i=0;i<12;i++)               // Compute sum
        sum = sum + cksum_arr[i];
    cksum = sum >> 16;              // Fold once
    sum = sum & 0x0000FFFF;
    sum = cksum + sum;
    cksum = sum >> 16;             // Fold once more
    sum = sum & 0x0000FFFF;
    cksum = cksum + sum;
    Segment4.checkSum = cksum;
    
    addr_size = sizeof Segment4;
    send(newSocket, (char *)&Segment4, addr_size, 0);
    printf("Sent\n");
    printf("Source: %d\n", Segment4.source);
    printf("Destination: %d\n", Segment4.destination);
    printf("seq: %d\n", Segment4.seq);
    printf("acknowledgemnt: %d\n", Segment4.ack);
    printf("reserved: %d\n", Segment4.reserved);
    printf("offset: %d\n", Segment4.offset);
    printf("Receive: %d\n", Segment4.receive);
    printf("check sum: %d\n", Segment4.checkSum);
    printf("data pointer: %d\n", Segment4.datPo);
    printf("flag: %d\n", Segment4.flag);
    printf("SYN: %d\n", Segment4.synbit);
    printf("ACK: %d\n\n", Segment4.ackbit);
    printf("FIN: %d\n\n", Segment4.finbit);
    
    
    recv(welcomeSocket, (char*)&Segment4, addr_size, 0);
    memcpy(&Received5, (char*)&Segment4, sizeof(Received5));
    printf("Received\n");
    printf("Source: %d\n", Received5.source);
    printf("Destination: %d\n", Received5.destination);
    printf("seq: %d\n", Received5.seq);
    printf("acknowledgemnt: %d\n", Received5.ack);
    printf("reserved: %d\n", Received5.reserved);
    printf("offset: %d\n", Received5.offset);
    printf("Receive: %d\n", Received5.receive);
    printf("check sum: %d\n", Received5.checkSum);
    printf("data pointer: %d\n", Received5.datPo);
    printf("flag: %d\n", Received5.flag);
    printf("SYN: %d\n", Received5.synbit);
    printf("ACK: %d\n\n", Received5.ackbit);    //acknowledgement segment
    printf("FIN: %d\n\n", Received5.finbit);
    
    return 0;
}


