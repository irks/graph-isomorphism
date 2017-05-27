
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


class Isomorphism {
private:
    int vNum1 = 0, vNum2 = 0;
    int eNum1 = 0, eNum2 = 0;

    int *degV1, *degV2;

    bool **graph1 = nullptr;
    bool **graph2 = nullptr;
    int *permArray = nullptr;

public:
    void exit();
    void createPermutationArray();
    bool openFiles(int argc, char **argv);
    bool verifyPermutation();
    void printfPermutation();
    bool nextPermutation();
    bool notEqualVertexOrEdgeNum();
    bool checkDegV();
};


void Isomorphism::exit() {
    delete [] permArray;
    delete [] degV1;
    delete [] degV2;

    for(int i = 0; i < vNum1; ++i)
        delete[] graph1[i];
    delete[] graph1;


    for(int i = 0; i < vNum2; ++i)
        delete[] graph2[i];
    delete[] graph2;
}

//tworzenie pomocniczej tablicy umozliwiajace permutowanie numerow wierzcholkow
void Isomorphism::createPermutationArray() {
    permArray = new int[vNum1];
    for(int i = 0; i < vNum1; ++i)
        permArray[i] = i;
}

//sprawdzanie czy w obu grafach jest tyle samo wierzcholkow o takich samych stopniach
bool Isomorphism::checkDegV() {

    std::sort(degV1, degV1 + vNum1);
    std::sort(degV2, degV2 + vNum2);

    for(int i = 0; i < vNum1; ++i)
        if(degV1[i] != degV2[i])
            return false;
    return true;
}


//pobieranie danych z plikow i tworzenie macierzy sasiedztwa
bool Isomorphism::openFiles(int argc, char** argv) {
      std::ifstream file;

      //otwieramy pierwszy plik
      file.open( argv[1] );
      if( !file.good())
        return false;

      //pobieranie informacji o grafie z pliku
      file >> vNum1;
      graph1 = new bool * [vNum1];
      for(int i = 0; i < vNum1; ++i)
          graph1[i] = new bool[vNum1];

      int a, b;
      degV1 = new int[vNum1];

      while( file >> a >> b ) {
          ++eNum1;
          graph1[a][b] = true;
          degV1[a] += 1;
          if( a != b ) {
              graph1[b][a] = true;
              degV1[b] += 1;
          }

      }
      file.close();


      //otwieramy drugi plik
      file.open( argv[2] );
      if( !file.good())
        return false;

      //pobieranie informacji o grafie z pliku
      file >> vNum2;
      graph2 = new bool * [vNum2];

      for(int i = 0; i < vNum2; ++i)
          graph2[i] = new bool[vNum2];
      degV2 = new int[vNum2];


      while( file >> a >> b ) {
          ++eNum2;
          graph2[a][b] = true;
          degV2[a] += 1;
          if( a != b ) {
              graph2[b][a] = true;
              degV2[b] += 1;
          }

      }


      file.close();

      return true;
}


//sprawdzanie czy dana permutacja jest dobra
bool Isomorphism::verifyPermutation() {
    for(int i = 0; i < vNum1; ++i) {
        for(int j = 0; j < vNum1; ++j) {
            if( graph1[i][j] != graph2[ permArray[i] ][ permArray[j] ]   )
                return false;
        }
    }
    return true;
}

void Isomorphism::printfPermutation() {
    std::cout << "Izomorficzne" << std::endl;
    for(int i =0; i < vNum1; ++i)
        std::cout << i << " --> " << permArray[i] << std::endl;
}

//permutowanie tablicy z numerami wierzcholkow, zwraca false gdy nie ma juz mozliwej permutacji
bool Isomorphism::nextPermutation() {
    return std::next_permutation(permArray, permArray + vNum1);
}

//sprawdzanie czy liczba wierzcholkow i krawedzi w dwoch grafach sie zgadza
bool Isomorphism::notEqualVertexOrEdgeNum() {
    return vNum1 != vNum2 || eNum1 != eNum2;
}

int main(int argc, char** argv) {
    if(argc != 3 ) {
        std::cout << "Musisz podac 2 pliki z grafami" << std::endl;
        return 0;
    }

    Isomorphism isomorp;


    if(!isomorp.openFiles(argc, argv)) {
        std::cout << "Nie udalo sie otworzyc plikow o podanych nazwach" << std::endl;
    }
    else {
        if( isomorp.notEqualVertexOrEdgeNum() ||  !isomorp.checkDegV() ) {}
        else {
            isomorp.createPermutationArray();
            do {
                if( isomorp.verifyPermutation() ) {
                    isomorp.printfPermutation();
                    isomorp.exit();
                    return 0;
                }            }
            while( isomorp.nextPermutation() );
        }
        std::cout << "Nieizomorficzne" << std::endl;
        isomorp.exit();
    }
    return 0;
}

