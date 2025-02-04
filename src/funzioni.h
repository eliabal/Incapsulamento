#ifndef FUNZIONI_H
#define FUNZIONI_H

#include <string>

using namespace std;

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
};

IpHeader datagram();
string leggiFile();
void scriviFile(string testo);
string chatToBin(string carattere);
string stringaABinario(string testo);
string binarioAStringa(string input);

#endif
