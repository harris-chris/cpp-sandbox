#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>

using std::cout;

int main(int argc, char const *argv[])
{
  int sock = 0;
  char serverPort[] = "12000";

  struct sockaddr rec_addr;
  struct addrinfo hints, *res;
  char rec_msg[1024] = "";

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = AI_PASSIVE;

  getaddrinfo(NULL, serverPort, &hints, &res);

  if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    cout << "Unable to create socket";
    return -1;
  }

  cout << "AI_ADDR" << res->ai_addr;
  bind(sock, res->ai_addr, res->ai_addrlen);

  while(true)
  {
    if(recvfrom(sock, rec_msg, strlen(rec_msg), 0, &rec_addr, (socklen_t*) sizeof(rec_addr)) < 0)
    {
      cout << "Problem receiving message";
      return -1;
    }
    for(auto &c: rec_msg) c = toupper(c);
    cout << "Converted to " << rec_msg;
    if(sendto(sock, rec_msg, strlen(rec_msg), 0, &rec_addr, sizeof(*rec_msg)) < 0)
    {
      cout << "Failed to respond with" << rec_msg;
      return -1;
    }
  }
}


