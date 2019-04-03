#include <iostream>
#include <string>
#include <time.h>

template <typename TipKljuca, typename TipVrijednosti>
class Mapa{
    public:
        Mapa() {}
        virtual ~Mapa() {}
        virtual TipVrijednosti operator [](TipKljuca k) const =0;
        virtual TipVrijednosti &operator [](TipKljuca k) =0;
        virtual int brojElemenata()const =0;
        virtual void obrisi() =0;
        virtual void obrisi(const TipKljuca& k) =0;
};


template <typename TipKljuca, typename TipVrijednosti>
struct Pair{
    TipKljuca kljuc;
    TipVrijednosti vrijednost;
};

template <typename TipKljuca, typename TipVrijednosti>
class NizMapa : public Mapa<TipKljuca, TipVrijednosti>{
    private:
        Pair<TipKljuca,TipVrijednosti>* niz;
        int velicina=0;
        int kapacitet=500;
    public:
        NizMapa() { niz = new Pair<TipKljuca,TipVrijednosti>[kapacitet];  }
        ~NizMapa() { delete []niz; }
        int brojElemenata() const { return velicina; }
        void obrisi();
        void obrisi(const TipKljuca& k);
        TipVrijednosti operator [](TipKljuca k) const;
        TipVrijednosti &operator [](TipKljuca k);
        NizMapa(const NizMapa<TipKljuca,TipVrijednosti> &temp);
        NizMapa(NizMapa<TipKljuca,TipVrijednosti> &&temp);
        NizMapa& operator=(const NizMapa<TipKljuca,TipVrijednosti> &temp);
        NizMapa& operator=(NizMapa<TipKljuca,TipVrijednosti> &&temp);
};


template <typename TipKljuca, typename TipVrijednosti>
NizMapa<TipKljuca,TipVrijednosti>& NizMapa<TipKljuca,TipVrijednosti>::operator=(const NizMapa<TipKljuca,TipVrijednosti> &temp){
    if(&temp==this) return *this;
    kapacitet=temp.kapacitet;
    velicina=temp.velicina;
    delete[] niz;
    niz = new Pair<TipKljuca,TipVrijednosti>[kapacitet];
    for(int i=0; i<velicina; i++){
        niz[i]=temp.niz[i];
    }
    return *this;
}

template <typename TipKljuca, typename TipVrijednosti>
NizMapa<TipKljuca,TipVrijednosti>& NizMapa<TipKljuca,TipVrijednosti>::operator=(NizMapa<TipKljuca,TipVrijednosti> &&temp){
    if(&temp==this) return *this;
    kapacitet=temp.kapacitet;
    velicina=temp.velicina;
    delete []niz;
    niz=temp.niz;
    return *this;
}


template <typename TipKljuca, typename TipVrijednosti>
NizMapa<TipKljuca,TipVrijednosti>::NizMapa(const NizMapa<TipKljuca,TipVrijednosti> &temp){
    kapacitet=temp.kapacitet;
    velicina=temp.velicina;
    niz = new Pair<TipKljuca,TipVrijednosti>[kapacitet];
    for(int i=0; i<velicina; i++){
        niz[i]=temp.niz[i];
    }
}

template <typename TipKljuca, typename TipVrijednosti>
NizMapa<TipKljuca,TipVrijednosti>::NizMapa(NizMapa<TipKljuca,TipVrijednosti> &&temp){
    kapacitet=temp.kapacitet;
    velicina=temp.velicina;
    niz=temp.niz;
}

template <typename TipKljuca, typename TipVrijednosti>
TipVrijednosti& NizMapa<TipKljuca, TipVrijednosti>::operator [](TipKljuca k){
    for(int i=0; i<velicina; i++){
        if(niz[i].kljuc==k) return niz[i].vrijednost;
    }
    if(velicina<kapacitet){
        niz[velicina].kljuc=k;
        niz[velicina].vrijednost=TipVrijednosti();
        velicina++;
        return niz[velicina-1].vrijednost;
    }
    else{
        Pair<TipKljuca,TipVrijednosti>* temp = new Pair<TipKljuca,TipVrijednosti>[kapacitet*2];
        kapacitet*=2;
        for(int i=0; i<velicina; i++) temp[i]=niz[i];
        delete []niz;
        niz=temp;
        niz[velicina].kljuc=k;
        niz[velicina].vrijednost=TipVrijednosti();
        velicina++;
        return niz[velicina-1].vrijednost;
    }
}


