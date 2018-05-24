#ifndef GUITARRAS_H
#define GUITARRAS_H

typedef struct guitarra guitarra, *ptrGuitarra;

//Constantes estrutura guitarra
#define DISPONIVEL 0
#define ALUGADA 1
#define DANIFICADA 2

struct guitarra{
  int id;
  char nome[100];
  int precoAluguerDia;
  int valor;
  int estado;
};

void preencheGuitarra(ptrGuitarra guitarra, int total);
ptrGuitarra adicionaGuitarra(ptrGuitarra guitarras, int *total);
void listarGuitarras(ptrGuitarra guitarras, int total);
void listarGuitarrasDisponiveis(ptrGuitarra guitarras, int total);
void listarGuitarrasAlugadas(ptrGuitarra guitarras, int total);
int verificaGuitarrasDisponiveis(ptrGuitarra listaGuitarras, int total);
int devolveIndexGuitarra(ptrGuitarra listaGuitarras, int total, int id);

#endif
