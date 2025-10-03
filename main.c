#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>


typedef struct grafo{
    int numno;
    int **arestas;
} grafo;

grafo *criar_grafo(int numnos){
    grafo *g = malloc(sizeof(*g));
    if(g == NULL){
        return NULL;
    }

    g->numno = numnos;

    g->arestas = calloc(sizeof(int*), g->numno);
    if(g->arestas == NULL){
        free(g);
        return NULL;
    }

    for(int i=0; i < g->numno; i++){
        g->arestas[i] = calloc(sizeof(int),g->numno);
        if(g->arestas[i] == NULL){
            destruir_grafo(g);
            return NULL;
        }
    }

    return g;
}

void destruir_grafo(grafo* g){
    if(g->arestas == NULL){
        return;
    }

    for (int i=0; i < g->numno; i++){
        if(g->arestas[i] != NULL){
            free(g->arestas[i]);
        }
    }

    free(g->arestas);
    free(g);
}

void printar_grafo(grafo *g){
    printf("grafo \n");

    for (int de=0; de < g->numno; de++){
        for(int para=0; para < g->numno; para++){
            if(g->arestas[de][para]){
                printf("%c -> %c : %d\n", de, para, g->arestas[de][para]);
            }
        }
    }
    printf("\n");
}

int tem_aresta(grafo *g, unsigned int de_no, unsigned int para_no){
    assert(g!=NULL);
    assert(de_no < g->numno);
    assert(para_no < g->numno);

    return g->arestas[de_no][para_no];
}

bool adicionar_aresta(grafo *g, unsigned int de_no, unsigned int para_no, int dist){
    assert(g!=NULL);
    assert(de_no < g->numno);
    assert(para_no < g->numno);

    if(tem_aresta(g, de_no, para_no)){
        return 0;
    }

    g->arestas[de_no][para_no] = dist;
    g->arestas[para_no][de_no] = dist;
    return true;
}

void greedy_algorithm(grafo *g, int ini, int fim){
    int estimativa[2][7] = { { 65,66,67,68,69,70,71 },
                             { 16,13,15,7 ,10,10,0  } },visitado[7]={0},aux=72 , caminho[7]={0}, cont=0;

    // adiciona o no de inicio no vetor de caminho
    caminho[cont]=ini;

    while(ini!=fim){
        for(int i=0; i < 7; i++){
            //verifica se tem uma aresta e qual dela tem a menor estimativa
            if(estimativa[1][i]<aux && g->arestas[ini][i+65]){
                //verifica se aresta ja foi visirada
                if(visitado[i]!=1){
                    //seleciona proximo no
                    aux=estimativa[0][i];
                }
            }
        }
        //marca no como visitado
        visitado[ini-65]=1;
        //recebe o proximo no
        ini=aux;
        //adiciona proximo no ao vetor de caminho
        cont++;
        caminho[cont]=ini;
    }

    printf("\nO caminho ate %c eh : \n",fim);
    for(int i=0; i < 7; i++){
        if(caminho[i]!=0){
            printf("%c ", caminho[i]);
        }
    }
}

int main()
{
    grafo *g1 = criar_grafo(72);


    /*codigo ansi usado para representar as letras
    A=65 , B=66, C=67, etc.*/

    adicionar_aresta(g1, 65, 66, 8);
    adicionar_aresta(g1, 65, 67, 3);
    adicionar_aresta(g1, 65, 68, 16);
    adicionar_aresta(g1, 66, 68, 8);
    adicionar_aresta(g1, 66, 69, 7);
    adicionar_aresta(g1, 67, 68, 14);
    adicionar_aresta(g1, 67, 70, 6);
    adicionar_aresta(g1, 68, 69, 5);
    adicionar_aresta(g1, 68, 71, 10);
    adicionar_aresta(g1, 68, 70, 6);
    adicionar_aresta(g1, 69, 71, 15);
    adicionar_aresta(g1, 70, 71, 17);


    greedy_algorithm(g1,65,71);

    destruir_grafo(g1);

}
