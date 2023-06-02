#include <stdio.h>
#include <string.h>

// @@ como varrer uma string que é membro de uma struct?

typedef struct
{
    char descricao[50];
    float peso, valor_compra, valor_venda;
    int id_uf, id_fabricante;
    int id_produto;
} PRODUTO;

typedef struct
{
    char nome_marca[34], site[50],telefone[18];
    int id_uf;
    int id_fabricante;
    int qtd_carac_nome, qtd_carac_site, qtd_carac_telefone; // incrementos
} FABRICANTE;

typedef struct
{
    char nome[30];
    int id_uf;
} UF;

void RegistrarMarca(FABRICANTE *fabricante, int i);
void RegistrarSite(FABRICANTE *fabricante, int i);
void RegistrarTelefone(FABRICANTE *fabricante, int i);
void RegistrarUf();
int le_valida_marca(FABRICANTE *fabricante);
void ImprimeMarca(int marca_registrada, FABRICANTE *fabricante);
void nome__marca_compactado(FABRICANTE *fabricante, int marca_registrada);
void nome__site_compactado(FABRICANTE *fabricante, int marca_registrada);
void EstruturaTabela(FABRICANTE *fabricante, int marca_registrada);

void ValorVendaProduto(PRODUTO* produto, int i);
void ValorCompraProduto(PRODUTO* produto, int i);
void PesoProduto(PRODUTO* produto,int i);

int main()
{

    PRODUTO produto[50];
    FABRICANTE fabricante[5];
    UF uf[27];
    int qtd_marcas;
    qtd_marcas = le_valida_marca(fabricante);

    EstruturaTabela(fabricante, qtd_marcas);

    return 0;
}

/*--------------------------- [1]LISTAR TODAS AS MARCAS -----------------*/
void RegistrarMarca(FABRICANTE *fabricante, int i)
{ // PRIMEIRA ALTERACAO

    printf("Informe o nome da %da marca:\n> ", i + 1);
    scanf(" %[^\n]s", (*(fabricante + i)).nome_marca);
}

void RegistrarSite(FABRICANTE *fabricante, int i)
{
    printf("Informe a URL do site:\n> ");
    scanf(" %[^\n]s", &fabricante[i].site);
    // acrescentar a validação para o site
}

void RegistrarTelefone(FABRICANTE *fabricante, int i)
{
    printf("Informe o Telefone:\n> ");
    scanf(" %[^\n]s", &fabricante[i].telefone);
    // acrescentar a validação para o telefone
}

void RegistrarUf()
{
    printf("Selecione uma UF:");
    // menu com as UF jah definidas
}
int le_valida_marca(FABRICANTE *fabricante)
{ // CHAMADA NA MAIN -> qtd_marcas = le_valida_marca(fabricante);
    int i = 0, marca_registrada = 2;
    char confirm;

    while (i < 2)
    { // minimo de 2 marcas registradas
        RegistrarMarca((*fabricante).nome_marca, i);
        RegistrarSite(fabricante, i);
        RegistrarTelefone(fabricante, i);
        // RegistrarUf();
        i++;
    }

    do
    {
        printf("\nDeseja cadastrar outra marca:(S/N)\n>");
        scanf(" %c", &confirm);

        if ((confirm == 's' || confirm == 'S') && i < 5)
        {
            RegistrarMarca(fabricante, i);
            RegistrarSite(fabricante, i);
            RegistrarTelefone(fabricante, i);
            marca_registrada++;
        }
        i++;
    } while ((confirm == 's' || confirm == 'S') && i < 5);

    return marca_registrada;
}

void ImprimeMarca(int marca_registrada, FABRICANTE *fabricante)
{ // CHAMADA NA MAIN -> ImprimeMarca(qtd_marcas, fabricante);
    for (int i = 0; i < marca_registrada; i++)
    {
        printf("fabricante[%d].nome_marca = %s\n", i, (*(fabricante + i)).nome_marca);
    }
}

