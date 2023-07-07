#include <stdio.h>
#include <stdlib.h>

struct arv {
  int info;
  struct arv* esq;
  struct arv* dir;
};

typedef struct arv Arv;

Arv* busca (Arv* r, int v)
{
  if (r == NULL) return NULL;
  else if (r->info > v) return busca(r->esq,v);
  else if (r->info < v) return busca(r->dir,v);
  else return r;
}


Arv* insere (Arv* a, int v)
{
  if (a==NULL) {
    a = (Arv*)malloc(sizeof(Arv));
    a->info = v;
    a->esq = a->dir = NULL;
  }
  else if (v < a->info)
    a->esq = insere(a->esq,v);
  else /* v < a->info */
    a->dir = insere(a->dir,v);
  return a;
}


Arv* libera (Arv* a){
  if (!vazia(a)){
    libera(a->esq); /* libera sae */
    libera(a->dir); /* libera sad */
    free(a); /* libera raiz */
  }
  return NULL;
}


void imprime_in (Arv* r)
{
  if(r == NULL) return;
  imprime_in(r->esq);
  printf("%d ", r->info);
  imprime_in(r->dir);
}

void main(void)
{
  Arv *raiz = NULL;

  int nos[] = {1, 2, 3, 5, 15, 7};
  int i = 0;

  for(i = 0; i< 6; i++){
    raiz = insere(raiz, nos[i]);
  }
  imprime_in(raiz);


  for(i = 0; i< 6; i++){
    raiz = insere(raiz, nos[i]);
  }

  if(busca(raiz, 2) == NULL){
    printf("Valor 2 nao encontrado");
  }else{
     printf("Valor 2 encontrado");
  }

  if(busca(raiz, 8) == NULL){
    printf("Valor 8 nao encontrado");
  }else{
     printf("Valor 8 encontrado");
  }

}
