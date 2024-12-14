import { dlopen, FFIType } from "bun:ffi";
import { Socket } from "node:net";

const libPath = "../../build/libancillary.so";

const {
  symbols: {
    ancillary_version,
    ancillary_send_fd,
  },
} = dlopen(
  libPath,
  {
    ancillary_version: { args: [], returns: FFIType.cstring },
    ancillary_send_fd: {
      args: [FFIType.i32, FFIType.i32],
      returns: FFIType.i32,
    },
  },
);

function version(): string {
  return ancillary_version().toString();
}

function sendFd(socket_fd: number, fd: number) {
  const result = ancillary_send_fd(socket_fd, fd);
  if (result < 0) throw new Error(`got errno error from ancillary_send_fd: ${-result}`);
}

// ---

console.log(`> using ${version()}`);

const socketPath = "/tmp/wayplain-0";
const socket = new Socket();
socket.connect(socketPath);

// there is no way to access the file descriptor as of now

const HIGHLY_UNSTABLE_SOCKET_FD = 13;
const STDOUT_FD = 1;

sendFd(HIGHLY_UNSTABLE_SOCKET_FD, STDOUT_FD);
