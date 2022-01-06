#include<iostream> 
#include<vector>
#include<memory>
#include<sstream>

template <typename T>
std::string to_string(T t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
}


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
    void apagarContato(contato contato){
        
        if(existe(contato)){
            this->contatos.erase(this->contatos.begin() + this->contatos.size() - 1);
            cout<<'\n'<<"Contato apagado com sucesso"<<'\n';
        }
        else{
        cout<<'\n'<<"Contato nao existe"<<'\n';
        }
    }

    void listarContatos(){
        for(auto contato : this->contatos){
            cout<<contato<<'\n';
        }
    }
    /*
    vector<contato> procurarContato(string nome){
        vector<contato> contatos_;
        for(auto contato : this->contatos){
            if(contato.getNome() == nome){
                contatos_.push_back(contato);
                cout<<'\n'<<"Contato encontrado:"<< contato << '\n';
            }
        }
        return contatos_;
    }*/
    void search(string pattern){
        vector<contato> ResultadoSearch;
        for (auto contato : this->contatos) {
            auto texto = to_string(contato.getNome());
            if (texto.find(pattern) != string::npos) {
                ResultadoSearch.push_back(contato);
            }
        }
        if(ResultadoSearch.size() == 0){
            cout<<'\n'<<"Nenhum contato encontrado"<<'\n';
        }
        else{
            cout<< '\n' <<ResultadoSearch.size()<<" contatos encontrados"<<'\n';
            cout<<"Contatos encontrados:"<<'\n';
            for (auto contato : ResultadoSearch) { 
                cout<<contato<<'\n';
            }
        }
    }
    friend ostream& operator<<(ostream& os, const agenda& agenda) {
        if (agenda.contatos.empty()) {
            os << "[AGENDA VAZIA]\n";
        } else {
            for (auto contato : agenda.contatos) {
                os << contato << "\n";
            }
        }
        return os;
    }

};
int main(){
    fone fone1("fone1","1112345678");
    fone fone2("fone2","2212345678");
    fone fone3("fone3","3312345678");
    contato contato1("belinha",{std::make_shared<fone>(fone1)});
    contato contato2("antonia",{std::make_shared<fone>(fone2)});
    contato contato3("beto",{std::make_shared<fone>(fone3)});
    cout<<contato1<<endl;
    cout<<contato2<<endl;
    cout<<contato3<<endl;
    agenda agenda1;
    agenda1.addContato(contato1);
    agenda1.addContato(contato2);
    agenda1.addContato(contato3);
    //agenda1.apagarContato(contato1);
    agenda1.listarContatos();
    agenda1.search("be");
    cout<< '\n' << agenda1;

    
}