template <typename TipKljuca, typename TipVrijednosti>
TipVrijednosti NizMapa<TipKljuca, TipVrijednosti>::operator [](TipKljuca k) const{
    for(int i=0; i<velicina; i++){
        if(niz[i].kljuc==k) return niz[i].vrijednost;
    }
    return TipVrijednosti();
}

template <typename TipKljuca, typename TipVrijednosti>
void NizMapa<TipKljuca, TipVrijednosti>::obrisi(const TipKljuca& k){
    if(velicina==0) throw "Izuzetak" ;
    for(int i=0; i<velicina; i++){
        if(niz[i].kljuc==k){
            for(int j=i; j<velicina-1; j++) niz[i]=niz[i+1];
            velicina--;
            return;
        }
    }
    throw "Izuzetak" ;
}

template <typename TipKljuca, typename TipVrijednosti>
void NizMapa<TipKljuca, TipVrijednosti>::obrisi(){
    delete []niz;
    velicina=0;
    kapacitet=500;
    niz = new Pair<TipKljuca,TipVrijednosti>[kapacitet];
}

template <typename TipKljuca, typename TipVrijednosti>
struct Cvor{
    TipKljuca kljuc;
    TipVrijednosti vrijednost;
    Cvor* lijevo;
    Cvor* desno;
    Cvor* roditelj;
};

template <typename TipKljuca, typename TipVrijednosti>
class BinStabloMapa : public Mapa<TipKljuca, TipVrijednosti>{
    private:
        int velicina=0;
        Cvor<TipKljuca, TipVrijednosti>* korijen;
        void preorder(Cvor<TipKljuca, TipVrijednosti>* pok, Cvor<TipKljuca, TipVrijednosti>* &pok1, Cvor<TipKljuca, TipVrijednosti>* pok2=nullptr);
    public:
        BinStabloMapa() { korijen=nullptr; }
        ~BinStabloMapa() { this->obrisi(); }
        int brojElemenata() const { return velicina; }
        void obrisi();
        void obrisi(const TipKljuca& k);
        TipVrijednosti operator [](TipKljuca k) const;
        TipVrijednosti &operator [](TipKljuca k);
        BinStabloMapa(const BinStabloMapa<TipKljuca,TipVrijednosti> &temp);
        BinStabloMapa(BinStabloMapa<TipKljuca,TipVrijednosti> &&temp);
        BinStabloMapa& operator=(const BinStabloMapa<TipKljuca,TipVrijednosti> &temp);
        BinStabloMapa& operator=(BinStabloMapa<TipKljuca,TipVrijednosti> &&temp);
        void foo(){ preorder(korijen); }
};

template <typename TipKljuca, typename TipVrijednosti>
void BinStabloMapa<TipKljuca,TipVrijednosti>::preorder(Cvor<TipKljuca, TipVrijednosti>* pok, Cvor<TipKljuca, TipVrijednosti>* &pok1, Cvor<TipKljuca, TipVrijednosti>* pok2){
    if(pok!=nullptr){
        pok1=new Cvor<TipKljuca, TipVrijednosti>();
        pok1->kljuc=pok->kljuc;
        pok1->vrijednost=pok->vrijednost;
        pok1->roditelj=pok2;
        preorder(pok->lijevo, pok1->lijevo, pok2);
        preorder(pok->desno, pok1->desno, pok2);
    }
}

template <typename TipKljuca, typename TipVrijednosti>
BinStabloMapa<TipKljuca,TipVrijednosti>::BinStabloMapa(const BinStabloMapa<TipKljuca,TipVrijednosti> &temp){
    velicina=temp.velicina;
    preorder(temp.korijen, korijen);
}

template <typename TipKljuca, typename TipVrijednosti>
BinStabloMapa<TipKljuca,TipVrijednosti>& BinStabloMapa<TipKljuca,TipVrijednosti>::operator=(const BinStabloMapa<TipKljuca,TipVrijednosti> &temp){
    if(&temp==this) return *this;
    this->obrisi();
    velicina=temp.velicina;
    preorder(temp.korijen, korijen);
    return *this;
}

template <typename TipKljuca, typename TipVrijednosti>
BinStabloMapa<TipKljuca,TipVrijednosti>& BinStabloMapa<TipKljuca,TipVrijednosti>::operator=(BinStabloMapa<TipKljuca,TipVrijednosti> &&temp){
    if(&temp==this) return *this;
    this->obrisi();
    velicina=temp.velicina;
    korijen=temp.korijen;
    return *this;
}

template <typename TipKljuca, typename TipVrijednosti>
BinStabloMapa<TipKljuca,TipVrijednosti>::BinStabloMapa(BinStabloMapa<TipKljuca,TipVrijednosti> &&temp){
    velicina=temp.velicina;
    korijen=temp.korijen;
}

