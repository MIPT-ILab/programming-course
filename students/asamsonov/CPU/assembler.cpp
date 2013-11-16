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

int asm_reg (char reg[]);

void asm_mark (char mark[], int pos, int mkdata[]);

int asm_set_marks (int *x, FILE* fi, int mkdata[]);

int asm_len_command (int command, int *x, FILE *fi);

int asm_command (int command, int x, FILE* fi, FILE* fo);

int asm_run (FILE *fi, FILE *fo); // see INPUT and OUTPUT in assembler.cpp.

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
	ASSERT (str_4);
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
	ASSERT (reg);
	return (reg[0] == 'a' && reg[1] == 'x')? AX : 
		   (reg[0] == 'b' && reg[1] == 'x')? BX :
		   (reg[0] == 'c' && reg[1] == 'x')? CX :
		   (reg[0] == 'd' && reg[1] == 'x')? DX :
	BAD;
}

//{-------------Assembler-------------------------------
//! @brief   This function writes mark adress in mkdata.
//!
//! @param		mark		mark store
//! @param		pos			address of mark in ASMed file.
//! @param		mkdata		data of all marks
//!
//! @see     asm_command()
//}-------------Assembler------------------------------

void asm_mark (char mark[], int pos, int mkdata[])
{
	ASSERT (mark);
	ASSERT (mkdata);
	mkdata[mark[1] - '0'] = pos;
}

//{-------------Assembler-------------------------------
//! @brief   reads from INPUT file all commands, 
//!			 checking their lengths in ASMed file 
//!			 and filling data of marks read.
//!
//! @param		x			number of last command in ASMED file.
//! @param		fi			file to read from.
//! @param		mkdata		data of all jump marks
//!
//! @return		0 if it's ok, 1 if it's not ok.
//!				x was given by adress so it can be checked.
//!				
//! @see     id_command(), asm_command()
//}-------------Assembler-----------------------------

int asm_set_marks (int *x, FILE* fi, int mkdata[])
{
	ASSERT (x);
	ASSERT (fi);
	ASSERT (mkdata);
	int command = 0;
	int ok = 0;
	char scanned[5] = {0};
	while (ok = fscanf (fi, "%s", scanned)) {
		if (scanned[0] == ':') { // mark check.
			asm_mark (scanned, *x, mkdata);
			continue;	
		}
		if (scanned[0] == '/')
			continue;
		ASSERT (sizeof (int) >= 4);
		command = id_command (scanned);
		CENSORED ("# %d %.8X\n", *x, command);
		if (command == 0) return 0;

		scanned[0] = '\0';
		scanned[1] = '\0';
		scanned[2] = '\0';
		scanned[3] = '\0';

		if (asm_len_command (command, x, fi, mkdata)) return 1;
	}
	return 0;
}

#define DO_SMTH(command)  case R_##command : { *x += 1; break; }
#define DO_JUMP(command)  case R_##command : { fscanf (fi, "%s", reg); *x += 2; break; }

//{-------------Assembler-------------------------------
//! @brief   This function indentifies what this command 
//!			 is to do and read missing components 
//!			 from a file given if it's necessary.
//!			 After all, function returns len of 
//!			 this command in ASMed file.
//!
//! @param		command		command.
//! @param		x			num of command in ASMed file.
//! @param		fi			file to read from.
//!
//! @return		0 if it's ok, @x if smth's wrong	
//!
//! @see     id_command(), assemble()
//}-------------Assembler------------------------------

