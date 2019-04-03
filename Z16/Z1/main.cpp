#include <iostream>
#include <string>
#include <stdexcept>

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

void NizMapaBrojElemenata(){
    try{
        NizMapa<std::string,std::string> m;
        m["BiH"] = "Sarajevo";
        m["Cro"] = "Zagreb";
        m["Srb"] = "Beograd";
        std::cout << m.brojElemenata() << std::endl;
    }
    catch(...){
        throw;
    }
}

void NizMapaObrisi(){
    try{
        NizMapa<std::string,std::string> m;
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

void NizMapaObrisiKljuc(){
    try{
        NizMapa<std::string,std::string> m;
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

void NizMapaObrisiKljucIzuzetak(){
    try{
        NizMapa<std::string,std::string> m;
        m["BiH"] = "Sarajevo";
        m["Cro"] = "Zagreb";
        m["Srb"] = "Beograd";
        m.obrisi("Slo");
    }
    catch(...){
        throw;
    }
}

void NizMapaOperatorUglaste(){
    try{
        NizMapa<std::string,std::string> m;
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

void NizMapaOperatorUglasteConst(){
    try{
        NizMapa<std::string,std::string> m;
        m["BiH"] = "Sarajevo";
        m["Cro"] = "Zagreb";
        m["Srb"] = "Beograd";
        std::cout << m["BiH"] << std::endl;
    }
    catch(...){
        throw;
    }
}

void NizMapaOperatorDodjele(){
    try{
        NizMapa<std::string,std::string> m;
        m["BiH"] = "Sarajevo";
        m["Cro"] = "Zagreb";
        m["Srb"] = "Beograd";
        NizMapa<std::string,std::string> k;
        k=m;
        std::cout << k.brojElemenata() << std::endl;
    }
    catch(...){
        throw;
    }
}


void NizMapaKobstruktor(){
    try{
        NizMapa<std::string,std::string> m;
        m["BiH"] = "Sarajevo";
        m["Cro"] = "Zagreb";
        m["Srb"] = "Beograd";
        NizMapa<std::string,std::string> k(m);
        std::cout << k.brojElemenata() << std::endl;
    }
    catch(...){
        throw;
    }
}

void NizMapaTest(){
    try{
        NizMapaBrojElemenata();
        NizMapaObrisi();
        NizMapaObrisiKljuc();
        NizMapaOperatorUglaste();
        NizMapaOperatorUglasteConst();
        NizMapaOperatorDodjele();
        NizMapaObrisiKljucIzuzetak();
    }
    catch(...){
        throw;
    }
}

int main(){
    try{
        NizMapaTest();
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
