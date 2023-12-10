#include <stdio.h>
#define MAXN (int)(2e5 + 10) // maior valor de N
#define MAXR 500 // raiz para o pior valor de N
#define dbug(x) printf("x: %d\n", x)
#define ll long long

ll arr[MAXN], bucket[MAXR + 1];
int n, a, b;
char op; // operacao do enunciado

void build(int n)
{
	for (int i = 0; i < n; i++)
		bucket[i/MAXR] += arr[i]; // bucket[x] = soma dos elementos no bloco x
}

void update(int pos, ll val)
{
	bucket[pos/MAXR] -= arr[pos]; // tiro o valor antigo
	arr[pos] = val; // atualizo o array
	bucket[pos/MAXR] += arr[pos]; // adiciono o valor novo
}

ll query(int l, int r)
{
	ll soma = 0;
	while (l%MAXR != 0 && l <= r) // enquanto eu nao estiver no começo de um bloco
	{
		soma += arr[l];
		l++; // incremento o l
	}	

	while (r%MAXR != MAXR-1 && r >= l) // enquanto eu nao estiver no fim de um bloco
	{
		soma += arr[r];
		r--; // decremento r
	}

	while (l < r) // adiciono a soma dos blocos contidos no intervalo
	{
		soma += bucket[l/MAXR];
		l += MAXR;
	}

	return soma;
}

int main(void)
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%lld", &arr[i]);
	
	build(n);
	while (scanf("%s%d%d", &op, &a, &b) == 3)
	{
		if (op == 's') printf("%lld\n", query(a, b));
		else update(a, b);	
	}
}
