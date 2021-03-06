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
  int status = 0;
  char error_str[256] = "";
  char serverPort[] = "12000";

  struct sockaddr rec_addr;
  struct addrinfo hints, *res;
  char rec_msg[1024] = "";

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = AI_PASSIVE;

  cout << "Starting";

  getaddrinfo(NULL, serverPort, &hints, &res);

  if((sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0)
  {
    cout << "Unable to create socket";
    return -1;
  }

  bind(sock, res->ai_addr, res->ai_addrlen);

  cout << "Awaiting message\n"; 
  cout << std::endl;

  while(true)
  {
    socklen_t addr_len = sizeof(rec_addr);
    int rec_msg_size = sizeof(rec_msg);
    cout << rec_msg_size << std::endl;
    if((status = recvfrom(sock, &rec_msg, rec_msg_size, 0, &rec_addr, &addr_len)) < 0)
    {
      cout << "Problem receiving message, exited with " << status;
      char *errorMsg = strerror_r( errno, error_str, 256 );
      cout << errorMsg;
      return -1;
    }
    cout << "Received message " << rec_msg << std::endl;
    for(auto &c: rec_msg) c = toupper(c);
    cout << "Converted to " << rec_msg << " with length " << strlen(rec_msg) << std::endl;
    if((status = sendto(sock, &rec_msg, strlen(rec_msg), 0, &rec_addr, addr_len)) < 0)
    {
      cout << "Failed to respond with " << rec_msg << std::endl;
      char *errorMsg = strerror_r( errno, error_str, 256 );
      cout << errorMsg << std::endl;
      return -1;
    }
    cout << "Successfully responded with " << status << " bytes" << std::endl;
  }

  cout << "Finishing";
}


