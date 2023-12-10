#include <stdio.h>
#include <stdlib.h>
#define int long long

typedef struct Linha 
{
    int j, v;
    struct Linha *nxt;
} Linha;

typedef struct Matrix 
{
    int i;
    Linha *linha;
    struct Matrix *nxt;
} Matrix;

Linha *addlinha(int j, int v, Linha *linha)
{
    Linha *l = linha, *prev = NULL;
    for (; l != NULL; prev = l, l = l->nxt) 
	{
		if (l->j == j) 
		{
			l->v = v;
			return linha;
		}
		if (l->j > j) 
		{
			Linha *node = malloc(sizeof(linha));
			node->v = v;
			node->j = j;
			node->nxt = l;
			if (prev != NULL)
				prev->nxt = node;
			else
				return linha = node;
			return linha;
		}
    }
	
	printf("final linha %d\n", j);
    Linha *node = malloc(sizeof(linha));
    node->v = v;
    node->j = j;
    node->nxt = NULL;
    if (linha == NULL)
		return linha = node;
    prev->nxt = node;
    return linha;
}

Linha *dellinha(int j, Linha * linha)
{
    Linha *l = linha, *prev = NULL;
    for (; l != NULL; prev = l, l = l->nxt) 
	{
		if (l->j == j) 
		{
			if (prev != NULL)
				prev->nxt = l->nxt;
			else 
				linha = l->nxt;
			free(l);
			return linha;
		}
    }
    return linha;
}

Matrix *add(int i, int j, int v, Matrix * matrix)
{
    Matrix *m = matrix, *prev = NULL;
    for (; m != NULL; prev = m, m = m->nxt) 
	{
		if (m->i == i) 
		{
			printf("existe linha %d\n", i);
			m->linha = addlinha(j, v, m->linha);
			return matrix;
		} 
		else if (m->i > i)
	   	{
			Matrix *node = malloc(sizeof(matrix));
			node->i = i;
			node->nxt = m;
			node->linha = NULL;
			node->linha = addlinha(j, v, node->linha);
			if (prev != NULL)
				prev->nxt = node;
			else
				return matrix = node;
			return matrix;
		}
    }
	printf("final %d, %d\n", i, j);
    Matrix *node = malloc(sizeof(matrix));
    node->i = i;
    node->linha = NULL;
    node->linha = addlinha(j, v, node->linha);
    node->nxt = NULL;
    if (matrix == NULL)
		return matrix = node;
    else
		prev->nxt = node;
    return matrix;
}

Matrix *del(int i, int j, Matrix * matrix)
{
    Matrix *m = matrix, *prev = NULL;
    for (; m != NULL; prev = m, m = m->nxt) 
	{
		if (m->i == i) 
		{
			m->linha = dellinha(j, m->linha);
			if (m->linha == NULL) 
			{
				if (prev != NULL)
					prev->nxt = m->nxt;
				else 
					matrix = m->nxt;
				free(m);
			}
			return matrix;
		}
    }
    return matrix;
}

Matrix *apaga(Matrix * matrix)
{
    while (matrix != NULL) 
	{
		Matrix *mt = matrix->nxt;
		while (matrix->linha != NULL) 
		{
			Linha *lt = matrix->linha->nxt;
			free(matrix->linha);
			matrix->linha = lt;
		}
		free(matrix);
		matrix = mt;
    }

    return matrix = NULL;
}

void printa(Matrix * matrix)
{
    if (matrix == NULL) 
	{
		printf("a matriz e' nula.\n");
		return;
    }
    printf("m:");
    for (Matrix * m = matrix; m != NULL; m = m->nxt)
		for (Linha * l = m->linha; l != NULL; l = l->nxt)
			printf(" (%lld,%lld,%lld)", m->i, l->j, l->v);
    printf(" \n");
}

int valor(int i, int j, Matrix * matrix)
{
    for (Matrix * m = matrix; m != NULL; m = m->nxt) 
	{
		if (m->i == i)
			for (Linha * l = matrix->linha; l != NULL; l = l->nxt) 
			{
				if (l->j == j)
					return l->v;
			}
    }
    return 0;
}

signed main(void)
{
    Matrix *matrix = NULL;
    char c;
    while (scanf("%c ", &c)) 
	{
		if (c == 'c') 
		{
			matrix = apaga(matrix);
		}
		else if (c == 'p') 
		{
			printa(matrix);
		}
		else if (c == 'a') 
		{
			int i, j, v;
			scanf("[%lld,%lld] %lld ", &i, &j, &v);
	//		if (v == 0)
	//			matrix = del(i, j, matrix);
	//		else
				matrix = add(i, j, v, matrix);
		} 
		else if (c == 'r') 
		{
			int i, j;
			scanf("[%lld,%lld] ", &i, &j);
			printf("m[%lld][%lld] == %lld\n", i, j, valor(i, j, matrix));
		} 
		else if (c == 't') 
		{
			matrix = apaga(matrix);
			return 0;
		}
    }
    return 0;
}
