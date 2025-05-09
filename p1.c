#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NOME 100
#define MAX_MAX 100

typedef struct{
    int codigo;
    char nome[NOME];
    char nome_social[NOME];
    char cpf[NOME];
    char rua_numero[MAX_MAX];
    char bairro[NOME];
    char celular[NOME];

}cadastro;

typedef struct{
    int codigo;
    char descricao[NOME];
    char categoria[NOME];
    float preco_compra;
    float margem_lucro;
    float preco_venda;
    int quantidade_estoque;
    int quantidade_minima;

}produto;

void cadastro_cliente(FILE *arquivo){
    cadastro usuario;
    int codigo;
    char linha[MAX_MAX];
    //faz com que o codigo nunca seja o mesmo
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (sscanf(linha, "Codigo: %d", &codigo) == 1) {
            usuario.codigo = codigo + 1;
        }
    }
    printf("**********************************************\n");
    printf("    ***       Cadastro Cliente       ***      \n");
    printf("**********************************************\n");

    printf("Digite o seu nome completo: ");
    fgets(usuario.nome, sizeof(usuario.nome), stdin);
    printf("Digite seu nome social: ");
    fgets(usuario.nome_social, sizeof(usuario.nome_social), stdin);
    printf("Digite a seu CPF: \n");
    fgets(usuario.cpf, sizeof(usuario.cpf), stdin);
    printf("digite sua rua e o numero: ");
    fgets(usuario.rua_numero, sizeof(usuario.rua_numero), stdin);
    printf("digite seu bairro: ");
    fgets(usuario.bairro, sizeof(usuario.bairro), stdin);
    printf("digite seu numero de celular: ");
    fgets(usuario.celular, sizeof(usuario.celular), stdin);


    fprintf(arquivo, "Codigo: %d\n    Nome: %s    Nome Social: %s    cpf: % s   rua/numero: %s    Bairro: %s    Celular: %s", usuario.codigo, usuario.nome, usuario.nome_social, usuario.cpf, usuario.rua_numero, usuario.bairro, usuario.celular);
    fclose(arquivo);

    printf("%d", usuario.codigo);
    return arquivo;
}

void cadastro_produto(FILE *produto_txt){
    produto prod;
    char alimento[] = "Alimento";
    int codigo;
    int escolha = 0;
    char linha[MAX_MAX];
    //faz com que o codigo nunca seja o mesmo
    while (fgets(linha, sizeof(linha), produto_txt)) {
        if (sscanf(linha, "Codigo: %d\n", &codigo) == 1) {
            prod.codigo = codigo + 1;
        }
    }
    printf("**********************************************\n");
    printf("    ***       Cadastro produto       ***      \n");
    printf("**********************************************\n");

    printf("Nome e descricao do produto: ");
    fgets(prod.descricao, sizeof(prod.descricao), stdin);
    printf("1) Alimento\n 2) Material de limpeza\n 3) Panificacao\n\nDigite a categoria do produto:");
    scanf("%d", &escolha);
    while(escolha < 0 || escolha > 3){
        printf("1) Alimento\n 2) Material de limpeza\n 3) Panificacao\n\nDigite a categoria do produto correta:");
        scanf("%d", &escolha);
    }
    switch(escolha){
        case 1:
            strcpy(prod.categoria, "alimento");
            break;
        case 2:
            strcpy(prod.categoria, "Material Limpeza");
            break;
        case 3:
            strcpy(prod.categoria, "Panificacao");
            break;
        default:
            break;
    }

    printf("Valor de compra do produto: ");
    scanf(" %f", &prod.preco_compra);
    getchar();
    printf("Digite a margem de lucro do produto: ");
    scanf("%f", &prod.margem_lucro);
    getchar();
    printf("Digite o preco de venda: ");
    scanf("%f", &prod.preco_venda);
    getchar();
    printf("digite a quantidade do produto:");
    scanf("%d", &prod.quantidade_estoque);
    getchar();
    printf("digite a quantidade minima do produto:");
    scanf("%d", &prod.quantidade_minima);
    getchar();

    while(prod.quantidade_minima > prod.quantidade_estoque){
        printf("quantidade minima menor que a quantidade em estoque!!!\ninsira novamente a quantidade:");
        scanf("%d", &prod.quantidade_minima);
        getchar();
    }

    fprintf(produto_txt, "Codigo: %d\nNome: %sCategoria: %s\nvalor de compra: %.2f\nmargem de lucro: %.2f\nvalor de venda: %.2f\nquantidade estoque: %d\nquantidade minima: %d\n\n\n", prod.codigo, prod.descricao, prod.categoria, prod.preco_compra, prod.margem_lucro, prod.preco_venda, prod.quantidade_estoque, prod.quantidade_minima);
    fclose(produto_txt);

    return produto_txt;
}
int menuPrincipal()
{
    // Exibe o Menu Principal
    printf("\033[35m===================================================\n");
    printf("*** Menu Principal ***\n");
    printf("===================================================\033[0m\n\n");

    printf("1. Cadastros\n"
           "2. Vendas\n"
           "3. Abertura de caixa\n"
           "4. Fechamento de caixa\n"
           "5. Relatorios\n"
           "7. Sair\n\n");

    // Aqui o usuário escolhe a opção do Menu Principal
    printf("Digite o numero da categoria: ");
    return 0;
}

