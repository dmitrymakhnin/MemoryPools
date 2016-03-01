#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include "pools.h"

int main(int argc, char **argv)
{
    pools::init();
    pools::report_status();

    char *my_memory = (char *)pools::malloc(strlen("hello, world!") + 1);
    printf("my_memory = %d.\n", (int)my_memory);

    strcpy(my_memory, "hello, world!");
    pools::report_status();
    printf("%s.\n", my_memory);
    pools::report_status();
    pools::free(my_memory);

    my_memory = (char *)pools::malloc(strlen("WORKS!") + 1);
    strcpy(my_memory, "WORKS!");
    printf("%s.\n", my_memory);
    pools::report_status();
    pools::free(my_memory);

    pools::report_status();

    return 0;    
}