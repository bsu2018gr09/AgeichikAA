﻿// 1-3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*
Элементы массива А(N), 
значения которых – простые числа, расположить в порядке возрастания, не нарушая порядка следования других элементов.
*/
#include "pch.h"
#include <iostream>
#include<time.h>
using namespace std;

void randomInitArray(int *arr, int n, int min, int max) {
	srand(time(0));
	max++;
	int tmp = max - min;
	for (int i = 0; i < n; i++)
	{
		*(arr + i) = rand() % tmp + min;
	}
}
void printArr(int*  arr, int n) {
	for (int i = 0; i < n; ++i) {
		cout << *(arr + i) << "   ";
	}
	cout << '\n';
}
bool isPrime(int a) {
	if ((!(a%2))&&(a!=2))
		return false;
	for (int i = 3; i*i <= a; i += 2) {
		if (!(a%i))
			return false;
	}
	return true;
}
void sort(int *Arr, int n, int m) {
	char flag{ 1 };
	char trueFlag{ 0 };
	int tmp;
	int cnt{ -1 };
	int *arr = Arr;
	int *prime=nullptr;
	int *prime2=arr;
	int *tmp2 = nullptr;
	for (int i = 0; i < n; ++i, ++arr) {    //находим первое простое число
		if (isPrime(*arr)){
			++cnt;
			
			tmp2 = arr;
			break;
	}
		++cnt;
	}
	

	for (int i = 0; i < n ; i++) { //сортируем так что сортировки касаются только простые числа
		flag = 1;
		prime = tmp2;
		prime2 = tmp2;
		arr = Arr;
		trueFlag = 0;
		for (int j = 0; j < n ; j++,++arr) {
			if (isPrime(*arr)) {
				prime2 = arr;
				trueFlag = 1;
			}
			else
				trueFlag = 0;
			if ((*prime>*prime2)&&trueFlag) {
				tmp = *prime;
				*prime = *prime2;
				*prime2 = tmp;
				
				flag = 0;
				trueFlag = 0;
			}
			prime = prime2;
		}
		if (flag)
			break;
	}

}
int *giveMemory(int n) {
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
	int m;
	cin >> m;
	int *arr = giveMemory(n);
	randomInitArray(arr, n,2,m);
	printArr(arr, n);
	sort(arr, n, m);
	printArr(arr, n);
	freeMemory(arr);
	
}

