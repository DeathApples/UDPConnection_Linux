#include <netinet/in.h> // struct sockaddr_in
#include <arpa/inet.h> // inet_addr()
#include <strings.h> // bzero()
#include <unistd.h> // close()

#include <iostream>
#include <fstream>


#define DEST_PORT   52000
#define MAX_LINE    1024
#define MAX_CHAR    250
#define IP_ADDRESS  "127.0.0.1"


char data[MAX_LINE];
char path[MAX_CHAR];
std::fstream fstream;
struct sockaddr_in interlocutor;


int main()
{    
    // initialize interlocutor
    bzero(&interlocutor, sizeof(interlocutor));
    interlocutor.sin_addr.s_addr = INADDR_ANY;
    interlocutor.sin_port = htons(DEST_PORT);
    interlocutor.sin_family = AF_INET;

    // create datagram socket
    int sockd = socket(AF_INET, SOCK_DGRAM, 0);
    
    // connect to interlocutor
	if(connect(sockd, (struct sockaddr *)&interlocutor, sizeof(interlocutor)) < 0)
	{
		printf("\nError : Connect Failed \n");
		exit(0);
	}

    printf("Введите путь к файлу >> ");
    std::cin.getline(path, MAX_CHAR);

    fstream.open(path, std::fstream::binary | std::fstream::in);

    if (!fstream.is_open()) 
    {
        printf("\nError : Open File Failed \n");
		exit(0);
    }

    while (!fstream.eof()) 
    {
        fstream.read(data, MAX_LINE);
        sendto(sockd, (void *)data, MAX_LINE, 0, (struct sockaddr*)NULL, (int)NULL);
    }

    fstream.close();
    close(sockd);

    return 0;
}
