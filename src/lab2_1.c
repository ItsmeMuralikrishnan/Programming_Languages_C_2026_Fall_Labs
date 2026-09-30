#include <stdio.h>

/* Returns the sum of integers 1..n using a for loop */
int sum_to_n(int n)
{
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    return sum;
}

int main(void)
{
    int n;

    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        printf("Error: invalid input.\n");
        return 1;
    }

    if (n < 1) {
        printf("Error: n must be at least 1.\n");
        return 1;
    }

    printf("Sum of 1..%d = %d\n", n, sum_to_n(n));
    return 0;
}