#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Struct que representa cada item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Vetor de itens (lista sequencial)
Item mochila[MAX_ITENS];
int totalItens = 0;

// Funções
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();

int main() {
    int opcao;

    do {
        printf("\n===== INVENTÁRIO DE SOBREVIVÊNCIA =====\n");
        printf("1 - Cadastrar item\n");
        printf("2 - Remover item\n");
        printf("3 - Buscar item\n");
        printf("4 - Listar itens\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        switch(opcao) {
            case 1:
                inserirItem();
                listarItens();
                break;
            case 2:
                removerItem();
                listarItens();
                break;
            case 3:
                buscarItem();
                break;
            case 4:
                listarItens();
                break;
            case 0:
                printf("\nSaindo do inventário...\n");
                break;
            default:
                printf("\nOpção inválida!\n");
        }

    } while(opcao != 0);

    return 0;
}

// Cadastrar novo item na mochila
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\n⚠️ Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("\nDigite o nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // remover quebra de linha

    printf("Digite o tipo do item (arma, munição, cura, ferramenta...): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[totalItens] = novo;
    totalItens++;

    printf("\n✔️ Item adicionado com sucesso!\n");
}

// Remover item pelo nome
void removerItem() {
    char nomeRemover[30];
    int encontrado = 0;

    printf("\nDigite o nome do item que deseja remover: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = 1;
            // Desloca os itens posteriores uma posição para trás
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalItens--;
            printf("\n🗑️ Item removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("\n⚠️ Item não encontrado na mochila.\n");
    }
}

// Busca sequencial pelo nome
void buscarItem() {
    char nomeBusca[30];
    int encontrado = 0;

    printf("\nDigite o nome do item para busca: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = 1;
            printf("\n🔍 Item encontrado:\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            break;
        }
    }

    if (!encontrado) {
        printf("\n❌ Item não encontrado.\n");
    }
}

// Mostrar todos os itens cadastrados
void listarItens() {
    printf("\n===== ITENS NA MOCHILA =====\n");

    if (totalItens == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    for (int i = 0; i < totalItens; i++) {
        printf("%d) Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}
