#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "funcoes_estoque.h"

#define MAX 100

// Função pra limpar o terminal
void limparTela(){
    system("cls"); 
}

// Função pra limpar o buffer pós scanf
void limparBuffer(){
    int c;
    do {
        c = getchar(); //Serve para ler um caractere da entrada padrão, pausar a execução ou limpar o buffer de entrada.
    } while (c != '\n' && c != EOF); //Limpa o buffer de entrada, ignorando todos os caracteres até a quebra de linha ou fim do arquivo
}

// Função para dá uma pequena pausa entre as mensagens/menus
void pequenaPausa(){
    printf("\nPressione ENTER para continuar...\n");

    int key;
    do {
        key = getchar();
    } while (key != '\n' && key != EOF);
}

// Função para cadastrar um novo item
int cadastrarItem(int id[], char nome[][50], float preco[], int quantidade[], int total_de_produtos){
    // Verifica se o limite de produtos foi atingido
    if(total_de_produtos >= MAX){
        limparTela();
        printf("Limite de produtos atingido\n");
        getchar();
        pequenaPausa();
        return 0; // Retorna 0 para indicar que o cadastro falhou
    }

    int novoID;    
    int id_duplicado;
    int input_valido;
    
    do {

        id_duplicado = 0;
        input_valido = 1;

        printf("Digite o ID do produto (entre 0 e 9999): ");
        
        // Verifica se o ID é um numero inteiro
        if (scanf("%d", &novoID) != 1){
            limparTela();
            printf("ERRO: DIGITE UM NUMERO INTEIRO POSITIVO!\n");
            limparBuffer();
            input_valido = 0;
            continue;
        }
        limparBuffer();

        //Verifica se o numero do ID está entre 0 e 9999
        if (novoID < 0 || novoID > 9999){
            limparTela();
            printf("ERRO: DIGITE UM NUMERO ENTRE 0 E 9999!\n");
            input_valido = 0;
            continue;
        }
        
        // Verifica se o ID já está cadastrado
        for(int i = 0; i < total_de_produtos; i++){
            if(id[i] == novoID){
                id_duplicado = 1;
                printf("ID ja existe. Digite outro!\n");
                pequenaPausa();
                break;
            }
        }

    } while (id_duplicado || !input_valido);
    
    // Armazena o novo ID no vetor
    id[total_de_produtos] = novoID;

    // Solicita o nome do produto
    printf("Digite o nome do produto: ");
    scanf(" %[^\n]", nome[total_de_produtos]);
    limparBuffer();

    // Solicita o preço do produto
    printf("Digite o preco do produto: ");
    scanf("%f", &preco[total_de_produtos]);
    limparBuffer();

    // Verifica se o preço do produto não é negativo
    if(preco[total_de_produtos] < 0){
        limparTela();
        printf("ERRO: o preço não pode ser negativo!\n");
        pequenaPausa();
        return 0;
    }

    // Solicita a quantidade do produto em estoque
    printf("Digite a quantidade em estoque: ");
    scanf("%d", &quantidade[total_de_produtos]);
    limparBuffer();

     if(quantidade[total_de_produtos] < 0){
        limparTela();
        printf("ERRO: a quantidade não pode ser negativa!\n");
        pequenaPausa();
        return 0;
    }

    limparTela();
    printf("Produto adicionado com sucesso!\n");
    pequenaPausa();

    return 1; // Retorna 1 para indicar sucesso no cadastro
}

