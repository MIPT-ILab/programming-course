#include <stdio.h>
#include <math.h>
#include <assert.h>
#define DOUBLE_EPSILON 0.00000001 //accuracy of comparing double

#define ASSERT(condition,message)            \
        {                                    \
            if(!(condition))                 \
            {                                \
                printf((message));           \
                assert(0);                   \
            }                                \
        }                                    \

void sort_data(float data[],unsigned int n);

int main()
{
    int n=0,i=0;
    float *data;

    printf("Please enter the number of elements you are going to sort:\n");
    ASSERT(scanf("%d",&n)==1 && n>0,"Wrong input format\n");

    data=(float*) calloc(n,sizeof(float));

    printf("Please enter the elements you are going to sort:\n");
    for(i=0;i<n;i++)
        ASSERT(scanf("%f",data+i)==1,"Wrong input format\n");

    sort_data(data,n);

    printf("Sorted elements(with accuracy up to 0.00000001):\n ");
    for(i=0;i<n;i++)
        printf("%g ",*(data+i));

    free(data);
    data=NULL;

    return 0;
}


void sort_data(float *data,unsigned int n)
{
    assert(n>0);
    assert(data!=NULL);

    int k=0;
    int l=0;
    float temp=0;

    for(k;k<n-1;k++){
        for(l=k+1;l<n;l++)
            if((*(data+k)-*(data+l))>DOUBLE_EPSILON)
            {
                    temp=*(data+l);
                    *(data+l)=*(data+k);
                    *(data+k)=temp;
            }
    }
}
