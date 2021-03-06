// 0-3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*
Массив чисел размера N проинициализировать случайными числами из промежутка от -N до N.
Написать функцию циклического сдвига элементов массива вправо на k элементов.*/
#include "pch.h"
#include <iostream>
#include<time.h>
using namespace std;

void randomInitArray(int *arr, int n, int max, int min) { // рандомная иницилизация
	srand(time(0));
	max++;
	int tmp = max - min;
	for (int i = 0; i < n; i++)
	{
		*(arr++) = rand() % tmp + min;
	}
}
void reverse(int *arr, int beg, int end) { //переворот

	while (beg < end) {
		swap(*(arr + beg), *(arr + end));
		++beg;
		--end;
	}
}
void sdvig(int *arr, int k, int n) { //сдвиг 
	reverse(arr, n - k, n - 1);
	reverse(arr, 0, n - 1 - k);
	reverse(arr, 0, n - 1);
}
void printArr(int*  arr, int n) {// вывод
	for (int i = 0; i < n; ++i) {
		cout << *(arr + i) << "   ";
	}
}
int* giveMemory(int a) {
	int* A = new int[a];
	if (!A) {
		cout << "very bad";
		exit;
	}
	return A;
}
void freeMemory(int* a) {
	delete[] a;
	a = nullptr;
	
	
}

int main()
{
	int n;
	cin >> n;
	int *arr = giveMemory(n);
	randomInitArray(arr, n, n, -n);
	printArr(arr, n);
	int k;
	cin >> k;
	sdvig(arr, k, n);
	printArr(arr, n);


	freeMemory(arr);


     
}
