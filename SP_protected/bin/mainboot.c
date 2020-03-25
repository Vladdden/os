const int fontAdrs = 0x9000; //менять если изменять boot.asm // 0x9018, 0x8018
//const int imgAddress = 0x8000 + 0x2018 + 31 * 5 * 6;
const int fontCount = 40; //менять если изменять font.c
const int fontWidth = 5; //менять если изменять font.c
const int fontHeight = 6; //менять если изменять font.c
//const int pixelWidth = 7; //менять если хотите
//const int pixelHeight = 7; //менять если хотите
const int width = 1024; //ширина экрана
const int height = 768; //высота экрана

void setPixel(int, int, int);
void drawRam(int , int , int , int , int , int);
void drawRect(int, int, int, int, int);
void wait(int);
void drawChar(char, int, int, int, int);
void readkey(char *);
void Resetkb();
void zachistka();
void pause(int);
void drawLine(int, int, int, int, int, int);
int paint();
void clearkey();
int change_size(int, char);
void change_form(int, int, int);
void clava();
void colors();
//void drawElipse(int,int,int,int,int);

int start()
{
	int i,j,x=120,y=10,val, flag = 1;
	int tree [9][9]={
		{0x000000,0x000000,0x000000,0x00ff00,0x00ff00,0x000000,0x000000,0x000000},
		{0x000000,0x000000,0x00ff00,0x00ff00,0x00ff00,0x00ff00,0x000000,0x000000},
		{0x000000,0x000000,0x00ff00,0x00ff00,0x00ff00,0x00ff00,0x000000,0x000000},
		{0x000000,0x00ff00,0x00ff00,0x00ff00,0x00ff00,0x00ff00,0x00ff00,0x000000},
		{0x00ff00,0x00ff00,0x00ff00,0x00ff00,0x00ff00,0x00ff00,0x00ff00,0x00ff00},
		{0x00ff00,0x00ff00,0x00ff00,0x8B4513,0x8B4513,0x00ff00,0x00ff00,0x00ff00},
		{0x000000,0x000000,0x000000,0x8B4513,0x8B4513,0x000000,0x000000,0x000000},
		{0x000000,0x000000,0x000000,0x8B4513,0x8B4513,0x000000,0x000000,0x000000}
	};
	int apple [9][9]={
		{0x000000,0x000000,0x000000,0x412000,0x000000,0x00ff00,0x00ff00,0x000000},
		{0x000000,0x000000,0x000000,0x412000,0x00ff00,0x00ff00,0x00ff00,0x000000},
		{0x000000,0x000000,0xff0000,0x412000,0x00ff00,0xff0000,0x000000,0x000000},
		{0x000000,0xff0000,0xff0000,0xff0000,0xff0000,0xff0000,0xff0000,0x000000},
		{0xff0000,0xff0000,0xff0000,0xff0000,0xff0000,0xff0000,0xff0000,0xff0000},
		{0xff0000,0xff0000,0xff0000,0xff0000,0xff0000,0xff0000,0xff0000,0xff0000},
		{0x000000,0xff0000,0xff0000,0xff0000,0xff0000,0xff0000,0xff0000,0x000000},
		{0x000000,0x000000,0xff0000,0xff0000,0xff0000,0xff0000,0x000000,0x000000},
	};
	for (val = 0; val<=5; val++){ //верхний ряд деревьев
		for (i = 0; i < 8; i++){
			for (j = 0; j < 8; j++){
				drawRect(x+j*16, y+i*16,16,16,tree[i][j]);
			}
		}
		x+=129;
	}
	drawLine(135, 135, 840, 140, 0x6B8E23, 41); //верхний грунт
	x=105;
	y=620;
	for (val = 0; val<=5; val++){ //нижний ряд деревьев
		for (i = 8; i > 0; i--){
			for (j = 8; j > 0; j--){
				drawRect(x+j*16, y+i*16,16,16,tree[8-i][8-j]);
			}
		}
		x+=129;
	}
	/*
	drawRect(135,180,5,5,0x6B8E23); // 1 квадратик
	drawRect(135,590,5,5,0x6B8E23); // 2 квадратик
	drawRect(875,180,5,5,0x6B8E23); // 3 квадратик
	drawRect(875,590,5,5,0x6B8E23); // 4 квадратик
	*/
	drawRam(135, 185, 875, 585, 0x5C2E00, 5); // внешняя рамка
	drawRam(225, 388, 785, 460, 0x6B8E23, 5);
	drawLine(135, 595, 840, 600, 0x6B8E23, 41); //нижний грунт

	drawChar('A', 320, 300, 0xffffff, 0);
	drawChar('P', 360, 300, 0xffffff, 0);
	drawChar('P', 400, 300, 0xffffff, 0);
	drawChar('L', 440, 300, 0xffffff, 0);
	drawChar('E', 480, 300, 0xffffff, 0);
	drawChar('O', 560, 300, 0xffffff, 0);
	drawChar('S', 600, 300, 0xffffff, 0);

	x = 235;
	y = 408;
	for (val = 0; val<=15; val++){ //480*32px
		for (i = 0; i < 8; i++){
			for (j = 0; j < 8; j++){
					drawRect(x+j*4, y+i*4,4,4,apple[i][j]);
			}
		}
		x+=34;
		pause(20);
	}
	pause(100);

	for (i = 0; i < 8; i++){
			for (j = 0; j < 8; j++){
					drawRect(650+j*8, 280+i*8,8,8,apple[i][j]);
			}
		}
	pause(100);
	flag = paint();
	if (flag != 0) while(1);
	paint();
	return 0;
}

