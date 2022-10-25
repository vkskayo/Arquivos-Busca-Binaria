#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct _Endereco Endereco;
struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2]; // Ao Espaço no final da linha + quebra de linha
};

int main(int argc, char **argv) {



  FILE *f;
	Endereco e;
	int qt;

  if(argc != 2)
	{
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}

  f = fopen("cep_ordenado.dat","r");
  fseek(f, 0, SEEK_END);
  int tamarq = ftell(f);
  int numOfReg = tamarq / sizeof(Endereco);
  int achei = 0;
  int inicio = 0;
  int fim = numOfReg - 1;
  int meio = 0;
  int numOfIters = 0;


  while(fim >= inicio && !achei){
    numOfIters++;
    meio = (inicio + fim) / 2;
    fseek(f,meio*sizeof(Endereco),SEEK_SET);
    qt = fread(&e, sizeof(Endereco), 1, f);
    if(strncmp(argv[1],e.cep,8)==0){
      achei = 1;
    }else if(strcmp(argv[1],e.cep) < 0){
      fim = meio - 1;
    }else {
      inicio = meio + 1;
    }
  }

  if(achei){
    printf("Encontrei\n");
    printf("Iteracoes: %d\n", numOfIters);
  }else{
    printf(" N Encontrei\n");
  }
  
  return 0;
}