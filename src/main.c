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
    char nome_marca[36], site[50];
    int telefone, id_uf;
    int id_fabricante;
    int qtd_carac_nome;
} FABRICANTE;

typedef struct
{
    char nome[30];
    int id_uf;
} UF;

void RegistrarMarca(FABRICANTE *fabricante, int i); // PRIMEIRA ALTERACAO
void RegistrarSite(FABRICANTE *fabricante, int i);
void RegistrarTelefone(FABRICANTE *fabricante, int i);
void RegistrarUf();
int le_valida_marca(FABRICANTE *fabricante);
void ImprimeMarca(int marca_registrada, FABRICANTE *fabricante);
void nome__marca_compactado(FABRICANTE *fabricante, int marca_registrada);
void EstruturaTabela(FABRICANTE *fabricante, int marca_registrada);


int main()
{

    PRODUTO produto[50];
    FABRICANTE fabricante[5];
    UF uf[27];
    int qtd_marcas;

    qtd_marcas = le_valida_marca(fabricante);
    ImprimeMarca(qtd_marcas, fabricante);
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
    scanf("%d", &fabricante[i].telefone);
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
    {                                                // minimo de 2 marcas registradas
        RegistrarMarca((*fabricante).nome_marca, i); // SEGUNDA ALTERACAO
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
        printf("fabricante[%d].nome_marca = %s\n", i, (*(fabricante + i)).nome_marca); // SEGUNDA ALTERACAO
    }
}

void nome__marca_compactado(FABRICANTE *fabricante, int marca_registrada)
{
    int i = 0;

    for (i = 0; i < marca_registrada; i++)
    {
        int posicao = 0;
        if(i==0){
            printf("-----------------+\n");// quebra linha entre uma marca e outra
        }else{
            printf("\n-----------------+\n");
        }
        fabricante[i].qtd_carac_nome = strlen(fabricante[i].nome_marca);
        if (fabricante[i].qtd_carac_nome > 16)
        {
            
            while (posicao < 17)
            {
                printf("%c", (*(fabricante + i)).nome_marca[posicao]);
                posicao++;
            }
            
            if (posicao == 17)
            {
                printf("|\n");
                printf("%c", (*(fabricante + i)).nome_marca[posicao]);
                posicao++;
            }
            
            while (posicao > 17 && posicao <= fabricante[i].qtd_carac_nome)
            {
                printf("%c", (*(fabricante + i)).nome_marca[posicao]);
                posicao++;
            }
            while(posicao < 35){
                printf(" ");
                posicao++;
            }
            if(posicao == 35){
                printf("|");
            }


        }else{
            //if (fabricante[i].qtd_carac_nome <= 16){
            //printf(" %s", (*(fabricante + i)).nome_marca);

            while (posicao <= fabricante[i].qtd_carac_nome)
            {
                printf("%c", (*(fabricante + i)).nome_marca[posicao]);
                posicao++;
            }
            while(posicao<18){
                printf(" ");
                posicao++;
            }
            if(posicao == 18){
                printf("|");
            }

        }
    }
}
/*-----------------------------------------------------------------------*/
void EstruturaTabela(FABRICANTE *fabricante, int marca_registrada)
{
    int i = 0;
    char TipoRelatorio[81] = {"                          RELATORIO 1 - LISTA DE TODAS AS MARCAS                "};
    char Topicos[82] = {"     MARCA       |               SITE               |     TELEFONE     |   UF   "};
    // fabricante[i].nome_marca
    // qtd_carac_nome -> guarda a quantidade de caracteres que cada nome possui
    
    printf("\n==============================================================================\n");
    printf("                          RELATORIO 1 - LISTA DE TODAS AS MARCAS                ");
    printf("\n==============================================================================\n");
    printf("     MARCA       |               SITE               |     TELEFONE     |   UF   \n");
    nome__marca_compactado(fabricante, marca_registrada);
    //teste
}