#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXN (int) 1e4
#define MOD (int) (1e9 + 7)
#define REMOVED -2
#define EMPTY -1

typedef struct no
{
	int flag;
	char s[300];
	int time;
} no;

unsigned long djb2(char *str) {
  unsigned long hash = 5381;
  long long c;
  
  while ((c = *str++))
    hash = (((hash << 5) + hash) ^ c) % MOD; // hash * 33 XOR c
  
  return hash;
}

int hash(unsigned long h, int i, int n)
{
	int a = h % n;
    int b = 1 + (h % (n - 2));
	return ((long long)b*i + a) % n;
}

int add(no *tab, char *s, int n, int *t)
{
	unsigned long h = djb2(s);
	for (int i = 0; i < n; i++)
	{
		int pos = hash(h, i, n);
		if (tab[pos].flag != EMPTY && tab[pos].flag != REMOVED) continue;
		strcpy(tab[pos].s, s);
		tab[pos].flag = 0;
		tab[pos].time = *t;
		(*t)++;
		return pos;
	}
	return -1;
}

int busca(no *tab, char *s, int n)
{
	unsigned long h = djb2(s);
	for (int i = 0; i < n; i++)
	{
		 int pos = hash(h, i, n);
		 if (tab[pos].flag == EMPTY) break;
		 if (tab[pos].flag == REMOVED || strcmp(tab[pos].s, s) != 0) continue;    
		 return pos;
	}
	return -1;
}

void deleta(no *tab, char *s, int n)
{
	int pos = busca(tab, s, n);
	if (pos != -1) tab[pos].flag = REMOVED;
}

void ler(char *str)
{
	char c;
	int idx = 0;
	while ((c = getchar()) != '\n')
	{	
		str[idx++] = c;
	}	
	str[idx] = '\0';
}

int main()
{
	char op;
	int t = 0, n = 0;
	no *tab = NULL;

	char s[300];
	while (scanf("%c", &op))
	{
		getchar();
		if (op == 'c')
		{
			t = 0;
			scanf("%d", &n);
			n<<=1;
			tab = realloc(tab, sizeof(no) * n);
			for (int i = 0; i < n; i++)
				tab[i].flag = EMPTY;
		}
		else if (op == 'i')
		{
			ler(s);
			int p = busca(tab, s, n);
			if (p == -1) add(tab, s, n, &t);
			continue;
		}
		else if (op == 'r')
		{
			ler(s);
			deleta(tab, s, n);
			continue;
		}
		else if (op == 'b')
		{
			ler(s);
			int p = busca(tab, s, n);
			if (p == -1) printf("[%s] nao esta na tabela\n", s);
			else printf("[%s] esta na tabela, timestamp %d\n", s, tab[p].time);
			continue;
		}
		else 
		{
			free(tab);
			return 0;
		}
		getchar();
	}
	return 0;
}
