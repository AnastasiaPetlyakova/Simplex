#ifndef _SIMPLEX_H_
#define _SIMPLEX_H_
#include <sstream>
#include "user_data.h"

class simplex:public user_data
{
	public:
		void initialize();//Инициализация исходной симплекс-таблицы
		void optimize();//Оптимизация
		bool plan_valid();//Проверка решения на допустимость
		bool not_optimized();//Проверка на оптимальность
		bool function_is_undefined();//Проверка на ограниченность
		void print_result();//Поиск опорного решения
		void exchange();//Перерасчет таблицы
		void clear();//Очистка памяти
	private:
		double func; //Значение целевой функции
		double **bv; //Значение базисных переменных
		double **sv; //Коэффициенты системы ограничений
		double *istr; //Коэффициенты целевой функции 
		double *th; //Отношение свободных членов к разрешающему столбцу
		double alm; //Разрешающий элемент
		int *free; //Массив с номерами свободных переменных
		int i_lrow; //Разрещающая строка
		int i_lcol; //Разрешающий столбец
		int iter;//Количество итераций
}; 
#endif /* _SIMPLEX_H_ */
