#include <fstream.h>
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/wait.h>

#define BACKLOG 5
/*
static ports
TCP port 22768
UDP port 3768
IP : nunki.usc.edu
*/


void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
char *toUser;
struct addrinfo *superNodeInfo;
char username[3][10];
char IPadd[3][INET_ADDRSTRLEN];
int row = 0;
struct addrinfo hints;
char buf[100];
char buf1[100];
char temp[6][100], temp1[6][100];

void clear()
{
	int i=0;
	for(i=0;i<100;i++)
	{
		buf1[i]='\0';
	}
}


void respond(int x)
{
int status;
	if(strcmp(toUser,"User#1") == 0)
	{
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;//IPv4
	hints.ai_socktype = SOCK_DGRAM;//TCP
	//hints.ai_flags = AI_PASSIVE;//fill in IP
	struct addrinfo *SUPInfo;
	int sockDescpUDP1;
	//cout<<"start"<<endl;
	if ((status = getaddrinfo("localhost", "3868", &hints, &SUPInfo)) != 0)
	{
		cout<<"getaddrinfo failure\n";
		exit(0);
	}
	if ((sockDescpUDP1 = socket(SUPInfo->ai_family, SUPInfo->ai_socktype, SUPInfo->ai_protocol)) == -1)
	{
		cout<<"Socket Error\n";
		exit(0);
	}

	if ((connect(sockDescpUDP1, SUPInfo->ai_addr, SUPInfo->ai_addrlen)) == -1)
	{
		perror("Connect error:");
		exit(0);
	}
	int getsock_check;
	int addrlen;
	struct sockaddr_in my_addr;
	addrlen = sizeof(my_addr);
	if ((getsock_check=getsockname(sockDescpUDP1,(struct sockaddr *)&my_addr, (socklen_t*) &addrlen))==-1){
      //Error checking
      perror("getsockname");
      exit(0);
    }
	int len = strlen(temp1[x]);
	int bytes_sent = send(sockDescpUDP1, temp1[x], len, 0);
	sleep(2);
	cout<<"Phase 3: SuperNode sent the message "<<temp1[x]<<" on dynamic UDP port number "<<ntohs(my_addr.sin_port)<<endl;
	//cout<<"End of send to 1\n"<<temp1[x]<<endl;
	close(sockDescpUDP1);
	return;
	} 
	
	if(strcmp(toUser,"User#2") == 0)
	{
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;//IPv4
	hints.ai_socktype = SOCK_DGRAM;//TCP
	//hints.ai_flags = AI_PASSIVE;//fill in IP
	struct addrinfo *SUPInfo;
	int sockDescpUDP1;
	//cout<<"start"<<endl;
	if ((status = getaddrinfo("localhost", "3968", &hints, &SUPInfo)) != 0)
	{
		cout<<"getaddrinfo failure\n";
		exit(0);
	}
	if ((sockDescpUDP1 = socket(SUPInfo->ai_family, SUPInfo->ai_socktype, SUPInfo->ai_protocol)) == -1)
	{
		cout<<"Socket Error\n";
		exit(0);
	}

	if ((connect(sockDescpUDP1, SUPInfo->ai_addr, SUPInfo->ai_addrlen)) == -1)
	{
		perror("Connect error:");
		exit(0);
	}
	int getsock_check;
	int addrlen;
	struct sockaddr_in my_addr;
	addrlen = sizeof(my_addr);
	if ((getsock_check=getsockname(sockDescpUDP1,(struct sockaddr *)&my_addr, (socklen_t*) &addrlen))==-1){
      //Error checking
      perror("getsockname");
      exit(0);
    }
	int len = strlen(temp1[x]);
	int bytes_sent = send(sockDescpUDP1, temp1[x], len, 0);
	sleep(2);
	cout<<"Phase 3: SuperNode sent the message "<<temp1[x]<<" on dynamic UDP port number "<<ntohs(my_addr.sin_port)<<endl;
	//cout<<"End of send to 2\n"<<temp1[x]<<endl;
	close(sockDescpUDP1);
	return;
	}
	
	if(strcmp(toUser,"User#3") == 0)
	{
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;//IPv4
	hints.ai_socktype = SOCK_DGRAM;//TCP
	//hints.ai_flags = AI_PASSIVE;//fill in IP
	struct addrinfo *SUPInfo;
	int sockDescpUDP1;
	//cout<<"start"<<endl;
	if ((status = getaddrinfo("localhost", "4068", &hints, &SUPInfo)) != 0)
	{
		cout<<"getaddrinfo failure\n";
		exit(0);
	}
	if ((sockDescpUDP1 = socket(SUPInfo->ai_family, SUPInfo->ai_socktype, SUPInfo->ai_protocol)) == -1)
	{
		cout<<"Socket Error\n";
		exit(0);
	}

	if ((connect(sockDescpUDP1, SUPInfo->ai_addr, SUPInfo->ai_addrlen)) == -1)
	{
		perror("Connect error:");
		exit(0);
	}
	int getsock_check;
	int addrlen;
	struct sockaddr_in my_addr;
	addrlen = sizeof(my_addr);
	if ((getsock_check=getsockname(sockDescpUDP1,(struct sockaddr *)&my_addr, (socklen_t*) &addrlen))==-1){
      //Error checking
      perror("getsockname");
      exit(0);
    }
	int len = strlen(temp1[x]);
	int bytes_sent = send(sockDescpUDP1, temp1[x], len, 0);
	sleep(2);
	cout<<"Phase 3: SuperNode sent the message "<<temp1[x]<<" on dynamic UDP port number "<<ntohs(my_addr.sin_port)<<endl;
	close(sockDescpUDP1);
	return;
	}
}

