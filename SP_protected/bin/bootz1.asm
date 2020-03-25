org 0x7C00
mov ax, ds
mov dx, 0xb000
mov ds, dx
mov cx, 0
mov di, cx
mov cl, 35
mov bx, a
while:
mov ch, [bx]
mov [ds:di], ch
inc bx
inc di
dec cl
jnz while
mov ds, ax
mov bx, 0
mov dx, 0
mov di, 0
mov cx, 0
mov ax, 0
call loader
cli
mov ax,0
mov ss,ax
mov ds,ax
mov fs,ax
mov gs,ax
mov es,ax
mov sp,0xfffc
lgdt[globalTable]
mov eax,cr0
or eax,1
mov cr0,eax
jmp MyCode:0x8000
ret

loader:
mov ah,2
mov al,3
mov dh,0
mov dl,0X80
mov bx,0X8000
mov ch,0
mov cl,2
int 0x13
ret



dTableStart:
null_d:
dd 0
dd 0
code_d:
dw 0xffff
dw 0
db 0
db 0b10011010
db 0b11001111
db 0
data_d:
dw 0xffff
dw 0
db 0
db 0b10010010
db 0
dTableEnd:
globalTable:
dw dTableEnd-dTableStart
dd dTableStart
MyCode equ code_d-dTableStart
MyData equ data_d-dTableStart

a db 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0