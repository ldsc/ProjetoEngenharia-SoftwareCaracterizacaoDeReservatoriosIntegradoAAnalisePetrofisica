#include "CAjusteCurvaMinimosQuadrados.h"

//inclui a biblioteca cmath pois usa a funcao logaritmica
#include <cmath>

//inclui a biblioteca vector pois usa funcoes dos vetores: push_back, resize
#include <vector>

//usa funcoes pertencentes ao namespace std
using namespace std;

//retorna o valor do coeficiente angular
void CAjusteCurvaMinimosQuadrados::CalcularAjusteMinimosQuadrados (vector<double> vx, vector<double> vy)
{
     double mnum = 0.0; //termo do denominador
     double mden = 0.0; //termo do numerador

     double mediax = estatistica.Media(vx);
     double mediay = estatistica.Media(vy);
     
     for (int j=0 ; j<vx.size() ; j++) //percorre todo o vetor
     { 
         //metodo dos minimos quadrados
        mnum = mnum + (vx[j] * (vy[j] - mediay));
        mden = mden + (vx[j] * (vx[j] - mediax));
     }
    
    coeficienteAngular = mnum/mden;
    
    coeficienteLinear = mediay - (coeficienteAngular * mediax);
       
       double somar = 0.0;
       double variax = 0.0;
       double variay = 0.0;
       
       for (int j=0 ; j<vx.size() ; j++)
       {
           somar = somar + ((vx[j] - mediax) * (vy[j] - mediay));
           variax = variax + (pow ((vx[j] - mediax),2));
           variay = variay + (pow ((vy[j] - mediay),2));
       }
     
       coeficienteCorrelacao = -somar / sqrt(variax * variay); 
    
}


double CAjusteCurvaMinimosQuadrados::CoeficienteLinear () const
{
     return coeficienteLinear;
}


double CAjusteCurvaMinimosQuadrados::CoeficienteCorrelacao() const
{
       return coeficienteCorrelacao; 
}

double CAjusteCurvaMinimosQuadrados::CoeficienteAngular() const
{
       return coeficienteAngular; 
}
