// 0-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*
В массиве размера N, заполненного случ.числами от 0 до 10, подсчитать количество элементов, встречающихся более одного раза.*/
#include "pch.h"
#include <iostream>
#include<time.h>
using namespace std;

int* giveMemory(int a) {
	int* A = new int[a];
	if (!A) {
		cout << "very bad";
		exit;
	}
	return A;
}
void initArr(int* arr, int n, int c) { //иницилизируем константой
	for (int i = 0; i < n; ++i) {
		*(arr++) = c;

	}
}
void freeMemory(int* a) {
	delete[] a;
	a = nullptr;


}
void randomInitArray(int *arr, int n, int min, int max) { // рандомная иницилизация
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

bool is(int m, int *tmp, int n) {   // проверка есть ли уже такое число 
	int *t = tmp;
	for (int i = 0; i < n; ++i) {
		if (*tmp == m)
			return true;
		tmp++;
	}
	tmp = t;
	*(tmp + (m % n)) = m;
	return false;
}

void fff(int *arr,int *cnt, int n, int maxval) {// осуществляется подсчет повторений
	int *tmp = giveMemory(maxval);
	//initArr(cnt, maxval, -1);
	
	

	for (int i = 0; i < n; ++i) {
		if (is(*arr, tmp, maxval)) {
			*(cnt + ((*arr) % n))+=1;
			cout << "cnt   "<<i<<"   " << *(cnt + ((*arr) % n))<<'\n';
			
		}
		++arr;

	}
	freeMemory(tmp);

}
void outprintArr(int* arr, int n) { // специальный вывод для результата
	for (int i = 0; i < n; ++i) {
		if (*(arr) > 1)
			cout << "Count " << i << ":" << *(arr) << '\n';
		++arr;
	}
}

int main()
{
	
	int n;
	cin >> n;
	int maxval=11;// так количество от 0 до 10 возможных чисел  =11
	int *cnt = giveMemory(maxval);
	initArr(cnt, maxval, 1);
	printArr(cnt, maxval);
	cout << cnt << '\n';
	int *arr = giveMemory(n);
	randomInitArray(arr, n,0,10);
	printArr(arr, n);
	
	fff(arr,cnt, n,maxval);
	cout << cnt << '\n';
	outprintArr(cnt, maxval);
	freeMemory(cnt);
	freeMemory(arr);

     
}

