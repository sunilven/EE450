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

#include"login.h"

#define USER1TCP "3868"
#define BACKLOG 5
/*Global Variable Declarations*/
char fileRead[100];
int j=0;
int i=0;
int m=0;
int num;
char user[10];
char pass[10];
char message[50];
extern int forkcount;
struct addrinfo *loginUserInfo;
int myid;



//extern struct addrinfo *loginServerInfo;


//read username file
void readUserFile0()
{
	ifstream read("/home/scf-03/sunilven/450proj/UserPass1.txt"); //load file
	if (read.is_open()== false) //check if the file is loaded
	{
		cout<<"Cannot Open File\n";
		return;
	}
	//while(j<3) //get values of username and password and store it in local variables
	//{
		i=0;
		read.getline(fileRead, 100);
		while(fileRead[i]!=' ')
		{
			user[i] = fileRead[i];
			i++;
		}//end of user while
		i++;
		m=0;
		while(i<=strlen(fileRead))
		{
			pass[m] = fileRead[i];
			i++;
			if (m!=strlen(fileRead))
			m++;
		}//end of pass while
		//j++;
	//}//end of while(j<3)

		/*for (j=0;j < 3; j++)
		{
			for (i=0;i < 10; i++)
			{
				cout<<user[j][i];
			}
			cout << " ";
			for (i=0;i < 10; i++)
			{/
				cout<<pass[j][i];
			}
			cout<<endl;
		}*/

}//end of read file()


void readUserFile1()
{
	ifstream read("/home/scf-03/sunilven/450proj/UserPass2.txt"); //load file
	if (read.is_open()== false) //check if the file is loaded
	{
		cout<<"Cannot Open File\n";
		return;
	}
	//while(j<3) //get values of username and password and store it in local variables
	//{
		i=0;
		read.getline(fileRead, 100);
		while(fileRead[i]!=' ')
		{
			user[i] = fileRead[i];
			i++;
		}//end of user while
		i++;
		m=0;
		while(i<=strlen(fileRead))
		{
			pass[m] = fileRead[i];
			i++;
			if (m!=strlen(fileRead))
			m++;
		}//end of pass while
		//j++;
	//}//end of while(j<3)

		/*for (j=0;j < 3; j++)
		{
			for (i=0;i < 10; i++)
			{
				cout<<user[j][i];
			}
			cout << " ";
			for (i=0;i < 10; i++)
			{/
				cout<<pass[j][i];
			}
			cout<<endl;
		}*/

}//end of read file()


void readUserFile2()
{
	ifstream read("/home/scf-03/sunilven/450proj/UserPass3.txt"); //load file
	if (read.is_open()== false) //check if the file is loaded
	{
		cout<<"Cannot Open File\n";
		return;
	}
	//while(j<3) //get values of username and password and store it in local variables
	//{
		i=0;
		read.getline(fileRead, 100);
		while(fileRead[i]!=' ')
		{
			user[i] = fileRead[i];
			i++;
		}//end of user while
		i++;
		m=0;
		while(i<=strlen(fileRead))
		{
			pass[m] = fileRead[i];
			i++;
			if (m!=strlen(fileRead))
			m++;
		}//end of pass while
		//j++;
	//}//end of while(j<3)

		/*for (j=0;j < 3; j++)
		{
			for (i=0;i < 10; i++)
			{
				cout<<user[j][i];
			}
			cout << " ";
			for (i=0;i < 10; i++)
			{/
				cout<<pass[j][i];
			}
			cout<<endl;
		}*/

}//end of read file()

char u1l1[100],u1l2[100];
char u2l1[100],u2l2[100];
char u3l1[100],u3l2[100];

