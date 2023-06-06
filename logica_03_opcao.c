#include <stdio.h>
#include <string.h>
#define MIN_PRODUTO 3
#define MAX_PRODUTO 50
#define MIN_FABRICANTE 2
#define MAX_FABRICANTE 5

typedef struct
{
    char descricao[25];
    char digitosPeso[16], dig_V_Venda[16], dig_V_Compra[16], dig_V_lucro[16], dig_P_lucro[16];
    float peso, valor_compra, valor_venda, lucro, porcentagem_de_lucro;
    int id_uf, id_fabricante;
    int id_produto;
} PRODUTO;

typedef struct
{
    char nome_marca[34], site[50], telefone[18];
    int id_uf;
    int id_fabricante;
    int qtd_carac_nome, qtd_carac_site, qtd_carac_telefone;
} FABRICANTE;

typedef struct
{
    char nome[30];
    int id_uf;
} UF;

void DescricaoProduto(PRODUTO *produto, int i);
int le_valida_produto(PRODUTO *produto, UF *uf, int marca_registrada, int UF_escolhidas_pelo_fabricante[]);

void RegistrarMarca(FABRICANTE *fabricante, int i,UF*uf);
int le_valida_marca(FABRICANTE *fabricante, UF *uf);


void RegistrarUf(UF *uf);
void menu_uf(UF*uf,int marca_registrada);
void UF_disponiveis_para_produtos(UF* uf, int marca_registrada, int UF_escolhidas_pelo_fabricante[]);


int main(){
    PRODUTO produto[50];
    FABRICANTE fabricante[5];
    UF uf[27];
    int qtd_marcas, qtd_produtos;
    int retorno;
    
    
    
    qtd_marcas = le_valida_marca(fabricante, uf);
    int UF_escolhidas_pelo_fabricante[qtd_marcas];
    qtd_produtos = le_valida_produto(produto, uf, qtd_marcas,UF_escolhidas_pelo_fabricante);

    return 0;
}
// o produto tem um fabricante e o fabricante tem uma unidade federativa ... produto vem dessa unidade federativa
void RegistrarMarca(FABRICANTE *fabricante, int i,UF*uf) // possui id_uf
{ // PRIMEIRA ALTERACAO
    //printf("\t%da MARCA\n",i+1);
    printf("Informe o nome da marca:\n> ");
    scanf(" %[^\n]s", (*(fabricante + i)).nome_marca);

    // atribuindo os id_uf para cada fabricante registrado
    uf[i].id_uf = i;

}

void RegistrarUf(UF *uf)
{
    printf("Selecione uma UF:\n");
    //validacao
}

void DescricaoProduto(PRODUTO *produto, int i) // possui id_produto
{
    printf("Informe a descricao:\n> ");
    scanf(" %[^\n]s", (*(produto + i)).descricao);

    // atribuindo os id_produtos
    produto[i].id_produto = i;
    // validacao
}

/*PRODUTO - TEM UF*/
int le_valida_produto(PRODUTO *produto, UF *uf, int marca_registrada, int UF_escolhidas_pelo_fabricante[])
{ // CHAMADA NA MAIN --> qtd_produtos = le_valida_produto(produto, uf);
    int produto_registrado = 0;
    char confirm;

    while (produto_registrado < MIN_PRODUTO)
    { // minimo de 5 produtos registrados
        printf("\t%do - PRODUTO\n",produto_registrado+1);
        DescricaoProduto(produto, produto_registrado); // possui id_produto
        UF_disponiveis_para_produtos(uf, marca_registrada, UF_escolhidas_pelo_fabricante);
        // RegistrarUf(uf, produto_registrado); // possui id_uf // vai aparecer a tabela soh dos id_uf disponiveis e não todos
        /*
        for()
        produto[produto[produto_registrado].id_produto].id_uf =  uf[uf_escolhida].id_uf;

        */
        
        produto_registrado++;
    }

    do
    {
        printf("\nDeseja cadastrar outro produto:(S/N)\n>");
        scanf(" %c", &confirm);

        if ((confirm == 's' || confirm == 'S') && produto_registrado < MAX_PRODUTO)
        {
            printf("\t%do - PRODUTO\n",produto_registrado+1);
            DescricaoProduto(produto, produto_registrado);
            //RegistrarUf(uf);
            produto_registrado++;
        }

    } while ((confirm == 's' || confirm == 'S') && produto_registrado < MAX_PRODUTO);

    return produto_registrado;
}

