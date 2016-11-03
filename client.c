#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];

printf("\n\t********Simple Client-Server Chat Application!********\n");

    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");


while(1)
{
printf("\nClient : ");
fgets(buffer,256,stdin);
if(strncmp(buffer,"exit",4)==0)//Use "end" to end communication with server
break;
n=send(sockfd,buffer,256,0);

if(n == -1)
{
printf("Error in sending");
exit(1);
}
n=recv(sockfd,buffer,256,0);
if(n == -1)
{
printf("Error in receiving");
exit(1);
}
printf("\t\t\t\t\tServer : %s",buffer);
}

    close(sockfd);
    return 0;
}