/*Read User Text files*/
void readUserText0()
{
	ifstream readText("/home/scf-03/sunilven/450proj/UserText1.txt"); //load file
	if (readText.is_open()== false) //check if the file is loaded
	{
		cout<<"Cannot Open File\n";
		return;
	}
	//while(j<3) //get values of username and password and store it in local variables

		readText.getline(fileRead, 100);
		for (i=0;i<strlen(fileRead);i++){
			u1l1[i]=fileRead[i];
		}
		
		readText.getline(fileRead, 100);
		//strcpy(u1l2,fileRead);
		for (i=0;i<strlen(fileRead);i++){
			u1l2[i]=fileRead[i];
		}
}//end of read file()

void readUserText1()
{
	ifstream readText("/home/scf-03/sunilven/450proj/UserText2.txt"); //load file
	if (readText.is_open()== false) //check if the file is loaded
	{
		cout<<"Cannot Open File\n";
		return;
	}
	//while(j<3) //get values of username and password and store it in local variables
	
		readText.getline(fileRead, 100);
		for (i=0;i<strlen(fileRead);i++){
			u2l1[i]=fileRead[i];
		}
		
		readText.getline(fileRead, 100);
		//strcpy(u1l2,fileRead);
		for (i=0;i<strlen(fileRead);i++){
			u2l2[i]=fileRead[i];
		}
}//end of read file()

void readUserText2()
{
	ifstream readText("/home/scf-03/sunilven/450proj/UserText3.txt"); //load file
	if (readText.is_open()== false) //check if the file is loaded
	{
		cout<<"Cannot Open File\n";
		return;
	}
	//while(j<3) //get values of username and password and store it in local variables
	
		readText.getline(fileRead, 100);
		for (i=0;i<strlen(fileRead);i++){
			u3l1[i]=fileRead[i];
		}
		
		readText.getline(fileRead, 100);
		//strcpy(u1l2,fileRead);
		for (i=0;i<strlen(fileRead);i++){
			u3l2[i]=fileRead[i];
		}
}//end of read file()