void phase2()
{

	int status, tempSockDescp,count;
	int  sockLoginDescp;
	
	char ipstr[INET_ADDRSTRLEN];
	char IP[3][INET_ADDRSTRLEN];
	char tempUser[100],tempPass[100];
	struct sockaddr_storage their_addr;
    socklen_t addr_size;

	count = 0;



	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;//IPv4
	hints.ai_socktype = SOCK_STREAM;//TCP
	//hints.ai_flags = AI_PASSIVE;//fill in IP

	if ((status = getaddrinfo("nunki.usc.edu", "22768", &hints, &superNodeInfo)) != 0)
	{
		cout<<"getaddrinfo failure\n";
		exit(0);
	}

	if ((sockLoginDescp = socket(superNodeInfo->ai_family, superNodeInfo->ai_socktype, superNodeInfo->ai_protocol)) == -1)
	{
		cout<<"Socket Error\n";
		exit(0);
	}

	if ((bind(sockLoginDescp, superNodeInfo->ai_addr, superNodeInfo->ai_addrlen)) == -1)
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
	struct sockaddr_in *ipv4 = (struct sockaddr_in *)superNodeInfo->ai_addr;
    addr = &(ipv4->sin_addr);
	inet_ntop(superNodeInfo->ai_family, addr, ipstr, sizeof ipstr);
	cout<<"Phase 2: Super Node has TCP port number: "<< "22768" <<" and IP address : "<<ipstr<<endl;
	//now accept the connection
	//cout<<"Waiting for connections\n";
	addr_size = sizeof their_addr;
    if ((tempSockDescp = accept(sockLoginDescp, (struct sockaddr *)&their_addr, &addr_size))== -1)
	{
		cout<<"Accept ERROR\n";
		exit(0);
	}
	inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), ipstr, sizeof ipstr);
    //cout<<"server: got connection from "<<ipstr<<endl;
    int num;

	if ((num = recv(tempSockDescp, buf, sizeof(buf), 0) == -1))
		{
			cout<<"recv error\n";
		}

	//cout<<buf<<endl;
	char *user = strtok(buf," ");
	//cout<<user<<endl;

	while((strcmp(user,"fin#")!=0))
	{
		char *IP = strtok(NULL," ");
		//cout<<IP<<endl;
		strcpy(username[row],user);
		strcpy(IPadd[row],IP);
		row++;
		user = strtok(NULL," ");
	}

	close(tempSockDescp);
	close(sockLoginDescp);
	

	/*phase 3*/
	//udp sock = 3100 + 668 = 3768
	struct addrinfo *supernodeUDPInfo;
	int socksupUDPDescp;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;//IPv4
	hints.ai_socktype = SOCK_DGRAM;//UDP
	//hints.ai_flags = AI_PASSIVE;//fill in IP
	if ((status = getaddrinfo("nunki.usc.edu", "3768", &hints, &supernodeUDPInfo)) != 0)
	{
		cout<<"getaddrinfo failure\n";
		exit(0);
	}

	if ((socksupUDPDescp = socket(supernodeUDPInfo->ai_family, supernodeUDPInfo->ai_socktype, supernodeUDPInfo->ai_protocol)) == -1)
	{
		cout<<"Socket Error\n";
		exit(0);
	}

	if ((bind(socksupUDPDescp, supernodeUDPInfo->ai_addr, supernodeUDPInfo->ai_addrlen)) == -1)
	{
		cout<<"bind error\n";
		perror("Error occured:");
		exit(0);
	}

	
	/*to display the IP address*/
	ipv4 = (struct sockaddr_in *)supernodeUDPInfo->ai_addr;
    addr = &(ipv4->sin_addr);
	inet_ntop(supernodeUDPInfo->ai_family, addr, ipstr, sizeof ipstr);
	cout<<"Phase 3: SuperNode has UDP port number: 3768 and IP address : "<<ipstr<<endl;
	int i=0;
	while(i<(2*row))
	{
	addr_size = sizeof their_addr;
    /*if ((tempSockDescp = accept(socksupUDPDescp, (struct sockaddr *)&their_addr, &addr_size))== -1)
	{
		perror("Accept error");
		exit(0);
	}*/
	inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), ipstr, sizeof ipstr);
    //printf("server: got connection from %s\n", ipstr);
    int num;
	clear();
	if ((num = recv(socksupUDPDescp, buf1, sizeof(buf1), 0) == -1))
		{
			cout<<"recv error\n";
		}
	//cout<<buf1<<endl;
	cout<<"Phase 3: SuperNode received the message : "<<buf1<<endl;
	strcpy(temp[i],buf1);
	strcpy(temp1[i], temp[i]);
	i++;
	//toUser[0]='/0';
	//cout<<i<<" "<<temp[i-1]<<endl;
	}
	
	for(i=0;i<(2*row);i++)
	{
		toUser = strtok(temp[i],"-");
	//cout<<toUser<<endl;
		respond(i);
	}
	close(socksupUDPDescp);
}

void clearTemp()
{
	int i,j;
	for(i=0;i<6;i++)
	{
		for(j=0;j<100;j++)
		{
			temp[i][j]='\0';
			temp1[i][j] = '\0';
		}
	}
}



int main()
{
	clearTemp();
	phase2();
	return 1;
}
