#include <stdio.h>

#define MAXCOMPANHIAS 100
#define MAXAIRPORTNAME 4
#define MAXNOME 50
#define MAXCODE 7
#define MAXVOOS 50

typedef struct Voo{
  char destino[MAXAIRPORTNAME];
  int partida;
  int chegada;
} Voo;

typedef struct Companhia{
  char nome[MAXNOME];
  char codigo[MAXCODE];
  int n_voos;
  Voo voos[MAXVOOS];
} Companhia;

Companhia info[MAXCOMPANHIAS];
int n_companhias = 0;

void nova_companhia(char linha[]) { 

  sscanf(linha,"%49s %6s", info[n_companhias].nome, info[n_companhias].codigo);
  info[n_companhias].n_voos = 0;
  n_companhias++;
}

void adiciona_voo(char linha[]) {
  Voo v;
  char compania[MAXNOME];
  int companianumber=0,i;

  sscanf(linha,"%49s %3s %d %d", compania ,v.destino, &v.partida, &v.chegada); /*Escreve no ultimo voo de dada compania*/
  
  for(i = 0;i < n_companhias; i++) {
    if()
  }

  int n_voos_companhia = info[companianumber-1].n_voos;
  info[n_companhias-1].voos[n_voos_companhia] = v; 

  info[info[n_companhias-1].n_voos].n_voos++; 
}


void adiciona_voo_lastcompania(char linha[]) { /*Versão anterior*/
  Voo v;
  int n_voos_companhia = info[n_companhias-1].n_voos;

  sscanf(linha,"%3s %d %d", v.destino, &v.partida, &v.chegada);
  info[n_companhias-1].voos[n_voos_companhia] = v; 

  info[info[n_companhias-1].n_voos].n_voos++; 
}