//Função para listar todos os produtos cadastrados
void listarItens(int id[], char nome[][50], float preco[], int quantidade[], int total_de_produtos){
    if(total_de_produtos == 0){
        limparTela();
        printf("NENHUM PRODUTO CADASTRADO PARA LISTAR!\n");
        getchar();
        pequenaPausa();
        return;
    }

    //Loop para ordenar pelo ID
    for(int i = 0; i < total_de_produtos - 1; i++){
        for(int j = 0; j < total_de_produtos - i - 1; j++){
            if(id[j] > id[j + 1]){
                //Trocar ID
                int temp_id = id[j];
                id[j] = id[j + 1];
                id[j + 1] = temp_id;

                //Trocar Nome
                char temp_nome[50];
                strcpy(temp_nome, nome[j]);
                strcpy(nome[j], nome[j + 1]);
                strcpy(nome[j + 1], temp_nome);

                //Trocar Preço
                float temp_preco = preco[j];
                preco[j] = preco[j + 1];
                preco[j + 1] = temp_preco;

                //Trocar Quantidade
                int temp_quant = quantidade[j];
                quantidade[j] = quantidade[j + 1];
                quantidade[j + 1] = temp_quant;
            }
        }
    }

    limparBuffer();
    printf("======== LISTA DE PRODUTOS CADASTRADOS ========\n");
    for(int i = 0; i < total_de_produtos; i++){
        printf("ID: %d | Nome: %s | Preco: %.2f | Quantidade: %d\n", id[i], nome[i], preco[i], quantidade[i]);
    }
    pequenaPausa();
}

//Função para editar um produto
void editarItem(int id[], char nome[][50], float preco[], int quantidade[], int total_de_produtos){
    int cod, encontrado = 0, input_valido, NId;

    limparTela();
    printf("===== OPCAO EDITAR PRODUTO =====\n");

    do {
        input_valido = 1;
        printf("Digite o ID do produto que deseja editar: ");
        if (scanf("%d", &cod) != 1){
            limparTela();
            printf("ERRO: DIGITE UM NUMERO INTEIRO POSITIVO!\n");
            limparBuffer();
            input_valido = 0;
        }
        limparBuffer();
    } while (!input_valido);

    limparTela();
    for(int i = 1; i <= 3; i++){
        printf("Buscando");
        for (int j = 0; j < i; j++){
            printf(".");
        }
        Sleep(650);
        limparTela();
    }
    
    for(int i = 0; i < total_de_produtos; i++){
        if(id[i] == cod){
            encontrado = 1;
            int op;
            
            limparTela();
            printf("===== OPCAO EDITAR PRODUTO =====\n");
            printf("\nProduto encontrado!\n");
            printf("ID: %d\n", id[i]);
            printf("Nome: %s\n", nome[i]);
            printf("Preco: %.2f\n", preco[i]);
            printf("Quantidade: %d\n", quantidade[i]);

            printf("\nO que deseja editar?\n");
            printf("1 - ID\n");
            printf("2 - Nome\n");
            printf("3 - Preco\n");
            printf("4 - Quantidade\n");
            printf("5 - Editar Tudo\n");
            printf("Opcao: ");
            scanf("%d", &op);
            limparBuffer();

            switch(op){
                case 1:
                    do {
                        limparTela();
                        printf("Novo ID: ");
                        if (scanf("%d", &NId) != 1 || NId < 0 || NId > 9999){
                            limparTela();
                            printf("ERRO: DIGITE UM NUMERO INTEIRO VALIDO!\n");
                            limparBuffer();
                            pequenaPausa();
                            input_valido = 0;
                        } else {
                            id[i] = NId;
                            printf("ID atualizado com sucesso!\n");
                            input_valido = 1;
                        }
                        limparBuffer();
                    } while (!input_valido);
                    pequenaPausa();
                    break;

                case 2:
                    limparTela();
                    printf("Novo nome: ");
                    scanf(" %[^\n]", nome[i]);
                    printf("Nome atualizado com sucesso!\n");
                    pequenaPausa();
                    break;

                case 3:
                    limparTela();
                    printf("Novo preco: ");
                    scanf("%f", &preco[i]);
                    limparBuffer();
                    printf("Preco atualizado com sucesso!\n");
                    pequenaPausa();
                    break;

                case 4:
                    limparTela();
                    printf("Nova quantidade: ");
                    scanf("%d", &quantidade[i]);
                    limparBuffer();
                    printf("Quantidade atualizada com sucesso!\n");
                    pequenaPausa();
                    break;

                case 5:
                    limparTela();
                    printf("Novo nome: ");
                    scanf(" %[^\n]", nome[i]);
                    limparBuffer();

                    do {
                        limparTela();
                        printf("Novo ID: ");
                        if (scanf("%d", &NId) != 1 || NId < 0 || NId > 9999){
                            limparTela();
                            printf("ERRO: DIGITE UM NUMERO INTEIRO VALIDO!\n");
                            pequenaPausa();
                            input_valido = 0;
                        } else {
                            id[i] = NId;
                            input_valido = 1;
                        }
                        limparBuffer();
                    } while (!input_valido);

                    limparTela();
                    printf("Novo preco: ");
                    scanf("%f", &preco[i]);
                    limparBuffer();

                    limparTela();
                    printf("Nova quantidade: ");
                    scanf("%d", &quantidade[i]);
                    limparBuffer();

                    limparTela();
                    printf("Todos os dados foram atualizados com sucesso!\n");
                    pequenaPausa();
                    break;

                default:
                    limparTela();
                    printf("Opcao invalida.\n");
                    pequenaPausa();
            }

            break;
        }
    }

    if(!encontrado){
        limparTela();
        printf("O PRODUTO NAO FOI ENCONTRADO.\n");
        pequenaPausa();
    }
}

