///Condicao para nao definir a classe mais de uma vez
#ifndef CReservatorio_h
#define CReservatorio_h

class CReservatorio; 

///Classe contendo as caracteristicas do reservatorio
class CReservatorio
{
      ///privados, so acessados por meio de funcoes get
      public: 
        
        ///porosidade do reservatorio
        double porosidade; 
        ///altura do reservatorio
        double altura;     
         
 public:
      
        ///Funcao que recebe dados do usuario, preenchendo atributos porosidade e altura
        void EntradaDados();
            
        ///Funcao que verifica se houve erro na entrada de dados e pede nova entrada ate nao ocorrer erro
        void Erro();
        
        ///Funcao que seta a porosidade
        void Porosidade(double _porosidade);   
        ///Funcao get da porosidade
        double Porosidade() const;       
        
         ///Funcao que seta a altura           
        void Altura(double _altura);
        ///Funcao get da porosidade           
        double Altura() const; 
	
      
};
#endif
