# include "CGasPermeametro.h"
# include <fstream>
# include <string>

using namespace std;

/// importando os dados do fluido
void CGasPermeametro :: ImportaDadosFluido ()  
{
  double x;
  string m;
  
  ifstream fin;
  fin.open ( "DadosFluidoRochaCilindro.dat" );
  
  for (int i=0; i<5; i++)
   fin >> m;
  
  // Faz com que o valor referenta a viscosidade seja sempre o ultimo do arquivo de onde esta sendo extraido os dados.
  while ( !fin.eof() ) 
  {
    fin >> x;
    viscosidade=x;     
  }

}
 
