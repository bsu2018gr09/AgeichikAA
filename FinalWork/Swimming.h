#pragma once
#ifndef Swimming_H
#define Swimming_H
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<ctime>
#include <fstream>
#include <cstring>
#include <Windows.h>//обязательно для setConsole
using namespace std;
typedef int type;





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
	Swimming(const Swimming& c) : id{ c.id }, distance{ c.distance }, rez{ c.rez }, surname{ giveMemory<char>(strlen(c.surname) + 1) }
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

		os >> c.surname;
		os >> c.id;
		os >> c.distance;

		os >> c.rez;

		return os;
	}


};
#endif