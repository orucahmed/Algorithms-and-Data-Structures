#include <iostream>
#include <vector>
#include <queue>

template <typename TipOznake>
class Grana;

template <typename TipOznake>
class Cvor;

template <typename TipOznake>
class GranaIterator;

template <typename TipOznake>
class UsmjereniGraf{
    protected:
        UsmjereniGraf() { }
    public:
        UsmjereniGraf(int brojCvorova) { }
        virtual ~UsmjereniGraf() { }
        virtual int dajBrojCvorova() const =0;
        virtual void postaviBrojCvorova(int brojCvorova) =0;
        virtual void dodajGranu(int polazniCvor, int dolazniCvor, float  tezina=0) =0;
        virtual void obrisiGranu(int polazniCvor, int dolazniCvor) =0;
        virtual void postaviTezinuGrane(int polazniCvor, int dolazniCvor, float  tezina=0) =0;
        virtual float dajTezinuGrane(int polazniCvor, int dolazniCvor) =0;
        virtual bool postojiGrana(int polazniCvor, int dolazniCvor) =0;
        virtual void postaviOznakuCvora(int brojCvora, TipOznake oznaka) =0;
        virtual TipOznake dajOznakuCvora(int brojCvora) =0;
        virtual void postaviOznakuGrane(int polazniCvor, int dolazniCvor, TipOznake oznaka) =0;
        virtual TipOznake dajOznakuGrane(int polazniCvor, int dolazniCvor) =0;
        virtual Cvor<TipOznake> dajCvor(int brojCvora) =0;
        virtual Grana<TipOznake> dajGranu(int polazniCvor, int dolazniCvor) =0;
        GranaIterator<TipOznake> dajGranePocetak() { return ++GranaIterator<TipOznake>(this,0,-1); }
        GranaIterator<TipOznake> dajGraneKraj() { return GranaIterator<TipOznake>(this,dajBrojCvorova(),0); }
};


template <typename TipOznake>
class Grana{
    private:
        UsmjereniGraf<TipOznake>* graf;
        int polazniCvor;
        int dolazniCvor;
    public:
        Grana(UsmjereniGraf<TipOznake>* g, int pc, int dc) { graf=g; polazniCvor=pc; dolazniCvor=dc;}
        float dajTezinu() const { return graf->dajTezinuGrane(polazniCvor, dolazniCvor); }
        void postaviTezinu(float tezina) { graf->postaviTezinuGrane(polazniCvor, dolazniCvor, tezina); }
        TipOznake dajOznaku() { return graf->dajOznakuGrane(polazniCvor, dolazniCvor); }
        void postaviOznaku(TipOznake oznaka) { graf->postaviOznakuGrane(polazniCvor, dolazniCvor, oznaka); }
        Cvor<TipOznake> dajPolazniCvor() const { return graf->dajCvor(polazniCvor); }
        Cvor<TipOznake> dajDolazniCvor() const { return graf->dajCvor(dolazniCvor); }
};


template <typename TipOznake>
class Cvor{
    private:
        UsmjereniGraf<TipOznake>* graf;
        int brojCvora;
    public:
        Cvor(UsmjereniGraf<TipOznake>* g, int bc) { graf=g; brojCvora=bc; }
        TipOznake dajOznaku() const { return graf->dajOznakuCvora(brojCvora); }
        void postaviOznaku(TipOznake oznaka) { graf->postaviOznakuCvora(brojCvora,oznaka); }
        int dajRedniBroj() const { return brojCvora; }
};

template <typename TipOznake>
class GranaIterator {
    private:
        UsmjereniGraf<TipOznake>* graf;
        int brojCvora1;
        int brojCvora2;
    public:
        GranaIterator(UsmjereniGraf<TipOznake>* g, int bc1, int bc2) { graf=g, brojCvora1=bc1, brojCvora2=bc2; }
        Grana<TipOznake> operator*() { return graf->dajGranu(brojCvora1,brojCvora2); }
        bool operator==(const GranaIterator &iter) const { return (brojCvora1==iter.brojCvora1 && brojCvora2==iter.brojCvora2 && graf==iter.graf); }
        bool operator!=(const GranaIterator &iter) const { return !(iter==*this); }
        GranaIterator& operator++();
        GranaIterator operator++(int);
};

template <typename TipOznake>
GranaIterator<TipOznake> &GranaIterator<TipOznake>::operator++(){
    do{
        if(brojCvora2 + 1>=graf->dajBrojCvorova()){
            brojCvora2=0;
            brojCvora1++;
        }
        else brojCvora2++;
    }
    while(!graf->postojiGrana(brojCvora1,brojCvora2) && brojCvora1<graf->dajBrojCvorova());
    return *this;
}

template <typename TipOznake>
GranaIterator<TipOznake> GranaIterator<TipOznake>::operator++(int){
    GranaIterator<TipOznake> temp=*this;
    ++(*this);
    return temp;
}

