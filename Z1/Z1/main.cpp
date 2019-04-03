#include <iostream>
#include <stdexcept>

template <typename Tip>
class Iterator;

template <typename Tip>
class Lista{
    public:
        Lista() {}
        virtual ~Lista() {}
        virtual int brojElemenata()const =0;
        virtual Tip trenutni() const =0;
        virtual bool prethodni() =0;
        virtual bool sljedeci() =0;
        virtual Tip &trenutni() =0;
        virtual void obrisi() =0;
        virtual void pocetak() =0;
        virtual void kraj() =0;
        virtual void dodajIspred(const Tip& el)=0;
        virtual void dodajIza(const Tip& el) =0;
        virtual Tip operator [](int i) const =0;
        virtual Tip &operator [](int i) =0;

};

template <typename Tip>
struct Cvor{
    Tip vrijednost;
    Cvor* sljedeci;
    Cvor* prethodni;
};

template <typename Tip>
class DvostrukaLista : public Lista<Tip>{
    private:
        Cvor<Tip>* prvi;
        Cvor<Tip>* posljedni;
        Cvor<Tip>* element;
        int velicina=0;
    public:
        DvostrukaLista() : Lista<Tip>(), prvi(nullptr), posljedni(nullptr), element(nullptr) { }
        ~DvostrukaLista();
        int brojElemenata() const { return velicina; }
        Tip trenutni() const { if(velicina==0) throw "Izuzetak"; return element->vrijednost; }
        bool prethodni();
        bool sljedeci();
        Tip &trenutni() { if(velicina==0) throw "Izuzetak"; return element->vrijednost; }
        void obrisi();
        void pocetak() { if(velicina==0) throw "Izuzetak"; element=prvi; }
        void kraj() { if(velicina==0) throw "Izuzetak"; element=posljedni; }
        void dodajIspred(const Tip& el);
        void dodajIza(const Tip& el);
        Tip operator [](int i) const;
        Tip &operator [](int i);
        DvostrukaLista(const DvostrukaLista<Tip> &temp);
        DvostrukaLista(DvostrukaLista<Tip> &&temp);
        DvostrukaLista& operator =(const DvostrukaLista<Tip> &temp);
        DvostrukaLista& operator =(DvostrukaLista<Tip> &&temp);
        friend class Iterator<Tip>;
};

template <typename Tip>
DvostrukaLista<Tip>::DvostrukaLista(const DvostrukaLista<Tip> &temp){
    Cvor<Tip>*pok = temp.prvi;
    prvi=new Cvor<Tip>();
    prvi->prethodni=nullptr;
    prvi->vrijednost=pok->vrijednost;
    if(pok==temp.element) element=prvi;
    pok=pok->sljedeci;
    Cvor<Tip>*pok1=new Cvor<Tip>();
    pok1->vrijednost=pok->vrijednost;
    pok1->prethodni=prvi;
    prvi->sljedeci=pok1;
    if(pok==temp.element) element=pok1;
    pok=pok->sljedeci;
    while(pok!=temp.posljedni){
        Cvor<Tip>* pok2 = new Cvor<Tip>();
        pok2->vrijednost=pok->vrijednost;
        pok2->prethodni=pok1;
        pok1->sljedeci=pok2;
        pok1=pok2;
        if(pok==temp.element) element=pok1;
        pok=pok->sljedeci;
    }
    Cvor<Tip>* pok2 = new Cvor<Tip>();
    pok2->vrijednost=temp.posljedni->vrijednost;
    pok1->sljedeci=pok2;
    pok2->prethodni=pok1;
    pok2->sljedeci=nullptr;
    if(pok==temp.element) element=pok1;
    velicina=temp.velicina;
}

template <typename Tip>
DvostrukaLista<Tip>::DvostrukaLista(DvostrukaLista<Tip> &&temp){
    prvi=temp.prvi;
    posljedni=temp.posljedni;
    velicina=temp.velicina;
    element=temp.velicina;
}

