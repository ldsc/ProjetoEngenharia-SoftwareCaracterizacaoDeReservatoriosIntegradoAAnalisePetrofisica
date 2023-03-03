#include "CPermeametro.h"
#include <fstream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

/// importando os dados para cálculo da permeabilidade
void CPermeametro :: ImportaCalculaDadosPermeametro ()  
{
  double x;
  double y;
  string m;
  ifstream fin;
  fin.open("DadosPermeametroGas.dat");
  
  //desconsidera o cabecalho do arquivo DadosPermeametroGas.dat
  for (int i=0; i<2; i++) 
    fin >> m;
 
  // faz com que a primeira coluna do arquivo seja os valores da vazao e a segunda da pressao de entrada
  while (!fin.eof()) 
  {
    fin>>x;
    vazao.push_back(x);
    fin>>y;
    pressaoEntrada.push_back(y);
  }
  
  /// gerando o vetor da diferenca dos quadrados das pressões
  for (int i=0 ; i<pressaoEntrada.size() ; i++) 
    difPressao.push_back(pow(pressaoEntrada[i],2)-pow(pressaoSaida,2));
}
