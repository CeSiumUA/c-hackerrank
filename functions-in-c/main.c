#include <stdio.h>

int max_of_four(int a, int b, int c, int d){
    int arr[4] = {a, b, c, d};

    int max = a;

    for(int i = 1; i < 4; i++){
        int elem = arr[i];
        if(elem > max){
            max = elem;
        }
    }

    return max;
}

int main() {
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    int ans = max_of_four(a, b, c, d);
    printf("%d", ans);
    
    return 0;
}