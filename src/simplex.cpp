#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include "user_data.h"
#include "simplex.h"

using namespace std;

void simplex::initialize() //Инициализация симплекс-таблицы
{
	int i, j;
	func = 0;
	sv = new double *[num_l];
	for (i = 0; i < num_l; i++) 
		sv[i] = new double [num_v];
	for (i = 0; i < num_l; i++) 
		for (j = 0; j < num_v; j++) 
			if (sign[i] == 2) sv[i][j] = system[i][j] * (-1);
			else sv[i][j] = system[i][j];
	istr = new double [num_v];
	free = new int [num_v];
	for (i = 0; i < num_v; i++) 
			free[i] = i;
	bv = new double * [num_l];
	for (i = 0; i < num_l; i++) 
		{
			bv[i] = new double [2]; //Матрица из двух столбцов - в одном хранятся номера переменных, в другом - их значения 
			bv[i][0] = i + num_v;
			if (sign[i] == 2) bv[i][1] = fm[i] * (-1); //Если >=, замена знаков на противоположные
			else bv[i][1] = fm[i];
		}
	for (i = 0; i < num_v ; i++)
		if (direction) istr[i] = function[i];
		else istr[i] = function[i] * (-1); //Если поиск максимума, замена знаков на противоположные
}
		
	
void simplex::print_result() //Вывод начальных данных, формирование исходной симплекс-таблицы и поиск опорного решения
{ 
	int i, j, k;
	double max;
	bool flag=true;
	
	cout << "\n\nЗадана целевая функция:" << endl;
	cout << "f(x) = "; 
	for (i = 0; i < num_v; i++)
	{
		if (function[i] == 1) 
			if (!i) cout << "x[" << i+1 << "] ";
			else cout << "+ x[" << i+1 <<"] ";
		else if (function[i] == (-1)) cout << "- x[" << i+1 <<"] ";
	 	 	 else if (function[i] != 0) 
			   { 
			  		if (!i) cout << function[i] << "x[" << i+1 <<"] ";
			  		else if (function[i] > 0) cout << " + " << function[i] << "x[" << i+1 <<"] ";
			  			 else cout << function[i] << "x[" << i+1 << "] ";
				}
	}
	string minmax;
	if (direction) minmax = "max";	
	else minmax = "min";
	cout << "=> " << minmax << endl;
	
	cout << "\nЗадана система ограничений:" << endl;
	string math_sign;
	for (i = 0; i < num_l; i++) 
	{
		for (j = 0; j < num_v; j++) 
		{
			if (system[i][j] == 1) 
				if (!j) cout << "x[" << j+1 <<"] ";
				else cout << "+ x[" << j+1 <<"] ";
			else if (system[i][j] == (-1)) cout << "-x[" << j+1 << "] ";
				 else if (system[i][j] != 0)  
				 		if (!j) cout << system[i][j] << "x[" << j+1 << "] ";
						else if (system[i][j] > 0) cout << "+ " << system[i][j] << "x[" << j+1 << "] ";
			  				else cout << system[i][j] << "x[" << j+1 <<"] ";
		} 	 	
		if (!sign[i])	math_sign = "<=";
		if (sign[i] == 1) math_sign = "=";
		if (sign[i] == 2) math_sign = ">=";	
		cout << math_sign << " " << fm[i] << endl;
	}
	
	cout << "\nКанонический вид:" << endl;
	cout << "f(x) = ";
	for (i = 0; i < num_v; i++)
	{
		if (direction) 
		{
			if (function[i] == 1) cout << "- x[" << i+1 <<"] ";
			else if (function[i] == (-1)) cout << "x[" << i+1 << "] ";
	 	 		 else if (function[i]!=0) 
				   { 
				   		if (!i) cout << " - " << function[i] << "x[" << i+1 <<"] ";
						else if (function[i] > 0) cout << " - " << function[i] << "x[" << i+1 <<"] ";
			  				else cout << " - " << function[i] << "x[" << i+1 <<"] ";
					}
		}
		else  
		{	
			if (function[i] == 1) 
				if (!i) cout << "x[" << i+1 <<"] ";
				else cout << " + x[" << i+1 <<"] ";
			else if (function[i] == (-1)) cout << " - x[" << i+1 <<"] ";
				else if (function[i] != 0) 
				{ 
			  		if (!i) cout << function[i] << " + x[" << i+1 <<"] ";
			  		else if (function[i] > 0) cout << "+ " << function[i] << "x[" << i+1 <<"] ";
			  			else cout << function[i] << " x[" << i+1 <<"] ";
				}
		}
	}

	if (!direction) minmax = "max";	
	else minmax = "min";
	cout << "=> " << minmax << endl;
	
	for (i = 0; i < num_l; i++) 
	{
		for (j = 0; j < num_v; j++) 
		{
			if (system[i][j] == 1) 
				if (!j) cout << "x[" << j+1 <<"] ";
				else cout << " + x[" << j+1 <<"] ";
			else if (system[i][j] == (-1)) cout << "- x[" << j+1 << "] ";
			   	else if (system[i][j] != 0)  
			  		if (!j) cout << system[i][j] << "x[" << j+1 <<"] ";
			  		else if (system[i][j] > 0) cout << " + " << system[i][j] << "x[" << j+1 <<"] ";
			  			else cout<<system[i][j]<<"x["<<j+1<<"] ";
		}
	if (bv[i][1] > 0) cout << "+ x["<< bv[i][0]+1 << "] ";
	if (bv[i][1] < 0) cout << "- x["<< bv[i][0]+1 <<"] ";
	cout << " = " << fm[i] << endl;}
			
	cout << "\nСоставим исходную симплекс-таблицу." << endl;
	cout << "\t" << "s\t";
	for (i = 0; i < num_v; i++) cout << "x" << free[i] + 1 << "\t";
	cout << endl;	
	for (i = 0; i < num_l; i++) 
	{
		cout << "x" << bv[i][0] + 1 << "\t" << bv[i][1] << "\t";
		for (j = 0; j < num_v; j++) cout << sv[i][j] << "\t"; 
		cout << endl;
	}
	cout << "f(x)\t" << func << "\t";
	for (i = 0; i < num_v; i++) cout << istr[i] << "\t";
	cout << "\n\nf(x) = ";
	if ((!direction) or (func == 0)) cout << func << endl; 
	else cout << (-func);
	for (i = 0; i < num_l; i++) cout << "x[" << bv[i][0] + 1 << "] = " << bv[i][1] <<endl; 
	iter=0;
	
	while (!plan_valid()) {
		cout << "Решение недопустимо, среди значений базисных переменных есть отрицательное.\n";
		k = -1; 
		i_lcol = -1; 
		max = 0; 
		iter++;
		for (i = 0; i < num_l; i++)	if ((bv[i][1] < 0) && (bv[i][1] < max)) //Поиск минимального (максимального по модулю) отрицательного элемента в столбце свободных членов 
		{
			max = bv[i][1]; 
			k = i;
		}
		max = 0;
    	for (j = 0; j < num_v; j++) if ((sv[k][j] < 0) && (sv[k][j] < max)) //Поиск минимального (максимального по модулю) отрицательно элемента в строке k
		{ 
			max = sv[k][j]; 
			i_lcol = j;
		}
		if (i_lcol == (-1))
		{
			cout << "Задача не имеет допустимых решений" << endl;	
			flag = false;
		}
		if (flag) exchange();
	}
	
	if (flag) cout << "\nДанное решение является опорным." << endl;
}
	
