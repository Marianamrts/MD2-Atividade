#include <stdio.h>
#include <stdbool.h>


//Cálculo do Máximo Divisor Comum (MDC) utilizando o Algoritmo de Euclides.

int mdc(int a, int b) {
    int original_a = a;
    int original_b = b;
    
    printf("      -> Iniciando calculo de MDC(%d, %d) via Algoritmo de Euclides:\n", a, b);
    
    int temp;
    while (b != 0) {
        //Divisão Euclidiana (a = q*b + r)
        printf("         - Divisao: %d = %d * %d + %d. O proximo 'a' sera %d e o 'b' sera %d.\n", a, (a/b), b, (a%b), b, (a%b));
        temp = b;
        b = a % b;
        a = temp;
    }
    
    printf("      -> Conclusao: O resto foi 0. O MDC e o ultimo resto nao-nulo: %d\n", a);
    return a;
}

//Cálculo do Mínimo Múltiplo Comum (MMC).

int mmc(int a, int b) {
    printf("   - Calculando MMC entre o resultado parcial (%d) e o proximo ciclo (%d).\n", a, b);
    
    // As restrições do problema garantem a > 0 e b > 0.
    int mdc_resultado = mdc(a, b);
    int mmc_resultado = (a / mdc_resultado) * b; 
    
    printf("   - MMC(%d, %d) calculado usando a formula (a*b)/mdc: (%d * %d) / %d = %d\n\n", a, b, a, b, mdc_resultado, mmc_resultado);
    return mmc_resultado;
}

int main() {
    
    printf("=====================================================\n");
    printf(" Nome: Mariana Martins Silva\n");
    printf(" Matrícula: 222025932\n");
    printf("=====================================================\n\n");
    printf(" ---- QUESTAO 2: CHAVES PERIÓDICAS ---- \n\n");

    int n_chaves;
    int ciclos[10];
    bool limite_excedido = false; 
    
    printf("-----------------------------------------------------\n");
    printf(" PASSO 1: Entrada de Dados\n");
    printf("-----------------------------------------------------\n");

    do {
        printf(" Digite o numero de chaves (entre 1 e 10): ");
        scanf("%d", &n_chaves);
        if (n_chaves < 1 || n_chaves > 10) {
            printf("  ++ Erro: Valor invalido. O numero de chaves deve ser entre 1 e 10.\n");
        }
    } while (n_chaves < 1 || n_chaves > 10);

    printf("\n Digite os %d ciclos de ativacao (cada um entre 2 e 20):\n", n_chaves);
    for (int i = 0; i < n_chaves; i++) {
        do {
            printf(" Ciclo da chave #%d: ", i + 1);
            scanf("%d", &ciclos[i]);
            if (ciclos[i] < 2 || ciclos[i] > 20) {
                printf("  ++ Erro: Valor invalido. O ciclo deve ser entre 2 e 20.\n");
            }
        } while (ciclos[i] < 2 || ciclos[i] > 20);
    }
    
    printf("\n-----------------------------------------------------\n");
    printf(" PASSO 2: Calculo do MMC Progressivo\n");
    printf("-----------------------------------------------------\n");
    printf(" JUSTIFICATIVA: O calculo sera feito em cadeia, pois o MMC tem a propriedade\n");
    printf(" associativa: mmc(a, b, c) = mmc(mmc(a, b), c).\n\n");

    int mmc_resultado = ciclos[0];
    printf(" - O valor inicial para o calculo do MMC e o ciclo da primeira chave: %d\n\n", mmc_resultado);

    // O laço abaixo combina as técnicas de MDC e MMC para encontrar o resultado final.
    for (int i = 1; i < n_chaves; i++) {
        mmc_resultado = mmc(mmc_resultado, ciclos[i]);
        
        if (mmc_resultado > 50) {
            printf(" *** ATENCAO: O resultado parcial (%d) ja excedeu o limite de 50 anos. ***\n", mmc_resultado);
            printf(" *** Interrompendo calculos desnecessarios. ***\n\n");
            limite_excedido = true;
            break; // Sai do laço 'for'
        }
    }
    
    printf("-----------------------------------------------------\n");
    printf(" PASSO 3: Analise e Conclusao Final\n");
    printf("-----------------------------------------------------\n");
    
    //Tratamento explícito do caso N=1
    if (n_chaves == 1) {
        mmc_resultado = ciclos[0]; // Garante que o valor está correto
        printf(" Analise para uma unica chave:\n");
        printf(" O primeiro ano de ativacao (apos o ano 0) e o seu proprio ciclo: %d\n", mmc_resultado);
    } else {
        printf(" O Minimo Multiplo Comum (MMC) final de todos os ciclos e: %d\n", mmc_resultado);
    }
    
    if (mmc_resultado > 0 && mmc_resultado <= 50) {
        printf("\n >> RESULTADO: O primeiro ano em que todas as chaves serao ativadas simultaneamente e: %d\n", mmc_resultado);
    } else {
        printf("\n >> RESULTADO: Impossibilidade. Nao existe um ano de sincronizacao dentro do limite de 1 a 50 anos.\n");
    }
    printf("-----------------------------------------------------\n");

    return 0;
}