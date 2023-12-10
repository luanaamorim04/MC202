#include <stdio.h>
#include <stdlib.h>

typedef struct Grafo
{
	int x;
	struct Grafo *nxt;
} Grafo;

Grafo *add(int v)
{
	Grafo *novo = malloc(sizeof(Grafo));
	novo->x = v;
	novo->nxt = NULL;
	return novo;
}

void dfs(int u, int *nivel, Grafo **grafo, Grafo **niveis, Grafo **last)
{
	nivel[u] = 0;
	for (Grafo *v = grafo[u]; v != NULL; v = v->nxt)
	{
		if (nivel[v->x] == -1) dfs(v->x, nivel, grafo, niveis, last);
		nivel[u] = (nivel[u] > nivel[v->x] + 1 ? nivel[u] : nivel[v->x] + 1);
	}	

	if (last[nivel[u]] == NULL) niveis[nivel[u]] = last[nivel[u]] = add(u); 
	else last[nivel[u]]->nxt = add(u), last[nivel[u]] = last[nivel[u]]->nxt;
}

int main()
{
	int n, m, a, b;
	scanf("tarefas: %d", &n);
	scanf(" precedencias: %d", &m);
	Grafo *grafo[n + 10], *last[n + 10], *niveis[n + 10];
	int nivel[n + 10];
	for (int i = 0; i < n; i++)
		nivel[i] = -1, grafo[i] = niveis[i] = last[i] = NULL;

	while (m--)
	{
		scanf("%d%d", &a, &b);
		if (last[a] == NULL) grafo[a] = last[a] = add(b);
		else last[a]->nxt = add(b), last[a] = last[a]->nxt; 
	}

	for (int i = 0; i < n; i++)
		last[i] = NULL;

	for (int i = 0; i < n; i++)
		if (nivel[i] == -1) dfs(i, nivel, grafo, niveis, last);

	for (int i = 0; i < n; i++)
	{
		if (niveis[i] == NULL) continue;
		for (Grafo *g = niveis[i]; g != NULL; g = g->nxt)
			printf("%d ", g->x);
		printf("\n");
	}

	for (int i = 0; i < n; i++)
	{
		while (grafo[i] != NULL)
		{
			Grafo *tmp = grafo[i]->nxt;
			free(grafo[i]);
			grafo[i] = tmp;
		}

		while (niveis[i] != NULL)
		{
			Grafo *tmp = niveis[i]->nxt;
			free(niveis[i]);
			niveis[i] = tmp;
		}
	}
}
