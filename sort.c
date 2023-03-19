#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct fila
{
	int *vetor;
	int tamanho;
} valores;

typedef struct resultadoFinal
{
	double mediaTr[3], mediaT[3], clocks[5], trocas[5];
} calculator;

double InsertionSort(valores *vetor)
{
	int clone;

	double troca = 0;
	for (int i = 1; i < vetor->tamanho; i++)
	{
		int j = i - 1;
		clone = vetor->vetor[i];
		while ((j >= 0) && (clone < vetor->vetor[j]))
		{
			vetor->vetor[j + 1] = vetor->vetor[j];
			j--;
			troca++;
		}
		vetor->vetor[j + 1] = clone;
	}
	return troca;
}

double BubbleSort(valores *vetor)
{
	int clone;
	double troca = 0;
	for (int i = 0; i < vetor->tamanho; i++)
	{
		for (int j = 0; j < vetor->tamanho - 1; j++)
		{
			if (vetor->vetor[j] > vetor->vetor[j + 1])
			{
				clone = vetor->vetor[j];
				vetor->vetor[j] = vetor->vetor[j + 1];
				vetor->vetor[j + 1] = clone;
				troca++;
			}
		}
	}
	return troca;
}

double SelectionSort(valores *vetor)
{
	int clone;
	double troca = 0;
	for (int i = 0; i < vetor->tamanho - 1; i++)
	{
		int j = i;
		while (j < vetor->tamanho)
		{
			if (vetor->vetor[i] >= vetor->vetor[j])
			{
				clone = vetor->vetor[i];
				vetor->vetor[i] = vetor->vetor[j];
				vetor->vetor[j] = clone;
				troca++;
			}
			j++;
		}
	}
	return troca;
}

double ShellSort(valores *vetor)
{
	int i = (vetor->tamanho - 1) / 2;
	int chave, clone;
	double troca = 0;

	while (i != 0)
	{
		do
		{
			chave = 1;
			for (int k = 0; k < vetor->tamanho - i; ++k)
			{
				if (vetor->vetor[k] > vetor->vetor[k + i])
				{
					clone = vetor->vetor[k];
					vetor->vetor[k] = vetor->vetor[k + i];
					vetor->vetor[k + i] = clone;
					chave = 0;
					troca++;
				}
			}
		} while (chave == 0);
		i = i / 2;
	}
	return troca;
}

double media(double vetor[5])
{

	double resultado = 0, soma = 0;
	for (int m = 0; m < 5; m++)
	{
		soma += vetor[m];
	}
	resultado = soma / 5;
	return resultado;
}

int main(void)
{

	clock_t tempo;
	calculator sort[4];
	FILE *file, *result;

	char nome[100];

	result = fopen("resultados", "w"); // limpando txt resultados
	fclose(result);
	result = fopen("resultados", "a");

	printf("(Pode demorar um pouco)\n");

	for (int x = 0, tm = 1000; tm <= 100000; tm *= 10, x++)
	{

		printf("Ordenando arquivos com %d componentes\n", tm);

		int qtd = 0;
		while (qtd < 5)
		{

			sprintf(nome, "%d-arq%d.txt", tm, qtd + 1);
			file = fopen(nome, "r");
			if (file == NULL)
			{
				printf("\nERRO! Algum arquivo não encontrado.\n\n");
				exit(1);
			}

			for (int q = 0; q < 4; q++)
			{

				valores fila;
				fila.tamanho = tm;
				fila.vetor = (int *)malloc(sizeof(int) * fila.tamanho);

				int i = 0;
				while (!feof(file))
				{
					fscanf(file, "%d", &fila.vetor[i]);
					i++;
				}
				if (q == 0)
				{
					tempo = clock();
					sort[q].trocas[qtd] = InsertionSort(&fila);
					tempo = clock() - tempo;
					sort[q].clocks[qtd] = ((double)tempo) / CLOCKS_PER_SEC;
				}
				if (q == 1)
				{
					tempo = clock();
					sort[q].trocas[qtd] = BubbleSort(&fila);
					tempo = clock() - tempo;
					sort[q].clocks[qtd] = ((double)tempo) / CLOCKS_PER_SEC;
				}
				if (q == 2)
				{
					tempo = clock();
					sort[q].trocas[qtd] = SelectionSort(&fila);
					tempo = clock() - tempo;
					sort[q].clocks[qtd] = ((double)tempo) / CLOCKS_PER_SEC;
				}
				if (q == 3)
				{
					tempo = clock();
					sort[q].trocas[qtd] = ShellSort(&fila);
					tempo = clock() - tempo;
					sort[q].clocks[qtd] = ((double)tempo) / CLOCKS_PER_SEC;
				}
				free(fila.vetor);
			}

			qtd++;
			fclose(file);
			printf(". ");
		}

		printf("\n\n");

		for (int z = 0; z < 4; z++)
		{
			sort[z].mediaTr[x] = media(sort[z].trocas);
			sort[z].mediaT[x] = media(sort[z].clocks);
		}
	}

	for (int p = 1000, o = 0; p <= 100000; p *= 10, o++)
	{
		fprintf(result, "\nArquivos com %d elementos:\n\n", p);

		fprintf(result, "Insertion Sort:\n\t\tMédia trocas: %.2lf\n\t\tMédia tempo: %.2lf \n", sort[0].mediaTr[o], sort[0].mediaT[o]);
		fprintf(result, "Bubble Sort:\n\t\tMédia trocas: %.2lf\n\t\tMédia tempo: %.2lf \n", sort[1].mediaTr[o], sort[1].mediaT[o]);
		fprintf(result, "Selection Sort:\n\t\tMédia trocas: %.2lf\n\t\tMédia tempo: %.2lf \n", sort[2].mediaTr[o], sort[2].mediaT[o]);
		fprintf(result, "Shell Sort:\n\t\tMédia trocas: %.2lf\n\t\tMédia tempo: %.2lf \n\n", sort[3].mediaTr[o], sort[3].mediaT[o]);
	}
	fclose(result);
	return 1;
}
