declare module "ancillaire" {
  function version(): string;

  function sendFd(socket_fd: number, fd: number): number;
  function recvFd(socket_fd: number): Promise<number>;
}
