#include <stdio.h>
#include "le_valida.c"
#include <string.h>
#include <stdlib.h>
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

void RegistrarMarca(FABRICANTE *fabricante, int i);
void RegistrarSite(FABRICANTE *fabricante, int i);
void RegistrarTelefone(FABRICANTE *fabricante, int i);
void RegistrarUf(UF *uf, int i);
int le_valida_marca(FABRICANTE *fabricante, UF *uf);

void nome__marca_compactado(FABRICANTE *fabricante, int marca_registrada, PRODUTO *produto, int ids_produtos[], UF *uf, int ans);
void nome__marca_compactado_p6(FABRICANTE *fabricante, int marca_registrada, PRODUTO *produto, int ids_produtos[], UF *uf);
void EstruturaTabela(FABRICANTE *fabricante, int marca_registrada, int ids_produtos[], UF *uf, PRODUTO *produto, int produto_registrado, int ans);

void DescricaoProduto(PRODUTO *produto, int i);
void ValorVendaProduto(PRODUTO *produto, int i);
void ValorCompraProduto(PRODUTO *produto, int i);
void PesoProduto(PRODUTO *produto, int i);
float ValorDeLucro(PRODUTO *produto, int i);
float ValorPercentualLucro(PRODUTO *produto, int i, float ValorLucro);
int le_valida_produto(PRODUTO *produto, UF *uf, FABRICANTE *fabricante, int qtd_fabr);
void receber_id_uf(PRODUTO *para_onde_vai, int i);
int associar_fabr_a_prod(PRODUTO *produto, int produto_registrado, FABRICANTE *fabricante, int qtd_fabr);

int pega_ufs_dos_prods_mais_caros(PRODUTO produtos[], int ids_top_mais_caros[], int quantidade_de_produtos);
pega_fabricantes_dos_prods_mais_baratos(PRODUTO produtos[], int ids_top_mais_baratos[], int quantidade_de_produtos);
void calcula_lucro(PRODUTO produtos[], int quantidade_de_produtos);
void calcula_percentuais_de_lucro(PRODUTO produtos[], int quantidade_de_produtos);
void ord_crescente_percentual_de_lucro(PRODUTO produtos[], int quantidade_de_produtos, int ids_percent_lucro_crescente[]);
void ord_crescente_lucro(PRODUTO produtos[], int ids_lucro_crescente[], int quantidade_de_produtos);
void ord_crescente_valor_venda(PRODUTO produtos[], int ids_pvenda_crescente[], int quantidade_de_produtos);
void ord_decrescente_valor_venda(PRODUTO produtos[], int ids_pvenda_crescente[], int quantidade_de_produtos);

// Helpers
void copiar_vet(int vet1[], int vet2[], int tam);
void preenche_vet_com_ids(int vet[], int tam);

int main()
{
    PRODUTO produto[50];
    FABRICANTE fabricante[5];
    UF uf[27];
    int qtd_marcas, qtd_produtos, i = 0, ans = 0, qtd_top_mais_caros = 0, qtd_top_mais_baratos = 0, qtd_prods_vindo_de_certa_UF = 0, id_UF_pesquisada = 0, ids_percent_lucro_crescente[50] = {}, ids_dos_vindos_de_certa_UF[50], ids_lucro_crescente[50] = {}, ids_pvenda_crescente[50] = {}, ids_top_mais_caros[50] = {}, ids_top_mais_baratos[50] = {};

    qtd_marcas = le_valida_marca(fabricante, uf);

    qtd_produtos = le_valida_produto(produto, uf, fabricante, qtd_marcas);

    calcula_lucro(&produto[0], qtd_produtos);
    calcula_percentuais_de_lucro(&produto[0], qtd_produtos);

    do
    {
        printf("\n\nDigite a opcao desejada: \n\n");

        printf("\n[1] Listar todas as marcas\n[2] Listar todos os produtos\n[3] Listar os produtos vindos de um certo estado\n[5] Listar os estados dos produtos mais caros\n[6] Listar os fabricantes dos produtos mais baratos\n[7] Listar todos os produtos em ordem crescente de valor\n[8] Listar todos os produtos em ordem crescente de lucro\n[9] Listar todos os produtos em ordem crescente de percentual de lucro\n[0] sair\n\n> ");
        scanf("%d", &ans);
        switch (ans)
        {
        case 0:
            break;
        case 1:

            EstruturaTabela(fabricante, qtd_marcas, ids_lucro_crescente /*não faz nada*/, uf, produto, qtd_marcas, ans); // teste, ajustar esse id
            break;
        case 2:
            ord_decrescente_valor_venda(&produto[0], ids_pvenda_crescente, qtd_produtos);
            EstruturaTabela(fabricante, qtd_marcas, ids_pvenda_crescente /*não faz nada*/, uf, produto, qtd_produtos, ans); // teste
            break;
        case 5:
            qtd_top_mais_caros = pega_ufs_dos_prods_mais_caros(&produto[0], ids_top_mais_caros, qtd_produtos);
            EstruturaTabela(fabricante, qtd_marcas, ids_top_mais_caros, uf, produto, qtd_top_mais_caros, ans);
            break;
        case 6:
            qtd_top_mais_baratos = pega_fabricantes_dos_prods_mais_baratos(&produto[0], ids_top_mais_baratos, qtd_produtos);
            EstruturaTabela(fabricante, qtd_marcas, ids_top_mais_baratos, uf, produto, qtd_top_mais_baratos, ans);
            break;
        case 7:
            ord_crescente_valor_venda(&produto[0], ids_pvenda_crescente, qtd_produtos);
            EstruturaTabela(fabricante, qtd_marcas, ids_pvenda_crescente, uf, produto, qtd_produtos, ans);
            break;
        case 8:
            ord_crescente_lucro(&produto[0], ids_lucro_crescente, qtd_produtos);
            EstruturaTabela(fabricante, qtd_marcas, ids_lucro_crescente, uf, produto, qtd_produtos, ans);
            break;
        case 9:
            ord_crescente_percentual_de_lucro(&produto[0], qtd_produtos, ids_percent_lucro_crescente);
            EstruturaTabela(fabricante, qtd_marcas, ids_percent_lucro_crescente, uf, produto, qtd_produtos, ans);
            break;
        default:
            printf("Essa nao e uma opcao valida!\n");
            break;
        }

    } while (ans != 0);

    return 0;
}

