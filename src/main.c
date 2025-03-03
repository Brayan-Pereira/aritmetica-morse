#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINHA 100

int valor_morse(char *morse) {
    int valor = 0;
    for (int i = 0; morse[i] != '\0'; i++) {
        switch (morse[i]) {
            case '.': valor += 1; break;
            case '-': valor += 5; break;
            case ':': valor += 2; break;
            case '=': valor += 10; break;
            default: break;
        }
    }
    return valor;
}

int avaliar_expressao_morse(char *expressoes[], int N) {
    if (expressoes == NULL || N <=0) return -1; //Tratamento de erro para entrada inválida

    int resultado = valor_morse(expressoes[0]);
    for (int i = 1; i < 2 * N; i += 2) { // Corrigido o limite do loop
        char operador = expressoes[i][0];
        int num = valor_morse(expressoes[i + 1]);
        if (operador == '+') resultado += num;
        else if (operador == '*') resultado *= num;
        else return -1; //Tratamento de erro para operador inválido
    }
    return resultado;
}

int main() {
    FILE *entrada, *saida;
    char filename_entrada[] = "..\\input\\instance_1.txt";
    char filename_saida[] = "../output/instance_1.txt";
    char buffer[MAX_LINHA];
    int N, resultado, resultado_esperado;
    char *expressoes[MAX_LINHA]; // Aumentado o tamanho para evitar estouro de buffer


    // Abre o arquivo de entrada
    entrada = fopen(filename_entrada, "r");
    if (entrada == NULL) {
        perror("Erro ao abrir o arquivo de entrada");
        return 1;
    }

    // Abre o arquivo de saída
    saida = fopen(filename_saida, "r");
    if (saida == NULL) {
        perror("Erro ao abrir o arquivo de saída");
        fclose(entrada);
        return 1;
    }

    // Lê N (número de operadores)
    if (fgets(buffer, MAX_LINHA, entrada) == NULL) {
        perror("Erro ao ler N do arquivo de entrada");
        fclose(entrada);
        fclose(saida);
        return 1;
    }
    N = atoi(buffer);

    // Lê as expressões (sem loop for)
    for (int i = 0; i < 2 * N + 1; i++) {
        expressoes[i] = malloc(MAX_LINHA * sizeof(char));
        if (fgets(expressoes[i], MAX_LINHA, entrada) == NULL) {
            fprintf(stderr, "Erro ao ler a expressão %d.\n", i);
            fclose(entrada);
            fclose(saida);
            for (int j = 0; j < i; j++) free(expressoes[j]);
            return 1;
        }
        expressoes[i][strcspn(expressoes[i], "\n")] = 0;
    }

    // Avalia a expressão
    resultado = avaliar_expressao_morse(expressoes, N);
    if (resultado == -1) {
        fprintf(stderr, "Erro na avaliação da expressão.\n");
        fclose(entrada);
        fclose(saida);
        for (int i = 0; i < 2 * N + 1; i++) free(expressoes[i]);
        return 1;
    }

    // Lê o resultado esperado
    if (fgets(buffer, MAX_LINHA, saida) == NULL) {
        perror("Erro ao ler o resultado esperado");
        fclose(entrada);
        fclose(saida);
        for (int i = 0; i < 2 * N + 1; i++) free(expressoes[i]);
        return 1;
    }
    resultado_esperado = atoi(buffer);

    // Compara e imprime os resultados
    printf("Resultado calculado: %d\n", resultado);
    printf("Resultado esperado: %d\n", resultado_esperado);
    printf("%s\n", resultado == resultado_esperado ? "Correto!" : "Incorreto!");

    // Libera memória
    for (int i = 0; i < 2 * N + 1; i++) free(expressoes[i]);
    fclose(entrada);
    fclose(saida);
    return 0;
}