void makeloginMessage()
{
	/*TO PREPARE THE LOGIN MESSAGE*/


	strcpy(message,"Login#");
	strcat(message,user);
	strcat(message,"#");
	strcat(message,pass);
	strcat(message,"#");

	//cout<<message<<endl;
}
void setupTCP()
{
	int status, sockDescp, sockDescp1, tempSockDescp,count;
	struct addrinfo hints;
	char ipstr[INET_ADDRSTRLEN], port[INET_ADDRSTRLEN];
	char IP[3][INET_ADDRSTRLEN];
	char buf[100], tempUser[100],tempPass[100];
	struct sockaddr_storage their_addr;
    socklen_t addr_size;
	struct addrinfo *loginInfo;



	count = 0;

	unlink("/tmp/mysocket");

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;//IPv4
	hints.ai_socktype = SOCK_STREAM;//TCP
	//hints.ai_flags = AI_PASSIVE;//fill in IP
	struct sockaddr_in my_addr;

	//cout<<"start"<<endl;
	if ((status = getaddrinfo("nunki.usc.edu", "21768", &hints, &loginInfo)) != 0)
	{
		cout<<"getaddrinfo failure\n";
		exit(0);
	}
	if ((sockDescp1 = socket(loginInfo->ai_family, loginInfo->ai_socktype, loginInfo->ai_protocol)) == -1)
	{
		cout<<"Socket Error\n";
		exit(0);
	}


	if ((connect(sockDescp1, loginInfo->ai_addr, loginInfo->ai_addrlen)) == -1)
	{
		perror("Connect error:");
		exit(0);
	}

	int getsock_check;
	int addrlen;
	addrlen = sizeof(my_addr);
	if ((getsock_check=getsockname(sockDescp1,(struct sockaddr *)&my_addr, (socklen_t*) &addrlen))==-1){
      //Error checking
      perror("getsockname");
      exit(0);
    }
	cout<<"Phase 1: User has TCP port: "<<ntohs(my_addr.sin_port)<<" and IP address: "<<inet_ntoa(my_addr.sin_addr)<<endl;
	//cout<<strlen(message)<<endl;
	int len = strlen(message);
	int bytes_sent = send(sockDescp1, message, len, 0);
	//cout<<"bytes sent: "<<bytes_sent<<endl;

	if ((num = recv(sockDescp1, buf, sizeof(buf), 0) == -1))
		{
			cout<<"recv error\n";
		}
	//cout<<buf<<endl;
	char *messagerecv = strtok(buf,"#");
	if (strcmp(messagerecv, "Accepted") ==0)
	{
		char *IP = strtok(NULL,"#");
		char *udpPort = strtok(NULL,"#");
		cout<<"Phase 1: SuperNode has IP address: "<<IP<<" and Port number: "<<udpPort<<endl;
	}else{return;}
	close(sockDescp1);

	//make a udp socket and listen to it
	if(myid==0){
	//udp sock = 3200 + 668 = 3868
	struct addrinfo *UDPsend0;
	int sockc1UDPDescp;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;//IPv4
	hints.ai_socktype = SOCK_DGRAM;//UDP
	//hints.ai_flags = AI_PASSIVE;//fill in IP

	if ((status = getaddrinfo("localhost", "3868", &hints, &UDPsend0)) != 0)
	{
		cout<<"getaddrinfo failure\n";
		exit(0);
	}

	if ((sockc1UDPDescp = socket(UDPsend0->ai_family, UDPsend0->ai_socktype, UDPsend0->ai_protocol)) == -1)
	{
		cout<<"Socket Error\n";
		exit(0);
	}

	if ((bind(sockc1UDPDescp, UDPsend0->ai_addr, UDPsend0->ai_addrlen)) == -1)
	{
		cout<<"bind error in 1\n";
		perror("Error occured:");
		exit(0);
	}
	cout<<"socket made sleeping before sending"<<endl;
 	sleep(10);
	
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;//IPv4
	hints.ai_socktype = SOCK_DGRAM;//TCP
	//hints.ai_flags = AI_PASSIVE;//fill in IP
	struct addrinfo *SUPInfo;
	int sockDescpUDP1;
	//cout<<"start"<<endl;
	if ((status = getaddrinfo("nunki.usc.edu", "3768", &hints, &SUPInfo)) != 0)
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
	int len = strlen(u1l1);
	int bytes_sent = send(sockDescpUDP1, u1l1, len, 0);
	//send msg 2
	if ((status = getaddrinfo("nunki.usc.edu", "3768", &hints, &SUPInfo)) != 0)
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
	len = strlen(u1l2);
	bytes_sent = send(sockDescpUDP1, u1l2, len, 0);
	//listen to recieve
	
	}//end of if(myid==0)

	if(myid==1){
		//udp sock = 3300 + 668 = 3968
		struct addrinfo *UDPsend1;
		int sockc1UDPDescprecv;
		memset(&hints, 0, sizeof hints);
		hints.ai_family = AF_INET;//IPv4
		hints.ai_socktype = SOCK_DGRAM;//UDP
		//hints.ai_flags = AI_PASSIVE;//fill in IP

		if ((status = getaddrinfo("localhost", "3968", &hints, &UDPsend1)) != 0)
		{
			cout<<"getaddrinfo failure\n";
			exit(0);
		}

		if ((sockc1UDPDescprecv = socket(UDPsend1->ai_family, UDPsend1->ai_socktype, UDPsend1->ai_protocol)) == -1)
		{
			cout<<"Socket Error\n";
			exit(0);
		}

		char yes='1'; // Solaris people use this
		// lose the pesky "Address already in use" error message
		if (setsockopt(sockc1UDPDescprecv,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
		perror("setsockopt");
		exit(1);
		}
		
		if ((bind(sockc1UDPDescprecv, UDPsend1->ai_addr, UDPsend1->ai_addrlen)) == -1)
		{
			cout<<"bind error in 2\n";
			perror("Error occured:");
			exit(0);
		}
		i=0;
		cout<<"socket made sleeping before recv"<<endl;
		sleep(10);
		while(i<2)
		{
			int num;
			if ((num = recv(sockc1UDPDescprecv, buf, sizeof(buf), 0) == -1))
			{
				cout<<"recv error\n";
			}
			i++;
			cout<<buf<<endl;
			char *dispmsg;
			dispmsg = strtok(buf,"-");
			dispmsg = strtok(NULL,"-");
			cout<<dispmsg<<endl;
		}
	cout<<"socket made sleeping before sending"<<endl;
 	sleep(10);
	
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;//IPv4
	hints.ai_socktype = SOCK_DGRAM;//TCP
	//hints.ai_flags = AI_PASSIVE;//fill in IP
	struct addrinfo *SUPInfo;
	int sockDescpUDP1;
	//cout<<"start"<<endl;
	if ((status = getaddrinfo("nunki.usc.edu", "3768", &hints, &SUPInfo)) != 0)
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
	int len = strlen(u2l1);
	int bytes_sent = send(sockDescpUDP1, u2l1, len, 0);
	//send msg 2
	if ((status = getaddrinfo("nunki.usc.edu", "3768", &hints, &SUPInfo)) != 0)
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
	len = strlen(u2l2);
	bytes_sent = send(sockDescpUDP1, u2l2, len, 0);
	}
	
	if(myid==2){
		//udp sock = 3400 + 668 = 4068
		struct addrinfo *UDPsend2;
		int sockc1UDPDescprecv2;
		memset(&hints, 0, sizeof hints);
		hints.ai_family = AF_INET;//IPv4
		hints.ai_socktype = SOCK_DGRAM;//UDP
		//hints.ai_flags = AI_PASSIVE;//fill in IP

		if ((status = getaddrinfo("localhost", "4068", &hints, &UDPsend2)) != 0)
		{
			cout<<"getaddrinfo failure\n";
			exit(0);
		}

		if ((sockc1UDPDescprecv2 = socket(UDPsend2->ai_family, UDPsend2->ai_socktype, UDPsend2->ai_protocol)) == -1)
		{
			cout<<"Socket Error\n";
			exit(0);
		}

		if ((bind(sockc1UDPDescprecv2, UDPsend2->ai_addr, UDPsend2->ai_addrlen)) == -1)
		{
			cout<<"bind error in 3\n";
			perror("Error occured:");
			exit(0);
		}
		while(i<2)
		{
			int num;
			if ((num = recv(sockc1UDPDescprecv2, buf, sizeof(buf), 0) == -1))
			{
				cout<<"recv error\n";
			}
			i++;
			char *dispmsg;
			dispmsg = strtok(buf,"-");
			dispmsg = strtok(NULL,"-");
			cout<<dispmsg<<endl;
		}
			cout<<"socket made sleeping before sending"<<endl;
 	sleep(10);
	
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;//IPv4
	hints.ai_socktype = SOCK_DGRAM;//TCP
	//hints.ai_flags = AI_PASSIVE;//fill in IP
	struct addrinfo *SUPInfo;
	int sockDescpUDP1;
	//cout<<"start"<<endl;
	if ((status = getaddrinfo("nunki.usc.edu", "3768", &hints, &SUPInfo)) != 0)
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
	int len = strlen(u3l1);
	int bytes_sent = send(sockDescpUDP1, u3l1, len, 0);
	//send msg 2
	if ((status = getaddrinfo("nunki.usc.edu", "3768", &hints, &SUPInfo)) != 0)
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
	len = strlen(u3l2);
	bytes_sent = send(sockDescpUDP1, u3l2, len, 0);
	}
	
}


int main(int id)
{
	myid = 0;
	int v = fork();
	if(v == 0)
	myid=1;
	if (myid!=1)
	{
		int q = fork();
		if (q==0)
		myid =2;
	}
	//cout<<myid<<endl;

	if(myid ==0)
	readUserFile0();
	readUserText0();

	if(myid ==1)
	readUserFile1();
	readUserText1();

	if(myid ==2)
	readUserFile2();
	readUserText2();

	makeloginMessage();
	setupTCP();
	return 0;
}