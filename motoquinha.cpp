#include <iostream>
#include <algorithm>
#include <vector>
struct pessoa
{
    int idade;
    std::string nome;

    pessoa(int idade = 0, std::string nome = ""):
        idade(idade), nome(nome){
            std::cout << this->nome << " Foi criado e tem " << this->idade << " anos" << std::endl;
        }
    friend std::ostream& operator<<(std::ostream& os, const pessoa& pessoa) {
        os << "Pessoa: " << "[" << pessoa.nome << ":" << pessoa.idade << "]" << "\n";
    }
};
struct moto{
    pessoa* pess = nullptr;
    int potencia = 0;
    int tempo = 0;

    moto(int potencia) : potencia(potencia){
        std::cout << "Moto criada com " << this->potencia << " de potencia" << std::endl;
    }

    void comprar(int tempo){
        if(tempo > 0){
            this->tempo = tempo; 
            std::cout << "tempo comprado:" << this->tempo << " minutos" << std::endl;
           
        }
        else {
            std::cout << "Tempo não pode ser comprado : " << tempo << " minutos" << std::endl;
           
        }
    }

    bool subir(pessoa* pess){
        if(this->pess != nullptr){
           std::cout << " tem alguem " << std::endl;
           return false;
        } else {
             this->pess = pess;
             std::cout << " subiu na moto" << std::endl;
             return true;
        }
    }
    
    pessoa* descer(){
        if (this->pess == nullptr){
            std::cout << "nao tem ninguem parar descer" << std::endl;
            return nullptr;
        }
        std::cout << "desceu" << std::endl;
        return std::exchange(this->pess, nullptr);
    }
    
    void digirir(){
        if (this->pess == nullptr){
            std::cout << "nao tem ninguem para digirir" << std::endl;
            
        }
        if(this->pess->idade < 10){
            std::cout << "nao pode digirir com essa idade" << std::endl;
            
        }
        if(this->tempo == 0){
            std::cout << "sem tempo, compre mais" << std::endl;
            
        }
        for(this->tempo; this->tempo > 0; this->tempo--){
            std::cout << "digirindo: "<< this->tempo <<" minutos" << std::endl;
            this->potencia++;
        }
        if(this->tempo <= 0){
        std::cout << "acabou o tempo, remova a criança. tempo digirindo "<< this-> tempo << " minutos" << std::endl;
        
        }
       
    }
    void buzinar(){
        if (this->pess == nullptr){
            std::cout << "nao tem ninguem para buzinar" << std::endl;
           
        } else {
            std::cout << "p";
            for(int i = 0; i < this->potencia; i++){
                std::cout << "e";
            }
            std::cout << "m" <<std::endl;
        }
    }
};


       

int main(){
    moto hayabusa = moto(0);
    pessoa victor = pessoa(18, "Victor");

    hayabusa.subir(&victor);
    hayabusa.comprar(10);
    hayabusa.digirir();
    hayabusa.buzinar();
    hayabusa.descer();

}