const libPath = `build/libancillary.so`;

const {
  symbols: {
    ancillary_version,
    ancillary_send_fd,
  }
} = Deno.dlopen(
  libPath,
  {
    ancillary_version: { parameters: [], result: "pointer" },
    ancillary_send_fd: { parameters: ["i32", "i32"], result: "i32" },
  } as const,
);

const version_ptr = ancillary_version();
const version = Deno.UnsafePointerView.getCString(version_ptr);

console.log(`libancillary version: ${version}`);

