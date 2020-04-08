#include <stdio.h>

int main()
{

    int num;
    printf("Enter Number:");
    scanf("%d", &num);

    if (num > 10)
    {
        printf("%d is Greater Than 10\n", num);
    }

    int num1;
    printf("Enter Number:");
    scanf("%d", &num1);

    if (num1 > 10)
    {
        printf("%d is Greater Than 10\n", num1);
    }
    else
    {
        printf("%d is not greater than 10\n", num1);
    }

    int num2;
    printf("Enter Number:");
    scanf("%d", &num2);

    if (num2 > 100)
    {
        printf("%d is Greater Than 100\n", num2);
    }
    else if (num2 > 50)
    {
        printf("%d is greater than 50 nut less than 100\n", num2);
    }
    else
    {
        printf("%d is less than 50\n", num2);
    }

    return 0;
}