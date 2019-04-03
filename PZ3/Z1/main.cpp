#include <iostream>
#include <stdexcept>

template <typename Tip>
struct Cvor{
    Tip vrijednost;
    Cvor* sljedeci;
};

template <typename Tip>
class Stek{
    private:
        int velicina=0;
        Cvor<Tip>* prvi;
    public:
        Stek() { velicina=0; prvi=nullptr; }
        ~Stek();
        Stek(const Stek &temp);
        Stek(Stek &&temp);
        Stek& operator =(const Stek &temp);
        Stek& operator =(Stek &&temp);
        void brisi();
        void stavi(const Tip& el);
        Tip skini();
        Tip& vrh() { return prvi->vrijednost; }
        int brojElemenata() { return velicina; }
};

template <typename Tip>
Stek<Tip>::Stek(const Stek &temp){
    Cvor<Tip>* pok = temp.prvi;
    prvi=new Cvor<Tip> ();
    prvi->vrijednost=pok->vrijednost;
    Cvor<Tip>*pok1 = prvi;
    pok=pok->sljedeci;
    while(pok!=nullptr){
       pok1->sljedeci=new Cvor<Tip>();
       pok1->sljedeci->vrijednost=pok->vrijednost;
       pok=pok->sljedeci;
       pok1=pok1->sljedeci;
    }
    velicina=temp.velicina;
}

template <typename Tip>
Stek<Tip>::Stek(Stek &&temp){
    prvi=temp.prvi;
    velicina=temp.velicina;
}

template <typename Tip>
Stek<Tip>& Stek<Tip>::operator=(Stek &&temp){
    if(this==&temp) return *this;
    this->brisi();
    prvi=temp.prvi;
    velicina=temp.velicina;
    return *this;
}

template <typename Tip>
Stek<Tip>& Stek<Tip>::operator=(const Stek &temp){
    if(this==&temp) return *this;
    this->brisi();
    Cvor<Tip>* pok = temp.prvi;
    prvi=new Cvor<Tip> ();
    prvi->vrijednost=pok->vrijednost;
    Cvor<Tip>*pok1 = prvi;
    pok=pok->sljedeci;
    while(pok!=nullptr){
       pok1->sljedeci=new Cvor<Tip>();
       pok1->sljedeci->vrijednost=pok->vrijednost;
       pok=pok->sljedeci;
       pok1=pok1->sljedeci;
    }
    velicina=temp.velicina;
    return *this;
}

template <typename Tip>
Stek<Tip>::~Stek(){
    Cvor<Tip>* pok=prvi;
    while(pok!=nullptr){
        prvi=pok->sljedeci;
        delete pok;
        pok=prvi;
    }
    delete prvi;
}

template <typename Tip>
void Stek<Tip>::brisi(){
    Cvor<Tip>* pok=prvi;
    while(pok!=nullptr){
        prvi=pok->sljedeci;
        delete pok;
        pok=prvi;
    }
    delete prvi;
    velicina=0;
}

template <typename Tip>
Tip Stek<Tip>::skini(){
    if(velicina==0) throw "Izuzetak!";
    Tip el = prvi->vrijednost;
    Cvor<Tip>* pok = prvi;
    prvi=prvi->sljedeci;
    velicina--;
    delete pok;
    return el;
}

template <typename Tip>
void Stek<Tip>::stavi(const Tip& el){
    if(velicina==0){
        prvi = new Cvor<Tip>();
        prvi->vrijednost=el;
        prvi->sljedeci=nullptr;
        velicina++;
    }
    else{
        Cvor<Tip>* pok = new Cvor<Tip>();
    pok->vrijednost=el;
    pok->sljedeci=prvi;
    prvi=pok;
    velicina++;
    }
}


void StekKopirajuciKonstruktor(){
    try{
        Stek<int> s;
        for (int i(1); i<=5; i++) s.stavi(i);
        Stek<int> l(s);
        std::cout << l.brojElemenata() << std::endl;
    }
    catch(...){
        throw;
    }
}

void StekOperatorDodjele(){
    try{
        Stek<int> s;
        for (int i(1); i<=5; i++) s.stavi(i);
        Stek<int> l;
        l=s;
        std::cout << l.brojElemenata() << std::endl;
    }
    catch(...){
        throw;
    }    
}

void StekBrisi(){
    try{
        Stek<int> s;
        for (int i(1); i<=5; i++) s.stavi(i);
        std::cout << s.brojElemenata() << std::endl;
        s.brisi();
        std::cout << s.brojElemenata() << std::endl;
    }
    catch(...){
        throw;
    }
}

void StekStavi(){
    try{
        Stek<int> s;
        for (int i(1); i<=5; i++) s.stavi(i);
        std::cout << s.brojElemenata() << std::endl;
    }
    catch(...){
        throw;
    }
}

void StekSini(){
    try{
        Stek<int> s;
        for (int i(1); i<=5; i++) s.stavi(i);
        std::cout << s.skini() << std::endl;
    }
    catch(...){
        throw;
    }
}

void StekVrh(){
    try{
        Stek<int> s;
        for (int i(1); i<=5; i++) s.stavi(i);
        std::cout << s.vrh() << std::endl;
    }
    catch(...){
        throw;
    }
}

void StekBrojElemenata(){
   try{
        Stek<int> s;
        for (int i(1); i<=5; i++) s.stavi(i);
        std::cout << s.brojElemenata() << std::endl;
    }
    catch(...){
        throw;
    } 
}


void StekTest(){
    try{
        StekBrisi();
        StekBrojElemenata();
        StekKopirajuciKonstruktor();
        StekOperatorDodjele();
        StekStavi();
        StekSini();
        StekVrh();
    }
    catch(...){
        throw;
    }
}

int main(){
    try{
        StekTest();
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