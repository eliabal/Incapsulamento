#ifndef FUNZIONI_H
#define FUNZIONI_H

// Polinomio standard per CRC-32 nell'Ethernet
#define POLYNOMIAL 0x04C11DB7 

#include <string>

using namespace std;

struct EthernetV2Header{
  string Preamble;
  string SFD;
  string DestinationMACAddress;
  string SourceMACAddress;
  string Type;
  string Data;
  string FCS;
};

struct IpHeader{
  string Version;
  string HLen;
  string TOS;
  string TotalLength;
  string Identification;
  string Flags;
  string FragmentOffset;
  string TTL;
  string Protocol;
  string HeaderChecksum;
  string SourceIpAddress;
  string DestinationIpAddress;
  string Options;
  string Padding;
  EthernetV2Header Frame;
};

// Funzione per calcolare il Frame Check Sequence (FCS) usando CRC-32
string calculateFCS(EthernetV2Header frame);

// Funzione per creare un datagramma IP con header Ethernet
IpHeader datagram();
string leggiFile();
void scriviFile(string testo);
string charToBin(string carattere);
string stringaABinario(string testo);
string binarioAStringa(string input);

#endif
