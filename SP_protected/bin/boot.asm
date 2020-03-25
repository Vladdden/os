org 0x7c00;32 разр€дный защищенный режим работы

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
cli;отключение возможных прерывание clear interupt - нажатие клавиши в момент запуска режима и тд.
mov sp, 0xfffc;выделили 4 байта пам€ти в стеке, стек 16-битный
mov ax, 0
call segnull
lgdt[gdt];считывание таблицы - копироване с десрипторную таблицу
;переход в защищенный режим. cr0-системный регистр
mov eax, cr0
or eax, 1; выбор режима работы
mov cr0, eax
mov eax, [buf+0x28];получаем адрес фреймбуфера
mov dword[0x8000],eax
jmp MyCode : 0x8004
ret

readProgram:
    mov ax, 0x0280
    mov dx, 0x0080
    mov cx, 0x0002
    mov bx, 0x8004;8000-адрес фреймбуфера (находитс€ перед _start())
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
    ;mov bx, 0xB3B6;8000-адрес фреймбуфера (находитс€ перед _start())
	mov bx, [movbx]; -0x0400
	int 0x13
	mov dx,es
	sub dx,[adddx] ; +0x1000
	mov es,dx
    ret


segnull:;ќбнуление сегментных регистров
    mov ss, ax
    mov ds, ax
    mov fs, ax
    mov es, ax
    mov gs, ax
    ret

setVESAMode:;VESA стандарты телеобработки и тд; переключение в продвинутый видеорежим
    mov ax, 0x4f01;4f - что-то делать с видоадаптером, 01-получить информацию: вз€ть из видеоадаптера информацию, соотв граф разрешени€
    mov cx, 0x118 ;1024x768
    mov di, buf
    int 0x10
    mov ax, 0x4f02;переключение видеорежима
    mov bx, 0x4118;переключение видеорежима
    int 0x10
    ret

gd_table:
    Null_d:
        Dd 0
        Dd 0
    Code_d:
        Dw 0xffff;предел пам€ти, в которую может расшир€тьс€
        Dw 0;младша€ часть базового адреса
        Db 0;адрес
        Db 0b10011010; флаги -> p ->dpl(2 бита) -> s -> e -> ed/c -> r/w -> a
            ;p определ€ет что сегмент содержит верные код и данные -> сегмент заполнен
            ;dpl - содержит уровень привилегий, присваемый сегменту
            ;s - системный дескриптор или дескриптор программы
            ;e - определ€ет тип дескриптора (содержит данные или исполн€емый код(1))
            ;ed/c - будет ли происходить расширение сегмента к области данных или к области стека(1)
            ;r/w - чтение/запись
            ;a - был ли доступ к дескриптору
            ;ƒескриптор, описывающий свою область кода, содержит правило работы с этим кодом
        Db 0b11001111;гранул€рность (размер страницы, которые описываютс€ дискриптором)
        Db 0;адрес, по€вилось позже
    Data_d:
        Dw 0xffff;65000 кб
        Dw 0
        Db 0
        Db 0b10010010
        Db 0b11001111;гранул€рность (размер страницы, которые описываютс€ дискриптором)
    gd_table_end:
    gdt:
        Dw gd_table_end-gd_table;размер таблицы
        Dd gd_table
MyCode equ Code_d-gd_table;присвоение (эквивалент)
;MyData equ Data_d-gd_table
buf dd 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 ;104 байта