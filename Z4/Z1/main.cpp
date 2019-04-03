#include <iostream>
#include <string>
#include <time.h>

using namespace std;

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
struct Cvor{
    TipKljuca kljuc=TipKljuca();
    TipVrijednosti vrijednost=TipVrijednosti();
    Cvor* lijevo=nullptr;
    Cvor* desno=nullptr;
    Cvor* roditelj=nullptr;
    int balans=0;
};

template <typename TipKljuca, typename TipVrijednosti>
class AVLStabloMapa : public Mapa<TipKljuca, TipVrijednosti>{
    private:
        int velicina=0;
        Cvor<TipKljuca, TipVrijednosti>* korijen;
        void preorder(Cvor<TipKljuca, TipVrijednosti>* pok, Cvor<TipKljuca, TipVrijednosti>* &pok1, Cvor<TipKljuca, TipVrijednosti>* pok2=nullptr);
        
        void azurirajBalans(Cvor<TipKljuca, TipVrijednosti>* cvor);
        void lijevaRotacija(Cvor<TipKljuca, TipVrijednosti>* cvor);
        void desnaRotacija(Cvor<TipKljuca, TipVrijednosti>* cvor);
    public:
        AVLStabloMapa() { korijen=nullptr; }
        ~AVLStabloMapa() { this->obrisi(); }
        int brojElemenata() const { return velicina; }
        void obrisi();
        void obrisi(const TipKljuca& k);
        TipVrijednosti operator [](TipKljuca k) const;
        TipVrijednosti &operator [](TipKljuca k);
        AVLStabloMapa(const AVLStabloMapa<TipKljuca,TipVrijednosti> &temp);
        AVLStabloMapa(AVLStabloMapa<TipKljuca,TipVrijednosti> &&temp);
        AVLStabloMapa& operator=(const AVLStabloMapa<TipKljuca,TipVrijednosti> &temp);
        AVLStabloMapa& operator=(AVLStabloMapa<TipKljuca,TipVrijednosti> &&temp);
};

template <typename TipKljuca, typename TipVrijednosti>
void AVLStabloMapa<TipKljuca,TipVrijednosti>::lijevaRotacija(Cvor<TipKljuca, TipVrijednosti>* cvor){
    if(cvor->balans * cvor->desno->balans < 0) desnaRotacija(cvor->desno);
    Cvor<TipKljuca, TipVrijednosti>* walker=cvor->desno;
    walker->roditelj=cvor->roditelj;
    cvor->desno=nullptr;
    walker->lijevo=cvor;
    cvor->roditelj=walker;
    walker->balans=0;
    cvor->balans=0;
}


template <typename TipKljuca, typename TipVrijednosti>
void AVLStabloMapa<TipKljuca,TipVrijednosti>::desnaRotacija(Cvor<TipKljuca, TipVrijednosti>* cvor){
    if(cvor->balans * cvor->lijevo->balans < 0) lijevaRotacija(cvor->lijevo);
    Cvor<TipKljuca, TipVrijednosti>* walker=cvor->lijevo;
    walker->roditelj=cvor->roditelj;
    cvor->lijevo=nullptr;
    walker->desno=cvor;
    cvor->roditelj=walker;
    walker->balans=0;
    cvor->balans=0;
}

template <typename TipKljuca, typename TipVrijednosti>
void AVLStabloMapa<TipKljuca,TipVrijednosti>::azurirajBalans(Cvor<TipKljuca, TipVrijednosti>* cvor){
    if(cvor->roditelj==nullptr) return;
    Cvor<TipKljuca,TipVrijednosti> *walker=cvor->roditelj;
    if(walker->lijevo==cvor) walker->balans++;
    else walker->balans--;
    if(walker->balans>1) desnaRotacija(walker);
    else if(walker->balans<-1) lijevaRotacija(walker);
}

template <typename TipKljuca, typename TipVrijednosti>
void AVLStabloMapa<TipKljuca,TipVrijednosti>::preorder(Cvor<TipKljuca, TipVrijednosti>* pok, Cvor<TipKljuca, TipVrijednosti>* &pok1, Cvor<TipKljuca, TipVrijednosti>* pok2){
    if(pok!=nullptr){
        pok1=new Cvor<TipKljuca, TipVrijednosti>();
        pok1->kljuc=pok->kljuc;
        pok1->vrijednost=pok->vrijednost;
        pok1->balans=pok->balans;
        pok1->roditelj=pok2;
        preorder(pok->lijevo, pok1->lijevo, pok2);
        preorder(pok->desno, pok1->desno, pok2);
    }
}




template <typename TipKljuca, typename TipVrijednosti>
AVLStabloMapa<TipKljuca,TipVrijednosti>::AVLStabloMapa(const AVLStabloMapa<TipKljuca,TipVrijednosti> &temp){
    velicina=temp.velicina;
    preorder(temp.korijen, korijen);
}

