/*В строке найти слова, содержащие цифры, расположенные подряд, и заменить их **…. Вставить перед такими словами заданную подстроку*/


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <clocale>
#include<cstring>
#include <Windows.h>//обязательно для setConsole
using namespace std;

char *giveMemory(int n) {
	char *a = new(nothrow) char[n];
	if (!a) {
		cout << "can't give memory";
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
		cout << "can't give memory";
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
	int cnt{ 0 }; // кол-во слов
	int word{ 0 }; //для временного хранения начала слово(одного)
	//char *tmp = s;
//	int i{ 0 };
	char flag = 0;
	int i{ 0 };
	for (int g = 0; g <= len; g++) {
		i++;// номер символа строки
		if ((*s > 47) && (*s < 58)) {
			s++; // s это массив строк
			i++;
			if ((*s > 47) && (*s < 58)) {
				*s = '*';
				s--;
				*s = '*';// заменяем цифру на строку
				s += 2;
				i++;
				flag = 1;
				while ((*s > 47) && (*s < 58)) { // если цифр больше двух то заменяем столько сколько надо
					*s = '*';
					s++;
					i++;
				}
			}
		}
		if (*s == ' ') {
			if (flag) {// т.е если в слове были две подряд цифры то запоминаем номер  куда надо вставлять подстроку
				if (word) //если это не первое слово
					*arr = word;
				arr++;
				cout << 'j' << '\n';
				flag = 0;
				cnt++;
			}
			word = i;//запоминаем начало слово с которым будем в последуещем работать
		}
		s++;
	}
	if (flag) { // для последнего слова так как в конце пробел не стоит
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
void delStr(char *s, int begin, int kol)//удаляет из строки  s,  начиная с символа begin,  kol символов.
{
	char *dest = s + begin, *from = s + begin + kol;
	//strcpy(p,q);// так- ПЛОХО. Если строки p и q перекрываются, то поведение функции strcpy() не определено!!!!

	 /*можно ручками скопировать*/
  //   while ( *dest++ = *from++ ); ++*dest = '\0';
	 /*можно использовать С++ STL*/
   //  copy(from,s+strlen(s)+1,dest);
	 /* можно как в С*/
	memmove(dest, from, s + strlen(s) + 1 - from);
}
void inL(char* str) {
	char tmp[] = " ";
	int n = strlen(str);
	insStr(str, n, tmp);

}
void insps(char *s, char *supers, char *pstr, int *arr, int cnt) {//s - первоначальная строка supers-строка в которую будем ставить pstr-подстрока arr-массив нужных нам начал слов cnt - кол-во сколько надо раз вставлять
	int a = strlen(s);
	int f = strlen(supers);

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

			subStr(s, tmp, *arr, *(arr + 1) + 1);
			insStr(supers, *arr + i * n, tmp);
			*(supers + a + i * n) = '\0';

			break;

		}
		subStr(s, tmp, *arr, *(arr + 1));
		insStr(supers, *arr + i * n, tmp);
		insStr(supers, *arr + i * n + *(arr + 1) - *arr, pstr);
		arr++;
		i++;
	}
}

int main()
{
	SetConsoleCP(1251); // Ввод с консоли в кодировке 1251
	SetConsoleOutputCP(1251); // Вывод на консоль в кодировке
	const int N{ 30 };
	const int MAX{ 100 };
	char buf[MAX], buf2[MAX];
	char *massOfWords[N];
	cout << "please enter line ";
	cin.getline(buf, MAX);

	char * str = new(nothrow) char[strlen(buf) + 2];
	strcpy(str, buf);
	inL(str);
	cout << "please enter second line";
	cin.getline(buf2, MAX);
	char * pstr = new(nothrow) char[strlen(buf2) + 1];
	strcpy(pstr, buf2);
	int *arr = giveMemoryInt(N);//будем хранить номера куда надо вставить подстроку
	initArrNull(arr, N);
	int cnt = fff(str, arr);
	int n = strlen(pstr);
	int lens = strlen(str);
	char *supers = new(nothrow) char[lens + n * cnt];
	//cout << "new arr" << '\n';
	printarr(arr, N);
	if (cnt)
		insps(str, supers, pstr, arr, cnt);
	else
		strcpy(supers, str);
	n = strlen(str);
	delStr(str, n, 1);
	cout << supers;
	freeMemory(arr);
	freeMemory(str);
	freeMemory(pstr);

}
