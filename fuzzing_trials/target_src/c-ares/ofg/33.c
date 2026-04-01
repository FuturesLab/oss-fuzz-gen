#include <ares.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
  ares_channel channel;
  int status = ares_init(&channel);
  if (status != ARES_SUCCESS) {
    return 0;
  }

  /* Create a pair of connected sockets */
  int fd[2];
  if (socketpair(AF_UNIX, SOCK_STREAM, 0, fd) != 0) {
    ares_destroy(channel);
    return 0;
  }

  /* Write data to the socket to simulate activity */
  write(fd[1], data, size);

  /* Call the function-under-test */
  ares_process_fd(channel, fd[0], fd[1]);

  /* Clean up */
  close(fd[0]);
  close(fd[1]);
  ares_destroy(channel);

  return 0;
}