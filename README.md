# Ancillary messages JS bindings

<p align="center"><strong>
JavaScript bindings to UNIX domain sockets ancillary messages
</strong></p>

<p align="center">
  <img alt="Nix Powered" src="https://img.shields.io/badge/Nix-Powered-blue?logo=nixos" />
  <a href="https://wakatime.com/badge/github/mrnossiom/ancillary-js">
    <img alt="Time spent" src="https://wakatime.com/badge/github/mrnossiom/ancillary-js.svg" />
  </a>
</p>

# Usage

You can check the current library interface in `src/ancillary.h`

Both `bun` and `deno` are supported because they can open a shared library (`.so`). 

# Building

## Tools

Check the `nativeBuildInputs` of the `flake.nix` file to get the up-to-date required tools.

They include
- `just`
- a C compiler (`clang`, `gcc`)
- your prefered supported JS runtime (`bun`, `deno`)

## Building

```sh
# Build the libancillary bindings to `build/libancillary.so`.
just buildc
```

You can then use `bun`/`deno` ffi features to open and access the shared library.
