#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void print_row(int rownum, int n){
    int depth = abs(n - rownum);

    int isUpscending = 0;

    for(int i = n; i >= 1 && i <=n;){
        if(i < depth){
            printf("%d ", depth);
        } else{
            printf("%d ", i);
        }
        if(i == 1){
            isUpscending = 1;
        }

        if(isUpscending){
            i++;
        } else{
            i--;
        }
    }
}

int main() 
{

    int n;
    scanf("%d", &n);

    int isUpscending = 0;

    for(int i = n; i >= 1 && i <= n;){
        print_row(n - i, n);
        printf("\n");

        if(i == 1){
            isUpscending = 1;
        }

        if(isUpscending){
            i++;
        } else{
            i--;
        }
    }

    return 0;
}