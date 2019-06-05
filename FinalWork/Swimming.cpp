
#ifndef Swimming_CPP
#define Swimming_CPP
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<ctime>
#include <fstream>
#include <cstring>
#include"Swimming.h"
#include <Windows.h>//обязательно для setConsole
char f[] = "D:\\VisualStudio project\\7-1\\file.txt";


void randArr(Swimming *arr, int n, int cntid);
int cntId(Swimming *arr, int n, int idS);
void initSwimId(Swimming *arr1, Swimming *arr2, int n, int idS);
void swap(Swimming & a, Swimming  &b);
void sortById(Swimming *arr, int beg, int end);
void sortByRes(Swimming *arr, int beg, int end);
void sortByID(Swimming *arr, int n);
type averageTime(Swimming *arr, int n);
Swimming* Swim(Swimming* arr, int n, int idS, int &c);
void printArr(Swimming *arr, int cnt);
int cntId(Swimming *arr, int n);
Swimming * ResSwim(Swimming *arr, int n, int &cnt, type &aver);
void readFile(Swimming &c);
void writeFile(Swimming &c, int n);
int findCnt();
void changeById(int id, int t);
void changeOneEl(const Swimming& nw, int n);
void changeOneElByEl(const Swimming& old, const Swimming& nw);
Swimming* initArrOfFile(int &c);
void outToFile(Swimming *arr, int n);


void randArr(Swimming *arr, int n, int cntid) {
	int tmp{ 0 };
	int *arrDist = giveMemory<int>(cntid);
	for (int i = 0; i < cntid; ++i)
		arrDist[i] = (rand() % 10) * 50 + 50;
	for (int i = 0; i < n; ++i) {
		tmp = rand() % cntid;
		arr[i].SetDistance(arrDist[tmp]);
		arr[i].SetId(tmp + 1);
		arr[i].SetTime(rand() % 570 + 30);
	}
}
int cntId(Swimming *arr, int n, int idS)
{
	int cnt{ 0 };
	for (int i = 0; i < n; i++)
	{
		if (arr[i].GetId() == idS)
			cnt++;
	}
	return cnt;
}
void initSwimId(Swimming *arr1, Swimming *arr2, int n, int idS)
{
	int tmp{ 0 };
	for (int i = 0; i < n; i++)
	{
		if (arr2[i].GetId() == idS)
		{
			arr1[tmp] = arr2[i];
			tmp++;
			if (tmp == n)
				break;

		}

	}
}

void swap(Swimming & a, Swimming  &b)
{
	Swimming tmp;
	tmp = a;
	a = b;
	b = tmp;
}

void sortById(Swimming *arr, int beg, int end)
{
	int l = beg, r = end;
	Swimming piv = arr[(l + r) / 2];
	while (l < r)
	{
		while (arr[l].GetId() < piv.GetId())
			l++;
		while (arr[r].GetId() > piv.GetId())
			r--;
		if (l <= r)
			swap(arr[l++], arr[r--]);
	}
	if (beg < r)
		sortById(arr, beg, r);
	if (end > l)
		sortById(arr, l, end);
}
void sortByRes(Swimming *arr, int beg, int end)
{
	int l = beg, r = end;
	Swimming piv = arr[(l + r) / 2];
	while (l < r)
	{
		while (arr[l].GetTime() < piv.GetTime())
			l++;
		while (arr[r].GetTime() > piv.GetTime())
			r--;
		if (l <= r)
			swap(arr[l++], arr[r--]);
	}
	if (beg < r)
		sortByRes(arr, beg, r);
	if (end > l)
		sortByRes(arr, l, end);
}
/*
void sortByRes(Swimming *arr, int n)
{
	bool flag{ 0 };
	for (int i = 0; i < (n); i++)
	{
		flag = 0;
		for (int j = 0; j < (n - 1); ++j)
		{
			if (arr[j].GetTime() > arr[j + 1].GetTime())
			{
				flag = 1;
				swap(arr[j], arr[j + 1]);
			}
		}
		if (!flag)
			break;
	}
}
*/
void sortByID(Swimming *arr, int n)
{
	bool flag{ 0 };
	for (int i = 0; i < (n); i++)
	{
		flag = 0;
		for (int j = 0; j < (n - 1); ++j)
		{
			if (arr[j].GetId() > arr[j + 1].GetId())
			{
				flag = 1;
				swap(arr[j], arr[j + 1]);
			}
		}
		if (!flag)
			break;
	}
}
/*
void sortByRes(Swimming *arr, int n) {
	bool flag{ 0 };
	for (int i = 0; i < (n); i++) {
		flag = 0;
		for (int j = 0; j < (n-1); ++j) {
			if (arr[j].GetTime() > arr[j + 1].GetTime()) {
				flag = 1;
				swap(arr[j], arr[j + 1]);
			}
		}
		if (!flag)
			break;
	}
}
*/
type averageTime(Swimming *arr, int n) {
	type aver{ 0 };
	type sum{ 0 };
	int h{ 10 };

	for (int j = 0; j < h; ++j) {
		for (int i = 0; i < n / h; ++i) {
			sum = arr[i*j].GetTime();
		}
		aver = aver + sum;
	}
	aver /= h;
	return aver;

}
Swimming* Swim(Swimming* arr, int n, int idS, int &c)
{
	//idS - какого заплыва резултатты

	c = cntId(arr, n, idS);

	Swimming *arr1 = giveMemory<Swimming>(c);
	initSwimId(arr1, arr, n, idS);
	sortByRes(arr1, 0, c);
	return arr1;
}
void printArr(Swimming *arr, int cnt)
{
	for (int i = 0; i < cnt; ++i)
		cout << arr[i] << '\n';
}

