#ifndef CSimuladorPermeabilidadeGas_h
#define CSimuladorPermeabilidadeGas_h
#include "CGasPermeametro.h"
#include "CTestemunhoRocha.h"
#include "CAjusteCurvaMinimosQuadrados.h"
#include "CPermeametro.h"
#include "CReservatorio.h"


class CSimuladorPermeabilidadeGas /// declara a classe CSimuladorPermeabilidadeGas
{
private:
  /// declaracao do objeto testemunho referente a classe CTestemunhoRochaCilindrica
  CTestemunhoRocha dados;
  /// declaracao do objeto fluido referente a classe CGasPermeametro
  CGasPermeametro fluido;
  /// declaracao do objeto permeametroGas referente a classe CPermeametroGas
  CPermeametro permeametro; 
  /// declaracao do objeto ajuste referente a classe CAjusteCurva
  CAjusteCurvaMinimosQuadrados ajuste; 
  /// declaracao do atributo permeabilidade do testemunho
  double permeabilidade; 

public:
  /// metodo para calculo da permeabilidade
  double Permeabilidade ();
  /// metodo para comparacao das permeabilidades
  void ComparaPermeabilidades(double k_reservatorio); 
   
};

#endif