template <typename TipKljuca, typename TipVrijednosti>
TipVrijednosti &BinStabloMapa<TipKljuca, TipVrijednosti>::operator [](TipKljuca k){
    Cvor<TipKljuca, TipVrijednosti>* temp=korijen;
    while(temp!=nullptr && k!=temp->kljuc){
        if(k>temp->kljuc) temp=temp->desno;
        else temp=temp->lijevo;
    }
    if(temp==nullptr){
        temp=new Cvor<TipKljuca, TipVrijednosti>();
        temp->kljuc=k;
        temp->vrijednost=TipVrijednosti();
        velicina++;
        Cvor<TipKljuca, TipVrijednosti>* walker=korijen;
        Cvor<TipKljuca, TipVrijednosti>* walker1=nullptr;
        while(walker!=nullptr){
            walker1=walker;
            if(temp->kljuc>walker->kljuc)walker=walker->desno;
            else walker=walker->lijevo;
        }
        if(walker1==nullptr) korijen=temp;
        else{
            if(temp->kljuc>walker1->kljuc) walker1->desno=temp;
            else walker1->lijevo=temp;
            temp->roditelj=walker1;
        }
    }
    return temp->vrijednost;
}

template <typename TipKljuca, typename TipVrijednosti>
TipVrijednosti BinStabloMapa<TipKljuca, TipVrijednosti>::operator[] (TipKljuca k) const{
    Cvor<TipKljuca, TipVrijednosti>* walker=korijen;
    while(walker!=nullptr && k!=walker->kljuc){
        if(k>walker->kljuc) walker=walker->desno;
        else walker=walker->lijevo;
    }
    if(walker==nullptr) return TipVrijednosti();
    return walker->vrijednost;
}

template <typename TipKljuca, typename TipVrijednosti>
void BinStabloMapa<TipKljuca, TipVrijednosti>::obrisi(){
    while(korijen!=nullptr) obrisi(korijen->kljuc);
}


template <typename TipKljuca, typename TipVrijednosti>
void BinStabloMapa<TipKljuca, TipVrijednosti>::obrisi(const TipKljuca& k){
    velicina=velicina-1;
    Cvor<TipKljuca, TipVrijednosti>* p=korijen;
    Cvor<TipKljuca, TipVrijednosti>* r=nullptr;
    while(p!=nullptr && k!=p->kljuc){
        r=p;
        if(k<p->kljuc) p=p->lijevo;
        else p=p->desno;
    }
    if(p==nullptr) throw "Izuzetak";
    Cvor<TipKljuca, TipVrijednosti>* m=nullptr;
    if(p->lijevo==nullptr) m=p->desno;
    else{
        if(p->desno==nullptr) m=p->lijevo;
        else{
            Cvor<TipKljuca, TipVrijednosti>* pm=p;
            m=p->lijevo;
            Cvor<TipKljuca, TipVrijednosti>* tmp=m->desno;
            while(tmp!=nullptr){
                pm=m;
                m=tmp;
                tmp=m->desno;
            }
            if(pm!=p){
                pm->desno=m->lijevo;
                m->lijevo=p->lijevo;
            }
            m->desno=p->desno;
        }
    }
    if(r==nullptr) korijen=m;
    else{
        if(p==r->lijevo) r->lijevo=m;
        else r->desno=m;
    }
    delete p;
}

void Test(){
    BinStabloMapa<int,int> m;
    NizMapa<int,int> m1;
    int a=rand();
    int b=rand();
    m[a]=b;
    m1[a]=b;
    clock_t vrijeme1 = clock();
    for(int i=0; i<10000; i++){
        int random=rand();
        int random1=rand();
        m[random]=random1;
    }
    clock_t vrijeme2 = clock();
    int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja dodavanja el BinStabloMapa: " << ukvrijeme << " ms." << std::endl;
    vrijeme1 = clock();
    for(int i=0; i<10000; i++){
        int random=rand();
        int random1=rand();
        m1[random]=random1;
    }
    vrijeme2 = clock();
    ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja dodavanja el NizMapa: " << ukvrijeme << " ms." << std::endl;
    vrijeme1 = clock();
    std::cout << "Random el BinStabloMapa: " <<m[a] << std::endl;
    vrijeme2 = clock();
    ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja pristupa random el BinStabloMapa: " << ukvrijeme << " ms." << std::endl;
    vrijeme1 = clock();
    std::cout << "Random el NizMapa: " <<m1[a] << std::endl;
    vrijeme2 = clock();
    ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja pristupa random el NizMapa: " << ukvrijeme << " ms." << std::endl;
    
    /*
    
    Vrijeme izvrsenja dodavanja el BinStabloMapa: 61 ms.
    Vrijeme izvrsenja dodavanja el NizMapa: 2349 ms.
    
    Kao sto vidimo BinStabloMapa puno brze dodaje elemente nego Niz mapa , jer se u nizmapi stalno vrsi realokacija za veliki broj elemenata
    
    Random el BinStabloMapa: 846930886
    Vrijeme izvrsenja pristupa random el BinStabloMapa: 1 ms.
    Random el NizMapa: 846930886
    Vrijeme izvrsenja pristupa random el NizMapa: 1 ms.
    
    Kao sto vidimo vrijeme pristupa za random element je otprilike isto
    
    */
}