template <typename TipOznake>
class MatricaGraf : public UsmjereniGraf<TipOznake>{
    private:
        std::vector<std::vector<float>> matrica;
        std::vector<TipOznake> oznakeCvorova;
        std::vector<std::vector<TipOznake>> oznakeGrana;
        bool ispravnostCvora(int brojCvora) const { if(brojCvora<0 || brojCvora>=dajBrojCvorova()) return false; else return true; }
        bool ispravnostGrane(int polazniCvor, int dolazniCvor) const {  if(ispravnostCvora(polazniCvor) && ispravnostCvora(dolazniCvor)) return true; else return false; }
    public:
        MatricaGraf(int brojCvorova);
        ~MatricaGraf() { }
        int dajBrojCvorova() const { return matrica.size(); }
        void postaviBrojCvorova(int brojCvorova);
        void dodajGranu(int polazniCvor, int dolazniCvor, float  tezina=0);
        void obrisiGranu(int polazniCvor, int dolazniCvor);
        void postaviTezinuGrane(int polazniCvor, int dolazniCvor, float  tezina=0);
        float dajTezinuGrane(int polazniCvor, int dolazniCvor);
        bool postojiGrana(int polazniCvor, int dolazniCvor);
        void postaviOznakuCvora(int brojCvora, TipOznake oznaka);
        TipOznake dajOznakuCvora(int brojCvora);
        void postaviOznakuGrane(int polazniCvor, int dolazniCvor, TipOznake oznaka);
        TipOznake dajOznakuGrane(int polazniCvor, int dolazniCvor);
        Cvor<TipOznake> dajCvor(int brojCvora);
        Grana<TipOznake> dajGranu(int polazniCvor, int dolazniCvor);
};

template <typename TipOznake>
Grana<TipOznake> MatricaGraf<TipOznake>::dajGranu(int polazniCvor, int dolazniCvor){
    if(!ispravnostGrane(polazniCvor,dolazniCvor)) throw("Izuzetak");
    return Grana<TipOznake>(this,polazniCvor,dolazniCvor);
}

template <typename TipOznake>
Cvor<TipOznake> MatricaGraf<TipOznake>::dajCvor(int brojCvora){
    if(!ispravnostCvora(brojCvora)) throw("Izuzetak");
    return Cvor<TipOznake>(this,brojCvora);
}

template <typename TipOznake>
TipOznake MatricaGraf<TipOznake>::dajOznakuGrane(int polazniCvor, int dolazniCvor){
    if(!ispravnostGrane(polazniCvor,dolazniCvor)) throw("Izuzetak");
    return oznakeGrana[polazniCvor][dolazniCvor];
}

template <typename TipOznake>
void MatricaGraf<TipOznake>::postaviOznakuGrane(int polazniCvor, int dolazniCvor, TipOznake oznaka){
    if(!ispravnostGrane(polazniCvor,dolazniCvor)) throw("Izuzetak");
    oznakeGrana[polazniCvor][dolazniCvor]=oznaka;
}

template <typename TipOznake>
TipOznake MatricaGraf<TipOznake>::dajOznakuCvora(int brojCvora){
    if(!ispravnostCvora(brojCvora)) throw("Izuzetak");
    return oznakeCvorova[brojCvora];
}

template <typename TipOznake>
void MatricaGraf<TipOznake>::postaviOznakuCvora(int brojCvora, TipOznake oznaka){
    if(!ispravnostCvora(brojCvora)) throw("Izuzetak");
    oznakeCvorova[brojCvora]=oznaka;
}

template <typename TipOznake>
bool MatricaGraf<TipOznake>::postojiGrana(int polazniCvor, int dolazniCvor){
    if(ispravnostGrane(polazniCvor,dolazniCvor)) return matrica[polazniCvor][dolazniCvor]!=-1;
    else return false;
}

template <typename TipOznake>
float MatricaGraf<TipOznake>::dajTezinuGrane(int polazniCvor, int dolazniCvor){
    if(!ispravnostGrane(polazniCvor,dolazniCvor)) throw("Izuzetak");
    return matrica[polazniCvor][dolazniCvor];
}

template <typename TipOznake>
void MatricaGraf<TipOznake>::postaviTezinuGrane(int polazniCvor, int dolazniCvor, float  tezina){
    if(!ispravnostGrane(polazniCvor,dolazniCvor)) throw("Izuzetak");
    matrica[polazniCvor][dolazniCvor]=tezina;
}

template <typename TipOznake>
void MatricaGraf<TipOznake>::obrisiGranu(int polazniCvor, int dolazniCvor){
    if(!ispravnostGrane(polazniCvor,dolazniCvor)) throw("Izuzetak");
    matrica[polazniCvor][dolazniCvor]=-1;
}

