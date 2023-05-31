#include <stdio.h>

typedef struct{
    char descricao[50];
    float peso, valor_compra, valor_venda;
    int id_uf, id_fabricante;
    int id_produto;
}PRODUTO;

typedef struct{
    char nome_marca[30], site[50];
    int telefone, id_uf;
    int id_fabricante;
}FABRICANTE;

typedef struct{
    char nome[30];
    int id_uf;
}UF;

int main(){

    PRODUTO produto[50];
    FABRICANTE fabricante[5];
    UF uf[27];


    return 0;
}

/*--------------------------- [1]LISTAR TODAS AS MARCAS -----------------*/
void RegistrarMarca(FABRICANTE* fabricante){
    int i=0;
    char confirmacao;

    while(i<2){
        printf("Informe o nome da %da marca: ",i+1); //minimo de 2 marcas registradas
        scanf(" %[^\n]s", &fabricante[i].nome_marca);
        i++;
    }

    do{
        printf("Deseja cadastrar outra marca:(S/N)\n>");
        scanf(" %c", &confirmacao);
        
        if( (confirmacao == 's' || confirmacao == 'S') && i<5){
            printf("Informe o nome da %da marca: ",i+1);
            scanf(" %[^\n]s", &fabricante[i].nome_marca);
        }
        i++;
    }while( (confirmacao == 's' || confirmacao == 'S') && i<5 );
}

void RegistrarSite(){

}

void RegistrarTelefone(){

}

void RegistrarUf(){

}
/*-----------------------------------------------------------------------*/