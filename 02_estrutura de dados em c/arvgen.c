#include <stdio.h>
#include <stdlib.h>

struct arvgen {
  int info;
  struct arvgen *prim;
  struct arvgen *prox;
};
typedef struct arvgen ArvGen;


ArvGen* cria (int info)
{
  ArvGen *a =(ArvGen *)malloc(sizeof(ArvGen));
  a->info = info;
  a->prim = NULL;
  a->prox = NULL;
  return a;
}

void insere (ArvGen* a, ArvGen* f)
{
  f->prox = a->prim;
  a->prim = f;
}

void libera (ArvGen* a)
{
  ArvGen* p = a->prim;
  while (p!=NULL) {
    ArvGen* t = p->prox;
    libera(p);
    p = t;
  }
  free(a);
}

void imprime (ArvGen* a)
{
  ArvGen* p;
  printf("%d\n",a->info);
  for (p=a->prim; p!=NULL; p=p->prox)
    imprime(p);
}

int busca (ArvGen* a, char c)
{
  ArvGen* p;
  if (a->info==c)
    return 1;
  else {
    for (p=a->prim; p!=NULL; p=p->prox) {
      if (busca(p,c))
        return 1;
    }
  }
  return 0;
}

int main()
{
	ArvGen* quarenta_tres       = cria (43);
  ArvGen* vinte_dois          = cria (22);
  ArvGen* vinte_um            = cria (21);
  ArvGen* cinquenta_oito      = cria (58);
  ArvGen* quarenta_cinco      = cria (45);
  ArvGen* sessenta_seis       = cria (66);
  ArvGen* trinta_um           = cria (31);
  ArvGen* setenta_um          = cria (71);
  ArvGen* cinquenta_nove      = cria (59);
  ArvGen* doze                = cria (12);
  ArvGen* trinta_cinco        = cria (35);

  insere(vinte_dois,      sessenta_seis);
  insere(vinte_dois,      trinta_um);
  insere(quarenta_tres,   vinte_dois);
  insere(quarenta_tres,   vinte_um);
  insere(cinquenta_oito,  setenta_um);
  insere(cinquenta_oito,  cinquenta_nove);
  insere(cinquenta_oito,  doze);
  insere(quarenta_tres,   cinquenta_oito);
  insere(quarenta_cinco,  trinta_cinco);
  insere(quarenta_tres,   quarenta_cinco);

  imprime(quarenta_tres);

  if(busca(quarenta_tres, 12)){
    printf("Numero 12 encontrado");
  }else{
    printf("Numero 12 nao encontrado");
  }

  if(busca(quarenta_tres, 88)){
    printf("Numero 88 encontrado");
  }else{
    printf("Numero 88 nao encontrado");
  }

}
