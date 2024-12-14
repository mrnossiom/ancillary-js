let libSuffix = "";
switch (Deno.build.os) {
  case "windows":
    libSuffix = "dll";
    break;
  case "darwin":
    libSuffix = "dylib";
    break;
  default:
    libSuffix = "so";
    break;
}

const libPath = `build/libancillary.${libSuffix}`;

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

