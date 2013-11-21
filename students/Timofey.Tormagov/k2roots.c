//{=================================================================================
//! @file    k2roots.c
//! @date    2013-10-08 18:57
//! @author  Timofey Tormagov <timofey.tormagov@frtk.ru>
//!
//! Решение квадратного уравнения с разбором частных случаев.
//!
//! @par     Условие задачи
//!          На вход подается 3 коэффициента А,В и С. Программа выводит количество 
//!          действительных корней уравнения и корни с точность до 3 знаков после запятой.  
//}=================================================================================
#include <stdio.h>
#include <math.h>

//!<Подсчет дискриминатна квадратного уравнения
float discrim(float coef_a,float coef_b,float coef_c)
	{
	return (coef_b*coef_b-(4*coef_a*coef_c));
	}

main()
{
	//!< Переменные для значений корней уравнения
	float root_x1 = 0 , root_x2 = 0;
	//!< Переменная для значения количества корней уравнения
	int k_root = -3;
	//!< Переменные для значений коэфицентов уравнения
	float coef_a = 0 , coef_b = 0 , coef_c = 0;
	printf("# Введите через пробел коэффициенты A,B,C в соответсвии с формулой Ax^2+Bx+C=0 \n");
	scanf("%f %f %f",&coef_a,&coef_b,&coef_c);
	if (coef_a != 0) 
	{
		//!< Переменная для значения дискриминанта уравнения
		float Droot=discrim(coef_a,coef_b,coef_c);
		if (Droot < 0) k_root = 0; 
		else
			if (Droot == 0) 
			{
				k_root  = 1; 
				root_x1 = ((-coef_b)/(2*coef_a));
			}
			else 
			{
				k_root  = 2; 
				root_x1 = (-coef_b+sqrt(Droot))/(2*coef_a);
				root_x2 = (-coef_b-sqrt(Droot))/(2*coef_a);
			}
	}
	else 
		if (coef_b == 0) 
		{
			if (coef_c == 0) k_root = -1; 
			else k_root = 0;
		}
		else
		{
			k_root = 1;
			root_x1 = -coef_c/coef_b; 
		}
	switch (k_root)
	{
	case -1: printf("# Уравнение имеет бесконечно много решений\n"); break;
	case 0: printf("# Уравнение не имеет действительных корней\n"); break;
	case 1: printf("# Уравнение имеет один корень\n# Значение корня \n%.3f\n", root_x1); break;
	case 2: printf("# Уравнение имеет два кореня\n# Значение корней \n%.3f  %.3f\n", root_x1, root_x2); break;
	}
	return 0;
}
