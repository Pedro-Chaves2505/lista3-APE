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
int le_valida_produto(FABRICANTE*fabricante,PRODUTO *produto, UF *uf, int marca_registrada);

void RegistrarMarca(FABRICANTE *fabricante, int i,UF*uf);
int le_valida_marca(FABRICANTE *fabricante, UF *uf);


void RegistrarUf();
void recebe_uf(FABRICANTE*fabricante, int marca_registrada,UF*uf);
void produto_recebe_id_uf(PRODUTO*produto ,FABRICANTE*fabricante, int marca_registrada,UF*uf);

int retornar_prods_de_certa_UF(PRODUTO *todos_os_produtos, int qtd_total_de_produtos, int ids_dos_vindos_de_certa_UF[], int id_UF_pesquisada);

int main(){
    PRODUTO produto[50];
    FABRICANTE fabricante[5];
    UF uf[27];
    int qtd_marcas, qtd_produtos;
    int retorno;
    
    
    
    qtd_marcas = le_valida_marca(fabricante, uf);
    qtd_produtos = le_valida_produto(fabricante ,produto, uf, qtd_marcas);

    return 0;
}
// o produto tem um fabricante e o fabricante tem uma unidade federativa ... produto vem dessa unidade federativa
void RegistrarMarca(FABRICANTE *fabricante, int i,UF*uf)
{ // PRIMEIRA ALTERACAO
    printf("\t%da MARCA\n",i+1);
    printf("Informe o nome da marca:\n> ");
    scanf(" %[^\n]s", (*(fabricante + i)).nome_marca);

    // atribuindo os ids para as marcas/fabricantes
    fabricante[i].id_fabricante = i;
}

void RegistrarUf()
{
    printf("Selecione uma UF:\n");
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
int le_valida_produto(FABRICANTE*fabricante,PRODUTO *produto, UF *uf, int marca_registrada)
{ // CHAMADA NA MAIN --> qtd_produtos = le_valida_produto(produto, uf);
    int produto_registrado = 0;
    char confirm;

    while (produto_registrado < MIN_PRODUTO)
    { // minimo de 5 produtos registrados
        printf("\t%do - PRODUTO\n",produto_registrado+1);
        DescricaoProduto(produto, produto_registrado);
        RegistrarUf();
        produto_recebe_id_uf(produto ,fabricante, marca_registrada, uf);// produto[]id_uf 
        
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
            produto_recebe_id_uf(produto ,fabricante, marca_registrada, uf);
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
        RegistrarMarca(fabricante, marca_registrada, uf);
        RegistrarUf(); 
        recebe_uf(fabricante, marca_registrada, uf); // fabricante[].id_uf, uf[].nome, uf[].id_uf
        marca_registrada++;
    }

    do
    {
        printf("\nDeseja cadastrar outra marca:(S/N)\n>");
        scanf(" %c", &confirm);

        if ((confirm == 's' || confirm == 'S') && marca_registrada < MAX_FABRICANTE)
        {
            printf("\t%da - MARCA\n",marca_registrada+1);
            RegistrarUf();
            recebe_uf(fabricante, marca_registrada, uf);
            marca_registrada++;
        }

    } while ((confirm == 's' || confirm == 'S') && marca_registrada < MAX_FABRICANTE);

    return marca_registrada;
}

void recebe_uf(FABRICANTE*fabricante, int marca_registrada,UF*uf){ // possui id_uf

    char ufs[27/*nm_ufs*/][50]=
    {   " AC"," AL"," AP"," AM"," BA",
        " CE"," DF"," ES"," GO","MA",
        "MT","MS","MG","PA","PB",
        "PR","PE","PI","RJ","RN",
        "RS","RO","RR","SC","SP",
        "SE","TO"
    };
    int op=0;
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

    // recebe os ids das ufs escolhidas pela marca/fabricante  
    for(int i=0;i<1;i++){ // laço de validacao do intervalo
        scanf("%d",&op);
        if(op>=1 && op<= 27){
            fabricante[marca_registrada].id_uf = op-1;
        }
        else{
            printf("Opcao invalida. Tente novamente!\n");
            i--;
        }
    }

    
    // atribuindo os ids para as UF
    for(int a=0;a<27;a++){
        uf[a].id_uf = a;
    }
    
    // atribuindo o nome da uf escolhida pela marca/fabricante  
    strcpy(uf[fabricante[marca_registrada].id_uf].nome, ufs[op-1]);
    
}

void produto_recebe_id_uf(PRODUTO*produto, FABRICANTE*fabricante, int marca_registrada,UF*uf){
    
    // imprimindo as ufs disponiveis para os produtos
    for(int i=0;i<marca_registrada;i++){
        printf("[%d]%-5s\t", i+1, uf[fabricante[i].id_uf].nome);
    }
    printf("\n");
    int op=0;

    // recebe os ids das ufs escolhidas pelos produtos
    for(int i=0;i<1;i++){
        scanf("%d",&op);
        if(op>=1 && op<= marca_registrada){
            produto[marca_registrada].id_uf = op-1;
        }
        else{
            printf("Opcao invalida. Tente novamente!\n");
            i--;
        }
    }
}
/*
void UF_disponiveis_para_produtos(UF* uf){

    printf(""uf[op-1].id_uf);
}
*/

int retornar_prods_de_certa_UF(PRODUTO *todos_os_produtos, int qtd_total_de_produtos, int ids_dos_vindos_de_certa_UF[], int id_UF_pesquisada)
{
    int i = 0, a = 0;
    for (i = 0; i < qtd_total_de_produtos; i++)
    //no caso, i vai estar fazendo o papel do id dos produtos, indo do produto 0 ao n (n<=50)
    {
        if ((*(todos_os_produtos + i)).id_uf == id_UF_pesquisada) 
        {
            *(ids_dos_vindos_de_certa_UF + a) = i;
            a++;
        }
    }
    return a;//"a" é a quantidade total de produtos que vieram de uma certa UF
}