template <typename TipKljuca, typename TipVrijednosti>
AVLStabloMapa<TipKljuca,TipVrijednosti>& AVLStabloMapa<TipKljuca,TipVrijednosti>::operator=(const AVLStabloMapa<TipKljuca,TipVrijednosti> &temp){
    if(&temp==this) return *this;
    this->obrisi();
    velicina=temp.velicina;
    preorder(temp.korijen, korijen);
    return *this;
}

template <typename TipKljuca, typename TipVrijednosti>
AVLStabloMapa<TipKljuca,TipVrijednosti>& AVLStabloMapa<TipKljuca,TipVrijednosti>::operator=(AVLStabloMapa<TipKljuca,TipVrijednosti> &&temp){
    if(&temp==this) return *this;
    this->obrisi();
    velicina=temp.velicina;
    korijen=temp.korijen;
    return *this;
}

template <typename TipKljuca, typename TipVrijednosti>
AVLStabloMapa<TipKljuca,TipVrijednosti>::AVLStabloMapa(AVLStabloMapa<TipKljuca,TipVrijednosti> &&temp){
    velicina=temp.velicina;
    korijen=temp.korijen;
}

//sitne izmjene u implementaciji funkcije [] , razlika u nacinu break funkcije
template <typename TipKljuca, typename TipVrijednosti>
TipVrijednosti &AVLStabloMapa<TipKljuca, TipVrijednosti>::operator [](TipKljuca k){
    Cvor<TipKljuca, TipVrijednosti>* walker=nullptr;
    Cvor<TipKljuca, TipVrijednosti>* temp=korijen;
    while(temp!=nullptr && k!=temp->kljuc){
        walker=temp;
        if(k>temp->kljuc) temp=temp->desno;
        else temp=temp->lijevo;
    }
    if(temp!=nullptr) return temp->vrijednost;
    else{
        temp=new Cvor<TipKljuca, TipVrijednosti>();
        temp->vrijednost=TipVrijednosti();
        temp->kljuc=k;
        temp->lijevo=nullptr;
        temp->desno=nullptr;
        temp->balans=0;
        if(korijen==nullptr){
            velicina++;
            korijen=temp;
            return temp->vrijednost;
        }
        else{
            if(k>walker->kljuc) walker->desno=temp;
            else walker->lijevo=temp;
            temp->roditelj=walker;
            azurirajBalans(temp);
            velicina++;
        }
    }
    
    
    return temp->vrijednost;
    
}


template <typename TipKljuca, typename TipVrijednosti>
TipVrijednosti AVLStabloMapa<TipKljuca, TipVrijednosti>::operator[] (TipKljuca k) const{
    Cvor<TipKljuca, TipVrijednosti>* walker=korijen;
    while(walker!=nullptr && k!=walker->kljuc){
        if(k>walker->kljuc) walker=walker->desno;
        else walker=walker->lijevo;
    }
    if(walker==nullptr) return TipVrijednosti();
    return walker->vrijednost;
}

template <typename TipKljuca, typename TipVrijednosti>
void AVLStabloMapa<TipKljuca, TipVrijednosti>::obrisi(){
    while(korijen!=nullptr) obrisi(korijen->kljuc);
    korijen=nullptr;
    velicina=0;
}

// sitna izmjena u funkciji m azurira se balans
template <typename TipKljuca, typename TipVrijednosti>
void AVLStabloMapa<TipKljuca, TipVrijednosti>::obrisi(const TipKljuca& k){
    if(velicina==0) return;
    velicina--;
    Cvor<TipKljuca, TipVrijednosti>* p=korijen;
    Cvor<TipKljuca, TipVrijednosti>* r=nullptr;
    while(p!=nullptr && k!=p->kljuc){
        r=p;
        if(k<p->kljuc) p=p->lijevo;
        else p=p->desno;
    }
    if(p==nullptr) return;
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
        if(p==r->lijevo){
             r->lijevo=m;
             r->balans--;
        }
        else{
            r->desno=m;
            r->balans++;
        }
    }
    delete p;
    
}

void AT2(){
    // Da li je "AVLStabloMapa" ustvari obicno binarno stablo?
AVLStabloMapa <int, int> m;
int vel(500000);
int progress(1000);
for (int i(0); i<vel; i++) {
    m[i] = i;
    if (i==progress) { 
       cout<<"Dodano "<<i<<endl;
       progress *= 2;
    }
}
// Obicno bin. stablo ce uspjeti dodati oko 30000-70000 el. za 10 sekundi
// Korektno AVL stablo ce zavrsiti kompletan test za <1 sekundu

for (int i(0); i>=-vel; i--)
    m[i] = i;
for (int i(-vel); i<vel; i++)
    if (m[i] != i) { cout << i << " NOT OK"; break; }
for (int i(-vel); i<vel; i++)
    m.obrisi(i);
cout << "OK";
}


int main() {
    try{
        AT2();
        
    }
    catch(...){
        std::cout << "Izuzetak";
    }
    return 0;
}
