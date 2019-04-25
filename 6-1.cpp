// 6-11.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*
Класс время. Операция - вывести что сейчас хранится в объекте: сейчас утро, день,вечер или ночь.
*/

#include "pch.h"
#include <iostream>
#include<string>
using namespace std;
typedef int type;

class Time {
private:
	type H;
	type M;
	type S;
	static void check(Time &c) {// хочу УСЛЫШАТЬ на паре обоснование зачем тут static
		const type secMax = 60;
		const type minMax = 60;
		const type hrMax = 23;
		type mp;
		if (c.S > secMax) {
			mp = c.S / secMax;
			c.M += mp;
			c.S = c.S % secMax;
		}
		if (c.M > minMax) {
			mp = c.M / minMax;
			c.H += mp;
			c.M = c.M % minMax;
		}
		if (c.H > hrMax)
			c.H = c.H % hrMax;
	}
	void checkMinus(Time &c) {// хочу УСЛЫШАТЬ на паре обоснование почему тут НЕ static
		const type secMax = 60;
		const type minMax = 60;
		const type hrMax = 23;
		type mp;
		if (c.S < 0) {

			--c.M;
			c.S = abs(c.S);
		}
		if (c.M < 0) {
			mp = c.M / minMax;
			--c.H;
			c.M = abs(c.M);
		}
		if (c.H < 0)
			c.H = abs(c.H);
	}
public:
	//конструктор по умолчанию
	Time() :H{ 0 }, M{ 0 }, S{ 0 }//список иницилизации 
	{ cout << "defolt constuctor" << '\n'; }


	Time(type a, type b = 0, type c = 0) :H{ a }, M{ b }, S{ c }//список иницилизации 
	{		
		check(*this);
		cout << "constreu" << '\n';
	}
	~Time() { std::cout << "Work destructor for" << H << " " << M << " " << S << '\n'; };
	void SetH(type t) { //чтоб не было больше 23 часов(в сутках больше быть не может) 
		const type hrMax = 23;
		if (t > hrMax)
			H = t % hrMax;
		else
			H = t;

	};
	type GetH() { return H; };
	void SetM(type t) {
		const type minMax = 60;
		if (t > minMax) {
			type tmp = t / minMax;
			H += tmp;
			M = t % minMax;
		}
		else
			M = t;
	};
	type GetM() { return M; };
	const type secMax = 60;
	void SetS(type t) {
		if (t > secMax) {
			type tmp = t / secMax;
			M += tmp;
			S = t % secMax;
		}
		else
			S = t;
	};
	type GetS() { return S; };
	const Time&  operator = (const Time& c) {
		this->H = c.H;
		this->M = c.M;
		this->S = c.S;
		return *this;
	}
	
