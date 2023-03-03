#include "CAjusteCurva.h"

//inclui a biblioteca iostrem pois usa funcoes de entrada e saida de dados para a tela
#include <iostream>

//inclui a biblioteca cmath pois usa a funcao logaritmica
#include <cmath>

//inclui a biblioteca vector pois usa funcoes dos vetores: push_back, resize
#include <vector>

//usa funcoes pertencentes ao namespace std
using namespace std;

/// Funcao que cria a variavel logaritmica a partir dos parametros 1 e 3 da funcao, executa a regressao linear atraves do metodo dos minimos quadrados.
void CAjusteCurva::Regressao(vector<double> vx, vector<double> vy, double z)
{
  //limpa o vetor do eixo x para novo preenchimento
  logt.resize(0);
  
  //loop que percorre todo o vetor vx e preenche logt
  for(int i=0 ; i<vx.size() ; i++)
          //transformacao da variavel em logaritmica
          logt.push_back (log10((z+vx[i]) / vx[i]));  

  CalcularAjusteMinimosQuadrados(logt, vy);
  m = CoeficienteAngular ();
  n = CoeficienteLinear ();
  r = CoeficienteCorrelacao ();

  cout << "EQUACAO: y = " << m << " * x + " << n << endl << "r = " << r << endl; 
}


/// Funcao que ajusta a regressao para o periodo correto, removendo os pontos referentes a estocagem 
void CAjusteCurva::Ajuste(vector<double> vx, vector<double> vy, double z)
{
 /// variavel que contem os coef. de correlacao
 vector<double> coef(vx.size()/2,r);
 
 /// variavel que ajusta o eixo y
 vector<double> y;         
 
 /// variavel que ajusta o eixo x          
 vector<double> t;                  
 
 // loop principal que vai aumentando o valor de k e retirando as primeiras posicoes dos vetores (estocagem)
 for (int k=1 ; k<(vx.size()/2) ; k++)
 {
     // repete o loop ate achar o coef. de correlacao aceitavel
     if(coef[k-1]<0.9900)              
     {
               // ocorre estocagem se cair na condicao
               efeitoEstocagem = true;           
               cout << "Necessario novo Ajuste." << endl; 
               
               // limpa os vetores
               t.resize(0);             
               y.resize(0);
          
               for(int l=0 ; l<vx.size() ; l++)
               {
                  // define o eixo x
                  t.push_back (log10((z + vx[l])/vx[l])); 
                  // define o eixo y
                  y.push_back (vy[l]);                    
               }
          
               for(int w=0 ; w<(vx.size()-k) ; w++)
               {
                  // retira o primeiro valor do vetor (estocagem)
                  t[w] = t[w+k];                          
                  // se repetir o if, vai retirando   
                  y[w] = vy[w+k];   
                  // até terminar a estocagem (coef. sera bom)                            
               }                                          
               
               // redefine o temanho dos vetores
               t.resize (vx.size()-k); 
               y.resize (vx.size()-k);
               
               // nova regressao linear   
	       CalcularAjusteMinimosQuadrados(t,y);
               m = CoeficienteAngular ();              
               n = CoeficienteLinear ();
               // novo coeficiente de correlacao
               coef[k] = CoeficienteCorrelacao ();    

               cout << "EQUACAO: y = " << m << " * x + " << n << endl << "r = " << coef[k] << endl;
  
               if (1.2*coef[k]<coef[0])
                         cout << "Regressao Linear nao tao perfeita, Indicativo de Reservatorio Heterogeneo"<<endl; 
	       //apos a segunda regressao
               if (k>1) 
               {
                       if ((1.2*coef[k])<coef[k-1])
                       {
                               k = vx.size()/2; //para terminar o loop
                               cout << "Maximo Coeficiente de Correlacao alcançado." << endl;
                       }
               }  
     
      } // Fecha a condicao inicial.
  } // Fecha loop.
} // Fecha o Metodo.