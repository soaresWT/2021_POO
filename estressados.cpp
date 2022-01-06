#include<iostream>
#include<vector>
#include<string>
#include <stdlib.h>  
# include<random>
#include <cstdlib> 
#include <ctime> 
#include<algorithm>
bool existe(std::vector<int> vetor, int valor)
{
    for (int x : vetor) {
       if( x == valor) 
        return true;
    }
    return false;
}
int contar(std::vector<int> vetor, int valor)
{
    int count = 0;
    for (int x : vetor) {
       if( x == valor) 
        count++;
    }
    return count;
}
int procurar_valor(std::vector<int> vetor, int valor)
{
   for (int i = 0; i < vetor.size(); i++) {
       if(vetor[i] == valor){
           return i;
           break;
       }
   }
   //menos 1 atua como um codigo de erro, ja que esta posição nao existe
   //aparentemente ele exigi um return para caso o codigo n retorne nada 
   return -1;
}
int procurar_valor_apos(std::vector<int> vetor, int valor,int Pinicial)
{
    for (int i = Pinicial+1; i < vetor.size(); i++) {
       if(vetor[i] == valor){
           return i;
           break;
       }
   }
   return -1;
}
int procurar_menor(std::vector<int> vetor)
{   
    int menor = vetor[0];
    for (int x : vetor) {
        if (x < menor) {
            menor = x;
        }
    }
    return menor;
}
int procurar_maior(std::vector<int> vetor)
{   
    int maior = vetor[0];
    for (int x : vetor) {
        if (x > maior) {
            maior = x;
        }
    }
    return maior;
}
int procurar_menor_pos(std::vector<int> vetor)
{
    int Pmenor = 0;
    for (int i = 0; i < vetor.size(); i++) {
        if(vetor[i]<vetor[Pmenor]){
            Pmenor = i;
        }
    }
    return Pmenor;
}
int procurar_menor_apos(std::vector<int> vetor, int Pinicial)
{
    int Pmenor = Pinicial+1;
    for (int i = Pinicial+1; i < vetor.size(); i++) {
        if(vetor[i]<vetor[Pmenor]){
            Pmenor = i;
        }
    }
    return Pmenor;
}
int procurar_melhor_se(std::vector<int> vetor)
{
    int PrimeiroH = 0;
    for( int x = 0; x < vetor.size(); x++) {
        if (vetor[x] > 0) {
            PrimeiroH = x;
            break;
        }
    }
    //posso reduzir o custo computacional, se ja começar da posição do primeiro homem
    //n fiz isso pq estava escrevendo esse codigo as 22 horas e realmente tive preguiça
    int HmaisCalmo = PrimeiroH;
    for (int i = 0; i < vetor.size(); i++) {
        if (vetor[i] < vetor[HmaisCalmo] && vetor[i] > 0) {
            HmaisCalmo = i;
        }
    }
    return HmaisCalmo;
}
float calcular_stress_medio(std::vector<int> fila)
{
   //necessita de atenção
   int soma = 0;
   for (int i = 0; i < fila.size(); i++) {
       if (fila[i]<0) {
           soma += -fila[i];
       } else {
           soma+=fila[i];
       }
   }
   float media = soma/fila.size();
   return media;
}
std::string mais_homens_ou_mulheres(std::vector<int> fila)
{
    int quantMulher = 0;
    int quantHomem = 0;
    for ( int i = 0; i < fila.size(); i++) {
        if (fila[i] < 0) {
            quantMulher++;
        } else {
            quantHomem++;
        }
    }
    if (quantHomem > quantMulher) {
        return "Homens";
    } else if ( quantMulher > quantHomem) {
        return "Mulheres";
    } else {
        return "Empate";
    }
}
std::string qual_metade_eh_mais_estressada(std::vector<int> fila)
{
    float metade = fila.size()/2;

    int primeiraSoma = 0;
    for (int i = 0; i < metade; i++) {
        if (fila[i] < 0) {
            primeiraSoma +=  -fila[i];
        } else {
            primeiraSoma+= fila[i];
        }
    }
    int segundaSoma = 0;
    for (int i = metade; i < fila.size(); i++) {
        if (fila[i] < 0) {
            segundaSoma += -fila[i];
        } else {
            segundaSoma+= fila[i];
        }
    }
    float primeiraMedia = primeiraSoma / metade;
    float segundaMedia = segundaSoma / metade;
    if (primeiraMedia > segundaMedia) {
        return "primeira";
    } else if (segundaMedia > primeiraMedia) {
        return "segunda";
    } else {
        return "empate";
    }
}
std::vector<int> clone(const std::vector<int>& fila)
{
    std::vector<int> clone;
    for (int i = 0; i < fila.size(); i++) {
        clone.push_back(fila[i]);
    }
    return clone;
}
std::vector<int> pegar_homens(const std::vector<int>& fila){
    std::vector<int> homens;
    for (int x : fila) {
        if (x > 0) {
            homens.push_back(x);
        }
    }
    return homens;
}
std::vector<int> pegar_calmos(const std::vector<int>& fila)
{
    std::vector<int> homens;
    for (int x : fila) {
        if (x > 0 && x < 10) {
            homens.push_back(x);
        }
    }
    return homens;
}
std::vector<int> pegar_mulheres_calmas(const std::vector<int>& fila)
{
    std::vector<int> mulher;
    for (int x : fila ) {
        if(x < 0 && x > -10) {
            mulher.push_back(x);
        }
    }
    return mulher;
}
std::vector<int> inverter_com_copia(const std::vector<int>& fila)
{
    std::vector<int> invetido;
    for (int i = fila.size()-1; i >= 0; i--) {
        invetido.push_back(fila[i]);
    }
    return invetido;
}
void inverter_inplace(std::vector<int>& fila)
{   
    int auxiliar = 0;
    int n = fila.size()-1;
    for(int i = 0; i < fila.size()/2; i++){
        auxiliar = fila[i];
        fila[i] = fila[n];
        fila[n] = auxiliar;
        n--;
    }
}   
int sortear(const std::vector<int> & vetor)
{
    unsigned seed = time(0);
    srand(seed);
    return vetor[rand()%vetor.size()];
}
void embaralhar(std::vector<int>& vet)
{
    for (int i = 0; i < vet.size(); i++)
	{
        unsigned seed = time(0);
        srand(seed);
		int r = rand() % vet.size();

		int temp = vet[i];
		vet[i] = vet[r];
		vet[r] = temp;
	}
   
}
void ordenar(std::vector<int>& v)
{
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = i+1; j < v.size(); j++)
        {
            if (v[i] > v[j])
            {
                int aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
        }
    }
}
std::vector<int> exclusivos(const std::vector<int>& v)
{
    std::vector<int> exclusivos;
    bool igual = false;
    for (int i = 0; i < v.size(); i++) {
       for (int x : exclusivos) {
           igual = false;
           if( v[i] == x) {
               igual = true;
               break;
           }
       }
       if (igual == false) {
           exclusivos.push_back(v[i]);
       }
    }
    return exclusivos;
}
std::vector<int> diferentes(const std::vector<int>& v)
{
    //std::vector<int> diferentes;
    std::vector<int> inveter;
    for (int p : v) {
        if (p < 0) {
            inveter.push_back(-p);
        } else {
            inveter.push_back(p);
        }
    }

    return  exclusivos(inveter);
}
std::vector<int> abandonados(const std::vector<int>& vet){
    
    //stand by
    return vet;
}
std::vector<int> sozinhos(const std::vector<int>& vet)
{
    std::vector<int> sozinhos;
    bool repetido;
    for(int i = 0; i < vet.size(); i++) {
        repetido = false;
        for (int j = 0; j < vet.size(); j++)
        { 
            if (abs(vet[j]) == abs(vet[i]) && i != j){
                repetido = true;
                break; 
            }
        }
         if (repetido == false) {
            sozinhos.push_back(vet[i]);
           
        } 
    }
    return sozinhos;
}
std::vector<int> mais_ocorrencias(const std::vector<int>& vet)
{
    //FIZ O MAIS RECO0RRENTES E MAIS OCORRENCIAS JUNTAS PORQUE É O MESMO CODIGO 
    std::vector<int> ocorrencias;
    int maior_temporario = 0, maior = 0;

    for (int i = 0; i < vet.size(); i++) {
        maior_temporario = 0;
        for (int x = 0; x < vet.size(); x++){
            if (vet[i] == vet[x]) {
                maior_temporario++;
                //std::cout << vet[i] << " " << maior_temporario << std::endl;
            }
        }
        if(maior_temporario > maior){
            maior = maior_temporario;
            ocorrencias.clear();
            ocorrencias.push_back(vet[i]);
        } else if (maior_temporario == maior) {
            ocorrencias.push_back(vet[i]);
        }
        }
        std::vector<int> auxiliar;
        auxiliar.push_back(ocorrencias[0]);

        bool igual = false;
        for (int i = 1; i < ocorrencias.size(); i++) {
            igual = false;
            for (int j = 0; j < auxiliar.size(); j++) {
                if (ocorrencias[i] == auxiliar[j]) {
                    igual = true;
                    break;
                }
            }
            if (igual == false) {
                auxiliar.push_back(ocorrencias[i]);
            }
        }
        
    //std::cout<< maior<< std::endl;
    auxiliar.push_back(maior);
    return auxiliar;    
}
int briga(const std::vector<int>& v)
{
    int brigas = 0;
    for (int i = 1; i < v.size()-1; i++) {
        if (abs(v[i]) > 50 && abs(v[i-1]) > 30 && abs(v[i+1]) > 30) {
            brigas++;
        }
}
    return brigas;
}
std::vector<int> apaziguados(const std::vector<int>& v)
{
    std::vector<int> apaziguados;

    for (int i = 0; i < v.size(); i++) {
        if (abs(v[i]) > 80 && abs(v[i+1]) < 10 || abs(v[i-1]) < 10 && abs(v[i]) > 80) {
            apaziguados.push_back(i);
        }
    }
    return apaziguados;
}
int quantos_times(const std::vector<int>& v)
{
    //std::vector<int> timesm;
    int times = 0;
    int feminino = -1;
    int masculino = -1;
    int menorqzero = 0;
    int maiorqzero = 0;
    for (int i = 0; i < v.size()-1; i++) {
        if(v[i] < 0){
            menorqzero++;
        } else {
            maiorqzero++;
        }
        
        if (v[i] < 0 && v[i+1] < 0 && i != feminino ) {
            times++;
            feminino = i+1;
            std::cout << "Feminino " << v[i] << " : " << i <<std::endl;
        }
        if (v[i] > 0 && v[i+1] > 0 && i != masculino) {
            times++;
            masculino = i+1;
            std::cout << "masculino " << v[i] << " : " << i <<std::endl;
        }
        
    }
    if(menorqzero == v.size()-1 || maiorqzero == v.size()-1){
        times = 1;
    } 
    return times;
}
int main()
{
    std::vector<int> x;
    std::vector<int> recebidos;
   
    
    x.push_back(11);
    x.push_back(-11);
    x.push_back(-5);
    x.push_back(-4);
    //inverter_inplace(x);
    /*
    std::vector<int> y = apaziguados({83, -4, 65, 8, -99, 12 });
    for (int i : y ){
      std::cout<<i<<" ";
    }*/
    std::cout<<quantos_times({5, 3, 1, -11, 1, 99, -11, -1, -2, 44})<<std::endl;
    
   
    
    //std::cout<<qual_metade_eh_mais_estressada({-51, 99, 1, -50, -1, -99})<<"\n";
    //std::cout<< mais_homens_ou_mulheres(x)<<"\n";
    //std::cout<<calcular_stress_medio(x)<<std::endl;
    //std::cout<<procurar_melhor_se(x)<<"\n";

    //std::cout<<existe(x,2)<<"\n";
    //std::cout<<contar(x,2)<<"\n";
    //std::cout<<procurar_valor_apos(x,4,0)<<"\n";
    return 0;
    
}