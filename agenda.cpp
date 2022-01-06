#include<iostream> 
#include<vector>
#include<memory>
using namespace std;
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

class agenda{
private:
    std::vector<contato> contatos;
    bool existe(contato contato){
        for(auto contato_ : this->contatos){
            if(contato_.getNome() == contato.getNome()){
                return true;
            }
        }
        return false;
    }
public:
    agenda(){}
    void addContato(contato contato){
       if(!this->existe(contato)){
           contatos.push_back(contato);
           cout<<'\n'<<"Contato adicionado com sucesso"<<'\n';
       }
       else{
           cout<<'\n'<<"Contato ja existe"<<'\n';
       }
    }
};
int main(){
    fone fone1("fone1","1112345678");
    contato contato1("contato1",{std::make_shared<fone>(fone1)});
    cout<<contato1<<endl;
    agenda agenda1;
    agenda1.addContato(contato1);
    agenda1.addContato(contato1);
    
}
