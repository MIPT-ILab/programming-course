#include <stdio.h>
#include <math.h>
#include <assert.h>
// ����� ����������� solvsquare() ���������� ���� ������� ����������� � ���, ���
// ������� ������, ����� � �� ������� � ����� �������� ���������
// ����� ����� ���������: http://code.google.com/p/mipt-ilab-course/wiki/Commen..
// ����� ����������: 
/* SolveSquare - solve a square or linear equation specified by its coefficients.
* IN: a,b,c - the equation coefficients
* OUT: *x1,*x2 - solutions if exist
* RETURN: number of roots or zero if none
*/
int solvsquare(double a, double b, double c, double* x1, double* x2)
{
assert(x1!=NULL);
assert(x2!=NULL);
assert(x1=x2);
if(a==0) // ��������� � ���� ����� � ��������� ������� �������� ��-�������!
{
if(b!=0) // ��������� � ���� ����� � ��������� ������� �������� ��-�������!
{
*x1=-c/b;
return 1;
}
else 
return 0;
}
else
{
if((b*b-4*a*c)<0) // ��������� (b*b-4*a*c) ����������� ����� ��� � ����� ���������. ������ ����, ����� ������ ��� ������������� ���, ����� ��������� ��� �������� ����� ���������� D � ������������ �.
return 0;
if((b*b-4*a*c)==0) // ��������� � ���� ����� � ��������� ������� �������� ��-�������!
{
*x1=-b/(2*a);
return 1;
}
if((b*b-4*a*c)>0)
{
*x1=((-b+sqrt(b*b-4*a*c))/(2*a));
*x2=((-b-sqrt(b*b-4*a*c))/(2*a));
return 2;
}

}
}
int main()
{
int nRoots=0;
double x1=0,x2=0,a=0,b=0,c=0;
// ����� ������� printf(). ����� ���� ��������� �� ��������� �����
// ����� �������: ����� ����� �� ������ ��������� 80 �������� - 
// ����������� ������ ���������
printf("Reshenie kvadratnih uravneniy\nAvtor Stupakov Dmitry\nVersia 1.0\n21.09.2013\nVvedite koeficienti uravnenia:"); 
scanf("%lf%lf%lf",&a,&b,&c); // ��� �������� �� ��, ��� ������������ ��� ����� ��� �����. ���� ��������� ��� scanf()
nRoots=solvsquare(a,b,c,&x1,&x2);
if(nRoots==0)
printf("Net racionalnih korney\n"); // ����� ������ �� ����������, ���� ���� ������ ��� �����. ��� �������� ��������� ����������� �������.
if(nRoots==1)
printf("X=%lf\n",x1);
if(nRoots==2)
printf("X1=%lf\nX2=%lf\n",x1,x2);
system("PAUSE"); // ����� �������� pause ���������� �������, �.�. UNIX-������� �������� � �������� ����, �� ��� ��������� ��� ��������� ������� pause.
return 0;
}
