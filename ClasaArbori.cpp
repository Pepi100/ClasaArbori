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
    int *valoare;
    int *nivel;
    int nivelmax = 1;
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
        this->nivel = new int[marime + 1];
    }

    void citireStanga() {
        for (int i = 1; i <= this->marime; i++)
            fin >> stanga[i];
    }

    void citireDreapta() {
        for (int i = 1; i <= this->marime; i++)
            fin >> dreapta[i];
    }

    void citireValori() {
        for (int i = 1; i <= this->marime; i++)
            fin >> valoare[i];
    }


    void citireXStDr() {
        // la citirea X st dr, sunt necesare n (marime) linii, pe fiecare se regaseste valoarea din nodul i, nodul din stanga lui i si nodul din dreapta lui i
        for (int i = 1; i <= marime; i++) {
            fin >> valoare[i];
            fin >> stanga[i];
            fin >> dreapta[i];
        }
    }



    void afisareFrunze() {
        for (int i = 1; i <= marime; i++)
            if (stanga[i] == 0 && dreapta[i] == 0) fout << i << " ";
    }
    void afisareValoriFrunze() {
        for (int i = 1; i <= this->marime; i++)
            if (stanga[i] == 0 && dreapta[i] == 0) fout << valoare[i] << " ";
    }

    void determinareIndiceRadacina() {
        //radacina va fi nodul care nu apare nici in vectorul stanga si nici in dreapta
        //aceasta functie determina radacina si o salveaza in variabila .radacina
        int size = marime + 1;
       
        int *v=new int[size];

        for (int i = 1; i <=marime; i++) {
            v[stanga[i]] = 1;
            v[dreapta[i]] = 1;
        }
        for(int i=1;i<=marime;i++)
            if (v[i] != 1) {
                radacina = i;
                return;
            }
            
    }

    void afisareValoriPreodrine(int radacina) {
        fout << valoare[radacina]<<" ";

        if (stanga[radacina] != 0) 
            afisareValoriPreodrine(stanga[radacina]);

        if (dreapta[radacina] != 0)
            afisareValoriPreodrine(dreapta[radacina]);
    }

    void afisareValoriInodrine(int radacina) {
        
        if (stanga[radacina] != 0)
            afisareValoriInodrine(stanga[radacina]);
        
        fout << valoare[radacina] << " ";

        if (dreapta[radacina] != 0)
            afisareValoriInodrine(dreapta[radacina]);
    }

    void afisareValoriPostordine(int radacina) {
        if (stanga[radacina] != 0)
            afisareValoriPostordine(stanga[radacina]);

        if (dreapta[radacina] != 0)
            afisareValoriPostordine(dreapta[radacina]);

        fout <<valoare[radacina] << " ";
    }

    int sumaValori(int radacina) {
        int sumst = 0;
        int sumdr = 0;
        if (stanga[radacina] != 0)
            sumst = sumaValori(stanga[radacina]);

        if (dreapta[radacina] != 0)
            sumdr = sumaValori(dreapta[radacina]);

        return valoare[radacina] + sumst + sumdr;
    }


    int diferentaSubarbori(int radacina) {
        //aceasta functie va calcula diferenta in valoare absoluta dintre subarborele stand si cel drept;

        int sumst = sumaValori(stanga[radacina]);
        int sumdr = sumaValori(dreapta[radacina]);

        int dif = sumst - sumdr;
        dif = abs(dif);
        return dif;

    }

    int nrNoduri(int radacina) {
       
        if (stanga[radacina] == 0 && dreapta[radacina] == 0) return 1;
        if (stanga[radacina] == 0 ) return nrNoduri(dreapta[radacina]) + 1;
        if (dreapta[radacina] == 0) return nrNoduri(stanga[radacina]) + 1;


        return nrNoduri(stanga[radacina]) + nrNoduri(dreapta[radacina]) + 1;
    }

    int nrNoduriPrime(int radacina) {
        int primeSt = 0, primeDr = 0;

        if (this->stanga[radacina] != 0)
           primeSt= nrNoduriPrime(stanga[radacina]);

        if (this->dreapta[radacina] != 0)
            primeDr = nrNoduriPrime(dreapta[radacina]);

        return primeSt + primeDr + nodPrim(radacina);

    }
    void setNivel(int radacina, int nivel) {
        //voi considera radacina pe nivelulul 1;
        this->nivel[radacina] = nivel;
        if (nivel > nivelmax)nivelmax = nivel;
        if (stanga[radacina] != 0) {
            setNivel(stanga[radacina], nivel + 1);
        }
        if (dreapta[radacina] != 0) {
            setNivel(dreapta[radacina], nivel + 1);
        }

    }
    void afisareCardinaliNivele() {
        for(int i=1;i<=nivelmax;i++){
            int a = 0;
            for (int j = 1; j <= marime; j++) {
                if (nivel[j] == i)a++;
            }
            fout << a << " ";
        }
    }


    private:
        int nodPrim(int nrNod) {
            if (ePrim(valoare[nrNod])) { return 1; cout << "1"; }
            return 0;

        }





};



int main()
{
    int n;
    fin >> n;
    ArboreBinar x(n);
    x.citireXStDr();
    x.determinareIndiceRadacina();
    x.setNivel(x.radacina, 1);
    fout << x.nivelmax << endl;
    x.afisareCardinaliNivele();

  


    return 0;
}