void nova_venda(FILE *produto_txt){
    produto amostra_produtos;
    char linha[MAX_MAX];
    char nome[90];
    char categoria[90];
    float valor;
    int quantidade_estoque;
    int codigo;
    printf("Codigo  |  Descricao   |   Categoria   |   Valor   |    Estoque\n\n");
    while (fgets(linha, sizeof(linha), produto_txt)) {
        if(sscanf(linha, "Codigo: %d", &codigo) == 1){
            printf("%5d", codigo);
        }
        if(sscanf(linha, "Nome: %s", &nome)){
            printf("%12s", nome);
        }
        if(sscanf(linha, "Categoria: %s", &categoria)){
            printf("%17s", categoria);
        }
        if(sscanf(linha, "valor de venda: %f", &valor)){
            printf("%14.2f", valor);
        }
        if(sscanf(linha, "quantidade estoque: %d", &quantidade_estoque)){
            printf("%12d\n\n", quantidade_estoque);
        }
    }
    printf("Escolha o produto pelo codigo: ");
    fclose(produto_txt);
}

int main(){
    produto prod;
    int escolha_menu;
    int quantidade;
    int codigo;
    int codigo_produto;
    int escolha;
    char linha[MAX_MAX];

    FILE* arquivo;
    arquivo = fopen("teste.txt", "a+");

    if(arquivo == NULL){
        printf("Erro ao encontrar o arquivo!");
        return 1;
    }
    FILE* produto_txt;
    produto_txt = fopen("produto.txt", "a+");

    if(produto_txt == NULL){
        printf("Erro ao encontrar o arquivo!");
        return 1;
    }
    menuPrincipal();
    while(scanf("%d", &escolha_menu) != 1){
        printf("Escolha somente uma das opcoes: >>");
        while(getchar() != '\n');
    }
    do{
        switch(escolha_menu){
            case 1:
                escolha_menu = 0;
                printf("\n 1) Cadastrar cliente\n 2) Cadastrar produto\n 3) Voltar ao menu principal\n\nEscolha uma opcao: >>");
                scanf("%d", &escolha_menu);
                getchar();
                switch(escolha_menu){
                    do{
                        case 1:
                            cadastro_cliente(arquivo);
                            break;
                        case 2:
                            cadastro_produto(produto_txt);
                            break;
                        case 3:
                            menuPrincipal();
                            while(scanf("%d", &escolha_menu) != 1){
                                printf("Escolha somente uma das opcoes >> ");
                                while(getchar() != '\n');
                            }

                    }while(escolha_menu != 2);
                }
                break;
            case 2:
                escolha_menu = 0;
                printf("\n 1) Nova venda\n 2) Retirada de caixa\n 3) Pagamento\n 4) Voltar ao menu principal\n\nEscolha uma opcao: >>");
                scanf("%d", &escolha_menu);
                getchar();
                switch(escolha_menu){
                    do{
                        case 1:
                            nova_venda(produto_txt);
                            while(scanf("%d", &escolha) != 1){
                                printf("digite um numero: >>");
                                while(getchar() != '\n');
                            }
                            printf("Informe a quantidade do produto: ");
                            scanf("%d", &quantidade);
                            while(fgets(linha, sizeof(linha), produto_txt)){
                                printf("%s", linha);
                                if(sscanf(linha, "Codigo: %d", &codigo) == 1){
                                    if(escolha == codigo){
                                        printf("eeeeeeeeeeeuuu!!!");
                                    }
                                }
                            }
                            break;
                        /*case 2:
                            retirada_de_caixa();
                            break;
                        case 3:
                            Pagamento();
                        case 4:
                            menuPrincipal();
                            while(scanf("%d", &escolha_menu) != 1){
                                printf("Escolha somente uma das opcoes >> ");
                                while(getchar() != '\n');
                            }*/

                    }while(escolha_menu != 2);
                }
                break;
        }
    }while(escolha_menu > 7);


    return 0;
}
