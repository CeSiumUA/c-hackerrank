#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct triangle
{
	int a;
	int b;
	int c;
};
typedef struct triangle triangle;

struct triangle_square_pair
{
    triangle tr;
    double sq;
};
typedef struct triangle_square_pair triangle_square_pair;

double triangle_square(triangle tr){
    double p = (double)(tr.a + tr.b + tr.c) / 2;
    return sqrt(p * (p - tr.a) * (p - tr.b) * (p - tr.c));
}

void sort_by_area(triangle* tr, int n) {
	triangle_square_pair *tr_sq = malloc(n * sizeof(triangle_square_pair));
    for(int i = 0; i < n; i++){
        triangle t = tr[i];
        triangle_square_pair p = {.tr = t, .sq = triangle_square(t)};
        tr_sq[i] = p;
    }

    int needsRun = 1;
    while (needsRun)
    {
        needsRun = 0;
        for(int i = 1; i < n; i++){
            if(tr_sq[i - 1].sq > tr_sq[i].sq){
                triangle_square_pair temp = tr_sq[i];
                tr_sq[i] = tr_sq[i - 1];
                tr_sq[i - 1] = temp;
                tr[i] = tr[i - 1];
                tr[i - 1] = temp.tr;
                needsRun = 1;
            }
        }
    }
}

int main()
{
	int n;
	scanf("%d", &n);
	triangle *tr = malloc(n * sizeof(triangle));
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &tr[i].a, &tr[i].b, &tr[i].c);
	}
	sort_by_area(tr, n);
	/*for (int i = 0; i < n; i++) {
		printf("%d %d %d\n", tr[i].a, tr[i].b, tr[i].c);
	}*/
	return 0;
}