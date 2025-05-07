// Biblioteca que possui comandos relativos à entrada e saída de dados do computador
#include <stdio.h>
// Biblioteca para funções envolvendo alocação de memória, controle de processos, conversões etc
#include <stdlib.h>

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

// Declaração das funções
int menuPrincipal();
int categoriaMaterialDeLimpeza();
int categoriaVendaDeAlimentos();
int categoriaPadaria();
int comprarProdutosLimpeza(float valorDoProduto);
int comprarProdutosAlimento(float valorDoProduto);
int comprarProdutosPadaria(float valorDoProduto);
int pagamento();
int continuarCompra();
int escolha_cadastro;
FILE* arquivoo;
arquivoo = fopen("teste.txt", "a+");

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


// Declaração das variáveis globais
char compra, abrindoCaixa;
int quantidade;
int quantProdVendidos = 0, diaJaIniciado = 0, simulacaoDias = 0, validacaoSaldoInicial = 0;
int i = 1, estoqueValido = 1, foiAbertoHoje = 0;

// Variável responsável por armazenar a escolha do Menu Principal
int escolhaDoMenuPrincipal = 0;

// Variáveis responsáveis por armazenamento das categorias
float totalDia;
float total, valorCompra, desconto, descontoDaBere, total_desconto, valor_cliente, troco, totalDia, saldoFinal, saldoInicial, total_limpeza, total_alimentos, total_padaria;

// Vetor responsável por armazenar a quantidade de produtos do estoque da categoria 2. Material de Limpeza
int estoqueLimpeza[] = {50, 30, 0, 20, 100, 15, 60};
// Vetor responsável por armazenar a quantidade de produtos do estoque da categoria 3. Venda de Alimentos
int estoquealimentos[] = {10, 15, 10, 5, 20, 6, 15};

