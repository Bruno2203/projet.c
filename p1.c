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

int salvar_vendas(FILE *vendas,FILE *produto_txt, int codigo, int quantidade_vendidas){
    produto prod;
    char linha[MAX_MAX];
    float lucro = 0;
    rewind(produto_txt);
    while (fgets(linha, sizeof(linha), produto_txt)) {
        if (sscanf(linha, "Codigo: %d", &prod.codigo) == 1) {
            fgets(linha, sizeof(linha), produto_txt);
            sscanf(linha, "Nome: %[^\n]", prod.descricao);

            fgets(linha, sizeof(linha), produto_txt);
            sscanf(linha, "Categoria: %[^\n]", prod.categoria);

            fgets(linha, sizeof(linha), produto_txt);
            sscanf(linha, "valor de compra: %f", &prod.preco_compra);

            fgets(linha, sizeof(linha), produto_txt);
            sscanf(linha, "margem de lucro: %f", &prod.margem_lucro);

            fgets(linha, sizeof(linha), produto_txt);
            sscanf(linha, "valor de venda: %f", &prod.preco_venda);

            fgets(linha, sizeof(linha), produto_txt);
            sscanf(linha, "quantidade estoque: %d", &prod.quantidade_estoque);

            fgets(linha, sizeof(linha), produto_txt);
            sscanf(linha, "quantidade minima: %d", &prod.quantidade_minima);

            if (codigo == prod.codigo){
                lucro = (prod.preco_venda - prod.preco_compra) * quantidade_vendidas;

                fprintf(vendas,
                    "Produto: %s\n"
                    "Categoria: %s\n"
                    "Quantidade vendida: %d\n"
                    "Preço unitário: %.2f\n"
                    "Lucro da venda: %.2f\n"
                    "--------------------------\n",
                    prod.descricao,
                    prod.categoria,
                    quantidade_vendidas,
                    prod.preco_venda,
                    lucro
                );
                return lucro;
            }
        }
    }
}

