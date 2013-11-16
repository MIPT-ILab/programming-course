#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define ST_SIZE 256
#define NUM_CMD 256
#define NUM_LBL 9

//------------------------------------------STACK---------------------------------

struct stack
{
	int *top      ;
	int *ch_start ;
};

int ok_stack(struct stack *st)//Checking pointers
{        
        assert(st->ch_start <= st->top)          ;
        assert(st->top < st->ch_start + ST_SIZE) ;

        return 0                                 ;
}


int stack_construct(struct stack *st)
{
        st->ch_start = (int*)calloc(ST_SIZE, sizeof(int)) ;
        st->top = st->ch_start + 1 ;
          
        return 0 ;
}

int stack_destruct(struct stack *st)
{
        free(st->ch_start) ;        

        return 0           ;
}


int push_stack(struct stack *st, int elem)
{
        ok_stack(st)       ;  
        ++st->top          ;
        *(st->top) = elem  ;
        ok_stack(st)       ; 
          
        return 0           ;
}

int pop_stack(struct stack *st)
{
        ok_stack(st)           ;        
        int val = *(st->top)   ;          
        --st->top              ;
        ok_stack(st)           ;       
            
        return val             ;
}
//-----------------------------------------Handlers-----------------------
int add(struct stack *st)//Add last+prev.
{
        int val_1 = pop_stack(st)   ;
        int val_2 = pop_stack(st)   ;
        push_stack(st, val_1+val_2) ;

        return 0                    ;
}

int mul(struct stack *st)//Multiply last and prev.
{
        int val_1 = pop_stack(st)   ;
        int val_2 = pop_stack(st)   ;
        push_stack(st, val_1*val_2) ;

        return 0                    ;
}

int out(struct stack *st)//Print the last element
{
	int last = pop_stack(st)	;
	push_stack(st, last)        ;
	printf("%d\n", last)	    ;	
	
	return 0		            ;
}

int comp(struct stack *st)//Compare last+prev
{
	int val_1 = pop_stack(st) ;
	int val_2 = pop_stack(st) ;
	if(val_2 > val_1) 
	{
		push_stack(st, val_2) ;
		push_stack(st, val_1) ;
		return 1 ;
	}
	else
	{
		push_stack(st, val_2) ;
		push_stack(st, val_1) ;
		return 0 ;
	}
}

int data_lbls_constr(int *data, int num)//Filling the data of labels with -1
{
	for(int j = 0 ; j < num ; j++)
	{
		data[j] = -1 ;
	}

	return 0 ;
}
//------------------------------------------CPU-----------------------------

int main()
{
  int ax,bx,cx,dx      ;
  int cmd              ;
  int fl = 0           ;
  int data[NUM_CMD]    ;
  int lbl[NUM_LBL]     ;
  
  const JMP_CMD = -1   ;
  const END = 9        ;
    
//****Open ASM_OUT for reading
  FILE *stream, *fopen() ;

  stream = fopen("ASM_OUT", "r") ;

  if (stream == NULL)//Checking opening file
  {  
  	printf("Can't open ASM_OUT\n") ;
	exit(1) ;
  }
//****

  struct stack MyStack ;

  data_lbls_constr(&lbl[0], NUM_LBL) ;  

  int counter = 0 ;
  
  while(1)
  {
  	fscanf(stream ,"%d", &data[counter])     ;
  	if(data[counter] == -2 ) break           ;
  	//++counter;
  	if(data[counter] == -1)
  	{ 	
  		++counter                            ;
  		fscanf(stream ,"%d", &data[counter]) ;
  		lbl[data[counter]] = counter         ;
  	} 
  	++counter                                ;
  }	 
  
  stack_construct(&MyStack) ;
  
  for(int step = 0 ; step < counter ; ++step )
  {   
  	switch (data[step])
	{ 
		case -1: ++step  ; 
				 break   ;

		case 0: step++ ;
	         	switch(data[step])//Push register
		   	    {
		   	 		case 0 : push_stack(&MyStack, ax) ; break        ;
		   			case 1 : push_stack(&MyStack, bx) ; break        ;
		   			case 2 : push_stack(&MyStack, cx) ; break        ;
		   			case 3 : push_stack(&MyStack, dx) ; break        ;
		   			default: assert('Wrong register' == 0) ; 
							break                          ;  
		   	 	}
			 	break ;
		case 1: ++step ;//Push value 
			 	push_stack(&MyStack, data[step]) ;
			 	break ;
		case 2: ++step ;//Move into register
                switch(data[step])
		  	 	{
		  			case 0: ax = pop_stack(&MyStack) ; break       ; 
		  			case 1: bx = pop_stack(&MyStack) ; break       ;
		  			case 2: cx = pop_stack(&MyStack) ; break       ;
		  			case 3: dx = pop_stack(&MyStack) ; break       ;
		  			default: assert('Wrong register' == 0) ;
		           			break                          ;  
		  	 	}
			 	break ;
		case 3: add(&MyStack) ;
			 	break ;
		case 4: mul(&MyStack) ;
			 	break ;
	  	case 5: ++step ;//JMP
	  			//assert('Wrong label' == 0) ;
	  			step = lbl[data[step]] ;

	  			break ;
		case 6: if(comp(&MyStack))//JBE
				{
					++step ;
					//assert('Wrong label' == 0);
					step = lbl[data[step]] ;
				}
				else ++step ;
				break;
		case 7: ++step ;
				lbl[data[step]] = step + 1 ;
	  	case 8: out(&MyStack) ;//OUT
			 	break ;		
		case 9: step = counter ;//END
			 	break ; 
		default: assert('Wrong argument' == 0) ; 
			 	break  ;	
	}
 
    }
    
  return 0 ;
}
