#
# Corey Savage
# ChatServer.py
# Description: This program completes the server side functionality of the messaging system.
# Users can choose what port they would like to connect from. Connections are made with TCP
# calls.
#
from socket import *
import sys
import os

#
# Function used to send server messages to the client. The function also check that the
# message has the right length requirements (1-500 char). Additionally, the function
# watches out for "\quit" messages.
#
def serverMessageHandling(connectionSocketIn):
    serverMessage = raw_input("> ")

    # Length error checking
    while (len(serverMessage) > 500 or len(serverMessage) < 1 ):
        print("ERROR: Your message has to be between 1 and 500 characters.")
        serverMessage = raw_input("> ")

    # Quit check
    if serverMessage[:-1] == "\quit":
        connectionSocketIn.close()
        print("Connection closed")
        return 0                        # Return 0 will set the messaging loop to break

    connectionSocketIn.send(serverMessage)


# Error checking for proper number of arguments
if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("USAGE ERROR: python ChatServer.py <Port Number>")
        sys.exit()


# Alias for server
serverHandle = (raw_input("Input Handle: "))
# Error checking with length, must be <= 10 and >= 1
while 1 > len(serverHandle) or len(serverHandle) > 10:
    serverHandle = raw_input("User Name must be between [1-10] characters.\nInput Handle: ")

# Sets up server variables, found on the class discussion boards and Lectures
serverPort = int(sys.argv[1])
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(('', serverPort))
serverSocket.listen(1)

#
# With the server listening for connections, this while loop will run until the program is closed.
# Once a connection has been made, the client and server begin messaging.
# Any time either of them types "\quit" the connection will be terminated.
#
while 1:

    print('The server is ready to receive')
    connectionSocket, addr = serverSocket.accept()
    # Displays client's hostname
    print("Connection from {}".format(gethostbyaddr(addr[0])[0]))
    # Clients Alias
    clientHandle = str(connectionSocket.recv(25))

    print("Connection established: {}".format(clientHandle[:-1]))
    # Send server handle to client
    connectionSocket.send(serverHandle)

    # Loops until the server or client quits the connection
    continueMessaging = 1                               # Used as bool
    while continueMessaging:
        # Server receives client message
        clientMessage = str(connectionSocket.recv(550))
        # If messages sent from client returns 0 than the client has quit the
        # connection successively
        if len(clientMessage) == 0:
            print("Connection closed")
            connectionSocket.close()
            continueMessaging = 0
            break
        # Prints client's message to server
        print("{0} > {1}".format(clientHandle[:-1], clientMessage[:-1]))
        # Sends server message to client unless the message is \quit
        if serverMessageHandling(connectionSocket) == 0:
            break




