#include <iostream>
#include <stdexcept>

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
class NizLista : public Lista<Tip>{
    private:
        Tip* prvi;
        Tip* posljedni;
        Tip* element;
        int kapacitet=490;
        int velicina=0;
    public:
        NizLista(const NizLista<Tip> &temp);
        NizLista(NizLista<Tip> &&temp);
        NizLista() { prvi = new Tip[kapacitet]; element=prvi; posljedni=prvi; }
        ~NizLista() { delete []prvi; }
        int brojElemenata() const { return velicina; }
        Tip trenutni() const { if(velicina==0) throw "Izuzetak"; return *element; }
        bool prethodni();
        bool sljedeci();
        Tip &trenutni() { if(velicina==0) throw "Izuzetak"; return *element; }
        void obrisi();
        void pocetak() { if(velicina==0) throw "Izuzetak"; element=prvi; }
        void kraj() { if(velicina==0) throw "Izuzetak"; element=posljedni; }
        void dodajIspred(const Tip& el);
        void dodajIza(const Tip& el);
        Tip operator [](int i) const;
        Tip &operator [](int i);
        NizLista& operator=(const NizLista<Tip> &temp);
        NizLista& operator=(NizLista<Tip> &&temp);

};

template <typename Tip>
NizLista<Tip> &NizLista<Tip>::operator=(const NizLista<Tip> &temp){
    if(&temp==this) return *this;
    kapacitet=temp.kapacitet;
    velicina=temp.velicina;
    delete[] prvi;
    prvi=new Tip[kapacitet];
    for(int i=0; i<=velicina; i++){
        prvi[i]=temp[i];
    }
    posljedni=&prvi[velicina-1];
    element=&prvi[temp.element-temp.prvi+1];
    return *this;
}

template <typename Tip>
NizLista<Tip> &NizLista<Tip>::operator=(NizLista<Tip> &&temp){
    if(&temp==this) return *this;
    kapacitet=temp.kapacitet;
    velicina=temp.velicina;
    delete []prvi;
    prvi=temp.prvi;
    posljedni=temp.posljedni;
    element=temp.element;
    return *this;
}

template <typename Tip>
NizLista<Tip>::NizLista(const NizLista<Tip> &temp){
    kapacitet=temp.kapacitet;
    velicina=temp.velicina;
    prvi=new Tip[kapacitet];
    for(int i=0; i<=velicina; i++){
        prvi[i]=temp[i];
    }
    posljedni=&prvi[velicina-1];
    element=&prvi[temp.element-temp.prvi+1];
}

template <typename Tip>
NizLista<Tip>::NizLista(NizLista<Tip> &&temp){
    kapacitet=temp.kapacitet;
    velicina=temp.velicina;
    prvi=temp.prvi;
    posljedni=temp.posljedni;
    element=temp.element;
}

template <typename Tip>
Tip NizLista<Tip>::operator [](int i) const{
    return *(prvi+i);
}

template <typename Tip>
Tip& NizLista<Tip>::operator [](int i){
    return *(prvi+i);
}

template <typename Tip>
bool NizLista<Tip>::prethodni(){
    if(velicina==0) throw "Izuzetak";
    if(element==prvi) return false;
    element--;
    return true;
}

template <typename Tip>
bool NizLista<Tip>::sljedeci(){
    if(velicina==0) throw "Izuzetak";
    if(element==posljedni) return false;
    element++;
    return true;
}

template <typename Tip>
void NizLista<Tip>::obrisi(){
    if(velicina==0) throw "Izuzetak" ;
    Tip* temp = element;
    while(temp<=posljedni){
        *temp=*(temp+1);
        temp++;
    }
    velicina--;
    posljedni--;
}

template <typename Tip>
void NizLista<Tip>::dodajIspred(const Tip& el){
    if(velicina==0){
        *prvi=el;
        posljedni=prvi;
        element=prvi;
        velicina++;
        return;
    }
    if(velicina==kapacitet){
        Tip* temp = new Tip[kapacitet*2];
        kapacitet*=2;
        Tip* temp1 = prvi;
        Tip* temp2 = temp;
        int index=element-prvi;
        while(temp1!=posljedni){
            *temp=*temp1;
            temp++;
            temp1++;
        }
        element=temp2+index-1;
        *temp=*temp1;
        posljedni=temp;
        delete[] prvi;
        prvi = temp2;
    }
    Tip* temp=posljedni;
    while(temp!=element){
            *(temp+1)=*temp;
            temp--;
        }
    posljedni++;
    *(element+1)=*element;
    *element=el;
    element++;
    velicina++;
}

