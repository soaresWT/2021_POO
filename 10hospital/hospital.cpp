#include <iostream>
#include <map>
#include <memory>
#include <sstream>

using namespace std;
class Interface_medico;

class Interface_paciente {
public:
    virtual void Adicionar_medicos(Interface_medico* medico) = 0;
    virtual void remover_medico(string idMedico) = 0;
    virtual string get_id() = 0;
    virtual map<string, Interface_medico*> get_medicos() = 0;
    virtual string get_diagnostico() = 0;
};

class Interface_medico {
public:
    virtual void Adicionar_paciente(Interface_paciente* paciente) = 0;
    virtual void remover_paciente(string idPaciente) = 0;
    virtual string get_id() = 0;
    virtual map<string, Interface_paciente*> get_pacientes() = 0;
    virtual string get_classe() = 0;
};

class Medico : public Interface_medico {
private:
    string sender;
    string classe;
    map<string, Interface_paciente*> pacientes;
public:
    Medico(string sender = "", string classe = "") : sender{sender}, classe{classe} {
    }

    virtual void Adicionar_paciente(Interface_paciente* paciente) {
        auto key = paciente->get_id();
        auto it = pacientes.find(key);
        if (it == pacientes.end()) {
            pacientes[key] = paciente;
            paciente->Adicionar_medicos(this);
        } 
    }

    virtual void remover_paciente(string idPaciente) {
        if (pacientes.find(idPaciente) != pacientes.end()) {
            auto paciente = this->pacientes[idPaciente];
            this->pacientes.erase(idPaciente);
            paciente->remover_medico(this->sender);
        } 
    }
      
    virtual map<string, Interface_paciente*> get_pacientes() { return this->pacientes; }

    virtual string get_id() { return this->sender; }

    virtual string get_classe() { return this->classe; }

    friend std::ostream& operator<<(std::ostream& os, const Medico& medico) {
        int contador = 0;
        os << "\nMedico: " << medico.sender << ":" << medico.classe << endl;
        os << "Pacientes: ";
        for (auto& [key, paciente] : medico.pacientes) {
            if (contador == 0) 
                os << key;
            else 
                os << ", " << key;
            contador++;
        }
        os << "," << "\n";
        os << "-----------------------------------------------";
        return os;
    }
};

class Paciente : public Interface_paciente {
protected:
    string sender;
    string diagnostico;
    map<string, Interface_medico*> medicos;
public:
    Paciente(string sender = "", string diagnostico = "") : sender{sender}, diagnostico{diagnostico} {
    }

    virtual void Adicionar_medicos(Interface_medico* medico) {
        auto key = medico->get_id();
        auto it = medicos.find(key);
        if (it == medicos.end()) {
            medicos[key] = medico;
            medico->Adicionar_paciente(this);       
        } 
    }

    virtual void remover_medico(string idMedico) {
       if (medicos.find(idMedico) != medicos.end()) {
            auto medico = this->medicos[idMedico];
            this->medicos.erase(idMedico);
            medico->remover_paciente(this->sender);
        } 
    }

    virtual map<string, Interface_medico*> get_medicos() { return this->medicos; }

    virtual string get_id() { return this->sender; }

    virtual string get_diagnostico() { return this->diagnostico; }
  
    friend std::ostream& operator<<(std::ostream& os, const Paciente& paciente) {
        int contador = 0;
        os << "\nPaciente: " << paciente.sender << ":" << paciente.diagnostico << endl;
        os << "Medicos: " ;
        for (auto& [key, medico] : paciente.medicos) {
            if (contador == 0) 
                os << key;
            else 
                os << ", " << key;
            contador++;
        }
        os << "," << "\n";
        os << "-----------------------------------------------";
        return os;
    }
          
};
           
class Hospital {
private:
    map<string, shared_ptr<Interface_paciente>> pacientes;
    map<string, shared_ptr<Interface_medico>> medicos;
public:
    Hospital() {
    }

    Interface_medico* buscarMedc(string nomeMed) {
        auto it = medicos.find(nomeMed);
        if (it != medicos.end()) 
            return it->second.get();
        else {throw runtime_error("medico nao encontrado.\n");}
    }
            

