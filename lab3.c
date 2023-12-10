#include <stdio.h>
// #define int long long

int dia, mes, ano, sh, sm, ss, th, tm, ts, sol, tot, flag, last;
int ano1, mes1, dia1, tot_seg;

int qtd_dias[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // quantos dias tem em cada mes

int is_bi(int ano) // vejo se o ano é bissexto
{
	return ano%4 == 0 && (ano%100 != 0 || ano%400 == 0);
}

void add(int *dia, int *mes, int *ano) // adiciono um dia na data
{
	++(*dia);
	if (*dia > qtd_dias[*mes] + (is_bi(*ano) && *mes == 2))
		(*mes)++, *dia = 1;

	if (*mes > 12) *mes = 1, ++(*ano);
}

int dif(int h, int m, int s, int h2, int m2, int s2) // calculo a diferença entre o nascer e o por do sol
{
	int resp = 0, ini, fim;
	if (h == 99 && m == 99 && s == 99) // se o sol nao nasceu
	{
		resp += tot_seg;
		if (sol) ini = last; // se ele nasceu outro dia
	}
	else // se o sol nasceu
	{
		sol = 1; // esta sol
		ini = last = s + (60*m) + (3600*h); // ultima vez que nasceu
	}

	if (h2 == 99 && m2 == 99 && s2 == 99) // se o sol nao se pos
	{
		if (sol == 0) return 0; // se nao estava sol
		return tot_seg; // se estava sol
	}
	else // se o sol se pos
	{
		sol = 0; // nao esta mais sol
		last = -1; // nao nasceu
	}

	fim = s2 + (60*m2) + (3600*h2);

	if (fim < ini)   
		resp = fim + tot_seg - ini;
	else 
		resp = fim - ini;

	return resp; // retorno quanto tempo o sol ficou 
}

int main(void)
{
	tot_seg = 24*3600; // segundos no dia
	while (scanf("%d/%d/%d%d:%d:%d%d:%d:%d", &dia, &mes, &ano, &sh, &sm, &ss, &th, &tm, &ts) == 9)
	{	
		if (!flag) dia1 = dia, mes1 = mes, ano1 = ano, flag = 1; // salvo o primeiro dia
		tot += dif(sh, sm, ss, th, tm, ts); // adiciono as horas no total de tempo
	}

	tot /= (3600*12);

	while (tot--) add(&dia1, &mes1, &ano1); //adiciono o total de dias na data inicial

	printf("%d/%d/%d\n", dia1, mes1, ano1);
	return 0;
}