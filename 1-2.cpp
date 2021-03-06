﻿// 1-2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*
Положительные элементы массива А(N) переставить в конец массива, сохраняя порядок следования. 
Отрицательные элементы расположить в порядке убывания. Дополнительный массив не использовать.*/
#include "pch.h"
#include <iostream>
#include<time.h>

using namespace std;
void randomInitArray(int *arr, int n, int min, int max) { //иницилизация массива
	srand(time(0));
	max++;
	int tmp = max - min;
	for (int i = 0; i < n; i++,++arr)
	{
		*(arr) = rand() % tmp + min;
	}
}
void sort(int *Arr, int n) {
	int tmp;
	int* a2 = nullptr; // переносим в конец массива
	int* a1 = nullptr;
	char flag{ 1 };
	char flagMin{ 0 };
	for (int i = 0; i < n; i++) {
		flagMin = 0;
		a2 = Arr + n;
		a1 = Arr + n-1;
		flag = 1;
		for (int j = n; j > -1; j--) {
			if ((!flagMin) && (*a1 < 0)) {
				a2 = a1;
				flagMin = 1;
			}
			else if (((*a1 >= 0)&&flagMin) ){
				tmp = *a2;
				*a2 = *a1;
				*a1 = tmp;
				flagMin = 0;
				flag = 0;
			}
			
			a1--;
			
		}
		if (flag)
			break;
	}
	int cnt{1};
	int *arr = Arr;
	while (*(arr+1) < 0) { //находим кол-во отрицательных элементов
		if (*arr < *(arr + 1)) {
			tmp = *arr;
			*arr = *(arr + 1);
			*(arr + 1) = tmp;
		}
		++cnt;
		++arr;
	}
	for (int i = 0; i < cnt ; i++) { //сортируем отрицательные элементы
		flag = 1;
		arr = Arr;
		for (int j = 0; j < cnt -1; j++) {
			if (*arr < *(arr + 1)) {
				tmp = *arr;
				*arr = *(arr + 1);
				*(arr + 1) = tmp;
				flag = 0;
			}
			++arr;
		}
		if (flag)
			break;
	}

}	

void printArr(int*  arr, int n) {
	for (int i = 0; i < n; ++i) {
		cout << *(arr++) << "   ";
	}
	cout << '\n';
}
int *giveMemory( int n) {
	int *a = new(nothrow) int[n];
	if (!a) {
		cout << "very bad";
		exit;
	}
	return a;
}
void freeMemory(int *a) {
	delete[] a;
	a = nullptr;
	
}


int main()
{
	int n;
	cin >> n;
	int *Arr = giveMemory(n);
	randomInitArray(Arr, n, -5, 5);
	printArr(Arr, n);
	sort(Arr, n);
	printArr(Arr, n);
	freeMemory(Arr);
}
