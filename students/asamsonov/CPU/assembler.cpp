//{-------------head----------------------------------
//
//! @file    assembler.cpp
//! @brief   Now it's (!)Assembler(!) for CPU.
//!
//}-------------head---------------------------------

//{-------------defines---------------------------------

#include "CPUheader.h"

#ifndef CPUHEADER 
	fprintf (stderr, "CPUwork.h is not existing.\n");
	abort ();
#endif

//}-------------defines---------------------------------

/* _______________________________________________________________________________________
   |																					 |
   |  Separator			Separator		  Separator 		Separator		  Separator  |
   | 		   Separator		 Separator		   Separator		 Separator 			 |
   |  Separator			Separator		  Separator 		Separator		  Separator  |
   |_____________________________________________________________________________________|
*/

//{-------------declarations----------------------------
/* 

int id_command (char *str_4);

int asm_command (int command, int x, FILE* fi, FILE* fo);

int assemble ()

*/
//}-------------declarations----------------------------

/* _______________________________________________________________________________________
   |																					 |
   |  Separator			Separator		  Separator 		Separator		  Separator  |
   | 		   Separator		 Separator		   Separator		 Separator 			 |
   |  Separator			Separator		  Separator 		Separator		  Separator  |
   |_____________________________________________________________________________________|
*/

//{-------------Assembler-------------------------------
//! @brief   This function makes 0x. code from command
//!			 stored in string (4 chars).
//!
//! @param		str_4	command
//!
//! @return		0x. code of this command.	
//!
//! @see     asm_command()
//}-------------Assembler------------------------------

int id_command (char *str_4)
{
	return (str_4[0] << 24) | 
		   (str_4[1] << 16) | 
		   (str_4[2] <<  8) | 
		   (str_4[3]      );
}

//{-------------Assembler-------------------------------
//! @brief   This function makes 0x. code from reg
//!			 stored in 2 chars.
//!
//! @param		reg		register store
//!
//! @return		0x. code of this command. -12 if such a reg doesn't exist.
//!
//! @see     asm_command()
//}-------------Assembler------------------------------

int asm_reg (char reg[])
{
	return (reg[0] == 'a' && reg[1] == 'x')? AX : 
		   (reg[0] == 'b' && reg[1] == 'x')? BX :
		   (reg[0] == 'c' && reg[1] == 'x')? CX :
		   (reg[0] == 'd' && reg[1] == 'x')? DX :
	BAD;
}

//{-------------Assembler-------------------------------
//! @brief   This function indentifies what this command 
//!			 is to do and read missing components 
//!			 from a file given if it's necessary.
//!			 After all, function writes command  
//!			 and it's components in another file given.
//!
//! @param		command		command.
//! @param		x			line of file we read on.
//! @param		fi			file to read from.
//! @param		fo			file to write to.
//!
//! @return		0 if it's ok, @x if smth's wrong	
//!
//! @see     id_command(), assemble()
//}-------------Assembler------------------------------

#define DO_SMTH(command)  case R_##command : { asm_c = command; fprintf (fo, "%d\n", asm_c); break; }
#define DO_JUMP(command)  case R_##command : { asm_c = command; fprintf (fo, "%d ", asm_c); \
										  fscanf (fi, "%s", reg); fprintf (fo, "%c\n", '?'); break; }

int asm_command (int command, int x, FILE* fi, FILE* fo)
{
	int asm_c = END;
	double extra = 0;
	char reg[3] = {};
	int str = 0;

	switch (command) {

		DO_SMTH(END);

		//{-------------command-with-argument------------------------------
		case R_PUSH : { asm_c = PUSH; fprintf (fo, "%d ", asm_c); str = 0;
					    if (!fscanf (fi, "%lg", &extra)) { 
							str = 1;
							if (!fscanf (fi, "%s", reg))
								return x;
						}
					    (!str)? fprintf (fo, "%d %lg\n", NUM, extra) : 
							 fprintf (fo, "%d %d\n", REG, asm_reg(reg));
						break; }
		//}-------------command-with-argument------------------------------

		//{-------------command-with-argument------------------------------
		case R_POP  : { asm_c =  POP; fprintf (fo, "%d ", asm_c); 
						char p = 0;
						while ((p = getc (fi)) == ' ');
						if (p == '\n' || p == EOF) {
							fprintf (fo, "%d\n", NUM);
							break;
						}
						ungetc(p, fi);
						if (!fscanf (fi, "%s", reg))
							return x;
						fprintf (fo, "%d %d\n", REG, asm_reg(reg));
						break; }
		//}-------------command-with-argument------------------------------

		DO_SMTH( ADD);
		DO_SMTH( SUB);
		DO_SMTH( MUL);
		DO_SMTH( DIV);
		DO_SMTH(SQRT);
		DO_SMTH( POW);
		DO_SMTH( SIN);
		DO_SMTH( COS);
		
		//{-------------command-with-argument------------------------------
		case R_OUT  : { asm_c =  OUT; fprintf (fo, "%d ", asm_c); 
						char p = 0;
						while ((p = getc (fi)) == ' ');
						if (p == '\n' || p == EOF) {
							fprintf (fo, "%d\n", NUM);
							break;
						}
						ungetc(p, fi);
						if (!fscanf (fi, "%s", reg))
							return x;
						fprintf (fo, "%d %d\n", REG, asm_reg(reg));
						break; }
		//}-------------command-with-argument------------------------------

		DO_JUMP( JMP); 
		DO_JUMP( JBE); 
		DO_JUMP( JAE); 
		DO_JUMP( JNE); 
		DO_JUMP(  JB); 
		DO_JUMP(  JA); 
		DO_JUMP(  JE);
		DO_JUMP(  JF); 

		//{-------------command-with-argument------------------------------
		case R_MOV : { asm_c = MOV; fprintf (fo, "%d ", asm_c); str = 0;
						
					    if (!fscanf (fi, "%lg", &extra)) { 
							str = 1;
							if (!fscanf (fi, "%s", reg))
								return x;
						}
					    (!str)? fprintf (fo, "%d %lg\n", NUM, extra) : 
							 fprintf (fo, "%d %d ", REG, asm_reg(reg));
						if (!fscanf (fi, "%s", reg))
							return x;
						fprintf (fo, "%d\n", asm_reg(reg));
						break; }
		//}-------------command-with-argument------------------------------

		default : { return x; } 
	}
	return 0;
}

#undef DO_SMTH
#undef DO_JUMP

//{-------------Assembler-------------------------------
//! @brief   reads from INPUT file all commands, 
//!			 interprete them and write in MC file
//!
//! @return		0 if it's ok, or num of line (starting with 1)
//!				where is error if it's not ok.
//!				
//! @see     id_command(), asm_command()
//}-------------Assembler-----------------------------

int assemble (FILE *fi, FILE *fo)
{
	int ok = 1;
	char scanned[5] = {0};
	unsigned int command = 0;
	int x = 0;

	while (ok = fscanf (fi, "%s", scanned)) {
		x ++;
		if (scanned[0] == ':') 
			continue; //mark check.
		ASSERT (sizeof (int) >= 4);
		command = id_command (scanned);
		printf ("%d %.8X\n", x, command);
		if (command == 0) return 0;

		scanned[0] = '\0';
		scanned[1] = '\0';
		scanned[2] = '\0';
		scanned[3] = '\0';

		if (asm_command (command, x, fi, fo)) return x;
	}
	return 0;
}