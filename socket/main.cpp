#include <arpa/inet.h>
#include <cstring>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>

int main(int argc, char const **argv) {
  addrinfo hints{.ai_family = AF_UNSPEC, .ai_socktype = SOCK_STREAM};
  addrinfo *servinfo;

  if (auto const status = getaddrinfo(argv[1], nullptr, &hints, &servinfo);
      status != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
    return 2;
  }

  printf("IP addresses for %s:\n\n", argv[1]);

  char ipstr[INET6_ADDRSTRLEN];
  void *addr;
  char const *ipver;
  for (auto *p = servinfo; p != nullptr; p = p->ai_next) {
    if (p->ai_family == AF_INET) {
      addr = &((struct sockaddr_in *)p->ai_addr)->sin_addr;
      ipver = "IPV4";
    } else {
      addr = &((struct sockaddr_in6 *)p->ai_addr)->sin6_addr;
      ipver = "IPV6";
    }
    inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
    printf("  %s: %s\n", ipver, ipstr);
  }
  freeaddrinfo(servinfo);
}
