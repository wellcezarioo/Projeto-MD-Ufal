#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

// Função para calcular n = p * q
void calcular_n(mpz_t p, mpz_t q, mpz_t n) {
    mpz_mul(n, p, q);
}

// Função para calcular d = e⁻¹ mod φ(n)
void calcular_d(mpz_t e, mpz_t p, mpz_t q, mpz_t d) {
    mpz_t phi, p1, q1;
    mpz_inits(phi, p1, q1, NULL);

    mpz_sub_ui(p1, p, 1);
    mpz_sub_ui(q1, q, 1);
    mpz_mul(phi, p1, q1);

    if (mpz_invert(d, e, phi) == 0) {
        fprintf(stderr, "Erro: e não tem inverso módulo φ(n)\n");
        mpz_set_ui(d, 0);
    }

    mpz_clears(phi, p1, q1, NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s p q e\n", argv[0]);
        return 1;
    }

    mpz_t p, q, e, n, d;
    mpz_inits(p, q, e, n, d, NULL);

    mpz_set_str(p, argv[1], 10);
    mpz_set_str(q, argv[2], 10);
    mpz_set_str(e, argv[3], 10);

    calcular_n(p, q, n);
    calcular_d(e, p, q, d);

    // Imprime n e d separados por espaço
    gmp_printf("n: %Zd d: %Zd\n", n, d);

    mpz_clears(p, q, e, n, d, NULL);
    return 0;
}