bool simplex::plan_valid() //Проверка на допустимость
{
    int i;
    bool result = true;
    for (i = 0; i < num_l; i++) if (bv[i][1] < 0) 
	{
		result = false; 
		break;
	}
	return result;
}

bool simplex::function_is_undefined() //Проверка на ограниченность функции
{   
	int i, k, j;
    bool result = true;
    k = -1;
    for (i = 0; i < num_v; i++) 
	{
		if (istr[i] > 0) 
		{
			k=i;
			break;
		}
		for (j = 0; j < num_l; j++)
		if (sv[i][k] <= 0) 
		{
			result = false; 
			break;
		}
	}
	return result;
 }

bool simplex::not_optimized() //Проверка на оптимизируемость
{
	int i;
    bool result = true;
    for (i = 0; i < num_v; i++) if (istr[i] > 0) 
	{
		result = false; 
		break;
	}
	return result;
}

void simplex::exchange()
{
	int i, j;
	double A, B, min;
	i_lrow = -1;
	th = new double [num_l];
	for (i = 0; i < num_l; i++)
	if (sv[i][i_lcol] != 0) th[i] = bv[i][1] / sv[i][i_lcol]; 
	else th[i] = -1;
	min = 1000000;
	for (i = 0; i < num_l; i++) if ((th[i] > 0) and (th[i] < min)) 
	{
		min = th[i]; 
		i_lrow = i;
	}
	cout << "\nРазрешающий столбец - " << i_lcol+1 << endl;
	cout << "Разрешающая строка - " << i_lrow+1 << endl;
	alm = sv[i_lrow][i_lcol];
	cout << "Разрешающий элемент - " << floor(alm * 100) / 100 << endl;
	cout << "\nИтерация №" << iter << endl;

	A = bv[i_lrow][1];
	B = istr[i_lcol];
	func -= A * B / alm;
	double *tmp_bv = new double [num_l];
	free [i_lrow] = bv [i_lrow][0];
	bv [i_lrow][0] = i_lcol;
	A = bv[i_lrow][1];
	for (i = 0; i < num_l; i++) 
	{
		B = sv[i][i_lcol];
		tmp_bv[i] = bv[i_lrow][1];
		if (i != i_lrow) tmp_bv[i] = bv[i][1] - A * B / alm;
		else tmp_bv[i] /= alm; 
	}
	for (i = 0; i < num_l; i++) bv[i][1] = tmp_bv[i];
	double *tmp_istr = istr;
	B = istr[i_lcol];
	for (i = 0; i < num_v; i++) 
	{
	A = sv[i_lrow][i];
	if (i != i_lrow) tmp_istr[i] = istr[i] - A * B / alm;
	else tmp_istr[i] /= - alm;
	}
	for (i = 0; i < num_l; i++) istr[i] = tmp_istr[i]; 
	double **tmp_sv = new double *[num_l];
	for (i = 0; i < num_l; i++) tmp_sv[i] = new double [num_v];
	for (i = 0; i < num_l; i++)
		for (j = 0; j < num_v; j++) 
		{
			tmp_sv[i][j] = sv[i][j]; 
			A = sv[i_lrow][j]; 
			B = sv[i][i_lcol];
			if (i == i_lrow) 
				if (j == i_lcol) tmp_sv[i][j] = 1/alm;
				else tmp_sv[i][j] /= alm;
			else if (j == i_lcol) tmp_sv[i][j] /= (-alm);
				 else tmp_sv[i][j] = sv[i][j] - A * B / alm;
		}
	for (i = 0; i < num_l; i++) 
		for (j = 0; j < num_v; j++) sv[i][j] = tmp_sv[i][j];
		
	
		
	cout << iter << "-я симплекс-таблица:" << endl;
	cout << "\t" << "s\t";
	for (i = 0; i < num_v; i++) cout << "x" << free[i] + 1 << "\t";
	cout << endl;
	for (i = 0; i < num_l; i++) 
	{
		cout << "x" << bv[i][0] + 1 << "\t" << floor(bv[i][1] * 100) / 100 << "\t";
		for (j = 0; j < num_v; j++)	cout << floor(sv[i][j] * 100) / 100 << "\t";
		cout << endl;
	}
	cout << "f(x)\t" << floor(func * 100) / 100 << "\t";
	for (i = 0; i < num_v; i++)	cout << floor(istr[i] * 100)/ 100 << "\t";
	cout << "\n"; 
	cout << "\nf(x) = ";
	if ((!direction) or (func == 0)) cout << floor(func * 100) / 100<<endl; 
	else cout << -floor(func * 100) / 100 << "\n" << endl;
	for (i = 0; i < num_l; i++) cout << "x" << bv[i][0] + 1 << " = " << floor(bv[i][1] * 100) / 100 << endl;
	
}


void simplex::optimize() //Оптимизация опорного решения
{
	int i,j;
	double max;
	i_lcol = -1; 
	iter = 0;
	
	while(!not_optimized()) {
		cout << "\nРешение может быть улучшено." << endl;
		max=0; 
		iter++;
		for (i = 0; i < num_v; i++) if ((istr[i] > 0) && (istr[i] > max)) 
		{
			i_lcol = i; 
			max = istr[i];
		}
	exchange();
	}

	if (!function_is_undefined()) cout << "\nРешение оптимально." << endl;
	else cout << "Функция не ограничена, решения не существует" << endl;
}	
	
void simplex::clear() //Очистка памяти
{
	for (int i = 0; i < num_l; i++)
		delete bv[i];
	delete [] bv;
	for (int i = 0; i < num_v; i++)
		{
			delete system[i];
			delete sv[i];
		}
	delete [] sv;
	delete [] system;
	delete [] istr;  
	delete [] function; 
	delete [] fm; 
	delete [] sign;
	delete [] free;
}

