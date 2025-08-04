#include <stdio.h>

int main()
{

    int a = 5;
    char b = 'a';
    double c = 1.00099;
    float d = 1.002;

    printf("%d\n", a);
    printf("%c\n", b);
    printf("%0.2f\n", d);
    printf("%lf\n", c);

    int integer;
    char character;
    double double_number;
    float float_number;
    bool boolean1 = true;  //1
    bool boolean2 = false; //0

    printf("\nEnter Integer:");
    scanf("%d", &integer);
    getchar();
    printf("\nEnter Character:");
    scanf("%c", &character);
    printf("\nEnter Double:");
    scanf("%lf", &double_number);
    printf("\nEnter Float:");
    scanf("%f", &float_number);

    printf("Integer: %d\n", integer);
    printf("Character: %c\n", character);
    printf("Double: %lf\n", double_number);
    printf("Float: %1f\n", float_number);

    printf("Data: %d %f %lf %c", character, float_number, double_number, character);

    return 0;
}