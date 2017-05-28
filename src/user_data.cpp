#include <iostream>
#include <string>
#include <cstdlib>
#include "user_data.h"

using namespace std;

void error(int err_no) //Вывод ошибок
{ 
	switch(err_no) 
	{
		case 0: 	
			cout << "Значение некорректно." << endl; 
			break;
		case 1: 
			cout << "Задано менее двух ограничений, измените данные." << endl; 
			break;
		case 2: 	
			cout << "Задано более ста ограничений, измените данные." << endl; 
			break;
		case 3:
			cout << "Задано менее двух переменных, измените данные." << endl;
			break;
		case 4: 
			cout << "Задано более ста ограничений, измените данные." << endl; 
			break;
	}
}

void user_data::get_data() //Запрос данных от пользователя
{
	string sn, dir; // sn - sign, dir - direction
	int i, j;
	bool flag = false;
	
	do { 
		cout << "Введите количество ограничений: ";
		cin >> num_l;
		if (num_l < 2) error(1);
		else if (num_l > 100) error(2);
			else flag = true;
	} while (!flag);

	flag = false;
	
	do {
		cout << "Введите количество переменных: ";
		cin >> num_v;
		if (num_v < 2) error(3);
		else if (num_v > 100) error(4);
			else flag = true;
			} while (!flag);

	flag = false;
	
	function = new double [num_v];
	system = new double *[num_l];
	for (i = 0; i < num_l; i++)
		system[i] = new double [num_v];  
	fm = new double [num_l];
	sign = new int [num_l];

	cout << "Введите коэффициенты при целевой функции: " << endl;
	for (i = 0; i < num_v; i++) 
	{
		cout << "При х[" << i + 1 <<"] : ";
		cin >> function[i];
	}
	
	do {
		cout << "Направление целевой функции ( min, max ) : ";
		cin >> dir;
		if (dir == "max" || dir == "MAX" || dir == "min" || dir == "MIN") 
		{
			flag = true;
			if (dir == "max" || dir == "MAX") 	direction = true;
			else direction = false;
		}
		else error (0);
	} while (!flag);

	cout << "Система ограничений: " << endl;
	for (i = 0; i < num_l; i++) 
	{
		cout << "Заполните " << i + 1 << "-е ограничение: " << endl;
		for (j = 0; j < num_v; j++) 
		{
			cout << "Введите коэффициент при x[" << j + 1 <<"] : ";
			cin >> system[i][j];
		}

		do {
			cout << "Введите знак при " << i + 1 << "-м ограничении ( <=, =, >= ) : ";
			cin >> sn;
			if (sn == "<=" || sn == "=" || sn == ">=") 
			{
				flag = true;
				if (sn == "<=")	sign[i] = 0; 
				if (sn == "=")	sign[i] = 1;
				if (sn == ">=")	sign[i] = 2; 
			}
			else error(0);
		} while (!flag);

		flag=false;

		cout << "Введите свободный член при " << i + 1 << "-м ограничении: ";
		cin >> fm[i];
	}
}
