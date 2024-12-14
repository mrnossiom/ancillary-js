#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <unistd.h>

#include "ancillary.h"

char *ancillary_version(void) { return "libancillary v0.0.0"; }

int ancillary_send_fd(int socket_fd, int fd) {
  // message needs dummy data
  int data = 0xDEADBEEF;
  struct iovec iov = {
      .iov_base = &data,
      .iov_len = sizeof(data),
  };

  // correctly align message
  union {
    char buf[CMSG_SPACE(sizeof(int))];
    struct cmsghdr align;
  } control_msg;

  struct msghdr msgh = {
      // no need for a name for ipc
      .msg_name = NULL,
      .msg_namelen = 0,

      .msg_iov = &iov,
      .msg_iovlen = 1,

      .msg_control = control_msg.buf,
      .msg_controllen = sizeof(control_msg.buf),
  };

  // build control message to pass through ancillary data
  // contains a fd
  struct cmsghdr *cmsgp;
  cmsgp = CMSG_FIRSTHDR(&msgh);
  cmsgp->cmsg_level = SOL_SOCKET;
  cmsgp->cmsg_type = SCM_RIGHTS;
  cmsgp->cmsg_len = CMSG_LEN(sizeof(int));
  memcpy(CMSG_DATA(cmsgp), &fd, sizeof(int));

  if (sendmsg(socket_fd, &msgh, 0) == -1)
    return -1;

  return 0;
}
