#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

class Personagem{
private:    
    bool vivo = true;
    std::string nome{""};
    int vida{10};
    int level{1};
public:
    Personagem(std::string nome = "NPC"): nome{nome}{
        std::cout << "Personagem criado" << std::endl;
    }
    ~Personagem(){
        //std::cout << "Personagem destruido" << std::endl;
    }
    void setNome(std::string nome){
        this->nome = nome;
    }
    std::string getNome(){
        return nome;
    }
    bool estaVivo(){
        return vivo;
    }
    int getVida(){
        return vida;
    }
    void RecebeDano(int dano){
        if(estaVivo()){
            vida -= dano;
        }
        if(vida <= 0){
            morrer();
        }
    }
    void morrer(){
        vivo = false;
        cout << "O personagem morreu" << endl;
    }
    void falas(){
        vector<string> falas;
        falas[0] = "Peguei voce";
        falas[1] = "Morra com essa";
        falas[2] = "Quais são as suas ultimas palavras?";
        falas[3] = "Você está morto";
        falas[4] = "Cheque Mate";
        falas[5] = "Game over";

        //int numero = rand() % falas.size();

        cout << "oi" << endl;
    }
};
class Guerreiro: public Personagem{
private:
    int vida = 100;
    int ataque = 5;
    
public:
    Guerreiro(std::string nome = "Guerreiro"): Personagem{nome}{
        std::cout << "Guerreiro criado" << std::endl;
    }
    ~Guerreiro(){
        //std::cout << "Guerreiro destruido" << std::endl;
    }
    void atacar(Personagem* inimigo){
        inimigo->RecebeDano(ataque);
        falas();
    }
};

class Mago: public Personagem{
private:
    int vida = 65;
    int ataque = 2;
    int feitico = 25;
    int mana = 100;
public:
    Mago(std::string nome = "Mago"): Personagem{nome}{
        std::cout << "Mago criado" << std::endl;
    }
    ~Mago(){
        //std::cout << "Mago destruido" << std::endl;
    }
    void atacar(Personagem* inimigo){
        inimigo->RecebeDano(ataque);
        cout << "Mago atacou" << endl;
    }
    void lancarfeitico(Personagem* inimigo){
        inimigo->RecebeDano(feitico);
        this -> mana -= 25;
        falas();
    }
};

int main(){
 
    
    Mago cleiton = Mago{"cleiton"};

    Guerreiro jose = Guerreiro{"jose"};

    cleiton.atacar(&jose);

    cout<< cleiton.getVida() << endl;
   


    return 0;
}



//atk normal é 10
//chance de critico 25%
//dano critico ele é 1.2 x atk
//Peguei voce
//Morra com essa
//Quais são as suas ultimas palavras?
//Você está morto
//Cheque Mate
//Game over