int asm_len_command (int command, int *x, FILE *fi, int mkdata[])
{
	ASSERT (x);
	ASSERT (fi);
	double extra = 0;
	char reg[3] = {};
	int str = 0;

	switch (command) {

		DO_SMTH(END);

		//{-------------command-with-argument------------------------------
		case R_PUSH : { if (!fscanf (fi, "%lg", &extra)) { 
							if (!fscanf (fi, "%s", reg))
								return *x;
						}
					    *x += 3;
						break; }
		//}-------------command-with-argument------------------------------

		//{-------------command-with-argument------------------------------
		case R_POP  : { char p = 0;
						while ((p = getc (fi)) == ' ');
						if (p == '\n' || p == EOF) {
							*x += 2;
							break;
						}
						ungetc(p, fi);
						if (!fscanf (fi, "%s", reg))
							return *x;
						*x += 3;
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
		DO_SMTH( DUB);
		
		//{-------------command-with-argument------------------------------
		case R_OUT  : { char p = 0;
						while ((p = getc (fi)) == ' ');
						if (p == '\n' || p == EOF) {
							*x += 2;
							break;
						}
						ungetc(p, fi);
						if (!fscanf (fi, "%s", reg))
							return *x;
						*x += 3;
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
		case R_MOV : {  if (!fscanf (fi, "%lg", &extra)) { 
							if (!fscanf (fi, "%s", reg))
								return *x;
							}
						if (!fscanf (fi, "%s", reg))
							return *x;
					    *x += 4;
						break; }
		//}-------------command-with-argument------------------------------

		//{-------------command-with-argument------------------------------
		case R_IN  : {  char p = 0;
						while ((p = getc (fi)) == ' ');
						if (p == '\n' || p == EOF) {
							*x += 2;
							break;
						}
						ungetc(p, fi);
						if (!fscanf (fi, "%s", reg))
							return *x;
						*x += 3;
						break; }
		//}-------------command-with-argument------------------------------
		
		DO_SMTH (DUMP);
		case R_FUNC : { if (!fscanf (fi, "%s", reg))
							return *x;
						if (reg[0] == ':') // mark check.
						asm_mark (reg, *x, mkdata); 
						break; }
		DO_JUMP (CALL);
		DO_SMTH ( RET);
		DO_SMTH ( HLT);
		DO_SMTH (  OR);
		DO_SMTH ( AND);
		DO_SMTH ( NOT);
		DO_SMTH ( XOR);

		default : { return *x; } 
	}
	return 0;
}

#undef DO_SMTH
#undef DO_JUMP

#define DO_SMTH(command)  case R_##command : { asm_c = command; fprintf (fo, "%d\n", asm_c); break; }
#define DO_JUMP(command)                        \
case R_##command : {                            \
	asm_c = command;                            \
	fprintf (fo, "%d ", asm_c);                 \
	fscanf (fi, "%s", reg);                     \
	fprintf (fo, "%d\n", mkdata[reg[1] - '0']); \
	break;                                      \
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
//! @param		mkdata		data of all jump marks
//!
//! @return		0 if it's ok, @x if smth's wrong	
//!
//! @see     id_command(), assemble()
//}-------------Assembler------------------------------

int asm_command (int command, int x, FILE* fi, FILE* fo, int mkdata[])
{
	ASSERT (fi);
	ASSERT (fo);
	ASSERT (mkdata);
	CENSORED ("# ASM: %d, %.8X\n", x, command);
	int asm_c = END;
	double extra = 0;
	char reg[3] = {};
	int str = 0;

	switch (command) {

		DO_SMTH (END);

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

		DO_SMTH ( ADD);
		DO_SMTH ( SUB);
		DO_SMTH ( MUL);
		DO_SMTH ( DIV);
		DO_SMTH (SQRT);
		DO_SMTH ( POW);
		DO_SMTH ( SIN);
		DO_SMTH ( COS);
		DO_SMTH ( DUB);
		
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

		DO_JUMP ( JMP); 
		DO_JUMP ( JBE); 
		DO_JUMP ( JAE); 
		DO_JUMP ( JNE); 
		DO_JUMP (  JB); 
		DO_JUMP (  JA); 
		DO_JUMP (  JE);
		DO_JUMP (  JF); 

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

		//{-------------command-with-argument------------------------------
		case R_IN  : { asm_c =  IN; fprintf (fo, "%d ", asm_c); 
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
		
		DO_SMTH (DUMP);
		case R_FUNC : { break; }
		DO_JUMP (CALL);
		DO_SMTH ( RET);
		DO_SMTH ( HLT);
		DO_SMTH (  OR);
		DO_SMTH ( AND);
		DO_SMTH ( NOT);
		DO_SMTH ( XOR);

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

int asm_run (FILE *fi, FILE *fo)
{
	ASSERT (fi);
	ASSERT (fo);
	int ok = 1;
	char scanned[5] = {0};
	unsigned int command = 0;
	int x = 0;
	int mkdata[20] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

	if (asm_set_marks (&x, fi, mkdata)) return 1;
	fseek (fi, 0, SEEK_SET);
	x = 0;

	while (ok = fscanf (fi, "%s", scanned)) {

		if (scanned[0] == ':') 
			continue; // mark check.
		if (scanned[0] == '/') 
			continue; // ignore comments.
		
		x++;
		ASSERT (sizeof (int) >= 4);
		command = id_command (scanned);
		if (command == 0) return 0;

		scanned[0] = '\0';
		scanned[1] = '\0';
		scanned[2] = '\0';
		scanned[3] = '\0';

		if (asm_command (command, x, fi, fo, mkdata)) return x;
	}
	return 0;
}