{
  "targets": [
    {
      "target_name": "libancillaire",
      "sources": [
        "csource/node.cpp",
        "csource/ancillaire.c"
      ],
      'include_dirs': [
        "<!@(node -p \"require('node-addon-api').include\")",
        "<!(pkg-config --cflags-only-I wayland-server | sed 's/-I//g')"
      ],
      'dependencies': ["<!(node -p \"require('node-addon-api').gyp\")"],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ]
    }
  ]
}
