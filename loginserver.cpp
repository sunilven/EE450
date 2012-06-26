#include <fstream.h>
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include "login.h"

#define LOGINTCP 21768
#define BACKLOG 5

/*Global Variable Declarations*/
char fileRead[100];
int j=0;
int i=0;
int m=0;
char user[3][10];
char pass[3][10];
extern struct addrinfo *loginServerInfo;
struct addrinfo *loginSupernodeInfo;
//read username file
void readFile()
{
	ifstream read("/home/scf-03/sunilven/450proj/UserPassMatch.txt"); //load file
	if (read.is_open()== false) //check if the file is loaded
	{
		cout<<"Cannot Open File\n";
		return;
	}
	while(j<3) //get values of username and password and store it in local variables
	{
		i=0;
		read.getline(fileRead, 100);
		while(fileRead[i]!=' ')
		{
			user[j][i] = fileRead[i];
			i++;
		}//end of user while
		i++;
		m=0;
		while(i<=strlen(fileRead))
		{
			pass[j][m] = fileRead[i];
			i++;
			if(i!=strlen(fileRead))
			m++;

		}//end of pass while
		/*
		user[j]=strtok(fileRead," ");
		pass[j]=strtok(NULL, " ");*/
		j++;
		//cout<<user;
	}//end of while(j<3)
	/*
		for (j=0;j < 3; j++)
		{
			for (i=0;i < 10; i++)
			{
				cout<<user[j][i];
			}
			cout << " ";
			for (i=0;i < 10; i++)
			{
				cout<<pass[j][i];
			}
			cout<<endl;
		}
	*/
}//end of read file()

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void setupTCP()
{
	int status, tempSockDescp,count, requestCount, socksupernodeDescp;
	int  sockLoginDescp;
	struct addrinfo hints;
	char ipstr[INET_ADDRSTRLEN];
	char IP[3][INET_ADDRSTRLEN];
	char buf[100], tempUser[100],tempPass[100];
	struct sockaddr_storage their_addr;
    socklen_t addr_size;
	struct in_addr **addr_list;
	bool userSend[3]={false,false,false};
	count = 0;
	requestCount = 0;


	struct hostent *supernode;
	if((supernode = gethostbyname("nunki.usc.edu")) == NULL)
	{
		herror("gethostbyname error");
		exit(0);
	}
	addr_list = (struct in_addr**)supernode->h_addr_list;


	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;//IPv4
	hints.ai_socktype = SOCK_STREAM;//TCP
	//hints.ai_flags = AI_PASSIVE;//fill in IP

	if ((status = getaddrinfo("nunki.usc.edu", "21768", &hints, &loginServerInfo)) != 0)
	{
		cout<<"getaddrinfo failure\n";
		exit(0);
	}

	if ((sockLoginDescp = socket(loginServerInfo->ai_family, loginServerInfo->ai_socktype, loginServerInfo->ai_protocol)) == -1)
	{
		cout<<"Socket Error\n";
		exit(0);
	}

	if ((bind(sockLoginDescp, loginServerInfo->ai_addr, loginServerInfo->ai_addrlen)) == -1)
	{
		cout<<"bind error\n";
		perror("Error occured:");
		exit(0);
	}

	if ((status = listen(sockLoginDescp, BACKLOG)) == -1)
	{
		cout<<"Listen ERROR\n";
		exit(0);
	}
	/*to display the IP address*/
	void *addr;
	struct sockaddr_in *ipv4 = (struct sockaddr_in *)loginServerInfo->ai_addr;
    addr = &(ipv4->sin_addr);
	inet_ntop(loginServerInfo->ai_family, addr, ipstr, sizeof ipstr);
	cout<<"Phase 1: Login server has TCP port number: "<< LOGINTCP <<" and IP address : "<<ipstr<<endl;
	//now accept the connection
	cout<<"Waiting for connections\n";
	while(requestCount < 3)
	{
	addr_size = sizeof their_addr;
    if ((tempSockDescp = accept(sockLoginDescp, (struct sockaddr *)&their_addr, &addr_size))== -1)
	{
		cout<<"Accept ERROR\n";
		exit(0);
	}
	inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), ipstr, sizeof ipstr);
    printf("server: got connection from %s\n", ipstr);
    int num;
	requestCount++;
	if ((num = recv(tempSockDescp, buf, sizeof(buf), 0) == -1))
		{
			cout<<"recv error\n";
		}
	m=0;
	//cout<<buf<<endl;
	//cout<<"Number of bits received : "<<strlen(buf)<<endl;
	char* request = strtok(buf, "#");
	char* username = strtok(NULL, " ");
	char* passw = strtok(NULL, " ");
	char usertmp[10];
	char passtmp[10];
	bool userbool;
	int k,l,myrow;

	if(strcmp(request,"Login") == 0)
		{
			for ( i=0;i<3;i++)
			{
				for(j=0;j<10;j++)
				{
					usertmp[j]=user[i][j];
					passtmp[j]=pass[i][j];

				}
				/*cout << usertmp<<" "<<strlen(usertmp)<<endl;
				cout << username<<" "<<strlen(username)<<endl;
				cout<<strcmp(username,usertmp);*/
				if(strcmp(username,usertmp) == 0)
				{
					userbool = true;
					myrow=i;
					int len = strlen(passw);
						for(int n=0;n<len-1;n++)
						{
							if(passw[n]!=pass[i][n])
								{
									userbool = false;
									//cout<<"false"<<" "<<n<<" "<<pass[i][n]<<endl;
								}
						}

				}
			}
		}


	cout<<"Authentication Request"<<endl;
	cout<<"User : "<<username<<endl;
	cout<<"Password : "<<passw<<endl;
	cout<<"User IP address : "<< ipstr<<endl;
	char msg[50];
	if (userbool == true)
	{
		cout<<"Authorized : Yes"<<endl;
		strcpy(msg,"#Accepted#");
		strcat(msg,inet_ntoa(*addr_list[0]));
		strcat(msg,"#");
		strcat(msg,"3768#");
		cout<<"Phase 1: SuperNode IP Address : "<<inet_ntoa(*addr_list[0])<<" Port Number: 3768 sent to User#"<<(myrow+1)<<endl;
		int len = strlen(msg);
		int bytesSent = send(tempSockDescp, msg, len, 0);
		userSend[myrow] = true;
		//cout<<"userSend "<<myrow<<" is "<<userSend[myrow]<<endl;
		for(i=0;i<strlen(ipstr);i++)
		{
			IP[myrow][i]=ipstr[i];
		}

		count++;
		//send the IP address and port number of the supernode

	}
	else if (userbool == false)
	{
		cout<<"Authorized : No"<<endl;
		char msg[] = "#Rejected";
		int len = strlen(msg);
		int bytesSent = send(tempSockDescp, msg, len, 0);
	}

        close(tempSockDescp);  // parent doesn't need this

	}
	close(sockLoginDescp);
	//cout<<IP[0];
	cout<<"End of Phase 1 for login server"<<endl;
	close(sockLoginDescp);
	/*PHASE 2*/
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;//IPv4
	hints.ai_socktype = SOCK_STREAM;//TCP
	hints.ai_flags = AI_PASSIVE;//fill in IP

	if ((status = getaddrinfo("nunki.usc.edu", "22768", &hints, &loginSupernodeInfo)) != 0)
	{
		cout<<"getaddrinfo failure\n";
		exit(0);
	}

	if ((socksupernodeDescp = socket(loginSupernodeInfo->ai_family, loginSupernodeInfo->ai_socktype, loginSupernodeInfo->ai_protocol)) == -1)
	{
		cout<<"Socket Error\n";
		exit(0);
	}

	if ((connect(socksupernodeDescp, loginSupernodeInfo->ai_addr, loginSupernodeInfo->ai_addrlen)) == -1)
	{
		perror("Connect error:");
		exit(0);
	}
	int k;
	int getsock_check;
	int addrlen;
	struct sockaddr_in my_addr;
	addrlen = sizeof(my_addr);
	if ((getsock_check=getsockname(socksupernodeDescp,(struct sockaddr *)&my_addr, (socklen_t*) &addrlen))==-1){
      //Error checking
      perror("getsockname");
      exit(0);
    }

	//display ip and port of loginserver
	cout<<"Phase 2: Login Server has TCP port: "<<ntohs(my_addr.sin_port)<<" and IP address: "<<inet_ntoa(my_addr.sin_addr)<<endl;
	char msg[100];
	msg[0]='\0';
	int countsender;
	countsender=0;
	//cout<<"Inside while"<<endl;
		//send the ip and username to supernode
	for(i=0;i<3;i++)
		{
			if (userSend[i]==true)
			{
				//cout<<IP[i]<<endl;
				strcat(msg, user[i]);
				strcat(msg, " ");
				strcat(msg, IP[i]);
				strcat(msg," ");
				countsender++;

			}

		}
		strcat(msg,"fin#");
		int len = strlen(msg);
		int bytesSent;
		//cout<<msg<<endl;
		if((bytesSent = send(socksupernodeDescp, msg, len, 0)) == -1)
		perror("Send issue");

		close(socksupernodeDescp);
		cout<<"Phase 2: LogIn Server sent "<<countsender<<" username/IP address pairs to SuperNode"<<endl;
		//cout<<msg;
		close(socksupernodeDescp);
		cout<<"End of Phase 2 for LogIn Server"<<endl;
		
		//Make a udp port to listen on port number is 3768
		
		


	}

	int main()
	{
		/*Create a TCP Socket and listen for incoming connections
		TCP port = 21100+668 = 21768*/
		readFile();
		setupTCP();
		return 0;
	}
