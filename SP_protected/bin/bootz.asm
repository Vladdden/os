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
call readProgram
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
	mov ax, 0x0203
	mov dx, 0x0080
	mov cx, 0x0002
	mov bx, 0x8004;8000-����� ����������� (��������� ����� _start())
	int 0x13
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
MyData equ Data_d-gd_table
buf dd 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 ;104 �����
a db 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0