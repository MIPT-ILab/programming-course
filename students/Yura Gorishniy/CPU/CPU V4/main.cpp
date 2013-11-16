#include "cpu.h"

int main()
{
    cpu* the_cpu = Cpu_Construct();

	FILE* output      = fopen ("output.txt", "w");
	FILE* the_log	  = fopen ("the_log.txt", "w");
	
    OUT printf ("# This is an emulator of Intel Core i7\n"
                "# The developer:     Yura Gorishniy     <strausmg@gmail.com>\n"
                "# Version 3.00\n"
                "# The file: %s\n"
                "# The compilation time: %s, %s\n\n", strrchr (__FILE__, '\\'), __DATE__, __TIME__);
	
	FILE* the_program = fopen ("the_program.txt", "r");
	FILE* binary	  = fopen ("binary.txt", "w");
	Check_Error (the_asm  (the_program, binary, the_log), the_log);
	fclose (binary);
	fclose (the_program);

	the_program = fopen ("the_program.txt", "r");
	binary = fopen ("binary.txt", "w");
	Check_Error (the_asm  (the_program, binary, the_log), the_log);
	fclose (binary);

	binary = fopen ("binary.txt", "r");
	Check_Error (Cpu_Load (the_cpu, binary), the_log);
	Check_Error (Cpu_Run  (the_cpu, output, the_log), the_log);

	fclose (the_log);
	fclose (the_program);
	fclose (binary);

return 0;
}