template <typename Tip>
void NizLista<Tip>::dodajIza(const Tip& el){
    if(velicina==0){
        *prvi=el;
        posljedni=prvi;
        element=prvi;
        velicina++;
        return;
    }
    if(velicina==kapacitet){
        Tip* temp = new Tip[kapacitet*2];
        kapacitet*=2;
        Tip* temp1 = prvi;
        Tip* temp2 = temp;
        int index=element-prvi;
        while(temp1!=posljedni){
            *temp=*temp1;
            temp++;
            temp1++;
        }
        element=temp2+index-1;
        *temp=*temp1;
        posljedni=temp;
        delete[] prvi;
        prvi = temp2;
    }
    Tip* temp=posljedni;
    while(temp!=element){
        *(temp+1)=*temp;
        temp--;
    }
    posljedni++;
    *(element+1)=el;
    velicina++;
}

template <typename Tip>
struct Cvor{
    Tip vrijednost;
    Cvor* sljedeci;
};

template <typename Tip>
class JednostrukaLista : public Lista<Tip>{
    private:
        Cvor<Tip>* prvi;
        Cvor<Tip>* posljedni;
        Cvor<Tip>* element;
        int velicina=0;
    public:
        JednostrukaLista() : Lista<Tip>(), prvi(nullptr), posljedni(nullptr), element(nullptr) { }
        ~JednostrukaLista();
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
        JednostrukaLista(const JednostrukaLista<Tip> &temp);
        JednostrukaLista(JednostrukaLista<Tip> &&temp);
        JednostrukaLista& operator =(const JednostrukaLista<Tip> &temp);
        JednostrukaLista& operator =(JednostrukaLista<Tip> &&temp);
};

template <typename Tip>
JednostrukaLista<Tip>::JednostrukaLista(const JednostrukaLista<Tip> &temp){
    int brojac=0;
    Cvor<Tip>* pokazivac = temp.prvi;
    while(pokazivac!=temp.element){
        brojac++;
        pokazivac=pokazivac->sljedeci;
    }
    velicina=temp.velicina;
    Cvor<Tip>* pok = new Cvor<Tip>();
    pok->vrijednost=temp[0];
    pok->sljedeci=nullptr;
    prvi=pok;
    Cvor<Tip>*pok2=temp.prvi;
    pok2=pok2->sljedeci;
    if(brojac==0) element=prvi;
    for(int i=1; i<velicina-1; i++){
        Cvor<Tip>* pok1 = new Cvor<Tip>();
        pok1->vrijednost=pok2->vrijednost;
        pok2=pok2->sljedeci;
        pok1->sljedeci=nullptr;
        pok->sljedeci=pok1;
        pok=pok1;
        if(brojac==i) element=pok;
    }
}

template <typename Tip>
JednostrukaLista<Tip>::JednostrukaLista(JednostrukaLista<Tip> &&temp){
    prvi=temp.prvi;
    posljedni=temp.posljedni;
    velicina=temp.velicina;
    element=temp.velicina;
}

template <typename Tip>
JednostrukaLista<Tip> &JednostrukaLista<Tip>::operator=(const JednostrukaLista<Tip> &temp){
    if(&temp==this) return *this;
    while(prvi!=nullptr){
        element=prvi;
        prvi=prvi->sljedeci;
        delete element;
        element=nullptr;
    }
    int brojac=0;
    Cvor<Tip>* pokazivac = temp.prvi;
    while(pokazivac!=temp.element){
        brojac++;
        pokazivac=pokazivac->sljedeci;
    }
    velicina=temp.velicina;
    Cvor<Tip>* pok = new Cvor<Tip>();
    pok->vrijednost=temp.prvi->vrijednost;
    Cvor<Tip>*pok2=temp.prvi;
    pok2=pok2->sljedeci;
    pok->sljedeci=nullptr;
    prvi=pok;
    if(brojac==0) element=prvi;
    for(int i=1; i<velicina-1; i++){
        Cvor<Tip>* pok1 = new Cvor<Tip>();
        pok1->vrijednost=pok2->vrijednost;
        pok2=pok2->sljedeci;
        pok1->sljedeci=nullptr;
        pok->sljedeci=pok1;
        pok=pok1;
        if(brojac==i) element=pok;
    }
    return *this;
}

