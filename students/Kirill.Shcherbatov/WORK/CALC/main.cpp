#include "libs.h"
#include "hash_t.h"

#define VAR_HASH_SIZE 50

char *input_data = NULL,
     *input_data_addr_copy = NULL;

struct hash_table_t **var_hash;


char* NormalizeStr (char *str, char *mask);
void MemoryFree();
void BugEnd();
double GetG0();
double GetE();
double GetN();
double GetP();
double GetT();
double GetId ();
double GetO ();

void MemoryFree ()
{
    OUT ("# starting memory unlocking\n");
        free (input_data_addr_copy);
        input_data = NULL;
        input_data_addr_copy = NULL;
        free_table (var_hash, VAR_HASH_SIZE);
        free (var_hash);
        var_hash = NULL;
    OUT ("# starting memory unlocking\t -- OK!\n");
}

void BugEnd ()
{
    printf ("!:\t%s\n!:\t", input_data_addr_copy);
    for (register unsigned i = 0; i<input_data-input_data_addr_copy; i++)
        putchar (' ');
    printf ("^ wrong char/operation/var %c\n", *input_data);
    MemoryFree ();
    exit(1);
}

char* NormalizeStr (char *str, char *mask)
{
  assert (str != NULL);

  char *buffer = strdup(str);
  char buffer_size = 0;

  for (register unsigned i=0; str[i]!='#'; i++)
    {
      char flag = 0;
      if (
        ('a' <= str[i] && str[i] <= 'z')
        ||
        ('A' <= str[i] && str[i] <= 'Z')
        ||
        ('0' <= str[i] && str[i] <= '9')
         ) flag = 1;
      else
        for (register unsigned j=0; j<strlen(mask); j++)
          if (mask[j] == str[i])
            {
              flag = 1;
              break;
            }
      if (flag == 1)
        buffer[buffer_size++] = str[i];
    }
  buffer[buffer_size++] = '#';
  buffer[buffer_size++] = '\0';
  return buffer;
}

double GetG0 ()
{
    OUT ("# Called GetG0()\n");
    OUT ("# input_data addr is [%p]\n", input_data);

    assert (input_data != NULL);
    assert (input_data_addr_copy != NULL);

    double res = 0.0;

    do
    {
      res = GetO ();
      while (*input_data == ';') input_data++;

    } while (*input_data != '#');

    OUT ("# end GetG0(); will return %lg\n", res);
    return res;
}

double GetO ()
{
  OUT ("# Called GetO; input_data [%p]* is %s\n", input_data, input_data);

  assert (input_data != NULL);
  assert (input_data_addr_copy != NULL);
  while (*input_data == ';') input_data++;
  if (*input_data == '{')
    {
      OUT ("# Finded {\n");
      input_data++;
      double val = 0;
      while (*input_data != '}')
        val = GetE ();
      input_data++;
      return val;
    } else return GetE ();

}

double GetN ()
{
    OUT ("# Called GetN; input_data [%p]* is %s\n", input_data, input_data);

    assert (input_data != NULL);
    assert (input_data_addr_copy != NULL);

    while (*input_data == ';') input_data++;

    double val = 0;
    if ('0' <= *input_data && *input_data <= '9')
      {
        while ('0' <= *input_data && *input_data <= '9')
        {
            val = val*10 + *input_data - '0';
            input_data++;
        }
        // reading digits after the decimal point
        if (*input_data == '.')
          {
            input_data++;
            if ('0' <= *input_data && *input_data <= '9')
              {
                OUT("DIG\n");
                char dig_n = 0;
                double val2 = 0;
                while ('0' <= *input_data && *input_data <= '9')
                {
                    val2 = val2*10 + *input_data - '0';
                    input_data++;
                    dig_n++;
                }
                val+=val2/pow(10, dig_n);
              }
            else
              {
                printf ("!:\tNo digits after the decimal point\n");
                BugEnd ();
              }
          }
         // end reading digits after the decimal point
      }
    else BugEnd();
    OUT ("# end GetN; will return %lg\n", val);
    return val;
}


double GetE ()
{
    OUT ("# Called GetE; input_data [%p]* is %s\n", input_data, input_data);

    assert (input_data != NULL);
    assert (input_data_addr_copy != NULL);

    while (*input_data == ';') input_data++;

    double val = GetT ();
    while (*input_data == '+' || *input_data == '-')
    {
        char op = *input_data++;
        double val2 = GetT ();
        if (op == '+') val += val2;
        if (op == '-') val -= val2;
    }
    OUT ("# end GetE; will return %lg\n", val);

    return val;
}

