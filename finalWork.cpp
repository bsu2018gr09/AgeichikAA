#include"pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<ctime>
#include <fstream>
#include <cstring>
#include <Windows.h>//обязательно для setConsole

using namespace std;
typedef int type;
char f[] = "D:\\VisualStudio project\\7-1\\file.txt";
template <class T>
T* giveMemory(int n)
{
	T *arr = new (nothrow) T[n];
	if (!arr)
	{
		cout << "Can't give memory";
		exit;
	}
	return arr;
}

template <class T>
void freeMemory(T*& arr)
{
	delete[] arr;
	arr = nullptr;
}


class Swimming
{
private:
	int id;
	int distance;
	char* surname;
	type rez;

	void checkDistance()
	{

		int tmp{ this->distance % 50 };
		if (tmp)
		{
			if (tmp < 25)
				this->distance -= tmp;
			else
				this->distance += (50 - tmp);
		}
	}

public:

	Swimming() :id{ 0 }, distance{ 0 }, surname{ giveMemory<char>(4) }, rez{ 0 }
	{

		strcpy(surname, "Loh");
		//cout << "sw constr";
	}
	
	Swimming(int i, int d, char* s, type r) :id{ i }, distance{ d }, surname{ giveMemory<char>(strlen(s) + 1) }, rez{ r }
	{
		strcpy(surname, s);
		this->checkDistance();
		//cout << "sw constr";
	}
	~Swimming()
	{
		//delete[] surname;
		freeMemory(surname);
		//freeMemory<char>(surname);

	}


	Swimming& operator = (const Swimming& c)
	{
		if (this == &c)
			return *this;
		this->id = c.id;
		this->distance = c.distance;
		freeMemory<char>(surname);
		surname = giveMemory<char>(strlen(c.surname) + 1);
		strcpy(this->surname, c.surname);
		this->rez = c.rez;
		return *this;
	}
	Swimming(const Swimming& c): id{c.id}, distance{c.distance},rez{c.rez} ,surname{ giveMemory<char>(strlen(c.surname) + 1) }
	{
		if (this == &c)
			return;
		strcpy(this->surname, c.surname);
		this->rez = c.rez;
		return;
	}
	void SetId(int i)
	{
		id = i;
	}
	void SetDistance(int i)
	{
		distance = i;
		this->checkDistance();
	}
	void SetSurname(char* i)
	{
		strcpy(surname, i);
	}
	void SetTime(type c)
	{
		rez = c;
	}
	int GetId()
	{
		return id;
	}
	int GetDistance()
	{
		return distance;
	}
	char* GetSurname()
	{
		return surname;
	}
	type GetTime()
	{
		return rez;
	}
	void Rand(int id = 10, int dist = 500, int time = 530)
	{
		dist /= 50;
		this->id = rand() % id + 1;
		this->distance = (rand() % dist) * 50;
		this->SetTime(rand() % time + 30);
	}


	bool operator ==(const Swimming &c) {
		if (id != c.id)
			return false;
		if (rez != c.rez)
			return false;
		if (distance != c.distance)
			return false;
		if (strcmp(surname, c.surname))
			return false;
		return true;
	}
	bool operator !=(const Swimming &c) {
		if (id != c.id)
			return true;
		if (rez != c.rez)
			return true;
		if (distance != c.distance)
			return true;
		if (!strcmp(surname, c.surname))
			return true;
		return false;
	}