template <typename Tip>
DvostrukaLista<Tip> &DvostrukaLista<Tip>::operator=(const DvostrukaLista<Tip> &temp){
    if(&temp==this) return *this;
    while(velicina!=0){
        element=prvi;
        prvi=prvi->sljedeci;
        delete element;
        element=nullptr;
        velicina--;
    }
    Cvor<Tip>*pok = temp.prvi;
    prvi=new Cvor<Tip>();
    prvi->prethodni=nullptr;
    prvi->vrijednost=pok->vrijednost;
    if(pok==temp.element) element=prvi;
    pok=pok->sljedeci;
    Cvor<Tip>*pok1=new Cvor<Tip>();
    pok1->vrijednost=pok->vrijednost;
    pok1->prethodni=prvi;
    prvi->sljedeci=pok1;
    if(pok==temp.element) element=pok1;
    pok=pok->sljedeci;
    while(pok!=temp.posljedni){
        Cvor<Tip>* pok2 = new Cvor<Tip>();
        pok2->vrijednost=pok->vrijednost;
        pok2->prethodni=pok1;
        pok1->sljedeci=pok2;
        pok1=pok2;
        if(pok==temp.element) element=pok1;
        pok=pok->sljedeci;
    }
    Cvor<Tip>* pok2 = new Cvor<Tip>();
    pok2->vrijednost=temp.posljedni->vrijednost;
    pok1->sljedeci=pok2;
    pok2->prethodni=pok1;
    pok2->sljedeci=nullptr;
    if(pok==temp.element) element=pok1;
    velicina=temp.velicina;
    return *this;
}

template <typename Tip>
DvostrukaLista<Tip> &DvostrukaLista<Tip>::operator=(DvostrukaLista<Tip> &&temp){
    if(&temp==this) return *this;
    while(velicina!=0){
        element=prvi;
        prvi=prvi->sljedeci;
        delete element;
        element=nullptr;
        velicina--;
    }
    velicina=temp.velicina;
    prvi=temp.prvi;
    posljedni=temp.posljedni;
    element=temp.element;
    return *this;
}

template <typename Tip>
Tip DvostrukaLista<Tip>::operator [](int i) const{
    if(i<0 || i>velicina) throw "Izuzetak";
    if(i<velicina/2){
        Cvor<Tip>* pok = prvi;
        for(int j=0; j<i; j++) pok=pok->sljedeci;
        return pok->vrijednost;
    }
    else{
        i=velicina-i-1;
        Cvor<Tip>* pok = posljedni;
        for(int j=0; j<i; j++) pok=pok->prethodni;
        return pok->vrijednost;
    }
}

template <typename Tip>
Tip& DvostrukaLista<Tip>::operator [](int i) {
    if(i<0 || i>velicina) throw "Izuzetak";
    Cvor<Tip>* pok = prvi;
    for(int j=0; j<i; j++) pok=pok->sljedeci;
    return pok->vrijednost;
}

template <typename Tip>
DvostrukaLista<Tip>::~DvostrukaLista(){
    while(velicina!=0){
        element=prvi;
        prvi=prvi->sljedeci;
        delete element;
        element=nullptr;
        velicina--;
    }
}

template <typename Tip>
void DvostrukaLista<Tip>::dodajIspred(const Tip& el){
    Cvor<Tip>* pok= new Cvor<Tip>();
    pok->vrijednost=el;
    if(velicina==0){
        prvi=pok;
        posljedni=pok;
        element=pok;
        prvi->sljedeci=nullptr;
        prvi->prethodni=nullptr;
    }
    else if(element==prvi){
        prvi->prethodni=pok;
        pok->sljedeci=prvi;
        pok->prethodni=nullptr;
        prvi=prvi->prethodni;
    }
    else{
        Cvor<Tip>*pok1 = element->prethodni;
        pok1->sljedeci=pok;
        element->prethodni=pok;
        pok->sljedeci=element;
        pok->prethodni=pok1;
    }
    velicina++;
} 

