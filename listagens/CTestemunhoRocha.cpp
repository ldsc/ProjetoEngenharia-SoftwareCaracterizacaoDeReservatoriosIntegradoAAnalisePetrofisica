#include "CTestemunhoRocha.h"
#include "CCilindro.h"
#include <string>
#include <fstream>

using namespace std;

/// importando os dados do testemunho
void CTestemunhoRocha:: ImportaDadosRocha () 
{
  int x;
  double y;
  double z;
  double w;
  double k;
  string m;
  
  ifstream fin;
  fin.open ( "DadosFluidoRochaCilindro.dat" );
  
  for (int i=0; i<5; i++) // Desconsidera o cabecalho do arquivo DadosFluidoRochaCilindro.dat
    fin >> m;
  // Neste ponto ira importar os dados na seguinte ordem id, pesoSeco, Comprimento, Diametro e para o id não pegar o valor da viscosidade é pedido para ler mais um valor.
  while ( !fin.eof() ) 
                        
  {
    fin >> x;
    ID(x);
    fin >> y;
    PesoSeco(y);
    fin >> z;
    Comprimento(z);
    fin >> w;
    Diametro(w);
    fin >> k;
  }
}
