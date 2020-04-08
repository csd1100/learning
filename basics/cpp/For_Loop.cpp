#include <stdio.h>

int main()
{
    int n;

    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", i);
    }

    printf("Enter Number:");
    scanf("%d", &n);

    printf("Numbers from 0 to %d.\n", n);
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", i);
    }

    printf("Squares from 0 to %d.\n", n);
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", i * i);
    }
    printf("Numbers from 0 to %d increasing by 2.\n", n);
    for (int i = 0; i < n; i += 2)
    {
        printf("%d\n", i);
    }
    return 0;
}