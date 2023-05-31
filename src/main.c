#include <stdio.h>

typedef struct{
    char descricao[50];
    float peso, valor_compra, valor_venda;
    int id_uf, id_fabricante;
    int id_produto;
}Produto;

typedef struct{
    char nome_marca[30], site[50];
    int telefone, id_uf;
    int id_fabricante;
}Fabricante;

typedef struct{
    char nome[30];
    int id_uf;
}Uf;

int main(){

    Produto produto[50];
    Fabricante fabricante[5];
    Uf uf[27];

    return 0;
}