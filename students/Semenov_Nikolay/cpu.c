#define ST_SIZE 256
#define NUM_CMD 256
#define NUM_LBL 9

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

//------------------------------------------STACK---------------------------------

        static int *top      ;
        static int *ch_start ;

  

/*int ok_stack()//Stack Check
{        
        return((ch_start <= top) && (top < ch_start + ST_SIZE)) ;
}
*/

int stack_construct()//Construct Stack
{
        ch_start = (int*)calloc(ST_SIZE, sizeof(int)) ;
        top = ch_start   ;
          
        return 0         ;
}

int stack_destruct()//Destruct Stack
{
        free(ch_start)    ;
        *ch_start = 0xBAD ;
        *top = *ch_start  ;          

        return 0          ;
}


int push_stack(int elem)//Push smth into stack
{
        assert(top < ch_start + ST_SIZE ) ;  
        ++top                             ;
        *top = elem                       ; 
          
        return 0                          ;
}

int pop_stack()//Pop smth outside stack
{
        assert(ch_start <= top);        
        int val = *top         ;          
        --top                  ;        
            
        return val             ;
}
//-----------------------------------------Handlers-----------------------
int add()//Add last+prev.
{
        int val_1 = pop_stack() ;
        int val_2 = pop_stack() ;
        push_stack(val_1+val_2) ;

        return 0                ;
}

int mul()//Multiply last and prev.
{
        int val_1 = pop_stack() ;
        int val_2 = pop_stack() ;
        push_stack(val_1*val_2) ;

        return 0                ;
}

int out()//Print the last element
{
	int last = pop_stack()	;
	printf("%d\n", last)	;	
	
	return 0		        ;
}

int comp()//Compare last+prev
{
	int val_1 = pop_stack() ;
	int val_2 = pop_stack() ;
	if(val_2 > val_1) 
	{
		return 1 ;
	}
	else
	{
		return 0 ;
	}
}
//------------------------------------------CPU-----------------------------

int main()
{
  int ax,bx,cx,dx   ;
  int cmd           ;
  int fl = 0        ;
  int data[NUM_CMD] ;
  int lbl[NUM_LBL]  ;

  for(int j = 0 ; j < NUM_LBL ; j++)
  {
  	lbl[j] = -1 ;
  }
  
  //Open ASM_out for reading

  int i = 0 ;
  while(EOF)
  {
  	scanf("%d", &data[i]);
  	i++;
  	if(data[i-1] == 37) lbl[data[i]] = i + 1 ;  
  }	 
  
  stack_construct();
  
  for(int j = 0 ; j < i ; j++ )
  {   
  	switch (data[j])
	{
		case 0: j++ ;
	         	switch(data[j])//Push register
		   	    {
		   	 		case 0 : push_stack(ax) ; break        ;
		   			case 1 : push_stack(bx) ; break        ;
		   			case 2 : push_stack(cx) ; break        ;
		   			case 3 : push_stack(dx) ; break        ;
		   			default: assert('Wrong argument' == 0) ; 
							break                          ;  
		   	 	}
			 	break ;
		case 1: j++ ;//Push value 
			 	push_stack(data[j]) ;
			 	break ;
		case 2: j++ ;//Move into register
                switch(data[j])
		  	 	{
		  			case 0: ax = pop_stack() ; break       ; 
		  			case 1: bx = pop_stack() ; break       ;
		  			case 2: cx = pop_stack() ; break       ;
		  			case 3: dx = pop_stack() ; break       ;
		  			default: assert('Wrong argument' == 0) ;
		           			break                          ;  
		  	 	}
			 	break ;
		case 3: add() ;
			 	break ;
		case 4: mul() ;
			 	break ;
	  	case 5: j++ ;//JMP
	  			assert('Wrong label' == 0);
	  			j = lbl[data[j]] ;
	  			break ;
		case 6: if(comp())//JBE
				{
					j++ ;
					assert('Wrong label' == 0);
					j = lbl[data[j]] ;
				}
				else j++ ;
				break;
		case 7: j++ ;
				lbl[data[j]] = j + 1 ;
	  	case 8: out() ;//OUT
			 	break ;		
		case 9: j = i ;//END
			 	break ; 
		default: assert('Wrong argument' == 0) ; 
			 	break  ;	
	}
 
    }
    
  return 0 ;
}
