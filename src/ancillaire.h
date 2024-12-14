#ifndef ANCILLAIRE_H
#define ANCILLAIRE_H

// Get the current ancillary version with a string
char *ancillaire_version(void);

// TODO: see unix(7) for all ancillary message types

// Send a file descriptor to another process through a UNIX domain socket
// using an ancillary message.
// 
// Implements `SCM_RIGHTS` ancillary message type.
// 
// Returns a negative number in case something went wrong.
int ancillaire_send_fd(int socket_fd, int fd);

// TODO
// 
// Implements `SCM_RIGHTS` ancillary message type.
// 
// Returns a negative number in case something went wrong.
int ancillaire_recv_fd(int socket_fd);

#endif /* ! ANCILLAIRE_H */