void BinStabloMapaBrojElemenata(){
    try{
        BinStabloMapa<std::string,std::string> m;
        m["BiH"] = "Sarajevo";
        m["Cro"] = "Zagreb";
        m["Srb"] = "Beograd";
        std::cout << m.brojElemenata() << std::endl;
    }
    catch(...){
        throw;
    }
}

void BinStabloMapaObrisi(){
    try{
        BinStabloMapa<std::string,std::string> m;
        m["BiH"] = "Sarajevo";
        m["Cro"] = "Zagreb";
        m["Srb"] = "Beograd";
        std::cout << m.brojElemenata() << " ";
        m.obrisi();
        std::cout << m.brojElemenata() << std::endl;
    }
    catch(...){
        throw;
    }
}

void BinStabloMapaObrisiKljuc(){
    try{
        BinStabloMapa<std::string,std::string> m;
        m["BiH"] = "Sarajevo";
        m["Cro"] = "Zagreb";
        m["Srb"] = "Beograd";
        std::cout << m.brojElemenata() << " ";
        m.obrisi("Cro");
        std::cout << m.brojElemenata() << std::endl;
    }
    catch(...){
        throw;
    }
}

void BinStabloMapaObrisiKljucIzuzetak(){
    try{
        BinStabloMapa<std::string,std::string> m;
        m["BiH"] = "Sarajevo";
        m["Cro"] = "Zagreb";
        m["Srb"] = "Beograd";
        m.obrisi("Slo");
    }
    catch(...){
        throw;
    }
}

void BinStabloMapaOperatorUglaste(){
    try{
        BinStabloMapa<std::string,std::string> m;
        m["BiH"] = "Sarajevo";
        m["Cro"] = "Zagreb";
        m["Srb"] = "Beograd";
        m["Slo"] ;
        m["Slo"] = "Ljubljana";
        std::cout << m.brojElemenata() << std::endl;
    }
    catch(...){
        throw;
    }
}

void BinStabloMapaOperatorUglasteConst(){
    try{
        BinStabloMapa<std::string,std::string> m;
        m["BiH"] = "Sarajevo";
        m["Cro"] = "Zagreb";
        m["Srb"] = "Beograd";
        std::cout << m["BiH"] << std::endl;
    }
    catch(...){
        throw;
    }
}

void BinStabloMapaOperatorDodjele(){
    try{
        BinStabloMapa<std::string,std::string> m;
        m["BiH"] = "Sarajevo";
        m["Cro"] = "Zagreb";
        m["Srb"] = "Beograd";
        BinStabloMapa<std::string,std::string> k;
        k=m;
        std::cout << k.brojElemenata() << std::endl;
    }
    catch(...){
        throw;
    }
}


void BinStabloMapaKobstruktor(){
    try{
        BinStabloMapa<std::string,std::string> m;
        m["BiH"] = "Sarajevo";
        m["Cro"] = "Zagreb";
        m["Srb"] = "Beograd";
        BinStabloMapa<std::string,std::string> k(m);
        std::cout << k.brojElemenata() << std::endl;
    }
    catch(...){
        throw;
    }
}

void BinStabloMapaTest(){
    try{
        BinStabloMapaBrojElemenata();
        BinStabloMapaObrisi();
        BinStabloMapaObrisiKljuc();
        BinStabloMapaOperatorUglaste();
        BinStabloMapaOperatorUglasteConst();
        BinStabloMapaOperatorDodjele();
        BinStabloMapaObrisiKljucIzuzetak();
    }
    catch(...){
        throw;
    }
}


int main() {
    try{
        Test();
        //BinStabloMapaTest();
    }
    catch(...){
        std::cout << "Izuzetak";
    }
    return 0;
}
