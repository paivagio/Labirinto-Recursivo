//
// Created by paiva on 12/10/2020.
//

#ifndef LABIRINTORECURSIVO_PILHA_H
#define LABIRINTORECURSIVO_PILHA_H

class Pilha {
public:
    virtual void limpar() = 0;
    virtual void empilha(int* dado) = 0;
    virtual int* desempilha() = 0;
    virtual bool isVazia() const = 0;
    virtual bool isCheia() const = 0;
    virtual bool igualUltimo(int* dado) const = 0;
    virtual ~Pilha() {}

};

#endif //LABIRINTORECURSIVO_PILHA_H
