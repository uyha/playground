#include <fmt/core.h>
#include <mqueue.h>
#include <sys/epoll.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  auto const mq_name  = "/sandbox.ftruncate.mq";
  auto const shm_name = "/sandbox.ftruncate.shm";

  auto epoll = ::epoll_create1(0);
  auto mq    = ::mq_open(mq_name, O_RDONLY | O_CREAT, 0666, nullptr);
  auto shm   = ::shm_open(shm_name, O_RDWR | O_CREAT, 0666);

  fmt::print("{} ", ftruncate(epoll, 0));
  fmt::print("{}\n", errno);
  fmt::print("{} ", ftruncate(mq, 0));
  fmt::print("{}\n", errno);
  fmt::print("{} ", ftruncate(shm, 100));
  fmt::print("{}\n", errno);

  ::mq_unlink(mq_name);
  ::shm_unlink(shm_name);
  ::close(epoll);
}