/*FABRICANTE - TEM UF*/
int le_valida_marca(FABRICANTE *fabricante, UF *uf)
{ // CHAMADA NA MAIN -> qtd_marcas = le_valida_marca(fabricante);
    int marca_registrada = 0;
    char confirm;

    while (marca_registrada < MIN_FABRICANTE)
    { // minimo de 2 marcas registradas
        printf("\t%da - MARCA\n",marca_registrada+1);
        RegistrarMarca(fabricante, marca_registrada, uf);
        RegistrarUf(uf /*op*/);
        menu_uf(uf,marca_registrada);
        marca_registrada++;
    }

    do
    {
        printf("\nDeseja cadastrar outra marca:(S/N)\n>");
        scanf(" %c", &confirm);

        if ((confirm == 's' || confirm == 'S') && marca_registrada < MAX_FABRICANTE)
        {
            printf("\t%da - MARCA\n",marca_registrada+1);
            RegistrarUf(uf /*op*/);
            menu_uf(uf,marca_registrada);
            marca_registrada++;
        }

    } while ((confirm == 's' || confirm == 'S') && marca_registrada < MAX_FABRICANTE);

    return marca_registrada;
}

void menu_uf(UF*uf,int marca_registrada){ // possui id_uf ... não mais

    char ufs[27/*nm_ufs*/][50]=
    {   " AC"," AL"," AP"," AM"," BA",
        " CE"," DF"," ES"," GO","MA",
        "MT","MS","MG","PA","PB",
        "PR","PE","PI","RJ","RN",
        "RS","RO","RR","SC","SP",
        "SE","TO"
    };
    int UF_escolhidas_pelo_fabricante[marca_registrada]; /* == op*/
    int count=0;

    // imprimindo as ufs em formato de tabela
    
    for(int i=0;i<6/*nm_linhas*/;i++){
            for(int j=0;j<5/*nm_colunas*/;j++){
                if(count<10/*num_ufs*/){
                    printf("[%d]%-9s",count+1,ufs[count]); 
                }
                else if(count>9 && count<27){
                    printf("[%d]%-8s",count+1,ufs[count]); // para um melhor alinhamento
                }
                count++;
            }
        printf("\n");
    }
    scanf("%d\n", &UF_escolhidas_pelo_fabricante[marca_registrada]);
    printf("%d\n",UF_escolhidas_pelo_fabricante[marca_registrada]);
    printf("%d\n", uf[marca_registrada].id_uf);
    // atribuindo valor aos id_ufs ... ao invés de ter 27 id_ufs eu posso ter soh os id_ufs registradas por um fabricante
    /*
    for(int a=0;a<27;a++){
        uf[a].id_uf = a;
    }
    */

    // atribuindo o nome da uf escolhida ao seu campo na struct  
    strcpy(uf[uf[UF_escolhidas_pelo_fabricante[marca_registrada]-1].id_uf].nome, ufs[UF_escolhidas_pelo_fabricante[marca_registrada]-1]);
    printf("UF escolhida:%s",uf[uf[UF_escolhidas_pelo_fabricante[marca_registrada]-1].id_uf].nome); // teste, retirar...
    
}


void UF_disponiveis_para_produtos(UF* uf, int marca_registrada, int UF_escolhidas_pelo_fabricante[]){

    for(int i=0;i<marca_registrada;i++){
        printf(" %s", uf[uf[UF_escolhidas_pelo_fabricante[marca_registrada]-1].id_uf].nome);
    }
}