//Função para buscar um produto e mostrar suas informações
void buscarItem(int id[], char nome[][50], float preco[], int quantidade[], int total_de_produtos){
    int codigo, input_valido;

    printf("===== OPCAO BUSCAR PRODUTO =====\n");
    do {
        input_valido = 1;

        printf("Informe o ID do produto: ");
    
        if (scanf("%d", &codigo) != 1){
            limparTela();
            printf("ERRO: DIGITE UM NUMERO INTEIRO POSITIVO!\n");
            limparBuffer();
            input_valido = 0;
            continue;
        }
        limparBuffer();
        
    } while (!input_valido);

    scanf("%d", &codigo);
    limparBuffer();

    limparTela();
    for(int i = 1; i <= 3; i++){
        printf("Buscando");
        for (int j = 0; j < i; j++){
            printf(".");
        }
        Sleep(650);
        limparTela();
    }

    for(int i = 0; i < total_de_produtos; i++){
        if(id[i] == codigo){
            printf("=====================================\n");
            printf("Produto encontrado:\n");
            printf("ID: %d\n", id[i]);
            printf("Nome: %s\n", nome[i]);
            printf("Preco: R$ %.2f\n", preco[i]);
            printf("Quantidade em estoque: %d\n", quantidade[i]);
            printf("=====================================\n");

            pequenaPausa();
            return;
        }
    }
    
    limparTela();
    printf("O PRODUTO NAO FOI ENCONTRADO.\n");
    pequenaPausa();
}

//Função para excluir um item
int excluirItem(int id[], char nome[][50], float preco[], int quantidade[], int total_de_produtos) {
    int cod, encontrado = 0, input_valido;

    if(total_de_produtos <= 0){
        limparTela();
        printf("Estoque vazio!\n");
        getchar();
        pequenaPausa();
        return total_de_produtos;
    }

    limparTela();
    printf("======= OPCAO EXCLUIR PRODUTO =======\n");
    
    do {
        input_valido = 1;

        printf("Digite o ID do produto: ");
    
        if (scanf("%d", &cod) != 1){
            limparTela();
            printf("ERRO: DIGITE UM NUMERO INTEIRO POSITIVO!\n");
            limparBuffer();
            input_valido = 0;
            continue;
        }
        limparBuffer();
        
    } while (!input_valido);

    limparTela();
    for(int i = 1; i <= 3; i++){
        printf("Buscando");
        for (int j = 0; j < i; j++){
            printf(".");
        }
        Sleep(650);
        limparTela();
    }

    for(int i = 0; i < total_de_produtos; i++){
        if(cod == id[i]){
            encontrado = 1;
            for(int j = i; j < total_de_produtos - 1; j++){
                id[j] = id[j + 1];
                preco[j] = preco[j + 1];
                quantidade[j] = quantidade[j + 1];
                strcpy(nome[j], nome[j + 1]);
            }
            limparTela();
            printf("ENCONTRADO!\n");
            printf("ID DO PRODUTO EXCLUIDO: %d\n", cod);
            total_de_produtos--;
            pequenaPausa();
            break;
        }
    }

    if(!encontrado){
        limparTela();
        printf("O PRODUTO NAO FOI ENCONTRADO.\n");
        pequenaPausa();
    }

    return total_de_produtos;
}