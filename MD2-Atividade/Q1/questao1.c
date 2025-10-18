#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Função para verificar se um número é primo (Trial Division)
int is_prime(long long int n) {
    if (n <= 1) return 0; // 0 e 1 não são primos
    if (n <= 3) return 1; // 2 e 3 são primos
    if (n % 2 == 0 || n % 3 == 0) return 0; // Divisíveis por 2 ou 3

    for (long long int i = 5; i * i <= n; i = i + 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return 0;
        }
    }
    return 1;
}

// Calcular (MDC) por Algoritmo de Euclides.
long long int mdc(long long int a, long long int b) {
    printf("  -> Calculando mdc(%lld, %lld) por Algoritmo de Euclides:\n", a, b);
    long long int temp;
    while (b != 0) {
        printf("      - a=%lld, b=%lld. Resto = %lld\n", a, b, a % b);
        temp = b;
        b = a % b;
        a = temp;
    }
    printf("  -> Resultado do mdc: %lld\n\n", a);
    return a;
}

// Algoritmo de Euclides Estendido para encontrar o inverso modular.
long long int mdc_extendido(long long int a, long long int b, long long int *x, long long int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    long long int x1;
    long long int y1;
    long long int mdc_val = mdc_extendido(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return mdc_val;
}

// Calcula o inverso modular de 'e' em relação a 'phi'.
long long int mod_inverso(long long int e, long long int phi) {
    printf("\n--- Calculo do Expoente Privado (d) ---\n");
    printf("  -> Usando o Algoritmo Estendido de Euclides para encontrar d em que (d * %lld) mod %lld = 1\n", e, phi);
    long long int x;
    long long int y;
    long long int g = mdc_extendido(e, phi, &x, &y);
    if (g != 1) {
        printf("  -> Erro: O inverso modular nao existe pois mdc(%lld, %lld) != 1.\n", e, phi);
        return -1;
    }
    long long int result = (x % phi + phi) % phi;
    printf("  -> O inverso modular de %lld (mod %lld) eh: %lld\n", e, phi, result);
    return result;
}

// Fatora um número n usando o método p de Pollard.
long long int p_rho(long long int n) {
    if (n % 2 == 0) return 2;

    printf("\n--- Fatoracao com Metodo p de Pollard para N = %lld ---\n", n);
    printf("Semente inicial: x = 2, y = 2\n");
    printf("Funcao de iteracao: g(x) = (x^2 + 1) mod %lld\n\n", n);

    long long int x = 2, y = 2, d = 1;
    int iteracao = 0;

    while (d == 1) {
        iteracao++;
        
        long long int x_anterior = x;
        
        x = (x * x + 1) % n;
        y = (y * y + 1) % n;
        y = (y * y + 1) % n;
        
        long long int diff = llabs(x - y);
        
        printf("Iteracao %d:\n", iteracao);
        printf("  x_%d = g(x_%d) = g(%lld) = %lld\n", iteracao, iteracao - 1, x_anterior, x);
        printf("  y_%d = g(g(y_%d)) = %lld\n", iteracao, iteracao - 1, y);
        printf("  |x - y| = |%lld - %lld| = %lld\n\n", x, y, diff);
        
        d = mdc(diff, n);

        if (d == n) {
            printf("\n  -> Falha: ciclo detectado. Tente outra semente.\n");
            return -1;
        }
    }
    
    printf("\n  -> Fator encontrado: %lld\n", d);
    printf("  -> Verificacao: %lld / %lld = %lld\n", n, d, n / d);
    return d;
}

// Calcula (base^exp) mod modulo com exponenciação 
long long int modular_expoente(long long int base, long long int exp, long long int mod) {
    long long int res = 1;
    printf("  -> Calculando (%lld^%lld) mod %lld (Exponenciacao Modular):\n\n", base, exp, mod);
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            printf("      - Expoente %lld e impar. res = (res * %lld) mod %lld", exp, base, mod);
            res = (res * base) % mod;
            printf(" = %lld\n", res);
        }
        if (exp > 1) {
            exp >>= 1;
            printf("      - Expoente agora e %lld. base = (%lld * %lld) mod %lld", exp, base, base, mod);
            base = (base * base) % mod;
            printf(" = %lld\n", base);
        } else {
            exp = 0;
        }
    }
    printf("  -> Resultado final da exponenciacao: %lld\n", res);
    return res;
}

