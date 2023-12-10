#include <stdio.h>
#include <math.h>
#define ll long long

ll a, b; // variaveis globais inicializadas com 0

ll soma(ll x)
{
	ll resp = 0;
	for (int i = 2; i*i <= x; i++)
	{
		if (x%i==0)
		{
			resp += i;
			if (i != x/i) resp += (x/i);
		}
	}

	return resp+(x>1?1:0);
}

int main(void)
{
	scanf("%lld%lld", &a, &b);
	printf("%lld e %lld ", a, b);
	printf((soma(a)==b&&soma(b)==a&&a!=b ? "sao amigos\n" : "nao sao amigos\n"));
}