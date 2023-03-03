#include "CSimuladorAnaliseTestePressao.h"

//inclui a biblioteca iostrem pois usa funcoes de entrada e saida de dados para a tela
#include <iostream>

//inclui a biblioteca cmath pois usa a funcao logaritmica
#include <cmath>

//inclui a biblioteca vector pois usa funcoes dos vetores: push_back, resize
#include <vector>

#include<fstream>

#include<string>

//usa funcoes pertencentes ao namespace std
using namespace std;

///Funcao principal que executa a simulacao do teste
void CSimuladorAnaliseTestePressao::Executar()
{
    cout << endl <<" ====================================================================================== "<<endl
		 <<	endl << " SIMULADOR PARA CARACTERIZACAO DE RESERVATORIOS INTEGRADO A ANALISE PETROFISICA" << endl 
		 << endl <<" ====================================================================================== " <<endl
         << endl << "1-Rodar o Programa" << endl << "2-Sair" << endl << endl;
   int i = 0;
   cin >> i;
    
    while (i==1) //quando terminar a execucao do programa, se o usuario quiser, o programa roda novamente
    {
           cout << "Entrada de Dados do teste de pressao realizado " << endl 
                  << "-------------------------------------------------" << endl;
     
             int n;
	     EntradaSistemaUnidades();
	     
	     cout<<"Digite (1) Para entrar com os parametros do teste manualmente ou (2) para puxar os dados a partir de um arquivo de disco: "<< endl;
	     cin>>n; cin.get();
	     
	     switch(n)
	     { 
	       case 1:
		 
		 EntradaDados();
		 
	       break;
	       
	       case 2:
	
		 ImportaDados();
		 
	       break;
	     }
	     
             cout << "Entrada de Dados Finalizada" << endl 
                  << "-------------------------------------------------" << endl << endl;
             cout << "Importacao dos dados do registrador de Pressao" << endl 
                  << "-------------------------------------------------" << endl << endl;
    
             registrador.Importa();
             cout << "Dados do registrador importados com sucesso" << endl << endl;
             
             cout << "Regressao Linear dos Dados" << endl 
                  << "-------------------------------------------------" << endl << endl;
                  
             ajuste.Regressao (registrador.TempoSemProducao(), registrador.PressaoMedida(), poco.TempoProducao());
             
             cin.get ();
              cout << "Localizando o Periodo Transiente" << endl 
                  << "-------------------------------------------------" << endl << endl;
             
             ajuste.Ajuste(registrador.TempoSemProducao(), registrador.PressaoMedida(), poco.TempoProducao());
             
             cout << "Regressao linear feita com sucesso" << endl
                  << "-------------------------------------------------" << endl;
    
             //GERA O GRAFICO CASO USUARIO QUEIRA
             
             cout << "Deseja gerar o grafico: " << endl << "1-Sim" << endl << "2-Nao" << endl << endl << endl;
             int j;
             cin >> j;
             
             if (j==1)
             {	     
                      CGnuplot plot;
                      //gera o grafico com a reta perfeita obtida
                      plot.set_ylabel ("Pressao");
                      plot.set_xlabel ("Log T");
                      
	                  plot.plot_slope (ajuste.m,ajuste.n);
	                  cin.get();
	                  if (ajuste.efeitoEstocagem==1)
             	      //compara com os pontos originais
	                  plot.plot_xy (ajuste.logt,registrador.PressaoMedida());
	                  cin.get();
             }
  
  
             cout << "Parametros do Reservatorio" << endl 
                  << "-------------------------------------------------" << endl << endl;
             //CALCULOS
             CalculoPermeabilidade();
	     CalculoPressaoInicial();
             CalculoFatorPelicula();
             CalculoRaioEfetivo();
             CalculoIndices();
            
             cin.get();
        
	           	char resp;
    	cout<<"\nVoce deseja comparar a permeabilidade a partir dos dados de poco com a permeabilidade a partir de dados de laboratorio? (s/n)" <<endl;
    	cin>> resp;
    
	    	if( resp== 's')
	    {
			CSimuladorPermeabilidadeGas simulador2;
			
			//executa a funcao Permeabilidade para calculo da mesma a partir de dados de laboratorio
		    
			simulador2.Permeabilidade();
			simulador2.ComparaPermeabilidades(permeabilidade);
		}     
             //se nao ocorreu estocagem
             if (ajuste.efeitoEstocagem==false)
                 cout << "Reservatorio sem o periodo de estocagem" << endl;
             else
                 {
                      CalculoEstocagem ();
                      //zera o valor em caso de novo calculo
                      ajuste.efeitoEstocagem = false;
                      }
    
             cout << "Caracterizacao do Reservatorio." << endl
                  << "-------------------------------------------------" << endl;
                  
             caracterizar.Caracterizacao(permeabilidade, fatorPelicula, indiceProdutividade, poco.RaioPoco(), raioEfetivo);
             cin.get();
            
	     char z;
	     	     
	     cout<<"Deseja salvar os resultados do teste num arquivo de disco (s/n) : "<< endl;
	     cin>>z; cin.get();
	     
	     if(z=='s') 
		Exporta();
	      
             //Nova Escolha
            
			cout << "\n1-Rodar o Programa Novamente" << endl << "2-Sair" << endl << endl;
            cin >> i;
             }
}

