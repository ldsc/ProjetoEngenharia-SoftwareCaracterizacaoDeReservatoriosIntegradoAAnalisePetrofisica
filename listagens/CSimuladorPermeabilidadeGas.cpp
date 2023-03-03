#include "CSimuladorPermeabilidadeGas.h"
#include <iostream>
#include <cmath>

using namespace std;

/// metodo para calcular a permeabilidade
double CSimuladorPermeabilidadeGas :: Permeabilidade ()
{
  // importa os dados do fluido
  fluido.ImportaDadosFluido(); 

  // importa os dados referentes as caracteristicas da rocha e do cilindro
  dados.ImportaDadosRocha(); 
  
  // importa os dados para calcular a permeabilidade
  permeametro.ImportaCalculaDadosPermeametro();
  
  // calculo da permeabilidade utilizando o coeficiente angular do ajuste
  ajuste.CalcularAjusteMinimosQuadrados(permeametro.DifPressao(),permeametro.Vazao());
        permeabilidade = ( 2000 * dados.Comprimento() * fluido.Viscosidade() * permeametro.PressaoSaida() * ajuste.CoeficienteAngular() )/ dados.AreaTransversal(dados.Diametro());
		cout << "Permeabilidade a partir de teste de laboratorio = " << permeabilidade;
		cout << " milidarcy" << endl;    
		 

  cout << "Viscosidade do fluido = " << fluido.Viscosidade() << " cp" << endl << endl; 
  
  // retornar a permeabilidade
  return permeabilidade;
}

void CSimuladorPermeabilidadeGas::ComparaPermeabilidades(double k_reservatorio)
{
	double erro= (k_reservatorio-permeabilidade)*(100/k_reservatorio);
	
	if(erro<0)
	{
	 double erro= (permeabilidade-k_reservatorio)*(100/permeabilidade);
	 	if (erro>50)
	 	{
	 		cout<< "O erro da permeabilidade foi: " << erro << " porcentos. "<< endl;
	 		cout<< " \nEsse erro pode ser explicado devido a heterogeneidades no reservatorio visto que num teste de laboratorio avalia-se um pequeno intervalo da formacao. \n " << endl;
		}
		else
		{
			cout<< "O erro da permeabilidade foi: " << erro << " porcentos. "<< endl;
			cout<< " \n A analise da amostra de rocha foi condizente com o encontrado no teste de poco.\n " <<endl;
		}
	}
	else if (erro>50)
	{
		cout<< "O erro da permeabilidade foi: " << erro << " porcentos. "<< endl;
		cout<< " \nEsse erro pode ser explicado devido a heterogeneidades no reservatorio visto que num teste de laboratorio avalia-se um pequeno intervalo da formacao. \n " << endl;
	}
	else
	{
	 cout<< "O erro da permeabilidade foi: " << erro << " porcentos.\n "<< endl;
	 cout<< " \n A analise da amostra de rocha foi condizente com o encontrado no teste de poco.\n " <<endl;
	}

}
