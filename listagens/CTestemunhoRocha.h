#ifndef CTestemunhoRocha_h
#define CTestemunhoRocha_h
#include "CCilindro.h"

using namespace std;

/// declaracao da classe CTestemunhoRocha
class CTestemunhoRocha: public CCilindro
{
private:
  /// declaracao do atributo id
  int id; 
  /// declaracao do atributo pesoSeco
  double pesoSeco; 
  /// declaracao do atributo temperatura
  double temperatura;
  
public:
  
   /// metodo set para o atributo id
   void ID ( int _id )
   { id = _id; };
   
   /// metodo get para o atributo  id
   int ID()  
   { return id; };
  
   /// metodo set para o atributo  pesoSeco
   void PesoSeco ( double _pesoSeco )	
   { pesoSeco = _pesoSeco; };
  
   /// metodo get para o atributo pesoSeco
   double PesoSeco ()	
   { return pesoSeco; };
  
   /// Construtor no qual ao ser acessada a classe gera um valor para temperatura igual a 25 graus Celsius
  CTestemunhoRocha() : temperatura (25) {};
  
  ///metodo para importar os dados referentes aos atribudo da rocha e do cilindro
  void ImportaDadosRocha(); 

};
#endif



                                                                            

