#ifndef CPermeametro_h
#define CPermeametro_h
#include <vector>

///Declaracao da classe CPermeametro
class CPermeametro 
{
private:  
  /// declaracao do atributo pressaoSaida
  double pressaoSaida;
  
  /// declaracao do vetor da diferenca Pentrada^2 - Psaida^2
  std::vector <double> difPressao;    
  
  /// declaracao do vetor pressaoEntrada
  std::vector <double> pressaoEntrada; 
  
  /// declaracao do vetor vazao
  std::vector <double> vazao; 
  
public:
  /// construtor da classe no qual e definido o valor 1 para a pressao saida
  CPermeametro () : pressaoSaida (1) {}; 
  
  /// método para importar os atributos para cálculo da permeabilidade
  void ImportaCalculaDadosPermeametro ();  
  
  /// metodo set para o atributo pressaoSaida
  void PressaoSaida ( double _pressaoSaida)  
  { pressaoSaida = _pressaoSaida; }; 
  
  /// metodo get para o atributo pressaoSaida
  double PressaoSaida()  
  { return pressaoSaida; };
  
  /// metodo set para o atributo do valor da diferença dos quadrados das pressões
  void DifPressao ( std::vector <double> _difPressao) 
  { difPressao = _difPressao; };
  
  /// metodo get para o atributo da diferença dos quadrados das pressões
  std::vector<double> DifPressao() 
  { return difPressao; };
  
  /// metodo set para o atributo pressaoEntrada
  void PressaoEntrada ( std::vector <double> _pressaoEntrada) 
  { pressaoEntrada = _pressaoEntrada; };
  
  /// metodo get para o atributo da pressaoEntrada
  std::vector<double> PressaoEntrada() 
  { return pressaoEntrada; };
  
  /// metodo set para o atributo vazao
  void Vazao ( std::vector <double> _vazao) 
  { vazao = _vazao; };
  
  /// metodo get para o atributo vazao
  std::vector<double> Vazao () 
  { return vazao; };

};
#endif
  
