// In acest proiect vom crea o clasa de arbori binari
#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("Arbori.in");
ofstream fout("Arbori.out");

bool ePrim(int n) {
    if (n == 1 || n == 0) return false;
    if (n == 2)return true;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}



class ArboreBinar {
public:
    int marime;
    int radacina=0;
    int *stanga;
    int *dreapta;
    int* valoare;
    //in aceasta implementare:
    //stanga[i] este nodul din stanga nodului numerotat cu i
    //dreapta[i] este nodul din dreapta nodului numerotat cu i
    //valoare[i] valoarea stocata in nodul i
    //i=numarul de ordine al fiecarui nod

    ArboreBinar(int marime){
        this->marime = marime;

        this->stanga = new int[marime + 1];
        this->dreapta = new int[marime + 1];
        this->valoare = new int[marime + 1];
    }

    void citireStanga() {
        for (int i = 1; i <= this->marime; i++)
            fin >> this->stanga[i];
    }

    void citireDreapta() {
        for (int i = 1; i <= this->marime; i++)
            fin >> this->dreapta[i];
    }

    void citireValori() {
        for (int i = 1; i <= this->marime; i++)
            fin >> this->valoare[i];
    }


    void citireXStDr() {
        // la citirea X st dr, sunt necesare n (marime) linii, pe fiecare se regaseste valoarea din nodul i, nodul din stanga lui i si nodul din dreapta lui i
        for (int i = 1; i <= this->marime; i++) {
            fin >> this->valoare[i];
            fin >> this->stanga[i];
            fin >> this->dreapta[i];
        }
    }

  


    void afisareFrunze() {
        for (int i = 1; i <= this->marime; i++)
            if (this->stanga[i] == 0 && this->dreapta[i] == 0) fout << i << " ";
    }
    void afisareValoriFrunze() {
        for (int i = 1; i <= this->marime; i++)
            if (this->stanga[i] == 0 && this->dreapta[i] == 0) fout << this->valoare[i] << " ";
    }

    void determinareIndiceRadacina() {
        //radacina va fi nodul care nu apare nici in vectorul stanga si nici in dreapta
        //aceasta functie determina radacina si o salveaza in variabila .radacina
        int size = this->marime + 1;
       
        int *v=new int[size];

        for (int i = 1; i <= this->marime; i++) {
            v[this->stanga[i]] = 1;
            v[this->dreapta[i]] = 1;
        }
        for(int i=1;i<=this->marime;i++)
            if (v[i] != 1) {
                this->radacina = i;
                return;
            }
            
    }

    void afisareValoriPreodrine(int radacina) {
        fout << this->valoare[radacina]<<" ";

        if (this->stanga[radacina] != 0) 
            this->afisareValoriPreodrine(stanga[radacina]);

        if (this->dreapta[radacina] != 0)
            this->afisareValoriPreodrine(dreapta[radacina]);
    }

    void afisareValoriInodrine(int radacina) {
        
        if (this->stanga[radacina] != 0)
            this->afisareValoriInodrine(stanga[radacina]);
        
        fout << this->valoare[radacina] << " ";

        if (this->dreapta[radacina] != 0)
            this->afisareValoriInodrine(dreapta[radacina]);
    }

    void afisareValoriPostordine(int radacina) {
        if (this->stanga[radacina] != 0)
            this->afisareValoriPostordine(stanga[radacina]);

        if (this->dreapta[radacina] != 0)
            this->afisareValoriPostordine(dreapta[radacina]);

        fout << this->valoare[radacina] << " ";
    }

    int sumaValori(int radacina) {
        int sumst = 0;
        int sumdr = 0;
        if (this->stanga[radacina] != 0)
            sumst = this->sumaValori(stanga[radacina]);

        if (this->dreapta[radacina] != 0)
            sumdr = this->sumaValori(dreapta[radacina]);

        return this->valoare[radacina] + sumst + sumdr;
    }


    int diferentaSubarbori(int radacina) {
        //aceasta functie va calcula diferenta in valoare absoluta dintre subarborele stand si cel drept;

        int sumst = sumaValori(this->stanga[radacina]);
        int sumdr = sumaValori(this->dreapta[radacina]);

        int dif = sumst - sumdr;
        dif = abs(dif);
        return dif;

    }

    int nrNoduri(int radacina) {
       
        if (this->stanga[radacina] == 0 && this->dreapta[radacina] == 0) return 1;
        if (this->stanga[radacina] == 0 ) return nrNoduri(this->dreapta[radacina]) + 1;
        if (this->dreapta[radacina] == 0) return nrNoduri(this->stanga[radacina]) + 1;


        return nrNoduri(this->stanga[radacina]) + nrNoduri(this->dreapta[radacina]) + 1;
    }

    int nrNoduriPrime(int radacina) {
        int primeSt = 0, primeDr = 0;

        if (this->stanga[radacina] != 0)
           primeSt= this->nrNoduriPrime(stanga[radacina]);

        if (this->dreapta[radacina] != 0)
            primeDr = this->nrNoduriPrime(dreapta[radacina]);

        return primeSt + primeDr + this->nodPrim(radacina);

    }

    private:
        int nodPrim(int nrNod) {
            if (ePrim(this->valoare[nrNod])) { return 1; cout << "1"; }
            return 0;

        }




};



int main()
{
    int n,k;
    fin >> n;
    ArboreBinar x(n);
    x.citireXStDr();
    fin >> k;
    int a;
    for (int i = 1; i <= k; i++) {
        fin >> a;
        fout << x.nrNoduriPrime(a) << endl;
    }
    

 

  


    return 0;
}



