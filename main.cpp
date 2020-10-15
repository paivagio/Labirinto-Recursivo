#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "Pilha.h"
#include "PilhaArray.h"
#include "PilhaEncadeada.h"
using namespace std;

void printMenuPilhas();
void printMenuCasas();
char** openMaze(const string& filename, int* h, int* w);
void achaEntrada(char** lab, int x, int y, int* xE, int* yE);
bool checaVizinhos(int choose, char** lab, Pilha& path, Pilha& wrong, int i, int j);
char** marcaCaminho(char** lab, Pilha& path, Pilha& wrong);
void printLabirinto(char** lab, int x, int y);
void print50lines();


int main() {
    cout << "\n\n--------- LABIRINTO ---------" << "\n\n";
    //// Abre o arquivo do labirinto e instancia uma matriz equivalente.
    int x=0, y=0;
    char** labirinto = openMaze("Labirinto.txt", &x, &y);

    //// Permite a escolha entre PilhaArray e PilhaEncadeada
    int wichPilha = 0;
    printMenuPilhas();
    cin >> wichPilha;
    cout << "\n";

    if(wichPilha == 0)
        exit(0);


    //// Permite a escolha da ordem de visita das casas.
    int wichOrder = 0;
    printMenuCasas();
    cin >> wichOrder;
    cout << "\n";

    if(wichOrder == 0)
        exit(0);

    /// Clear da tela
    print50lines();

    //// Acha as coordenadas da entrada do labirinto.
    int xE=0, yE=0;
    achaEntrada(labirinto, x, y, &xE, &yE);


    //// Inicializa a pilha dependendo da escolha anterior.
    Pilha* caminho = nullptr;
    Pilha* visitados= nullptr;

    if(wichPilha == 1) {
        caminho = new PilhaArray(30);
        visitados = new PilhaArray(3);
    }
    else {
        caminho = new PilhaEncadeada;
        visitados = new PilhaEncadeada;
    }


    //// Acha a saída do labirinto e registra o tempo levado.
    auto start = std::chrono::steady_clock::now();
    bool result = checaVizinhos(wichOrder, labirinto, *caminho, *visitados, xE, yE);
    auto end = std::chrono::steady_clock::now();



    //// Printa o resultado
    cout << "Especificações: " << "\n";
    if(wichPilha == 1)
        cout << "- Pilha: Array" << "\n";
    else
        cout << "- Pilha: Encadeada" << "\n";

    if(wichOrder == 1)
        cout << "- Sentido: Horário" << "\n\n";
    else
        cout << "- Sentido: Anti-Horário" << "\n\n";

    /// Marca e printa o labirinto
    labirinto = marcaCaminho(labirinto, *caminho, *visitados);
    printLabirinto(labirinto, x, y);

    if(!result)
        cout << "\nSaída encontrada!" << "\n";

    else
        cout << "\nLabirinto sem saida." << "\n";

    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "\nTempo levado: " << elapsed_seconds.count()/1000 << " ms\n";

    return 0;
}


void printMenuPilhas(){
    cout << "\n\n--------- TIPO DE PILHA ---------" << "\n";
    cout << "1 - PilhaArray" << "\n";
    cout << "2 - PilhaEncadeada" << "\n";
    cout << "0 - Sair " << "\n";
    cout << "---------------------------------" << "\n";
    cout << "Escolha uma opção: ";
}

void printMenuCasas(){
    cout << "--------- ORDEM DE VISITA ---------" << "\n";
    cout << "1 - Sentido horário" << "\n";
    cout << "2 - Sentido anti-horário" << "\n";
    cout << "0 - Sair " << "\n";
    cout << "-----------------------------------" << "\n";
    cout << "Escolha uma opção: ";
}

