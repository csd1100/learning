#include <stdio.h>

int main()
{
    int n;

    for (int i = 0; i <= 5; i++)
    {
        printf("%d\n", i);
    }

    printf("Enter Number:");
    scanf("%d", &n);

    // printf("Numbers from 0 to %d.\n", n);
    // for (int i = 0; i < n; i++)
    // {
    //     printf("%d\n", i);
    // }

    // printf("Squares from 0 to %d.\n", n);
    // for (int i = 0; i < n; i++)
    // {
    //     printf("%d\n", i * i);
    // }
    // printf("Table %d.\n", n);
    // for (int i = 1; i <= 10; i++)
    // {
    //     printf("%d\n", n * i);
    // }
    printf("Numbers from 0 to %d Even Numbers.\n", n);
    for (int i = 1; i <= n; i++)
    {
        if (i % 2 == 1)
        {
            printf("%d\n", i);
        }
    }
    return 0;
}
