// 5-11.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
// 5-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include<iostream>
#include<fstream>  
using namespace std;
struct color { unsigned char r; unsigned char g; unsigned char b; } c;
struct tmp { float r; float g; float b; } t; //tmp  для w
struct tmpH { float r; float g; float b; } th; // tmp для h

void swap(unsigned char &a, unsigned char &b) {
	a += b;
	b = a - b;
	a = a - b;
}

int main() {
	ifstream fff("D:\\VisualStudio project\\5-1\\haha.bmp", ios::binary); //  ios::binary влияет ТОЛЬКО на endl.
	ofstream ggg("D:\\VisualStudio project\\5-1\\rez.bmp", ios::binary);//сюда пишем (поток типа ofstream= output file stream)
	if (!fff) { cout << "No file d:\\1.bmp. Can't open\n"; exit(1); }
	if (!ggg) { cout << "   file d:\\rez.bmp. Can't create\n"; exit(1); }

	char buf[30];// куда читать байты
	unsigned char r, g, b;//компоненты цвета
	color c;
	tmp t;
	tmpH th;
	unsigned int w, h;//надеемся. что тут 4 байта

	fff.read((char *)&buf, 18);   //чтение 18 байт заголовка bmp
	ggg.write((char *)&buf, 18);    //запись 18 байт заголовка bmp
	fff.read((char *)&w, 4); cout << "w=" << w;   //чтение width из заголовка bmp
	fff.read((char *)&w, 4); cout << ", h=" << w; //чтение height из заголовка bmp
	w = 512; ggg.write((char *)&w, 4);    //запись width в заголовок bmp ( w кратно 4, обязательно для нас, чтобы не делать выравнивание)
	h = 256; ggg.write((char *)&h, 4);    //запись height в заголовок bmp
	fff.read((char *)&buf, 28);   //чтение 28 байт заголовка bmp
	ggg.write((char *)&buf, 28);    //запись 28 байт заголовка bmp

	c.r = 128; //первый цвет градиента
	c.g = 16;
	c.b = 77;
		
	unsigned char rr = 255; //второй цвет градиента
	unsigned char gg = 46;
	unsigned char bb = 99;
	
	float step = 520; // количество шагов
	
	swap(c.r, rr);
	swap(c.g, gg);
	swap(c.b, bb);
	float stepR = ((float)rr - c.r) / step; // cчитаем размер одного шага
	float stepG = ((float)gg - c.g) / step;
	float stepB = ((float)bb - c.b) / step;
	int kk = 0;
	int jj = 0;
	t.r = (float)c.r; // присваиваем значение flot чтобы потом можно было считать когда шаг дробный
	t.g = (float)c.g;
	t.b= (float)c.b;

	th.r = (float)c.r;
	th.g = (float)c.g;
	th.b = (float)c.b;
	int tmp{ 0 };
	//int ww = w;
	//int hh = h;
	for (int i = 1; i <= h ; ++i) {
		if (jj < step) {
			th.g += stepG; //  чтобы получать точное значение (например если трижды прибавить 0,34 и затем присвоим c.r значение увеличиться на 1 )
			th.r += stepR;
			th.b += stepB;
			c.r = (unsigned char)th.r;
			c.g = (unsigned char)th.g;
			c.b = (unsigned char)th.g;
			jj++;
		}
		t.r = c.r;
		t.g = c.g;
		t.b = c.b;
		jj = i-1;
		kk = i-1;
		for (int j = 1; j <= w; ++j) {
			if (kk < step) {
				t.g += stepG;
				t.r += stepR;
				t.b += stepB;
				c.r = (unsigned char)t.r;
				c.g = (unsigned char)t.g;
				c.b = (unsigned char)t.b;
				kk++;
			}
			ggg.write((char *)&c, 3); //запись сразу всего цвета
		}

	}

	fff.close();//закрыли файл
	ggg.close();//закрыли файл
	return 1;
}