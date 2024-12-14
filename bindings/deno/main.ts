const libPath = "../../build/libancillary.so";

const {
  symbols: {
    ancillary_version,
    ancillary_send_fd,
  },
} = Deno.dlopen(
  libPath,
  {
    ancillary_version: {
      parameters: [],
      result: "pointer",
    },
    ancillary_send_fd: { parameters: ["i32", "i32"], result: "i32" },
  } as const,
);

function version(): string {
  const versionPtr = ancillary_version();
  if (versionPtr == null) throw new Error("got null pointer from ancillary_version");
  return new Deno.UnsafePointerView(versionPtr).getCString();
}

function sendFd(socket_fd: number, fd: number) {
  const result = ancillary_send_fd(socket_fd, fd);
  if (result < 0) throw new Error(`got errno error from ancillary_send_fd: ${-result}`);
}

// ---

console.log(`> using ${version()}`);

const socketPath = "/tmp/wayplain-0";
const listener = await Deno.connect({ path: socketPath, transport: "unix" })

// there is no way to access the file descriptor as of now

const HIGHLY_UNSTABLE_SOCKET_FD = 21;
const STDOUT_FD = 1;

ancillary_send_fd(HIGHLY_UNSTABLE_SOCKET_FD, STDOUT_FD);
