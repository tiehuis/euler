#include <stdio.h>

#define I 1
#define V 5
#define X 10
#define L 50
#define C 100
#define D 500
#define M 1000

/* Converts a roman numeral to it's integer representation */
int strtoroman(char *str)
{
    int value = 0;
    while (*str) {
        switch (*str) {
        case 'I':
            if (str[1] == 'V' || str[1] == 'X')
                value -= I;
            else
                value += I;
            break;
        case 'V':
            value += V;
            break;
        case 'X':
            if (str[1] == 'L' || str[1] == 'C')
                value -= X;
            else
                value += X;
            break;
        case 'L':
            value += L;
            break;
        case 'C':
            if (str[1] == 'D' || str[1] == 'M')
                value -= C;
            else
                value += C;
            break;
        case 'D':
            value += D;
            break;
        case 'M':
            value += M;
            break;
        default:
            return -1;
        }
        str++;
    }
    return value;
}

/* Calculates the number of symbols required to represent n */
int minroman(int n)
{
    int c = 0;

#define cond(cond, inc)\
    do {\
        while (n >= (cond)) {\
            n -= (cond);\
            c += (inc);\
        }\
    } while (0)

    cond( M   , 1 );
    cond( M-C , 2 );
    cond( D   , 1 );
    cond( D-C , 2 );
    cond( C   , 1 );
    cond( C-X , 2 );
    cond( L   , 1 );
    cond( L-X , 2 );
    cond( X   , 1 );
    cond( X-I , 2 );
    cond( V   , 1 );
    cond( V-I , 2 );
    cond( I   , 1 );
    return c;

#undef cond
}

int main(void)
{
    FILE *fd  = fopen("res/089.data", "r");
    int sum   = 0;
    int lines = 1;
    char str[100];

    while (fscanf(fd, "%100s", str) != EOF) {
        ++lines;
        int v = strtoroman(str);
        sum -= minroman(v);
    }

    sum += (ftell(fd) - lines);
    printf("%d\n", sum);
    return 0;
}