	friend ostream& operator << (ostream & os, const Swimming& c)
	{
		os << c.surname << ' ' << c.id << '	' << c.distance << ' ' << c.rez << '\n';
		return os;
	}
	friend istream& operator >> (istream & os, Swimming &  c)
	{

		os>>c.surname;
		os >> c.id;
		os >> c.distance;
		
		os >> c.rez;

		return os;
	}


};
/*
void RandT(Swimming a,int id = 10, int dist = 500, int time = 530)
{

	a.SetId(id);
	a.SetDistance(dist);
	a.SetTime(rand() % time + 30);
}

void randArr(Swimming *arr, int n, int cntid) {
	int dist{ 0 };
	for (int i = 0; i < cntid; ++i) {
		dist = rand() % 10 * 50;
		for (int j = 0; j<(n / cntid-1); ++j) {
			RandT(arr[i*n / cntid +j],i, dist,500);
		}
	}


}*/
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
					if (arr[j].GetTime() < win1.GetTime()){
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
int main()
{
	SetConsoleCP(1251); // Ввод с консоли в кодировке 1251
	SetConsoleOutputCP(1251); // Вывод на консоль в кодировке
	int k{ 0 };//кол-во элементов
	int n;
	bool flag{ true };
	int countId{0};
	Swimming *arr = giveMemory<Swimming>(1);
	while (1) {
		cout << "0-выйти из меню 1 -  иницилизировать из файла 2 - рандомная иницилизация 3- сам вводишь ,4 -ничего из перечисленного не делать ";
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
				cout << "Неверные значения. Попробуйте еще раз";
				break;
			}
		}
		if (!n)
			break;
		flag = true;
		Swimming *arr1 = giveMemory<Swimming>(1);

		cout << "1- отсортировать в нужном заплыве по результатам; 2- тройка лучших результатов в каждом заплыве 3- изменить один эл-т в файле на заданный эл 4-прибавить к каждому участнику заплва опр время 5- вывести на экран ранее иницилизированный массив 6-вывести в файл ранее иницилизированный массив ";

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
					if (b > countId) // номер заплыва
						cout << "Такого заплыва нет";
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
				cout << "Неверные значения. Попробуйте еще раз";
				break;
			}
			
		}
		flag = true;
	}
	//работа с файлами
	/*srand(time(0));
	Swimming a;
	for (int i = 0; i < 30; ++i) {
		readFile(a);
	}
	Swimming b;
	b.SetId(100);
	changeOneEl(b, 5);
	Swimming c;
	c.SetId(250);
	changeOneElByEl(b, c);
	*/
	//результаты заплыва
	/*Swimming *arr = giveMemory<Swimming>(1000);
	randArr(arr, 1000, 50);
	int c{ 0 };
	Swimming *arr1;
	arr1=Swim(arr, 1000, 23, c);
	printArr(arr1, c);
	*/
	//changeById(5, 45);
	/*
	//победители в заплыве
	int n{ 1000000 };
	Swimming *arr = giveMemory<Swimming>(n);
	randArr(arr, n, 50);
	int cnt{ 0 };
	int aver{ 0 };
	Swimming *win = ResSwim(arr, n, cnt, aver);
	printArr(win, cnt * 3);
	*/
	/*
	char *s = giveMemory<char>(5);
	strcpy(s, "leha");

	int c{ 100 };

	//writeFile(a);

	Swimming b(5, 150, s, c);
	//writeFile(b);

	strcpy(s, "DEn");
	Swimming nw(25, 150, s, c);
	b.SetSurname(s);
	//writeFile(b);

	//b.SetSurname(s);
	cout << a << endl;
	cout << b << endl;
	int cnt{ 0 };
	Swimming tmp;
	tmp.SetDistance(900);
	//readFile(tmp, 3);
	Swimming* arr = giveMemory<Swimming>(10000);
	for (int i = 0; i < 10000; ++i)
		arr[i].Rand();
	//randArr(arr, 100, 10);
	//Swimming *arr1 = Swim(arr, 10000, 9, cnt);
	cout << '\n';
	//printArr(arr1, cnt);
	cout << '\n';
	//cout << (arr1[0].GetTime() > arr1[1].GetTime());
	//cout << cnt;
	type aver{ 0 };
	Swimming *win = ResSwim(arr, 100, cnt,aver);
	printArr(win, cnt*3);
	cout << '\n';
	cout << aver;
	//changeOneEl(b,nw);
	cout << tmp;
	cout << '\n' << tmp.GetId() << tmp.GetDistance() << tmp.GetSurname() << tmp.GetTime() << '\n' << tmp.GetSurname();

	cin >> aver;
	*/
}
