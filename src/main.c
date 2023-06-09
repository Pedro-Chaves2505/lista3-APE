#include <stdio.h>
#include "le_valida.c"
#include <string.h>
#include <stdlib.h>
#define TOTAL_UFS 27
#define MIN_PRODUTO 5
#define MAX_PRODUTO 50
#define MIN_FABRICANTE 2
#define MAX_FABRICANTE 5

typedef struct
{
    char descricao[25], nome[20];
    char digitosPeso[16], dig_V_Venda[16], dig_V_Compra[16], dig_V_lucro[16], dig_P_lucro[16];
    float peso, valor_compra, valor_venda, lucro, porcentagem_de_lucro;
    int id_uf, id_fabricante, qtd_carac_nome_produto;
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
void receber_UF_fabricante(FABRICANTE *fabricante, int i, UF *uf);
int le_valida_marca(FABRICANTE **fabricante, UF *uf);

void nome__marca_compactado(FABRICANTE *fabricante, int marca_registrada, PRODUTO *produto, int ids_produtos[], UF *uf, int ans);
void nome__marca_compactado_p6(FABRICANTE *fabricante, int marca_registrada, PRODUTO *produto, int ids_produtos[], UF *uf);
void EstruturaTabela(FABRICANTE *fabricante, int marca_registrada, int ids_produtos[], UF *uf, PRODUTO *produto, int produto_registrado, int ans);

void nomeProduto(PRODUTO *produto, int i);
void DescricaoProduto(PRODUTO *produto, int i);
void ValorVendaProduto(PRODUTO *produto, int i);
void ValorCompraProduto(PRODUTO *produto, int i);
void PesoProduto(PRODUTO *produto, int i);
float ValorDeLucro(PRODUTO *produto, int i);
float ValorPercentualLucro(PRODUTO *produto, int i, float ValorLucro);
int le_valida_produto(PRODUTO **produto, UF *uf, FABRICANTE *fabricante, int qtd_fabr);
void receber_id_uf(PRODUTO *para_onde_vai, int i);
int associar_fabr_a_prod(PRODUTO *produto, int produto_registrado, FABRICANTE *fabricante, int qtd_fabr);
void imprimir_idFabr_nomeFabr(FABRICANTE *fabricante, int qtd_fabr);

int pega_ufs_dos_prods_mais_caros(PRODUTO produtos[], int ids_top_mais_caros[], int quantidade_de_produtos);
int pega_fabricantes_dos_prods_mais_baratos(PRODUTO produtos[], int ids_top_mais_baratos[], int quantidade_de_produtos);
void calcula_lucro(PRODUTO produtos[], int quantidade_de_produtos);
void calcula_percentuais_de_lucro(PRODUTO produtos[], int quantidade_de_produtos);
void ord_crescente_percentual_de_lucro(PRODUTO produtos[], int quantidade_de_produtos, int ids_percent_lucro_crescente[]);
void ord_crescente_lucro(PRODUTO produtos[], int ids_lucro_crescente[], int quantidade_de_produtos);
void ord_crescente_valor_venda(PRODUTO produtos[], int ids_pvenda_crescente[], int quantidade_de_produtos);
void ord_decrescente_valor_venda(PRODUTO produtos[], int ids_pvenda_crescente[], int quantidade_de_produtos);
void list_prods_por_uf(PRODUTO *produtos, FABRICANTE *fabricantes, int tam, int marca_registrada, UF *uf);
void list_prods_marca(PRODUTO *produtos, FABRICANTE *fabricantes, int tam);
void list_prods_ordem_alfab_crescente(PRODUTO produtos[], int ids_produtos[], int quantidade_de_produtos);
void list_nomeMarca_ordem_alfab_decrescente(FABRICANTE fabricantes[], int ids_fabricantes[], int quantidade_de_fabricantes);

// Helpers
void copiar_vet(int vet1[], int vet2[], int tam);
void preenche_vet_com_ids(int vet[], int tam);
int compara_nome_produtos(const void *a, const void *b);
int compara_nome_marca(const void *a, const void *b);

float le_valida_constraints(float min, float max, char message[], char err[]);

int main()
{
    PRODUTO *produto;
    FABRICANTE *fabricante;
    UF uf[TOTAL_UFS];

    produto = calloc(MIN_PRODUTO, sizeof(PRODUTO));
    fabricante = calloc(MIN_FABRICANTE, sizeof(FABRICANTE));

    int qtd_marcas, qtd_produtos, i = 0, ans = 0, qtd_top_mais_caros = 0, qtd_top_mais_baratos = 0, qtd_prods_vindo_de_certa_UF = 0, id_UF_pesquisada = 0, *ids_percent_lucro_crescente, *ids_lucro_crescente, *ids_pvenda_crescente, *ids_top_mais_caros, *ids_top_mais_baratos, *ids_produtos, *ids_fabricantes, *ids_nomeMarca_decrescente;

    qtd_marcas = le_valida_marca(&fabricante, uf);

    ids_fabricantes = calloc(qtd_marcas, sizeof(int));
    ids_nomeMarca_decrescente = calloc(qtd_marcas, sizeof(int));

    qtd_produtos = le_valida_produto(&produto, uf, fabricante, qtd_marcas);

    ids_percent_lucro_crescente = calloc(qtd_produtos, sizeof(int));
    ids_lucro_crescente = calloc(qtd_produtos, sizeof(int));
    ids_pvenda_crescente = calloc(qtd_produtos, sizeof(int));
    ids_top_mais_caros = calloc(qtd_produtos, sizeof(int));
    ids_top_mais_baratos = calloc(qtd_produtos, sizeof(int));
    ids_produtos = calloc(qtd_produtos, sizeof(int));

    calcula_lucro(&produto[0], qtd_produtos);
    calcula_percentuais_de_lucro(&produto[0], qtd_produtos);

    do
    {
        printf("\n\nDigite a opcao desejada: \n\n");

        printf("\n[1] Listar todas as marcas\n[2] Listar todos os produtos\n[3] Listar os produtos vindos de um certo estado\n[4] Listar os produtos vindos de uma certa marca\n[5] Listar os estados dos produtos mais caros\n[6] Listar os fabricantes dos produtos mais baratos\n[7] Listar todos os produtos em ordem crescente de valor\n[8] Listar todos os produtos em ordem crescente de lucro\n[9] Listar todos os produtos em ordem crescente de percentual de lucro\n[10] Listar todos os produtos em ordem alfabetica crescente(A-Z)\n[11] Listar todas as marcas em ordem alfabetica decrescente(Z-A)\n[0] sair\n\n> ");
        scanf("%d", &ans);
        switch (ans)
        {
        case 0:
            break;
        case 1:
            preenche_vet_com_ids(ids_fabricantes, qtd_marcas);
            EstruturaTabela(fabricante, qtd_marcas, ids_fabricantes, uf, produto, qtd_marcas, ans);
            break;
        case 2:
            ord_decrescente_valor_venda(&produto[0], ids_pvenda_crescente, qtd_produtos);
            EstruturaTabela(fabricante, qtd_marcas, ids_pvenda_crescente, uf, produto, qtd_produtos, ans);
            break;
        case 3:
            list_prods_por_uf(produto, fabricante, qtd_produtos, qtd_marcas, uf);
            break;
        case 4:
            imprimir_idFabr_nomeFabr(fabricante, qtd_marcas);
            list_prods_marca(produto, fabricante, qtd_produtos);
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
        case 10:
            list_prods_ordem_alfab_crescente(produto, ids_produtos, qtd_produtos);
            EstruturaTabela(fabricante, qtd_marcas, ids_produtos, uf, produto, qtd_produtos, ans);
            break;
        case 11:
            list_nomeMarca_ordem_alfab_decrescente(fabricante, ids_nomeMarca_decrescente, qtd_marcas);
            EstruturaTabela(fabricante, qtd_marcas, ids_nomeMarca_decrescente, uf, produto, qtd_marcas, ans);
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

void receber_UF_fabricante(FABRICANTE *fabricante, int i, UF *uf)
{
    char ufs[TOTAL_UFS /*nm_ufs*/][50] =
        {" AC", " AL", " AP", " AM", " BA",
         " CE", " DF", " ES", " GO", "MA",
         "MT", "MS", "MG", "PA", "PB",
         "PR", "PE", "PI", "RJ", "RN",
         "RS", "RO", "RR", "SC", "SP",
         "SE", "TO"};
    int op = 0;
    int count = 0;

    // imprimindo as ufs em formato de tabela
    for (int i = 0; i < 6 /*nm_linhas*/; i++)
    {
        for (int j = 0; j < 5 /*nm_colunas*/; j++)
        {
            if (count < 10 /*num_ufs*/)
            {
                printf("[%d]%-9s", count, ufs[count]);
            }
            else if (count > 9 && count < TOTAL_UFS)
            {
                printf("[%d]%-8s", count, ufs[count]); // para um melhor alinhamento
            }
            count++;
        }
        printf("\n");
    }
    // validacao, apenas numerica, das ufs
    do
    {
        printf("Selecione uma UF:\n> ");
        scanf("%d", &(*(fabricante + i)).id_uf);
    } while ((*(fabricante + i)).id_uf < 0 || (*(fabricante + i)).id_uf > 26);

    // atribuindo nome para cada uf escolhida
    for (int v = 0; v < TOTAL_UFS; v++)
    {
        if ((*(fabricante + i)).id_uf >= 0 && (*(fabricante + i)).id_uf <= 26)
        {
            if ((*(fabricante + i)).id_uf == v)
                strcpy((*(uf + fabricante[i].id_uf)).nome, ufs[v]);
        }
    }
}

int le_valida_marca(FABRICANTE **fabricante, UF *uf)
{ // CHAMADA NA MAIN -> qtd_marcas = le_valida_marca(fabricante);
    int marca_registrada = 0;
    char confirm;

    while (marca_registrada < MIN_FABRICANTE)
    { // minimo de 2 marcas registradas
        RegistrarMarca(*fabricante, marca_registrada);
        RegistrarSite(*fabricante, marca_registrada);
        RegistrarTelefone(*fabricante, marca_registrada);
        receber_UF_fabricante(*fabricante, marca_registrada, uf);

        marca_registrada++;
    }

    do
    {
        printf("\nDeseja cadastrar outra marca:(S/N)\n>");
        scanf(" %c", &confirm);

        if ((confirm == 's' || confirm == 'S') && marca_registrada < MAX_FABRICANTE)
        {

            *fabricante = realloc(*fabricante, ((marca_registrada + 1) * sizeof(FABRICANTE)));
            RegistrarMarca(*fabricante, marca_registrada);
            RegistrarSite(*fabricante, marca_registrada);
            RegistrarTelefone(*fabricante, marca_registrada);
            receber_UF_fabricante(*fabricante, marca_registrada, uf);
            marca_registrada++;
        }

    } while ((confirm == 's' || confirm == 'S') && marca_registrada < MAX_FABRICANTE);

    return marca_registrada;
}

void nome__marca_compactado(FABRICANTE *fabricante, int marca_registrada, PRODUTO *produto, int ids_produtos[], UF *uf, int ans)
{
    int i = 0;
    int ids_fabrs[5] = {};
    if (ans == 1 || ans == 11)
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
            if (ans == 6)
            {
                printf("-----------------+----------------------------------+------------------+--------+-----------------+--------------\n");
            }
            else
            {
                printf("-----------------+----------------------------------+------------------+--------\n"); // quebra linha entre uma marca e outra
            }
        }
        else
        {
            if (ans == 6)
            {
                printf("\n-----------------+----------------------------------+------------------+--------+-----------------+--------------\n");
            }
            else
            {
                printf("\n-----------------+----------------------------------+------------------+--------\n");
            }
        }
        fabricante[ids_fabrs[i]].qtd_carac_nome = strlen(fabricante[ids_fabrs[i]].nome_marca);
        fabricante[ids_fabrs[i]].qtd_carac_site = strlen(fabricante[ids_fabrs[i]].site);
        fabricante[ids_fabrs[i]].qtd_carac_telefone = strlen(fabricante[ids_fabrs[i]].telefone);
        (*(produto + ids_produtos[i])).qtd_carac_nome_produto = strlen((*(produto + ids_produtos[i])).nome);
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
                            printf("%-7s", uf[(*(fabricante + ids_fabrs[i])).id_uf].nome); // TABELA - UF
                            if (ans == 6)
                            {
                                printf("| ");
                                int sequecia_caracter_nome = 0;
                                while (sequecia_caracter_nome <= (*(produto + ids_produtos[i])).qtd_carac_nome_produto)
                                {
                                    printf("%c", (*(produto + ids_produtos[i])).nome[sequecia_caracter_nome]); // TABELA - NOME PRODUTO
                                    sequecia_caracter_nome++;
                                }

                                while (sequecia_caracter_nome < 20)
                                { // condicoes de alinhamento
                                    printf(" ");
                                    if (sequecia_caracter_nome == 16)
                                    {
                                        printf("| ");
                                        printf("R$ %.2f", produto[ids_produtos[i]].valor_venda); // TABELA - PREÇO
                                    }
                                    sequecia_caracter_nome++;
                                }
                            }
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
                        printf("%-7s", uf[(*(fabricante + ids_fabrs[i])).id_uf].nome); // TABELA - UF
                        if (ans == 6)
                        {
                            printf("| ");
                            int sequecia_caracter_nome = 0;
                            while (sequecia_caracter_nome <= (*(produto + ids_produtos[i])).qtd_carac_nome_produto)
                            {
                                printf("%c", (*(produto + ids_produtos[i])).nome[sequecia_caracter_nome]); // TABELA - NOME PRODUTO
                                sequecia_caracter_nome++;
                            }

                            while (sequecia_caracter_nome < 20)
                            { // condicoes de alinhamento
                                printf(" ");
                                if (sequecia_caracter_nome == 16)
                                {
                                    printf("| ");
                                    printf("R$ %.2f", produto[ids_produtos[i]].valor_venda); // TABELA - PREÇO
                                }
                                sequecia_caracter_nome++;
                            }
                        }
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
                                printf("%-7s", uf[(*(fabricante + ids_fabrs[i])).id_uf].nome); // TABELA - UF
                                if (ans == 6)
                                {
                                    printf("| ");
                                    int sequecia_caracter_nome = 0;
                                    while (sequecia_caracter_nome <= (*(produto + ids_produtos[i])).qtd_carac_nome_produto)
                                    {
                                        printf("%c", (*(produto + ids_produtos[i])).nome[sequecia_caracter_nome]); // TABELA - NOME PRODUTO
                                        sequecia_caracter_nome++;
                                    }

                                    while (sequecia_caracter_nome < 20)
                                    { // condicoes de alinhamento
                                        printf(" ");
                                        if (sequecia_caracter_nome == 16)
                                        {
                                            printf("| ");
                                            printf("R$ %.2f", produto[ids_produtos[i]].valor_venda); // TABELA - PREÇO
                                        }
                                        sequecia_caracter_nome++;
                                    }
                                }
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
                        printf("%-7s", uf[(*(fabricante + ids_fabrs[i])).id_uf].nome); // TABELA - UF
                        if (ans == 6)
                        {
                            printf("| ");
                            int sequecia_caracter_nome = 0;
                            while (sequecia_caracter_nome <= (*(produto + ids_produtos[i])).qtd_carac_nome_produto)
                            {
                                printf("%c", (*(produto + ids_produtos[i])).nome[sequecia_caracter_nome]); // TABELA - NOME PRODUTO
                                sequecia_caracter_nome++;
                            }

                            while (sequecia_caracter_nome < 20)
                            { // condicoes de alinhamento
                                printf(" ");
                                if (sequecia_caracter_nome == 16)
                                {
                                    printf("| ");
                                    printf("R$ %.2f", produto[ids_produtos[i]].valor_venda); // TABELA - PREÇO
                                }
                                sequecia_caracter_nome++;
                            }
                        }
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
void nomeProduto(PRODUTO *produto, int i)
{

    printf("\n\t%do PRODUTO\n", i + 1);
    printf("Informe seu nome:\n> ");
    scanf(" %[^\n]s", (*(produto + i)).nome);
    // validacao --> máx=20 de caracters no nome
}

void DescricaoProduto(PRODUTO *produto, int i)
{

    printf("Informe a descricao:\n> ");
    scanf(" %[^\n]s", (*(produto + i)).descricao);
    // validacao
}

void PesoProduto(PRODUTO *produto, int i)
{
    produto[i].peso = le_valida_constraints(0.05, 50, "Informe o peso(KG):\n> ", "!!!O peso deve estar entre 0.05kg e 50kg!!!");
    // validação
}

void ValorVendaProduto(PRODUTO *produto, int i)
{
    produto[i].valor_venda = le_valida_constraints(1, 10000, "Informe o valor de venda(R$):\n> ", "!!!O preco deve estar entre 1 real e 10000 reais!!!");
    // validação
}

void ValorCompraProduto(PRODUTO *produto, int i)
{
    produto[i].valor_compra = le_valida_constraints(0.5, 8000, "Informe o valor de compra(R$):\n> ", "!!!O preco de compra deve estar entre 0.5 e 8000 reais!!!");
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

int le_valida_produto(PRODUTO **produto, UF *uf, FABRICANTE *fabricante, int qtd_fabr)
{ // CHAMADA NA MAIN --> qtd_produtos = le_valida_produto(produto, uf);
    int produto_registrado = 0;
    char confirm;

    while (produto_registrado < MIN_PRODUTO)
    { // minimo de 5 produtos registrados
        nomeProduto(*produto, produto_registrado);
        DescricaoProduto(*produto, produto_registrado);
        PesoProduto(*produto, produto_registrado);
        ValorCompraProduto(*produto, produto_registrado);
        ValorVendaProduto(*produto, produto_registrado);
        associar_fabr_a_prod(*produto, produto_registrado, fabricante, qtd_fabr);
        produto_registrado++;
    }

    do
    {
        printf("\nDeseja cadastrar outro produto:(S/N)\n>");
        scanf(" %c", &confirm);

        if ((confirm == 's' || confirm == 'S') && produto_registrado < MAX_PRODUTO)
        {
            *produto = realloc(*produto, (produto_registrado + 1) * sizeof(PRODUTO));
            nomeProduto(*produto, produto_registrado);
            DescricaoProduto(*produto, produto_registrado);
            PesoProduto(*produto, produto_registrado);
            ValorCompraProduto(*produto, produto_registrado);
            ValorVendaProduto(*produto, produto_registrado);
            associar_fabr_a_prod(*produto, produto_registrado, fabricante, qtd_fabr);
            produto_registrado++;
        }

    } while ((confirm == 's' || confirm == 'S') && produto_registrado < MAX_PRODUTO);

    return produto_registrado;
}

void nome_produto_compactado(PRODUTO *produto, int produto_registrado, int ids_produtos[], UF *uf,FABRICANTE*fabricante)
{
    int i;
    float VetLucro[produto_registrado];
    float VetPercLucro[produto_registrado];

    for (i = 0; i < produto_registrado; i++)
    { // ESCOPO MAIS ABRANGENTE

        int ContPosicao = 0;

        if (i == 0)
        {
            printf("-----------------+------------+-----------------+-----------------+-----------------+-----------------+-------------+-------------------------\n");
        }
        else
        {
            printf("\n-----------------+------------+-----------------+-----------------+-----------------+-----------------+-------------+-------------------------\n");
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
        produto[ids_produtos[i]].qtd_carac_nome_produto = strlen(produto[ids_produtos[i]].nome); // armazena a quantidade de caracteres que terah no nome do produto... para fazer um melhor alinhamento na tabela

        if (produto[ids_produtos[i]].qtd_carac_nome_produto < 20)
        {
            int sequencia_caracter = 0;
            while (sequencia_caracter <= produto[ids_produtos[i]].qtd_carac_nome_produto)
            {
                printf("%c", (*(produto + ids_produtos[i])).nome[sequencia_caracter]);
                sequencia_caracter++;
            }
            while (sequencia_caracter < 18)
            {
                printf(" ");
                sequencia_caracter++;
            }
            if (sequencia_caracter == 18)
            {
                printf("| ");
            }
        }

        printf("KG %.2f", produto[ids_produtos[i]].peso);

        ContPosicao = 0;
        ContPosicao += posicoesPeso;
        while (ContPosicao < 8)
        {
            printf(" ");
            ContPosicao++;
        }
        if (ContPosicao == 8)
        {
            printf("| ");
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
        printf("%-7s", uf[(*(fabricante + produto[ids_produtos[i]].id_fabricante)).id_uf].nome);
        // printf(" %s", uf[fabricante[i].id_uf].nome); // OBS: nao temos produto[].id_uf pois associamos a uf do produto ao fabricante

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
    char cabecalhoTopFabricanteBaratos[] = {"     MARCA       |               SITE               |     TELEFONE     |   UF   |   NOME-PRODUTO  | PRECO-PRODUTO"};
    char cabecalhoProduto[] = {"     NOME        |   PESO     |   VALOR-VENDA   |  VALOR-COMPRA   |   VALOR-LUCRO   |  PENCENT-LUCRO  |      UF     |        DESCRICAO                "};
    char relatorio[12][80] = {"", "Lista de todas as marcas", "Lista de todos os produtos", "Produtos de um determinado estado", "Produtos de uma determinada marca", "Estado(s) do(s) produto(s) mais caro(s)", "Fabricante(s) com produto(s) mais barato(s)", "Produtos em ordem crescente de valor-venda", "Produtos em ordem crescente de lucro", "Produtos em ordem crescente de percentual de lucro", "Lista dos produtos em ordem alfabetica(A-Z)", "Lista marcas em ordem alfabetica(Z-A)"};

    // opção 1,6 e 11 do menu principal imprime esta tabela
    if (ans == 1 || ans == 6 || ans == 11)
    {
        system("clear"); // linux
        system("cls");   // windows
        if (ans == 1 || ans == 11)
        {
            printf("\n================================================================================\n");
            printf("                          RELATORIO %d -  %s               ", ans, relatorio[ans]);
            printf("\n================================================================================\n");
            printf("%s\n", cabecalhoFabricante);
            nome__marca_compactado(fabricante, marca_registrada, produto, ids_produtos, uf, ans);
        }
        else
        {
            printf("\n=================================================================================================================\n");
            printf("                          RELATORIO %d -  %s               ", ans, relatorio[ans]);
            printf("\n=================================================================================================================\n");
            printf("%s\n", cabecalhoTopFabricanteBaratos);
            nome__marca_compactado(fabricante, produto_registrado, produto, ids_produtos, uf, ans);
        }
    }
    // opção 2,3,4,5,7,8,9 e 10 do menu principal imprime esta tabela{
    else
    {
        system("clear"); // linux
        system("cls");   // windows
        printf("\n==============================================================================================================================================\n");
        printf("                          RELATORIO %d - %s                                                                              ", ans, relatorio[ans]);
        printf("\n==============================================================================================================================================\n");
        printf("%s\n", cabecalhoProduto);
        nome_produto_compactado(produto, produto_registrado, ids_produtos, uf,fabricante);
    }
}

// Só vão ser necessários esses dois parâmetros mesmo?
int associar_fabr_a_prod(PRODUTO *produto, int produto_registrado, FABRICANTE *fabricante, int qtd_fabr)
{
    int id_fabr = 0;
    imprimir_idFabr_nomeFabr(fabricante, qtd_fabr);

    scanf("%d", &id_fabr);
    if (qtd_fabr == 1)
    {
        while (id_fabr != 0)
        {
            imprimir_idFabr_nomeFabr(fabricante, qtd_fabr);
            scanf("%d", &id_fabr);
        }
    }
    else if (qtd_fabr == 2)
    {
        while (id_fabr != 0 && id_fabr != 1)
        {
            imprimir_idFabr_nomeFabr(fabricante, qtd_fabr);
            scanf("%d", &id_fabr);
        }
    }
    else if (qtd_fabr == 3)
    {
        while (id_fabr != 0 && id_fabr != 1 && id_fabr != 2)
        {
            imprimir_idFabr_nomeFabr(fabricante, qtd_fabr);
            scanf("%d", &id_fabr);
        }
    }
    else if (qtd_fabr == 4)
    {
        while (id_fabr != 0 && id_fabr != 1 && id_fabr != 2 && id_fabr != 3)
        {
            imprimir_idFabr_nomeFabr(fabricante, qtd_fabr);
            scanf("%d", &id_fabr);
        }
    }
    else
    {
        while (id_fabr != 0 && id_fabr != 1 && id_fabr != 2 && id_fabr != 3 && id_fabr != 4)
        {
            imprimir_idFabr_nomeFabr(fabricante, qtd_fabr);
            scanf("%d", &id_fabr);
        }
    }

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

void list_prods_por_uf(PRODUTO *produtos, FABRICANTE *fabricantes, int tam, int marca_registrada, UF *uf)
{
    int i, idx_uf_pesquisada, aux;
    int j, retorno;
    char uf_search[30];
    char ufs[TOTAL_UFS /*nm_ufs*/][50] =
        {" AC", " AL", " AP", " AM", " BA",
         " CE", " DF", " ES", " GO", "MA",
         "MT", "MS", "MG", "PA", "PB",
         "PR", "PE", "PI", "RJ", "RN",
         "RS", "RO", "RR", "SC", "SP",
         "SE", "TO"};

    // imprimindo APENAS as ufs DISPONIVEIS
    printf("\nSelecione uma UF a ser pesquisada:\n");
    for (int i = 0; i < marca_registrada; i++)
    {
        printf("[%d]%s\t", i, uf[fabricantes[i].id_uf].nome);
    }
    printf("\n> ");
    scanf("%d", &idx_uf_pesquisada);
    // validacao da uf a ser pesquisada de acordo com a quantidade de fabricantes disponiveis
    if (marca_registrada == 1)
    {
        while (idx_uf_pesquisada != 0)
        {
            printf("\tA UF escolhida nao possui nenhum fabricante\nSelecione uma UF disponivel\n> ");
            scanf("%d", &idx_uf_pesquisada);
        }
    }
    else if (marca_registrada == 2)
    {
        while (idx_uf_pesquisada != 0 && idx_uf_pesquisada != 1)
        {
            printf("\tA UF escolhida nao possui nenhum fabricante\nSelecione uma UF disponivel\n> ");
            scanf("%d", &idx_uf_pesquisada);
        }
    }
    else if (marca_registrada == 3)
    {
        while (idx_uf_pesquisada != 0 && idx_uf_pesquisada != 1 && idx_uf_pesquisada != 2)
        {
            printf("\tA UF escolhida nao possui nenhum fabricante\nSelecione uma UF disponivel\n> ");
            scanf("%d", &idx_uf_pesquisada);
        }
    }
    else if (marca_registrada == 4)
    {
        while (idx_uf_pesquisada != 0 && idx_uf_pesquisada != 1 && idx_uf_pesquisada != 2 && idx_uf_pesquisada != 3)
        {
            printf("\tA UF escolhida nao possui nenhum fabricante\nSelecione uma UF disponivel\n> ");
            scanf("%d", &idx_uf_pesquisada);
        }
    }
    else
    {
        while (idx_uf_pesquisada != 0 && idx_uf_pesquisada != 1 && idx_uf_pesquisada != 2 && idx_uf_pesquisada != 3 && idx_uf_pesquisada != 4)
        {
            printf("\tA UF escolhida nao possui nenhum fabricante\nSelecione uma UF disponivel\n> ");
            scanf("%d", &idx_uf_pesquisada);
        }
    }

    // organizando a impressao do nome da uf pesquisada
    for (int i = 0; i < marca_registrada; i++)
    {
        if (idx_uf_pesquisada == i)
            strcpy(uf[idx_uf_pesquisada].nome, uf[fabricantes[i].id_uf].nome);
    }
    for (int v = 0; v < TOTAL_UFS; v++)
    {
        retorno = strcmp(uf[idx_uf_pesquisada].nome, ufs[v]);
        if (retorno == 0)
        {
            idx_uf_pesquisada = v;
        }
    }

    system("clear"); // linux
    system("cls");   // windows
    printf("\n=====================================================================================================\n");
    printf("                          RELATORIO 3 - Produtos de um determinado estado            ");
    printf("\n=====================================================================================================\n");
    printf("    NOME     |     Peso    | VALOR-VENDA | VALOR-COMPRA | VALOR-LUCRO | %%-LUCRO  |  UF  | DESCRICAO \n");
    printf("-------------+-------------+-------------+--------------+-------------+----------+------+-------------\n");
    for (i = 0; i < tam; i++)
    {
        if ((*(fabricantes + (*(produtos + i)).id_fabricante)).id_uf == idx_uf_pesquisada)
        {
            j++;
            // printf("%d\t%s|\t %s\n", (*(produtos + i)).id_produto, (*(produtos + i)).descricao, ufs[idx_uf_pesquisada]);
            printf("%-14s KG %-10.2f R$ %-10.2f R$ %-11.2f R$ %-10.2f %.2f%%\t   %-5s %-5s\n", (*(produtos + i)).nome, (*(produtos + i)).peso, (*(produtos + i)).valor_venda, (*(produtos + i)).valor_compra, (*(produtos + i)).lucro, (*(produtos + i)).porcentagem_de_lucro, uf[idx_uf_pesquisada].nome, (*(produtos + i)).descricao);
        }
    }
}

void list_prods_marca(PRODUTO *produtos, FABRICANTE *fabricantes, int tam/*, int ids_produtos[]*/)
{
    int i = 0, idx_fabr = 0;
    printf("digite a marca a ser pesquisada: ");
    scanf("%d", &idx_fabr);
    printf("\n======================================================================================\n");
    printf("                          RELATORIO 4 - Produtos de uma determinada marca           ");
    printf("\n======================================================================================\n");
    printf("Peso    | VALOR-VENDA | VALOR-COMPRA | VALOR-LUCRO | %%-LUCRO  |  MARCA  | DESCRICAO \n");
    printf("--------+-------------+--------------+-------------+----------+---------+-------------\n");
    for (i = 0; i < tam; i++)
    {
        if ((*(produtos + i)).id_fabricante == idx_fabr)
        {
            // printf("%d\t%s|\t %s\n", (*(produtos + i)).id_produto, (*(produtos + i)).descricao, fabricantes[idx_fabr].nome_marca);
            printf("KG %-7.2f R$ %-10.2f R$ %-11.2f R$ %-10.2f %.2f%%\t %-10s %-5s\n", (*(produtos + i)).peso, (*(produtos + i)).valor_venda, (*(produtos + i)).valor_compra, (*(produtos + i)).lucro, (*(produtos + i)).porcentagem_de_lucro, fabricantes[idx_fabr].nome_marca, (*(produtos + i)).descricao);
        }
    }
}

void list_prods_ordem_alfab_crescente(PRODUTO produtos[], int ids_produtos[], int quantidade_de_produtos)
{

    int i = 0, ids_ordenados[50] = {};

    // colocando todos os ids de produtos que foram trazidos
    for (i = 0; i < quantidade_de_produtos; i++)
    {
        ids_ordenados[i] = i;
    }

    // Colocando em ordem alfabetica
    qsort(produtos, quantidade_de_produtos, sizeof(PRODUTO), compara_nome_produtos);
    // usa o array de ids para imprmir
    copiar_vet(ids_produtos, ids_ordenados, quantidade_de_produtos);
    printf("\nOrdem crescente de A-Z.\n");
}

void list_nomeMarca_ordem_alfab_decrescente(FABRICANTE fabricantes[], int ids_nomeMarca_decrescente[], int quantidade_de_fabricantes)
{

    // usa o array de ids para imprmir
    preenche_vet_com_ids(ids_nomeMarca_decrescente, quantidade_de_fabricantes);

    // Colocando em ordem alfabetica
    qsort(fabricantes, quantidade_de_fabricantes, sizeof(FABRICANTE), compara_nome_marca);
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

int compara_nome_produtos(const void *a, const void *b)
{
    const PRODUTO *produtoA = (const PRODUTO *)a;
    const PRODUTO *produtoB = (const PRODUTO *)b;
    // retorna em ordem crescente(A-Z)
    return strcmp((*(produtoA)).nome, (*(produtoB)).nome);
}

int compara_nome_marca(const void *a, const void *b)
{
    const FABRICANTE *fabricanteA = (const FABRICANTE *)a;
    const FABRICANTE *fabricanteB = (const FABRICANTE *)b;
    // retorna em ordem decrescente(Z-A)
    return strcmp((*(fabricanteB)).nome_marca, (*(fabricanteA)).nome_marca);
}

float le_valida_constraints(float min, float max, char message[], char err[])
{
    float n;
    int loop = 1;
    if (max < min)
    {
        float aux = max;
        max = min;
        min = aux;
    }
    do
    {
        printf("%s", message);
        scanf("%f", &n);
        if ((min <= n) && (n <= max))
        {
            return n;
        }
        else
        {
            printf("%s", err);
        }
    } while (loop);
}