char** openMaze(const string& filename, int* h, int* w){
    string line;
    int i = 0, j = 0;
    char** labirinto;
    ifstream myfile (filename);

    //Pega o tamanho do labirinto
    if (myfile.is_open()){
        while ( getline (myfile,line) ){
            j = line.length();
            for(char letter : line)
                cout << letter;
            cout<<"\n";
            i++;
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    *h = i;
    *w = j;
    labirinto = new char*[i];
    int x=0;

    //Cria o labirinto
    ifstream myfile2 (filename);
    if (myfile2.is_open())
    {
        while ( getline (myfile2,line) ){
            labirinto[x] = new char[j];
            for(int y=0; y<line.length(); y++)
                labirinto[x][y] = line[y];
            x++;
        }
        myfile2.close();
    }
    else cout << "Unable to open file";

    return labirinto;
}

void achaEntrada(char** lab, int x, int y, int* xE, int* yE){
    for (int i=0; i<x; i++){
        for (int j=0; j<y; j++){
            if (lab[i][j] == 'E'){
                *xE = i;
                *yE = j;
            }
        }
    }
}

bool checaVizinhos(int choose, char** lab, Pilha& path, Pilha& wrong, int i, int j){
    bool end = true;

    if(choose == 1){ //// Sentido horario

        //// Procura a saída
        if (lab[i - 1][j] == 'S')
            end = false;

        if (lab[i][j + 1] == 'S')
            end = false;

        if (lab[i + 1][j] == 'S')
            end = false;

        if (lab[i][j - 1] == 'S')
            end = false;


        //// Procura um caminho para continuar
        int array1[2] = {i-1, j};

        if (lab[i - 1][j] == ' ' && end && !path.igualUltimo(array1) ){
            path.empilha(array1);
            end = checaVizinhos(choose, lab, path, wrong, (i-1), j);
        }

        int array2[2] = {i, j+1};
        if (lab[i][j + 1] == ' ' && end && !path.igualUltimo(array2) ){
            path.empilha(array2);
            end = checaVizinhos(choose, lab, path, wrong, i, (j+1));
        }

        int array3[2] = {i+1, j};
        if (lab[i + 1][j] == ' ' && end && !path.igualUltimo(array3) ){
            path.empilha(array3);
            end = checaVizinhos(choose, lab, path, wrong, (i+1), j);
        }

        int array4[2] = {i, j-1};
        if (lab[i][j - 1] == ' ' && end && !path.igualUltimo(array4) ){
            path.empilha(array4);
            end = checaVizinhos(choose, lab, path, wrong, i, (j-1));
        }

    }

    else if(choose == 2){ //// Sentido anti-horario

        //// Procura a saída
        if (lab[i - 1][j] == 'S')
            end = false;

        if (lab[i][j - 1] == 'S')
            end = false;

        if (lab[i + 1][j] == 'S')
            end = false;

        if (lab[i][j + 1] ==  'S')
            end = false;


        //// Procura um caminho para continuar
        int array1[2] = {i-1, j};
        if (lab[i - 1][j] == ' ' && end && !path.igualUltimo(array1) ){
            path.empilha(array1);
            end = checaVizinhos(choose, lab, path, wrong, (i-1), j);
        }

        int array2[2] = {i, j-1};
        if (lab[i][j - 1] == ' ' && end && !path.igualUltimo(array2)){
            path.empilha(array2);
            end = checaVizinhos(choose, lab, path, wrong, i, (j-1));
        }

        int array3[2] = {i+1, j};
        if (lab[i + 1][j] == ' ' && end && !path.igualUltimo(array3)){
            path.empilha(array3);
            end = checaVizinhos(choose, lab, path, wrong, (i+1), j);
        }

        int array4[2] = {i, j+1};
        if (lab[i][j + 1] == ' ' && end && !path.igualUltimo(array4)){
            path.empilha(array4);
            end = checaVizinhos(choose, lab, path, wrong, i, (j+1));
        }
    }


    if(end){
        if(!path.isVazia()) {
            int array[2] = {i, j};
            wrong.empilha(array);
            path.desempilha();
        }
        return true;
    }
    else{
        return false;
    }
}

char** marcaCaminho(char** lab, Pilha& path, Pilha& wrong){
    if(!path.isVazia()) {
        int *aux = path.desempilha();
        while (!path.isVazia()) {
            lab[aux[0]][aux[1]] = '.';
            aux = path.desempilha();
        }
    }

    if(!wrong.isVazia()) {
        int *aux2 = wrong.desempilha();
        while (!wrong.isVazia()) {
            lab[aux2[0]][aux2[1]] = '-';
            aux2 = wrong.desempilha();
        }
    }
    return lab;
}

void printLabirinto(char** lab, int x, int y){
    for (int i=0; i<x; i++){
        for (int j=0; j<y; j++)
            cout << lab[i][j];
        cout << "\n";
    }
}

void print50lines(){
    for(int i=0; i<50; i++){
        cout << "\n";
    }
}