int paint (){ //1024*768
	int size = 20, form = 1,x = 600,y = 400, color = 0x000000;
	char c;
zachistka();
drawRect(x, y, size, size, 0x000000);
drawRam (4,4,1016,760, 0x5C2E00, 5); //внешняя рамка
drawRect (9,9,1007,751, 0xffffff); // белое заполнение
drawRect (9,9,304,751, 0xDCE6F4); //рамка управления
drawLine (310,4,311,760, 0x5C2E00, 5);

drawChar('C', 10, 30, 0x000000, 0);
drawChar('O', 50, 30, 0x000000, 0);
drawChar('L', 90, 30, 0x000000, 0);
drawChar('O', 130, 30, 0x000000, 0);
drawChar('R', 170, 30, 0x000000, 0);
drawChar('S', 210, 30, 0x000000, 0);
drawChar(':', 240, 30, 0x000000, 0);

colors();
//////////////////////////////////////////////////////
//drawLine (9, 70, 310, 71, 0x000000, 2);
/*
drawRect(50, 122, 50, 50, 0xF1102C);
drawRect(130, 122, 50, 50, 0xFF7D28);
drawRect(210, 122, 50, 50, 0xFFD03B);

//drawLine (9, 140, 310, 141, 0x000000, 2);

drawRect(50, 192, 50, 50, 0x44B32B);
drawRect(130, 192, 50, 50, 0xffffff);
drawRect(210, 192, 50, 50, 0x5459C9);

//drawLine (9, 210, 310, 211, 0x000000, 2);

drawRect(50, 262, 50, 50, 0x8600C7);
drawRect(130, 262, 50, 50, 0xC400A6);
drawRect(210, 262, 50, 50, 0x000000);

*/
//drawLine (9, 280, 310, 281, 0x000000, 2);
//drawLine (9, 350, 310, 351, 0x000000, 2);

	drawChar('S', 20, 366, 0x000000, 0);
	drawChar('I', 60, 366, 0x000000, 0);
	drawChar('Z', 100, 366, 0x000000, 0);
	drawChar('E', 140, 366, 0x000000, 0);
	drawChar(':', 180, 366, 0x000000, 0);

//drawLine (9, 420, 310, 421, 0x000000, 2);

	drawChar('F', 20, 436, 0x000000, 0);
	drawChar('O', 60, 436, 0x000000, 0);
	drawChar('R', 100, 436, 0x000000, 0);
	drawChar('M', 140, 436, 0x000000, 0);
	drawChar(':', 180, 436, 0x000000, 0);

drawLine (9, 490, 310, 491, 0x5C2E00, 5); // граница кнопок

	drawChar('E', 10, 506, 0x000000, 0);
	drawChar('X', 50, 506, 0x000000, 0);
	drawChar('I', 90, 506, 0x000000, 0);
	drawChar('T', 130, 506, 0x000000, 0);

drawLine (173, 490, 174, 560, 0x5C2E00, 5); //разделитель кнопок

	drawChar('N', 187, 506, 0x000000, 0);
	drawChar('E', 227, 506, 0x000000, 0);
	drawChar('W', 267, 506, 0x000000, 0);

drawLine (9, 560, 310, 561, 0x5C2E00, 5); //граница инструкции
drawRect (9, 565, 300, 195, 0xffffff); //ИНСТРУКЦИЯ

	drawChar('C', 10, 570, 0x000000, 1);
	drawChar('O', 30, 570, 0x000000, 1);
	drawChar('L', 50, 570, 0x000000, 1);
	drawChar('O', 70, 570, 0x000000, 1);
	drawChar('R', 90, 570, 0x000000, 1);
	drawChar('S', 110, 570, 0x000000, 1);
	drawChar(':', 130, 570, 0x000000, 1);
	drawChar('1', 160, 570, 0x000000, 1);
	drawChar('-', 180, 570, 0x000000, 1);
	drawChar('9', 200, 570, 0x000000, 1);


	drawChar('S', 12, 600, 0x000000, 1);
	drawChar('I', 30, 600, 0x000000, 1);
	drawChar('Z', 50, 600, 0x000000, 1);
	drawChar('E', 70, 600, 0x000000, 1);
	drawChar(':', 90, 600, 0x000000, 1);
	drawChar('<', 120, 600, 0x000000, 1);
	drawChar('>', 140, 600, 0x000000, 1);
/*
	drawChar('N', 10, 630, 0x000000, 1);
	drawChar('E', 30, 630, 0x000000, 1);
	drawChar('W', 50, 630, 0x000000, 1);
	drawChar(':', 70, 630, 0x000000, 1);
	drawChar('N', 100, 630, 0x000000, 1);


	drawChar('E', 10, 660, 0x000000, 1);
	drawChar('X', 30, 660, 0x000000, 1);
	drawChar('I', 50, 660, 0x000000, 1);
	drawChar('T', 70, 660, 0x000000, 1);
	drawChar(':', 90, 660, 0x000000, 1);
	drawChar('E', 120, 660, 0x000000, 1);
*/
size = change_size(size, '-');
change_form(1, size, color);
////////////////////////////////////////////////////////
while (1){
	//drawElipse(400,400,50,50,0x000000);
	readkey(&c);
	if (c == 0x50){	//P - вниз
		y++;
		if ((y + size) >= 760) y = 760 - size;
		drawRect(x, y, size, size, color);
	}
	if (c == 0x48){	//H - вверх
		y--;
		if (y < 9) y = 9;
		drawRect(x, y, size, size, color);
	}
	if (c == 0x4B){	//K - влево
		x--;
		if (x < 315) x = 315;
		drawRect(x, y, size, size, color);
	}
	if (c == 0x4D){	//M - Вправо
		x++;
		if ((x + size) >= 1016) x = 1016 - size;
		drawRect(x, y, size, size, color);
	}
	if (c == 0x01){	// Выход 69
		drawRect (1,1,1023,767, 0x000000);
		/*drawChar('G', 10, 50, 0x000000, 0);
		drawChar('O', 50, 50, 0x000000, 0);
		drawChar('O', 90, 50, 0x000000, 0);
		drawChar('D', 130, 50, 0x000000, 0);
		drawChar('B', 170, 50, 0x000000, 0);
		drawChar('Y', 210, 50, 0x000000, 0);
		drawChar('E', 240, 50, 0x000000, 0);
		
		drawChar(':', 300, 50, 0x000000, 0);
		drawChar('>', 340, 50, 0x000000, 0);*/
		pause(10000);
		return 0;
	}
	if (c == 0x31){	// Очистка листа 78
		drawRect (315,9,701,751, 0xffffff); // белое заполнение 315-1016  15-745
	}
	if (c == 0x33){	// Размер--
		size = change_size(size,'-');
		change_form(form, size, color);
	}
	if (c == 0x34){	// Размер++
		size = change_size(size,'+');
		change_form(form, size, color);
	}
	if (c == 0x1F){	//M - Форма-квадрат 83 квадрат
		form = 1;
		 change_form(form, size, color);
	}
	if (c == 0x2E){	//M - Форма-круг 67 круг
		form = 0;
		 change_form(form, size, color);
	}
	if (c == 0x02){	// Красный цвет
		 color = 0xF1102C;
		 colors();
		 drawRam(50, 122, 100, 172, 0xffffff, 3);
	}
	if (c == 0x03){	// Оранжевый цвет
		 color = 0xFF7D28;
		 colors();
		 drawRam(130, 122, 180, 172, 0xffffff, 3);
	}
	if (c == 0x04){	// Желтый цвет
		 color = 0xFFD03B;
		 colors();
		 drawRam(210, 122, 260, 172, 0xffffff, 3);
	}
	if (c == 0x05){	// Зеленый цвет
		 color = 0x44B32B;
		 colors();
		 drawRam(50, 192, 100, 242, 0xffffff, 3);
	}
	if (c == 0x06){	// Белый цвет
		  color = 0xffffff;
		  colors();
		  drawRam(130, 192, 180, 242, 0x000000, 3);
	}
	if (c == 0x07){	// Синий цвет
		 color = 0x5459C9;
		 colors();
		 drawRam(210, 192, 260, 242, 0xffffff, 3);
	}
	if (c == 0x08){	// Фиолетовый цвет
		 color = 0x8600C7;
		 colors();
		 drawRam(50, 262, 100, 312, 0xffffff, 3);
	}
	if (c == 0x09){	// Розовый цвет
		 color = 0xC400A6;
		 colors();
		 drawRam(130, 262, 180, 312, 0xffffff, 3);
	}
	if (c == 0x0A){	// Черный цвет
		 color = 0x000000;
		 colors();
		 drawRam(210, 262, 260, 312, 0xffffff, 3);
	}
	clearkey();
}
return 1;
}