double GetT ()
{
    OUT ("# called GetT; input_data [%p]* is %s\n", input_data, input_data);

    assert (input_data != NULL);
    assert (input_data_addr_copy != NULL);

    while (*input_data == ';') input_data++;

    double val = GetP ();
    while (*input_data == '*' || *input_data == '/')
    {
        char op = *input_data++;
        double val2 = GetP ();
        if (op == '/' && val2 == 0)
        {
            printf ("!:\tDevision by zero!\n");
            input_data-=1;
            BugEnd ();
        }
        if (op == '*') val *= val2;
        if (op == '/') val /= val2;
    }
    OUT ("# end GetT; will return %lg\n", val);
    return val;
}

double GetP ()
{
    OUT ("# Called GetP; input_data [%p]* is %s\n", input_data, input_data);

    assert (input_data != NULL);
    assert (input_data_addr_copy != NULL);

    while (*input_data == ';') input_data++;

    double val = 0;
    if (*input_data == '(')
    {
        input_data++;
        val = GetE();
        if (*input_data++ != ')')
        {
            printf ("!:\tMissing closing brace ')'\n");
            BugEnd ();
        }
    } else
      if (('a' <= *input_data && *input_data <= 'z')
          ||
          ('A' <= *input_data && *input_data <= 'Z')
         ) val = GetId (); else val = GetN ();

    if (*input_data == '^')
      {
        input_data++;
        double val2 = 0;
        val2 = GetP ();
        if (val == 0 && val2 == 0) val = 1;
          else val = pow(val, val2);
      }
    OUT ("# end GetP; will return %lg\n", val);
    return val;
}

double GetId ()
{
  OUT ("# Called GetId; input_data [%p]* is %s\n", input_data, input_data);

  assert (input_data != NULL);
  assert (input_data_addr_copy != NULL);assert (input_data != NULL);
  assert (input_data_addr_copy != NULL);

  while (*input_data == ';') input_data++;

  char *Id = (char *)calloc (255, sizeof(char));
  register unsigned i = 0;
  while (('a' <= *input_data && *input_data <= 'z')
         ||
         ('A' <= *input_data && *input_data <= 'Z')
         ||
         ('0' <= *input_data && *input_data <= '9')
         ||
         (*input_data == '_')
        )
    {
      Id[i++] = *input_data++;
    }

  OUT ("# ID now is '%s'\n", Id);
  if (*input_data != '=')
    {
      struct hash_table_t *var = find_in_table (Id, (const struct hash_table_t **)var_hash, VAR_HASH_SIZE);
      if (var != NULL)
        {
          return var -> value;
        } else
            {
              printf ("!:\tUnknown var '%s'\n", Id);
              free (Id);
              BugEnd ();
            }
    } else
          {
            input_data++;
            double val = GetE ();
            add_data_in_table (Id, val, var_hash, VAR_HASH_SIZE);
            return val;
          }

  free (Id);
  assert("WTF DO I HERE?!\n");
  return 0;
}

int main (int, char *argv[])
{
    OUT ("# called main() with *(argv+1) = '%s'\n", *(argv+1));

    input_data = NULL;
    if (argv[1] != NULL) input_data = strdup (argv[1]);
        else
            {
                OUT ("# try to lock memory for char array[255]\n");
                    input_data = (char *)calloc (255, sizeof (char));
                    assert (input_data != NULL);
                OUT ("# try to lock memory for char array[255]\t -- OK!\n");

                do
                {
                    printf ("Enter your expression\n");
                    scanf ("%[^#]", input_data);
                    strcat(input_data, "#");
                } while (input_data == NULL);
            }

    OUT ("# try to lock memory for hash array[%d]\n", VAR_HASH_SIZE);
        var_hash = (struct hash_table_t **)calloc(VAR_HASH_SIZE, sizeof(struct hash_table_t *));
        assert (var_hash != NULL);
    OUT ("# try to lock memory for char array[%d]\t -- OK!\n", VAR_HASH_SIZE);

    add_data_in_table ("PI", M_PI, var_hash, VAR_HASH_SIZE);
    add_data_in_table ("E", M_E, var_hash, VAR_HASH_SIZE);
    if (input_data[strlen(input_data)-1] != '#')
      strcat (input_data, "#");
    char *temp = NormalizeStr (input_data, (char*)"_^*/+-()=;");
    free(input_data);
    input_data = temp;
    input_data_addr_copy = input_data;

    double res = GetG0();

    printf ("Result is %lg\n", res);
    MemoryFree ();

    OUT ("# end main()\n");

    return 0;
}
