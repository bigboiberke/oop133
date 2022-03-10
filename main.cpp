#include <iostream>
const int a=100;
using namespace std;

class Multime{
    int n=0,max;
    int *element;
public:
    Multime(){}
    Multime(const int &nr,const int vect[]){
        n=nr;
        element=new int[n];
        max=vect[0];
        for(int i=0;i<n;i++) {
            element[i] = vect[i];
            if(max<vect[i])
                max=vect[i];
        }
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
            int *p=new int [n+1];
            //memcpy(p,element,sizeof(int)*n);
            //delete[] element;
            for (int j=0; j<n; j++)
                p[j] = element[j];
                //element=p;
                delete[] element;
            element=new int [n+1];
            for (int j=0; j<n; j++)
                element[j]=p[j];
        element[n]=v;
        /*int i=n-1;
        while (i>=0 && element[i]>v){
            element[i+1]=element[i];
            i--;
        }
        element[i+1]=v;*/
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
    Multime t;
    t.n=0;
    t.element=new int [n+m.n];

    for(int i=0;i<n;i++){
        t.element[t.n++]=element[i];
        if(i==0)
            t.max=element[i];
        else
        if(element[i]>t.max)
            t.max=element[i];

    }
    for(int i=0;i<m.n;i++){
        bool ok=true;
        for(int j=0;j<n;j++)
            if(m.element[i]==element[j])
                ok= false;
        if(ok){
            t.element[t.n++]=m.element[i];
            if(t.max<m.element[i])
                t.max=m.element[i];
        }
    }
    return t;
}

Multime Multime::operator -(const Multime& m) const{
    Multime t;
    t.n=0;
    t.element=new int [n];


    for (int i=0;i<n;i++) {
        if (!m.search(element[i])) {
            t.element[t.n++] = element[i];
            if (t.n == 1)
                t.max = element[i];
            else if (t.max < element[i])
                t.max = element[i];
        }
    }
    return t;
}

Multime Multime::operator *(const Multime& m) const{
    Multime t;
    t.n=0;
    t.element=new int [n];

    for (int i=0;i<n;i++)
        if (m.search(element[i])) {
            t.element[t.n++] = element[i];
            if(t.n==1)
                t.max=element[i];
            else
            if(t.max<element[i])
                t.max=element[i];
        }
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
    m.n=nr;
    m.element=new int[nr];
    for (int i=0;i<nr;i++){
        is>>v;
        if(i==0)
            m.max=v;
        else
            if(m.max<v)
                m.max=v;
        m.element[i]=v;
    }
    return is;
}

int main() {
    int v[]={1,2,3,4,5};
    Multime a(5,v);
    cout<<a;
    cin >> a;
    Multime b;
    cin >> b;
    Multime c(a + b);
    cout << "Reuniune: " << c;
    cout << "Diferenta: " << (a - b);
    cout << "Intersectie: " << (a * b);
}
