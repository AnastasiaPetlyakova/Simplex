#ifndef _USER_DATA_H_
#define _USER_DATA_H_

class user_data 
{ 
	public:
		void get_data(); //������ ������ 
	protected:
		double *function; //������������ ������� �������
		double *fm; //�������� ��������� ������ 
		double **system; //������������ ������� �����������
		int *sign; //���� ����������� (0 - <=. 1 - =, 2 - >=)
		int num_v; //���������� ���������� 
		int num_l; //���������� �����������
		bool direction; //true, ���� ��������; false, ���� �������
}; 
#endif /* _USER_DATA_H_ */
