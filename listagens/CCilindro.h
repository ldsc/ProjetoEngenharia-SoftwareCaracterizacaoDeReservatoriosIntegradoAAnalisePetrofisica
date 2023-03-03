#ifndef CCilindro_h
#define CCilindro_h

/// Declaracao da classe CCilindro
class CCilindro 
{
private:
  /// declaracao do atributo diametro
  double diametro; 
  /// declaracao do atributo comprimento
  double comprimento; 
  /// declaracao do atributo volumeTotal
  double volumeTotal; 
  /// declaracao do atributo areaTransversal
  double areaTransversal; 

public:
  /// metodo set para o atributo diametro
  void Diametro ( double _diametro)  
  { diametro = _diametro; }; 
  
  /// metodo get para o atributo diametro
  double Diametro()  
  { return diametro; }; 
   
  /// metodo set para o atributo comprimento
  void Comprimento ( double _comprimento)  
  { comprimento = _comprimento; }; 
  
  /// metodo get para o atributo comprimento
  double Comprimento()  
  { return comprimento; };
  
  /// metodo set para o atributo volumeTotal
  void VolumeTotal ( double _volumeTotal)  
  { volumeTotal = _volumeTotal; }; 
  
  /// metodo get para o atributo volumeTotal
  double VolumeTotal()  
  { return volumeTotal; };
  
  /// metodo get para o atributo areaTransversal
  double AreaTransversal()  
  { return areaTransversal; };
   
  
  /// metodo para calcular o volume total de um cilindro
  double VolumeTotal ( double diametro , double comprimento );
  
  /// metodo para calcular a área transversal de um cilindro
  double AreaTransversal ( double diametro );  
 
};
#endif
