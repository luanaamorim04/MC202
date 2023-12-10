#include <stdio.h>
#include <stdlib.h>
#define INF (int) (1e9 + 7)
#define esq(x) (x<<1)
#define dir(x) ((x<<1)|1)

typedef struct Par
{
	int num, val;
} Par;

void swap(Par *a, Par *b)
{
	Par t = *a;
	*a = *b;
	*b = t;
}

void swapi(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int menor(Par a, Par b)
{
	if (a.val != b.val) return a.val < b.val;
	return a.num <= b.num;
}

void add(Par *heap, int *pos, int v, int c, int tam)
{
	int pai = tam/2;
	heap[tam].val = v;
	heap[tam].num = c;
	pos[c] = tam;
	while (pai)
	{
		if (menor(heap[pai], heap[tam])) break;
		swap(&heap[pai], &heap[tam]);
		swapi(&pos[heap[pai].num], &pos[heap[tam].num]);
		tam = pai;
		pai = pai/2;
	}
}

Par deleta(Par *heap, int *pos, int tam)
{
	Par resp = heap[1];
	swap(&heap[1], &heap[tam]);
	pos[heap[tam].num] = -1;
	heap[tam] = (Par){INF, INF};
	int p = 1;

	while (p < tam)
	{
		if (menor(heap[esq(p)], heap[dir(p)]))
		{
			if (menor(heap[p], heap[esq(p)])) break;
			swap(&heap[p], &heap[esq(p)]);
			swapi(&pos[heap[p].num], &pos[heap[esq(p)].num]);
			p = esq(p);
		}
		else 
		{
			if (menor(heap[p], heap[dir(p)])) break;
			swap(&heap[p], &heap[dir(p)]);
			swapi(&pos[heap[p].num], &pos[heap[dir(p)].num]);
			p = dir(p);
		}
	}
//	for (int i = 1; i < tam; i++)
//		printf("heap[%d] = %d\n", i, heap[i].val);
//	printf("\n");
	
	return resp;
}

void diminui(Par *heap, int *pos, int c, int d)
{
	int p = pos[c];
	int pai = p / 2;
	heap[p].val = d;
	while (pai)
	{
		if (menor(heap[pai], heap[p])) break;
		swap(&heap[pai], &heap[p]);
		swapi(&pos[heap[pai].num], &pos[heap[p].num]);
		p = pai;
		pai = pai/2;
	}
}

int main()
{
	Par *heap = NULL;
	char op;
	int n, v, c, tam = 0;
	int *pos = NULL;
	while (scanf("%c", &op))
	{
		if (op == 'c')
		{
			scanf("%d", &n);
			n *= 3;
			heap = realloc(heap, sizeof(Par) * n);
			pos = realloc(pos, sizeof(int) * n);
			for (int i = 0; i < n; i++) pos[i] = -1, heap[i] = (Par){INF, INF};
			tam = 0;
		}
		else if (op == 'i')
		{
			scanf("%d%d", &v, &c);
			if (pos[v] == -1) add(heap, pos, c, v, ++tam);
		}
		else if (op == 'm')
		{
			if (tam == 0) 
			{
				printf("heap vazio\n");
			}
			else
			{
				Par resp = deleta(heap, pos, tam--);
				printf("minimo {%d,%d}\n", resp.num, resp.val);
			}

		}
		else if (op == 'd')
		{
			scanf("%d%d", &v, &c);
			diminui(heap, pos, v, c);
		}
		else
		{
			free(heap);
			free(pos);
			return 0;
		}
		getchar();
	}
}


