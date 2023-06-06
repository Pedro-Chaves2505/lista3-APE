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

void RegistrarMarca(FABRICANTE* fabricante, int i);
void RegistrarSite(FABRICANTE* fabricante, int i);
void RegistrarTelefone(FABRICANTE* fabricante,int i);
void RegistrarUf();
int le_valida_marca(FABRICANTE* fabricante);
void ImprimeMarca(int marca_registrada, FABRICANTE* fabricante);




int main(){

    PRODUTO produto[50];
    FABRICANTE fabricante[5];
    UF uf[27];
    int qtd_marcas;

    


    return 0;
}

/*--------------------------- [1]LISTAR TODAS AS MARCAS -----------------*/
void RegistrarMarca(FABRICANTE* fabricante, int i){

    printf("Informe o nome da %da marca:\n> ",i+1);
    scanf(" %[^\n]s", &fabricante[i].nome_marca);
}

void RegistrarSite(FABRICANTE* fabricante, int i){
    printf("Informe a URL do site:\n> ");
    scanf(" %[^\n]s", &fabricante[i].site);
    // acrescentar a validação para o site
}

void RegistrarTelefone(FABRICANTE* fabricante,int i){
    printf("Informe o Telefone:\n> ");
    scanf("%d", &fabricante[i].telefone);
    // acrescentar a validação para o telefone
}

void RegistrarUf(){
    printf("Selecione uma UF:");
    //menu com as UF jah definidas
}
int le_valida_marca(FABRICANTE* fabricante){ //CHAMADA NA MAIN -> qtd_marcas = le_valida_marca(fabricante);
    int i=0, marca_registrada=2;
    char confirm;

    while(i<2){ //minimo de 2 marcas registradas
        RegistrarMarca(fabricante, i);
        RegistrarSite(fabricante, i);
        RegistrarTelefone(fabricante, i);
        //RegistrarUf();
        i++;
    }

    do{
        printf("\nDeseja cadastrar outra marca:(S/N)\n>");
        scanf(" %c", &confirm);

        if( (confirm == 's' || confirm == 'S') && i<5){
            RegistrarMarca(fabricante, i);
            RegistrarSite(fabricante, i);
            RegistrarTelefone(fabricante, i);
            marca_registrada++;
        }
        i++;
    }while( (confirm == 's' || confirm == 'S') && i<5 );

    return marca_registrada;
}

void ImprimeMarca(int marca_registrada, FABRICANTE* fabricante){ // CHAMADA NA MAIN -> ImprimeMarca(qtd_marcas, fabricante);
    for(int i=0;i<marca_registrada;i++){
        printf("fabricante[%d].nome_marca = %s\n",i,fabricante[i].nome_marca);
    }
}
/*-----------------------------------------------------------------------*/