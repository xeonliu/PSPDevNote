# PSPDEV Directory Structure
```
pspdev
├── bin
├── etc
├── include
├── lib
├── libexec
├── psp
├── share
└── var
```

## `bin`
```
bin
├── PrxEncrypter
├── bin2c
├── bin2o
├── bin2s
├── ebootsign
├── mksfo
├── mksfoex
├── pack-pbp
├── psp-addr2line
├── psp-ar
├── psp-as
├── psp-build-exports
├── psp-c++
├── psp-c++filt
├── psp-cmake
├── psp-config
├── psp-cpp
├── psp-elfedit
├── psp-fixup-imports
├── psp-g++
├── psp-gcc
├── psp-gcc-11.2.0
├── psp-gcc-ar
├── psp-gcc-nm
├── psp-gcc-ranlib
├── psp-gcov
├── psp-gcov-dump
├── psp-gcov-tool
├── psp-gdb
├── psp-gdb-add-index
├── psp-ld
├── psp-ld.bfd
├── psp-lto-dump
├── psp-makepkg
├── psp-nm
├── psp-objcopy
├── psp-objdump
├── psp-pacman
├── psp-pkg-config
├── psp-pkgconf -> psp-pkg-config
├── psp-prxgen
├── psp-ranlib
├── psp-readelf
├── psp-run
├── psp-size
├── psp-strings
├── psp-strip
├── pspsh
├── unpack-pbp
└── usbhostfs_pc
```
这个目录下储存着PSPDev中所有编译好后可供运行的二进制可执行文件。可以看到其中许多都属于GNU的编译套件。