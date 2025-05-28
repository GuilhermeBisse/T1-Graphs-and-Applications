#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_VERTICES 100
#define valor_infinito 99999999

typedef struct Aresta {
    int destino;
    int peso;
    struct Aresta* prox;
} Aresta;

typedef struct Vertice {
    Aresta* lista_adj;
} Vertice;

typedef struct Grafo {
    int num_vertices;
    int num_arestas;
    int digrafo;   
    int ponderado;   
    Vertice* vertices;
} Grafo;

Grafo* criar_grafo(int num_vertices, int digrafo, int ponderado) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->num_vertices = num_vertices;
    grafo->num_arestas = 0;
    grafo->digrafo = digrafo;
    grafo->ponderado = ponderado;
    grafo->vertices = (Vertice*)malloc(num_vertices * sizeof(Vertice));
    
    for (int i = 0; i < num_vertices; i++) {
        grafo->vertices[i].lista_adj = NULL;
    }
    
    return grafo;
}

void adicionar_aresta(Grafo* grafo, int origem, int destino, int peso){
    Aresta* nova = (Aresta*)malloc(sizeof(Aresta));
    nova->destino = destino;
    nova->peso = peso;
    nova->prox = grafo->vertices[origem].lista_adj;
    grafo->vertices[origem].lista_adj = nova;

    if (grafo->digrafo == 0) {
        Aresta* nova_reversa = (Aresta*)malloc(sizeof(Aresta));
        nova_reversa->destino = origem;
        nova_reversa->peso = peso;
        nova_reversa->prox = grafo->vertices[destino].lista_adj;
        grafo->vertices[destino].lista_adj = nova_reversa;
    }
}

