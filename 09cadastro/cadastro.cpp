#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <exception>

using namespace std;
class conta {
protected:
    float saldo{0};
    string Client_Id; 
    int idCount;
    string tipo{""};
public:
    conta(string Client_id = "", int id = -1) : Client_Id{Client_id}, idCount{id} {}

    float get_saldo() {
        return this->saldo;
    }
    int get_id() {
        return this->idCount;
    }
    string get_tipo() {
        return this->tipo;
    }
    string get_Client_Id() {
        return this->Client_Id;
    }
    virtual void atualizarConta() = 0;

    virtual void deposito(float valor) {
        if (valor > 0) { this->saldo += valor; }
        else{  }
    }
    virtual void saque(float valor){
        if(valor > 0 && valor <= this->saldo){ this->saldo -= valor; }
        else{ throw invalid_argument("Valor invalido");}
    }
    
    virtual void transferencia (shared_ptr<conta> contaDestino, float valor){
            
            if(valor < 0 || valor > this->saldo){ 
               throw invalid_argument("Valor invalido");
            }
            
            else{
                if(contaDestino == nullptr){
                   throw invalid_argument("Conta nao existe");
                }
                else{
                    this->saldo -= valor;
                    contaDestino->saldo += valor;
                    cout << "Transferencia realizada com sucesso, para" << contaDestino->get_Client_Id() << ", valor de:"<< valor << endl;
                }
            }
    }
    
    friend std::ostream& operator<<(std::ostream& os, const conta& conta) {
        os << conta.idCount << " : " << conta.Client_Id <<  " : " << "R$" << conta.saldo <<  " : " << conta.tipo << "\n";
        return os;
    }

   
};

class ContaCorrente : public conta{
public:
    ContaCorrente(int id, string clientId) : conta{clientId, id} {
        this->tipo = "CC";
    };  

    virtual void atualizarConta(){
        this->saldo -= 20;
    }
};

class ContaPoupanca : public conta{
public:
    ContaPoupanca(int id, string clientId) : conta{clientId, id} {
        this->tipo = "CP";
    }
    

    virtual void atualizarConta(){
        this->saldo += this->saldo * 0.01;
    }
};

class cliente{
private:
    string Client_id;
    vector<shared_ptr<conta>> contas;
public:
    cliente(string Client_id = " ") : Client_id{Client_id} {}
    
    void adicionarConta(shared_ptr<conta> conta){
        contas.push_back(conta);
    } 
    vector<shared_ptr<conta>> get_contas(){
        return contas;
    }
    string get_Client_id(){
        return Client_id;
    }
    void set_Client_id(string Client_id){
        this->Client_id = Client_id;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const cliente& cliente) {
        os << cliente.Client_id << "\n";
        for(auto conta : cliente.contas){
            os << *conta;
        }
        return os;
    }
};

class banco{
private:
    map<string, shared_ptr<cliente>> clientes;
    map<int, shared_ptr<conta>> contas;
    int Next_id{0};

    shared_ptr<conta> get_conta(int id){ 
        auto it = this->contas.find(id);

        if (it == this->contas.end()){
           throw invalid_argument("Conta nao existe");
        }

        return it->second;
    }

    bool existe_nome(string nome) {
        auto it = this->clientes.find(nome);
        if(it == this->clientes.end()){
            return false;
        }
        return true;
    }

    bool existe_id(int id) {
        auto it = this->contas.find(id);
        if(it == this->contas.end()){
            return false;
        }
        return true;
    }

public:
    banco() {}

    void adicionarCliente(string nome){
        if(existe_nome(nome)){
           throw invalid_argument("Cliente ja existe");
        }else{
            cliente client(nome);
            ContaCorrente cc(Next_id, nome);
            ContaPoupanca cp(Next_id, nome);
           
            client.adicionarConta(make_shared<ContaCorrente>(cc));
            client.adicionarConta(make_shared<ContaPoupanca>(cp));

            this->clientes[nome] = make_shared<cliente>(client);
            this->contas[Next_id] = make_shared<ContaCorrente>(cc);
            this->contas[Next_id] = make_shared<ContaPoupanca>(cp);
            Next_id++;
        }
    }

    void deposito(int id, float valor){
        if(existe_id(id)){
            this->get_conta(id)->deposito(valor);
        }else{
           throw invalid_argument("Conta nao existe");
        }
    }

    void saque(int id, float valor){
        if(existe_id(id) && valor > 0){
            this->get_conta(id)->saque(valor);
        }else{
              throw invalid_argument("Conta nao existe");
        }
    }

    void transferir(int idOrigem, int idDestino, float valor){
        if(existe_id(idOrigem) && existe_id(idDestino) && valor > 0){
            this->get_conta(idOrigem)->transferencia(this->get_conta(idDestino), valor);
        }else{
            throw invalid_argument("Conta nao existe");
        }
    }
    void atualizarMensal() {
        for (auto conta : this->contas) {
            conta.second->atualizarConta();
        }
    }

    friend std::ostream& operator<<(std::ostream& os, banco& bank) {
        
        os << "Contas: \n";

        for (auto account : bank.contas) {
            os << *account.second << "\n";
            cout <<"------------------------------------" << endl;
        }

        return os;
    }

};

int main(){
    try{
        banco inter;

        inter.adicionarCliente("raposo");
        inter.adicionarCliente("dora");
        inter.adicionarCliente("aventureira");
        inter.adicionarCliente("dora");

        inter.deposito(0, 100);
        inter.deposito(1, 200);
        inter.deposito(2, 300);

        cout << inter << endl;

        inter.saque(0, 50);
        inter.saque(1, 100);
        inter.saque(2, 150);

        cout << inter;

        inter.transferir(0, 1, 50);
        inter.transferir(1, 2, 100);
        inter.transferir(2, 0, 150);

        cout << inter;
    }catch(invalid_argument& e){
        cout << e.what() << endl;
    }
   
}


