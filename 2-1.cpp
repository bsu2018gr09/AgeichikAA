﻿/*В массиве А(N,М) столбец с минимальным количеством нечетных элементов поменять местами с последним столбцом.
*/

#include "pch.h"
#include <iostream>
#include<iomanip>
using namespace std;

void initRand(int *arr, int n, int a, int b)//присваиваем массиву рандомные числа
{
	for (int i{ 0 }; i < n; ++i) { 
		*(arr) = rand() % (b - a + 1) + a;
		arr++;

	}
}
int** give_memory(int a, int b) {
	int **arr = new (nothrow) int*[a];
	if (!arr) {
		cout << "very bad";
		exit;
	}
	for (int i = 0; i < a; ++i)
		arr[i] = new int[b];
	return arr;
}
void free_array(int **arr, int n, int) {
	for (int i = 0; i < n; ++i) {
		delete[] arr[i];
		arr[i] = nullptr;
	}
	delete[] arr;
	arr = nullptr;
}
void init_array(int **arr, int n, int m, int min=0, int max=50) {
	for (int i = 0; i < n; ++i) {
		initRand(*arr, m, min, max);
		++arr;
	}
}

void print_array(int **arr, int n, int m) {
	int k{ 0 };
	for (int i = 0; i < n; ++i) {

		for (int j = 0; j < m; ++j) {
			cout <<setw(5) <<arr[j][i] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
}
int cntNec(int *arr, int a) { //считаем кол-во нечетных чисел в столбце
	int cnt{ 0 };
	for (int i = 0; i < a; ++i) {
		if ((*arr) % 2)
			cnt++;
		arr++;
	}
	return cnt;
}
int comparison(int **arr, int a, int b) { //сравниваем все столбцы между собой
	int tmp = cntNec(*arr, b);
	arr++;
	int ind{ 0 };
	int tmpcnt;
	for (int i = 1; i < a; ++i) {
		tmpcnt = cntNec(*arr, b);
		if (tmp > tmpcnt) {
			ind = i;
			tmp = tmpcnt;
		}
		arr++;
	}
	return ind;
}

void swap(int **arr, int ind, int m) { //меняем нужные столбцы местами	
	int *tmp= *(arr + ind);
	*(arr + ind) = *(arr + m - 1);
	*(arr + m - 1) = tmp;
}
int main()
{
	int n, m;
	cin >> n >> m;
	int **arr = give_memory(m, n);
	init_array(arr, m, n);
	print_array(arr, n,m);
	int ind= comparison(arr,m,n);
	swap(arr, ind, m);
	print_array(arr, n, m);
	free_array(arr, m, n);
}

