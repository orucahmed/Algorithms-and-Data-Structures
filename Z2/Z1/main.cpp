#include <iostream>
#include <stdexcept>

template <typename Tip>
struct Cvor{
    Tip vrijednost;
    Cvor* sljedeci;
    Cvor* prethodni;
};

template <typename Tip>
class DvostraniRed{
    private:
        Cvor<Tip>* prvi;
        Cvor<Tip>* posljednji;
        int velicina;
    public:
        DvostraniRed() { velicina=0; prvi=nullptr; posljednji =nullptr; }
        DvostraniRed(const DvostraniRed &temp);
        DvostraniRed(DvostraniRed &&temp);
        DvostraniRed& operator=(const DvostraniRed &temp);
        DvostraniRed& operator=(DvostraniRed &&temp);
        ~DvostraniRed() { this->brisi(); }
        void brisi();
        int brojElemenata() { return velicina; }
        void staviNaVrh(const Tip& el);
        Tip skiniSaVrha();
        void staviNaCelo(const Tip& el);
        Tip skiniSaCela();
        Tip& vrh() { if(velicina==0) throw "Izuzetak"; return posljednji ->vrijednost; }
        Tip& celo() { if(velicina==0) throw "Izuzetak"; return prvi->vrijednost; }
};

template <typename Tip>
DvostraniRed<Tip>::DvostraniRed(const DvostraniRed &temp){
    Cvor<Tip>*pok = temp.prvi;
    prvi=new Cvor<Tip>();
    prvi->prethodni=nullptr;
    prvi->vrijednost=pok->vrijednost;
    pok=pok->sljedeci;
    Cvor<Tip>*pok1=new Cvor<Tip>();
    pok1->vrijednost=pok->vrijednost;
    pok1->prethodni=prvi;
    prvi->sljedeci=pok1;
    pok=pok->sljedeci;
    while(pok!=temp.posljednji ){
        Cvor<Tip>* pok2 = new Cvor<Tip>();
        pok2->vrijednost=pok->vrijednost;
        pok2->prethodni=pok1;
        pok1->sljedeci=pok2;
        pok1=pok2;
        pok=pok->sljedeci;
    }
    Cvor<Tip>* pok2 = new Cvor<Tip>();
    pok2->vrijednost=temp.posljednji ->vrijednost;
    pok1->sljedeci=pok2;
    pok2->prethodni=pok1;
    pok2->sljedeci=nullptr;
    posljednji=pok2;
    velicina=temp.velicina;
}

template <typename Tip>
DvostraniRed<Tip>::DvostraniRed(DvostraniRed &&temp){
    prvi=temp.prvi;
    posljednji=temp.prvi;
    velicina=temp.velicina;
}

template <typename Tip>
DvostraniRed<Tip>& DvostraniRed<Tip>::operator=(const DvostraniRed &temp){
    if(this==&temp) return *this;
    this->brisi();
    Cvor<Tip>*pok = temp.prvi;
    prvi=new Cvor<Tip>();
    prvi->prethodni=nullptr;
    prvi->vrijednost=pok->vrijednost;
    pok=pok->sljedeci;
    Cvor<Tip>*pok1=new Cvor<Tip>();
    pok1->vrijednost=pok->vrijednost;
    pok1->prethodni=prvi;
    prvi->sljedeci=pok1;
    pok=pok->sljedeci;
    while(pok!=temp.posljednji){
        Cvor<Tip>* pok2 = new Cvor<Tip>();
        pok2->vrijednost=pok->vrijednost;
        pok2->prethodni=pok1;
        pok1->sljedeci=pok2;
        pok1=pok2;
        pok=pok->sljedeci;
    }
    Cvor<Tip>* pok2 = new Cvor<Tip>();
    pok2->vrijednost=temp.posljednji ->vrijednost;
    pok1->sljedeci=pok2;
    pok2->prethodni=pok1;
    pok2->sljedeci=nullptr;
    posljednji=pok2;
    velicina=temp.velicina;
    return *this;
}

template <typename Tip>
DvostraniRed<Tip>& DvostraniRed<Tip>::operator=(DvostraniRed &&temp){
    if(this==&temp) return *this;
    this->brisi();
    prvi=temp.prvi;
    posljednji=temp.prvi;
    velicina=temp.velicina;
    return *this;
}

template <typename Tip>
Tip DvostraniRed<Tip>::skiniSaCela(){
    if(velicina==0) throw "Izuzetak";
    Cvor<Tip>* pok=prvi;
    prvi=prvi->sljedeci;
    Tip temp = pok->vrijednost;
    delete pok;
    velicina--;
    return temp;
}

template <typename Tip>
Tip DvostraniRed<Tip>::skiniSaVrha(){
    if(velicina==0) throw "Izuzetak";
    Cvor<Tip>* pok=posljednji;
    posljednji=posljednji->prethodni;
    Tip temp = pok->vrijednost;
    delete pok;
    velicina--;
    return temp;
}

template <typename Tip>
void DvostraniRed<Tip>::brisi(){
    while(velicina!=0){
        Cvor<Tip>* pok=prvi;
        prvi=prvi->sljedeci;
        delete pok;
        velicina--;
    }
}

