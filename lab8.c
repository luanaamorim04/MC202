#include <stdio.h>
#define MAXN (int) (2e5 + 10)

struct Par 
{
	int pos, val;
};

int main(void)
{
	int n;
	while (scanf("%d", &n) && n)
	{
		int resp = 1, arr[n], ini = -1, soma[n];
		struct Par pilha[n];
		for (int i = 0; i < n; i++)
			soma[i] = 0;
		for (int i = 0; i < n; i++)
		{
			scanf("%d", &arr[i]);
			pilha[++ini].val = arr[i]; //push
			pilha[ini].pos = i;
			if (pilha[ini].val > 0)
			{
				if (pilha[--ini].val != -arr[i]) //pop
					resp = 0;
				else 
					--ini; //pop

				if (ini != -1) soma[pilha[ini].pos] += arr[i];
			}
		}

		for (int i = 0; i < n; i++)
		{
			if (arr[i] < 0) resp &= (soma[i] < -arr[i]);
		}

		printf(resp ? ":-) Matriosca!\n" : ":-( Tente novamente.\n");
			
	}
}
