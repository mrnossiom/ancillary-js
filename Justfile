# Just is not a build system but works fine for our usecase

_default:
	@just --list --unsorted --list-heading '' --list-prefix '—— '

cc := "clang"
cflags := "-Wall -Wextra -Wvla -pedantic"
cdebug_flags := "-g -fsanitize=address"

buildc:
    mkdir -p build
    {{cc}} -c {{cflags}} -o build/libancillary.o src/ancillary.c
    {{cc}} -shared -o build/libancillary.so build/libancillary.o

clean:
	rm -rd build
