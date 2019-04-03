#include <iostream>

int nzd(int x, int y){
    if(y==0) return x;
    return nzd(y, x%y);
}

int fib2_0(int n, int x=0, int y=1){
    if(n==0) return x;
    if(n==1) return y;
    return fib2_0(n-1, y,x+y);
}


void NZDTEST(){
    try{
        std::cout << nzd(10,5) << std::endl;
        std::cout << nzd(56,4) << std::endl;
        std::cout << nzd(14,2) << std::endl;
    }
    catch(...){
        throw;
    }
}


void FIBTEST(){
    try{
        std::cout << fib2_0(20) << std::endl;
        std::cout << fib2_0(5) << std::endl;
    }
    catch(...){
        throw;
    }
}

int main(){
    try{
        
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