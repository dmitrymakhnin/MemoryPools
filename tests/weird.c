#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *happy_msg;
} happy_t;

void happy_print(happy_t *happiness)
{
    happy_t tmp;
    printf(happiness->happy_msg);
}

int main(int argc, char **argv)
{
    happy_t *happiness = (happy_t *)malloc(sizeof(happiness));
    char *happy_msg = "Meep!";
    happiness->happy_msg = happy_msg;
    happy_print(happiness);
    free(happiness);

    return 0;
}