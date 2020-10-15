//
// Created by paiva on 12/10/2020.
//

#ifndef LABIRINTORECURSIVO_PILHAENCADEADA_H
#define LABIRINTORECURSIVO_PILHAENCADEADA_H

#include "Pilha.h"

class No {
private:
    No* anterior;
    int *valor;
public:
    No(No* anterior, const int* valor);
    No* getAnterior() const;
    int* getValor() const;
};

class PilhaEncadeada : public Pilha {
private:
    No* topo;
public:
    PilhaEncadeada();
    void limpar() override;
    void empilha(int* dado) override;
    int* desempilha() override;
    bool isVazia() const override;
    bool isCheia() const override;
    bool igualUltimo(int* dado) const override;
};

#endif //LABIRINTORECURSIVO_PILHAENCADEADA_H
