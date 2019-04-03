#include <iostream>
#include <string>
#include <time.h>

using namespace std;

unsigned int nekihash(int ulaz, unsigned int max) {
	return max-1;
}

unsigned int glupihas(int ulaz, unsigned int max) {
	return max-1;
}


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
    TipKljuca kljuc=TipKljuca();
    TipVrijednosti vrijednost=TipVrijednosti();
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


template <typename TipKljuca, typename TipVrijednosti>
class HashMapa : public Mapa<TipKljuca, TipVrijednosti>{
    private:
        Pair<TipKljuca,TipVrijednosti>* niz;
        int velicina=0;
        int kapacitet=500;
        unsigned int (*foo)(TipKljuca, unsigned int)=0;
    public:
        HashMapa() { niz = new Pair<TipKljuca,TipVrijednosti>[kapacitet];  }
        ~HashMapa() { delete []niz; }
        int brojElemenata() const { return velicina; }
        void obrisi();
        void obrisi(const TipKljuca& k);
        TipVrijednosti operator [](TipKljuca k) const;
        TipVrijednosti &operator [](TipKljuca k);
        HashMapa(const HashMapa<TipKljuca,TipVrijednosti> &temp);
        HashMapa(HashMapa<TipKljuca,TipVrijednosti> &&temp);
        HashMapa& operator=(const HashMapa<TipKljuca,TipVrijednosti> &temp);
        HashMapa& operator=(HashMapa<TipKljuca,TipVrijednosti> &&temp);
        void definisiHashFunkciju(unsigned int (*funkcija)(TipKljuca, unsigned int)) { foo=funkcija; }
};



template <typename TipKljuca, typename TipVrijednosti>
HashMapa<TipKljuca,TipVrijednosti>& HashMapa<TipKljuca,TipVrijednosti>::operator=(const HashMapa<TipKljuca,TipVrijednosti> &temp){
    if(&temp==this) return *this;
    foo=temp.foo;
    kapacitet=temp.kapacitet;
    velicina=temp.velicina;
    delete[] niz;
    niz = new Pair<TipKljuca,TipVrijednosti>[kapacitet];
    for(int i=0; i<kapacitet; i++){
        niz[i]=temp.niz[i];
    }
    return *this;
}

template <typename TipKljuca, typename TipVrijednosti>
HashMapa<TipKljuca,TipVrijednosti>& HashMapa<TipKljuca,TipVrijednosti>::operator=(HashMapa<TipKljuca,TipVrijednosti> &&temp){
    if(&temp==this) return *this;
    foo=temp.foo;
    kapacitet=temp.kapacitet;
    velicina=temp.velicina;
    delete []niz;
    niz=temp.niz;
    return *this;
}


template <typename TipKljuca, typename TipVrijednosti>
HashMapa<TipKljuca,TipVrijednosti>::HashMapa(const HashMapa<TipKljuca,TipVrijednosti> &temp){
    kapacitet=temp.kapacitet;
    foo=temp.foo;
    velicina=temp.velicina;
    niz = new Pair<TipKljuca,TipVrijednosti>[kapacitet];
    for(int i=0; i<kapacitet; i++){
        niz[i]=temp.niz[i];
    }
}

template <typename TipKljuca, typename TipVrijednosti>
HashMapa<TipKljuca,TipVrijednosti>::HashMapa(HashMapa<TipKljuca,TipVrijednosti> &&temp){
    kapacitet=temp.kapacitet;
    foo=temp.foo;
    velicina=temp.velicina;
    niz=temp.niz;
}

template <typename TipKljuca, typename TipVrijednosti>
TipVrijednosti& HashMapa<TipKljuca, TipVrijednosti>::operator [](TipKljuca k){
    if(foo==0) throw "Izuzetak";
    int index=foo(k,kapacitet);
    for(int i=0; i<kapacitet; i++){
        if(niz[i].kljuc==k) return niz[i].vrijednost;
    }
    while(index<kapacitet && niz[index].kljuc!=TipKljuca()) index++;
    if(index<kapacitet){
        niz[index].kljuc=k;
        niz[index].vrijednost=TipVrijednosti();
        velicina++;
        return niz[index].vrijednost;
    }
    else{
        Pair<TipKljuca,TipVrijednosti>* temp = new Pair<TipKljuca,TipVrijednosti>[kapacitet+50];
        kapacitet+=50;
        for(int i=0; i<kapacitet-50; i++) temp[i]=niz[i];
        delete []niz;
        niz=temp;
        niz[index].kljuc=k;
        niz[index].vrijednost=TipVrijednosti();
        velicina++;
        return niz[index].vrijednost;
    }
}


