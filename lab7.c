#include <stdio.h>
#include <stdlib.h>
#define MAXN (int) 1e3 + 10  // limites estavam errados no enunciado (1e4 da mle)

int pode(int a, int b, int n, int m) // vejo se a, b estao nos bounds
{
	return (a>=0 && a<n && b>=0 && b<m);
}

void dfs(int a, int b, int n, int m, char tab[MAXN][MAXN]) // dfs
{
	if (!pode(a, b, n, m) || tab[a][b] != '@') return;
	tab[a][b] = '#';
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			dfs(a + i, b + j, n, m, tab);
}

int main(void)
{
	int n, m;
	char tab[MAXN][MAXN]; // matriz
	while (scanf("%d%d", &n, &m) && n && m)
	{
		int resp = 0; // resposta
		for (int i = 0; i < n; i++)
		    scanf("%s", tab[i]);	

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (tab[i][j] == '@') // se é petroleo
				{
					resp++;
					dfs(i, j, n, m, tab); // marco a componente como visitada			
				}
			}
		}
		printf("%d\n", resp);
	}
}
