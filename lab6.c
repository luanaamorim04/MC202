#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXN 100
#define MAXT 30

struct Time //estrutura de um time 
{
	int ponto, vitoria, gols, golsm, jogos, sofrido, empate, derrota;
	char *nome;
};

typedef struct Time Time;

int __strcmp(char *a, char *b) //comparacao de strings
{
	int idx = 0;
	while (a[idx] != '\0' && b[idx] != '\0')
	{
		char c = a[idx], d = b[idx];
		if (c >= 'a') c = a[idx] + ('A' - 'a');
		if (d >= 'a') d = b[idx] + ('A' - 'a');
		if (c > d) return 1;
		else if (c < d) return -1;
		idx++;
	}
	if (a[idx] != '\0') return 1;
	if (b[idx] != '\0') return -1;
	return 0;
}

int cmp(Time a, Time b) //comparacao de times
{
	if (a.ponto != b.ponto) return a.ponto < b.ponto;
	if (a.vitoria != b.vitoria) return a.vitoria < b.vitoria;
	if (a.gols != b.gols) return a.gols < b.gols;
	if (a.golsm != b.golsm) return a.golsm < b.golsm;
	if (a.jogos != b.jogos) return a.jogos > b.jogos;
	return (__strcmp(a.nome, b.nome) > 0);
}

int main(void)
{
	int flag = 0, j, t, n;
	scanf("%d", &t);
	getchar();
	while (t--)
	{
		if (flag) printf("\n"); //formatacao
		flag = 1;

		char *nome; //nome do campeonato
		Time times[MAXN]; //array de times
		size_t tam = MAXN, tam2 = MAXT; //tamanhos das strings
		nome = malloc(tam * sizeof(char)); 
		getline(&nome, &tam, stdin);
		scanf("%d", &n);
		getchar();
		for (int i = 0; i < n; i++) //leitura de times
		{
			times[i].ponto = times[i].vitoria = times[i].empate = times[i].gols = times[i].golsm =
			times[i].derrota = times[i].sofrido = times[i].jogos = 0;//inicializar	
			times[i].nome = malloc(tam2 * sizeof(char));
			getline(&times[i].nome, &tam2, stdin);
			for (int j = 0; times[i].nome[j] != '\0'; j++) 
				if (times[i].nome[j] == '\n') times[i].nome[j] = '\0'; //tirar o \n
		}

		scanf("%d", &j);
		getchar();
		while (j--) //lendo os jogos
		{	
			char *time1, *time2;
			int t1, t2, p1, p2, idx = 0;
			time1 = (char*)malloc(tam2 * sizeof(char));
			time2 = (char*)malloc(tam2 * sizeof(char));
			while (scanf("%c", &time1[idx]) && time1[idx++] != '#');
			time1[idx-1] = '\0';
			scanf("%d", &p1);
			getchar();
			scanf("%d", &p2);
			idx = 0;
			getchar();
			while (scanf("%c", &time2[idx]) && time2[idx++] != '\n');
			time2[idx-1] = '\0';
			
			for (int i = 0; i < n; i++) //achando o indice dos times
			{
				if (strcmp(times[i].nome, time1) == 0) t1 = i;
				if (strcmp(times[i].nome, time2) == 0) t2 = i;
			}
			
			//update
			if (p1 > p2)
			{
				times[t1].ponto += 3;
				times[t1].vitoria++;
				times[t2].derrota++;
			}
			else if (p2 > p1)
			{
				times[t2].ponto += 3;
				times[t2].vitoria++;
				times[t1].derrota++;
			}
			else
			{
				times[t1].ponto++;
				times[t2].ponto++;
				times[t1].empate++;
				times[t2].empate++;
			}

			times[t1].gols += (p1 - p2);
			times[t2].gols += (p2 - p1);
			times[t1].golsm += p1;
			times[t2].golsm += p2;
			times[t1].jogos++;
			times[t2].jogos++;
			times[t1].sofrido += p2;
			times[t2].sofrido += p1;
			free(time1);
			free(time2);
		}
		for (int i = 0; i < n; i++) //bubble sort
		{
			for (int j = 0; j < n; j++)
			{
				if (!cmp(times[i], times[j]))
				{
					Time tmp = times[j];
					times[j] = times[i];
					times[i] = tmp;
				}
			}
		}

		printf("%s", nome);
		for (int i = 0; i < n; i++) //imprime
		{
			printf("%d) %s, %dp, %dj (%d-%d-%d), %ds (%d-%d)\n", i+1, times[i].nome, 
					times[i].ponto, times[i].jogos, times[i].vitoria, times[i].empate, 
					times[i].derrota, times[i].gols, times[i].golsm, times[i].sofrido);
			free(times[i].nome);
		}
		free(nome);
	}
}
