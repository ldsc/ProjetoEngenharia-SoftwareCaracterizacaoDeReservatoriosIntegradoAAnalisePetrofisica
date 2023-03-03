#ifndef CGasPermeametro_h
#define CGasPermeametro_h

/// Declaracao da classe CGasPermeametro
class CGasPermeametro
{
 private:
   /// declaracao do atributo viscosidade
   double viscosidade;

 public:
   /// metodo para importar os dados referendo ao fluido
   void ImportaDadosFluido (); 

   /// metodo set para o atributo viscosidade
   void Viscosidade ( double _viscosidade )	
   { viscosidade = _viscosidade; };
  
   /// metodo get para o atributo diametro viscosidade
   double Viscosidade ()  
   { return viscosidade; };
        
};
#endif                
      
