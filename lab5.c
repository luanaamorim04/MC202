#include <stdio.h>
#include <string.h>
#define MAXN 260 // tamanho maximo para a string

/*
 apenas verifico os palindromos de tamanho 3 e 4, pois seria redundante verificar os maiores
 */

int i;
char t[MAXN], s[MAXN]; // strings da entrada
char p[MAXN*MAXN][MAXN]; // para um caso mais geral, teoricamente exitem (n**2) substrings

int palindrome(char s[MAXN]) // 1 caso seja 2palindromo e 0 caso nao
{
	int idx = 0; // quantidade de palindromos
	for (int i = 0; s[i] != '\0'; i++) // i é o centro do palindromo atual
	{
		int j;
		if (i-1 >= 0 && s[i+1] != '\0' && s[i-1] == s[i+1]) // verifico se existe palindromo impar
		{
			for (j = i-1; j <= i+1; j++) // adiciono na minha lista de palindromos
				p[idx][j - (i-1)] = s[j];
			p[idx++][j - (i-1)] = '\0';	
		}

		if (i-2 >= 0 && s[i+1] != '\0' && s[i-1] == s[i] && s[i-2] == s[i+1]) // verifico par
		{
			for (j = i-2; j <= i+1; j++) // adiciono na minha lista de palindromos
				p[idx][j - (i-2)] = s[j];
			p[idx++][j - (i-2)] = '\0';	
		}
	}

	for (int i = 0; i < idx; i++)
		for (int j = i+1; j < idx; j++) // passo por todos os pares (i, j) de palindromos e vejo se existe pelo menos um par que nao é substring um do outro
			if (strstr(p[i], p[j]) == NULL && strstr(p[j], p[i]) == NULL) return 1;

	return 0;
}

int main(void)
{
	while (scanf("%s", s) != EOF)
	{
		for (i = 0; s[i] != '\0'; i++)
			t[i] = (s[i] >= 'a' ? s[i] - 'a' + 'A' : s[i]); //formato em t
		t[i] = '\0';
		if (palindrome(t)) printf("%s\n", s); //imprimo a string so se for 2palindromo
	}
}
