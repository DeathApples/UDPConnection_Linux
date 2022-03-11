#include <netinet/in.h> // struct sockaddr_in
#include <arpa/inet.h> // inet_addr()
#include <strings.h> // bzero()
#include <unistd.h> // close()

#include <iostream>
#include <fstream>


#define SOUR_PORT   52000
#define MAX_LINE    1024
#define MAX_CHAR    250
#define IP_ADDRESS  "127.0.0.1"


int n;
char data[MAX_LINE];
char path[MAX_CHAR];
std::fstream fstream;
struct sockaddr_in interlocutor;


int main()
{
    // initialize interlocutor
    bzero(&interlocutor, sizeof(interlocutor));
    interlocutor.sin_addr.s_addr = INADDR_ANY;
    interlocutor.sin_port = htons(SOUR_PORT);
    interlocutor.sin_family = AF_INET;

    // create datagram socket
    int sockd = socket(AF_INET, SOCK_DGRAM, 0);

    // listen on a port
	if(bind(sockd, (struct sockaddr *)&interlocutor, sizeof(interlocutor)) < 0)
	{
		printf("\nError : Connect Failed \n");
		exit(0);
	}

    // Open or Create file in binary mod
    fstream.open("Image.png", std::fstream::binary | std::fstream::out);

    if(!fstream.is_open()) 
    {
        printf("\nError : Open File Failed \n");
		exit(0);
    }

    //receive message from interlocutor
    while((n = recvfrom(sockd, data, MAX_LINE, 0, (struct sockaddr*)NULL, NULL)) > 0)
    {
        fstream.write(data, n);
    }

    fstream.close();
    close(sockd);

    return 0;
}
