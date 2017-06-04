
/*
 Travis Allan
 11/19/15
 CSCE 3530
 Program 4
 Special note: Dr. Pottathuparambil provided the code for the checksum, specifically lines 29, 30, and 41-51. The base code used in this program is property of programminglogic.com.I do not claim ownership of that code.
 source: Example of Client-Server Program in C (Using Sockets and TCP) */

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

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


int main(int argc, char *argv[]){
    struct TCP Segment; //handshake
    struct TCP Segment2; //file transfer
    struct TCP Segment3; //closing
    struct TCP Segment4; //final
    struct TCP Segment5; //final
    struct TCP Received; //returned from server
    struct TCP Received2; //returned from server
    struct TCP Received3;
    struct sockaddr_storage serverStorage;
    
    unsigned short int cksum_arr[12]; //code provided by Dr. Pottathuparrambil
    unsigned int i,sum=0, cksum; //code provided by Dr. Pottathuparrambil
    
    int returnSocket, requestSocket, retrieveSocket, temp, total;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    
    /*---- Create the socket. The three arguments are: ----*/
    /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
    requestSocket = socket(PF_INET, SOCK_STREAM, 0);
    retrieveSocket = socket(PF_INET, SOCK_STREAM, 0);
    
    /*---- Configure settings of the server address struct ----*/
    /* Address family = Internet */
    serverAddr.sin_family = AF_INET;
    /* Set port number, using htons function to use proper byte order */
    serverAddr.sin_port = htons(1110);
    /* Set IP address to localhost or cse */
    serverAddr.sin_addr.s_addr = inet_addr("129.120.151.95"); //cse
    //serverAddr.sin_addr.s_addr = inet_addr("192.168.0.146"); //home
    

    //set variables
    Segment.receive = 0;
    Segment.datPo = 0;
    Segment.options = 0;
    //Segment.destination = 71.10.216.1
    //Segment.source = 71.10.216.1
    
    
    
    //handshake with checksum
    Segment.seq = 0;
    Segment.synbit = 1;
    
    //lines xx - xx provided by Dr. Pottathuparambil for checksum
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
    
    /*---- Bind the address struct to the socket ----*/
    bind(requestSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    
    addr_size = sizeof Segment;
    send(requestSocket, (struct TCP*)&Segment, addr_size, 0);
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
    Segment.seq = Segment.seq + 1;
    Segment.ack = Received.seq + 1;
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
    send(requestSocket, (struct TCP*)&Segment, addr_size, 0);
    //recv(retrieveSocket, (struct sockaddr *) &serverAddr, &addr_size);
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
    printf("ACK: %d\n", Segment.ackbit);
    printf("FIN: %d\n\n", Segment.finbit);
    
    
    //file send segment
    Segment3.seq = 0;
    Segment3.ack = 0;
    strcpy(Segment3.data, argv[1024]);
    while (total > 0) {
        
        
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
        send(requestSocket, (struct TCP*)&Segment3, addr_size, 0);
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
        
        listen(retrieveSocket, 1);
        recv(retrieveSocket, (char*)&Segment, addr_size, 0);
        memcpy(&Received3, (char*)&Segment, sizeof(Received3));
        printf("Received\n");
        printf("Source: %d\n", Received3.source);
        printf("Destination: %d\n", Received3.destination);
        printf("seq: %d\n", Received3.seq);
        printf("acknowledgemnt: %d\n", Received3.ack);
        printf("reserved: %d\n", Received3.reserved);
        printf("offset: %d\n", Received3.offset);
        printf("Receive: %d\n", Received3.receive);
        printf("check sum: %d\n", Received3.checkSum);
        printf("data pointer: %d\n", Received3.datPo);
        printf("flag: %d\n", Received3.flag);
        printf("SYN: %d\n", Received3.synbit);
        printf("ACK: %d\n\n", Received3.ackbit);    //acknowledgement segment
        printf("FIN: %d\n\n", Received3.finbit);
        Segment3.seq = Segment3.seq + 1;
        Segment3.ack = Received.seq + 1;
        Segment3.ackbit = 1;
        
        total = total - 128;
    }
    
    //close connection segment
    
    //variables
    Segment4.seq = 0;
    Segment4.finbit = 1;
    
    //lines xx - xx provided by Dr. Pottathuparambil for checksum
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
    send(requestSocket, (struct TCP*)&Segment4, addr_size, 0);
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
    
    listen(retrieveSocket, 2);
    recv(retrieveSocket, (char*)&Segment4, addr_size, 0);
    memcpy(&Received, (char*)&Segment4, sizeof(Received));
    recv(retrieveSocket, (char*)&Segment4, addr_size, 0);
    memcpy(&Received2, (char*)&Segment4, sizeof(Received2));
    
    printf("Received1\n");
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
    
    printf("Received2\n");
    printf("Source: %d\n", Received2.source);
    printf("Destination: %d\n", Received2.destination);
    printf("seq: %d\n", Received2.seq);
    printf("acknowledgemnt: %d\n", Received2.ack);
    printf("reserved: %d\n", Received2.reserved);
    printf("offset: %d\n", Received2.offset);
    printf("Receive: %d\n", Received2.receive);
    printf("check sum: %d\n", Received2.checkSum);
    printf("data pointer: %d\n", Received2.datPo);
    printf("flag: %d\n", Received2.flag);
    printf("SYN: %d\n", Received2.synbit);
    printf("ACK: %d\n\n", Received2.ackbit);    //acknowledgement segment
    printf("FIN: %d\n\n", Received2.finbit);
    
    //variables
    Segment5.seq = Segment4.seq + 1;
    Segment5.ack = Received.seq + 1;
    Segment5.ackbit = 1;
    
    //lines xx - xx provided by Dr. Pottathuparambil for checksum
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
    send(requestSocket, (struct TCP*)&Segment4, addr_size, 0);
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
    
    
    return 0;
}
