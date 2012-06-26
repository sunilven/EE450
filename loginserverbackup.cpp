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
	int status, tempSockDescp,count;
	int  sockLoginDescp;
	struct addrinfo hints;
	char ipstr[INET_ADDRSTRLEN];
	char IP[3][INET_ADDRSTRLEN];
	char buf[100], tempUser[100],tempPass[100];
	struct sockaddr_storage their_addr;
    socklen_t addr_size;
	
	count = 0;
	
	
	
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
	while(1)
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
	if ((num = recv(tempSockDescp, buf, sizeof(buf), 0) == -1))
		{
			cout<<"recv error\n";
		}
	m=0;
	char* request = strtok(buf, "#");
	char* username = strtok(NULL, "#");
	char* passw = strtok(NULL, "#");
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
					//cout<<pass[i][j];
					//getchar();
					passtmp[j]=pass[i][j];
					
				}
				/*cout << usertmp<<" "<<strlen(usertmp)<<endl;
				cout << username<<" "<<strlen(username)<<endl;
				cout<<strcmp(username,usertmp);*/
				if(strcmp(username,usertmp) == 0)
				{
					cout<<"in for "<<usertmp<<endl;
					//cout<<passtmp;
					//cout<<strcmp(passw,passtmp);
					//cout<<"now puts"<<endl;
					//puts(passtmp);
					userbool = true;
					//for ( k=0;k<3;k++)
					//{	int num = strlen(pass[k]);
						//cout<<num;
						//for(l=0;l<num;l++)
						//{
							/*-passtmp[l]=pass[k][l];
							cout << passtmp[l];
							getchar();*/
							//if(pass[k][l]=='/0')
							//continue;
							
							//cout<<pass[k][l]<<" "<<l;
							//getchar();
						//}
						
						//cout << pass[k]<<" "<<strlen(pass[k])<<"1"<<endl;
						//cout << passw<<" "<<strlen(passw)<<endl;
						//cout<<strcmp(passw,pass[k]);
						//getchar();
						/*if(strcmp(passw,passtmp) == 0)
						{
							userbool = true;
							break;
							myrow = i;
						}*/
						for(int n=0;n<10;n++)
						{
							if(passw[n]!=pass[i][n])
								{
									userbool = false;
									cout<<"false"<<" "<<n<<" "<<pass[i][n]<<endl;
								}
						}
					//}
				}
			}
		}
		
	/*while(buf[i]!='#')
	{
		temp[m]=buf[i];
		i++;
		m++;
	}
	i++;
	m=0;
	while(buf[i]!='/')
	{
		tempUser[m]=buf[i];
		i++;
		m++;
	}
	i++;
	m=0;
	while(buf[i]!='/n')
	{
		tempPass[m]=buf[i];
		i++;
		m++;
	}
	*/
	
	/*for (j=0;j<3;j++)
	{
		for(i=0;i<10;i++)
		{
			if (tempUser[i]!=user[j][i])
			{
				tok=-1;
				break;
			}
		}
		if(tok==0)
		{
			myrow=j;
			userbool = true;
			break;
		}
		tok=0;
	}
	
	for (i=0;i<0;i++)
	{
		if(tempPass[i]!=pass[j][i])
		{
			userbool = false;
			break;
		}
	}*/
	
	cout<<"Authentication Request"<<endl;
	cout<<"User : "<<username<<endl;
	cout<<"Password : "<<passw<<endl;
	cout<<"User IP address : "<< ipstr<<endl;
		
	if (userbool == true)
	{
		cout<<"Authorized : Yes"<<endl;
		char msg[] = "#Accepted";
		int len = strlen(msg);
		int bytesSent = send(tempSockDescp, msg, len, 0);
		for(i=0;i<strlen(ipstr);i++)
		{
			IP[myrow][i]=ipstr[i];
		}
		count++;
		//send the IP address and port number of the supernode
		if(count == 3)
		break;
		
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
	cout<<"End of Phase 1 for login server"<<endl;
	/*PHASE 2*/
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;//IPv4
	hints.ai_socktype = SOCK_STREAM;//TCP
	hints.ai_flags = AI_PASSIVE;//fill in IP
	//random number generator
	srand((unsigned)time(0));
	int random_integer;
	int lowest=1025, highest=65535;
	int range=(highest-lowest)+1;
	random_integer = lowest+int(range*rand()/(RAND_MAX + 1.0)); 
	//convert random_integer to string
	
	
	if ((status = getaddrinfo(NULL, "21768", &hints, &loginServerInfo)) != 0)
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
		exit(0);
	}
}
	
	
	
	


	

	
	


int main()
{
	/*Create a TCP Socket and listen for incoming connections
	TCP port = 21100+668 = 21768*/
	readFile();
	setupTCP();
	return 0;
}
