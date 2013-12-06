#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "defines.h"
#include "tree_t.cpp"

int main(int, char *argv[])
{
	OUT("# %s \n"
		"# (%s)\n"
		"# %s %s:\n\n",
		argv[0], __FILE__, __DATE__, __TIME__);

    FILE *f = fopen ("tree.txt", "r");
    assert (f != NULL);

    char *memory = (char *)calloc(128, sizeof(char));
    assert (memory != NULL);

    unsigned i = 0;
    while (fscanf (f, "%c", &memory[i]) != EOF) i++;
    fclose (f);

    unsigned int idx = 0;
    struct tree_elem_t *my_tree = tree_read (memory, &idx, IN_ORDER);

    free (memory);

    f = fopen ("tree_result.txt", "w");
    tree_print (my_tree, f, POST_ORDER);
    fclose(f);

    tree_destructor (my_tree);

    return 0;
}
