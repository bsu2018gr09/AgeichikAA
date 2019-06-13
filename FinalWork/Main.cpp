#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<ctime>
#include <fstream>
#include <cstring>
#include"Swimming.h"
#include <Windows.h>//обязательно для setConsole
using namespace std;


bool findId(Swimming* arr, int n, int id);
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
void addElFile(Swimming& n);


int main()
{
	SetConsoleCP(1251); // Ввод с консоли в кодировке 1251
	SetConsoleOutputCP(1251); // Вывод на консоль в кодировке
	int k{ 0 };//кол-во элементов
	int n;
	//bool ffllagg{0};
	bool flag{ true };
	int countId{ 0 };
	Swimming *arr = giveMemory<Swimming>(1);
	while (1) {
		cout << "0-выйти из меню "<<'\n'<<"1 -  иницилизировать из файла " << '\n' << 
			"2 - рандомная иницилизация" << '\n' << " 3- сам вводишь " << '\n' << 
			"4 -ничего из перечисленного не делать ";
		while (flag)
		{
			cin >> n;

			if (!n)
				break;
			switch (n)
			{
			case 1:
				freeMemory(arr);
				arr = initArrOfFile(k);
				if(k)
				sortById(arr, 0, k - 1);
				countId = cntId(arr, k);
				cout << '\n' << k;
				cout << '\n' << countId;
				flag = false;
				break;
			case 2:
				cout << "введите кол-во участников";
				cin >> k;
				freeMemory<Swimming>(arr);
				arr = giveMemory<Swimming>(k);
				cout << "кол-во заплывов";
				cin >> countId;
				randArr(arr, k, countId);
				flag = false;
				break;
			case 3:
				cout << "введите кол-во участников";
				cin >> k;
				cout << "пример: Name(одно слово)" << '\n' << " id" << '\n' << " distance" << '\n' << " time(кол-во секунд)";
				freeMemory(arr);
				arr = giveMemory<Swimming>(k);
				for (int i = 0; i < k; ++i) {
					cin >> arr[i];
					
				}
				sortById(arr, 0, k-1);
				countId = cntId(arr, k);
				flag = false;
				break;
			case 4:
				flag = false;
				break;
			default:
				cout << "Неверные значения. Попробуйте еще раз";
				break;
			}
		}
		if (!n)
			break;
		flag = true;
		Swimming *arr1 = giveMemory<Swimming>(1);

		cout << "1- отсортировать в нужном заплыве по результатам;" << '\n' << " 2- тройка лучших результатов в каждом заплыве " << '\n' << "3- изменить один эл-т в файле на заданный эл " << '\n' << "4-прибавить к каждому участнику заплва опр время" << '\n' << " 5- вывести на экран ранее иницилизированный массив" << '\n' << " 6-вывести в файл ранее иницилизированный массив " << '\n' << "7- добавить эл-т в файл";

		int aver{ 0 };
		int b{ 0 };
		int dif{ 0 };
		int cnt{ 0 };

		Swimming a3;
		Swimming b3;

		while (flag) {
			cin >> n;
			switch (n)

			{
			case 1:
					while (1) {
						cout << "номер заплыва";
						cin >> b;
						if (findId(arr,k,b)) // номер заплыва
							break;
						else
							cout << "Такого заплыва нет"; 
					}
				
				
				freeMemory(arr1);
				arr1 = Swim(arr, k, b, cnt);
				flag = false;
				break;
			case 2:
				if (k) {
					cnt = countId * 3;
					freeMemory(arr1);
					arr1 = ResSwim(arr, k, countId, aver);
				}
				flag = false;
				break;
			case 3:
				cout << "участника которого надо заменить";
				cin >> a3;
				cout << "участника на которого надо заменить";
				cin >> b3;
				changeOneElByEl(a3, b3);
				flag = false;
				break;
			case 4:
				cout << "номер заплыва";
				while (1) {
					cin >> b;

					if (b > countId) // номер заплыва
						cout << "Такого заплыва нет";
					else
						break;
				}
				cout << "доп время";
				cin >> dif;
				changeById(b, dif);
				flag = false;
				break;
			case 5:
				printArr(arr, k);
				flag = false;
				break;
			case 6:
				outToFile(arr, k);
				flag = false;
				break;
			case 7:
				cin >> a3;
				addElFile(a3);
				flag = false;
				break;
			default:
				cout << "Неверные значения. Попробуйте еще раз";
				break;
			}
		}
		flag = true;
		cout << "1-out console; 2-out file";
		while (flag) {
			cin >> n;

			switch (n)
			{
			case 1:
				printArr(arr1, cnt);
				flag = false;
				break;
			case 2:
				flag = false;
				outToFile(arr1, cnt);
				break;
			default:
				if(!n)

				cout << "Неверные значения. Попробуйте еще раз";
				break;
			}

		}
		flag = true;
	}
	
	freeMemory(arr);
}
