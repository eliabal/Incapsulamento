#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <bitset>
#include <sstream>

#include "funzioni.h"

using namespace std;

// Funzione per convertire una stringa binaria in un array di byte (utile al calcolo del CRC-32)
vector<uint8_t> binaryStringToBytes(const string& binaryString) {
    vector<uint8_t> bytes;
    for (size_t i = 0; i < binaryString.size(); i += 8) {
        bitset<8> byte(binaryString.substr(i, 8));
        bytes.push_back(static_cast<uint8_t>(byte.to_ulong()));
    }
    return bytes;
}

// Funzione per calcolare il CRC-32
string calculateFCS(EthernetV2Header frame) {
    // Concatenazione dei campi necessari per il calcolo del CRC
    string data = frame.DestinationMACAddress + 
                  frame.SourceMACAddress + 
                  frame.Type + 
                  frame.Data;
    
    // Convertire la stringa binaria in un array di byte
    vector<uint8_t> bytes = binaryStringToBytes(data);

    // Inizializzazione del CRC a tutti 1 (0xFFFFFFFF)
    uint32_t crc = 0xFFFFFFFF;
    
    // Calcolo del CRC
    for (uint8_t byte : bytes) {
        crc ^= (byte << 24);
        for (int i = 0; i < 8; i++) {
            if (crc & 0x80000000) {
                crc = (crc << 1) ^ POLYNOMIAL;
            } else {
                crc <<= 1;
            }
        }
    }

    // Complemento a 1 del CRC
    crc = ~crc;
    
    // Convertire il CRC a stringa binaria
    bitset<32> crcBits(crc);
    return crcBits.to_string();
}

IpHeader datagram() { 
    IpHeader header; 
    
    // Versione IPv4 (4)
    header.Version = "0100";  

    // Header Length: 5 words x 4 byte = 20 byte (5) 
    header.HLen = "0101"; 

    // Type of Service (TOS):
    // - Precedence: 3 (011)
    // - Delay: 0
    // - Throughput: 0 
    // - Reliability: 1
    // - Cost: 1
    header.TOS = "01100011"; 

    // Total Length: 1500 byte 
    header.TotalLength = "0000010111011100";  

    // Identification: 1
    header.Identification = "0000000000000001"; 

    // Flags:
    // - DF (Don't Fragment): 0 
    // - MF (More Fragment): 0
    header.Flags = "000";  

    // Fragment Offset: 0
    header.FragmentOffset = "0000000000000"; 

    // Time to Live: 64
    header.TTL = "01000000"; 

    // Protocol: TCP (6)
    header.Protocol = "00000110"; 

    // Header Checksum: 0x0000 (da calcolare dinamicamente)
    header.HeaderChecksum = "0000000000000000"; 

    // Indirizzo IP Sorgente: 192.168.100.200 (in binario)
    header.SourceIpAddress = "11000000101010000110010011001000"; 

    // Indirizzo IP Destinazione: 192.168.1.1 (in binario)
    header.DestinationIpAddress = "11000000101010000000000100000001"; 

    // Campi Opzioni IP:
    // - Copy Flag: 0 
    // - Class Number: 0
    // - Option Number: 0
    header.Options = "00000000"; 

    // Padding (nessun padding in questo caso)
    header.Padding = "00000000"; 

    // Ethernet Frame
    header.Frame.Preamble = "1010101010101010101010101010101010101010101010101010101010101010"; // 8 byte preambolo
    header.Frame.SFD = "11010101"; // Start Frame Delimiter

    // Indirizzo MAC Destinazione (dsap): ff:08:00:c2:54:7b
    header.Frame.DestinationMACAddress = "111111110000100000000000110000100101010001111011"; 

    // Indirizzo MAC Sorgente (ssap): 00:ff:80:ac:52:eb
    header.Frame.SourceMACAddress = "000000001111111110000000101011000101001011101011"; 

    // Type (Ethertype): 0x8000 (verificare endianness)
    header.Frame.Type = "1000000000000000"; 

    // Data (vuoto in questo esempio, può essere popolato in base ai dati dell'applicazione)
    header.Frame.Data = ""; 

    // Frame Check Sequence (FCS) (da calcolare dinamicamente)
    header.Frame.FCS = calculateFCS(header.Frame);; 

    return header;
}

string leggiFile(){
    ifstream fileIn("messaggio.txt"); // Apro file 'messaggio.txt' in lettura
    string riga;
    getline(fileIn, riga);  // Copio prima riga del file in 'riga'
    //cout << "Contenuto file: " << riga << endl; Stampo 'riga'
    fileIn.close();

    return riga;
}

void scriviFile(string testo){
    ofstream fileOut("frame.txt");    // Apro il file 'frame.txt' in scrittura
    if(!fileOut) {
        cout << "Errore nell'apertura del file." << endl;
    }
    fileOut << testo;   // Scrivo il contenuto della variabile 'testo' nel file
    fileOut.close();    // Chiudo il file
}

string charToBin(char carattere){
    string binario= "";
    binario += bitset<8>(carattere).to_string() + " ";
    return binario;
}

string stringaABinario(string testo){
    string binario = "";
    for(char carattere : testo) {
        binario += charToBin(carattere);
    }
    return binario;
}

string binarioAStringa(string input) {
    stringstream lettoreBinario(input);  // Crea uno stream per elaborare l'input
    string carattereBinario;
    string testo;

    // Legge ogni gruppo di 8 bit (separati da spazi) e li converte in caratteri
    while (lettoreBinario >> carattereBinario) {
        char carattere = bitset<8>(carattereBinario).to_ulong(); // Converte il binario in un carattere
        testo += carattere; // Aggiunge il carattere alla stringa risultante
    }
    return testo;
}
