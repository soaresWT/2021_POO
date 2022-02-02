#include<iostream>
#include<map>
#include<memory>
#include<sstream>

using namespace std;

class Interface_medico;
class Interface_paciente;

class Interface_paciente{
public:
    virtual void adicionar_medicos(Interface_medico*) = 0;
    virtual void remover_medicos(string Id_medico) = 0;
    virtual string get_id() = 0;
    virtual string get_diagnostico() = 0;
    virtual map<string, Interface_medico*> get_medicos() = 0;
};

class Interface_medico{
public:
    virtual void adicionar_pacientes(Interface_paciente*) = 0;
    virtual void remover_pacientes(string Id_paciente) = 0;
    virtual string get_id() = 0;
    virtual map<string, Interface_paciente*> get_pacientes() = 0;
    virtual string get_classes() = 0;
};

class Medico : public Interface_medico{
private:
    string classe;
    string sender;
    map<string, Interface_paciente*> pacientes;
public:
    Medico(string classe = " ", string sender = " "): classe(classe), sender(sender){}
    
    void adicionar_pacientes(Interface_paciente* paciente){
    auto id = paciente->get_id();
    if(pacientes.find(id) == pacientes.end()){ pacientes[id] = paciente;} 
    else { cout << "Paciente ja existe" << endl;}
    }

    void remover_pacientes(string Id_paciente){
        auto it = pacientes.find(Id_paciente);
        if(it != pacientes.end()){ 
            pacientes.erase(it);
        }
        else { cout << "Paciente nao existe" << endl;}
    }
    string get_id(){ return sender;}
    map<string, Interface_paciente*> get_pacientes(){ return pacientes;}
    string get_classes(){ return classe;}

    friend ostream& operator<<(ostream& os, const Medico& medico){
        os << "Medico: " << medico.sender << " Classe: " << medico.classe << endl;
        return os;
    }
    friend ostream& operator<<(ostream& os, const map<string, Interface_paciente*>& pacientes){
        for(auto it = pacientes.begin(); it != pacientes.end(); it++){
            os << it->second;
        }
        return os;
    }
};

class Paciente : public Interface_paciente{
private:
    string sender;
    string diagnostico;
    map<string, Interface_medico*> medicos;
public:
    Paciente(string sender = " ", string diagnostico = " "): sender(sender), diagnostico(diagnostico){}

    void adicionar_medico(Interface_medico* medico){
       auto id = medicos.find(medico->get_id());
         if(id == medicos.end()){ medicos[medico->get_id()] = medico;}
         else { cout << "Medico ja existe" << endl;}
    }

    void remover_medicos(string Id_medico){
        auto it = medicos.find(Id_medico);
        if(it != medicos.end()){ 
            auto backup = this->medicos[Id_medico];
            medicos.erase(it);
            backup->remover_pacientes(this->sender);
        }
        else { cout << "Medico nao existe" << endl;}
    }
    string get_id(){ return this->sender;}
    string get_diagnostico(){ return this->diagnostico;}
    map<string, Interface_medico*> get_medicos(){ return this-> medicos;}

    friend ostream& operator<<(ostream& os, const Paciente& paciente){
        os << "Paciente: " << paciente.sender << " Diagnostico: " << paciente.diagnostico << endl;
        return os;
    }
};

class hospital{
private:
    map<string, shared_ptr<Interface_medico>> medicos;
    map<string, shared_ptr<Interface_paciente>> pacientes;
public:
    hospital(){}
    void adicionar_medico(shared_ptr<Medico> medico){
        auto id = medico->get_id();
        if(medicos.find(id) == medicos.end()){ medicos[id] = medico;}
        else { cout << "Medico ja existe" << endl;}
    }
     void adicionar_paciente(shared_ptr<Medico> Paciente){
        auto id = Paciente->get_id();
        if(pacientes.find(id) == pacientes.end()){ pacientes[id] = Paciente;}
        else { cout << "Paciente ja existe" << endl;}
    }
    void remover_medico(string Id_medico){
        auto it = medicos.find(Id_medico);
        if(it != medicos.end()){
            for(auto& [nome, paciente] : this->medicos[Id_medico]->get_pacientes()){
                this->medicos[Id_medico]->remover_pacientes(paciente->get_id());
            }
        }
    }
    void remover_paciente(string Id_paciente){
        auto it = pacientes.find(Id_paciente);
        if(it != pacientes.end()){
            for(auto& [nome, medico] : this->pacientes[Id_paciente]->get_medicos()){
                medico->remover_pacientes(this->pacientes[Id_paciente]->get_id());

            }
            pacientes.erase(Id_paciente);
        }
    }

    void conectar(string Id_medico, string Id_paciente){
        auto it = pacientes.find(Id_paciente);
        if(it != pacientes.end()){
            auto it2 = medicos.find(Id_medico);
            if(it2 != medicos.end()){
                this->medicos[Id_medico]->adicionar_pacientes(this->pacientes[Id_paciente].get());
                this->pacientes[Id_paciente]->adicionar_medicos(this->medicos[Id_medico].get());
            }
            else { cout << "Medico nao existe" << endl;}
        }
        else { cout << "Paciente nao existe" << endl;}
    }
    friend ostream& operator<<(ostream& os, const hospital& hospital){
        os << "Hospital" << endl;
        for(auto& [nome, medico] : hospital.medicos){
            os << medico;
        }
        for(auto& [nome, paciente] : hospital.pacientes){
            os << paciente;
        }
        return os;
    }
};
int main(){



}