#include <stdio.h>
#include <stdlib.h>
#define MAXN 100000
#define min(x, y) (x<y?x:y)

typedef struct Grafo
{
	int x;
	struct Grafo *nxt;
} Grafo;

Grafo **deleta(int n, Grafo **tail, Grafo **grafo, int *vis, int *resp, int *tin, int *low)
{
	for (int i = 1; i <= n; i++)
	{
		resp[i] = vis[i] = low[i] = tin[i] = 0;
		while (grafo[i] != NULL)
		{
			Grafo *tmp = grafo[i]->nxt;
			free(grafo[i]);
			grafo[i] = tmp;
		}
		tail[i] = NULL;
	}
	return grafo;
}

Grafo *add(int v)
{
	Grafo *novo = malloc(sizeof(Grafo));
	novo->x = v;
	novo->nxt = NULL;
	return novo;
}

void printa(int n, Grafo **grafo)
{
	for (int i = 1; i <= n; i++)
	{
		printf("u: %d\n", i);
		for (Grafo *g = grafo[i]; g != NULL; g = g->nxt)
			printf("%d ", g->x);
		printf("\n");
	}
}

void dfs(int u, int p, Grafo **grafo, int *resp, int *vis, int *tin, int *low, int *t)
{
	vis[u] = 1;
	tin[u] = low[u] = ++(*t);
	int child = 0;
	for (Grafo *v = grafo[u]; v != NULL; v = v->nxt)
	{
		if (v->x == p) continue;
		if (vis[v->x] == 1) //sobe 
			low[u] = min(low[u], tin[v->x]);
		else
		{
			dfs(v->x, u, grafo, resp, vis, tin, low, t);
			low[u] = min(low[u], low[v->x]);
			if (low[v->x] >= tin[u] && p != 0)
				resp[u] = 1;
			child++;
		}
	}

	if (p == 0 && child > 1)
		resp[u] = 1;
}

int existe(Grafo **grafo, int a, int b)
{
	for (Grafo *g = grafo[a]; g != NULL; g = g->nxt)
		if (g->x == b) return 1;
	return 0;
}

int main()
{
	int n, u, v, vis[MAXN], resp[MAXN], tin[MAXN], low[MAXN];
	Grafo *grafo[MAXN], *tail[MAXN];
	for (int i = 1; i < MAXN; i++)
		tail[i] = grafo[i] = NULL, resp[i] = vis[i] = low[i] = tin[i] = 0;
	while (scanf("%d", &n) && n)
	{
		int t = 0, ans = 0;
		while (scanf("%d", &u) && u)
		{
			do
			{
				scanf("%d", &v);
				if (!existe(grafo, u, v))
				{
					if (grafo[u] == NULL) tail[u] = grafo[u] = add(v);
					else tail[u]->nxt = add(v), tail[u] = tail[u]->nxt;
				}

				if (!existe(grafo, v, u))
				{
					if (grafo[v] == NULL) tail[v] = grafo[v] = add(u);
					else tail[v]->nxt = add(u), tail[v] = tail[v]->nxt;
				}
			} while (getchar() != '\n');		
		}

		//printa(n, grafo);
		for (int i = 1; i <= n; i++)
		{
			if (!vis[i]) dfs(i, 0, grafo, resp, vis, tin, low, &t);
			ans += resp[i];
			//printf("resp[%d] == %d\n", i, resp[i]);
		}

		deleta(n, tail, grafo, vis, resp, tin, low);
		printf("%d\n", ans);
	}
}