template <typename TipKljuca, typename TipVrijednosti>
TipVrijednosti HashMapa<TipKljuca, TipVrijednosti>::operator [](TipKljuca k) const{
    for(int i=0; i<kapacitet; i++){
        if(niz[i].kljuc==k) return niz[i].vrijednost;
    }
    return TipVrijednosti();
}

template <typename TipKljuca, typename TipVrijednosti>
void HashMapa<TipKljuca, TipVrijednosti>::obrisi(const TipKljuca& k){
    if(velicina==0) throw "Izuzetak" ;
    for(int i=0; i<kapacitet; i++){
        if(niz[i].kljuc==k){
            for(int j=i; j<kapacitet-1; j++) niz[i]=niz[i+1];
            velicina--;
        }
    }
}

template <typename TipKljuca, typename TipVrijednosti>
void HashMapa<TipKljuca, TipVrijednosti>::obrisi(){
    delete []niz;
    velicina=0;
    kapacitet=500;
    niz = new Pair<TipKljuca,TipVrijednosti>[kapacitet];
}

void Test(){
    BinStabloMapa<int,int> m;
    NizMapa<int,int> m1;
    HashMapa<int,int> m2;
    m2.definisiHashFunkciju(nekihash);
    
    //mjerenje vremena ubacivanja 1000 elemenata u svaku mapu
    clock_t vrijeme1 = clock();
    for(int i=0; i<1000; i++){
        int random=rand();
        int random1=rand();
        m[random]=random1;
    }
    clock_t vrijeme2 = clock();
    int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja dodavanja el BinStabloMapa: " << ukvrijeme << " ms." << std::endl;
    
    vrijeme1 = clock();
    for(int i=0; i<1000; i++){
        int random=rand();
        int random1=rand();
        m1[random]=random1;
    }
    vrijeme2 = clock();
    ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja dodavanja el NizMapa: " << ukvrijeme << " ms." << std::endl;
    
    vrijeme1 = clock();
    for(int i=0; i<1000; i++){
        int random=rand();
        int random1=rand();
        m2[random]=random1;
    }
    vrijeme2 = clock();
    ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja dodavanja el HashMapa: " << ukvrijeme << " ms." << std::endl;
    
    //random element koji ce biti u svakoj mapi
    int a=rand();
    int b=rand();
    m[a]=b;
    m1[a]=b;
    m2[a]=b;
    
    //mjerenje vremena pristupa tom elementu u svakoj mapi
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
    
    vrijeme1 = clock();
    std::cout << "Random el HashMapa: " <<m2[a] << std::endl;
    vrijeme2 = clock();
    ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja pristupa random el HashMapa: " << ukvrijeme << " ms." << std::endl;
    
    //mjerenje vremena koje je potrebno da se taj random element obrise iz svake mape
    vrijeme1 = clock();
    m.obrisi(a);
    vrijeme2 = clock();
    ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Brisanje random el BinStabloMapa: " << ukvrijeme << " ms." << std::endl;
    
    vrijeme1 = clock();
    m1.obrisi(a);
    vrijeme2 = clock();
    ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Brisanje random el NizMapa: " << ukvrijeme << " ms." << std::endl;
    
    vrijeme1 = clock();
    m2.obrisi(a);
    vrijeme2 = clock();
    ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Brisanje random el HashMapa: " << ukvrijeme << " ms." << std::endl;
    
    /*
    
    Vrijeme izvrsenja dodavanja el BinStabloMapa: 16 ms.
    Vrijeme izvrsenja dodavanja el NizMapa: 32 ms.
    Vrijeme izvrsenja dodavanja el HashMapa: 1856 ms.
    
    Kao sto vidimo elementi se najbrze ubacuju u BinStabloMapa ,  a najduze vremena treba HashMapi
    
    Random el BinStabloMapa: 998597238
    Vrijeme izvrsenja pristupa random el BinStabloMapa: 0 ms.
    Random el NizMapa: 998597238
    Vrijeme izvrsenja pristupa random el NizMapa: 0 ms.
    Random el HashMapa: 998597238
    Vrijeme izvrsenja pristupa random el HashMapa: 2 ms.
    
    Kao sto vodimo za ovaj random element BinStabloMapa i NizMapa skoro pa nemaju vrijeme izvrsavanja , dok je HashMapi potrebno jako malo vrmena
    
    Brisanje random el BinStabloMapa: 2 ms.
    Brisanje random el NizMapa: 1 ms.
    Brisanje random el HashMapa: 2 ms.
    
    Kao sto vidimo vrijeme potrebno da se obrise neki random element je u svakoj Mapi otprilike isto
    
    */
    
}

int main() {
    try{
        Test();
    }
    catch(...){
        std::cout << "Izuzetak";
    }
    return 0;
}
