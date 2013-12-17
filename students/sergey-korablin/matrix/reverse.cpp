#include <iostream>
using namespace std;
#include <math.h>
#define EPS 0.000000001
typedef double type_m;

void Print (type_m **k, int N) {
    int i,j;
    for (i=0; i<N; i++) {
        for (j=0; j<N; j++)
            cout<<k[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}

bool IsZero (type_m a) {
    if (fabs(a)<=EPS)
        return true;
    return false;
}

bool IsColumnFullOfZeros (int N, int a, type_m **k) {
    int i;
    for (i=0; i<N; i++) {
        if (!IsZero(k[i][a]))
            return false;
    }
    return true;
}

void StringsSwap (int N, int a, int b, type_m **s) {
    type_m tmp;
    int i;
    for (i=0; i<N; i++) {
        tmp=s[a][i];
        s[a][i]=s[b][i];
        s[b][i]=tmp;
    }
}


int main ()
{
    int N;
    cin>>N;

	type_m **k;
	k=new type_m* [N];
	int i,j;
	for (i=0;i<N;i++)
		k[i]=new type_m [N];
	for (i=0;i<N;i++) 
		for (j=0;j<N;j++)
			cin>>k[i][j];

    type_m **e;
	e=new type_m* [N];
	for (i=0;i<N;i++)
		e[i]=new type_m [N];
	for (i=0;i<N;i++) 
		for (j=0;j<N;j++)
			e[i][j]=0;
    for (i=0;i<N;i++) 
		e[i][i]=1;

    int iter;
    int num_1;
    int num;
    type_m x;
    for (iter=0; iter<N; iter++) {
        num=iter;
        while (IsColumnFullOfZeros(N,num,k)) {
            num++;
            if (num==N) {
                cout<<"NO"<<endl;
                return 0;
            }
        }
        //Swap
        num_1=iter+1;
        if (num_1==N)
            num_1--; //bad! rewrite!
        if (IsZero(k[iter][num])) {
            while (IsZero(k[num_1][num])) {
                num_1++;
                if (num_1==N) {
                    cout<<"NO"<<endl;
                    return 0;
                }
            }
            StringsSwap (N, iter, num_1, e);
            StringsSwap (N, iter, num_1, k);
        }
        //First to one
        x=k[iter][num];
        for (i=0; i<N; i++) { 
            k[iter][i]=k[iter][i]/x;
            e[iter][i]=e[iter][i]/x;
        }
        //First to null
        for (i=iter+1; i<N; i++) {
            x=k[i][iter];
            for (j=0; j<N; j++) {
                k[i][j]=k[i][j]-x*k[iter][j];
                e[i][j]=e[i][j]-x*e[iter][j];
            }
        }
    }
    for (i=N-1; i>=1; i--) {
        for (j=i-1; j>=0; j--) {
            x=k[j][i];
            for (num=0; num<N; num++) {
                k[j][num]=k[j][num]-x*k[i][num];
                e[j][num]=e[j][num]-x*e[i][num];
            }
        }
    }
    Print (e,N);
    return 0;
}
