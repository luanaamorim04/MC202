#include <stdio.h>
#include <stdlib.h>

typedef struct List 
{
	char tipo;
	char c;
	char *s;
	int i;
	float d;
	struct List *nxt;
} List;

List *rev(List *head, int i, int j)
{
	if (i == j) return head;

	List *esq = head, *cur, *prev;
	for (int c = 0; c < i; c++, esq = esq->nxt);
	
	prev = esq->nxt;
	cur = prev->nxt;
	for (int c = i+1; c <= j; c++)
	{
		List *tmp = cur->nxt;
		cur->nxt = prev;
		prev = cur;
		cur = tmp;		
	}

	esq->nxt->nxt = cur;
	esq->nxt = prev;
	return head;
}

void printa(List *Lista)
{
	for (List *l = Lista; l != NULL; l = l->nxt)
	{
		if (l->tipo == 'c') printf("%c ", l->c);
		else if (l->tipo == 's') printf("%s ", l->s);
		else if (l->tipo == 'd') printf("%d ", l->i);
		else if (l->tipo == 'f') printf("%.4f ", l->d);
	}
	printf("\n");
}

List *trans(List *head, int k, int i, int j)
{
    List *esq = NULL, *esqq = head, *dir = head, *aaa = head;
	for (int c = 0; c < i; c++, esqq = esqq->nxt);
	esq = esqq->nxt;

	for (int c = 0; c <= j; c++, dir = dir->nxt);

	for (int c = 0; c <= k; c++, aaa = aaa->nxt);

	if (k == i-1) return head;
	esqq->nxt = dir->nxt;
	dir->nxt = aaa->nxt;
	aaa->nxt = esq;
	return head;
}

List *deleta(List *Lista)
{
	while (Lista != NULL)
	{
		List *tmp = Lista->nxt;
		if (Lista->tipo == 's') free(Lista->s);
		free(Lista);
		Lista = tmp;
	}
	return Lista;
}

signed main(void)
{
	char op, t;
	List *head = NULL, *tail = NULL;
	while (scanf("%c ", &op))
	{
		if (op == 'i')
		{
			scanf("%c ", &t);
			for (tail = head; tail->nxt != NULL; tail = tail->nxt);
			List *node = malloc(sizeof(List));
			node->tipo = t;
			node->nxt = NULL;
			if (t == 'c') scanf("%c ", &node->c);
			else if (t == 's') 
			{
				node->s = malloc(sizeof(char)*130);
				scanf("%[^\n] ", node->s);
			}
			else if (t == 'd') scanf("%d ", &node->i);
			else if (t == 'f') scanf("%f ", &node->d);
			
			tail->nxt = node;
		}
		else if (op == 'r')
		{
			int i, j;
			scanf("%d %d ", &i, &j);
			head = rev(head, i, j);
		}
		else if (op == 't')
		{
			int i, j, k;
			scanf("%d %d %d ", &i, &j, &k);
			head = trans(head, k, i, j);
		}
		else if (op == 'p')
		{
			printa(head->nxt);
		}
		else if (op == 'f')
		{
			head = deleta(head);
			return 0;
		}
		else if (op == 'c')
		{
			head = deleta(head);
			head = malloc(sizeof(List));
			head->nxt = NULL;
			head->tipo = 'd';
			tail = NULL;
		}
	}
	return 0;
}