template <typename Tip>
JednostrukaLista<Tip> &JednostrukaLista<Tip>::operator=(JednostrukaLista<Tip> &&temp){
    if(&temp==this) return *this;
    velicina=temp.velicina;
    delete []prvi;
    prvi=temp.prvi;
    posljedni=temp.posljedni;
    element=temp.element;
    return *this;
}

template <typename Tip>
Tip JednostrukaLista<Tip>::operator [](int i) const{
    Cvor<Tip>* temp = prvi;
    for(int j=0; j<i; j++){
        temp=temp->sljedeci;
    }
    return temp->vrijednost;
}

template <typename Tip>
Tip& JednostrukaLista<Tip>::operator [](int i) {
    Cvor<Tip>* temp = prvi;
    for(int j=0; j<i; j++){
        temp=temp->sljedeci;
    }
    return temp->vrijednost;
}

template <typename Tip>
void JednostrukaLista<Tip>::dodajIza(const Tip& el){
    Cvor<Tip> * temp = new Cvor<Tip>();
    temp->vrijednost=el;
    if(velicina==0){
        temp->sljedeci=nullptr;
        prvi=posljedni=element=temp;
    }
    else if(element==posljedni){
        element->sljedeci=temp;
        temp->sljedeci=nullptr;
        posljedni=temp;
    }
    else{
        Cvor<Tip> * temp1 = element->sljedeci;
        element->sljedeci=temp;
        temp->sljedeci=temp1;
    }
    velicina++;
}

template <typename Tip>
void JednostrukaLista<Tip>::dodajIspred(const Tip& el){
    Cvor<Tip> * temp = new Cvor<Tip>();
    temp->vrijednost=el;
    if(velicina==0){
        temp->sljedeci=nullptr;
        prvi=posljedni=element=temp;
    }
    else if(element==prvi){
        temp->sljedeci=prvi;
        prvi=temp;
    }
    else{
        Cvor<Tip>* prije = prvi;
        while(prije->sljedeci!=element){
            prije=prije->sljedeci;
        }
        prije->sljedeci=temp;
        temp->sljedeci=element;
    }
    
    velicina++;
}


template <typename Tip>
JednostrukaLista<Tip>::~JednostrukaLista(){
    while(prvi!=nullptr){
        element=prvi;
        prvi=prvi->sljedeci;
        delete element;
        element=nullptr;
    }
}

template <typename Tip>
bool JednostrukaLista<Tip>::sljedeci(){
    if(element==posljedni) return false;
    element=element->sljedeci;
    return true;
}

template <typename Tip>
bool JednostrukaLista<Tip>::prethodni(){
    if(element==prvi) return false;
    Cvor<Tip>* temp = prvi;
    while(temp->sljedeci!=element){
        temp=temp->sljedeci;
    }
    element=temp;
    return true;
}

template <typename Tip>
void JednostrukaLista<Tip>::obrisi(){
    if(element==prvi){
        prvi=prvi->sljedeci;
        delete element;
        element=prvi;
    }
    else{
        Cvor<Tip>* temp = prvi;
        while(temp->sljedeci!=element) temp=temp->sljedeci;
        temp->sljedeci=element->sljedeci;
        delete element;
        if(temp->sljedeci==nullptr){
            element=temp;
            posljedni=temp;
        }
        else{
            element=temp->sljedeci;
        }
    }
    velicina--;
}

