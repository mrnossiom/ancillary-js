#ifndef ANCILLARY_H
#define ANCILLARY_H

// Get the current ancillary version with a string
char *ancillary_version(void);

// Send a file descriptor to another process through a UNIX domain socket
// using ancillary data.
// 
// Returns a negative number in case something went wrong.
int ancillary_send_fd(int socket_fd, int fd);

#endif /* ! ANCILLARY_H */
