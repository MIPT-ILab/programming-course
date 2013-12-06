struct list_t
{
    double data;
    struct list_t *next;
};

void    list_stick_value_to                      (double data_value, struct list_t **target_list);
void    list_destructor                          (struct list_t *root_node);
void    print_list                               (const struct list_t *root_node);
struct  list_t *create_list_from_integers_1_to_n (unsigned int  n);
struct  list_t* remove_elems                     (struct list_t *root_node, double value);
