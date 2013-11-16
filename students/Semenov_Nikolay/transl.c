#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define CMD_SIZE 5
#define REG_SIZE 2

int main()
{
//****Open ASM_OUT for reading
  FILE *open, *fopen() ;

  open = fopen("ASM_IN", "r") ;

  if (open == NULL)//Checking opening file
  {  
  	printf("Can't open ASM_IN\n") ;
	exit(1) ;
  }
//****
	
//****Open ASM_OUT for reading
  FILE *stream, *fopen() ;

  stream = fopen("ASM_OUT", "w") ;

  if (stream == NULL)//Checking opening file
  {  
  	printf("Can't open ASM_OUT\n") ;
	exit(1) ;
  }
//****
/*-------------------------------------------------
Add assert, to check command name!
-------------------------------------------------*/
	char cmd[CMD_SIZE] ;
	char reg[REG_SIZE] ;
	int cmd_n, check, val, reg_n ;
	int flag = 1 ;
	
	while(flag)
	{
		fscanf(open,"%s", &cmd) ;

		if(cmd[1] == 'U') cmd_n = 3 ; //Mulv
		if(cmd[0] == 'P') cmd_n = 0 ; //Push
		if(cmd[1] == 'O') cmd_n = 1 ; //Pop
		if(cmd[1] == 'D') cmd_n = 2 ; //Add
		if(cmd[1] == 'M') cmd_n = 4 ; //JMP
		if(cmd[1] == 'B') cmd_n = 5 ; //JBE
		if(cmd[0] == ':') cmd_n = 6 ; // :
		if(cmd[2] == 'T') cmd_n = 7 ; //OUT
		if(cmd[1] == 'N') cmd_n = 8 ; //End

		switch(cmd_n)
		{
			case 0: check = fscanf(open,"%d", &val) ;
				switch(check)
				{
					case 0: fscanf(open,"%s", &reg) ;
						if(reg[0] == 'A') reg_n = 0 ; //AX
						if(reg[0] == 'B') reg_n = 1 ; //BX
						if(reg[0] == 'C') reg_n = 2 ; //CX	
						if(reg[0] == 'D') reg_n = 3 ; //DX
						fprintf(stream," 0 %d", reg_n); //PUSH REG
						break ;
					case 1: fprintf(stream," 1 %d", val) ; //PUSH VALUE
						break ;
					default: assert('Push is dropped' == 0) ;
				} 
				break ;
			case 1: fscanf(open,"%s", &reg) ;
				if(reg[0] == 'A') reg_n = 0 ; //AX
				if(reg[0] == 'B') reg_n = 1 ; //BX
				if(reg[0] == 'C') reg_n = 2 ; //CX	
				if(reg[0] == 'D') reg_n = 3 ; //DX
				fprintf(stream," 2 %d", reg_n); //POP
				break ;
			case 2: fprintf(stream," 3 ") ; break ;//ADD
			case 3: fprintf(stream," 4 ") ; break ;//MUL
			case 4: fscanf(open,"%d", &val)  ;
				fprintf(stream," 5 %d", val) ; //JMP
				break ;
			case 5: fscanf(open,"%d", &val)  ;
				fprintf(stream," 6 %d", val) ; //JBE 
				break ;
			case 6: fprintf(stream," -1 %c", cmd[1]) ; //:LABEL
				break ;
			case 7: fprintf(stream," 8 ") ; //OUT
				break ;
			case 8: fprintf(stream," -2 ") ;
					flag = 0 ; //END
				break ; 
			default: assert('Wrong argument' == 0) ; 
				break ;
		}   
	}
	return 0;
}