//0xff0ffa
void drawLine(int x1, int y1, int x2, int y2, int color, int size){
int i,j;
for (i = y1; i < y2; i++)
		for (j = x1; j < x2; j++)
			drawRect(j,i,size,size,color);
}

void setPixel(int x, int y, int color) {
	int *p = 0x8000;//адрес фреймбуфера, куда писать цвета пикселей
	char *c = *p;
	c += ((y * 1024) + x) * 3;//сдвиг по фреймбуферу, 3 - размер пикселя (объем занимаемой памяти)
	*(int*)c = color;
}

void drawRam(int x1, int y1, int x2, int y2, int color, int size){
	int i,j;
	for (i = y1; i == y1; i++)
		for (j = x1; j < x2; j++)
			drawRect(j,i,size,size,color);

	for (i = x2; i == x2; i++)
		for (j = y1; j < y2; j++)
			drawRect(i,j,size,size,color);

	for (i = y2; i == y2; i++)
		for (j = x2; j > x1; j--)
			drawRect(j,i,size,size,color);

	for (i = x1; i == x1; i++)
		for (j = y2; j > y1; j--)
			drawRect(i,j,size,size,color);
}

void drawRect(int x, int y, int pixelWidth, int pixelHeight, int color1) {
	int i,j;
	for (i = y; i < y + pixelHeight; i++)
		for (j = x; j < x + pixelWidth; j++)
			setPixel(j, i, color1);
}

