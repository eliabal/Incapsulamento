#include <iostream>
#include <string>

#include "funzioni.h"
#include "funzioni.cpp"

using namespace std;

int main(){
    string testo = leggiFile(); // Creo 'testo' e ci metto il contenuto di 'messaggio.txt'
    string binario = stringaABinario(testo); // Converto il contenuto di 'testo' in binario e lo salvo in 'binario'
    cout << "Messaggio in binario: " << binario << endl; // Stampo binario a schermo
    scriviFile(binario); // Scrivo 'binario' in 'frame.txt'

    //system("pause");  Funziona solo su Windows

    //testo = ""; // Pulisco 'testo'
    //testo = leggiFile();
    //testo = binarioAStringa(testo);
    //cout << "Contenuto originale del file: " << testo << endl;
    //system("pause");  Funziona solo su Windows
}
