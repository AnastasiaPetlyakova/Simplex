#include "simplex.h"
#include <iostream>

using namespace std;

int main() 
{
	bool flag = true;
	int i, a;
	setlocale(LC_ALL, "Russian");
	simplex *ud = new simplex;
	ud->get_data();
	ud->initialize();
	ud->print_result();
	ud->optimize();
	ud->clear();
	
	do {
		cout << "\n1 -Новое решение\n2 - Закончить работу программы\n \n";
		cin >> a;	
		switch (a) 
		{
			case 1:
			{
				system("cls");
				simplex *ud = new simplex;
					ud->get_data();
					ud->initialize();
					ud->print_result();
					ud->optimize();
					ud->clear();
				flag=false;
				break;
			}
			case 2:
			{
				flag=true;
				break;
			}
			default:
			{
				cout<<"Значение некорректно"<<endl;
				break;
			}
		}
	} while (!flag);

	system("pause");
	return 0;
}