template <typename Tip>
void DvostrukaLista<Tip>::dodajIza(const Tip& el){
    Cvor<Tip>* pok= new Cvor<Tip>();
    pok->vrijednost=el;
    if(velicina==0){
        prvi=pok;
        posljedni=pok;
        element=pok;
        pok->sljedeci=nullptr;
        pok->prethodni=nullptr;
    }
    else if(element==posljedni){
        posljedni->sljedeci=pok;
        pok->prethodni=posljedni;
        pok->sljedeci=nullptr;
        posljedni=posljedni->sljedeci;
    }
    else{
        Cvor<Tip>* pok1=element->sljedeci;
        pok1->prethodni=pok;
        pok->sljedeci=pok1;
        element->sljedeci=pok;
        pok->prethodni=element;
    }
    velicina++;
}

template <typename Tip>
bool DvostrukaLista<Tip>::prethodni(){
    if(velicina==0) throw "Izuzetak";
    if(element==prvi) return false;
    else element=element->prethodni;
    return true;
}

template <typename Tip>
bool DvostrukaLista<Tip>::sljedeci(){
    if(velicina==0) throw "Izuzetak";
    if(element==posljedni) return false;
    else element=element->sljedeci;
    return true;
}

template <typename Tip>
void DvostrukaLista<Tip>::obrisi(){
    if(velicina==0) throw "Izuzetak";
    else if(element==posljedni){
        element=element->prethodni;
        delete posljedni;
        posljedni=element;
    }
    else if(element==prvi){
        element=element->sljedeci;
        delete prvi;
        prvi=element;
    }
    else{
        Cvor<Tip>* pok = element->prethodni;
        Cvor<Tip>* pok1 = element;
        element=element->sljedeci;
        pok->sljedeci=element;
        element->prethodni=pok;
        delete pok1;
    }
    velicina--;
}

template <typename Tip>
class Iterator{
    private:
        const Lista<Tip>* lista;
        int broj;
        Cvor<Tip> *prviLista;
        Cvor<Tip> *zadnjLista;
    public:
        Iterator(const DvostrukaLista<Tip>& temp) { lista=&temp; prviLista=temp.prvi; zadnjLista=temp.posljedni; broj=0; }
        Iterator(const Lista<Tip>& temp) { lista=&temp; prviLista=nullptr; zadnjLista=nullptr; broj=1; }
        bool sljedeci();
        Tip trenutni() { if(broj==0) return prviLista->vrijednost; return (*lista)[broj-1]; }
};

template <typename Tip>
bool Iterator<Tip>::sljedeci(){
    if(broj==0){
        if(prviLista==zadnjLista) return false;
        prviLista=prviLista->sljedeci;
        return true;
    }
    else{
        if(broj==lista->brojElemenata()) return false;
        broj++;
        return true;
    }
}

template <typename Tip>
Tip dajMaksimum(const Lista<Tip>& n){
    Iterator<Tip> iter(n);
    Tip max=iter.trenutni();
    while(iter.sljedeci()){
        Tip temp=iter.trenutni();
        if(temp>max) max=temp;
    }
    return max;
}

void ListaKopirajuciKonstruktor(){
    try{
        DvostrukaLista<int> n;
        for(int i=1; i<=10; i++) n.dodajIza(i);
        DvostrukaLista<int> l(n);
        std::cout << l.brojElemenata() << std::endl;
    }
    catch(...){
        throw;
    }
}

void ListaBrojElemenata(){
    try{
        DvostrukaLista<int> n;
        for(int i=1; i<=10; i++) n.dodajIza(i);
        std::cout << n.brojElemenata() << std::endl;
    }
    catch(...){
        throw;
    }
}

void ListaTrenutniCOnst(){
    try{
        DvostrukaLista<int> n;
        for(int i=1; i<=10; i++) n.dodajIza(i);
        std::cout << n.trenutni() << std::endl;
    }
    catch(...){
        throw;
    }
}

