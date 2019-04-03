#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

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

void pretraga(Stek<vector<int>>& s, int trazeni, std::vector<int> vektor={}){ 
    int brojac=s.brojElemenata();
    if(brojac==0){
        std::cout << "Nema elementa";
        return;
    }
    if(s.vrh().size()==0){
        pretraga(s, trazeni,s.skini());
        s.stavi(vektor);
    }
    else if(trazeni<s.vrh()[0]){
        pretraga(s, trazeni,s.skini());
        s.stavi(vektor);
    }
    else{
        int dno=0;
        int vrh =s.vrh().size()-1;
        int pozicija;
        while(vrh>=dno){
            pozicija=(dno+vrh)/2;
            if(s.vrh()[pozicija]==trazeni){
                std::cout << pozicija << " " << s.brojElemenata()-1;
                s.stavi(vektor);
                return;
            }
            else if(s.vrh()[pozicija]>trazeni) vrh=pozicija-1;
            else dno=pozicija+1;
        }
        std::cout << "Nema elementa";
        return;
    }
}

void TEST(){
    Stek<vector<int> > s;
    vector<int> a;
    vector<int> b;
    vector<int> c;
    vector<int> d;
    a.push_back(1);a.push_back(2);a.push_back(3);a.push_back(4);
    b.push_back(5);b.push_back(6);b.push_back(7);b.push_back(8);
    c.push_back(9);c.push_back(10);c.push_back(11);c.push_back(12);
    d.push_back(13);d.push_back(14);d.push_back(15);d.push_back(16);
    s.stavi(a);
    s.stavi(b);
    s.stavi(c);
    s.stavi(d);
    std::cout << s.brojElemenata() << std::endl;
    pretraga(s,17);
    std::cout << std::endl << s.brojElemenata();
}

void TEST1(){
    Stek<vector<int> > s;
    vector<int> a;
    vector<int> b;
    vector<int> c;
    vector<int> d;
    a.push_back(1);a.push_back(2);a.push_back(3);a.push_back(4);
    b.push_back(5);b.push_back(6);b.push_back(7);b.push_back(8);
    c.push_back(9);c.push_back(10);c.push_back(11);c.push_back(12);
    d.push_back(13);d.push_back(14);d.push_back(15);d.push_back(16);
    s.stavi(a);
    s.stavi(b);
    s.stavi(c);
    s.stavi(d);
    pretraga(s,10);
}

void TEST2(){
    Stek<vector<int> > s;
    vector<int> a;
    vector<int> b;
    vector<int> c;
    vector<int> d;
    a.push_back(1);a.push_back(2);a.push_back(3);a.push_back(4);
    b.push_back(5);b.push_back(6);b.push_back(7);b.push_back(8);
    c.push_back(9);c.push_back(10);c.push_back(11);c.push_back(12);
    d.push_back(13);d.push_back(14);d.push_back(15);d.push_back(16);
    s.stavi(a);
    s.stavi(b);
    s.stavi(c);
    s.stavi(d);
    pretraga(s,1);
}

void AT(){
    Stek<vector<int> > s;
    vector<int> a;
    for (int i(0); i<5; i++)
    a.push_back(i);
    vector<int> b;
    vector<int> c;
    vector<int> d;
    for (int i(5); i<7; i++)
    b.push_back(i);
    s.stavi(a);
    s.stavi(b);
    c.push_back(8);
    s.stavi(c);
    d.push_back(9);
    s.stavi(d);
    pretraga(s,2);
    cout<<" ";
    while(s.brojElemenata()!=0){
        vector<int> k = s.skini();
        for(int i(0);i<k.size();i++){
            cout<<k[i]<<" ";
        }
    }
    std::cout << std::endl << "2 0 9 8 5 6 0 1 2 3 4";
    
}

int main(){
    try{
        AT();
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