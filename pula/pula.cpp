/*
    Inserir crianças na fila de espera do pula pula
    Mover a primeira criança da fila de espera do pula pula para dentro do pula pula.
    Mover a primeira criança que entrou no pula pula para o final da fila de espera.
*/
#include<iostream>
#include<vector>
#include<list>
#include<utility>
#include<memory>
using namespace std;
class kid{
public:
    std::string name;
    int idade;

    kid(std::string name, int idade): name(name), idade(idade){}
    
    friend std::ostream& operator<<(std::ostream& os, const kid& k){
        os << k.name << "-" << k.idade;
        return os;
    }   
      
};

class pula_pula{
public:
    std::vector<shared_ptr<kid>>lugares;
    std::list<shared_ptr<kid>>espera;

    pula_pula(int qtd_lugares = 1) : lugares(qtd_lugares, nullptr){}
        
    void entrar_espera(const shared_ptr<kid>& k){
        cout<<"entrando na fila de espera"<<endl;
        this->espera.push_back(k);
    }
    bool entrar_pula(int vaga){
        if(vaga < 0 || vaga >= this->lugares.size()){
            cout<<"vaga invalida"<<endl;
            return false;
        }
        if(this->lugares[vaga] != nullptr){
            cout<<"vaga ocupada"<<endl;
            return false;
        }
        if(this->espera.empty()){
            cout<<"fila de espera vazia"<<endl;
            return false;
        }
        cout<< "a pessoa " << this->espera.front()->name << " entrou no pula pula" << endl; 
        this->lugares[vaga] = this->espera.front();
        this->espera.pop_front();
        return true;
    }
    bool tirando_kid(int vaga){
        if(vaga < 0 || vaga >= this->lugares.size()){
            cout<< "essa vaga do pula pula nao existe" << endl;
            return false;
        };
        if(this->lugares[vaga] == nullptr){
            cout<< "essa vaga do pula pula esta vazia" << endl;
            return false;
        };
        cout<< "a pessoa " << this->lugares[vaga]->name << " saiu do pula pula" << endl;
        this->espera.push_back(this->lugares[vaga]);
        this->lugares[vaga] = nullptr;
        return true;
    }
    void imprimir_espera(){
        cout<<"fila de espera"<<endl;
        for(auto& k: this->espera){
            cout<<*k<<endl;
        }
    }
    void imprimir_pula(){
        cout<<"pula pula"<<endl;
        for(auto& k: this->lugares){
            if(k != nullptr){
                cout<<*k<<endl;
            }
        }
    }
};




    


int main(){
    
    pula_pula pula(2);
    pula.entrar_espera(make_shared<kid>("joao", 10));
    pula.entrar_espera(make_shared<kid>("maria", 12));
    pula.entrar_pula(0);
    pula.entrar_espera(make_shared<kid>("jubileu", 12));
    pula.entrar_espera(make_shared<kid>("marianinha", 12));
    pula.entrar_pula(1);
    pula.tirando_kid(0);
    pula.tirando_kid(1);
    pula.entrar_pula(0);
    pula.entrar_pula(1);
    pula.imprimir_espera();
    pula.imprimir_pula(); 
    return 0;
    
}
