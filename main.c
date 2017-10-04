//
//  Corey Savage
//  main.c
//  ChatClient
//  Description: Client side application for messaging system.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#define MESSAGESIZE 1000            // Message size is larger to ensure no data overflow
#define HANDLESIZE 25

int main(int argc, char *argv[]){
    
    // Found from Beej's Guide
    struct addrinfo hints, *res;
    int sockfd;

    // Error checking for proper number of arguments. (file <hostname> <port num>)
    if(argc!=3){
        printf("ERROR: No port specified. Type: chatClient <hostname> <port number>");
        exit(1);
    }

    // Alias for client, with error reporting for length requirments, (1-10 char)
    // Subtract 1 from strlen() to remove null sign
    char clientHandle[HANDLESIZE];
    do {
        printf("Input Handle: ");
        fgets(clientHandle, sizeof(clientHandle), stdin);
        if ((strlen(clientHandle) - 1) > 10) {
            printf("User Name must be between [1-10] characters.\n");
        }
    } while ((strlen(clientHandle) - 1) > 10);
    
    
    // Load address structs with getaddrinfo(): -Found on class discussion board
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    getaddrinfo(argv[1], argv[2], &hints, &res);
    
    
    // Make the socket
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    
    // Connect with server application
    int status = connect(sockfd, res->ai_addr, res->ai_addrlen);
    if (status == -1){
        printf("Error in connecting socket");
    }
    
    // Send client alias
    send(sockfd, clientHandle, strlen(clientHandle), 0);
    
    // Receives server handle, or prints an error if the socket connection was unsucessful
    int recieveCheck;
    char serverHandle[HANDLESIZE];
    recieveCheck = recv(sockfd, serverHandle, HANDLESIZE-1, 0);
    // 0 - quit, -1 - Error, 1 < message length
    if (recieveCheck == -1) {
        printf("ERROR: in recv function while receiving message for a connected socket\n");
    }

    printf("Connection established: %s\n", serverHandle);

    
    int exitChat = 0;                       // Bool to exit connection
    char clientMessage[MESSAGESIZE];        // message buffer for client
    char serverMessage[MESSAGESIZE];        // message buffer for server
    char exitCommand[7] = "\\quit\n";       // command to quit
    while (exitChat == 0) {
        
        // Reset buffer
        memset(&serverMessage, 0, sizeof(serverMessage));
        memset(&clientMessage, 0, sizeof(clientMessage));
        
        // Asks user for input for message delivery. Messages must be no more than 500 char
        // If client user types "\quit" the message will not be sent and the connection
        // will be terminated.
        do {
            printf("> ");
            fgets(clientMessage, sizeof(clientMessage), stdin);
            if (strlen(clientMessage) > 501 || strlen(clientMessage) < 1) {
                printf("Message must be between [1-500] characters.\n");
            }
        } while (strlen(clientMessage) > 500);
        
        if (!(strcmp(clientMessage, exitCommand))) {
            exitChat = 1;
            printf("Connection closed\n");
            close(sockfd);
            break;
        }
        // Message passes error checking and quit command - send
        send(sockfd, clientMessage, strlen(clientMessage), 0);

        
        
        // Recieve message from server and prints to console with server handle
        recv(sockfd, serverMessage, MESSAGESIZE-1, 0);
        
        if (!(strcmp(serverMessage, "\\quit"))) {
            close(sockfd);
            exitChat = 1;
            printf("Connection closed\n");
            break;
        }
        
        // If message passes error checking and quit command - send
        printf("%s > %s\n", serverHandle, serverMessage);
    }
    
    
    
    return 0;
    
    
}