int cntId(Swimming *arr, int n)
{
	int cnt{ 1 };
	int tmp = arr[0].GetId();
	for (int i = 1; i < n; ++i)
	{
		if (arr[i].GetId() != tmp)
		{
			tmp = arr[i].GetId();
			++cnt;
		}
	}
	return cnt;

}
Swimming * ResSwim(Swimming *arr, int n, int &cnt, type &aver)
{
	aver = averageTime(arr, n);
	sortById(arr, 0, n - 1);
	//printArr(arr, n);
	//cnt = cntId(arr, n);
	Swimming* win = giveMemory<Swimming>(cnt * 3);
	Swimming win1;
	Swimming win2;
	Swimming win3;
	win3.SetTime(1000000);
	win2.SetTime(1000000);
	win1.SetTime(1000000);
	int j{ 0 };
	int tmp{ 0 };
	for (int i = 0; i < cnt; ++i)
	{
		win3.SetTime(1000000);
		win2.SetTime(1000000);
		win1.SetTime(1000000);

		tmp = arr[j].GetId();
		while (arr[j].GetId() == tmp)
		{
			if (arr[j].GetTime() < win3.GetTime())
			{
				if (arr[j].GetTime() < win2.GetTime())
					if (arr[j].GetTime() < win1.GetTime()) {
						win3 = win2;
						win2 = win1;
						win1 = arr[j];
					}
					else {
						win3 = win2;
						win2 = arr[j];
					}
				else
					win3 = arr[j];
			}
			++j;

		}
		tmp = arr[j].GetId();
		win[i * 3 + 0] = win1;
		win[i * 3 + 1] = win2;
		win[i * 3 + 2] = win3;
	}
	return win;
}
void readFile(Swimming &c) {
	ofstream fff(f, ios::in | ios::out | ios::app);
	fff << c;
	fff.close();
	//cout << "haha";
}
void writeFile(Swimming &c, int n) {
	ifstream fff(f, ios::in);

	for (int i = 0; i < n; ++i)
		fff >> c;

	fff.close();
}
int findCnt() {
	int cnt{ 0 };
	Swimming tmp;
	ifstream fff(f);
	fff >> tmp;

	while (!fff.eof()) {
		fff >> tmp;
		++cnt;
	}
	fff.close();
	return cnt;
}
void changeById(int id, int t) {//добавляет ко всем элементам в файле с заданныи id  заданное кол-во секунд
	ifstream fff(f);
	int a{ 0 };
	int cnt = findCnt();
	Swimming *tmp = giveMemory<Swimming>(cnt);
	for (int i = 0; i < cnt; ++i) {
		fff >> tmp[i];
		if (tmp[i].GetId() == id) {
			a = tmp[i].GetTime();
			tmp[i].SetTime(a + t);
		}
	}
	fff.close();
	ofstream kk(f, ios::trunc);
	kk << tmp[3];
	kk.close();
	ofstream ggg(f);
	for (int i = 0; i < cnt; ++i)
		ggg << tmp[i];
	ggg.close();

}
void changeOneEl(const Swimming& nw, int n) {
	Swimming *tmp = giveMemory<Swimming>(1000);
	ifstream fff(f);
	for (int i = 0; i < n; ++i)
		fff >> tmp[i];
	tmp[n] = nw;
	int cnt{ n };

	for (int i = n + 1;; ++i)
	{
		fff >> tmp[i];
		cnt++;
		if (fff.eof())
			break;
	}
	fff.close();
	ofstream ggg(f, ios::trunc);
	for (int i = 0; i < cnt; ++i)
		ggg << tmp[i];
	ggg.close();
}

void changeOneElByEl(const Swimming& old, const Swimming& nw) {
	int cnt{ 0 };
	Swimming *tmp = giveMemory<Swimming>(1000000);
	ifstream fff(f);
	for (int i = 0;; ++i) {
		fff >> tmp[i];
		if (tmp[i] == old)
			tmp[i] = nw;
		if (fff.eof())
			break;
		++cnt;

	}
	fff.close();
	ofstream ggg(f, ios::trunc);
	for (int i = 0; i < cnt; ++i)
		ggg << tmp[i];
	ggg.close();
}
Swimming* initArrOfFile(int &c) {
	c = findCnt();
	Swimming *arr = giveMemory<Swimming>(c);
	ifstream fff(f);
	for (int i = 0; i < c; ++i)
		fff >> arr[i];
	fff.close();
	return arr;
}
void outToFile(Swimming *arr, int n) {
	ofstream fff(f, ios::trunc);
	for (int i = 0; i < n; ++i)
		fff << arr[i];
	fff.close();
}
#endif