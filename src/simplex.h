#ifndef _SIMPLEX_H_
#define _SIMPLEX_H_
#include <sstream>
#include "user_data.h"

class simplex:public user_data
{
	public:
		void initialize();//������������� �������� ��������-�������
		void optimize();//�����������
		bool plan_valid();//�������� ������� �� ������������
		bool not_optimized();//�������� �� �������������
		bool function_is_undefined();//�������� �� ��������������
		void print_result();//����� �������� �������
		void exchange();//���������� �������
		void clear();//������� ������
	private:
		double func; //�������� ������� �������
		double **bv; //�������� �������� ����������
		double **sv; //������������ ������� �����������
		double *istr; //������������ ������� ������� 
		double *th; //��������� ��������� ������ � ������������ �������
		double alm; //����������� �������
		int *free; //������ � �������� ��������� ����������
		int i_lrow; //����������� ������
		int i_lcol; //����������� �������
		int iter;//���������� ��������
}; 
#endif /* _SIMPLEX_H_ */
