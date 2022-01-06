#include <iostream>
#include <list>
#include <vector>
#include <memory>
using namespace std;
class cliente {
    int telefone;
    int id;
public:
    cliente(int id = 0, int telefone = 0) : id(id), telefone(telefone) {}
    int get_id() { return this->id; }
    int get_telefone() { return this->telefone; }

    friend std::ostream& operator<<(std::ostream& os, const cliente& c) {
        os << "id: " << c.id << " telefone: " << c.telefone;
        return os;
    }
};
class sala {
private: 
    int capacidade;
    vector<shared_ptr<cliente>> cadeiras;
public:
    sala(int capacidade = 0) : cadeiras(capacidade, nullptr) {
        this->capacidade = capacidade;
    };
    
    void mostrar_cadeiras_livres(){
        cout<< "cadeiras livres: " << endl;
        for (int i = 0; i < this->capacidade; i++) {
            if (cadeiras[i] == nullptr)
                std::cout << "[ "<< i << " ]" << " ";
        }
    }
    bool verificador(int id) {
        for (auto cadeira : cadeiras) {
            if (cadeira != nullptr && cadeira->get_id() == id) 
                return true;   
        }  

        return false;
    }
    void reservar(shared_ptr<cliente> cliente, int idcadeira) {
        if (idcadeira < 0 || idcadeira >= this->capacidade) {
            cout << "cadeira não existe nesta sala, porfavor veja as cadeiras livres a seguir" << endl;
            mostrar_cadeiras_livres();
        }
        if(cadeiras[idcadeira] != nullptr) {
            cout << "cadeira ocupada, porfavor veja as cadeiras livres a seguir" << endl;
            mostrar_cadeiras_livres();
        }
        if (this->verificador(cliente->get_id())) {
            cout << "cliente já está na sala, porfavor veja as cadeiras livres a seguir" << endl;
        }
        cout << "cadeira reservada com sucesso" << endl;
        cadeiras[idcadeira] = cliente;
    }
    void cancelar(int id) {
        for (int i = 0; i < this->capacidade; i++) {
            if (cadeiras[i] != nullptr && cadeiras[i]->get_id() == id) {
                cadeiras[i] = nullptr;
                cout << "cadeira cancelada com sucesso" << endl;
            }
        }      
    }
    friend std::ostream& operator<<(std::ostream& os, const sala& sala) {
        
        cout << endl;
        for (int i = 0; i < (int) sala.cadeiras.size(); i++) {
            if (sala.cadeiras[i] == nullptr)
                os << " [ vazio : " << i << " ] " << endl;
            else 
                os << " [ Cadeira " << i << ": " << *sala.cadeiras[i] << " ] " << endl;
        }
        

        return os;
    }

};
int main(){
    
    sala s1(10);
    s1.reservar(make_shared<cliente>(1, 123456789), 1);
    s1.reservar(make_shared<cliente>(2, 123456789), 2);
    s1.reservar(make_shared<cliente>(3, 123456789), 6);
    //s1.mostrar_cadeiras_livres();
    s1.cancelar(1);
   
   // s1.mostrar_cadeiras_livres();
    cout << s1 << endl;

}