Grafo* ler_grafo_arquivo(char* nome_arquivo){
    FILE* arq = fopen(nome_arquivo, "r");
    if(!arq){
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    int num_vertices, num_arestas, ponderado;
    char tipo;
    fscanf(arq, "%d %d %c %d", &num_vertices, &num_arestas, &tipo, &ponderado);
    int digrafo = (tipo=='G') ? 0 : 1;
    Grafo* grafo_arq = criar_grafo(num_vertices, digrafo, ponderado);

    int origem, destino, peso;
    for (int i=0; i<num_arestas; i++){
        if(ponderado == 0){
            fscanf(arq, "%d %d", &origem, &destino);
            peso = 1;
    }
        else{
            fscanf(arq, "%d %d %d", &origem, &destino, &peso);
        }
        adicionar_aresta(grafo_arq, origem, destino, peso);
    }

    fclose(arq);
    return grafo_arq;
}

void imprimir_grafo(Grafo* g){
    for (int i = 0; i < g->num_vertices; i++) {
        printf("V%d: ", i);
        Aresta* atual = g->vertices[i].lista_adj;
        while (atual != NULL) {
            printf("-> %d", atual->destino);
            if (g->ponderado) {
                printf("(%d)", atual->peso);
            }
            atual = atual->prox;
        }
        printf("\n");
    }
}

void criar_e_salvar_grafo_em_txt (char* nome_arquivo){
    int num_vertices, num_arestas, ponderado;
    char tipo;
    printf("Digite o número de vértices: ");
    scanf("%d", &num_vertices);
    printf("Digite o número de arestas: ");
    scanf("%d", &num_arestas);
    printf("Digite o tipo de grafo (G para não direcionado, D para direcionado): ");
    scanf(" %c", &tipo);
    tipo = toupper(tipo);
    printf("O grafo é ponderado? (1 para sim, 0 para não): ");
    scanf("%d", &ponderado);

    FILE* arq = fopen(nome_arquivo, "w");
    if(!arq){
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    fprintf(arq, "%d %d %c %d\n", num_vertices, num_arestas, tipo, ponderado);

    for (int i=0; i<num_arestas; i++){
        int origem, destino, peso;
        printf("Digite a origem, destino e peso da aresta %d: ", i+1);
        if(ponderado == 0){
            scanf("%d %d", &origem, &destino);
            peso = 1;
        }
        else{
            scanf("%d %d %d", &origem, &destino, &peso);
        }
        fprintf(arq, "%d %d %d\n", origem, destino, peso);

    }

    fclose(arq);
    printf("Grafo salvo com sucesso em %s\n", nome_arquivo);
}

void criar_e_imprimir_matriz_de_adjacencia(Grafo* g){
    int matriz[MAX_VERTICES][MAX_VERTICES];

    for(int i=0; i<g->num_vertices; i++){
        for(int j=0; j<g->num_vertices; j++){
            matriz[i][j] = 0;
        }
    }
    for(int i=0; i<g->num_vertices; i++){
        Aresta* atual = g->vertices[i].lista_adj;
        while(atual != NULL){
            if(g->ponderado){
                matriz[i][atual->destino] = atual->peso;
                if(g->digrafo == 0){
                    matriz[atual->destino][i] = atual->peso;
                }
            }
            else{
                matriz[i][atual->destino] = 1;
                if(g->digrafo == 0){
                    matriz[atual->destino][i] = 1;
                }
            }
            
            atual = atual->prox;
        }
    }

    printf("Matriz de Adjacência:\n");
    for(int i=0; i<g->num_vertices; i++){
        for(int j=0; j<g->num_vertices; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}


void calcular_grau_vertices(Grafo* g){
    for(int i=0; i<g->num_vertices; i++){
        int grau = 0;
        Aresta* atual = g->vertices[i].lista_adj;
        while(atual != NULL){
            grau++;
            atual = atual->prox;
        }
        printf("Grau do vértice %d: %d\n", i, grau);
    }
}

void prim (Grafo* g){
    if (g->digrafo == 1 || g->ponderado == 0){
        printf("O algoritmo de Prim só pode ser aplicado a grafos não direcionados e ponderados.\n");
        return;
    }

    int num_vertices = g->num_vertices;
    int visitados[num_vertices];
    int chave[num_vertices];
    int arvore[num_vertices];

    for (int i = 0; i < num_vertices; i++) {
        visitados[i] = 0;
        chave[i] = valor_infinito;
        arvore[i] = -1;
    }

    chave[0] = 0;

    for (int i=0; i<num_vertices-1; i++){
        int menor_vertice = -1;
        int min = valor_infinito;

        for(int v=0; v<num_vertices; v++){
            if (visitados[v] == 0 && chave[v] < min){
                min = chave[v];
                menor_vertice = v;
            }
        }

        if (menor_vertice == -1){
            printf("O grafo não é conexo.\n");
            return;
        }
        visitados[menor_vertice] = 1;

        Aresta* atual = g->vertices[menor_vertice].lista_adj;

        while(atual!=NULL){
            int destino = atual->destino;
            if (visitados[destino] == 0 && atual->peso < chave[destino]){
                arvore[destino] = menor_vertice;
                chave[destino] = atual->peso;
            }
            atual = atual->prox;
        }
    }

    printf("\nÁrvore Geradora Mínima (Prim):\n");
    int peso_total = 0;
    for (int i = 1; i < num_vertices; i++) {
        if (arvore[i] != -1) {
            printf("%d - %d (peso: %d)\n", arvore[i], i, chave[i]);
            peso_total += chave[i];
        }
    }
    printf("Peso total da AGM: %d\n", peso_total);
}

void dijkstra (Grafo* g, int origem){
    if (g->ponderado == 0){
        printf("O algoritmo de Dijkstra só pode ser aplicado a grafos ponderados.\n");
        return;
    }

    int distancia[g->num_vertices];
    int visitados[g->num_vertices];
    int anterior[g->num_vertices];

    for (int i=0; i<g->num_vertices; i++){
        distancia[i] = valor_infinito;
        visitados[i] = 0;
        anterior[i] = -1;
    }
    distancia[origem] = 0;

    for(int i=0; i<g->num_vertices;i++){
        int menor_vertice = -1;
        int min = valor_infinito;

        for(int v=0; v<g->num_vertices; v++){
            if (visitados[v] == 0 && distancia[v] < min){
                min = distancia[v];
                menor_vertice = v;
            }
        }

        if (menor_vertice == -1){
            break;
        }
        visitados[menor_vertice] = 1;

        Aresta* atual = g->vertices[menor_vertice].lista_adj;

        while(atual!=NULL){
            int destino = atual->destino;
            int peso = atual->peso;

            if(visitados[destino] == 0 && distancia[menor_vertice] + peso < distancia[destino]){
                distancia[destino] = distancia[menor_vertice] + peso;
                anterior[destino] = menor_vertice;
            }
            atual = atual->prox;
        }
    }

    printf("\nMenores distâncias a partir do vértice %d:\n", origem);
    for (int i=0; i<g->num_vertices; i++){
        if (distancia[i] == valor_infinito){
            printf("V%d: Infinito\n", i);
        }
        else{
            printf("V%d: %d\n", i, distancia[i]);
        }
        if (anterior[i] != -1){
            printf("Caminho: ");
            int j = i;
            while (j != -1){
                printf("%d ", j);
                j = anterior[j];
            }
            printf("\n");
        }
    }
}

void bfs(Grafo* g, int origem){
    int fila[MAX_VERTICES];
    int visitados[g->num_vertices];
    int ordem_visita[MAX_VERTICES];

    for (int i=0; i<g->num_vertices; i++){
        visitados[i] = 0;
        ordem_visita[i] = -1;
    }

    visitados[origem] = 1;
    int inicio = 0; int fim = 0;
    fila[inicio] = origem;
    ordem_visita[fim] = origem;
    fim++;
    while (inicio<fim){
        int vertice_atual = fila[inicio];
        inicio++;
        Aresta* atual = g->vertices[vertice_atual].lista_adj;
        while(atual != NULL){
            int destino = atual->destino;
            if (visitados[destino] == 0){
                visitados[destino] = 1;
                fila[fim] = destino;
                ordem_visita[fim] = destino;
                fim++;
            }
            atual = atual->prox;
        }
    }
    printf("Ordem de visita (BFS): ");
    for (int i=0; i<g->num_vertices; i++){
        if (ordem_visita[i] != -1){
            printf("%d ", ordem_visita[i]);
        }
    }
    printf("\n");
}

void dfs_recursivo (Grafo* g, int vertice, int visitados[], int ordem_visita[], int* contador){
    visitados[vertice] = 1;
    ordem_visita[(*contador)++] = vertice;
    
    Aresta* atual = g->vertices[vertice].lista_adj;
    while (atual != NULL){
        if (visitados[atual->destino] == 0){
            dfs_recursivo(g, atual->destino, visitados, ordem_visita, contador);
        }
        atual = atual->prox;
    }
}

void dfs (Grafo* g, int origem){
    int visitados[g->num_vertices];
    int ordem_visita[g->num_vertices];
    int contador = 0;

    for (int i=0; i<g->num_vertices; i++){
        visitados[i] = 0;
        ordem_visita[i] = -1;
    }

    dfs_recursivo(g, origem, visitados, ordem_visita, &contador);
    printf("Ordem de visita (DFS): ");
    for (int i=0; i<contador; i++){
        if (ordem_visita[i] != -1){
            printf("%d ", ordem_visita[i]);
        }
    }
    printf("\n");
}

void liberar_grafo(Grafo* g){
    for (int i=0; i<g->num_vertices; i++){
        Aresta* atual = g->vertices[i].lista_adj;
        while(atual != NULL){
            Aresta* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->vertices);
    free(g);
}

int main(){

    printf("CRIAR GRAFO À PARTIR DE ARQUIVO:\n");
    Grafo* g = ler_grafo_arquivo("grafo_extremo.txt");
    imprimir_grafo(g);

    printf("MATRIZ DE ADJACÊNCIA DO GRAFO CRIADO\n");
    criar_e_imprimir_matriz_de_adjacencia(g);

    printf("GRAU DOS VÉRTICES DO GRAFO CRIADO:\n");
    calcular_grau_vertices(g);

    printf("ÁRVORE GERADORA MÍNIMA (PRIM):\n");
    prim(g);

    printf("DIJKSTRA:");
    dijkstra(g, 0);

    printf("BFS:\n");
    bfs(g, 0);

    printf("DFS:\n");
    dfs(g, 0);

    liberar_grafo(g);

    printf("CRIAR E SALVAR GRAFO NO ARQUIVO, A PARTIR DO USUÁRIO:\n");
    criar_e_salvar_grafo_em_txt("novo_grafo.txt");
    printf("\nLENDO O NOVO GRAFO CRIADO:\n");
    Grafo* novo = ler_grafo_arquivo("novo_grafo.txt");
    imprimir_grafo(novo);
    liberar_grafo(novo);

    

    return 0;
}