#include<iostream> 
#include<vector>
#include<memory>

class fone{
private:
    std::string id;
    std::string numero;
public:
    fone(std::string id, std::string numero){
        if(!fone::validate(numero)){
            throw std::invalid_argument("Numero invalido");
        }
        this->numero = numero;
        this->id = id;
    }
    std::string getId(){return id;}
    std::string getNumero(){return numero;}

    static bool validate(std::string number) {
        for (const auto &n : number) {
            if ((n != '(' && n != ')') && (n > '9' || n < '0')) {
                return false;
            }
        }

        return true;
    }
    friend std::ostream& operator<<(std::ostream &os, const fone &fone) {
        os << fone.id << ":" << fone.numero;
        return os;   
    }

};

class contato{
private:
    std::string nome;
    std::vector<std::shared_ptr<fone>> fones;
public:
    contato(std::string nome, std::vector<std::shared_ptr<fone>> fones):nome(nome),fones(fones){}
    std::string getNome(){return nome;}
    std::vector<std::shared_ptr<fone>> getFones(){return fones;}
    
    void addFone(fone numero) {
        std::string copia = numero.getNumero();
        if(numero.validate(copia)) {
            fones.push_back(std::make_shared<fone>(numero));
        }  
    }

    void apagar(int index) {
        this->fones.erase(this->fones.begin() + index);
    }
    friend std::ostream& operator<<(std::ostream &os, const contato &contato) {
        os << contato.nome << ":";
        for(auto fone : contato.fones){
            os << *fone << ",";
        }
        return os;   
    }
    
};

int main(){
    contato c("Joao",{std::make_shared<fone>("1", "88981215572"),std::make_shared<fone>("2", "88981215572")});
    std::cout << c << std::endl;
    c.apagar(1);
    std::cout << c << std::endl;
    c.addFone(fone("3", "88981215572"));
    std::cout << c << std::endl;
}