// Função principal do sistema
int main()
{
    // Variável responsável por armazenar a escolha de produtos do usuário
    int produtoEscolhido;
    // Vetor responsável por armazenar os preços dos produtos da categoria 2. Material de Limpeza
    float valoresProdutoLimpeza[] = {1.99, 8.99, 1.50, 15.00, 4.99, 7.99, 1.00};
    // Vetor responsável por armazenar os preços dos produtos da categoria 3. Venda de Alimentos
    float valoresProdutoAlimento[] = {19.99, 5.90, 4.50, 8.00, 5.00, 2.00, 5.00};
    // Vetor responsável por armazenar os preços dos produtos da categoria 4. Padaria
    float valoresProdutosPadaria[] = {9.50, 12.50, 1.90, 8.50, 12.50, 2.50, 17.50};
    // Vetor responsável por armazenar a quantidade de produtos do estoque da categoria 3. Venda de Alimentos
    int estoqueAlimentos[] = {10, 15, 10, 5, 20, 6, 15};
    // Variável auxiliar usada em loops de repetição (ex: para percorrer arrays)
    int a;
    // Quantidade total de produtos da padaria
    int n = 7;

    // Vetor que armazena a quantidade em estoque de cada produto da padaria
    int EstoquePadaria[n];
    // Vetor de strings com os nomes dos produtos da padaria
    char *nomesProdutosPadaria[] = {"Pao de Forma", "Pao Integral", "Pao Frances", "Sonho", "Biscoito", "Pao Doce", "Salgado"};

    // Vetor responsável por armazenar as categorias do Menu Principal
    float categorias[] = {total_limpeza, total_alimentos, total_padaria};
    // Variável responsável por armazenar a escolha de pagamento do usuário
    int formaPagamento, cartao;

    // Início do loop principal que representa os dias de operação da mercearia
    do
    {
        // Enquanto o dia atual (i) for diferente da quantidade total de dias simulados
        while (i != simulacaoDias)
        {
            // Executa o procedimento de "fim de dia" somente se for o primeiro acesso do dia
            if (diaJaIniciado == 0)
            {
                // Exibe informações de finalização do dia anterior
                diaFinalizado();
            }

            // O usuário escolhe uma opção no Menu Principal
            switch (escolhaDoMenuPrincipal)
            {

            // Caso o usuário escolha a opção 1. Abertura de Caixa
            case 1:
                // Verifica se o caixa ainda não foi aberto no dia
                if (foiAbertoHoje == 0)
                {
                    // Solicita ao usuário que confirme a abertura do caixa com 'A' ou 'a'
                    do
                    {
                        avisoAbrindoCaixa();
                        printf("Digite 'A' ou 'a' para abrir o caixa: ");
                        scanf(" %c", &abrindoCaixa);

                        // Se o usuário digitar corretamente
                        if (abrindoCaixa == 'A' || abrindoCaixa == 'a')
                        {
                            // Solicita o valor inicial do caixa
                            printf("Insira o Saldo Inicial do Caixa: R$ ");
                            while (scanf("%f", &saldoInicial) != 1)
                            {
                                // Valida a entrada e solicita novamente caso não seja número
                                printf("Insira o Saldo Inicial do Caixa: R$ ");
                                while (getchar() != '\n');
                            }

                            // Validações específicas para quando o sistema já passou do primeiro dia
                            while (i >= 2)
                            {
                                // Verifica se o saldo inicial inserido é maior que o fechamento anterior
                                if (saldoInicial > saldoFinal)
                                {
                                    validacaoSaldoInicial = 1;
                                    break;
                                }

                                else
                                {
                                    validacaoSaldoInicial = 0;
                                    break;
                                }
                            }

                            // Se o valor inserido for maior do que o saldo final anterior
                            if (validacaoSaldoInicial == 1)
                            {
                                while (saldoInicial > saldoFinal)
                                {
                                    printf("Voce esta tentando inserir um valor maior que o fechamento do caixa do dia anterior\n"
                                           "INSIRA UM VALOR MENOR PARA DAR PROSSEGUIMENTO NO SISTEMA\n\n");
                                    // Solicita novo valor inicial válido
                                    adicionarNovoSaldoInicial();
                                }
                            }

                            // Se o valor for menor que R$ 200,00. Pede confirmação da Dona Berê
                            if (validacaoSaldoInicial == 0)
                            {
                                while (saldoInicial < 200.00)
                                {
                                    // Mensagem avisando que o valor é muito baixo
                                    avisoParaBere();
                                    scanf("%s", &compra);

                                    // Se a Dona Berê quiser continuar mesmo assim
                                    if (compra == 's' || compra == 'S')
                                    {
                                        // Exibe um alerta de valor baixo
                                        avisoValorMinimo();
                                        break;
                                    }

                                    // Se quiser digitar um novo valor
                                    if (compra == 'n' || compra == 'N')
                                    {
                                        while (saldoInicial < 200.00)
                                        {
                                            // Solicita um novo valor
                                            adicionarNovoSaldoInicial();
                                            break;
                                        }

                                    }
                                }
                            }

                            // Exibe mensagem de sucesso ao abrir o caixa com o valor informado
                            avisoSaldoInicial();
                            // Marca que o dia já começou
                            diaJaIniciado = 1;
                            // Marca que o caixa foi aberto hoje
                            foiAbertoHoje = 1;

                                // Solicita o estoque dos produtos da padaria (manual)
                                for (a = 0; a < n; a++)
                                {
                                    printf("Informe o estoque para %s (codigo %d): ", nomesProdutosPadaria[a], 31 + a);

                                    // Validação: entrada deve ser número
                                    while(scanf("%d", &EstoquePadaria[a]) != 1)
                                    {
                                        printf("Por favor, informe somente numeros: >> ");
                                        while(getchar() != '\n');
                                    }

                                    // Validação: não permitir valores negativos
                                    while (EstoquePadaria[a] < 0)
                                    {
                                        printf("\033[31mNao eh permitido inserir valores negativos. Por favor, insira valores maiores que 0:\033[0m ");
                                        scanf("%d", &EstoquePadaria[a]);
                                    }
                            }
                            break;
                        }

                        // Limpa o buffer de entrada caso o usuário digite algo inválido (ex: letras)
                        while (getchar() != '\n');

                    // Continua solicitando até que digite 'A' ou 'a' corretamente
                    } while (diaJaIniciado != 'A' || diaJaIniciado != 'a');

                }

                // Se tentar abrir o caixa novamente no mesmo dia, não permite
                else
                {
                    printf("\033[31mNao eh possivel abrir o caixa novamente. Tente no dia seguinte\033[0m\n");

                    // Exibe o Menu Principal
                    menuPrincipal();
                    // Garante que o usuário digite um número válido ao escolher a opção no menu
                    while(scanf("%d", &escolhaDoMenuPrincipal) != 1){
                        printf("Por favor, informe somente numeros: >> ");
                        // Limpa o buffer de entrada caso o usuário digite algo inválido (ex: letras)
                        while(getchar() != '\n');
                    }break;
                }

                // Exibe o Menu Principal
                menuPrincipal();
                // Enquanto a escolha do usuário seja diferente da Abertura de Caixa
                while (scanf("%d", &escolhaDoMenuPrincipal) != 1)
                {
                    // Limpa o buffer de entrada caso o usuário digite algo inválido (ex: letras)
                    while (getchar() != '\n');
                    // Mensagem caso digite algo inválido
                    avisoPalavra();
                    // Exibe o Menu Principal
                    menuPrincipal();
                }
                break;

            // Caso o usuário escolha a opção 2. Material de Limpeza
            case 2:
                do{
                    printf("Escolha uma opcao: \n 1) Cadastrar cliente\n 2) Cadastrar produto");
                    while(scanf("%d", &escolha_cadastro) != 1){
                        printf("Digite uma opcao valida entre 1 e 2: ");
                        while(getchar() != '\n');

                    }
                    switch(escolha_cadastro){
                        do{
                            case 1:
                                cadastro_cliente(arquivo);
                                break;
                            case 2:
                                cadastro_produto(produto_txt);
                                break;
                        }while(escolha_menu > 2);
                    }
                }while(escolhaDoMenuPrincipal != 8);
            case 3:
                // Início do loop Do While da categoria 3. Venda de Alimentos
                do
                {
                    // Exibe o menu da categoria 3. Venda de Alimentos
                    categoriaVendaDeAlimentos();
                    // Garante que o usuário digite um número válido ao escolher a opção no menu
                    while(scanf("%d", &produtoEscolhido) != 1){
                        printf("Por favor, informe somente numeros: >> ");
                        // Limpa o buffer de entrada caso o usuário digite algo inválido (ex: letras)
                        while(getchar() != '\n');
                    }

                    // Escolha do produtos da categoria 3. Venda de Alimentos
                    switch (produtoEscolhido)
                    {
                        // 21 - Cafe (500 mg) - R$ 19.99 - Estoque: 10
                        case 21:
                            // Função utilizando como parâmetro o valor do produto
                            comprarProdutosAlimento(valoresProdutoAlimento[0]);

                            // Se o estoque do Café estiver vazio
                            if (estoqueAlimentos[0] == 0)
                            {
                                // Exibirá um aviso que falta Café no estoque
                                faltaProdutoNoEstoque();
                                total_alimentos = total_alimentos - (quantidade * valoresProdutoAlimento[0]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usuário escolheu for maior que a quantidade que tem no estoque
                            while (quantidade > estoqueAlimentos[0])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    estoqueAlimentos[0]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usuário
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque após a venda do item
                            estoqueAlimentos[0] -= quantidade;
                            // Registra o total da categoria 3. Venda de Alimentos
                            categorias[1] = total_alimentos;
                            // Indica que não houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 22 - Leite (caixinha) - R$ 5.90 - Estoque: 15
                        case 22:
                            // Função utilizando como parâmetro o valor do produto
                            comprarProdutosAlimento(valoresProdutoAlimento[1]);

                            // Se o estoque do Detergente estiver vazio
                            if (estoqueAlimentos[1] == 0)
                            {
                                // Exibirá um aviso que falta Leite no estoque
                                faltaProdutoNoEstoque();
                                total_alimentos = total_alimentos - (quantidade * valoresProdutoAlimento[1]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usuário escolheu for maior que a quantidade que tem no estoque
                            while (quantidade > estoqueAlimentos[1])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    estoqueAlimentos[1]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usuário
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque após a venda do item
                            estoqueAlimentos[1] -= quantidade;
                            // Registra o total da categoria 3. Venda de Alimentos
                            categorias[1] = total_alimentos;
                            // Indica que não houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 23 - Arroz (1 kg) - R$ 4.50 - Estoque: 10
                        case 23:
                            // Função utilizando como parâmetro o valor do produto
                            comprarProdutosAlimento(valoresProdutoAlimento[2]);

                            // Se o estoque do Arroz estiver vazio
                            if (estoqueAlimentos[2] == 0)
                            {
                                // Exibirá um aviso que falta Arroz no estoque
                                faltaProdutoNoEstoque();
                                total_alimentos = total_alimentos - (quantidade * valoresProdutoAlimento[2]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usuário escolheu for maior que a quantidade que tem no estoque
                            while (quantidade > estoqueAlimentos[2])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    estoqueAlimentos[2]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usuário
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque após a venda do item
                            estoqueAlimentos[2] -= quantidade;
                            // Registra o total da categoria 3. Venda de Alimentos
                            categorias[1] = total_alimentos;
                            // Indica que não houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 24 - Feijao Preto (1kg) - R$ 8.00 - Estoque: 5
                        case 24:
                            // Função utilizando como parâmetro o valor do produto
                            comprarProdutosAlimento(valoresProdutoAlimento[3]);

                            // Se o estoque do Detergente estiver vazio
                            if (estoqueAlimentos[3] == 0)
                            {
                                // Exibirá um aviso que falta Detergente no estoque
                                faltaProdutoNoEstoque();
                                total_alimentos = total_alimentos - (quantidade * valoresProdutoAlimento[3]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usuário escolheu for maior que a quantidade que tem no estoque
                            while (quantidade > estoqueAlimentos[3])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    estoqueAlimentos[3]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usuário
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque após a venda do item
                            estoqueAlimentos[3] -= quantidade;
                            // Registra o total da categoria 3. Venda de Alimentos
                            categorias[1] = total_alimentos;
                            // Indica que não houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 25 - Acucar (1 kg) - R$ 5.00 - Estoque: 20
                        case 25:
                            // Função utilizando como parâmetro o valor do produto
                            comprarProdutosAlimento(valoresProdutoAlimento[4]);

                            // Se o estoque do Detergente estiver vazio
                            if (estoqueAlimentos[4] == 0)
                            {
                                // Exibirá um aviso que falta Detergente no estoque
                                faltaProdutoNoEstoque();
                                total_alimentos = total_alimentos - (quantidade * valoresProdutoAlimento[4]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usuário escolheu for maior que a quantidade que tem no estoque
                            while (quantidade > estoqueAlimentos[4])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    estoqueAlimentos[4]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usuário
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque após a venda do item
                            estoqueAlimentos[4] -= quantidade;
                            // Registra o total da categoria 3. Venda de Alimentos
                            categorias[1] = total_alimentos;
                            // Indica que não houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 26 - Sal (1 kg) - R$ 2.00 - Estoque: 6
                        case 26:
                            // Função utilizando como parâmetro o valor do produto
                            comprarProdutosAlimento(valoresProdutoAlimento[5]);

                            // Se o estoque do Sal estiver vazio
                            if (estoqueAlimentos[5] == 0)
                            {
                                // Exibirá um aviso que falta Detergente no estoque
                                faltaProdutoNoEstoque();
                                total_alimentos = total_alimentos - (quantidade * valoresProdutoAlimento[5]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usuário escolheu for maior que a quantidade que tem no estoque
                            while (quantidade > estoqueAlimentos[5])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    estoqueAlimentos[5]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usuário
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque após a venda do item
                            estoqueAlimentos[5] -= quantidade;
                            // Registra o total da categoria 3. Venda de Alimentos
                            categorias[1] = total_alimentos;
                            // Indica que não houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 27 - Farinha de Trigo (1 kg) R$ 5.00 - Estoque: 15
                        case 27:
                            // Função utilizando como parâmetro o valor do produto
                            comprarProdutosAlimento(valoresProdutoAlimento[6]);

                            // Se o estoque do Detergente estiver vazio
                            if (estoqueAlimentos[6] == 0)
                            {
                                // Exibirá um aviso que falta Detergente no estoque
                                faltaProdutoNoEstoque();
                                total_alimentos = total_alimentos - (quantidade * valoresProdutoAlimento[6]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usuário escolheu for maior que a quantidade que tem no estoque
                            while (quantidade > estoqueAlimentos[6])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    estoqueAlimentos[6]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usuário
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque após a venda do item
                            estoqueAlimentos[6] -= quantidade;
                            // Registra o total da categoria 3. Venda de Alimentos
                            categorias[1] = total_alimentos;
                            // Indica que não houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 28 - Voltar ao Menu Principal
                        case 28:
                            // Exibe uma mensagem perguntando ao usuário se ele deseja permanecer na categoria ou não
                            continuarCompra();
                            break;

                        // Caso o usuário não escolha nenhuma das alternativas anteriores
                        default:
                            printf("\033[31m*** Escolha invalida ***\033[0m\n");
                            continue;
                    }
                } while (compra == 'S' || compra == 's');

                if (compra == 'n' || compra == 'N')
                {
                    menuPrincipal();
                    scanf("%d", &escolhaDoMenuPrincipal);
                }
                break;

            // Caso o usuário escolha a opção 4. Padaria
            case 4:
                // Início do loop Do While da categoria 4.Padaria
                do
                {
                    // Exibe o menu da categoria 4. Padaria
                    categoriaPadaria();
                    // Garante que o usuário digite um número válido ao escolher a opção no menu
                    while(scanf("%d", &produtoEscolhido) != 1){
                        printf("Por favor, informe somente numeros: >> ");
                        // Limpa o buffer de entrada caso o usuário digite algo inválido (ex: letras)
                        while(getchar() != '\n');
                    }

                    // Escolha dos produtos da categoria 4. Padaria
                    switch (produtoEscolhido)
                    {
                        // 31 - Pao de Forma (pacote) - R$ 9.50 - Unidade: ?
                        case 31:
                            // Função utilizando como parâmetro o valor do produto
                            comprarProdutosPadaria(valoresProdutosPadaria[0]);

                            // Se o estoque do Pão de Forma estiver vazio
                            if (EstoquePadaria[0] == 0)
                            {
                                // Exibirá um aviso que falta Pão de Forma no estoque
                                faltaProdutoNoEstoque();
                                total_padaria = total_padaria - (quantidade * valoresProdutosPadaria[0]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usuário escolheu for maior que a quantidade que tem no estoque
                            while (quantidade > EstoquePadaria[0])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    EstoquePadaria[0]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usuário
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque após a venda do item
                            EstoquePadaria[0] -= quantidade;
                            // Registra o total da categoria 4. Padaria
                            categorias[2] = total_padaria;
                            // Indica que não houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 32 - Pao Integral (pacote) - R$ 12.50 - Unidade: ?
                        case 32:
                            // Função utilizando como parâmetro o valor do produto
                            comprarProdutosPadaria(valoresProdutosPadaria[1]);

                            // Se o estoque do Pão Integral estiver vazio
                            if (EstoquePadaria[1] == 0)
                            {
                                // Exibirá um aviso que falta Pão Integral no estoque
                                faltaProdutoNoEstoque();
                                total_padaria = total_padaria - (quantidade * valoresProdutosPadaria[1]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usuário escolheu for maior que a quantidade que tem no estoque
                            while (quantidade > EstoquePadaria[1])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    EstoquePadaria[1]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usuário
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque após a venda do item
                            EstoquePadaria[1] -= quantidade;
                            // Registra o total da categoria 4. Padaria
                            categorias[2] = total_padaria;
                            // Indica que não houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 33 - Pao Frances (unidade) - R$ 1.90 - Unidade: ?
                        case 33:
                            // Função utilizando como parâmetro o valor do produto
                            comprarProdutosPadaria(valoresProdutosPadaria[2]);

                            // Se o estoque do Pão Francês estiver vazio
                            if(EstoquePadaria[2] == 0)
                            {
                                // Exibirá um aviso que falta Pão Francês no estoque
                                faltaProdutoNoEstoque();
                                total_padaria = total_padaria - (quantidade * valoresProdutosPadaria[2]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usuário escolheu for maior que a quantidade que tem no estoque
                            while(quantidade > EstoquePadaria[2])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    EstoquePadaria[2]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usuário
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque após a venda do item
                            EstoquePadaria[2] -= quantidade;
                            // Registra o total da categoria 4. Padaria
                            categorias[2] = total_padaria;
                            // Indica que não houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 34 - Sonho (unidade) - R$ 8.50 - Unidade: ?
                        case 34:
                            // Função utilizando como parâmetro o valor do produto
                            comprarProdutosPadaria(valoresProdutosPadaria[3]);

                            // Se o estoque do Sonho estiver vazio
                            if(EstoquePadaria[3] == 0)
                            {
                                // Exibirá um aviso que falta Sonho no estoque
                                faltaProdutoNoEstoque();
                                total_padaria = total_padaria - (quantidade * valoresProdutosPadaria[3]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usuário escolheu for maior que a quantidade que tem no estoque
                            while(quantidade > EstoquePadaria[3])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    EstoquePadaria[3]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usuário
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque após a venda do item
                            EstoquePadaria[3] -= quantidade;
                            // Registra o total da categoria 4. Padaria
                            categorias[2] = total_padaria;
                            // Indica que não houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 35 - Biscoito (kg) - R$ 12.50 - Unidade: ?
                        case 35:
                            // Função utilizando como parâmetro o valor do produto
                            comprarProdutosPadaria(valoresProdutosPadaria[4]);

                            // Se o estoque do Biscoito estiver vazio
                            if(EstoquePadaria[4] == 0)
                            {
                                // Exibirá um aviso que falta Biscoito no estoque
                                faltaProdutoNoEstoque();
                                total_padaria = total_padaria - (quantidade * valoresProdutosPadaria[4]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usuário escolheu for maior que a quantidade que tem no estoque
                            while(quantidade > EstoquePadaria[4])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    EstoquePadaria[4]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usuário
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque após a venda do item
                            EstoquePadaria[4] -= quantidade;
                            // Registra o total da categoria 4. Padaria
                            categorias[2] = total_padaria;
                            // Indica que não houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 36 - Pao Doce (unidade) - R$ 2.50 - Unidade: ?
                        case 36:
                            // Função utilizando como parâmetro o valor do produto
                            comprarProdutosPadaria(valoresProdutosPadaria[5]);

                            // Se o estoque do Pão Doce estiver vazio
                            if(EstoquePadaria[5] == 0)
                            {
                                // Exibirá um aviso que falta Pão Doce no estoque
                                faltaProdutoNoEstoque();
                                total_padaria = total_padaria - (quantidade * valoresProdutosPadaria[5]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usuário escolheu for maior que a quantidade que tem no estoque
                            while (quantidade > EstoquePadaria[5])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    EstoquePadaria[5]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usuário
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque após a venda do item
                            EstoquePadaria[5] -= quantidade;
                            // Registra o total da categoria 4. Padaria
                            categorias[2] = total_padaria;
                            // Indica que não houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 37 - Salgado (unidade) - R$ 17.50 - Estoque: ?
                        case 37:
                            // Função utilizando como parâmetro o valor do produto
                            comprarProdutosPadaria(valoresProdutosPadaria[6]);

                            // Se o estoque do Salgado estiver vazio
                            if (EstoquePadaria[6] == 0)
                            {
                                // Exibirá um aviso que falta Detergente no estoque
                                faltaProdutoNoEstoque();
                                total_padaria = total_padaria - (quantidade * valoresProdutosPadaria[6]);
                                quantProdVendidos -= quantidade;
                                break;
                            }

                            // Enquanto a quantidade de produtos que o usuário escolheu for maior que a quantidade que tem no estoque
                            while (quantidade > EstoquePadaria[6])
                            {
                                printf("A quantidade em estoque eh inferior a qual o cliente esta comprando \n"
                                    "Por favor, insira a quantidade menor ou igual a: %d\n\n",
                                    EstoquePadaria[6]);
                                // Solicita a quantidade do produto
                                printf("Informe a quantidade do produto: ");
                                // Guarda a escolha do usuário
                                scanf("%d", &quantidade);
                            }

                            // Atualiza o estoque após a venda do item
                            EstoquePadaria[6] -= quantidade;
                            // Registra o total da categoria 2. Material de Limpeza
                            categorias[2] = total_padaria;
                            // Indica que não houve tentativa de "venda acima do estoque" ou "roubo"
                            estoqueValido = 0;
                            break;

                        // 38 - Voltar ao Menu Principal
                        case 38:
                            // Exibe uma mensagem perguntando ao usuário se ele deseja permanecer na categoria ou não
                            continuarCompra();
                            break;

                        // Caso o usuário não escolha nenhuma das alternativas anteriores
                        default:
                            printf("\033[31m*** Escolha invalida ***\033[0m\n");
                            continue;
                    }
                } while (compra == 'S' || compra == 's');

                // Se o usuário não queira permanecer na categoria
                if (compra == 'n' || compra == 'N')
                {
                    // Exibe o Menu Principal
                    menuPrincipal();
                    // Garante que o usuário digite um número válido ao escolher a opção no menu
                    while(scanf("%d", &escolhaDoMenuPrincipal) != 1){
                        printf("Por favor, informe somente numeros: >> ");
                        // Limpa o buffer de entrada caso o usuário digite algo inválido (ex: letras)
                        while(getchar() != '\n');
                    }
                }
                break;

            // Caso o usuário escolha a opção 5. Pagamento
            case 5:
                // Início do Do While da categoria 5. Pagamento
                do
                {
                    // Função que mostra as opções de pagamento
                    pagamento();
                    // Guarda a escolha do usuário
                    while(scanf("%d", &formaPagamento) != 1){
                        printf("Por favor, informe somente numeros: >> ");
                        while(getchar() != '\n');
                    }
                    // Switch do 5. Pagamento
                    switch (formaPagamento)
                    {
                    // Caso o usuário escolha a opção de pagamento 1. Dinheiro
                    case 1:
                        // Informando a forma de pagamento
                        avisoPagamento();
                        // Aqui estou guardando o valor total da compra do cliente
                        total = total_alimentos + total_limpeza + total_padaria;
                        // Histórico das categorias
                        printf("1. Material de Limpeza - Total: R$ %.2f\n", total_limpeza);
                        printf("2. Venda de Alimentos - Total: R$ %.2f\n", total_alimentos);
                        printf("3. Padaria - Total: R$ %.2f\n\n", total_padaria);

                        // Valor total sem desconto
                        printf("Valor Total (SEM desconto): R$ %.2f\n\n", total);
                        printf("-------------------------------------------------\n");

                        // Se o usuário gastou menos ou igual a R$ 50.00
                        if (total <= 50)
                        {
                            total = total_alimentos + total_limpeza + total_padaria;
                            // Cálculo do valor do desconto
                            desconto = total * 0.05;
                            // Cálculo do valor que o cliente irá pagar
                            total_desconto = total - desconto;
                            // Mostrando o valor que o usuário irá pagar
                            printf("Valor Total (COM desconto): R$ %.2f \n\n", total_desconto);
                            // Aqui está dizendo para o usuário inserir o valor recebido em dinheiro
                            printf("Insira o Valor recebido em Dinheiro: R$ ");
                            // Armazenando o valor que o usuário informou acima
                            scanf("%f", &valor_cliente);

                            // Condição que é quando o usuário coloca um valor menor do que ele tem que pagar
                            if (valor_cliente < total_desconto)
                            {
                                // Informando o usuario que o valor inserido é menor que o valor a pagar
                                printf("-------------------------------------------------\n");
                                printf("O numero em Dinheiro fornecido pelo cliente eh menor que o Valor a Pagar\n"
                                       "Insira o Valor Novamente: R$ ");
                                // Aqui ficará armazenado o novo valor que o usuário deu para o pagamento
                                scanf("%f", &valor_cliente);
                            }

                            // Cálculo do valor de troco
                            troco = valor_cliente - total_desconto;
                            // Informa o troco que precisa ser entregado ao cliente
                            printf("Devolva o Troco de: R$ %.2f \n", troco);

                            // Calcula o que foi gastado no dia
                            totalDia = totalDia + total_desconto;
                            saldoFinal = (totalDia + saldoInicial) - troco;

                            // Aqui estamos calculando o que foi vendido no dia
                            categorias[0] = categorias[0] + total_limpeza;
                            categorias[1] = categorias[2] + total_alimentos;
                            categorias[2] = categorias[2] + total_padaria;

                            // Categorias zeradas para serem usadas no histórico
                            total_alimentos = 0;
                            total_limpeza = 0;
                            total_padaria = 0;

                            estoqueValido = 1;
                            break;
                        }

                        // Se o usuário gastou mais que R$ 50.00 e menos que R$ 100.00
                        else if (total > 50 && total < 200)
                        {
                            total = total_alimentos + total_limpeza + total_padaria;
                            // Cálculo do valor do desconto
                            desconto = total * 0.1;
                            // Cálculo do valor que o cliente irá pagar
                            total_desconto = total - desconto;
                            // Mostrando o valor que o usuário irá pagar
                            printf("Valor Total (COM desconto): R$ %.2f \n\n", total_desconto);
                            // Aqui está dizendo para o usuário inserir o valor recebido em dinheiro
                            printf("Insira o Valor recebido em Dinheiro: R$ ");
                            // Armazenando o valor que o usuário informou acima
                            scanf("%f", &valor_cliente);

                            // Condição que é erro que eh quando o usuário coloca um valor menor do que ele tem que pagar
                            if (valor_cliente < total_desconto)
                            {
                                // Informando o usuario que o valor inserido é menor que o valor a pagar
                                printf("-------------------------------------------------\n");
                                printf("O numero em Dinheiro fornecido pelo cliente eh menor que o Valor a Pagar\n"
                                       "Insira o Valor Novamente: R$ ");
                                // Aqui ficará armazenado o novo valor que o usuário deu para o pagamento
                                scanf("%f", &valor_cliente);
                            }

                            // Cálculo do valor de troco
                            troco = valor_cliente - total_desconto;
                            // Informa o troco que precisa ser entregado ao cliente
                            printf("Devolva o Troco de: R$ %.2f \n", troco);
                            // Calcula o que foi gastado no dia
                            totalDia = totalDia + total_desconto;
                            saldoFinal = (totalDia + saldoInicial) - troco;

                            // Aqui estamos calculando o que foi vendido no dia
                            categorias[0] = categorias[0] + total_limpeza;
                            categorias[1] = categorias[2] + total_alimentos;
                            categorias[2] = categorias[2] + total_padaria;

                            // Categorias zeradas para serem usadas no histórico
                            total_alimentos = 0;
                            total_limpeza = 0;
                            total_padaria = 0;

                            estoqueValido = 1;
                            break;
                        }

                        // Caso o valor total da compra seja superior a R$ 200,00
                        else if (total >= 200)
                        {
                            printf("O cliente fez uma compra superior a R$ 200.00\n");

                            // Solicita que Dona Berê informe o desconto (percentual)
                            do
                            {
                                printf("Dona Bere, informe o percentual de desconto (ex: 10 para 10%%): ");
                                // Garante que o usuário digite um número válido ao escolher a opção no menu
                                if (scanf("%f", &descontoDaBere) != 1 || descontoDaBere < 0 || descontoDaBere > 100) {
                                    printf("\033[31mValor invalido. Informe um numero entre 0 e 100.\033[0m\n");
                                    // Limpa o buffer de entrada caso o usuário digite algo inválido (ex: letras)
                                    while (getchar() != '\n');
                                } else {
                                    break;
                                }
                            // While (1) é como um loop que nunca termina, até que algo dentro dele interrompa a execução (normalmente com 'break')
                            } while (1);

                            // Recalcula o total e aplica o desconto corretamente
                            total = total_alimentos + total_limpeza + total_padaria;
                            desconto = total * (descontoDaBere / 100.0);
                            total_desconto = total - desconto;

                            printf("Valor com %.2f%% de desconto: R$ %.2f\n", descontoDaBere, total_desconto);

                            // Solicita o valor recebido pelo cliente
                            printf("Insira o valor recebido em dinheiro: R$ ");
                            scanf("%f", &valor_cliente);

                            // Validação: valor deve ser suficiente
                            while (valor_cliente < total_desconto)
                            {
                                printf("\033[31mValor insuficiente. Por favor, insira novamente: R$ \033[0m");
                                scanf("%f", &valor_cliente);
                            }

                            // Calcula o troco e exibe
                            troco = valor_cliente - total_desconto;
                            printf("Troco: R$ %.2f\n", troco);

                            // Atualiza os dados financeiros do dia
                            totalDia += total_desconto;
                            saldoFinal = (totalDia + saldoInicial) - troco;

                            // Atualiza totais por categoria
                            categorias[0] += total_limpeza;
                            categorias[1] += total_alimentos;
                            categorias[2] += total_padaria;

                            // Reseta os acumuladores para o próximo cliente
                            total_alimentos = 0;
                            total_limpeza = 0;
                            total_padaria = 0;
                            estoqueValido = 1;

                            break;
                        }

                    // Caso o usuário escolha a opção de pagamento 2. Cartão
                    case 2:

                        // Informando a forma de pagamento
                        printf("\033[35m==========================================================\n"
                                "*** Forma de pagamento escolhida: Cartao***\n"
                                "==========================================================\033[0m\n\n");

                        // Opções que o usuário tem que escolher no pagamento por cartão
                        printf("Pagamento na maquina (1. Ok ou 0. Nao Ok): ");
                        // Guarda o que o usuário escolheu
                        scanf("%d", &cartao);

                        // Switch do pagamento 2. Cartão
                        switch (cartao)
                        {
                        // Caso o usuário escolha a opção de pagamento 1. Ok
                        case 1:
                            total = total_alimentos + total_limpeza + total_padaria;
                            // Cálculo do total vendido que aparecerá no histórico
                            totalDia += total;
                            saldoFinal = totalDia + saldoInicial;
                            // Exibindo que o pagamento foi concluído
                            printf("\033[32mPagamento realizado com sucesso! :D \n"
                                   "O valor pago foi de\033[0m: R$ %.2f \n",
                                   total);

                            // Aqui estamos calculando o que foi vendido no dia
                            categorias[0] = categorias[0] + total_limpeza;
                            categorias[1] = categorias[2] + total_alimentos;
                            categorias[2] = categorias[2] + total_padaria;

                            // Categorias zeradas para serem usadas no histórico
                            total_alimentos = 0;
                            total_limpeza = 0;
                            total_padaria = 0;

                            estoqueValido = 1;

                            // Faz o case 1 parar
                            break;

                        // Caso o usuário escolha a opção de pagamento 0. Não Ok
                        case 0:
                            // Exibindo que o pagamento deu errado
                            printf("\033[31mPagamento deu erro! Tente outra forma de pagamento :( \033[0m\n");
                            // Aqui vai fazer ele voltar para o usuário escolher a forma de pagamento novamente
                            continue;
                        } // Fecha switch cartao
                        break;

                    // Caso o usuário não escolha nenhuma das opções listadas
                    default:
                        printf("\033[31m*** Escolha invalida ***\033[0m\n");
                        continue;
                    }
                    break; // fecha o switch de  pagamento

                    // Aqui encera o Do While do cartao ele faz voltar na escolha do pagamento
                } while (cartao == 0);

                menuPrincipal();
                while(scanf("%d", &escolhaDoMenuPrincipal) != 1){
                    printf("Por favor, informe somente numeros: >> ");
                    while(getchar() != '\n');
                }

            // Caso o usuário escolha a opção 6. Fechamento de Caixa
            case 6:
                // Se o usuário pagar corretamente
                if (estoqueValido == 1)
                {
                    avisoValoresFinais();
                    mostraFinalDia();
                    troco = 0;
                    diaFinalizado();
                }
                // Se o usuário não pagar o valor correto ou sair sem pagar
                else
                {
                    avisoDeRoubo();
                    menuPrincipal();
                    scanf("%d", &escolhaDoMenuPrincipal);
                }
                break;

            // Exibe mensagem de encerramento e finaliza o sistema imediatamente
            case 7:
                printf("\033[31m *** Sistema encerrado ***\033[0m\n");
                // O programa termina na hora com sucesso (sem erro)
                exit(0);
            }
        }
    } while (escolhaDoMenuPrincipal != 8);
    return 0;
}

// Função que mostra o Menu Principal
int menuPrincipal()
{
    // Exibe o Menu Principal
    printf("\033[35m===================================================\n");
    printf("*** Menu Principal ***\n");
    printf("===================================================\033[0m\n\n");

    printf("1. Abertura de Caixa\n"
           "2. cadastros\n"
           "3. Venda de Alimentos\n"
           "4. Padaria\n"
           "5. Pagamento\n"
           "6. Fechamento do Caixa\n"
           "7. Sair\n\n");

    // Aqui o usuário escolhe a opção do Menu Principal
    printf("Digite o numero da categoria: ");
    return 0;
}

// Função que mostra os produtos da categoria 2. Material de Limpeza

// Função que faz toda as etapas de comprar os produtos da categoria funcionarem

// Função que mostra as opções de pagamento
int pagamento()
{
    // Exibe o título da categoria 5. Pagamento
    printf("\033[35m=====================================================\n"
            "                *** Pagamento ***\n"
            "=====================================================\033[0m\n\n");
    // Opções em Dinheiro ou Cartão que o usuário tem que escolher
    printf("1. Dinheiro \n"
           "2. Cartao\n\n");

    // O usuário escolhe a forma de pagamento
    printf("Escolha forma de pagamento (1. Dinheiro ou 2. Cartao): ");
    return 0;
}

// Função que mostra o aviso de permanecer ou não na categoria escolhida pelo usuário
int continuarCompra()
{
    // Deixando o menu mais agradável para o usuário interagir
    printf("\033[35m===================================================\n");
    printf("*** Voltar ao Menu Principal ***\n");
    printf("===================================================\033[0m\n\n");
    // Mostrando para o usuario se ele quer permanecer ou não da categoria que escolheu
    printf("Deseja permanecer nessa categoria? Digite N para sair ou S para permanecer: ");
    // Guarda a escolha do usuário
    scanf(" %c", &compra);
    return 0;
}

// Função de aviso para o usuário iniciar apenas com o 1. Abertura de Caixa
int avisoAberturaDeCaixa()
{
    printf("\033[31m============================================================================================\033[0m\n");
    printf("\033[33m*** Para iniciar o dia, sera necessario a abertura de caixa! ***\033[0m\n");
    printf("\033[31m============================================================================================\033[0m\n");
}

// Função que exibe o título da categoria 2. Material de Limpeza
int tituloCategoriaLimpeza()
{
    printf("\033[34m===================================================\n");
    printf("*** 2. Material de Limpeza ***\n");
    printf("===================================================\033[0m\n\n");
}

// Função que exibe o título da categoria 3. Venda de Alimentos
int tituloCategoriaAlimentos()
{
    printf("\033[33m===================================================\n");
    printf("*** 3. Venda de Alimentos ***\n");
    printf("===================================================\033[0m\n\n");
}

// Função que exibe o título da categoria 4. Padaria
int tituloCategoriaPadaria()
{
    printf("\033[36m===================================================\n");
    printf("*** 4. Padaria ***\n");
    printf("===================================================\033[0m\n\n");
}

// Função que exibe a forma de pagamento escolhida pelo usuário 1. Dinheiro
int avisoPagamento()
{
    printf("\033[35m==============================================================\n"
            "*** Forma de pagamento escolhida: Dinheiro ***\n"
            "==============================================================\n\n\033[0m");
}

// Função que exibe a quantidade em dinheiro que o caixa foi aberto
int avisoSaldoInicial()
{
    printf("\033[35m======================================================\n");
    printf("O caixa foi aberto com o total de: R$ %.2f \n", saldoInicial);
    printf("======================================================\033[0m\n");
}

// Função que exibe que o item específico não tem no estoque
int faltaProdutoNoEstoque()
{
    printf("\033[31m===================\033[0m \033[33mATENCAO\033[0m \033[31m===================\033[0m\n\n"
           "\033[31mProduto sem estoque! Por favor, selecione outro item\033[0m\n\n");
}

// Função que exibe para o usuário digitar apenas números, e não palavras
int avisoPalavra()
{
    printf("\033[31m=====================================================================\n");
    printf("Nao eh possivel digitar letra. Por favor, insira um numero: \n");
    printf("=====================================================================\033[0m\n\n");
}

// Função que exibe o aviso de fechamento do dia
int diaFinalizado()
{
    while (escolhaDoMenuPrincipal != 1)
    {
        avisoDoDia();
        avisoAberturaDeCaixa();
        menuPrincipal();
        while (scanf("%d", &escolhaDoMenuPrincipal) != 1)
        {
            avisoPalavra();
            menuPrincipal();
            while (getchar() != '\n');
        }
        saldoFinal = (totalDia + saldoInicial) - troco;
        quantProdVendidos = 0;
        foiAbertoHoje = 0;
        totalDia = 0;
    }
}

// Função que exibe o título de Venda e Faturamento
int avisoValoresFinais()
{
    printf("\033[35m=================================================\n");
    printf("*** Quantidade de Vendas e Faturamento ***\n");
    printf("=================================================\033[0m\n\n");
}

// Função que exibe o histórico do dia
int mostraFinalDia()
{
    // Conta que indica o saldo final do dia
    saldoFinal = (totalDia + saldoInicial - troco);
    // Histórico da quantidades de produtos vendidos e das vendas
    printf("Valor de Abertura de Caixa: %.2f\n", saldoInicial);
    printf("Lucro do Dia: %.2f\n", totalDia);
    printf("Quantidade de produtos vendidos - Total: %d\n", quantProdVendidos);
    printf("Valor total do Fechamento de Caixa: %.2f\n\n", saldoFinal);
    printf("\033[32m*** DIA FINALIZADO! ***	\033[0m\n\n\n");
    i++;
}

// Função que exibe qual dia é
int avisoDoDia()
{
    printf("==========================\n");
    printf("Day Number: %d\n", i);
    printf("==========================\n\n");
}

// Função que exibe o aviso de que o caixa foi aberto abaixo do saldo mínimo
int avisoValorMinimo()
{
    printf("\033[35m=================================================\n");
    printf("*** O CAIXA FOI ABERTO ABAIXO DO SALDO MINIMO ***\n");
    printf("=================================================\033[0m\n");
}

// Função que exibe um aviso caso o usuário escolha um valor menor que o mínimo para iniciar a abertura de caixa
int avisoParaBere()
{
    printf("\n\033[31m=================== \033[33mATENCAO\033[0m\033[31m ===================\033[0m\n");
    printf("\033[38m\nVoce esta abrindo o caixa com a valor a baixo do minimo que eh: R$ 200.00\n"
            "Tem certeza em abrir o caixa abaixo do valor minimo?\n\n"
            "Digite S para entrar com o Saldo Inferior ao Minimo ou N para inserir outro valor: >> \033[0m");
}

// Função que exibe que o caixa foi aberto
int avisoAbrindoCaixa()
{
    printf("\033[35m======================================\n"
            "*** Realizando a Abertura do Caixa ***\n"
            "======================================\033[0m\n");
}

// Função que exibe um aviso que o cliente não pode sair sem finalizar o pagamento
int avisoDeRoubo()
{
    printf("\033[31m===================\033[0m \033[33mATENCAO\033[0m \033[31m===================\033[0m\n\n"
           "Nao eh possivel fechar o dia. Pois tem item para finalizar pagamento\n\n");
}

// Função que exibe um aviso para o usuário inserir novamente o saldo inicial do caixa
int adicionarNovoSaldoInicial()
{
    printf("Insira novamente o Saldo Inicial do Caixa: R$  ");
    while (scanf("%f", &saldoInicial) != 1)
    {
        while (getchar() != '\n');
    }
}
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
    int codigo;
    char linha[MAX_MAX];
    //faz com que o codigo nunca seja o mesmo
    while (fgets(linha, sizeof(linha), produto_txt)) {
        if (sscanf(linha, "Codigo: %d\n", &codigo) == 1) {
            prod.codigo = codigo + 1;
            printf("%d", codigo);
        }
    }
    printf("**********************************************\n");
    printf("    ***       Cadastro produto       ***      \n");
    printf("**********************************************\n");

    printf("Nome e descricao do produto: ");
    fgets(prod.descricao, sizeof(prod.descricao), stdin);
    printf("Digite a categoria do produto: ");
    fgets(prod.categoria, sizeof(prod.categoria), stdin);
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

    fprintf(produto_txt, "Codigo: %d\n    Nome: %s     Categoria: %s    valor de compra: %.2f\n    margem de lucro: %.2f\n    valor de venda: %.2f\n    quantidade estoque: %d\n    quantidade minima: %d\n\n\n", prod.codigo, prod.descricao, prod.categoria, prod.preco_compra, prod.margem_lucro, prod.preco_venda, prod.quantidade_estoque, prod.quantidade_minima);
    fclose(produto_txt);

    return produto_txt;
}

