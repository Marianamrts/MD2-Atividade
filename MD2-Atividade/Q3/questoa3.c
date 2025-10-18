#include <stdio.h>
#include <math.h>

int main() {
    printf("=====================================================\n");
    printf(" Nome: Mariana Martins Silva\n");
    printf(" Matrícula: 222025932\n");
    printf("=====================================================\n\n");
    printf(" ---- Questao 03: A Razao de Eficiencia de um Numero ----\n\n");

    int N;
    
    // Solicita e valida o inteiro N no intervalo [1, 105].
    do {
        printf(" Digite um inteiro N (entre 1 e 105): ");
        scanf("%d", &N);
        if (N < 1 || N > 105) {
            printf("   ++ Erro: O numero deve estar entre 1 e 105. Tente novamente.\n");
        }
    } while (N < 1 || N > 105);

    // Trata o caso especial N = 1, que não possui fatores primos.
    if (N == 1) {
        printf("\n--- Analise para N = 1 ---\n");
        printf(" tau(1) = 1 (Apenas o divisor 1)\n");
        printf(" sigma(1) = 1 (Soma dos divisores = 1)\n");
        printf("\n--- Resultado Final ---\n");
        printf(" Razao de Eficiencia = sigma(1) / tau(1) = 1 / 1 = 1.00\n");
        return 0; 
    }

    // Adicionando a Justificativa do Método 
    printf("\n-----------------------------------------------------\n");
    printf(" Justificativa do Metodo:\n");
    printf(" As formulas para tau(N) e sigma(N) dependem\n");
    printf(" fundamentalmente da fatoracao prima de N. Portanto,\n");
    printf(" o primeiro passo e decompor N. Para N <= 105,\n");
    printf(" o metodo de Trial Division (divisao por tentativa)\n");
    printf(" e eficiente e suficiente.\n");
    printf("-----------------------------------------------------\n");

    // PASSO 1: FATORAÇÃO PRIMA
    printf("\n--- Passo 1: Fatoracao Prima de N = %d (Trial Division) ---\n", N);
    
    int fatores_primos[20]; // Array para os fatores primos unicos
    int expoentes[20];      // Array para os expoentes
    int num_fatores_unicos = 0;
    int temp_n = N;

    // Trata o fator 2
    int count = 0;
    while (temp_n % 2 == 0) {
        count++;
        temp_n /= 2;
    }
    if (count > 0) {
        fatores_primos[num_fatores_unicos] = 2;
        expoentes[num_fatores_unicos] = count;
        num_fatores_unicos++;
    }

    // Trata os fatores ímpares
    for (int i = 3; i * i <= temp_n; i += 2) {
        count = 0;
        while (temp_n % i == 0) {
            count++;
            temp_n /= i;
        }
        if (count > 0) {
            fatores_primos[num_fatores_unicos] = i;
            expoentes[num_fatores_unicos] = count;
            num_fatores_unicos++;
        }
    }

    // Se o que sobrou for um primo > 2
    if (temp_n > 2) {
        fatores_primos[num_fatores_unicos] = temp_n;
        expoentes[num_fatores_unicos] = 1;
        num_fatores_unicos++;
    }

    // Exibe a fatoração
    printf(" A fatoracao de %d e:\n", N);
    printf("   N = ");
    for (int i = 0; i < num_fatores_unicos; i++) {
        printf("%d^%d", fatores_primos[i], expoentes[i]);
        if (i < num_fatores_unicos - 1) {
            printf(" * ");
        }
    }
    printf("\n");

    // PASSO 2: CÁLCULO DE τ(N)
    printf("\n--- Passo 2: Calculo de tau(N) (Numero de Divisores) ---\n");
    long long tau = 1;
    printf("   tau(%d) = ", N);
    for (int i = 0; i < num_fatores_unicos; i++) {
        tau *= (expoentes[i] + 1);
        printf("(%d + 1)", expoentes[i]);
        if (i < num_fatores_unicos - 1) {
            printf(" * ");
        }
    }
    printf(" = %lld\n", tau);

    // PASSO 3: CÁLCULO DE σ(N)
    printf("\n--- Passo 3: Calculo de sigma(N) (Soma dos Divisores) ---\n");
    long long sigma = 1;
    
    //cálculo de cada termo individualmente
    long long termos_sigma[20]; // Para guardar os resultados parciais

    for (int i = 0; i < num_fatores_unicos; i++) {
        long long p = fatores_primos[i];
        int a = expoentes[i];
        // fórmula (p^(a+1) - 1) / (p - 1)
        termos_sigma[i] = (long long)(pow(p, a + 1) - 1) / (p - 1);
        sigma *= termos_sigma[i];
        printf("   Calculando termo para p=%lld, a=%d: ((%lld^%d - 1)/(%lld - 1)) = %lld\n", p, a, p, a + 1, p, termos_sigma[i]);
    }
    
    printf("\n   Multiplicando os termos calculados:\n");
    printf("   sigma(%d) = ", N);
    for (int i = 0; i < num_fatores_unicos; i++){
        printf("%lld", termos_sigma[i]);
        if (i < num_fatores_unicos - 1) {
            printf(" * ");
        }
    }
    printf(" = %lld\n", sigma);
    
    // PASSO 4: CÁLCULO DA RAZÃO DE EFICIÊNCIA
    printf("\n--- Passo 4: Calculo da Razao de Eficiencia ---\n");
    
    double razao = (double)sigma / tau;
    printf("   Razao = sigma(N) / tau(N)\n");
    printf("   Razao = %lld / %lld\n", sigma, tau);
    
    printf("\n--- Resultado Final ---\n");
    printf("   A Razao de Eficiencia de %d e: %.2lf\n", N, razao);
    
    return 0;
}