// DZ290319TMP.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*В тексте выбрать все слова, начинающиеся с заданной буквы, и расположить их в порядке убывания количества букв в слове.*/
#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<fstream> // подключение библиотеки файлового ввода/вывода через потоки
using namespace std;

const int N = 200;
void free_array(char **arr, int n) {
	for (int i = 0; i < n; ++i) {
		delete[] arr[i];
		arr[i] = nullptr;
	}
	delete[] arr;
	arr = nullptr;
}
void swapuk(char *a, char *b)
{
	char* tmp = new (nothrow) char[N];
	strcpy(tmp, b);
	strcpy(b, a);
	strcpy(a, tmp);
}

int firstshg(char **arr, char n) {
	char *tmp;
	//char *tmp2{ NULL };

	char *buff = new (nothrow) char[N];
	if (!buff) {
		cout << "very bad";
		exit;
	}
	ifstream fffff("D:\\VisualStudioProject\\4-1\\text2.txt"); // отсюда читаем (поток типа ifstream= input file stream)
	ofstream ggggg("D:\\VisualStudioProject\\4-1\\sher.txt");//сюда пишем (поток типа ofstream= output file stream)
	if (!fffff)
	{
		cout << "No file D:\VisualStudio project\Sherlock\sher.txt. Can't open\n";
		exit(1);
	}
	if (!ggggg)
	{
		cout << " file D:\VisualStudio project\Sherlock\text2.txt. Can't create\n";
		exit(1);
	}

	int cnt = 0;
	while (1)
	{
		fffff.getline(buff, N - 1); //читаем ПОСТРОЧНО.
  //Если будет в строке файла больше N-1 символов, то getline() поместит в буфер N-1 символов, в конец поместит '\0', установит флаг ошибки (failbit), поток станет нерабочим, не введённое останется в очереди ввода.
		if (fffff.fail())
			fffff.clear(); //getline при переполнении выставляет бит состояния =1. Его проверяем fail'ом. А потом подчищаем буфер
   //cout << buff << '\n'; //на экран
		tmp = strtok(buff, " ");
		while (tmp != 0)
		{
			if (tmp[0] == n)
			{
				*(arr + cnt) = new (nothrow) char[N];
				strcpy(*(arr + cnt), tmp); // запоминаю слова которые нужны
				cout << *(arr + cnt) << endl;
				cnt++;
			}
			tmp = strtok(0, " ,.!?");
		}
		
		if (fffff.eof())
			break; //читаем пока не кончится исходный файл. Т.е. пока не прочитаем EOF.
   //cout << '\n';//переход на новую строку пишем в date2.txt только, если в строке 16 мы прочитали действительно СТРОКУ (до endl), а не последнюю строку афйла в которой EOF, а не endl
	}
	delete[] buff;
	fffff.close();
	ggggg.close();
	return cnt;
}

void sort(char **arr, int n)
{
	bool flag{ 0 };
	for (int i = 0; i < n; i++)
	{
		flag = 1;
		for (int j = 0; j < n - i - 1; j++)
		{
			if (strlen(*(arr + j)) < strlen(*(arr + j + 1)))
			{
				flag = 0;
				swapuk(*(arr + j), *(arr + j + 1));
			}
		}
		if (flag)
			break;
	}
}
void secondshg(char **arr, char n) {
	char *tmp;
	//char *tmp2{ NULL };

	char *buff = new (nothrow) char[N];
	if (!buff) {
		cout << "very bad";
		exit;
	}
	ifstream ffff("D:\\VisualStudioProject\\4-1\\text2.txt"); // отсюда читаем (поток типа ifstream= input file stream)
	ofstream gggg("D:\\VisualStudioProject\\4-1\\sher.txt");//сюда пишем (поток типа ofstream= output file stream)
	if (!ffff)
	{
		cout << "No file D:\VisualStudio project\Sherlock\sher.txt. Can't open\n";
		exit(1);
	}
	if (!gggg)
	{
		cout << " file D:\VisualStudio project\Sherlock\text2.txt. Can't create\n";
		exit(1);
	}

	int cnt = 0;

	while (1) // второй раз прохожу и вставляю слова
	{
		ffff.getline(buff, N - 1); //читаем ПОСТРОЧНО.
  //Если будет в строке файла больше N-1 символов, то getline() поместит в буфер N-1 символов, в конец поместит '\0', установит флаг ошибки (failbit), поток станет нерабочим, не введённое останется в очереди ввода.
		if (ffff.fail())
			ffff.clear(); //getline при переполнении выставляет бит состояния =1. Его проверяем fail'ом. А потом подчищаем буфер
   //cout << buff << '\n'; //на экран
		tmp = strtok(buff, " .,!?");
		while (tmp != 0)
		{
			if (tmp[0] == n) {
				tmp = *arr;
				cout << tmp << ' ';
				arr++;
			}
			cout << tmp << ' ';
			gggg << tmp << ' ';
			tmp = strtok(0, " ");
		}
		cout << endl;
		if (ffff.eof())
			break; //читаем пока не кончится исходный файл. Т.е. пока не прочитаем EOF.
		gggg << '\n';//переход на новую строку пишем в date2.txt только, если в строке 16 мы прочитали действительно СТРОКУ (до endl), а не последнюю строку афйла в которой EOF, а не endl
	}

	//cout << "-----In file " << cnt << " lines";
	delete[] buff;
	ffff.close();//закрыли файл
	gggg.close();//закрыли файл
}


int main()
{
	setlocale(LC_ALL, ".1251");
	const int M = 10000;
	char n='д';	
	cout << n;
	char **arr = new (nothrow) char*[M];
	if (!arr) {
		cout << "very bad";
		exit;
	}
	
	int cnt = firstshg(arr, n);

	sort(arr, cnt); //сортирую
	cout << endl << endl << endl;
	for (int i{ 0 }; i < cnt; ++i)
		cout << *(arr + i) << endl;
	cout << '\n';
	cout << '\n';
	cout << '\n';
	secondshg(arr, n);//это что???? Здесь прохожу по тексту второй раз и расставляю слова в нужном мне порядке
	free_array(arr, cnt);
}
