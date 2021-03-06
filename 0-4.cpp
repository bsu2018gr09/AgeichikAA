// 0-4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*
Расположить в порядке возрастания элементы массива А(N), начиная с k-го элемента.*/
#include "pch.h"
#include <iostream>
#include<time.h>
using namespace std;
void swap(int *big, int *small) {
	*small = *big + *small;
	*big = *small - *big;
	*small = *small - *big;
}



void sort(int *a, int n, int k) {
	char flag{ 1 };
	a = a + k;
	int *tmp = a;
	for (int i = k; i < n ; i++) {
		flag = 1;
		a = tmp;
		for (int j = k; j < n-1 ; j++) {
			if (*a > *(a+1)) {
				swap(a, a+1);
				flag = 0;
			}
			++a;
		}
		if (flag)
			break;
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
void randomInitArray(int *arr, int n, int max, int min) { // рандомная иницилизация
	srand(time(0));
	max++;
	int tmp = max - min;
	for (int i = 0; i < n; i++)
	{
		*(arr++) = rand() % tmp + min;
	}
}
void printArr(int*  arr, int n) {// вывод
	for (int i = 0; i < n; ++i) {
		cout << *(arr + i) << "   ";
	}
	cout << '\n';
}

int main()
{
	int n;
	cin >> n;
	int *arr = giveMemory(n);
	randomInitArray(arr, n,0, 10);
	printArr(arr, n);
	int k;
	cin >> k;
	sort(arr, n, k);
	
	printArr(arr, n);
     
}