void testNizLista(){
    try{
        std::cout << "Test NizLista: " << std::endl;
        NizLista<int> lista;
        for (int i(1); i<=10000; i++)lista.dodajIspred(i);
        std::cout << lista.brojElemenata() << " ";
        for(int i(0);i<=100;i++) {
            lista.prethodni();
        }
        std::cout << lista.trenutni() << " ";
        for(int i(0);i<50;i++) {
            lista.sljedeci();
        }
        std::cout << lista.trenutni() << " ";
        lista.pocetak();
        std::cout << lista.trenutni() << " ";
        lista.kraj();
        std::cout << lista.trenutni() << " ";
        std::cout << lista[20] << " ";
        for (int i(1); i<=10000; i++) lista.obrisi();
        std::cout << lista.brojElemenata() << std::endl;
        for (int i(1); i<=10000; i++)
    	    lista.dodajIza(i);
        std::cout << lista.brojElemenata() << " ";
        for(int i(0);i<=100;i++) {
            lista.sljedeci();
        }
        std::cout << lista.trenutni() << " ";
        for(int i(0);i<50;i++) {
            lista.prethodni();
        }
        std::cout << lista.trenutni() << " ";
        lista.pocetak();
        std::cout << lista.trenutni() << " ";
        lista.kraj();
        std::cout << lista.trenutni() << " ";
        std::cout << lista[20] << " ";
        for (int i(1); i<=10000; i++) lista.obrisi();
        std::cout << lista.brojElemenata() << std::endl;
        std::cout << "Kraj testa!" << std::endl<< std::endl;
    }
    catch(...){
        throw;
    }
}

void testJednostrukaLista(){
    try{
        std::cout << "Test JednostrukaLista: "<< std::endl;
        JednostrukaLista<int> jlista;
        for (int i(1); i<=10000; i++)
	    jlista.dodajIspred(i);
        std::cout << jlista.brojElemenata() << " ";
        for(int i(0);i<=100;i++) {
            jlista.prethodni();
        }
        std::cout << jlista.trenutni() << " ";
        for(int i(0);i<50;i++) {
            jlista.sljedeci();
        }
        std::cout << jlista.trenutni() << " ";
        jlista.pocetak();
        std::cout << jlista.trenutni() << " ";
        jlista.kraj();
        std::cout << jlista.trenutni() << " ";
        std::cout << jlista[20] << " ";
        for (int i(1); i<=10000; i++) jlista.obrisi();
        std::cout << jlista.brojElemenata() << std::endl;
        for (int i(1); i<=10000; i++) jlista.dodajIza(i);
        std::cout << jlista.brojElemenata() << " ";
        for(int i(0);i<=100;i++) {
            jlista.sljedeci();
        }
        std::cout << jlista.trenutni() << " ";
        for(int i(0);i<50;i++) {
            jlista.prethodni();
        }
        std::cout << jlista.trenutni() << " ";
        jlista.pocetak();
        std::cout << jlista.trenutni() << " ";
        jlista.kraj();
        std::cout << jlista.trenutni() << " ";
        std::cout << jlista[20] << " ";
        for (int i(1); i<=10000; i++) jlista.obrisi();
        std::cout << jlista.brojElemenata() << std::endl;
        std::cout << "Kraj testa!" << std::endl << std::endl;
    }
    catch(...){
        throw;
    }
}

void Test3(){
    std::cout << "Test broj 3" << std::endl;
    JednostrukaLista<int> lista;
    for (int i(1); i<=5; i++)
    lista.dodajIspred(i);
    JednostrukaLista<int> lista2(lista);
    JednostrukaLista<int> lista3;
    lista3=lista;
    lista.obrisi();
    std::cout << lista2.brojElemenata();
    std::cout << " " << lista3.brojElemenata() << " ";
    std::cout << lista.brojElemenata();
    std::cout << std::endl << "Treba biti :5 5 4 " << std:: endl << "Obratiti paznju na memorijske greske! Kraj testa!" << std::endl << std::endl;
}

void Test15(){
    std::cout << "Test broj 15" << std::endl;
    NizLista<int> n;
    n.dodajIza(5);
    const int& x(n[0]); 
    n.dodajIspred(10);
    std::cout << x;
    std::cout << std::endl << "Treba biti :5" << std::endl << "Kraj testa!" << std::endl << std::endl;
}

int main(){
    try{
        testNizLista();
        testJednostrukaLista();
        Test3();
        Test15();
        
        
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