void wait(int t) {
	int i;
	for (i = 0; i < t; i++) {
	}
}

void zachistka(){

	int i;
	drawRect (1,1,1024,768,0x000000);
}

void pause(int x)
{
int i, j, m;
for (j = 0; j < 300*x; j++)
{
for (i = -5000; i < 0; i = i + 2)
{
m = m - 1;
m = m + 1;
i--;
}
m=m + 1;
}
}


void drawChar(char ch, int x, int y, int color, int flag) {
	int positionChar, pixelWidth, pixelHeight;
	char *p = fontAdrs + 0x3018;//3018
	if (flag == 1) {
		pixelWidth = 3;
		pixelHeight = 3;
	}
	else {
		pixelWidth = 7; 
		pixelHeight = 7; 
	}
	if ((int)ch == 65) positionChar = 0;
	if ((int)ch == 66) positionChar = 1;
	if ((int)ch == 67) positionChar = 2;
	if ((int)ch == 68) positionChar = 3;
	if ((int)ch == 69) positionChar = 4;
	if ((int)ch == 70) positionChar = 5;
	if ((int)ch == 71) positionChar = 6;
	if ((int)ch == 72) positionChar = 7;
	if ((int)ch == 73) positionChar = 8;
	if ((int)ch == 74) positionChar = 9;
	if ((int)ch == 75) positionChar = 10;
	if ((int)ch == 76) positionChar = 11;
	if ((int)ch == 77) positionChar = 12;
	if ((int)ch == 78) positionChar = 13;
	if ((int)ch == 79) positionChar = 14;
	if ((int)ch == 80) positionChar = 15;
	if ((int)ch == 81) positionChar = 16;
	if ((int)ch == 82) positionChar = 17;
	if ((int)ch == 83) positionChar = 18;
	if ((int)ch == 84) positionChar = 19;
	if ((int)ch == 85) positionChar = 20;
	if ((int)ch == 86) positionChar = 21;
	if ((int)ch == 87) positionChar = 22;
	if ((int)ch == 88) positionChar = 23;
	if ((int)ch == 89) positionChar = 24;
	if ((int)ch == 90) positionChar = 25;
	if ((int)ch == 49) positionChar = 26;
	if ((int)ch == 50) positionChar = 27;
	if ((int)ch == 51) positionChar = 28;
	if ((int)ch == 52) positionChar = 29;
	if ((int)ch == 53) positionChar = 30;
	if ((int)ch == 54) positionChar = 31;
	if ((int)ch == 55) positionChar = 32;
	if ((int)ch == 56) positionChar = 33;
	if ((int)ch == 57) positionChar = 34;
	if ((int)ch == 58) positionChar = 36;
	if ((int)ch == 48) positionChar = 35;
	if ((int)ch == 45) positionChar = 37;
	if ((int)ch == 60) positionChar = 38;
	if ((int)ch == 62) positionChar = 39;


	for (int i = 0; i < positionChar; i++) p += fontWidth * fontHeight;

	for (int i = y; i < y + fontHeight * pixelHeight; i += pixelHeight) {
		for (int j = x; j < x + fontWidth * pixelWidth; j += pixelWidth) {
			if (*p == 1) {
				drawRect(j, i, pixelWidth, pixelWidth, color);
			}
			p++;
		}
	}
}

