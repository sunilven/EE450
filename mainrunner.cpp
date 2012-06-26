/*actual main*/

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
#include "login.h"



int main()
{
	int s;
   struct sockaddr sa;
   int sa_len;
   sa_len = sizeof(sa);
   if (getsockname(s, &sa, &sa_len) == -1) {
      perror("getsockname() failed");
      return -1;
   }
   
   printf("Local IP address is: %s\n", inet_ntoa(sa.sin_addr));
   printf("Local port is: %d\n", (int) ntohs(sa.sin_port));
	return -1;
}
	