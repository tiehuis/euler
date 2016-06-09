#include <stdio.h>
#include <gmp.h>

#define alim 100
#define blim 100
#define size (alim * blim)

/* sdbm hash */
int quick_hash(mpz_t a)
{
    char strrep[201 + 1]; /* 100^100 is 201 digits */
    char *s = strrep;
    mpz_get_str(strrep, 10, a);
    
    int hash = 0;
    while (*s)
        hash = *s++ + (hash << 6) + (hash << 16) - hash;

    return hash;
}

int main(void)
{
    mpz_t p;
    mpz_init(p);

    /* Utilizing a proper hashmap would have a
     * noticeable increase in speed */
    int map[size] = { 0 };
    int index     = 0;

    int a, b;
    for (a = 2; a <= alim; ++a) {
        for (b = 2; b <= blim; ++b) {
            mpz_ui_pow_ui(p, a, b);

            int hash = quick_hash(p);
            int i = 0;
            while (i < index) {
                if (map[i] == hash)
                    break;
                ++i;
            }

            if (i == index)
                map[index++] = hash;
        }
    }

    printf("%d\n", index);
    return 0;
}