    Interface_paciente* buscarPac(string nomePac) {
        auto it = pacientes.find(nomePac);
        if (it != pacientes.end()) 
            return it->second.get();
        else {throw runtime_error("paciente naoencontrado.\n");}
    }
            

    void Adicionar_paciente(shared_ptr<Interface_paciente> paciente) {
        auto key = paciente->get_id();
        auto it = pacientes.find(key);
        if (it == pacientes.end()) 
            pacientes[key] = paciente;
        else 
            throw runtime_error("O paciente ja existe.\n");
    }
         
    void remover_paciente(string idPaciente) {
        if (pacientes.find(idPaciente) != pacientes.end()) {
            for (auto& [key, medico] : pacientes[idPaciente]->get_medicos()) {
                medico->remover_paciente(idPaciente);
            }   
            pacientes.erase(idPaciente);
        } 
        else {throw runtime_error("O paciente nao existe.\n");}
    }
            

    void Adicionar_medicos(shared_ptr<Interface_medico> medico) {
        auto key = medico->get_id();
        auto it = medicos.find(key);
        if (it == medicos.end()) 
            medicos[key] = medico;
        else {throw runtime_error("O medico ja existe.\n");}
    }
            

      

    void remover_medico(string idMedico) {
        if (medicos.find(idMedico)!= medicos.end()) {
            for (auto& [key, paciente] : medicos[idMedico]->get_pacientes()) {
                paciente->remover_medico(idMedico);
            }
        } 
        else { throw runtime_error("O medico nao existe.\n");}
    }
           
    void vincular(string nomePac, string nomeMedc) {
        auto paciente = this->buscarPac(nomePac);
        auto medico = this->buscarMedc(nomeMedc);
        medico->Adicionar_paciente(paciente);
    }
           
    friend std::ostream& operator<<(std::ostream& os, Hospital& hospital) {
        for (auto paciente : hospital.pacientes) {
            auto pacienteCast = dynamic_cast<Paciente*>(paciente.second.get());
            os << *pacienteCast;
        }

        for (auto medico : hospital.medicos) {
            auto medicoCast = dynamic_cast<Medico*>(medico.second.get());
            os << *medicoCast;
        }

        return os;
    }
       
};

    


int main(){

    Hospital hospital;
    cout << "a qualquer momento digite 'sair' para sair do programa" << endl;
    cout << "Digite comandos para ver a lista" << endl;
    while (true) {
        string linha{}, cmd{};
        getline(cin, linha);
        stringstream ss(linha);
        ss >> cmd;
        cout << "Comando anterior: " << linha << "\n\n";
        try {
            if (cmd == "adpac") {
                string nome{}, diag{};
                ss >> nome >> diag;
                auto pac = make_shared<Paciente>(nome, diag);
                hospital.Adicionar_paciente(pac);
            } else if (cmd == "adMed") {
                string nome{}, especi{};
                ss >> nome >> especi;
                auto medc = make_shared<Medico>(nome, especi);
                hospital.Adicionar_medicos(medc);
            } else if (cmd == "mostrar") {
                cout << hospital << "\n";
            } else if (cmd == "rmPac") {
                string nome{};
                ss >> nome;
                hospital.remover_paciente(nome);
            } else if (cmd == "rmMed") {
                string nome{};
                ss >> nome;
                hospital.remover_medico(nome);
            } else if (cmd == "sair") {
                break;
            } else if (cmd == "vincular") {
                string paciente{}, medico{};
                ss >> paciente >> medico;
                hospital.vincular(paciente, medico);
            } else if(cmd == "comandos"){
                cout << "adpac <nome> <diagnostico>\n";
                cout << "adMed <nome> <especialidade>\n";
                cout << "mostrar\n";
                cout << "rmPac <nome>\n";
                cout << "rmMed <nome>\n";
                cout << "vincular <nomePaciente> <nomeMedico>\n";
                cout << "end\n";
            } else {
                cout << "Comando invalido\n";
            }
            
            
        } catch (runtime_error &e) {
            cout << e.what() << "\n";
        }
    }

}
               




