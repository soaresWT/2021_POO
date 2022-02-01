#include<iostream>
#include<memory>
#include<vector>
#include<utility>

class grafite{
private:
    float calibre;
    std::string dureza;
    int tamanho;
public:
    grafite(float calibre, std::string dureza, int tamanho):calibre(calibre),dureza(dureza),tamanho(tamanho){}
    
    void desgaste(){
       if (this->dureza == "HB")
            this->tamanho--;
        else if (this->dureza == "2B")
            this->tamanho-=2;
        else if (this->dureza == "4B")
            this->tamanho-=4;
        else if (this->dureza == "6B")
            this->tamanho-=6;
    }
    int get_tamanho(){
        return this->tamanho;
    }
    float get_calibre(){
        return this->calibre;
    }
    void set_tamanho(int tamanho){
        this->tamanho = tamanho;
        std::cout << "Tamanho do grafite alterado para " << this->tamanho << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const grafite& g){
        os << "Calibre: " << g.calibre << " Dureza: " << g.dureza << " Tamanho: " << g.tamanho << std::endl;
        return os;
    }


};
class lapiseira{
private:
    std::shared_ptr<grafite> grafito{nullptr};
    float calibre;
    std::vector<std::shared_ptr<grafite>> tambor;
public:
    lapiseira(float calibre):calibre(calibre){}

    void inserir(std::shared_ptr<grafite> g){
        if(this->calibre != g->get_calibre()){
            std::cout << "Calibre diferente" << std::endl;
        }
        this->tambor.push_back(g);
    }
    void carregarbico(){
        if(this->grafito != nullptr) {
            std::cout << "Ja carregado" << std::endl;
        }
        this->grafito = this->tambor.front();
        this->tambor.erase(this->tambor.begin());
        std::cout << "Carregado" << std::endl;
    } 
    std::shared_ptr<grafite> removerGrafite() {
        if (this->grafito == nullptr) {
            std::cout << "não ha grafite na ponta.\n";
            return nullptr;
        }

        return exchange(this->grafito, nullptr);
    }
    void escrever() {
        if (this->grafito == nullptr) {
            std::cout << "Nao existe um grafite no grafito.\n";
        } else if (this->grafito->get_tamanho() <= 1) {
            std::cout << "Nao e mais possivel escrever com esse grafite.\n";
        } else {
            this->grafito->desgaste();
            std::cout << "Escrevendo...\n";
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const lapiseira& l){
        os << "Calibre: " << l.calibre << std::endl;
        for(auto& g: l.tambor){
            os << *g;
        }
        return os;
    }
};
int main(){
    
    

    
    lapiseira l1(0.5);
    l1.inserir(std::make_shared<grafite>(0.5, "HB", 10));
    l1.inserir(std::make_shared<grafite>(0.5, "2B", 10));
  
    l1.carregarbico();
    l1.escrever();



    
}