void nova_venda(FILE *produto_txt, FILE *vendas, float total, float desconto){
    produto prod;
    int quantidade_estoque;
    int escolha;
    int quantidade;
    int pagamento = 0;
    int descontoDaBere;
    char linha[MAX_MAX];
    char continuar;
    float lucro_total = 0;

    do{
        rewind(produto_txt);
        printf("Codigo  |  Descricao   |   Categoria   |   Valor   |    Estoque\n\n");
        while (fgets(linha, sizeof(linha), produto_txt)) {
            if (sscanf(linha, "Codigo: %d", &prod.codigo) == 1) {
                fgets(linha, sizeof(linha), produto_txt);
                sscanf(linha, "Nome: %[^\n]", prod.descricao);

                fgets(linha, sizeof(linha), produto_txt);
                sscanf(linha, "Categoria: %[^\n]", prod.categoria);

                fgets(linha, sizeof(linha), produto_txt);
                sscanf(linha, "valor de compra: %f", &prod.preco_compra);

                fgets(linha, sizeof(linha), produto_txt);
                sscanf(linha, "margem de lucro: %f", &prod.margem_lucro);

                fgets(linha, sizeof(linha), produto_txt);
                sscanf(linha, "valor de venda: %f", &prod.preco_venda);

                fgets(linha, sizeof(linha), produto_txt);
                sscanf(linha, "quantidade estoque: %d", &prod.quantidade_estoque);

                fgets(linha, sizeof(linha), produto_txt);
                sscanf(linha, "quantidade minima: %d", &prod.quantidade_minima);

                printf("%6d | %12s | %13s | %8.2f | %9d\n",
                   prod.codigo, prod.descricao, prod.categoria, prod.preco_venda, prod.quantidade_estoque);
            }
        }
        printf("\n%50s Total: R$ %.2f\n", "", total);
        printf("%47s Desconto: R$ %.2f\n", "", desconto);
        printf("%44s Total final: R$ %.2f\n", "", total - desconto);
        rewind(produto_txt);
        printf("insira o codigo do produto: ");
        while(scanf("%d", &escolha) != 1){
            printf("digite um numero: >>");
            while(getchar() != '\n');
        }
        getchar();

        printf("Informe a quantidade do produto: ");
        while(scanf("%d", &quantidade) != 1){
            printf("digite um numero: >>");
            while(getchar() != '\n');
        }
        getchar();
        while (fgets(linha, sizeof(linha), produto_txt)) {
            if (sscanf(linha, "Codigo: %d", &prod.codigo) == 1) {
                fgets(linha, sizeof(linha), produto_txt);
                sscanf(linha, "Nome: %[^\n]", prod.descricao);

                fgets(linha, sizeof(linha), produto_txt);
                sscanf(linha, "Categoria: %[^\n]", prod.categoria);

                fgets(linha, sizeof(linha), produto_txt);
                sscanf(linha, "valor de compra: %f", &prod.preco_compra);

                fgets(linha, sizeof(linha), produto_txt);
                sscanf(linha, "margem de lucro: %f", &prod.margem_lucro);

                fgets(linha, sizeof(linha), produto_txt);
                sscanf(linha, "valor de venda: %f", &prod.preco_venda);

                fgets(linha, sizeof(linha), produto_txt);
                sscanf(linha, "quantidade estoque: %d", &prod.quantidade_estoque);

                fgets(linha, sizeof(linha), produto_txt);
                sscanf(linha, "quantidade minima: %d", &prod.quantidade_minima);

                if(escolha == prod.codigo){
                    lucro_total += salvar_vendas(vendas, produto_txt, escolha, quantidade);
                    atualiza_estoque(produto_txt, escolha, quantidade);
                    float aux = prod.preco_venda * quantidade;
                    total = total + aux;
                    break;
                }
            }
        }
        printf("\nDeseja adicionar mais produtos? (s/n): ");
        scanf(" %c", &continuar);
        getchar();

    }while (continuar == 's' || continuar == 'S');
    if (continuar == 'n' || continuar == 'N') {
        // Aplica desconto, imprime total e sai da função
        if (total <= 50) {
            desconto = total * 0.05;
        } else if (total > 50 && total < 200) {
            desconto = total * 0.1;
        } else if (total >= 200) {
            printf("Valor da compra maior que 200!\nDigite o valor do desconto em porcentagem Ex:(10 = 10%): >> ");
            scanf("%d", &descontoDaBere);
            desconto = total * (descontoDaBere / 100.0);
        }
    }
        printf("\n%50s Total: R$ %.2f\n", "", total);
        printf("%47s Desconto: R$ %.2f\n", "", desconto);
        printf("%44s Total final: R$ %.2f\n", "", total - desconto);

        fprintf(vendas, "Lucro Total: %.2f\n\n", lucro_total);
    return;
}

void atualiza_estoque(FILE *produto_txt, int codigo, int quantidade_vendida) {
    produto prod;

    // Percorre o arquivo procurando o produto
    while (fread(&prod, sizeof(produto), 1, produto_txt) == 1) {
        if (prod.codigo == codigo) {
            // Atualiza a quantidade
            if (prod.quantidade_estoque >= quantidade_vendida) {
                prod.quantidade_estoque -= quantidade_vendida;

                // Move o ponteiro de volta para regravar este produto
                fseek(produto_txt, -sizeof(produto), SEEK_CUR);
                fwrite(&prod, sizeof(produto), 1, produto_txt);
                printf("Estoque atualizado com sucesso.\n");
            } else {
                printf("Estoque insuficiente.\n");
            }
            fclose(produto_txt);
            return;
        }
    }

}

