#include <stdio.h>

/* Returns n! computed iteratively */
long long factorial(int n)
{
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main(void)
{
    int n;

    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        printf("Error: invalid input.\n");
        return 1;
    }

    if (n < 0) {
        printf("Error: factorial is not defined for negative numbers.\n");
        return 1;
    }

    if (n > 20) {
        printf("Error: %d! does not fit in a long long (max n is 20).\n", n);
        return 1;
    }

    printf("%d! = %lld\n", n, factorial(n));
    return 0;
}