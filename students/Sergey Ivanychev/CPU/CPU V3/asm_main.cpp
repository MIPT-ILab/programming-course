
#include "cpu.h"
#include "command_codes.h"

const int LENGTH_MARKS = 20;


/**
			main						Function builds executable.txt and executable.ivz (my own format:) files and uses asm()
										executable.txt contains all instructions and arguments printed in .txt file using '\n'
										executable.ivz is kind of the same file, but the data has been saved in binary format
			@return						0
**/
int asm_main()
{
	FILE* strin  = fopen("code.txt", "r");
	FILE* strout_bin = fopen("executable.ivz", "wb");
	FILE* strout_txt = fopen("executable.txt", "w");
	FILE* strerr = fopen("asm_log.txt", "w");

	pointer pts[NUM_OF_POINTERS] = {};
	for (int i = 0; i < NUM_OF_POINTERS; ++i)
	{
		(pts[i]).mark = POISON_MARK;
		for (int j = 0; j < 15; ++j) (pts[i]).name[j] = 0;
	}

	double* code = assemble(strin, strerr, pts);

	if (code == NULL) 
	{
		fprintf(strerr, "\nAssemble failed\n");

		fclose(strin);
		fclose(strout_txt);
		fclose(strout_bin);
		
		strout_bin = fopen("executable.ivz", "wb");
		strout_txt = fopen("executable.txt", "w");

		fclose(strout_txt);
		fclose(strout_bin);

		
		fclose(strerr);
		return ASM_FAIL;
	}
	
	fclose(strin);
	strin = fopen("code.txt", "r");

	code = assemble(strin, strerr, pts);

	
	
	int i = 0;
	while (code[i++] != CMD_END) fprintf(strout_bin, "%lg ", code[i - 1]);
	fprintf(strout_bin, "%lg ", code[i - 1]);
	
	i = 0;
	while (code[i++] != CMD_END) fprintf(strout_txt, "%lg\n", code[i - 1]);
	fprintf(strout_txt, "%lg\n", code[i - 1]);
	
	fclose(strin);
	fclose(strout_txt);
	fclose(strout_bin);
	fclose(strerr);
	
	free(code);

	return ASM_OK;
}
