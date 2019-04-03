#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>

void generisi(std::string filename, int vel){
    std::ofstream it(filename);
    for(int i=0; i<vel; i++){
        int random=rand();
        it << random << std::endl;
    }
}

void upisi(std::string filename, int* niz, int vel){
    std::ofstream it(filename);
    for(int i=0; i<vel; i++) it << niz[i] << std::endl;
}

void ucitaj(std::string filename, int*& niz, int &vel){
    std::ifstream ut(filename);
    std::ifstream ut1(filename);
    int broj;
    while(ut1>>broj) vel++;
    niz = new int[vel];
    int brojac=0;
    while(ut>>broj){
        niz[brojac]=broj;
        brojac++;
    }
}

template <typename Tip>
void bubble_sort(Tip* niz, int vel){
    for(int i=vel-1; i>=1; i--){
        for(int j=1; j<=i; j++){
            if(niz[j-1]>niz[j]){
                Tip temp=niz[j-1];
                niz[j-1]=niz[j];
                niz[j]=temp;
            }
        }
    }
}

template <typename Tip>
void selection_sort(Tip* niz, int vel){
    for(int i=0; i<=vel-2; i++){
        Tip min=niz[i];
        int pmin=i;
        for(int j=i+1; j<=vel-1; j++){
            if(niz[j]<min){
                min=niz[j];
                pmin=j;
            }
        }
        niz[pmin]=niz[i];
        niz[i]=min;
    }
}

template <typename Tip>
int particija(Tip *niz, int prvi, int zadnji){
    Tip pivot=niz[prvi];
    int p=prvi+1;
    while(p<=zadnji && niz[p]<pivot) p++;
    for(int i=p+1; i<=zadnji; i++){
        if(niz[i]<pivot){
            Tip temp=niz[i];
            niz[i]=niz[p];
            niz[p]=temp;
            p++;
        }
    }
    Tip temp=niz[prvi];
    niz[prvi]=niz[p-1];
    niz[p-1]=temp;
    return p-1;
}

template <typename Tip>
void quick_sort_helper(Tip* niz, int prvi, int zadnji){
    if(prvi<zadnji){
        int j=particija(niz, prvi, zadnji);
        quick_sort_helper(niz,prvi,j-1);
        quick_sort_helper(niz,j+1,zadnji);
    }
}

template <typename Tip>
void quick_sort(Tip* niz, int vel){
    quick_sort_helper(niz,0, vel-1);
}

template <typename Tip>
void merge(Tip* niz,int l, int p, int q, int u){
    int i=0;
    int j=q-l;
    int k=l;
    Tip * niz1 = new Tip[u-l+1];
    for(int m=0; m<=u-l; m++) niz1[m]=niz[l+m];
    while(i<=p-l && j<=u-l){
        if(niz1[i]<niz1[j]){
            niz[k]=niz1[i];
            i++;
        }
        else{
            niz[k]=niz1[j];
            j++;
        }
        k++;
    }
    while(i<=p-l){
        niz[k]=niz1[i];
        k++;
        i++;
    }
    while(j<=u-l){
        niz[k]=niz1[j];
        k++;
        j++;
    }
    delete []niz1;
}

template <typename Tip>
void merge_sort_helper(Tip* niz, int l, int u){
    if(u>l){
        int p=(l+u-1)/2;
        int q=p+1;
        merge_sort_helper(niz, l, p);
        merge_sort_helper(niz, q, u);
        merge(niz, l, p, q, u);
    }
}

template <typename Tip>
void merge_sort(Tip* niz, int vel){
    merge_sort_helper(niz, 0, vel-1);
}

template <typename Tip>
void TestBubble(Tip* niz, int vel){
    clock_t vrijeme1 = clock();
    bubble_sort(niz, vel);
    clock_t vrijeme2 = clock();
    int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja: " << ukvrijeme << " ms." << std::endl;
    for(int i(0); i<vel-1; i++) 
        if(niz[i] > niz[i+1]) {
            std::cout << "Niz nije dobro sortiran";
            break;
        }
    std::cout << "Niz je dobro sortiran";
}

template <typename Tip>
void TestSelection(Tip* niz, int vel){
    clock_t vrijeme1 = clock();
    selection_sort(niz, vel);
    clock_t vrijeme2 = clock();
    int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja: " << ukvrijeme << " ms." << std::endl;
    for(int i(0); i<vel-1; i++) 
        if(niz[i] > niz[i+1]) {
            std::cout << "Niz nije dobro sortiran";
            break;
        }
    std::cout << "Niz je dobro sortiran";
}

template <typename Tip>
void TestQuick(Tip* niz, int vel){
    clock_t vrijeme1 = clock();
    quick_sort(niz, vel);
    clock_t vrijeme2 = clock();
    int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja: " << ukvrijeme << " ms." << std::endl;
    for(int i(0); i<vel-1; i++) 
        if(niz[i] > niz[i+1]) {
            std::cout << "Niz nije dobro sortiran";
            break;
        }
    std::cout << "Niz je dobro sortiran";
}

template <typename Tip>
void TestMerge(Tip* niz, int vel){
    clock_t vrijeme1 = clock();
    merge_sort(niz, vel);
    clock_t vrijeme2 = clock();
    int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja: " << ukvrijeme << " ms." << std::endl;
    for(int i(0); i<vel-1; i++) 
        if(niz[i] > niz[i+1]) {
            std::cout << "Niz nije dobro sortiran";
            break;
        }
    std::cout << "Niz je dobro sortiran";
}

void Meni(){
    std::cout<< "Odabir sorta" << std::endl;
    std::cout<< "1. Bubble sort" << std::endl;
    std::cout<< "2. Selection sort" << std::endl;
    std::cout<< "3. Quick sort" << std::endl;
    std::cout<< "4. Merge sort" << std::endl;
    std::cout<< "5. Izlaz" << std::endl;
    std::cout<< "Unesite broj da odaberete koji sort zelite: ";
}

void Meni1(){
    std::cout << "Odabir datoteke random brojeva" << std::endl;
    std::cout << "1. Da" << std::endl;
    std::cout << "1. Ne" << std::endl;
    std::cout << "Unesite broj za odabir: ";
}
void TEST(){
    int* niz;
    int vel = 0;
    int temp;
    for(;;){
        Meni1();
        std::cin >> temp;
        if(temp==1){
            std::cout << "Unesite broj elemenata datoteke :";
            int nesto;
            std::cin >> nesto;
            generisi("autotest.txt",nesto);
            break;
        }
        if(temp==2){
            break;
        }
        else std::cout << "Unijeli ste nepostojecu komandu!" << std::endl;
    }
    ucitaj("autotest.txt", niz, vel);
    int broj;
    for(;;){
        Meni();
        std::cin>>broj;
        if(broj==1) {
            TestBubble(niz,vel);
            break;
        }
        if(broj==2){
            TestSelection(niz,vel);
            break;
        }
        if(broj==3){
            TestQuick(niz,vel);
            break;
        }
        if(broj==4) {
            TestMerge(niz,vel);
            break;
        }
        if(broj==5) break;
        else std::cout << "Unijeli ste nepostojecu komandu!" << std::endl;
    }
    upisi("izlaz.txt", niz, vel);
    delete []niz;
}

int main() {
    TEST();
    return 0;
}