void nome__marca_compactado(FABRICANTE *fabricante, int marca_registrada)
{
    int i = 0;

    for (i = 0; i < marca_registrada; i++)
    {
        int posicao_nome = 0;

        if (i == 0)
        {
            printf("-----------------+----------------------------------+------------------+--------\n"); // quebra linha entre uma marca e outra
        }
        else
        {
            printf("\n-----------------+----------------------------------+------------------+--------\n");
        }
        fabricante[i].qtd_carac_nome = strlen(fabricante[i].nome_marca);
        fabricante[i].qtd_carac_site = strlen(fabricante[i].site);
        if (fabricante[i].qtd_carac_nome > 16)
        { // impressao nome da marca com 2 linhas

            int posicao_site = 0;
            while (posicao_nome < 17)
            {
                printf("%c", (*(fabricante + i)).nome_marca[posicao_nome]);
                posicao_nome++;
            }

            if (posicao_nome == 17)
            {
                printf("| ");
                // inserir as expressões pro site quando o nome da marca ocupar 2 linhas 
                if (fabricante[i].qtd_carac_site > 33)
                { // impressao do fabricante com 2 linhas

                    while (posicao_site < 33)// 52 - 19 = 33
                    {                                                      
                        printf("%c", (*(fabricante + i)).site[posicao_site]); // @@@@@@@@@@@@@@@@@@@@@@@@@
                        posicao_site++;
                    }

                    if (posicao_site == 33)
                    {
                        printf("| ");
                        printf(" %[^\n]s",fabricante[i].telefone); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                        printf("\n\t\t | ");
                        printf("%c", (*(fabricante + i)).site[posicao_site]);
                        posicao_site++;
                    }

                    while (posicao_site > 33 && posicao_site <= fabricante[i].qtd_carac_site)
                    {
                        printf("%c", (*(fabricante + i)).site[posicao_site]);
                        posicao_site++;
                    }
                    while (posicao_site < 67)
                    {
                        printf(" ");
                        posicao_site++;
                    }
                    if (posicao_site == 67)
                    {
                        printf("| ");

                        //@@@@@@@@@@@@@@
                    }
                    
                }
                else
                { // impressao do fabricante com 1 linha

                    while (posicao_site <= fabricante[i].qtd_carac_site)
                    {
                        printf("%c", (*(fabricante + i)).site[posicao_site]);
                        posicao_site++;
                    }
                    while (posicao_site < 33)
                    {
                        printf(" ");
                        posicao_site++;
                    }
                    if (posicao_site == 33)
                    {
                        printf(" | ");
                    }
                    printf(" %[^\n]s",fabricante[i].telefone); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                }

                /*======================================*/
                printf("\n");
                // while(posicao_site<33){ // 52 - 19 = 33
                //     printf("%c", (*(fabricante + i)).site[posicao_site]); // @@@@@@@@@@@@@@@@@@@@@@@@@
                //     posicao_site++;
                // }
                printf("%c", (*(fabricante + i)).nome_marca[posicao_nome]);
                posicao_nome++;
            }

            while (posicao_nome > 17 && posicao_nome </*=*/ fabricante[i].qtd_carac_nome)
            {
                printf("%c", (*(fabricante + i)).nome_marca[posicao_nome]);
                posicao_nome++;
            }
            while (posicao_nome < 34)
            {
                printf(" ");
                posicao_nome++;
            }
            if (posicao_nome == 34)
            {
                printf("| ");
            }
            while(posicao_nome<67){
                printf(" ");
                posicao_nome++;
            }
            if(posicao_nome ==67){
                printf("| ");
            }
        }
        else // impressao de nome de marcas de 1 linha
        {
            // if (fabricante[i].qtd_carac_nome <= 16){
            // printf(" %s", (*(fabricante + i)).nome_marca);

            while (posicao_nome <= fabricante[i].qtd_carac_nome)
            {
                printf("%c", (*(fabricante + i)).nome_marca[posicao_nome]);
                posicao_nome++;
            }
            while (posicao_nome < 18)
            {
                printf(" ");
                posicao_nome++;
            }
            if (posicao_nome == 18)
            {
                printf("| ");
                int posicao_site = 0; // 19 --> 0
                if (fabricante[i].qtd_carac_site > 33)
                { // impressao do fabricante com 2 linhas

                    while (posicao_site < 33)
                    {                                                         // 52 - 19 = 33
                        printf("%c", (*(fabricante + i)).site[posicao_site]); // @@@@@@@@@@@@@@@@@@@@@@@@@
                        posicao_site++;
                    }

                    if (posicao_site == 33)
                    {
                        printf("| ");
                        printf(" %[^\n]s",fabricante[i].telefone);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                        
                        printf("\n\t\t | ");
                        printf("%c", (*(fabricante + i)).site[posicao_site]);
                        posicao_site++;
                    }

                    while (posicao_site > 33 && posicao_site <= fabricante[i].qtd_carac_site)
                    {
                        printf("%c", (*(fabricante + i)).site[posicao_site]);
                        posicao_site++;
                    }
                    while (posicao_site < 67)
                    {
                        printf(" ");
                        posicao_site++;
                    }
                    if (posicao_site == 67)
                    {
                        printf("| ");

                        //@@@@@@@@@@@@@@
                    }
                }
                else
                { // impressao do fabricante com 1 linha

                    while (posicao_site <= fabricante[i].qtd_carac_site)
                    {
                        printf("%c", (*(fabricante + i)).site[posicao_site]);
                        posicao_site++;
                    }
                    while (posicao_site < 33)
                    {
                        printf(" ");
                        posicao_site++;
                    }
                    if (posicao_site == 33)
                    {
                        printf(" | ");
                    }
                    printf(" %[^\n]s",fabricante[i].telefone);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    
                }
            }
        }
    }
}

/*-----------------------------------------------------------------------*/
/*--------------------------- [2]LISTAR TODOS OS PRODUTOS -----------------*/

void DescricaoProduto(PRODUTO* produto, int i){
    printf("Informe a descricao:\n> ");
    scanf(" %[^\n]s", (*(produto+i)).descricao);
    // validacao
}

void PesoProduto(PRODUTO* produto,int i){
    printf("Infome o peso:\n> ");
    scanf("%.2f",(*(produto+i)).peso);

}

void ValorVendaProduto(PRODUTO* produto, int i){
    printf("%do Produto - Informe o valor de venda:\n> ", i+1);
    scanf("%.2f", (*(produto+i)).valor_venda);
    // validação
}

void ValorCompraProduto(PRODUTO* produto, int i){
    printf("%do Produto - Informe o valor de compra:\n> ", i+1);
    scanf("%.2f", (*(produto+i)).valor_compra);
    // validação
}
/*-----------------------------------------------------------------------*/


void EstruturaTabela(FABRICANTE *fabricante, int marca_registrada)
{
    

    // char TipoRelatorio[81] = {"                          RELATORIO 1 - LISTA DE TODAS AS MARCAS                "};
    // char Topicos[82] = {"     MARCA       |               SITE               |     TELEFONE     |   UF   "};
    //  qtd_carac_nome -> guarda a quantidade de caracteres que cada nome possui
    

    printf("\n==============================================================================\n");
    printf("                          RELATORIO 1 - LISTA DE TODAS AS MARCAS                ");
    printf("\n==============================================================================\n");
    printf("     MARCA       |               SITE               |     TELEFONE     |   UF   \n");
    
    
    nome__marca_compactado(fabricante, marca_registrada); //... nao eh eficiente.... irei fazer por matrizes
    
}