//chama as outras entradas de dados
void CSimuladorAnaliseTestePressao::EntradaDados()
{ 
     reservatorio.EntradaDados();
     reservatorio.Erro();
     fluido.EntradaDados();
     fluido.Erro();
     poco.EntradaDados();
     poco.Erro();      
}

//Calcula a permeabilidade
void CSimuladorAnaliseTestePressao::CalculoPermeabilidade ()
{
      permeabilidade = (1.151 * sistemaUnidade * poco.Vazao() * fluido.FatorVolumeFormacao() * 
                    fluido.Viscosidade()) / (-ajuste.m * reservatorio.Altura());
                    
      cout << "Permeabilidade: " << permeabilidade;

         cout << " milidarcy" << endl;

}

//Calcula a pressao inicial
void CSimuladorAnaliseTestePressao::CalculoPressaoInicial()
{
      pressaoInicial = ajuste.n;
      cout << "Pressao Inicial: " << pressaoInicial;
      
      if (sistemaUnidade==141.2)
         cout << " psi" << endl;
      
      if (sistemaUnidade==19.03)
         cout << " kgf/cm2" << endl;
      
}



//Calcula fator pelicula
void CSimuladorAnaliseTestePressao::CalculoFatorPelicula ()
{
       fatorPelicula = 1.151 * ((((ajuste.m * log10(poco.TempoProducao())) + ajuste.n - poco.PressaoPoco())/ 
                       -ajuste.m) - log10((sistemaUnidade * permeabilidade) / 
                       (reservatorio.Porosidade() * fluido.Viscosidade() * fluido.Compressibilidade() 
                       * poco.RaioPoco () * poco.RaioPoco())) - 0.3514 + log10 (poco.TempoProducao()+1));

       
       cout << "Fator de Pelicula: " << fatorPelicula << endl;       
}

//Calcula raio efetivo
void CSimuladorAnaliseTestePressao::CalculoRaioEfetivo()
{
       raioEfetivo = poco.RaioPoco() * exp(-fatorPelicula); 
       cout << "Raio Efetivo: " << raioEfetivo;
       
       if (sistemaUnidade==19.03)
         cout << " metros" << endl;
       
       if (sistemaUnidade==141.2)
         cout << " ft" << endl;
}

//Calcula do indice de produtividade, eficiencia de fluxo e queda de pressao referente ao dano
void CSimuladorAnaliseTestePressao::CalculoIndices ()
{
       pressaoDano = 0.869 * (-ajuste.m) * fatorPelicula;
       
       indiceProdutividade = poco.Vazao() / (pressaoInicial - poco.PressaoPoco());
       
       eficienciaFluxo = (pressaoInicial - poco.PressaoPoco() - pressaoDano) / (pressaoInicial - poco.PressaoPoco());
       
       cout << "Queda de Pressao devido ao dano: " << pressaoDano << endl;
       
       //Exibir em porcentagens
       cout << "Indice de Produtividade: " << indiceProdutividade*100.0 << " % " << endl << 
            "Eficiencia de Fluxo: " << eficienciaFluxo*100.0 << " % " << endl;
}