	Time  operator + (const Time c) {

		Time tmp{c.H+H,c.M + M, c.S + S };
		check(tmp);
		return (tmp);
	}
	Time  operator += (const Time c) {

		this->H +=c.H;
		this->M += c.M;
		this->S += c.S;
		check(*this);
		return *this;
			
	}
	Time  operator -= (const Time c) {

		this->H -= c.H;
		this->M -= c.M;
		this->S -= c.S;
		checkMinus(*this);
		return *this;

	}
	Time  operator *= (const Time c) {

		this->H *= c.H;
		this->M *= c.M;
		this->S *= c.S;
		check(*this);
		return *this;

	}
	Time  operator /= (const Time c) {
		if(c.H)
		this->H /= c.H;
		if (c.M)
		this->M /= c.M;
		if (c.S)
		this->S /= c.S;
		return *this;

	}
	Time  operator + (const type c) {

		Time tmp{ c + H,c + M, c + S };
		check(tmp);
		return (tmp);
	}
	Time operator *(const Time c) {
		Time tmp{ c.H * H,c.M * M, c.S * S };
		
		check(tmp);

		return (tmp);
	}
	Time operator *(const type c) {
		Time tmp{ c* H,c* M,c* S };
		check(tmp);
		return (tmp);
	}
	Time  operator - (const Time c) {

		Time tmp{ H - c.H,M - c.M, S - c.S };
		checkMinus(tmp);
		return (tmp);
	}Time  operator - (type c) {
		Time tmp{ H - c,M - c, S - c };
		checkMinus(tmp);
		return (tmp);
	}
	Time  operator / (const Time c) {

		Time tmp;
		if (c.S)
			tmp.S = S / c.S;
		if (c.M)
			tmp.M = M / c.M;
		if (c.H)
			tmp.H = H / c.H;
		checkMinus(tmp);
		return (tmp);
	}
	Time  operator / (const type c) {

		Time tmp;
		if (c) {
			tmp.S = S / c;

			tmp.M = M / c;

			tmp.H = H / c;
		}
		checkMinus(tmp);
		return (tmp);
	}
	friend ostream& operator << (ostream & os, const Time c)
	{
		os << "Time" << c.H << ':' << c.M << ':' << c.S;
		return os;
	}
	friend istream& operator >> (istream & os, Time &c)
	{
		cout << '\n' << "Введите время";
		os >> c.H;
		os >> c.M;
		os >> c.S;
		check(c);
		return os;
	}
	bool operator > (const Time c) {
		if (H > c.H)
			return true;
		else if (H < c.H)
			return false;
		else {
			if (M > c.M)
				return true;
			else if (M < c.M)
				return false;
			else {
				if (S > c.S)
					return true;
				else
					return false;

			}
		}

	}
	bool operator < (const Time c) {
		if (H < c.H)
			return true;
		else if (H > c.H)
			return false;
		else {
			if (M < c.M)
				return true;
			else if (M > c.M)
				return false;
			else {
				if (S < c.S)
					return true;
				else
					return false;

			}
		}

	}
	bool operator ==(const Time c) {
		if ((H == c.H) && (M == c.M) && (S == c.S))
			return true;
		else
			return false;
	}
	string getPeriod() {//выводим что хранится в объекте

		if (H < 4)
			return "Ночь";
		else if (H < 10)
			return "Утро";
		else if (H < 18)
			return "День";
		else
			return "Вечер";
	}



};






int main()
{
	setlocale(LC_ALL, "Russian");
	const int n{ 10 };
	Time c{ 0,59,1 };

	Time a{ 0,58,0 };//иницилизируем
	Time b{ 0,68,25 };
	Time w;
	Time m{ a };//иницилизируем уже сущ объктом
	cout << "m=a" << m;
	w = a + b;
	cout << "w=a+b" << w;
	w = a + 5;
	cout << "w=a+5" << w;
	w = b - a;
	cout << "w=b-a" << w;
	w = a * b;
	cout << "w=a*b" << w;
	w = a * 5;
	cout << "w=a*5" << w;
	w = a / b;
	cout << "w=a/b" << w;
	Time arr[n];
	Time *arrr = new(nothrow) Time[n];
	if (!arrr) {
		cout << "very bad";
		exit;
	}
	for (int i = 0; i < n; ++i) {
		*(arrr + i) = Time{ i,i + 58,i };
		cout << *(arrr + i);
	}
	cout << '\n' << '\n';
	cout << '\n' << "Bool " << (*(arrr + 5) > *(arrr + 6)) << ' ';
	cout << '\n' << "Bool " << (*(arrr + 5) < *(arrr + 6)) << ' ';
	Time *ptr = new (nothrow) Time;
	if (!ptr) {
		cout << "very bad";
		exit;
	}
	*ptr = Time{ 25,61,62 };
	cout << ptr << ' ' << (*ptr);
	cout << c.getPeriod();


	Time e{ 9,25,65 };
	cout << e.getPeriod();
	cin >> e;
	cout << e.getPeriod()<<'\n';
	Time haha{ 15, 25, 36 };
	cout << e + haha,'\n';
	Time hahaha = 156;
	
	cout << e;
	Time nnn{ 15,25,69 };
	Time mmm{ 23,55,85 };
	mmm += nnn;
	cout<<"MMMM=" << mmm;
	mmm /= nnn;
	cout << "MMMM=" << mmm;

}
