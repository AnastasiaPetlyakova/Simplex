#ifndef _USER_DATA_H_
#define _USER_DATA_H_

class user_data 
{ 
	public:
		void get_data(); //Запрос данных 
	protected:
		double *function; //Коэффициенты целевой функции
		double *fm; //Значения свободных членов 
		double **system; //Коэффициенты системы ограничений
		int *sign; //Знак ограничений (0 - <=. 1 - =, 2 - >=)
		int num_v; //Количество переменных 
		int num_l; //Количество ограничений
		bool direction; //true, если максимум; false, если минимум
}; 
#endif /* _USER_DATA_H_ */
