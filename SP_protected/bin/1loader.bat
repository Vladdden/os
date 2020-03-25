gcc font.c
a.exe
nasm -f bin boot.asm -o boot.bin
gcc -nostdlib -m32 -masm=intel mainboot.c
objcopy -O binary a.exe
python pyt.py
copy disk.img qemu
cd qemu
qemu-system-i386 disk.img
pause