template <typename Tip>
void DvostraniRed<Tip>::staviNaCelo(const Tip& el){
    if(velicina==0){
        prvi = new Cvor<Tip>();
        prvi->vrijednost=el;
        prvi->prethodni=nullptr;
        prvi->sljedeci=nullptr;
        posljednji=prvi;
    }
    else{
        Cvor<Tip>* temp = new Cvor<Tip>();
        temp->vrijednost=el;
        temp->prethodni=nullptr;
        temp->sljedeci=prvi;
        prvi->prethodni=temp;
        prvi=temp;
    }
    velicina++;
}

template <typename Tip>
void DvostraniRed<Tip>::staviNaVrh(const Tip& el){
    if(velicina==0){
        posljednji = new Cvor<Tip>();
        posljednji->vrijednost=el;
        posljednji->prethodni=nullptr;
        posljednji->sljedeci=nullptr;
        prvi=posljednji;
    }
    else{
        Cvor<Tip>* temp = new Cvor<Tip>();
        temp->vrijednost=el;
        temp->sljedeci=nullptr;
        temp->prethodni=posljednji;
        posljednji->sljedeci=temp;
        posljednji=temp;
    }
    velicina++;
}

void DvostraniRedKonstruktorKopije(){
    try{
        DvostraniRed<int> d;
        for(int i=0; i<5; i++) d.staviNaCelo(i);
        DvostraniRed<int> d1(d);
        std::cout << d1.brojElemenata() << std::endl;
    }
    catch(...){
        throw;
    }
}
void DvostraniRedOperatorDodjele(){
    try{
        DvostraniRed<int> d;
        for(int i=0; i<5; i++) d.staviNaCelo(i);
        DvostraniRed<int> d1;
        d1=d;
        std::cout << d1.brojElemenata() << std::endl;
    }
    catch(...){
        throw;
    }
}
void DvostraniRedBrisi(){
    try{
        DvostraniRed<int> d;
        for(int i=0; i<5; i++) d.staviNaCelo(i);
        d.brisi();
        std::cout << d.brojElemenata() << std::endl;
    }
    catch(...){
        throw;
    }
}
void DvostraniRedBrojElemenata(){
    try{
        DvostraniRed<int> d;
        for(int i=0; i<5; i++) d.staviNaCelo(i);
        std::cout << d.brojElemenata() << std::endl;
    }
    catch(...){
        throw;
    }
}
void DvostraniRedStaviNaVrh(){
    try{
        DvostraniRed<int> d;
        for(int i=0; i<5; i++) d.staviNaVrh(i);
        std::cout << d.brojElemenata() << std::endl;
    }
    catch(...){
        throw;
    }
}
void DvostraniRedSkiniSaVrha(){
    try{
        DvostraniRed<int> d;
        for(int i=0; i<5; i++) d.staviNaCelo(i);
        std::cout << d.skiniSaVrha() << std::endl;
    }
    catch(...){
        throw;
    }
}
void DvostraniRedStaviNaCelo(){
    try{
        DvostraniRed<int> d;
        for(int i=0; i<5; i++) d.staviNaCelo(i);
        std::cout << d.skiniSaVrha() << std::endl;
    }
    catch(...){
        throw;
    }
}
void DvostraniRedSkiniSaCela(){
    try{
        DvostraniRed<int> d;
        for(int i=0; i<5; i++) d.staviNaCelo(i);
        std::cout << d.skiniSaCela() << std::endl;
    }
    catch(...){
        throw;
    }
}
void DvostraniRedVrh(){
    try{
        DvostraniRed<int> d;
        for(int i=0; i<5; i++) d.staviNaCelo(i);
        std::cout << d.vrh() << std::endl;
    }
    catch(...){
        throw;
    }
}
void DvostraniRedCelo(){
    try{
        DvostraniRed<int> d;
        for(int i=0; i<5; i++) d.staviNaCelo(i);
        std::cout << d.celo() << std::endl;
    }
    catch(...){
        throw;
    }
}

void DvostraniRedTest(){
    try{
        std::cout << "Test DvostraniRed" << std::endl;
        DvostraniRedKonstruktorKopije();
        DvostraniRedOperatorDodjele();
        DvostraniRedBrisi();
        DvostraniRedBrojElemenata();
        DvostraniRedStaviNaVrh();
        DvostraniRedSkiniSaVrha();
        DvostraniRedStaviNaCelo();
        DvostraniRedSkiniSaCela();
        DvostraniRedVrh();
        DvostraniRedCelo();
        std::cout << "Kraj testa DvostraniRed" << std::endl;
    }
    catch(...){
        
    }
}

int main(){
    try{
        DvostraniRedTest();
    }
    catch(std::domain_error poruka){
        std::cout << poruka.what() << std::endl;
    }
    catch(std::range_error poruka){
        std::cout << poruka.what() << std::endl;
    }
    catch(std::logic_error poruka){
        std::cout << poruka.what() << std::endl;
    }
    catch(...){
        std::cout << "Izuzetak";
    }
    return 0;
}
