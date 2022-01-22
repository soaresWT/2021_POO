#include <iostream>
#include <list>
#include <vector>
#include <memory>
#include <unordered_map>

using namespace std;
class cliente {
    int telefone;
    int id;
public:
    cliente(int id = 0, int telefone = 0) : id(id), telefone(telefone) {}
    int get_id() { return this->id; }
    int get_telefone() { return this->telefone; }
    
    void setTelefone(int telefone){
        this->telefone = telefone;
    }
    void setId(int id){
        if(id > 0){
            this->id = id;
        }else{
            cout<< "Porfavor, informe um id inteiro positivo" << endl;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const cliente& c) {
        os << "id: " << c.id << " telefone: " << c.telefone;
        return os;
    }
};
class sala {
private: 
    int capacidade;
    unordered_map<int, shared_ptr<cliente>> cadeiras;
public:
    sala(int capacidade = 0) : capacidade(capacidade) {}
       
    int get_capacidade() { return this->capacidade; }
    
    void reservar(shared_ptr<cliente> cliente, int idcadeira) {
       auto it = cadeiras.find(idcadeira);
       if(idcadeira < capacidade && idcadeira >= 0){
            if (it == cadeiras.end() || cadeiras[idcadeira] == nullptr) {
                cadeiras[idcadeira] = cliente;
                cout << "Cadeira " << idcadeira << " reservada com sucesso" << endl;
            } else {
                cout << "Cadeira ocupada" << endl;
            }
       }else{
           cout << "Cadeira não existe" << endl;
       }
    }
     void cancelar(int id) {
        for (auto cliente : cadeiras) {
            if (cliente.second->get_id() == id) {
                cadeiras[cliente.first] = nullptr;
            }   
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const sala& sala) {
        os << "----------------------------------------------- \n";
        for (auto cadeira : sala.cadeiras) {
            if (cadeira.second == nullptr)
                os << "";
            else 
                os << "Cadeira " <<  ": " << *cadeira.second << "\n";
        }
        os << "-----------------------------------------------";

        return os;
    }


};
int main(){
    
    sala s1(10);
    s1.reservar(make_shared<cliente>(1, 123456789), 1);
    s1.reservar(make_shared<cliente>(2, 123456789), 2);
    s1.reservar(make_shared<cliente>(3, 123456789), 6);
    
   // s1.cancelar(1);
    s1.cancelar(3);
    cout << s1 << endl;
    s1.reservar(make_shared<cliente>(4, 123456789), 3);
    cout << s1 << endl;
    s1.cancelar(3);
    cout << s1 << endl;
   
   

}