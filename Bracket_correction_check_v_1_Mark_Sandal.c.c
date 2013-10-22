#include<stdio.h>
#include<assert.h>

int main()
{   char currsymb;
    int  cyclecount = 0;
    currsymb = getchar();
    assert (   currsymb  ==  '('  ||  currsymb  ==  ')'  );
    while  (   currsymb != '\n'   )
    {
        assert (  currsymb  ==  '('  || currsymb  ==  ')');
        if     ( currsymb  ==  '(')
        {
            cyclecount  =  cyclecount  +  1;
        }
        else
        {
            cyclecount  =  cyclecount  -  1;
        };
        if (  cyclecount  <  0 )
           break ;
        else
            currsymb  =  getchar() ;

    }
    if (   cyclecount   ==   0   )
        printf (   "YES"   ) ;
    else
        printf (   "NO"   ) ;
    return  0 ;
}
