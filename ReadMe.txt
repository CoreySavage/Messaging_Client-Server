Read Me - Client/Server Messaging System
COREY SAVAGE
________________


This program was tested on OSU’s flip2 server with a Mac and a PC




OVERVIEW -
________________
This messaging system allows clients to connect to servers through a TCP connection. The program allows users to send alternating messages, display their own name, and quit the messaging program at any time during a conversation. 


Server - Remains open after a client closes their connection, waiting for a new connection with another client. Additionally, servers will display client's hostname along with some error reporting. 


Client - Begins messaging first.




COMPILE - 
________________
With the included makefile, compiling the c file can be done in a couple simple steps
        
1. Download the file to you local computer or desired server.
2. Open up your favorite command-line tool.
3. Go to the directory that the files are currently located.
4. Type make main.c 


You c file will be compiled from the makefile.








EXECUTE -
________________
To execute the server and client applications, the server application must be launched and ready to receive connections before launching the client.
        
To execute the server:
1. Go to a command line tool
2. Go to the directory with the server application 
3. Type Python ChatServer.py <port number>


Once the server is running and listening for connections, open the client application.


        To execute the client:
1. Go to a command line tool
2. Go to the directory with the client application 
3. Type ChatClient <server hostname> <server port number>


Once a client has chosen a handle, the client and server can begin messaging.




CONTROLS - 
________________
        
        \quit                -                Exits Program






RESTRICTIONS -
________________


        500 Character                -                Messages
        10 Character                        -                Handles