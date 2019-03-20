﻿// 3-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*В строке найти слова, содержащие цифры, расположенные подряд, и заменить их **…. Вставить перед такими словами заданную подстроку*/

#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<cstring>
using namespace std;

char *giveMemory(int n) {
	char *a = new(nothrow) char[n];
	if (!a) {
		cout << "very bad";
		exit;
	}
	return a;
}
void freeMemory(char *a) {
	delete[] a;
	a = nullptr;

}
void initArrNull(int *arr, int n) {//иницилизируем массив
	for (int i = 0; i < n; i++) {
		*arr = 0;
		arr++;
	}
}
int *giveMemoryInt(int n) {
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

int fff(char *s, int *arr) {//заменяем цифру * и находим те места куда надо будет вставлять подстроку
	int len = strlen(s);
	int cnt{ 0 };
	int word{ 0 };
	//char *tmp = s;
//	int i{ 0 };
	char flag = 0;
	int i{ 0 };
	while (*s) {
		i++;
		if ((*s > 47) && (*s < 58)) {
			s++;
			i++;
			if ((*s > 47) && (*s < 58)) {
				*s = '*';
				s--;
				*s = '*';
				s += 2;
				i++;
				flag = 1;
				while ((*s > 47) && (*s < 58)) {
					*s = '*';
					s++;
					i++;
				}
			}
		}
			if (*s == ' ') {
					if (flag) {// т.е если в слове были две подряд цифры то запоминаем номер  куда надо вставлять подстроку
					if (word)
					*arr = word;
					arr++;
					cout << 'j' << '\n';
					flag = 0;
					cnt++;
				}
				word = i;
			}
			s++;
		}
		if (flag) {
			*arr = word;
			arr++;
		}
		*arr = len;// последний элемент массива будет длина строки
		return cnt;
	}
void printarr(int *arr, int n) {
	for (int i = 0; i < n; ++i) {
		cout << *(arr + i) << '\n';
	}
}
void insStr(char* s, int begin, char* sub)//Вставить в строку s с адреса begin подстроку sub.
{
	strcat(sub, s + begin);
	strcpy(s + begin, sub);
}
void subStr(char *s, char *rez, int begin, int end)//выделяет из строки s, начиная с символа begin, и заканчивая символом end
{
	int kol = end - begin;
	s = s + begin;
	strncpy(rez, s, kol);
	rez[kol] = '\0';
}
void insps(char *s, char *supers,  char *pstr, int *arr, int cnt) {
	int a = strlen(s);
	int f = strlen(supers);
	char *t = '\0';
	int n = strlen(pstr);
	char *tmp = new(nothrow) char[a];
	if (*arr) {//первый раз вставляем строку
		subStr(s, tmp, 0, *arr);
		insStr(supers, 0, tmp);
		insStr(supers, *arr, pstr);
	}
	else //если две цифры в первом слове
		insStr(supers, 0, pstr);
	
	int i{ 1 };
	//cout << *(arr + 1) << "   " << a;
	while (1) {
		if (*(arr + 1) == (a)) {//берем последний кусок из строки
			subStr(s, tmp, *arr, *(arr + 1)+1);
			insStr(supers, *arr + i * n, tmp);
			*(supers + a + i * n) = '\0';
			break;
		}
		subStr(s, tmp, *arr, *(arr+1));
		insStr(supers, *arr+i*n, tmp);
		insStr(supers, *arr + i * n + *(arr+1)-*arr, pstr);
		arr++;
		i++;
	}
}

int main()
{
	const int N{ 30 };
	const int MAX{ 100 };
	char buf[MAX], buf2[MAX];
	char *massOfWords[N];
	cout << "please enter line ";
	cin.getline(buf, MAX);
	char * str = new(nothrow) char[strlen(buf) + 1];
	strcpy(str, buf);
	cout<<"please enter second line";
	cin.getline(buf2,MAX);
	char * pstr = new(nothrow) char[strlen(buf2) + 1];
	strcpy(pstr, buf2);
	int *arr = giveMemoryInt(N);//будем хранить номера куда надо вставить подстроку
	initArrNull(arr, N);
	int cnt=fff(str, arr);
	int n = strlen(pstr);
	int lens = strlen(str);
	char *supers = new(nothrow) char[lens + n * cnt];
	cout << "new arr" << '\n';
	//printarr(arr, N);
	if(cnt)
	insps(str, supers, pstr, arr, cnt);
	cout << supers;
	freeMemory(arr);
    freeMemory(str);
	freeMemory(pstr);

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
