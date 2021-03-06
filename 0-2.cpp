// 0-2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*
В массиве размера N, заполненного случ.числами от 0 до 10, определить максимальную длину последовательности равных элементов.*/
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
		*(arr) = rand() % tmp + min;
		++arr;
	}
}
int  findMaxSequence(int* arr, int n) {// нахождение максимальной длины
	int cnt{ 1};
	int cnt2{ 1};
	for (int i = 0; i < n-1; ++i) {
		if (*(arr + i) == *(arr + (i + 1))) {
			while (*(arr + i) == *(arr + (i + 1))) {
				++cnt;
				++i;
			}
		}
		
		if(cnt>cnt2)
			cnt2 = cnt;
	}
	return (cnt2);
}
void printArr(int*  arr, int n) {
	for (int i = 0; i < n; ++i) {
		cout << *(arr + i) << '\n';
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
	//int i[10] = { 1,1,1,0,2,4,4,0,4,4 };
	//arr = i;
	randomInitArray(arr, n, 0, 10);
	printArr(arr, n);
	cout <<"max sequence = "<< findMaxSequence(arr, n);
	freeMemory(arr);
}

