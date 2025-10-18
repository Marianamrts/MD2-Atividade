#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

// Funcao para calcular o MDC 
int mdcComPassos(int a, int b) { 
    int resto;
    while (b != 0) { // Linha 10 (adicionada)
        resto = a % b;
        printf("Algoritmo de Euclides: %d mod %d = %d\n", a, b, resto);
        a = b;
        b = resto; // Linha 14 (adicionada)
    }
    return a;
}
int inversoModular(int a, int m) {
    int m0 = m; // Linha 23 (adicionada)
    int t, q;
    int x0 = 0, x1 = 1;
    int A = a, B = m;

    if (m == 1) return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0) {
        x1 += m0; // Linha 36 (adicionada)
    }
    printf("\nSubstituindo, temos que o inverso de %d em %d e %d.\n\n", A, B, x1);
    return x1;
}
int PowMod(int base, int exp, int mod) {
    long long res = 1;
    long long b = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) { // Linha 45 (adicionada)
            res = (res * b) % mod;
            b = (b * b) % mod; 
            exp >>= 1;     
    }
    return (int)res;
    }
}
int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    int H, G, Zn, x, n1;

    printf("Insira H: ");
    scanf("%d", &H);
    printf("Insira G: ");
    scanf("%d", &G);
    printf("Insira Zn: ");
    scanf("%d", &Zn);
    printf("Insira x: ");
    scanf("%d", &x); 
    printf("Insira n1: ");
    scanf("%d", &n1);
    printf("\n");

    int inverso = inversoModular(G, Zn); // Linha 72 (adicionada)
    int a = (H * inverso) % Zn;

    printf("Fazendo a multiplicacao modular: %d * %d mod %d = %d\n", H, inverso, Zn, a);
    printf("Sendo %d o inverso de %d.\n", inverso, G); 

    int resultado = PowMod(a, x, n1); // Linha 78 (adicionada)
    printf("Valor final da congruencia: %d^%d mod %d = %d\n", a, x, n1, resultado); 

    return 0;
}

//RESPOSTAS DAS QUESTÕES ABERTAS: 
// 1) Com o código completo e preenchido corretamente, qual seria a saída com os valores: H: 7,
// G: 3, Zn: 11,  x: 10, n1: 13?
// Subistituindo, temos que o inverso de 3 em 11 é 4
// Fazendo a multiplicação modular: 7 * 4 mod 11 = 6
// Sendo 4 o inverso de 3
// .: Valor final da Congruência: 6^10 mod 13 = 4

// 2) 1) verdadeiro
//    2) falso
//    3) verdadeiro
//    4) verdadeiro
//    5) falso
//    6) verdadeiro
//    7) verdadeiro