int retirada_caixa(FILE *produto_txt){

}
void pagamento_f(float total, float desconto) {
    int escolha;
    int pagamento_cartao;
    float valor_dinheiro;
    char continuar;
    float total_final = total - desconto;

    printf("\033[1mPagamento:\033[0m\n1) Pagamento no cartao\n2) Pagamento em dinheiro\n3) Retornar às compras\nDigite a forma de pagamento: ");

    while (scanf("%d", &escolha) != 1 || escolha < 1 || escolha > 3) {
        printf("Escolha inválida. Tente novamente: ");
        while (getchar() != '\n');
    }

    switch (escolha) {
        case 1:
            printf("\n%50s Total: R$ %.2f\n\n", "", total);
            printf("Informe (1) – Pagamento na maquininha OK; (0) – Pagamento não OK: ");
            while (scanf("%d", &pagamento_cartao) != 1 || (pagamento_cartao != 0 && pagamento_cartao != 1)) {
                printf("Digite 0 ou 1: ");
                while (getchar() != '\n');
            }

            if (pagamento_cartao == 1) {
                printf("Pagamento aprovado!\n");
                menuPrincipal(); // Essa função precisa estar definida
            } else {
                pagamento_f(total, desconto); // Tenta de novo
            }
            break;

        case 2:
            printf("\n%50s Total: R$ %.2f\n", "", total);
            printf("%47s Desconto: R$ %.2f\n", "", desconto);
            printf("%44s Total final: R$ %.2f\n\n", "", total_final);

            printf("Insira o valor recebido em dinheiro: ");
            while (scanf("%f", &valor_dinheiro) != 1 || valor_dinheiro < 0) {
                printf("Valor inválido. Tente novamente: ");
                while (getchar() != '\n');
            }

            if (valor_dinheiro >= total_final) {
                printf("Troco: R$ %.2f\n", valor_dinheiro - total_final);
                menuPrincipal();
            } else {
                printf("Valor insuficiente. Deseja pagar o restante no cartão? (S/N): ");
                while (getchar() != '\n'); // limpa buffer antes de ler char
                scanf("%c", &continuar);

                if (continuar == 's' || continuar == 'S') {
                    float restante = total_final - valor_dinheiro;
                    printf("Valor em débito: R$ %.2f\n", restante);
                    printf("Informe (1) – Pagamento na maquininha OK; (0) – Pagamento não OK: ");
                    while (scanf("%d", &pagamento_cartao) != 1 || (pagamento_cartao != 0 && pagamento_cartao != 1)) {
                        printf("Digite 0 ou 1: ");
                        while (getchar() != '\n');
                    }

                    if (pagamento_cartao == 1) {
                        printf("Pagamento aprovado!\n");
                        menuPrincipal();
                    } else {
                        pagamento_f(total, desconto);
                    }
                } else {
                    pagamento_f(total, desconto); // retorna ao início do pagamento
                }
            }
            break;

        case 3:
            printf("Retornando às compras...\n");
            menuPrincipal(); // ou lógica para voltar às compras
            break;
    }
}



int main(){
    produto prod;
    int escolha_menu;
    int quantidade;
    int codigo;
    int codigo_produto;
    int escolha;
    char continuar;
    char linha[MAX_MAX];
    float total;
    float desconto;

    FILE* arquivo;
    arquivo = fopen("cliente.txt", "a+");

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
    FILE* vendas;
    vendas = fopen("vendas.txt", "a+");

    if(vendas == NULL){
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
                            do{
                                nova_venda(produto_txt, vendas, total, desconto);
                                printf("\n 1) Nova venda\n 2) Retirada de caixa\n 3) Pagamento\n 4) Voltar ao menu principal\n\nEscolha uma opcao: >>");
                                scanf("%d", &escolha_menu);
                            }while(escolha_menu != 1);
                            fclose(produto_txt);
                            break;
                        case 2:
                            retirada_caixa(produto_txt);
                            break;
                        case 3:
                            pagamento_f(total, desconto);
                        case 4:
                            menuPrincipal();
                            while(scanf("%d", &escolha_menu) != 1){
                                printf("Escolha somente uma das opcoes >> ");
                                while(getchar() != '\n');
                            }

                    }while(escolha_menu != 2);
                }
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                printf("Relatorios\n1) Listagem de clientes\n2) Listagem de Produtos\n3)Listagem de vendas\n4)Voltar ao menu principal\n");
                scanf("%d", &escolha);
                switch(escolha){
                    case 1:
                        while (fgets(linha, sizeof(linha), arquivo)) {
                            printf("%s", linha);
                        }
                        break;
                    case 2:
                        while (fgets(linha, sizeof(linha), produto_txt)) {
                            printf("%s", linha);
                        }
                        break;
                    case 3:
                        while (fgets(linha, sizeof(linha), vendas)) {
                            printf("%s", linha);
                        }
                        break;
                    case 4:
                        menuPrincipal();
                        while(scanf("%d", &escolha_menu) != 1){
                            printf("Escolha somente uma das opcoes: >>");
                            while(getchar() != '\n');
                        }
                        break;
                }
        }
    }while(escolha_menu > 7);


    return 0;
}
