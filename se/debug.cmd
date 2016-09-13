#!/bin/sh
set PATH=%PATH%;C:\Maxim\Toolchain\msys\1.0\bin
start C:\Maxim\Toolchain\bin\openocd.exe -s C:\Maxim\Toolchain\share\openocd\scripts -f interface/ftdi/olimex-arm-usb-tiny-h.cfg -f target/MAX3263x.cfg -c init -c "reset init" -c "flash erase_sector 0 0 255"
