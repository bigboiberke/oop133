#include <iostream>
const int a=100;
using namespace std;

class Multime{
    int n,max;
    int *element;
public:
    Multime(int v){
        max=v;
        element=new int[max];
    }
    Multime(const Multime& m){
        n=m.n;
        element=new int[n];
        n=0;
        memcpy(element,m.element,sizeof(int)*n);
    }
    ~Multime(){
        if (element) delete[] element;
    }

    int search(int v) const;
    void add(int v);

    Multime& operator =(Multime&);
    Multime operator +(const Multime&) const; //reuniune
    Multime operator -(const Multime&) const; //diferenta
    Multime operator *(const Multime&) const; //intersectie

    friend ostream& operator <<(ostream& os, const Multime& m);
    friend istream& operator >>(istream& is,Multime& m);
};

int Multime::search(int v) const{
    int p=0;
    int u=n-1;
    int mij;
    while (p<=u){
        mij=(p+u)/2;
        if (element[mij]<v) p=mij+1;
        else
        if (element[mij]>v) u=mij-1;
        else return 1;
    }
    return 0;
}

void Multime::add(int v){
    if (!search(v)){
        if (n>=max){
            int *p=new int [max+a];
            memcpy(p,element,sizeof(int)*n);
            delete[] element;
            element=p;
        }
        int i=n-1;
        while (i>=0 && element[i]>v){
            element[i+1]=element[i];
            i--;
        }
        element[i+1]=v;
        n++;
    }
}

Multime& Multime::operator =(Multime& m){
    if (this==&m) return *this;
    if (element) delete[] element;
    max=m.max;
    n=m.n;
    element=new int[max];
    memcpy(element,m.element,sizeof(int)*n);
    return *this;
}

Multime Multime::operator +(const Multime& m) const{
    Multime t=m;
    int i;

    for (i=0;i<n;i++) t.add(element[i]);
    return t;
}

Multime Multime::operator -(const Multime& m) const{
    Multime t(n);

    for (int i=0;i<n;i++)
        if (!m.search(element[i]))
            t.element[t.n++]=element[i];
    return t;
}

Multime Multime::operator *(const Multime& m) const{
    Multime t(n);

    for (int i=0;i<n;i++)
        if (m.search(element[i]))
            t.element[t.n++]=element[i];
    return t;
}

ostream& operator <<(ostream& os, const Multime& m){
    for (int i=0;i<m.n;i++)
        os<<m.element[i]<<" ";
    os<<endl;
    return os;
}

istream& operator >>(istream& is,Multime& m){
    int nr,v;

    cout<<"Numar elemente=";
    is>>nr;
    nr=(nr>m.max)?m.max:nr;
    for (int i=0;i<nr;i++){
        is>>v;
        m.add(v);
    }
    return is;
}

int main() {
    Multime a(5);
    cin >> a;
    Multime b(6);
    cin >> b;
    Multime c(a + b);
    cout << "Reuniune: " << c;
    cout << "Diferenta: " << (a - b);
    cout << "Intersectie: " << (a * b);
}