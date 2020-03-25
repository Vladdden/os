org 0x7c00;32 ��������� ���������� ����� ������

call readProgram
bigwhile:
mov word[adddx], 0x1000
mov word[movdx], 0x0280
mov word[movbx],0x7c01
mov word[counter],8
while:
call readMore
add word[adddx], 0x1000
add word[movdx], 0x0200
sub word[movbx], 0x0400
dec word[counter]
jnz while
add word[movcx], 0x0100
inc word[movdx]
dec word[alcounter]
jnz bigwhile

bigwhile2:
mov word[movdx], 0x0280
mov word[movbx],0x7c01
mov word[counter],5
mov word[alcounter], 1
while2:
call readMore
add word[adddx], 0x1000
add word[movdx], 0x0200
sub word[movbx], 0x0400
dec word[counter]
jnz while2
add word[movcx], 0x0100
inc word[movdx]
dec word[alcounter]
jnz bigwhile2
call setVESAMode
cli;���������� ��������� ���������� clear interupt - ������� ������� � ������ ������� ������ � ��.
mov sp, 0xfffc;�������� 4 ����� ������ � �����, ���� 16-������
mov ax, 0
call segnull
lgdt[gdt];���������� ������� - ���������� � ������������ �������
;������� � ���������� �����. cr0-��������� �������
mov eax, cr0
or eax, 1; ����� ������ ������
mov cr0, eax
mov eax, [buf+0x28];�������� ����� �����������
mov dword[0x8000],eax
jmp MyCode : 0x8004
ret

readProgram:
    mov ax, 0x0280
    mov dx, 0x0080
    mov cx, 0x0002
    mov bx, 0x8004;8000-����� ����������� (��������� ����� _start())
    int 0x13
    ret

adddx dw 0x1000
movdx dw 0x0280
movbx dw 0x7c01
counter dw 8
alcounter dw 1
axint dw 0x0280
movcx dw 0x0002

readMore:
	mov dx,es
	add dx, [adddx]; +0x1000
	mov es, dx
    mov ax, [axint]
    mov dx, [movdx]; +0x0200
    mov cx, [movcx]
    ;mov bx, 0xB3B6;8000-����� ����������� (��������� ����� _start())
	mov bx, [movbx]; -0x0400
	int 0x13
	mov dx,es
	sub dx,[adddx] ; +0x1000
	mov es,dx
    ret


segnull:;��������� ���������� ���������
    mov ss, ax
    mov ds, ax
    mov fs, ax
    mov es, ax
    mov gs, ax
    ret

setVESAMode:;VESA ��������� ������������� � ��; ������������ � ����������� ����������
    mov ax, 0x4f01;4f - ���-�� ������ � �������������, 01-�������� ����������: ����� �� ������������� ����������, ����� ���� ����������
    mov cx, 0x118 ;1024x768
    mov di, buf
    int 0x10
    mov ax, 0x4f02;������������ �����������
    mov bx, 0x4118;������������ �����������
    int 0x10
    ret

gd_table:
    Null_d:
        Dd 0
        Dd 0
    Code_d:
        Dw 0xffff;������ ������, � ������� ����� �����������
        Dw 0;������� ����� �������� ������
        Db 0;�����
        Db 0b10011010; ����� -> p ->dpl(2 ����) -> s -> e -> ed/c -> r/w -> a
            ;p ���������� ��� ������� �������� ������ ��� � ������ -> ������� ��������
            ;dpl - �������� ������� ����������, ���������� ��������
            ;s - ��������� ���������� ��� ���������� ���������
            ;e - ���������� ��� ����������� (�������� ������ ��� ����������� ���(1))
            ;ed/c - ����� �� ����������� ���������� �������� � ������� ������ ��� � ������� �����(1)
            ;r/w - ������/������
            ;a - ��� �� ������ � �����������
            ;����������, ����������� ���� ������� ����, �������� ������� ������ � ���� �����
        Db 0b11001111;������������� (������ ��������, ������� ����������� ������������)
        Db 0;�����, ��������� �����
    Data_d:
        Dw 0xffff;65000 ��
        Dw 0
        Db 0
        Db 0b10010010
        Db 0b11001111;������������� (������ ��������, ������� ����������� ������������)
    gd_table_end:
    gdt:
        Dw gd_table_end-gd_table;������ �������
        Dd gd_table
MyCode equ Code_d-gd_table;���������� (����������)
;MyData equ Data_d-gd_table
buf dd 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 ;104 �����