void ListaTrenutni(){
    try{
        DvostrukaLista<int> n;
        for(int i=1; i<=10; i++) n.dodajIza(i);
        n.trenutni()=33;
        std::cout << n.trenutni() << std::endl;
    }
    catch(...){
        throw;
    }
}

void ListaPredhodni(){
    try{
        DvostrukaLista<int> n;
        for(int i=1; i<=10; i++) n.dodajIspred(i);
        n.prethodni();
        std::cout << n.trenutni() << std::endl;
    }
    catch(...){
        throw;
    }
}

void ListaSljedeci(){
    try{
        DvostrukaLista<int> n;
        for(int i=1; i<=10; i++) n.dodajIza(i);
        n.sljedeci();
        std::cout << n.trenutni() << std::endl;
    }
    catch(...){
        throw;
    }
}

void ListaObrisi(){
    try{
        DvostrukaLista<int> n;
        for(int i=1; i<=10; i++) n.dodajIza(i);
        n.obrisi();
        std::cout << n.brojElemenata() << std::endl;
    }
    catch(...){
        throw;
    }
}
void ListaPocetak(){
    try{
        DvostrukaLista<int> n;
        for(int i=1; i<=10; i++) n.dodajIspred(i);
        n.pocetak();
        std::cout << n.trenutni() << std::endl;
    }
    catch(...){
        throw;
    }
}

void ListaKraj(){
    try{
        DvostrukaLista<int> n;
        for(int i=1; i<=10; i++) n.dodajIza(i);
        n.kraj();
        std::cout << n.trenutni() << std::endl;
    }
    catch(...){
        throw;
    }
}

void ListaOperatorUglasteConst(){
    try{
        DvostrukaLista<int> n;
        for(int i=1; i<=10; i++) n.dodajIspred(i);
        std::cout << n[5] << std::endl;
    }
    catch(...){
        throw;
    }
}

void ListaOperatorUglaste(){
    try{
        DvostrukaLista<int> n;
        for(int i=1; i<=10; i++) n.dodajIspred(i);
        n[5]=33;
        std::cout << n[5] << std::endl;
    }
    catch(...){
        throw;
    }
}

void ListaOperatorDodjele(){
    try{
        DvostrukaLista<int> n;
        for(int i=1; i<=10; i++) n.dodajIspred(i);
        DvostrukaLista<int> l; 
        l=n;
        std::cout << l.brojElemenata() << std::endl;
    }
    catch(...){
        throw;
    }
}

void ListaTest(){
    try{
        std::cout << "Test DvostrukaLista" << std::endl;
        ListaBrojElemenata();
        ListaKopirajuciKonstruktor();
        ListaKraj();
        ListaObrisi();
        ListaOperatorDodjele();
        ListaOperatorUglaste();
        ListaOperatorUglasteConst();
        ListaPocetak();
        ListaPredhodni();
        ListaSljedeci();
        ListaTrenutni();
        ListaTrenutniCOnst();
        std::cout << "Kraj testa DvostrukaLista" << std::endl;
    }
    catch(...){
        throw;
    }
}

void DajMaxSortiranoRastuce(){
    DvostrukaLista<int> l;
    for(int i=0; i<10000; i++) l.dodajIspred(i);
    std::cout << dajMaksimum(l) << std::endl;
}

void DajMaxSortiranoOpadajuce(){
    DvostrukaLista<int> l;
    for(int i=0; i<10000; i++) l.dodajIza(i);
    std::cout << dajMaksimum(l) << std::endl;
    
}

void DajMaxTest(){
    try{
        std::cout << "Test dajMaksimum" << std::endl;
        DajMaxSortiranoOpadajuce();
        DajMaxSortiranoRastuce();
        std::cout << "Kraj testa dajMaksimum" << std::endl;
    }
    catch(...){
        throw;
    }
}

int main(){
    try{
        ListaTest();
        DajMaxTest();
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