#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<ctime>
#include <fstream>
#include <cstring>
#include"Swimming.h"
#include <Windows.h>//����������� ��� setConsole
using namespace std;

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


int main()
{
	SetConsoleCP(1251); // ���� � ������� � ��������� 1251
	SetConsoleOutputCP(1251); // ����� �� ������� � ���������
	int k{ 0 };//���-�� ���������
	int n;
	bool flag{ true };
	int countId{ 0 };
	Swimming *arr = giveMemory<Swimming>(1);
	while (1) {
		cout << "0-����� �� ���� 1 -  ��������������� �� ����� 2 - ��������� ������������ 3- ��� ������� ,4 -������ �� �������������� �� ������ ";
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
				sortById(arr, 0, k - 1);
				countId = cntId(arr, k);
				cout << '\n' << k;
				cout << '\n' << countId;
				flag = false;
				break;
			case 2:
				cout << "������� ���-�� ����������";
				cin >> k;
				freeMemory<Swimming>(arr);
				arr = giveMemory<Swimming>(k);
				cout << "���-�� ��������";
				cin >> countId;
				randArr(arr, k, countId);
				flag = false;
				break;
			case 3:
				cout << "������� ���-�� ����������";
				cin >> k;
				freeMemory(arr);
				arr = giveMemory<Swimming>(k);
				for (int i = 0; i < k; ++i)
					cin >> arr[i];
				sortById(arr, 0, k);
				countId = cntId(arr, k);
				flag = false;
				break;
			case 4:
				flag = false;
				break;
			default:
				cout << "�������� ��������. ���������� ��� ���";
				break;
			}
		}
		if (!n)
			break;
		flag = true;
		Swimming *arr1 = giveMemory<Swimming>(1);

		cout << "1- ������������� � ������ ������� �� �����������; 2- ������ ������ ����������� � ������ ������� 3- �������� ���� ��-� � ����� �� �������� �� 4-��������� � ������� ��������� ������ ��� ����� 5- ������� �� ����� ����� ����������������� ������ 6-������� � ���� ����� ����������������� ������ ";

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
					cout << "����� �������";
					cin >> b;
					if (b > countId) // ����� �������
						cout << "������ ������� ���";
					else
						break;
				}

				freeMemory(arr1);
				arr1 = Swim(arr, k, b, cnt);
				flag = false;
				break;
			case 2:
				cnt = countId * 3;
				freeMemory(arr1);
				arr1 = ResSwim(arr, k, countId, aver);
				flag = false;
				break;
			case 3:
				cout << "��������� �������� ���� ��������";
				cin >> a3;
				cout << "��������� �� �������� ���� ��������";
				cin >> b3;
				changeOneElByEl(a3, b3);
				flag = false;
				break;
			case 4:
				cout << "����� �������";
				while (1) {
					cin >> b;

					if (b > countId) // ����� �������
						cout << "������ ������� ���";
					else
						break;
				}
				cout << "��� �����";
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
			default:
				cout << "�������� ��������. ���������� ��� ���";
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
				cout << "�������� ��������. ���������� ��� ���";
				break;
			}

		}
		flag = true;
	}
}