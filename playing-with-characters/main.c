#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main()
{
    char chr;
    char s[100];
    char ln[100];

    scanf("%c", &chr);

    scanf("\n");

    scanf("%[^\n]%*c", s);

    scanf("\n");

    scanf("%[^\n]%*c", ln);

    printf("%c\n", chr);

    printf("%s\n", s);

    printf("%s\n", ln);

    return 0;
}