void Resetkb() {
	asm("mov eax, 0");
	asm("mov al, [ebp-4]");
	asm("out 0x60, al");
}

void readkey(char *c)
{
asm("mov bx, [ebp+8]");
asm("in al, 0x60");
asm("mov [bx], al");
}

void clearkey()
{
asm("mov al, 0");
asm("out 0x60, al");
}

int change_size(int val, char simb){
	if (simb == '+') {
		val = val + 10;
		if (val > 50) val = 50;
	}
	if (simb == '-'){
		val = val - 10;
		if (val < 10) val = 10;
	}
		drawRect(230, 366, 78, 42, 0xDCE6F4);
		if (val == 10)
			drawChar('1', 230, 366, 0x000000, 0);
		if (val == 20)
			drawChar('2', 230, 366, 0x000000, 0);
		if (val == 30)
			drawChar('3', 230, 366, 0x000000, 0);
		if (val == 40)
			drawChar('4', 230, 366, 0x000000, 0);
		if (val == 50)
			drawChar('5', 230, 366, 0x000000, 0);
		return val;
}

void change_form(int form, int size, int color) {
	drawRect(230, 432, 78, 50, 0xDCE6F4);
		if (form == 0);//circle

		if (form == 1) //square
			drawRect(230, 432, size, size, color);
}

/*
void drawElipse(int cx,int cy,int h,int w,int color){
int hh = h * h;
int ww = w * w;
int hhww = hh * ww;
int x0 = w;
int dx = 0;

// do the horizontal diameter
for (int x = -w; x <= w; x++)
setPixel(cx + x, cy,color);

// now do both halves at the same time, away from the diameter
for (int y = 1; y <= h; y++)
{
int x1 = x0 - (dx - 1); // try slopes of dx - 1 or more
for ( ; x1 > 0; x1--)
if (x1*x1*hh + y*y*ww <= hhww)
break;
dx = x0 - x1; // current approximation of the slope
x0 = x1;

for (int x = -x0; x <= x0; x++)
{
setPixel(cx + x, cy - y,color);
setPixel(cx + x, cy + y,color);
}
}
}*/

void colors(){
	drawRect(35, 100, 273, 240,0xDCE6F4);
	drawRect(50, 122, 50, 50, 0xF1102C);
	drawRect(130, 122, 50, 50, 0xFF7D28);
	drawRect(210, 122, 50, 50, 0xFFD03B);
//drawLine (9, 140, 310, 141, 0x000000, 2);
	drawRect(50, 192, 50, 50, 0x44B32B);
	drawRect(130, 192, 50, 50, 0xffffff);
	drawRect(210, 192, 50, 50, 0x5459C9);
//drawLine (9, 210, 310, 211, 0x000000, 2);
	drawRect(50, 262, 50, 50, 0x8600C7);
	drawRect(130, 262, 50, 50, 0xC400A6);
	drawRect(210, 262, 50, 50, 0x000000);
}