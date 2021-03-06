﻿// 1-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*
Даны точки плоскости своими координатами в виде двух одномерных массивов (случайные числа).
Точки плоскости рассортировать по возрастанию расстояния до прямой ax + by + c = 0.
*/
#include "pch.h"
#include <iostream>
using namespace std;
void initArrc(float *a, int n, float c) {
	float *x = a;
	
	for (int i = 0; i < n; ++i) {
		*a = c;
		a++;
	}
	a = x;
	
}
void initArrc(float *a, int n) {
	float *x = a;
	
	for (int i = 0; i < n; ++i) {
		*a = i;
		a++;
	}
	a = x;
	
}
float d(float x, float y, float a, float b, float c) { //находим расстояние от точки до прямой
		return abs(a*x + b * y + c) / sqrt(a*a + b * b);;
}

void sort(float *X, float *Y, int n, float a, float b, float c) {
	float tmp;
	float *x = X;
	float *y = Y;
	
	for (int i = 0; i < n; i++) {
		X = x;
		Y = y;
		for (int j = 0; j < n-2; j++) {
			

			if (d(*X,*Y,a,b,c)> d(*(X+1),*(Y+1),a,b,c)) { //сравниваем расстояние 
				tmp = *X;
				*X = *(X + 1);
				*(X+1) = tmp;
				tmp = *Y;
				*Y = *(Y + 1);
				*(Y+1) = tmp;

			}
		
			++X;
			++Y;
		}
	}
	X = x;
	Y = y;
}


 void output(float *X, float *Y, int n) {
	 float *x = X;
	float *y = Y;
	 for (int i = 0; i < n; ++i) {
		 cout << *X << ' ' << *Y<<'\n';
		 ++X;
		 ++Y;
	 }
	 X = x;
	 Y = y;
	 cout << "new out" << '\n';
}
 float *giveMemory(int n) {
	 float *a = new(nothrow) float[n];
	 if (!a) {
		 cout << "very bad";
		 exit;
	 }
	 return a;
 }
 void freeMemory(float *a) {
	 delete[] a;
	 a = nullptr;
	 
 }
 void enterStraight(int &a, int &b, int &c) { //вводим координаты прямой
	 cout << "Enter straight";
	 cin >> a >> b >> c;
 }
int main()
{
	int n;
	cin >> n;
	float *X=giveMemory(n);
	float *Y=giveMemory(n);
	

	initArrc(X, n, 1);
	initArrc(Y, n );
	output(X, Y, n);
	int a, b, c;
	enterStraight(a, b, c);
	sort(X, Y, n, a, b, c);
	output(X, Y,n);
	freeMemory(X);
	freeMemory(Y);


  
}


