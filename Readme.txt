Name : Sunil Venkatraman
Student ID : 7763-9086-68

Aim of the project:

We aim to simulate a chat client with three users and two servers in this project. The requirements state that we must have three users, user1, user2 and user3. We also must have a login server which authenticates the users and if valid allows them to go forward to the supernode. The supernode functions ass a final relay between the end users. 
We are to create TCP and UDP sockets to show how messages are passed between clients through a server environment.

Design:

In my implementation of the above mentioned chat client, i have stuck to the requirements as far as possible. In the project you will find that the requirements are all met. No more or less functionality is present. Where expected dynamic ports have been chosen and been properly displayed. One of the main aims of the assignment is to familiarize students with the TCP and UDP socket programming methodologies which i believe i now completely grasp.

There are three phases to the project. Phase 1 demands us to show how a server listening on a static TCP port will listen to connections coming for it. In this phase we also show how a client authenticates itself at the server. On positive authentication, the loginserver returns the IP address and the UDP port on which the Supernode is listening to the authenticated users.
  
Phase 2 does not involve the clients . In this phase the loginserver opens a dynamic port and sends the IP/login id of all the authenticated clients. The Supernode accepts these inputs, processes them ,then shuts down the TCP port and opens a UDP port to listen on.

Phase 3 involves actual sending and recieving of messages by the clients who have been authenticated. The clients all listen on a fixed UDP port while they send the messages through dynamic ports. The same is the case with the Supernode.

Files:
1. user1.cpp : The code for user 1 in the system. The program reads the username and password from a file and sends the message over a static TCP port that it has created. It then recieves the authentication response. On a positive response it creates a static UDP port. It sends the messages to the supernode then listens on the static UDP port for responses. It produces output messages as and when necessary.

2. user2.cpp : The code for user 2 in the system. The program reads the username and password from a file and sends the message over a static TCP port that it has created. It then recieves the authentication response. On a positive response it creates a static UDP port. It sends the messages to the supernode then listens on the static UDP port for responses. It produces output messages as and when necessary.

3. user3.cpp : The code for user 3 in the system. The program reads the username and password from a file and sends the message over a static TCP port that it has created. It then recieves the authentication response. On a positive response it creates a static UDP port. It sends the messages to the supernode then listens on the static UDP port for responses. It produces output messages as and when necessary.

4. login.cpp : The login server opens UserPassMatch.txt and gets all the username/password combinations. After that it opens a static TCP socket and listens. It accepts connections coming to it and authenticates or rejects clients. After a set number of clients are processed the TCP connection is closed and a dynamic TCP port is created. Over this connection, the loginserver connects with the supernode and sends att the suthenticated IP/username combinations. At this point the job of the login server is done and it is terminated.

5. supernode.cpp : The supernode opens up a static TCP connection and listens to connections on it. When the login server provides the username/IP combinations it accepts and processes it. It then closes the TCP connection. Creates a UDP connection and when a message is recieved it parses the message to find the destination user and forwards it to the right user via a dynamic UDP connection.

To run the program:

To compile the code please type :

g++ -o user1 user1.cpp -lsocket -lnsl -lresolv
g++ -o user2 user2.cpp -lsocket -lnsl -lresolv
g++ -o user3 user3.cpp -lsocket -lnsl -lresolv
g++ -o login login.cpp -lsocket -lnsl -lresolv
g++ -o supernode supernode.cpp -lsocket -lnsl -lresolv


After clean compilation of code, to run type 

./login
./supernode
./user1
./user2
./user3

each one in a different instance and following the abovemwntioned order.

The format of the messages exchanged are as mentioned with <space> being a delimiter at the messages where a username or password is being exchanged. Otherwise the delimiter is a #.

Code has heavily been used from the beej's guide to socket programming which has proven to be an invaluable asset for the purpose of this assigment.

Any error occuring anywhere in the socket related sections is given by perror().
