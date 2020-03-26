#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

class AFN
{
    int q;          //numarul de stari totale
    int f;          //numarul de  stari finale
    int *F;         //starile finale
    int g;          //numarul de  tranzitii 
    struct tranz
    {
        int a,b;    //tranzitiile
        char c;     //litera prin care se face tranzitia
    } *G;
    int stc;         //starea curenta
    int ok;     //ia valoarea 0 daca cuvantul nu este acceptat si 1 in caz contrar
public:
    AFN(char *fisier)
    {
        int i;
        ifstream in(fisier);
        in>>q>>f;               //citesc nr. stari totale si nr. stari finale
        F=new int[f];
        for (i=0;i<f;i++)
            in>>F[i];           //citesc starea/starile finale
        in>>g;                  //citesc numarul de tranzitii
        G=new tranz[g];
        for (i=0;i<g;i++)
        {
            in>>G[i].a>>G[i].b>>G[i].c;
        }
        stc=0;                   //starea curenta=0
        ok=0;             
    }
    int verificare(char *cuvant, int stc, int pozitia_in_cuvant);           //afiseaza 1 daca cuvantul apartine alfabetului,
    //0 in caz contrar
};



int AFN::verificare(char *cuvant, int stc, int pozitia_in_cuvant)
{
    int i;
    //daca am terminat cuvantul si nu am depasit numarul de stari
    if ((pozitia_in_cuvant==strlen(cuvant))&&(stc<=q))
    {
        //verific daca ma aflu intr-o stare finala
        for (i=0;i<f;i++)
            if (stc==F[i])
            {
                ok=1;
                return 1;
            }
    }
    else
    {
        for (i=0;i<g;i++)
        {
            if (ok==1)
                return 1;
            //verific daca starea mea curenta si litera curenta din cuvant se afla in vreun triplet
            if ((G[i].a==stc)&&(G[i].c==cuvant[pozitia_in_cuvant]))
            {
                verificare(cuvant,G[i].b,pozitia_in_cuvant+1);
            }
        }

        return 0;
    }
}

int main()
{
    //declaram un obiect de tip AFN
    AFN automat("afn.in");
    //apelam metoda "verificare"  cu parametrii: cuvantul ce ne dorim a fi testat,
    //starea initiala si pozitia in cuvant
    char cuv[100];
        cin>>cuv; //citim cuvantul de la consola
    if (automat.verificare(cuv,0,0)==1)
        cout<<"Cuvantul este acceptat!";
    else
        cout<<"Cuvantul nu este acceptat!";

    return 0;
}
//Citirea se face in modul urmator:
//cuvantul se citeste de la consola;
//din fisier se citeste:
//numarul de stari,
//numarul de stari finale,
//starile finale,
//numarul de tranzitii,
//tranzitiile.

