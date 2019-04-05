// 5-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include<iostream>
#include<fstream>  
using namespace std;
struct color { unsigned char r; unsigned char g; unsigned char b; } c;
struct tmp { float r; float g; float b; } t; //tmp  для w


int main() {
	float kkk;
	cout << sizeof(kkk);
	ifstream fff("D:\\VisualStudio project\\5-1\\haha.bmp", ios::binary); //  ios::binary влияет ТОЛЬКО на endl.
	ofstream ggg("D:\\VisualStudio project\\5-1\\rez.bmp", ios::binary);//сюда пишем (поток типа ofstream= output file stream)
	if (!fff) { cout << "No file d:\\1.bmp. Can't open\n"; exit(1); }
	if (!ggg) { cout << "   file d:\\rez.bmp. Can't create\n"; exit(1); }

	char buf[30];// куда читать байты
	unsigned char r, g, b;//компоненты цвета
	color c;
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
	unsigned char R = c.r;
	unsigned char G = c.g;
	unsigned char B = c.b;


	float rr = 255;// второй цвет градиента
	float gg = 46;
	float bb = 99;
	float step = 100;// кол-во шагов 

	float stepR = (rr - c.r) / step;
	float stepG = (gg - c.g) / step;
	float stepB = (bb - c.b) / step;
	int kk = 0;
	
	t.r = (float)c.r; // присваиваем значение flot чтобы потом можно было считать когда шаг дробный
	t.g = (float)c.g;
	t.b = (float)c.b;

	
	int tmp{ 0 };
	int W = 100; //координаты точек из которыз будет начинаться градиент
	int H = 200;
	int x = H - step / 2;
	int y = W - step / 2;
	for (int i = 1; i <= x; ++i) {
		for (int j = 1; j <= w; ++j)
			ggg.write((char *)&c, 3);
	}

	
	for (int i = x + 1; i < step + x + 1; i++) {
	if (y > 0) {
		
			for (int j = 1; j <= y; j++) {
				ggg.write((char *)&c, 3);
			}
			for (int z = (y + 1); z <= (y + 1 + step); z++) {
				t.g += stepG;
				t.r += stepR;
				t.b += stepB;
				c.r = (unsigned char)t.r;
				c.g = (unsigned char)t.g;
				c.b = (unsigned char)t.b;
				ggg.write((char *)&c, 3);
			}
			c.r = R;
			c.g = G;
			c.b = B;
			t.r = R;
			t.g = G;
			t.b = B;

			for (int p = (y + 2 + step); p <= w; p++)
				ggg.write((char *)&c, 3);


		}
	
	else {
		for (int z = 1; z <= y + 1 + step; z++) {
			if (z > w)
				break;
			t.g += stepG;
			t.r += stepR;
			t.b += stepB;
			c.r = (unsigned char)t.r;
			c.g = (unsigned char)t.g;
			c.b = (unsigned char)t.b;
			ggg.write((char *)&c, 3);
		}
		c.r = R;
		c.g = G;
		c.b = B;
		t.r = R;
		t.g = G;
		t.b = B;

		for (int p = (y + 2 + step); p <= w; p++)
			ggg.write((char *)&c, 3);

	}
	
	}
	for (int i = x+step+1; i <= h; ++i) {
		for (int j = 1; j <= w; ++j)
			ggg.write((char *)&c, 3);
	}
	fff.close();//закрыли файл
	ggg.close();//закрыли файл
	return 1;
}
