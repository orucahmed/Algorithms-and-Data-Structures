#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
#include <time.h>
using namespace std;

std::string pretvoriUString(int x) {
std::ostringstream s; s << x; return s.str();
}

void radixSort(vector<int> &a){
    std::vector<std::queue<int>> v(10);
    int eksp=a[0];
    for(int i=1; i<a.size(); i++) if(a[i]>eksp) eksp=a[i];
    std::string s=pretvoriUString(eksp);
    eksp=s.size();
    for(int i=0; i<eksp; i++){
        for(int j=0; j<a.size(); j++){
            int broj=a[j];
            for(int k=0; k<i; k++) broj=broj/10;
            broj=broj%10;
            v[broj].push(a[j]);
        }
        int f=0;
        for(int j=0; j<10; j++){
            while(!v[j].empty()){
                a[f]=v[j].front();
                f++;
                v[j].pop();
            }
        }
    }
}

int roditelj(int i){
    return (i-1)/2;
}

int lijevoDijete(int i){ 
    return 2*i+1; 
}

int desnoDijete(int i){ 
    return 2*i+2; 
}

bool jeLiList(vector<int> a, int i, int velicina){ 
    return (i>=velicina/2 && i<velicina);
}

void popraviDolje(vector<int> &a, int i, int &velicina){
    while(!jeLiList(a, i, velicina)){
        int veci=lijevoDijete(i);
        int dd=desnoDijete(i);
        if(dd<velicina && a[dd]>a[veci]) veci=dd;
        if(a[i]>a[veci]) return;
        int temp=a[i];
        a[i]=a[veci];
        a[veci]=temp;
        i=veci;
    }
}

void stvoriGomilu(vector<int> &a){
    int velicina=a.size();
    for(int i=velicina/2; i>=0; i--) popraviDolje(a,i,velicina);
    
}

void popraviGore(vector<int> &a, int i){
    while(i!=0 && a[i]>a[roditelj(i)]){
        int temp=a[i];
        a[i]=a[roditelj(i)];
        a[roditelj(i)]=temp;
        i=roditelj(i);
    }
}

void umetniUGomilu(vector<int> &a, int umetnuti, int &velicina){
    a.push_back(umetnuti);
    velicina++;
    popraviGore(a, velicina-1);
}

int izbaciPrvi(vector<int> &a, int &velicina){
    velicina--;
    int temp=a[0];
    a[0]=a[velicina];
    a[velicina]=temp;
    if(velicina!=0) popraviDolje(a,0, velicina);
    return temp;
    
}

void gomilaSort(vector<int> &a){
    stvoriGomilu(a);
    int velicina=a.size();
    for(int i=0; i<=a.size()-2; i++) izbaciPrvi(a,velicina);
}


void TEST(){
    int vel=1000;
    std::vector<int>a(vel);
    std::vector<int>b(vel);
    std::vector<int>c(vel);
    for(int i=0; i<vel; i++){
        int random=rand();
        a[i]=random;
        b[i]=random;
        c[i]=random;
    }
    clock_t vrijeme1 = clock();
    radixSort(a);
    clock_t vrijeme2 = clock();
    int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme potrebno da se niz sortitra Radix sortom je :" << ukvrijeme << " ms." <<std::endl;
    vrijeme1 = clock();
    gomilaSort(b);
    vrijeme2 = clock();
    ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme potrebno da se niz sortitra Gomila sortom je :" << ukvrijeme<< " ms." << std::endl;
    vrijeme1 = clock();
    sort(c.begin(),c.end());
    vrijeme2 = clock();
    ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme potrebno da se niz sortitra ugradjenim sortom je :" << ukvrijeme << " ms."<< std::endl;
    std::cout << "Provjera da li je sve sortirano: " << std::endl;
    bool istina=true;
    for(int i=0; i<vel; i++){
        if(a[i]!=b[i] || a[i]!=c[i]){
            istina=false;
            break;
        }
    }
    if(istina) std::cout << "Da" << std::endl;
    else std::cout << "Ne" << std::endl;
}

int main() {
    TEST();
    return 0;
}
