#include <stdio.h>
#include <math.h>

double n, m, r1, r2, c1, c2, b1, b2;

double dist(double a, double b) //calcula norma de um vetor
{
	return sqrt(a*a + b*b);
}

int main(void)
{
	scanf("%lf%lf%lf%lf%lf", &n, &c1, &c2, &r1, &r2); 
	while (n--)
	{
		scanf("%lf%lf", &b1, &b2);
		if (dist(r1-b1, r2-b2) >= dist(c1-b1, c2-b2)*2)
		{
			printf("O coelho pode escapar pelo buraco (%.3lf,%.3lf).\n", b1, b2);
			return 0;
		}
	}

	printf("O coelho nao pode escapar.\n");
	return 0;
}
