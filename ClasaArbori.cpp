// In acest proiect vom crea o clasa de arbori binari
#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("Arbori.in");
ofstream fout("Arbori.out");

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
    // i=numarul de ordine al fiecarui nod

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




};



int main()
{
    int n;
    fin >> n;
    ArboreBinar x(n);
    x.citireXStDr();
    x.determinareIndiceRadacina();
   x.afisareValoriPreodrine(x.radacina);

 

  


    return 0;
}



