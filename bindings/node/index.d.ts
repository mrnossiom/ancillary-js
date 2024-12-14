declare module "ancillary" {
  function version(): string;

  function sendFd(socket_fd: number, fd: number): number;
  function recvFd(socket_fd: number, fd: number): number;
}