template <typename TipOznake>
void MatricaGraf<TipOznake>::dodajGranu(int polazniCvor, int dolazniCvor, float  tezina){
    if(!ispravnostGrane(polazniCvor,dolazniCvor)) throw("Izuzetak");
    matrica[polazniCvor][dolazniCvor]=tezina;
}

template <typename TipOznake>
void MatricaGraf<TipOznake>::postaviBrojCvorova(int brojCvorova){
    if(brojCvorova<0) throw "Izuzetak";
    matrica.resize(brojCvorova);
    oznakeCvorova.resize(brojCvorova);
    oznakeGrana.resize(brojCvorova);
    for(int i=0; i<brojCvorova; i++){
        matrica[i].resize(brojCvorova,-1);
        oznakeGrana[i].resize(brojCvorova);
    }
}

template <typename TipOznake>
MatricaGraf<TipOznake>::MatricaGraf(int brojCvorova){
    if(brojCvorova<0) throw "Izuzetak";
    matrica.resize(brojCvorova);
    oznakeCvorova.resize(brojCvorova);
    oznakeGrana.resize(brojCvorova);
    for(int i=0; i<brojCvorova; i++){
        matrica[i].resize(brojCvorova,-1);
        oznakeGrana[i].resize(brojCvorova);
    }
}

template <typename TipOznake>
void bfs(UsmjereniGraf<TipOznake>* graf, std::vector<Cvor<TipOznake>>& bfs_obilazak, Cvor<TipOznake> cvor){
    cvor.postaviOznaku(true);
    bfs_obilazak.push_back(cvor);
    std::queue<Cvor<TipOznake>> red;
    red.push(cvor);
    while(!red.empty()){
        Cvor<TipOznake> temp=red.front();
        red.pop();
        for(GranaIterator<TipOznake> iter = graf->dajGranePocetak(); iter != graf->dajGraneKraj(); ++iter){
            if((*iter).dajPolazniCvor().dajRedniBroj()==temp.dajRedniBroj() && (*iter).dajDolazniCvor().dajOznaku()!=true){
                (*iter).dajDolazniCvor().postaviOznaku(true);
                bfs_obilazak.push_back((*iter).dajDolazniCvor());
                red.push((*iter).dajDolazniCvor());
            }
        }
    }
}  

template <typename TipOznake>
void dfs(UsmjereniGraf<TipOznake>* graf, std::vector<Cvor<TipOznake>>& dfs_obilazak, Cvor<TipOznake> cvor){
    cvor.postaviOznaku(true);
    dfs_obilazak.push_back(cvor);
    for(GranaIterator<TipOznake> iter = graf->dajGranePocetak(); iter != graf->dajGraneKraj(); ++iter){
        if((*iter).dajPolazniCvor().dajRedniBroj()==cvor.dajRedniBroj() && (*iter).dajDolazniCvor().dajOznaku()!=true) dfs(graf, dfs_obilazak, (*iter).dajDolazniCvor());
    }
} 

void AT19(){
    UsmjereniGraf<bool> *g = new MatricaGraf<bool>(6);
    g->dodajGranu(0, 1, 2.5);
    g->dodajGranu(1, 2, 1.2);
    g->dodajGranu(1, 3, 0.1);
    g->dodajGranu(2, 4, 3.14);
    g->dodajGranu(2, 3, 2.73);
    g->dodajGranu(3, 5, 1);
    g->dodajGranu(5, 2, -5.0);
    std::vector<Cvor<bool> > dfs_obilazak;
    dfs(g, dfs_obilazak, g->dajCvor(0));
    for (int i = 0; i < dfs_obilazak.size(); i++) std::cout << dfs_obilazak[i].dajRedniBroj() << ",";
    delete g;
    std::cout << std::endl << "Treba ispisati: " << std::endl;
    std::cout << "0,1,2,3,5,4," << std::endl;
    std::cout << "0,1,2,4,3,5," << std::endl;
}

void AT20(){
    UsmjereniGraf<bool> *g = new MatricaGraf<bool>(6);
    g->dodajGranu(0, 1, 2.5);
    g->dodajGranu(1, 2, 1.2);
    g->dodajGranu(1, 3, 0.1);
    g->dodajGranu(2, 4, 3.14);
    g->dodajGranu(2, 3, 2.73);
    g->dodajGranu(3, 5, 1);
    g->dodajGranu(5, 2, -5.0);
    std::vector<Cvor<bool> > bfs_obilazak;
    bfs(g, bfs_obilazak, g->dajCvor(0));
    for (int i = 0; i < bfs_obilazak.size(); i++) std::cout << bfs_obilazak[i].dajRedniBroj() << ",";
    delete g;
    std::cout << std::endl << "Treba ispisati: " << std::endl;
    std::cout << "0,1,2,3,4,5," << std::endl;
}

int main() {
    AT20();
    return 0;
}