//Calcula os parametros da estocagem, se houver
void CSimuladorAnaliseTestePressao::CalculoEstocagem()
{
     coeficienteEstocagem = (poco.Vazao() * fluido.FatorVolumeFormacao() * registrador.TempoSemProducao(0)) 
                            / (24.0 * (registrador.PressaoMedida(0) - poco.PressaoPoco()));
     
     tempoEstocagem = ((60.0 + 3.5 * fatorPelicula)/(permeabilidade * reservatorio.Altura())) 
                    * sistemaUnidade * 24.0 * coeficienteEstocagem * fluido.Viscosidade(); 
                    
     cout << "Coeficiente de Estocagem: " << coeficienteEstocagem << endl 
        << "Tempo de Estocagem: " << tempoEstocagem;
     
         cout << " horas" << endl;
      
}    

void CSimuladorAnaliseTestePressao::Exporta ()
{
		//armazena a string digitada em nomeSaida
   		string nome;
	  	cout << "\nInforme o nome do arquivo de saida com os parametros calculados pelo simulador: " << endl;
  	    	cin>>nome;
		cin.get();
  	    
	  	//getline (cin,nome);    
		string formato = ".dat";
		string Saida = nome+formato;
		
	///abre aquivo    
    fout.open (Saida.c_str());
    
  fout<< "Permeabilidade: " << permeabilidade;
  fout<< " milidarcy" << endl;
  fout<< "Pressao Inicial: " << pressaoInicial;
      
      if (sistemaUnidade==141.2)
         fout << " psi" << endl;
      
      if (sistemaUnidade==19.03)
         fout << " kgf/cm2" << endl;
      
      fout << "Fator de Pelicula: " << fatorPelicula << endl;
      fout << "Raio Efetivo: " << raioEfetivo;
       
       if (sistemaUnidade==19.03)
         fout << " metros" << endl;
       
       if (sistemaUnidade==141.2)
         fout << " ft" << endl;
       fout << "Queda de Pressao devido ao dano: " << pressaoDano << endl;
       
       //Exibir em porcentagens
       fout << "Indice de Produtividade: " << indiceProdutividade*100.0 << " % " << endl
	        << "Eficiencia de Fluxo: " << eficienciaFluxo*100.0 << " % " << endl;
  fout.close ();
}
void CSimuladorAnaliseTestePressao:: ImportaDados ()  ///< importando os dados do testemunho
{
  double a;
  double b;
  double c;
  double d;
  double e;
  double f;
  double g;
  double h;
  double j;
  
  string m;
  string nomeArquivo;                   
  
  cout << "Informe o nome do arquivo com os dados : " << endl;
  //armazena a string digitada em nomearquivo
  getline (cin,nomeArquivo);  
  
  ifstream fin;
  fin.open ( nomeArquivo.c_str() );
  
  for (int i=0; i<9; i++)
    fin >> m;
  
  while ( !fin.eof() ) ///< neste ponto ira importar os dados na seguinte ordem id, pesoSeco, Comprimento, Diametro e para o id não pegar o valor da
                       ///< viscosidade é pedido para ler mais um valor.
  {
    fin >> a;
	reservatorio.porosidade=a;
	fin>>b;
	reservatorio.altura=b;
	fin>>c;
	fluido.fatorVolumeFormacao=c;
	fin>>d;
	fluido.viscosidade=d;
	fin>>e;
	fluido.compressibilidade=e;
	fin>>f;
	poco.vazao=f;
	fin>>g;
	poco.tempoProducao=g;
    fin >> h;
    poco.pressaoPoco=h;
    fin >> j;
    poco.raioPoco=j;
  }
}

//set
void CSimuladorAnaliseTestePressao::SistemaUnidade(double _sistemaUnidade)
{
  sistemaUnidade = _sistemaUnidade; 
}

//get
double CSimuladorAnaliseTestePressao::SistemaUnidade() const
{
  return sistemaUnidade;   
}


//Funcao que preenche o sistemaunidade por um pequeno menu  
void CSimuladorAnaliseTestePressao::EntradaSistemaUnidades()
{
  cout << "Qual o sistema de unidades utilizado para informar os parametros:" << endl << 
       "1 - Americano (Oilfield)" << endl << "2 - Brasileiro (Petrobras)" << endl; 
  int i;
  cin >> i;
  cin.get();
  
  //repete a entrada enquanto o valor for equivocado
  while ((i!=1)&&(i!=2))
  {
          cout << "Reinforme o sistema de unidades utilizado." << endl;
          cin>>i;
          cin.get(); 
  }
  
  if(i==1)
              sistemaUnidade = 141.2; 
  
  if(i==2)
              sistemaUnidade = 19.03;

}
