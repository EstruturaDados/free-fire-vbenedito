#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// ---------- STRUCTS ----------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ---------- VARIÁVEIS GLOBAIS ----------
Item mochilaVetor[MAX_ITENS];
int totalVetor = 0;

No* mochilaLista = NULL;

int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// ---------- ASSINATURA DAS FUNÇÕES ----------
void menuPrincipal();
void menuVetor();
void menuLista();

// ---- Funções do Vetor ----
void inserirItemVetor();
void removerItemVetor();
void listarVetor();
void ordenarVetor();
void buscarSequencialVetor();
void buscarBinariaVetor();

// ---- Funções da Lista Encadeada ----
void inserirItemLista();
void removerItemLista();
void listarLista();
void buscarSequencialLista();

int main() {
    menuPrincipal();
    return 0;
}

// =============== MENU PRINCIPAL ===============
void menuPrincipal() {
    int opcao;

    do {
        printf("\n===== MODO SOBREVIVÊNCIA — INVENTÁRIO =====\n");
        printf("1 - Usar mochila com Vetor\n");
        printf("2 - Usar mochila com Lista Encadeada\n");
        printf("0 - Sair do jogo\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1: menuVetor(); break;
            case 2: menuLista(); break;
            case 0: printf("\nSaindo...\n"); break;
            default: printf("\nOpção inválida!\n");
        }

    } while(opcao != 0);
}

// ====================== MENU DO VETOR ======================
void menuVetor() {
    int opcao;
    do {
        printf("\n===== MOCHILA (VETOR) =====\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Ordenar itens por nome\n");
        printf("5 - Busca sequencial\n");
        printf("6 - Busca binária\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1: inserirItemVetor(); break;
            case 2: removerItemVetor(); break;
            case 3: listarVetor(); break;
            case 4: ordenarVetor(); break;
            case 5: buscarSequencialVetor(); break;
            case 6: buscarBinariaVetor(); break;
            case 0: break;
            default: printf("\nOpção inválida!\n");
        }
    } while(opcao != 0);
}

// ====================== FUNÇÕES DO VETOR ======================
void inserirItemVetor() {
    if (totalVetor >= MAX_ITENS) {
        printf("\nMochila cheia!\n");
        return;
    }

    Item novo;
    printf("\nNome: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochilaVetor[totalVetor++] = novo;
    printf("\n✔ Item inserido!\n");
}

void removerItemVetor() {
    if (totalVetor == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    char nomeRemover[30];
    printf("\nNome do item para remover: ");
    fgets(nomeRemover, 30, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    for (int i = 0; i < totalVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nomeRemover) == 0) {
            for (int j = i; j < totalVetor - 1; j++)
                mochilaVetor[j] = mochilaVetor[j + 1];
            totalVetor--;
            printf("\n🗑 Item removido!\n");
            return;
        }
    }
    printf("\nItem não encontrado.\n");
}

void listarVetor() {
    printf("\n===== ITENS NA MOCHILA (Vetores) =====\n");
    if (totalVetor == 0) {
        printf("Mochila vazia.\n");
        return;
    }
    for (int i = 0; i < totalVetor; i++)
        printf("%d) Nome: %s | Tipo: %s | Qtd: %d\n", i+1, mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
}

void ordenarVetor() {
    Item temp;
    for (int i = 0; i < totalVetor - 1; i++)
        for (int j = i + 1; j < totalVetor; j++)
            if (strcmp(mochilaVetor[i].nome, mochilaVetor[j].nome) > 0) {
                temp = mochilaVetor[i];
                mochilaVetor[i] = mochilaVetor[j];
                mochilaVetor[j] = temp;
            }
    printf("\n📌 Itens ordenados por nome!\n");
}

void buscarSequencialVetor() {
    char nomeBusca[30];
    comparacoesSequencial = 0;

    printf("\nNome do item para busca: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < totalVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
            printf("\n🔍 Item encontrado! Comparações: %d\n", comparacoesSequencial);
            printf("Nome: %s | Tipo: %s | Qtd: %d\n",
                   mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
            return;
        }
    }
    printf("\n❌ Não encontrado — Comparações: %d\n", comparacoesSequencial);
}

void buscarBinariaVetor() {
    char nomeBusca[30];
    int inicio = 0, fim = totalVetor - 1;
    comparacoesBinaria = 0;

    printf("\nNome do item para busca binária: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinaria++;

        int cmp = strcmp(nomeBusca, mochilaVetor[meio].nome);

        if (cmp == 0) {
            printf("\n🔍 Item encontrado! Comparações: %d\n", comparacoesBinaria);
            printf("Nome: %s | Tipo: %s | Qtd: %d\n",
                   mochilaVetor[meio].nome, mochilaVetor[meio].tipo, mochilaVetor[meio].quantidade);
            return;
        }
        if (cmp > 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    printf("\n❌ Não encontrado — Comparações: %d\n", comparacoesBinaria);
}

// ====================== MENU DA LISTA ENCADEADA ======================
void menuLista() {
    int opcao;
    do {
        printf("\n===== MOCHILA (LISTA ENCADEADA) =====\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar por nome\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1: inserirItemLista(); break;
            case 2: removerItemLista(); break;
            case 3: listarLista(); break;
            case 4: buscarSequencialLista(); break;
            case 0: break;
            default: printf("\nOpção inválida!\n");
        }
    } while(opcao != 0);
}

// ====================== FUNÇÕES DA LISTA ENCADEADA ======================
void inserirItemLista() {
    No* novo = (No*)malloc(sizeof(No));

    printf("\nNome: ");
    fgets(novo->dados.nome, 30, stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(novo->dados.tipo, 20, stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    getchar();

    novo->proximo = mochilaLista;
    mochilaLista = novo;

    printf("\n✔ Item inserido!\n");
}

void removerItemLista() {
    if (!mochilaLista) {
        printf("\nMochila vazia!\n");
        return;
    }

    char nomeRemover[30];
    printf("\nNome do item para remover: ");
    fgets(nomeRemover, 30, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    No *atual = mochilaLista, *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nomeRemover) == 0) {
            if (anterior == NULL) mochilaLista = atual->proximo;
            else anterior->proximo = atual->proximo;

            free(atual);
            printf("\n🗑 Item removido!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("\nItem não encontrado!\n");
}

void listarLista() {
    printf("\n===== ITENS NA MOCHILA (Lista Encadeada) =====\n");
    if (!mochilaLista) {
        printf("Mochila vazia.\n");
        return;
    }

    No* atual = mochilaLista;
    int i = 1;
    while (atual) {
        printf("%d) Nome: %s | Tipo: %s | Qtd: %d\n",
               i++, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

void buscarSequencialLista() {
    char nomeBusca[30];
    comparacoesSequencial = 0;

    printf("\nNome do item para busca: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    No* atual = mochilaLista;
    while (atual) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            printf("\n🔍 Item encontrado! Comparações: %d\n", comparacoesSequencial);
            printf("Nome: %s | Tipo: %s | Qtd: %d\n",
                   atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            return;
        }
        atual = atual->proximo;
    }
    printf("\n❌ Não encontrado — Comparações: %d\n", comparacoesSequencial);
}