// Converte texto em números.
void pre_codificacao(const char* msg, long long int *blocos, int* n_blocos) {
    *n_blocos = 0;
    for (int i = 0; msg[i] != '\0'; ++i) {
        char c = toupper(msg[i]);
        if (c >= 'A' && c <= 'Z') {
            blocos[*n_blocos] = c - 'A' + 11;
            (*n_blocos)++;
        } else if (c == ' ') {
            blocos[*n_blocos] = 0;
            (*n_blocos)++;
        }
    }
}

// Converte números em texto.
void pos_decodificacao(const long long int *blocos, int n_blocos, char* msg) {
    int msg_len = 0;
    for (int i = 0; i < n_blocos; ++i) {
        if (blocos[i] >= 11 && blocos[i] <= 36) {
            msg[msg_len++] = (char)(blocos[i] - 11 + 'A');
        } else if (blocos[i] == 0) {
            msg[msg_len++] = ' ';
        }
    }
    msg[msg_len] = '\0';
}

int main() {
    printf("-----------------------------------------------------------------\n");
    printf(" Nome: Mariana Martins Silva\n");
    printf(" Matrícula: 222025932 \n");
    printf("-----------------------------------------------------------------\n\n");
    printf(" ==== ATIVIDADE DE MD2: SISTEMA RSA COM FATORAÇÃO DE POLLARD ====\n\n\n");
    
    //ETAPA 1: Fatoração Interativa
    long long int N1, N2;
    do {
        printf("Digite o primeiro numero composto N1 (3 ou 4 digitos, entre 100 e 9999): ");
        scanf("%lld", &N1);
        printf("Digite o segundo numero composto N2 (3 ou 4 digitos e diferente de N1): ");
        scanf("%lld", &N2);

        if (N1 < 100 || N1 > 9999 || N2 < 100 || N2 > 9999) {
            printf("\n ++ Erro: Ambos os numeros devem estar entre 100 e 9999. Tente novamente.\n\n");
        } else if (N1 == N2) {
            printf("\n ++ Erro: Os numeros devem ser distintos. Tente novamente.\n\n");
        }
    } while (N1 < 100 || N1 > 9999 || N2 < 100 || N2 > 9999 || N1 == N2);

    long long int p = p_rho(N1);
    if (p == -1) return 1;

    long long int q = p_rho(N2);
    if (q == -1) return 1;

    printf("\n--- Definicao dos primos RSA ---\n");
    printf("p (fator de N1=%lld) = %lld\n", N1, p);
    printf("q (fator de N2=%lld) = %lld\n", N2, q);
    
    //ETAPA 2: Geração das Chaves RSA
    printf("\n=================================================================\n");
    printf("                         ETAPA 2: Geracao das Chaves RSA\n");
    printf("=================================================================\n");
    
    long long int n = p * q;
    long long int z_n = (p - 1) * (q - 1);
    
    printf("\n--- Calculo do modulo n ---\n");
    printf("n = p * q = %lld * %lld = %lld\n", p, q, n);
    printf("\n--- Calculo do Totiente de Euler z(n) ---\n");
    printf("z(n) = (p-1)*(q-1) = %lld * %lld = %lld\n", p - 1, q - 1, z_n);

    long long int e;
    printf("\n--- Escolha do Expoente Publico (e) ---\n");
    printf("  -> Procurando o menor e > 1 tal que mdc(e, %lld) = 1\n", z_n);
    for (e = 3; e < z_n; e += 2) {
        long long int a = e, b = z_n, temp;
        while (b != 0) { temp = b; b = a % b; a = temp; }
        if (a == 1) {
            printf("  -> 'e' encontrado: %lld\n", e);
            break;
        }
    }
    
    long long int d = mod_inverso(e, z_n);
    if (d == -1) return 1;

    printf("\n--- Impressao das Chaves ---\n");
    printf("Chave Publica: (n, e) = (%lld, %lld)\n", n, e);
    printf("Chave Privada: (n, d) = (%lld, %lld)\n", n, d);

    //ETAPA 3: Criptografia e Descriptografia
    printf("\n=================================================================\n");
    printf("        ETAPA 3: Criptografia e Descriptografia da Mensagem\n");
    printf("=================================================================\n");

    char mensagem_original[256];
    printf("\nDigite a mensagem a ser criptografada: ");
    while (getchar() != '\n');
    fgets(mensagem_original, sizeof(mensagem_original), stdin);
    mensagem_original[strcspn(mensagem_original, "\n")] = 0;

    char mensagem_original_maiuscula[256];
    strcpy(mensagem_original_maiuscula, mensagem_original);
    for(int i = 0; mensagem_original_maiuscula[i]; i++){
      mensagem_original_maiuscula[i] = toupper(mensagem_original_maiuscula[i]);
    }

    long long int blocos_numericos[256];
    int n_blocos;
    pre_codificacao(mensagem_original, blocos_numericos, &n_blocos);

    printf("\n--- Pre-codificacao da Mensagem ---\n");
    printf("Mensagem original: '%s'\n", mensagem_original);
    printf("Mensagem em blocos numericos (M):\n");
    for (int i = 0; i < n_blocos; i++) printf("%02lld ", blocos_numericos[i]);
    printf("\n");

    long long int blocos_cifrados[256];
    printf("\n--- Codificacao (C = M^e mod n) ---\n");
    for (int i = 0; i < n_blocos; i++) {
        long long int M = blocos_numericos[i];
        printf("\nCriptografando bloco M = %lld:\n", M);
        
        printf("-> Resolucao da exponenciacao modular:\n");
        
        if (is_prime(n)) {
            printf("   - Teorema Aplicado: Pequeno Teorema de Fermat. Como o modulo n (%lld) e primo, o expoente %lld pode ser reduzido para %lld mod %lld = %lld.\n", n, e, e, n - 1, e % (n - 1));
        } else {
            long long int mdc_check = mdc(M, n);
            if (mdc_check == 1) {
                printf("   - Teorema Aplicado: Teorema de Euler. Como mdc(%lld, %lld) = 1, o expoente %lld pode ser reduzido para %lld mod %lld = %lld.\n", M, n, e, e, z_n, e % z_n);
            } else {
                printf("   - Teorema Aplicado: Divisao Euclidiana. Como mdc(%lld, %lld) != 1, o Teorema de Euler nao se aplica. O calculo usa as propriedades gerais da aritmetica modular.\n", M, n);
            }
        }

        blocos_cifrados[i] = modular_expoente(M, e, n);
        printf("-> Bloco criptografado C = %lld\n", blocos_cifrados[i]);
    }

    printf("\nMensagem cifrada completa (C):\n");
    for (int i = 0; i < n_blocos; i++) printf("%lld ", blocos_cifrados[i]);
    printf("\n");
    
    long long int blocos_decifrados[256];
    printf("\n--- Decodificacao (M = C^d mod n) ---\n");
    for (int i = 0; i < n_blocos; i++) {
        long long int C = blocos_cifrados[i];
        printf("\nDescriptografando bloco C = %lld:\n", C);
        
        printf("-> Resolucao da exponenciacao modular:\n\n");
        printf("   - Teorema Aplicado: Teorema de Euler. A base matematica do RSA garante que C^d = M (mod n), onde o expoente %lld e reduzido por z(n)=%lld.\n", d, z_n);

        blocos_decifrados[i] = modular_expoente(C, d, n);
        printf("-> Bloco descriptografado M' = %lld\n", blocos_decifrados[i]);
    }
    
    printf("\nMensagem descriptografada em blocos numericos (M'):\n");
    for (int i = 0; i < n_blocos; i++) printf("%02lld ", blocos_decifrados[i]);
    printf("\n");

    char mensagem_final[256];
    pos_decodificacao(blocos_decifrados, n_blocos, mensagem_final);
    
    printf("\n--- Pos-decodificacao e Verificacao ---\n");
    printf("Mensagem final: '%s'\n", mensagem_final);
    
    if (strcmp(mensagem_original_maiuscula, mensagem_final) == 0) {
        printf("\n ++++ A mensagem decifrada é idêntica a mensagem original.\n");
    } else {
        printf("\n[ERRO] A mensagem decifrada e diferente da mensagem original.\n");
    }

    return 0;
}