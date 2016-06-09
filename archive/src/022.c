#include <stdio.h>
#include <ctype.h>

int name_value(char *s)
{
    int value = 0;
    while (*s)
        value += (toupper(*s++) - 'A') + 1;
    return value;
}

int main(void)
{
    FILE *fd = fopen("../res/022.data", "r");
    char str[30];
    long name_sum = 0;
    size_t position = 1;

    while (fscanf(fd, "%30s", str) != EOF)
        name_sum += position++ * name_value(str);

    printf("%ld\n", name_sum);
    return 0;
}
