#include <stdbool.h>
#include <string.h>
#include <stdio.h>

char le_valida_char(char strin[],int length,bool negation,char msg[]);
int le_valida_lista(int lista[],int length,bool negation,char msg[]);
int le_valida_constraint(int min, int max,bool negation,char msg[]);

char le_valida_char(char strin[],int length,bool negation,char msg[]) {
	char n;
	int i=0;
	bool inc=false;
	do {
		inc=!negation;
		printf("%s",msg);
		scanf("%c",&n);
		for(i=0;i<length;i++) {
			if(strin[i]==n) {
				inc = !inc;
				break;
			}
		}
	}while(inc);
	return n;
}

int le_valida_lista(int lista[],int length,bool negation,char msg[]) { //lista a ser comparada, tamanho da lista, (0 ou false) se deve ser igual e (1 ou true) se deve ser diferente, mensagem
	int i=0;
	int n=0;
	bool inc=false;
	do {
		inc=!negation;
		printf("%s",msg);
		scanf("%d",&n);
		for(i=0;i<length;i++) {
			if(lista[i]==n) {
				inc = !inc;
				break;
			}
		}
	}while(inc);
	return n;
}

int le_valida_constraint(int min, int max,bool negation,char msg[]) { //valor mínimo, valor máximo, (0 ou false) estar dentro dos constraints e (1 ou true) de deve estar fora,mensagem
	int n=0;
	bool inc=false;
	if (min > max) {
		int aux = min;
		min = max;
		max = min;
	}
	do {
		inc = negation;
		printf("%s",msg);
		scanf("%d",&n);
		if (n<min || max<n) {
			inc = !inc;
		}
	}while(inc);
	return n;
}
