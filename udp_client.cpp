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

  const char *send_message = argv[1];
  char receive_message[1024] = "";

  if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    cout << "Socket creation error";
    return -1;
  }

  struct sockaddr_in dest; 
  dest.sin_family = AF_INET;
  dest.sin_port = htons(serverPort);
  memset(&dest.sin_zero, 0, sizeof dest.sin_zero);
  inet_pton(AF_INET, "127.0.0.1", &dest.sin_addr);

  cout << "Sending send_message " << send_message << "\n";
  
  if(sendto(sock, send_message, strlen(send_message), 0, (struct sockaddr *) &dest, sizeof(dest)) < 0) 
  {
    cout << "Failed to send message";
  }

  cout << "send_message sent" << std::endl;

  sockaddr *dest_addr = (sockaddr *) &dest;
  socklen_t dest_size = sizeof(*dest_addr);
  recvfrom(sock, &receive_message, sizeof(receive_message), 0, dest_addr, &dest_size);
  cout << "Received back " << receive_message << std::endl;
}

