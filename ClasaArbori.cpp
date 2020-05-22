// In acest proiect vom crea o clasa de arbori binari
#include <iostream>
#include <fstream>
#include <algorithm>
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
        for (int i = 1; i <= marime; i++) stanga[i] = 0;
        this->dreapta = new int[marime + 1];
        for (int i = 1; i <= marime; i++) dreapta[i] = 0;
        this->valoare = new int[marime + 1];
        for (int i = 1; i <= marime; i++) valoare[i] = 0;
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
        int* x = new int[marime + 1];
        int p = 0;
        for (int i = 1; i <= marime; i++)
            if (stanga[i] == 0 && dreapta[i] == 0) {
                x[++p] = valoare[i];
            }
        sort(x+1, x+p+1);

        for (int i = 1; i <= p; i++)
            fout << x[i] << " ";
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

    void afisareValoriInordine(int radacina) {
        
        if (stanga[radacina] != 0)
            afisareValoriInordine(stanga[radacina]);
        
        fout << valoare[radacina] << " ";

        if (dreapta[radacina] != 0)
            afisareValoriInordine(dreapta[radacina]);
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

    int citireLant() {
        int x;
        fin >> x;
        if (x != 0) {
            int p = ++marime;
            valoare[p] = x;
            stanga[p] = citireLant();
            dreapta[p] = citireLant();
            return p;
        }
        else return 0;
    }

    void creareBST() {
        radacina = 1;
        fin >> valoare[1];

        for (int i = 2; i <= marime; i++) {
            fin >> valoare[i];
            BST(i,radacina);
        }
    }

    int nrNod(int radacina) {
        //this functions counts the number of nodes witn only one descendent;
        if (radacina == 0)return 0;

        if (int(bool(stanga[radacina])) + int(bool(dreapta[radacina])) == 1)
            return 1 + nrNod(stanga[radacina]) + nrNod(dreapta[radacina]);
        else return nrNod(stanga[radacina]) + nrNod(dreapta[radacina]);
    }

    int maxVal(int radacina) {
        if (radacina == 0)return 0;
        int m = max(maxVal(stanga[radacina]), maxVal(dreapta[radacina]));

            if (m > valoare[radacina])return m;
        return valoare[radacina];

    }

    int levelSum( int level) {
        //must be run after setNivel;
        int s = 0;
        for (int i = 1; i <= marime; i++) {
            if (nivel[i] == level) s+= valoare[i];
        }
        return s;
    }
    int minimPrim(int radacina) {
        if (radacina == 0) return 999999999;
        int s = minimPrim(stanga[radacina]);
        int d = minimPrim(dreapta[radacina]);
        s = min(s, d);
        if (nodPrim(radacina) == 1)
            s = min(s, valoare[radacina]);
        return s;


    }

    void parcurgereNivel(){
    //must be run afte setNivel
        for (int i = 1; i <= nivelmax; i++) {
            for (int j = 1; j <= marime; j++) {
                if (nivel[j] == i)fout << valoare[j] << " ";
            }
        }
        fout << '\n';
    
    }
    
    
    private:
        void BST(int indice, int radacina) {
            if (valoare[indice] <= valoare[radacina]) {
                if (stanga[radacina] == 0) {
                    stanga[radacina] = indice;
                }
                else BST(indice, stanga[radacina]);
            }
            else {
                if (dreapta[radacina] == 0) {
                    dreapta[radacina] = indice;
                }
                else BST(indice, dreapta[radacina]);
            }

        }

        
        int nodPrim(int nrNod) {
            if (ePrim(valoare[nrNod])) { return 1; }
            return 0;

        }
};



int main()
{
    int n;
    fin >> n;
    ArboreBinar x(n);
    x.creareBST();
    x.afisareValoriInordine(x.radacina);


    
  


    return 0;
}



