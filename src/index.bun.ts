import { dlopen, FFIType } from "bun:ffi";

const path = `build/libancillary.so`;

const {
  symbols: {
    ancillary_version,
    ancillary_send_fd,
  },
} = dlopen(
  path,
  {
    ancillary_version: { args: [], returns: FFIType.cstring },
    ancillary_send_fd: {
      args: [FFIType.i32, FFIType.i32],
      returns: FFIType.i32,
    },
  },
);

console.log(`libancillary version: ${ancillary_version()}`);