/*--------------------------- [1]LISTAR TODAS AS MARCAS -----------------*/
void RegistrarMarca(FABRICANTE *fabricante, int i)
{ // PRIMEIRA ALTERACAO
    printf("\t%da MARCA\n", i + 1);
    printf("Informe o nome da marca:\n> ");
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
    scanf(" %[^\n]s", (*(fabricante + i)).telefone);
    // acrescentar a validação para o telefone
}

void RegistrarUf(UF *uf, int i)
{
    printf("Selecione uma UF:\n> ");
    scanf(" %[^\n]s", (*(uf + i)).nome); // apenas para testes
    // validacao - menu com as UF jah definidas
    (*(uf + i)).id_uf = i;
}

int le_valida_marca(FABRICANTE *fabricante, UF *uf)
{ // CHAMADA NA MAIN -> qtd_marcas = le_valida_marca(fabricante);
    int marca_registrada = 0;
    char confirm;

    while (marca_registrada < MIN_FABRICANTE)
    { // minimo de 2 marcas registradas
        RegistrarMarca(fabricante, marca_registrada);
        RegistrarSite(fabricante, marca_registrada);
        RegistrarTelefone(fabricante, marca_registrada);
        RegistrarUf(uf, marca_registrada);

        marca_registrada++;
    }

    do
    {
        printf("\nDeseja cadastrar outra marca:(S/N)\n>");
        scanf(" %c", &confirm);

        if ((confirm == 's' || confirm == 'S') && marca_registrada < MAX_FABRICANTE)
        {
            RegistrarMarca(fabricante, marca_registrada);
            RegistrarSite(fabricante, marca_registrada);
            RegistrarTelefone(fabricante, marca_registrada);
            RegistrarUf(uf, marca_registrada);
            marca_registrada++;
        }

    } while ((confirm == 's' || confirm == 'S') && marca_registrada < MAX_FABRICANTE);

    return marca_registrada;
}

