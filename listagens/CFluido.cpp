#include "CFluido.h"
#include <cmath>

//inclui a biblioteca iostrem pois usa funcoes de entrada e saida de dados para a tela
#include <iostream>

using namespace std;


//funcao de entrada de dados da classe
void CFluido::EntradaDados()
{
 cout << "Informe o fator volume-formacao do fluido: " << endl;
 cin >> fatorVolumeFormacao;
 cin.get();
  
 int resp;
 cout << "Usuario deseja entrar com o valor da viscosidade (1) ou calcular a partir de uma correlacao (2) ? "<< endl;
 cin>> resp;
 
  
 switch (resp)
 {
 	case 1:
 	
	cout<<"Entre com o valor da viscosidade: " <<endl;
 	cin>> viscosidade;
 	cin.get();

   break; 
 
    case 2:
	
	cout << "Entre com a temperatura do fluido em Fahrenheit: " << endl;
 cin >> temperatura;
 cin.get(); 

 cout<< "Entre com o grau API do fluido: " <<endl;
 cin>> api;
 cin.get();
 
	cout<< " A viscosidade sera calculada a partir da correlacao de Petrosky Farshad para Oleo Morto" << endl;
    Viscosidadecorrelacao();
    cout<< " A viscosidade calculada e: " << viscosidade << endl;
 }
 
 cout << "Informe a compressibilidade total (fluido+rocha): " << endl;
 cin >> compressibilidade;
 cin.get();
 

}

//funcao que acusa e conserta erro de entrada
void CFluido::Erro()
{
  
  //repete a entrada enquanto o valor for equivocado
   
  while (fatorVolumeFormacao<0.00)
  {
         cout << "Reinforme o Fator Volume-Formacao: " << endl;
         cin >> fatorVolumeFormacao;
         cin.get();
  }
  
   while (viscosidade<0.00)
  { 
          cout << "Reinforme a viscosidade." << endl; 
          cin >> viscosidade;
          cin.get();
  }
  
  while (compressibilidade<0.00)
  {
          cout << "Reinforme a compressibilidade." << endl; 
          cin >> compressibilidade;
          cin.get();
  }
  
  while (api<0.00)
  {
          cout << "Reinforme o grau API" << endl; 
          cin >> api;
          cin.get();
  }
}


//set
void CFluido::FatorVolumeFormacao(double _fatorVolumeFormacao)
{
  fatorVolumeFormacao = _fatorVolumeFormacao;   
}

//get
double CFluido::FatorVolumeFormacao() const
{
  return fatorVolumeFormacao;   
}

//set
void CFluido::Viscosidadecorrelacao()
{
  double X;
  X = (4.59388*log10(temperatura))-22.82792;
  viscosidade = (2.3511 * pow(10,7)) * pow(temperatura, (-2.10255)) * pow(log10(api), X);
}

void CFluido::Viscosidade(double _viscosidade)
{
	viscosidade = _viscosidade;
}

//get
double CFluido::Viscosidade() const
{
  return viscosidade;   
}

//set
void CFluido::Compressibilidade(double _compressibilidade)
{
  compressibilidade = _compressibilidade;   
}

//get
double CFluido::Compressibilidade() const
{
  return compressibilidade;   
}

