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
		void check(Time &c) {
		const type secMax = 60;
		const type minMax = 60;
		const type hrMax = 24;
		type mp;
		if (c.S < 0) {
			mp = 1 + abs(c.S / secMax);
			c.M -= mp;
			c.S = abs(c.S);
			c.S = c.S % (secMax);
			c.S = secMax - c.S;
		}
		if (c.M < 0) {
			mp = 1 + abs(c.M / minMax);
			c.H -= mp;
			c.M = abs(c.M);
			c.M = c.M % (minMax);
			c.M = minMax  - c.M;
		}
		if (c.H < 0) {
			c.H = abs(c.H);
			c.H = c.H % (hrMax);
			c.H = hrMax  - c.H;
		}

		if (c.S > (secMax-1)) {
			mp = c.S / (secMax);
			c.M += mp;
			c.S = c.S % (secMax);
		}
		if (c.M > (minMax-1)) {
			mp = c.M / (minMax);
			c.H += mp;
			c.M = c.M % (minMax);
		}
		if (c.H > (hrMax-1))
			c.H = c.H % (hrMax);
	}
	/*void checkMinus(Time &c) {
		const type secMax = 59;
		const type minMax = 59;
		const type hrMax = 23;
		type mp;
		if (c.S < 0) {

			--c.M;
			c.S = abs(c.S);
		}
		if (c.M < 0) {
			mp = c.M / (minMax+1);
			--c.H;
			c.M = abs(c.M);
		}
		if (c.H < 0)
			c.H = abs(c.H);
	}*/
public:
	//конструктор по умолчанию
	Time() :H{ 0 }, M{ 0 }, S{ 0 }//список иницилизации 
	{ cout << "defolt constuctor" << '\n'; }

	//Time(const Time& c) :H{ c.H }, M{ c.M }, S{ c.S }{	}
		
	
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
	type GetH() const { return H; };
	void SetM(type t) {
		const type minMax = 59;
		if (t > minMax) {
			type tmp = t / minMax;
			H += tmp;
			M = t % minMax;
		}
		else
			M = t;
	};
	type GetM() const { return M; };
	
	void SetS(type t) {
		const type secMax = 59;
		if (t > secMax) {
			type tmp = t / secMax;
			M += tmp;
			S = t % secMax;
		}
		else
			S = t;
	};
	type GetS() const { return S; };
	 Time&  operator = (const Time& c) {
		this->H = c.H;
		this->M = c.M;
		this->S = c.S;
		return *this;
	}

	Time  operator + (const Time c)  {

		Time tmp{ c.H + H,c.M + M, c.S + S };
		check(tmp);
		return (tmp);

	}
	Time  operator += (const Time c) {

		this->H += c.H;
		this->M += c.M;
		this->S += c.S;
		check(*this);
		return *this;

	}
	Time  operator -= (const Time c) {

		this->H -= c.H;
		this->M -= c.M;
		this->S -= c.S;
		check(*this);
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
		if (c.H)
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
		check(tmp);
		return (tmp);
	}Time  operator - (type c) {
		Time tmp{ H - c,M - c, S - c };
		check(tmp);
		return (tmp);
	}
	Time  operator / (const Time c) {

		Time tmp;
		if (c.S)
			tmp.S = S / c.S;
		else
			tmp.S = S;
		if (c.M)
			tmp.M = M / c.M;
		else
			tmp.M = M;
		if (c.H)
			tmp.H = H / c.H;
		else
			tmp.H = H;
		check(tmp);
		return (tmp);
	}
	Time  operator / (const type c) {

		Time tmp;
		if (c) {
			tmp.S = S / c;

			tmp.M = M / c;

			tmp.H = H / c;
		}
		check(tmp);
		return (tmp);
	}
	friend ostream& operator << (ostream & os, const Time c)
	{
		os << "Time" << c.H << ':' << c.M << ':' << c.S;
		return os;
	}
	friend istream& operator >> (istream & os,  Time &  c)
	{
		
		os >> c.H;
		os >> c.M;
		os >> c.S;
		c.check(c);
		return os;
	}
	bool operator > (const Time c)  {
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
	Time a{ 23,59,0 };
	Time b{ 0,0,100};
	Time c{ -1,-1,-1 };
	cout << "haha " << c;
	//setlocale(LC_ALL, "Russian");
	//const int n{ 10 };
	//Time c{ a };


	//Time a{ 0,58,0 };//иницилизируем
	//Time b{ 0,68,25 };
	//Time w;
	//Time m{ a };//иницилизируем уже сущ объктом
	//cout << "m=a" << m;
	//w = a + b;
	//cout << "w=a+b" << w;
	//w = a + 5;
	//cout << "w=a+5" << w;
	//w = b - a;
	//cout << "w=b-a" << w;
	//w = a * b;
	//cout << "w=a*b" << w;
	//w = a * 5;
	//cout << "w=a*5" << w;
	//w = a / b;
	//cout << "w=a/b" << w;
	//Time arr[n];
	//Time *arrr = new(nothrow) Time[n];
	//if (!arrr) {
	//	cout << "very bad";
	//	exit;
	//}
	//for (int i = 0; i < n; ++i) {
	//	*(arrr + i) = Time{ i,i + 58,i };
	//	cout << *(arrr + i);
	//}
	//cout << '\n' << '\n';
	//cout << '\n' << "bool " << (*(arrr + 5) > *(arrr + 6)) << ' ';
	//cout << '\n' << "bool " << (*(arrr + 5) < *(arrr + 6)) << ' ';
	//Time *ptr = new (nothrow) Time;
	//if (!ptr) {
	//	cout << "very bad";
	//	exit;
	//}
	//*ptr = Time{ 25,61,62 };
	//cout << ptr << ' ' << (*ptr);
	//cout << c.getPeriod();


	//Time e{ 9,25,65 };
	//cout << e.getPeriod();
	//cin >> e;
	//cout << e.getPeriod() << '\n';
	//Time haha{ 15, 25, 36 };
	//cout << e + haha, '\n';
	//Time hahaha = 156;
	
	//cout << e;
	//Time nnn{ 15,25,69 };
	//Time mmm{ 23,55,85 };
	//mmm += nnn;
	//cout << "MMMM=" << mmm;
	//mmm /= nnn;
	//cout << "MMMM=" << mmm;
	//Time aaaa{ a };
	//cout << '\n' << "a=" << a;
	//cout << '\n' << "aaaa=" << c;
}
