#include <iostream>
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
    }
    void feitico(Personagem* inimigo){
        inimigo->RecebeDano(feitico);
        this -> mana -= feitico;
}
};

int main(){
    Personagem jorge = Personagem{"Jorge"};
    Guerreiro guerreiro = Guerreiro{"Guerreiro"};
    Mago mago = Mago{"Mago"};
    guerreiro.atacar(&mago);
    mago.atacar(&guerreiro);
    guerreiro.atacar(&jorge);
    cout << jorge.getVida() << endl;

    return 0;
}



//atk normal é 10
//chance de critico 25%
//dano critico ele é 1.2 x atk

