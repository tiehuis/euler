#include <stdio.h>

#define H 80
#define W 80

int min_child(int matrix[H][W], const int i, const int j)
{
    int low = i < H - 1 ? matrix[i + 1][j] : 0;
    int sid = j < W - 1 ? matrix[i][j + 1] : 0;

    if (!sid) return low;
    if (!low) return sid;

    return sid < low ? sid : low;
}

int main(void)
{
    FILE *fd = fopen("res/081.data", "r");
    int matrix[H][W];

    int i, j;
    for (i = 0; i < H; ++i) {
        for (j = 0; j < W; ++j) {
            if (fscanf(fd, "%d,", &matrix[i][j]) == EOF) 
                return 1;
        }
    }
    fclose(fd);

    /* Backtrack */
    for (i = H - 1; i >= 0; --i) {
        for (j = W - 1; j >= 0; --j) {
            matrix[i][j] += min_child(matrix, i, j);
        }
    }

    printf("%d\n", matrix[0][0]);
    return 0;
}
