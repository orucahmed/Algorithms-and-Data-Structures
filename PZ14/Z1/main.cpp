#include <iostream>
#include <stdexcept>

template <typename Tip>
struct Cvor{
    Tip vrijednost;
    Cvor* sljedeci;
};

template <typename Tip>
class Red{
    private:
        int velicina=0;
        Cvor<Tip>* prvi;
        Cvor<Tip>* posljednji;
    public:
        Red() { prvi=nullptr; posljednji=nullptr; }
        ~Red() { this->brisi(); }
        Red(const Red &temp);
        Red(Red &&temp);
        Red& operator =(const Red &temp);
        Red& operator =(Red &&temp);
        void brisi();
        void stavi(const Tip& el);
        Tip skini();
        Tip& celo() { return prvi->vrijednost; }
        int brojElemenata() { return velicina; }
};

template <typename Tip>
Red<Tip>::Red(const Red &temp){
    Cvor<Tip>* pok=temp.prvi;
    prvi=new Cvor<Tip>();
    prvi->vrijednost=pok->vrijednost;
    posljednji=prvi;
    pok=pok->sljedeci;
    while(pok!=nullptr){
        posljednji->sljedeci=new Cvor<Tip>();
        posljednji->sljedeci->vrijednost=pok->vrijednost;
        posljednji=posljednji->sljedeci;
        pok=pok->sljedeci;
    }
    velicina=temp.velicina;
}

template <typename Tip>
Red<Tip>::Red(Red &&temp){
    prvi=temp.prvi;
    posljednji=temp.posljednji;
    velicina=temp.velicina;
}

template <typename Tip>
Red<Tip>& Red<Tip>::operator=(const Red &temp){
    if(this==&temp) return *this;
    this->brisi();
    Cvor<Tip>* pok=temp.prvi;
    prvi=new Cvor<Tip>();
    prvi->vrijednost=pok->vrijednost;
    posljednji=prvi;
    pok=pok->sljedeci;
    while(pok!=nullptr){
        posljednji->sljedeci=new Cvor<Tip>();
        posljednji->sljedeci->vrijednost=pok->vrijednost;
        posljednji=posljednji->sljedeci;
        pok=pok->sljedeci;
    }
    velicina=temp.velicina;
    return *this;
}

template <typename Tip>
Red<Tip>& Red<Tip>::operator=(Red &&temp){
    if(this==&temp) return *this;
    this->brisi();
    prvi=temp.prvi;
    posljednji=temp.posljednji;
    velicina=temp.velicina;
    return *this;
}

template <typename Tip>
void Red<Tip>::stavi(const Tip& el){
    if(velicina==0){
        prvi=new Cvor<Tip>();
        prvi->vrijednost=el;
        prvi->sljedeci=nullptr;
        posljednji=prvi;
    }
    else{
        Cvor<Tip>* temp = new Cvor<Tip>();
        temp->sljedeci=nullptr;
        temp->vrijednost=el;
        posljednji->sljedeci=temp;
        posljednji=temp;
    }
    velicina++;
}

template <typename Tip>
Tip Red<Tip>::skini(){
    if(velicina==0) throw "Izuzetak";
    Tip el=prvi->vrijednost;
    Cvor<Tip>* temp = prvi;
    prvi=prvi->sljedeci;
    delete temp;
    velicina--;
    return el;
}

template <typename Tip>
void Red<Tip>::brisi(){
    while(prvi!=nullptr){
        Cvor<Tip>* pok=prvi;
        prvi=prvi->sljedeci;
        delete pok;
    }
    velicina=0;
}

void RedKopirajuciKonstruktor(){
    try{
        Red<int> s;
        for (int i(1); i<=5; i++) s.stavi(i);
        Red<int> l(s);
        std::cout << l.brojElemenata() << std::endl;
    }
    catch(...){
        throw;
    }
}

void RedOperatorDodjele(){
    try{
        Red<int> s;
        for (int i(1); i<=5; i++) s.stavi(i);
        Red<int> l;
        l=s;
        std::cout << l.brojElemenata() << std::endl;
    }
    catch(...){
        throw;
    }    
}

void RedBrisi(){
    try{
        Red<int> s;
        for (int i(1); i<=5; i++) s.stavi(i);
        std::cout << s.brojElemenata() << std::endl;
        s.brisi();
        std::cout << s.brojElemenata() << std::endl;
    }
    catch(...){
        throw;
    }
}

void RedStavi(){
    try{
        Red<int> s;
        for (int i(1); i<=5; i++) s.stavi(i);
        std::cout << s.brojElemenata() << std::endl;
    }
    catch(...){
        throw;
    }
}

void RedSini(){
    try{
        Red<int> s;
        for (int i(1); i<=5; i++) s.stavi(i);
        std::cout << s.skini() << std::endl;
    }
    catch(...){
        throw;
    }
}

void RedVrh(){
    try{
        Red<int> s;
        for (int i(1); i<=5; i++) s.stavi(i);
        std::cout << s.celo() << std::endl;
    }
    catch(...){
        throw;
    }
}

void RedBrojElemenata(){
   try{
        Red<int> s;
        for (int i(1); i<=5; i++) s.stavi(i);
        std::cout << s.brojElemenata() << std::endl;
    }
    catch(...){
        throw;
    } 
}


void RedTest(){
    try{
        RedBrisi();
        RedBrojElemenata();
        RedKopirajuciKonstruktor();
        RedOperatorDodjele();
        RedStavi();
        RedSini();
        RedVrh();
    }
    catch(...){
        throw;
    }
}

int main(){
    try{
        RedTest();
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
