#include "CCilindro.h"
#include <cmath>

using namespace std;

///Calculando o volume total de um cilindro
double CCilindro :: VolumeTotal ( double diametro, double comprimento ) 
{  
  volumeTotal = 3.14 * pow (( diametro / 2.0 ), 2.0) * comprimento;
  return volumeTotal;
}


/// Calculando a area transversal de um cilindro.
double CCilindro :: AreaTransversal ( double diametro )  
{
  areaTransversal = 3.14 * pow (( diametro / 2.0 ), 2.0);
  return areaTransversal;
}
  
  
