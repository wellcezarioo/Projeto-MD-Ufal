#!/bin/bash

# Caminhos fixos para subpastas
PASTA_CHAVES="./chaves"
PASTA_RESPOSTAS="./respostas"

# Verifica se o programa está compilado
if [ ! -f ./rsa ]; then
    echo "Erro: Programa rsa não encontrado. Compile com gcc -o rsa rsa.c -lgmp"
    exit 1
fi

# Verifica se a pasta de chaves existe
if [ ! -d "$PASTA_CHAVES" ]; then
    echo "Erro: Pasta 'chaves/' não encontrada."
    exit 1
fi

# Cria a pasta de respostas se não existir
mkdir -p "$PASTA_RESPOSTAS"

# Processa cada arquivo chave_*.txt na pasta 'chaves'
for arquivo in $PASTA_CHAVES/chave*.txt; do
    nome_arquivo=$(basename "$arquivo")
    indice="${nome_arquivo#chave_}"
    indice="${indice%.txt}"

    # Lê p, q e e
    read -r p q e < "$arquivo"

    # Gera saída em respostas/resposta_<indice>.txt
    ./rsa "$p" "$q" "$e" > "$PASTA_RESPOSTAS/resposta${indice}.txt"
    echo "Gerado: respostas/resposta${indice}.txt"
done
