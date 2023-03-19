#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct fila
{
	int *vetor;
	int tamanho;
} valores;

int aleatorio(int num)
{
	int random1;
	random1 = rand() & 255;
	random1 = (random1 << 8) | (rand() & 255);
	random1 = (random1 << 8) | (rand() & 255);
	random1 = (random1 << 7) | (rand() & 127);
	return random1 % num;
}

int comparador(valores *vetor)
{
	for (int i = 1; i <= vetor->tamanho; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (vetor->vetor[j] == vetor->vetor[i])
			{
				vetor->vetor[i] = aleatorio(999999);
			}
		}
	}
}

int main(void)
{
	printf("\nGerando arquivos...\n\n");
	char var[100];
	valores fila;
	for (fila.tamanho = 1000; fila.tamanho <= 100000; fila.tamanho *= 10)
	{
		printf("Carregando arquivos de tamanho %d...\n", fila.tamanho);
		for (int qtd = 1; qtd <= 5; qtd++)
		{

			fila.vetor = (int *)malloc(sizeof(int) * fila.tamanho);

			for (int i = 0; i < fila.tamanho; i++)
			{
				fila.vetor[i] = aleatorio(999999);
			}

			comparador(&fila);

			FILE *file;

			sprintf(var, "%d-arq%d.txt", fila.tamanho, qtd);
			file = fopen(var, "w");

			if (file == NULL)
			{
				printf("Erro ao abrir arquivo");

				exit(1);
			}

			for (int i = 0; i < fila.tamanho; i++)
			{
				fprintf(file, "%d\n", fila.vetor[i]);
			}

			fclose(file);
			free(fila.vetor);
		}
		printf("\n");
	}

	return 1;
}