void nome__marca_compactado(FABRICANTE *fabricante, int marca_registrada, PRODUTO *produto, int ids_produtos[], UF *uf, int ans)
{
    int i = 0;
    int ids_fabrs[5] = {};
    if (ans == 1)
    {
        preenche_vet_com_ids(ids_fabrs, marca_registrada);
    }
    else if (ans == 6)
    {
        for (i = 0; i < marca_registrada; i++)
        {
            ids_fabrs[i] = produto[ids_produtos[i]].id_fabricante;
        }
    }

    for (i = 0; i < marca_registrada; i++)
    {
        int posicao_nome = 0;        // ##
        int posicao_DigTelefone = 0; // ##
        if (i == 0)
        {
            printf("-----------------+----------------------------------+------------------+--------\n"); // quebra linha entre uma marca e outra
        }
        else
        {
            printf("\n-----------------+----------------------------------+------------------+--------\n");
        }
        fabricante[ids_fabrs[i]].qtd_carac_nome = strlen(fabricante[ids_fabrs[i]].nome_marca);
        fabricante[ids_fabrs[i]].qtd_carac_site = strlen(fabricante[ids_fabrs[i]].site);
        fabricante[ids_fabrs[i]].qtd_carac_telefone = strlen(fabricante[ids_fabrs[i]].telefone);
        if (fabricante[ids_fabrs[i]].qtd_carac_nome > 16)
        {                         // impressao - nome da marca com 2 linhas //##@
            int posicao_site = 0; // ##

            while (posicao_nome < 17)
            {
                printf("%c", (*(fabricante + ids_fabrs[i])).nome_marca[posicao_nome]);
                posicao_nome++;
            }

            if (posicao_nome == 17)
            {
                printf("| ");

                if (fabricante[ids_fabrs[i]].qtd_carac_site > 33)
                { // impressao - fabricante com 2 linhas e nome da marca com 2 linhas

                    while (posicao_site < 33) // 52 - 19 = 33
                    {
                        printf("%c", (*(fabricante + ids_fabrs[i])).site[posicao_site]); // @@@@@@@@@@@@@@@@@@@@@@@@@
                        posicao_site++;
                    }

                    if (posicao_site == 33)
                    {
                        printf("| ");
                        // ==== INICIO TABELA - TELEFONE =====

                        while (posicao_DigTelefone < fabricante[ids_fabrs[i]].qtd_carac_telefone)
                        {
                            printf("%c", (*(fabricante + ids_fabrs[i])).telefone[posicao_DigTelefone]);
                            posicao_DigTelefone++;
                        }
                        while (posicao_DigTelefone < 17)
                        {
                            printf(" ");
                            posicao_DigTelefone++;
                        }
                        if (posicao_DigTelefone == 17)
                        {
                            printf("| ");
                            printf("%s", uf[ids_fabrs[i]].nome); // TABELA - UF
                        }
                        /*===========FINAL TABELA - TELEFONE===========*/
                        printf("\n\t\t | ");
                        printf("%c", (*(fabricante + ids_fabrs[i])).site[posicao_site]);
                        posicao_site++;
                    }

                    while (posicao_site > 33 && posicao_site <= fabricante[ids_fabrs[i]].qtd_carac_site)
                    {
                        printf("%c", (*(fabricante + ids_fabrs[i])).site[posicao_site]);
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
                    while (posicao_site < 84)
                    {
                        printf(" ");
                        posicao_site++;
                    }
                    if (posicao_site == 84)
                    {
                        printf("| ");
                    }
                }
                else
                { // impressao - fabricante com 1 linha e nome da marca com 2 linhas

                    while (posicao_site <= fabricante[ids_fabrs[i]].qtd_carac_site)
                    {
                        printf("%c", (*(fabricante + ids_fabrs[i])).site[posicao_site]);
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
                    // ==== INICIO TABELA - TELEFONE =====

                    while (posicao_DigTelefone < fabricante[ids_fabrs[i]].qtd_carac_telefone)
                    {
                        printf("%c", (*(fabricante + ids_fabrs[i])).telefone[posicao_DigTelefone]);
                        posicao_DigTelefone++;
                    }
                    while (posicao_DigTelefone < 17)
                    {
                        printf(" ");
                        posicao_DigTelefone++;
                    }
                    if (posicao_DigTelefone == 17)
                    {
                        printf("| ");
                        printf("%s", uf[i].nome); // TABELA - UF
                    }
                    /*===========FINAL TABELA - TELEFONE===========*/

                    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                }

                /*======================================*/
                printf("\n");

                printf("%c", (*(fabricante + ids_fabrs[i])).nome_marca[posicao_nome]);
                posicao_nome++;
            }

            while (posicao_nome > 17 && posicao_nome < /*=*/fabricante[ids_fabrs[i]].qtd_carac_nome)
            {
                printf("%c", (*(fabricante + ids_fabrs[i])).nome_marca[posicao_nome]);
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
            while (posicao_nome < 67)
            {
                printf(" ");
                posicao_nome++;
            }
            if (posicao_nome == 67)
            {
                printf("| ");
            }
            while (posicao_nome < 84)
            {
                printf(" ");
                posicao_nome++;
            }
            if (posicao_nome == 84)
            {
                printf("| ");
            }
        }
        else // impressao de nome da marca com 1 linha //##@
        {
            // if (fabricante[i].qtd_carac_nome <= 16){
            // printf(" %s", (*(fabricante + i)).nome_marca);

            while (posicao_nome <= fabricante[ids_fabrs[i]].qtd_carac_nome)
            {
                printf("%c", (*(fabricante + ids_fabrs[i])).nome_marca[posicao_nome]);
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
                if (fabricante[ids_fabrs[i]].qtd_carac_site > 33)
                { // impressao do fabricante com 2 linhas e nome da marca com 1 linha

                    while (posicao_site < 33)
                    {
                        printf("%c", (*(fabricante + ids_fabrs[i])).site[posicao_site]); // @@@@@@@@@@@@@@@@@@@@@@@@@
                        posicao_site++;
                    }

                    if (posicao_site == 33)
                    {
                        printf("| ");
                        // ==== INICIO TABELA - TELEFONE =====
                        if (fabricante[ids_fabrs[i]].qtd_carac_telefone < 18)
                        {
                            while (posicao_DigTelefone < fabricante[ids_fabrs[i]].qtd_carac_telefone)
                            {
                                printf("%c", (*(fabricante + ids_fabrs[i])).telefone[posicao_DigTelefone]);
                                posicao_DigTelefone++;
                            }
                            while (posicao_DigTelefone < 17)
                            {
                                printf(" ");
                                posicao_DigTelefone++;
                            }
                            if (posicao_DigTelefone == 17)
                            {
                                printf("| ");
                                printf("%s", uf[i].nome); // TABELA - UF
                            }
                        }
                        /*===========FINAL TABELA - TELEFONE===========*/

                        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                        printf("\n\t\t | ");
                        printf("%c", (*(fabricante + ids_fabrs[i])).site[posicao_site]);
                        posicao_site++;
                    }

                    while (posicao_site > 33 && posicao_site <= fabricante[ids_fabrs[i]].qtd_carac_site)
                    {
                        printf("%c", (*(fabricante + ids_fabrs[i])).site[posicao_site]);
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
                    while (posicao_site < 84)
                    {
                        printf(" ");
                        posicao_site++;
                    }
                    if (posicao_site == 84)
                    {
                        printf("| ");
                    }
                }
                else
                { // impressao do fabricante com 1 linha e nome da marca com 1 linha

                    while (posicao_site <= fabricante[ids_fabrs[i]].qtd_carac_site)
                    {
                        printf("%c", (*(fabricante + ids_fabrs[i])).site[posicao_site]);
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
                    // ==== INICIO TABELA - TELEFONE =====

                    while (posicao_DigTelefone < fabricante[ids_fabrs[i]].qtd_carac_telefone)
                    {
                        printf("%c", (*(fabricante + ids_fabrs[i])).telefone[posicao_DigTelefone]);
                        posicao_DigTelefone++;
                    }
                    while (posicao_DigTelefone < 17)
                    {
                        printf(" ");
                        posicao_DigTelefone++;
                    }
                    if (posicao_DigTelefone == 17)
                    {
                        printf("| ");
                        printf("%s", uf[i].nome); // TABELA - UF
                    }
                    /*===========FINAL TABELA - TELEFONE===========*/
                    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                }
            }
        }
    }
}

/*-----------------------------------------------------------------------*/
/*--------------------------- [2]LISTAR TODOS OS PRODUTOS -----------------*/

void DescricaoProduto(PRODUTO *produto, int i)
{
    printf("\n\t%do PRODUTO\n", i + 1);
    printf("Informe a descricao:\n> ");
    scanf(" %[^\n]s", (*(produto + i)).descricao);
    // validacao
}

void PesoProduto(PRODUTO *produto, int i)
{
    printf("Infome o peso(KG):\n> ");
    scanf("%f", &produto[i].peso);
}

void ValorVendaProduto(PRODUTO *produto, int i)
{
    printf("Informe o valor de venda(R$):\n> ");
    scanf("%f", &produto[i].valor_venda);
    // validação
}

void ValorCompraProduto(PRODUTO *produto, int i)
{
    printf("Informe o valor de compra(R$):\n> ");
    scanf("%f", &produto[i].valor_compra);
    // validação
}

float ValorDeLucro(PRODUTO *produto, int i)
{
    float ValorLucro;
    ValorLucro = produto[i].valor_venda - produto[i].valor_compra;
    return ValorLucro;
}

float ValorPercentualLucro(PRODUTO *produto, int i, float ValorLucro)
{
    float PercentualLucro;
    PercentualLucro = (ValorDeLucro(produto, i) / produto[i].valor_venda) * 100;

    return PercentualLucro;
}
int le_valida_produto(PRODUTO *produto, UF *uf, FABRICANTE *fabricante, int qtd_fabr)

{ // CHAMADA NA MAIN --> qtd_produtos = le_valida_produto(produto, uf);
    int produto_registrado = 0;
    char confirm;

    while (produto_registrado < MIN_PRODUTO)
    { // minimo de 5 produtos registrados
        DescricaoProduto(produto, produto_registrado);
        PesoProduto(produto, produto_registrado);
        ValorCompraProduto(produto, produto_registrado);
        ValorVendaProduto(produto, produto_registrado);
        RegistrarUf(uf, produto_registrado);
        associar_fabr_a_prod(produto, produto_registrado, fabricante, qtd_fabr);
        produto_registrado++;
    }

    do
    {
        printf("\nDeseja cadastrar outro produto:(S/N)\n>");
        scanf(" %c", &confirm);

        if ((confirm == 's' || confirm == 'S') && produto_registrado < MAX_PRODUTO)
        {
            DescricaoProduto(produto, produto_registrado);
            PesoProduto(produto, produto_registrado);
            ValorCompraProduto(produto, produto_registrado);
            ValorVendaProduto(produto, produto_registrado);
            RegistrarUf(uf, produto_registrado);
            associar_fabr_a_prod(produto, produto_registrado, fabricante, qtd_fabr);
            produto_registrado++;
        }

    } while ((confirm == 's' || confirm == 'S') && produto_registrado < MAX_PRODUTO);

    return produto_registrado;
}

void nome_produto_compactado(PRODUTO *produto, int produto_registrado, int ids_produtos[], UF *uf)
{
    int i;
    float VetLucro[produto_registrado];
    float VetPercLucro[produto_registrado];

    for (i = 0; i < produto_registrado; i++)
    { // ESCOPO MAIS ABRANGENTE

        int ContPosicao = 0;

        if (i == 0)
        {
            printf("-----------+-----------------+-----------------+-----------------+-----------------+---------+-------------------------\n");
        }
        else
        {
            printf("\n-----------+-----------------+-----------------+-----------------+-----------------+---------+-------------------------\n");
        }

        /*OBJ: Descobrir a quantidade de digitos que tem em cada valor sem precisa alterar a sua "TIPAGEM padrão"*/

        PRODUTO stringPeso; // representacao do numero como string
        sprintf(stringPeso.digitosPeso, "%.2f", produto[produto[ids_produtos[i]].id_fabricante].peso);
        int posicoesPeso = strlen(stringPeso.digitosPeso); // numero de digitos do produto[i].peso

        PRODUTO stringValorVenda;
        sprintf(stringValorVenda.dig_V_Venda, "%.2f", produto[ids_produtos[i]].valor_venda);
        int posicoesValorVenda = strlen(stringValorVenda.dig_V_Venda); // numero de digitos do produto[i].valor_venda

        PRODUTO stringValorCompra;
        sprintf(stringValorCompra.dig_V_Compra, "%.2f", produto[ids_produtos[i]].valor_compra);
        int posicoesValorCompra = strlen(stringValorCompra.dig_V_Compra); // numero de digitos do produto[i].valor_compra

        PRODUTO stringValorLucro;
        sprintf(stringValorLucro.dig_V_lucro, "%.2f", produto[ids_produtos[i]].lucro);
        int posicoesValorLucro = strlen(stringValorLucro.dig_V_lucro); // numero de digitos do produto[i].lucro

        PRODUTO stringPercentualLucro;
        sprintf(stringPercentualLucro.dig_P_lucro, "%.2f", produto[ids_produtos[i]].porcentagem_de_lucro);
        int posicoesPercLucro = strlen(stringPercentualLucro.dig_P_lucro); // numero de digitos do produto[i].porcentagem_de_lucro

        /*=================================================================================================*/
        printf("%.2f KG", produto[ids_produtos[i]].peso);

        ContPosicao = posicoesPeso;
        while (ContPosicao < 8)
        {
            printf(" ");
            if (ContPosicao == 7)
            {
                printf("| ");
            }
            ContPosicao++;
        }
        printf("R$ %.2f", produto[ids_produtos[i]].valor_venda);

        ContPosicao = 0;
        ContPosicao += posicoesValorVenda;
        while (ContPosicao < 13)
        {
            printf(" ");
            if (ContPosicao == 12)
            {
                printf("| ");
            }
            ContPosicao++;
        }
        printf("R$ %.2f", produto[ids_produtos[i]].valor_compra);

        ContPosicao = 0;
        ContPosicao += posicoesValorCompra;
        while (ContPosicao < 13)
        {
            printf(" ");
            if (ContPosicao == 12)
            {
                printf("| ");
            }
            ContPosicao++;
        }
        printf("R$ %.2f", produto[ids_produtos[i]].lucro);

        ContPosicao = 0;
        ContPosicao += posicoesValorLucro;
        while (ContPosicao < 13)
        {
            printf(" ");
            if (ContPosicao == 12)
            {
                printf("| ");
            }
            ContPosicao++;
        }
        printf("%.2f %%", produto[ids_produtos[i]].porcentagem_de_lucro);

        ContPosicao = 0;
        ContPosicao += posicoesPercLucro;
        while (ContPosicao < 15)
        {
            printf(" ");
            if (ContPosicao == 13)
            {
                printf("| ");
            }
            ContPosicao++;
        }
        printf(" %s", uf[ids_produtos[i]].nome);

        ContPosicao = 0;
        ContPosicao += 2; // todas uf possuem apenas 2letras.
        while (ContPosicao < 6)
        {
            printf(" ");
            if (ContPosicao == 5)
            {
                printf("| ");
            }
            ContPosicao++;
        }

        printf(" %s", produto[ids_produtos[i]].descricao);
    }
}
/*-----------------------------------------------------------------------*/

/*------------------------------- OUTPUT --------------------------------*/
void EstruturaTabela(FABRICANTE *fabricante, int marca_registrada, int ids_produtos[], UF *uf, PRODUTO *produto, int produto_registrado, int ans)
{
    char cabecalhoFabricante[82] = {"     MARCA       |               SITE               |     TELEFONE     |   UF   "};
    char cabecalhoProduto[] = {"   PESO    |   VALOR-VENDA   |  VALOR-COMPRA   |   VALOR-LUCRO   |  PENCENT-LUCRO  |   UF    |          DESCRICAO                "};
    char relatorio[10][80] = {"", "Lista de todas as marcas", "Lista de todos os produtos", "Listar os produtos de um determinado estado", "Listar os produtos de uma determinada marca", "Apresentar o(s) estado(s) onde esta(ao) registrado o produto mais caro", "Apresentar o(s) fabricante(s) que está registrado o produto mais barato", "Listar todos os produtos em ordem crescente de valor-venda", "Listar todos os produtos em ordem crescente de lucro", "Listar todos os produtos em ordem crescente de percentual de lucro"};

    // opção 1,6 do menu principal imprime esta tabela
    if (ans == 1 || ans == 6)
    {
        system("clear"); // linux
        system("cls");   // windows

        printf("\n================================================================================\n");
        printf("                          RELATORIO %d -  %s               ", ans, relatorio[ans]);
        printf("\n================================================================================\n");
        printf("%s\n", cabecalhoFabricante);
        if (ans == 1)
        {
            nome__marca_compactado(fabricante, marca_registrada, produto, ids_produtos, uf, ans);
        }
        else
        {
            nome__marca_compactado(fabricante, produto_registrado, produto, ids_produtos, uf, ans);
        }
    }
    // opção 2,3,4,5,7,8,9 do menu principal imprime esta tabela{
    else
    {
        system("clear"); // linux
        system("cls");   // windows
        printf("\n==========================================================================================================================\n");
        printf("                          RELATORIO %d - %s                                                                              ", ans, relatorio[ans]);
        printf("\n==========================================================================================================================\n");
        printf("%s\n", cabecalhoProduto);
        nome_produto_compactado(produto, produto_registrado, ids_produtos, uf);
    }
}

// Só vão ser necessários esses dois parâmetros mesmo?
int associar_fabr_a_prod(PRODUTO *produto, int produto_registrado, FABRICANTE *fabricante, int qtd_fabr)
{
    int id_fabr = 0;
    imprimir_idFabr_nomeFabr(fabricante, qtd_fabr);

    scanf("%d", &id_fabr);

    (*(produto + produto_registrado)).id_fabricante = id_fabr;

    return id_fabr;
}

int pega_ufs_dos_prods_mais_caros(PRODUTO produtos[], int ids_top_mais_caros[], int quantidade_de_produtos)
{
    /*Estou achando somente que estou usando muito a ordenação nessa função. Averiguar a possibilidade de transformar essas ordenações em outras funções*/
    int k = 0, b = 0, i = 0, aux, ids_ordenados[50] = {}, ids_dos_mais_caros[50], qtd_mais_caros;

    // colocando todos os ids de produtos que foram trazidos
    preenche_vet_com_ids(ids_ordenados, quantidade_de_produtos);

    // Pegando o que e mais caro
    for (b = 0; b < quantidade_de_produtos - 1; b++)
    {
        if ((*(produtos + ids_ordenados[b])).valor_venda > (*(produtos + ids_ordenados[b + 1])).valor_venda)
        {
            aux = ids_ordenados[b];
            ids_ordenados[b] = ids_ordenados[b + 1];
            ids_ordenados[b + 1] = aux;
        }
    }

    ids_dos_mais_caros[0] = ids_ordenados[quantidade_de_produtos - 1];

    // Conferindo se tem algum com o mesmo preco do mais caro e armazenando o id desse se for igual
    i = 1;
    for (b = 0; b < quantidade_de_produtos; b++)
    {
        if ((*(produtos + ids_ordenados[b])).valor_venda == (*(produtos + ids_dos_mais_caros[0])).valor_venda && ids_ordenados[b] != ids_dos_mais_caros[0])
        {
            ids_dos_mais_caros[i] = ids_ordenados[b];
            i++;
        }
    }

    qtd_mais_caros = i;

    // Ordena os mais caros segundo o id (talvez seja melhor em ordem alfabetica)

    for (k = qtd_mais_caros - 1; k > 0; k--)
    {
        for (b = 0; b < k; b++)
        {
            if ((*(produtos + ids_ordenados[b])).valor_venda < (*(produtos + ids_ordenados[b + 1])).valor_venda)
            {
                aux = ids_dos_mais_caros[b];
                ids_dos_mais_caros[b] = ids_dos_mais_caros[b + 1];
                ids_dos_mais_caros[b + 1] = aux;
            }
        }
    }

    // Impressão pegando o fabricante a partir do ID

    copiar_vet(ids_top_mais_caros, ids_dos_mais_caros, qtd_mais_caros);
    printf("\nUFs dos produtos mais caros");

    return qtd_mais_caros;
}

int pega_fabricantes_dos_prods_mais_baratos(PRODUTO produtos[], int ids_top_mais_baratos[], int quantidade_de_produtos)
{
    /*Estou achando somente que estou usando muito a ordenação nessa função. Averiguar a possibilidade de transformar essas ordenações em outras funções*/
    int k = 0, b = 0, i = 0, aux, ids_ordenados[50] = {}, ids_dos_mais_baratos[50], qtd_mais_baratos;

    // colocando todos os ids de produtos que foram trazidos
    preenche_vet_com_ids(ids_ordenados, quantidade_de_produtos);

    // Pegando o que e mais barato
    for (b = 0; b < quantidade_de_produtos - 1; b++)
    {
        if ((*(produtos + ids_ordenados[b])).valor_venda < (*(produtos + ids_ordenados[b + 1])).valor_venda)
        {
            aux = ids_ordenados[b];
            ids_ordenados[b] = ids_ordenados[b + 1];
            ids_ordenados[b + 1] = aux;
        }
    }

    ids_dos_mais_baratos[0] = ids_ordenados[quantidade_de_produtos - 1];

    // Conferindo se tem algum com o mesmo preco do mais barato e armazenando o id desse se for igual
    i = 1;
    for (b = 0; b < quantidade_de_produtos; b++)
    {
        if ((*(produtos + ids_ordenados[b])).valor_venda == (*(produtos + ids_dos_mais_baratos[0])).valor_venda && ids_ordenados[b] != ids_dos_mais_baratos[0])
        {
            ids_dos_mais_baratos[i] = ids_ordenados[b];
            i++;
        }
    }

    qtd_mais_baratos = i;

    // Ordena os mais baratos segundo o id (talvez seja melhor em ordem alfabetica)

    for (k = qtd_mais_baratos - 1; k > 0; k--)
    {
        for (b = 0; b < k; b++)
        {
            if ((*(produtos + ids_ordenados[b])).valor_venda < (*(produtos + ids_ordenados[b + 1])).valor_venda)
            {
                aux = ids_dos_mais_baratos[b];
                ids_dos_mais_baratos[b] = ids_dos_mais_baratos[b + 1];
                ids_dos_mais_baratos[b + 1] = aux;
            }
        }
    }

    // Impressão pegando o fabricante a partir do ID

    copiar_vet(ids_top_mais_baratos, ids_dos_mais_baratos, qtd_mais_baratos);
    printf("\nUFs dos produtos mais baratos");

    return qtd_mais_baratos;
}

void calcula_lucro(PRODUTO produtos[], int quantidade_de_produtos)
{
    int i = 0;
    float valor_venda = 0, valor_compra = 0;

    for (i = 0; i < quantidade_de_produtos; i++)
    {
        valor_venda = (*(produtos + i)).valor_venda;
        valor_compra = (*(produtos + i)).valor_compra;
        (*(produtos + i)).lucro = valor_venda - valor_compra;
    }
}

void calcula_percentuais_de_lucro(PRODUTO produtos[], int quantidade_de_produtos)
{
    int i = 0;
    float valor_compra = 0, lucro = 0;
    for (i = 0; i < quantidade_de_produtos; i++)
    {
        valor_compra = (*(produtos + i)).valor_compra;
        lucro = (*(produtos + i)).lucro;
        (*(produtos + i)).porcentagem_de_lucro = (lucro / valor_compra) * 100;
    }
}

void ord_crescente_percentual_de_lucro(PRODUTO produtos[], int quantidade_de_produtos, int ids_percent_lucro_crescente[])
{
    int k = 0, b = 0, i = 0, aux = 0, ids_ordenados[50] = {};

    // colocando todos os ids de produtos que foram trazidos - ver se transforma isso em função
    for (i = 0; i < quantidade_de_produtos; i++)
    {
        ids_ordenados[i] = i;
    }

    // ordenando somente os ids segundo o lucro
    for (k = quantidade_de_produtos - 1; k > 0; k--)
    {
        for (b = 0; b < k; b++)
        {
            if ((*(produtos + ids_ordenados[b])).porcentagem_de_lucro > (*(produtos + ids_ordenados[b + 1])).porcentagem_de_lucro)
            {
                aux = ids_ordenados[b];
                ids_ordenados[b] = ids_ordenados[b + 1];
                ids_ordenados[b + 1] = aux;
            }
        }
    }
    // usa o array de ids para imprmir
    printf("\nOrdem crescente percentual de lucro.\n");
    copiar_vet(ids_percent_lucro_crescente, ids_ordenados, quantidade_de_produtos);
}

void ord_crescente_lucro(PRODUTO produtos[], int ids_lucro_crescente[], int quantidade_de_produtos)
{
    // ordena e armazena em array
    int k = 0, b = 0, i = 0, aux = 0, ids_ordenados[50] = {};

    // colocando todos os ids de produtos que foram trazidos
    for (i = 0; i < quantidade_de_produtos; i++)
    {
        ids_ordenados[i] = i;
    }

    // ordenando somente os ids
    for (k = quantidade_de_produtos - 1; k > 0; k--)
    {
        for (b = 0; b < k; b++)
        {
            if ((*(produtos + ids_ordenados[b])).lucro > (*(produtos + ids_ordenados[b + 1])).lucro)
            {
                aux = ids_ordenados[b];
                ids_ordenados[b] = ids_ordenados[b + 1];
                ids_ordenados[b + 1] = aux;
            }
        }
    }
    // usa o array de ids para imprmir
    copiar_vet(ids_lucro_crescente, ids_ordenados, quantidade_de_produtos);
    printf("\nOrdem crescente de lucro.\n");
}

void ord_crescente_valor_venda(PRODUTO produtos[], int ids_pvenda_crescente[], int quantidade_de_produtos)
{
    /*Um comentário é que estou pensando em retornar os ids aqui*/
    // ordena e armazena em array
    int k = 0, b = 0, i = 0, aux, ids_ordenados[50] = {};

    // colocando todos os ids de produtos que foram trazidos
    for (i = 0; i < quantidade_de_produtos; i++)
    {
        ids_ordenados[i] = i;
    }

    // ordenando somente os ids
    for (k = quantidade_de_produtos - 1; k > 0; k--)
    {
        for (b = 0; b < k; b++)
        {
            if ((*(produtos + ids_ordenados[b])).valor_venda > (*(produtos + ids_ordenados[b + 1])).valor_venda)
            {
                aux = ids_ordenados[b];
                ids_ordenados[b] = ids_ordenados[b + 1];
                ids_ordenados[b + 1] = aux;
            }
        }
    }
    // usa o array de ids para imprmir
    copiar_vet(ids_pvenda_crescente, ids_ordenados, quantidade_de_produtos);
    printf("\nOrdem crescente de valor de venda.\n");
}

void ord_decrescente_valor_venda(PRODUTO produtos[], int ids_pvenda_crescente[], int quantidade_de_produtos)
{
    /*Um comentário é que estou pensando em retornar os ids aqui*/
    // ordena e armazena em array
    int k = 0, b = 0, i = 0, aux, ids_ordenados[50] = {};

    // colocando todos os ids de produtos que foram trazidos
    for (i = 0; i < quantidade_de_produtos; i++)
    {
        ids_ordenados[i] = i;
    }

    // ordenando somente os ids
    for (k = quantidade_de_produtos - 1; k > 0; k--)
    {
        for (b = 0; b < k; b++)
        {
            if ((*(produtos + ids_ordenados[b])).valor_venda < (*(produtos + ids_ordenados[b + 1])).valor_venda) // alterado o sinal para manter uma ordem descrescente
            {
                aux = ids_ordenados[b];
                ids_ordenados[b] = ids_ordenados[b + 1];
                ids_ordenados[b + 1] = aux;
            }
        }
    }
    // usa o array de ids para imprmir
    copiar_vet(ids_pvenda_crescente, ids_ordenados, quantidade_de_produtos);
    printf("\nOrdem decrescente de valor de venda.\n");
}

// Helpers
void copiar_vet(int vet1[], int vet2[], int tam)
{
    int i = 0;
    for (i = 0; i < tam; i++)
    {
        *(vet1 + i) = *(vet2 + i);
    }
}

void preenche_vet_com_ids(int vet[], int tam)
{
    int i;
    for (i = 1; i < tam; i++)
    {
        *(vet + i) = i;
    }
}

void imprimir_idFabr_nomeFabr(FABRICANTE *fabricante, int qtd_fabr)
{
    int i = 0;
    printf("Digite o fabricante do produto:\n\n");
    for (i = 0; i < qtd_fabr; i++)
    {
        printf("[%d] %s", i, (*(fabricante + i)).nome_marca);
        printf("\n");
    }
    printf("\n> ");
}
