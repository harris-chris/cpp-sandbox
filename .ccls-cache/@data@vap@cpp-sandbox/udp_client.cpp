#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>

using std::cout;

int main (int argc, char const *argv[]) 
{
  int sock = 0;
  char serverName[] = "localhost";
  int serverPort = 12000;
  if(argc != 2)
  {
    cout << "Please supply at least one argument";
    return -1;
  }

  const char *message = argv[1];

  if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    cout << "Socket creation error";
    return -1;
  }

  struct sockaddr_in dest; 
  dest.sin_family = AF_INET;
  dest.sin_port = htons(serverPort);
  inet_pton(AF_INET, "127.0.0.1", &dest.sin_addr);
  
  if(sendto(sock, message, strlen(message), 0, (struct sockaddr *) &dest, sizeof(dest)) < 0) 
  {
    cout << "Failed to send message";
  }
}


