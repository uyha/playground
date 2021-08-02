#include <cstdio>
#include <cstring>
#include <errno.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

int main(int argc, char const **argv) {
  auto const can_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW);
  std::printf("SocketCAN: %d\n", can_socket);
  if (can_socket == -1) {
    return -1;
  }
  ifreq can_ifreq{};
  std::strcpy(can_ifreq.ifr_name, argv[1]);
  if (auto const status = ioctl(can_socket, SIOGIFINDEX, &can_ifreq);
      status == -1) {
    perror(strerror(errno));
    return errno;
  }
  std::printf("Index: %d\n", can_ifreq.ifr_ifindex);
}
