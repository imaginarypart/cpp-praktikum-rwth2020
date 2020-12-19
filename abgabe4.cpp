//
//  main.cpp
//  A4
//
//  Created by Paul Wirkus on 15.12.20.
//

#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::istream;
using std::ostream;
using std::string;
using std::vector;
using std::list;



struct Datum
{
    int Tag;
    int Monat;
    int Jahr;
    bool gueltig() const
    {
        int Tag = this->Tag;
        int Monat = this->Monat;
        return Tag > 0 && Tag < 32 && Monat > 0 && Monat < 13;
    }
};
struct Person
{
    std::string Nachname;
    std::string Vorname;
    std::string Email;
    int MatNr;
    Datum Geburtstag;
};

typedef std::vector<Person> AdressbuchT;
typedef std::list<Datum> GebListeT;

void Datum_schreiben(ostream& out, const Datum& datum);
void Person_schreiben(ostream& out, const Person& person);
void AB_schreiben(ostream& out, const AdressbuchT& AB);
void Datum_lesen(istream& in, Datum& datum);
void Person_lesen(istream& in, Person& person);
void AB_lesen(istream& in, AdressbuchT& AB);
void geboren_in(int Monat, const AdressbuchT& AB, AdressbuchT& MonatAB);
void listeGueltigeGeb(const AdressbuchT& AB, GebListeT& geb);
bool operator<(const Datum& A, const Datum& B);
istream& operator>> (istream& in, Datum& dat);
ostream& operator<< (ostream& out, const Datum& dat);


ostream& operator<< (ostream& out, const Datum& dat)
{
    Datum_schreiben(out, dat);
    return out;
}

istream& operator>> (istream& in, Datum& dat)
{
    Datum_lesen(in, dat);
    return in;
}
void Datum_schreiben(ostream& out, const Datum& datum)
{
    out << datum.Tag << "." << datum.Monat << "."
        << datum.Jahr;
}

void Person_schreiben(ostream& out, const Person& person)
{
    out << person.Nachname << " " << person.Vorname << " "
        << person.Email << " " << person.MatNr << " ";
    Datum_schreiben( out, person.Geburtstag);
}

void AB_schreiben(ostream& out, const AdressbuchT& AB)
{
    for (int i= 0; i < AB.size(); i++)
    {
        Person_schreiben( out, AB[i]);
        out << "\n";
    }
}

void Datum_lesen(istream& in, Datum& datum)
{
    in >> datum.Jahr >> datum.Monat >> datum.Tag;
}

void Person_lesen(istream& in, Person& person)
{
    in  >> person.Nachname
        >> person.Vorname
        >> person.Email
        >> person.MatNr;
    Datum_lesen(in, person.Geburtstag);
}

void AB_lesen(istream& in, AdressbuchT& AB)
{
    do
    {
        Person person;
        Person_lesen(in, person);
        AB.push_back(person);
    } while (!in.eof());
}

void geboren_in(int Monat, const AdressbuchT& AB, AdressbuchT& MonatAB)
{
    for (int i = 0; i < AB.size(); i++)
    {
        if (AB[i].Geburtstag.Monat == Monat)
        {
            MonatAB.push_back(AB[i]);
        }
    }
}

void listeGueltigeGeb(const AdressbuchT& AB, GebListeT& geb)
{
    for (int i = 0; i < AB.size(); i++)
    {
        if (AB[i].Geburtstag.gueltig())
        {
            geb.push_back(AB[i].Geburtstag);
        }
    }
}

bool operator<(const Datum& A, const Datum& B)
{
    if (A.Jahr < B.Jahr)
    {
        return true;
    } else if (A.Jahr == B.Jahr and A.Monat < B.Monat)
    {
        return true;
    } else if (A.Jahr == B.Jahr and A.Monat == B. Monat and A.Tag < B.Tag)
    {
        return true;
    }
    return false;
}

int main()
{   //Objekt "Ich" definieren.
    Person Ich;
    Ich.Nachname = "Wirkus";
    Ich.Vorname = "Paul";
    Ich.Email = "paul.wirkus@rwth-aachen.de";
    Ich.MatNr = 405845;
    Ich.Geburtstag.Tag = 9;
    Ich.Geburtstag.Monat = 1;
    Ich.Geburtstag.Jahr = 2001;

    // In AB das Adressbuch unter AB.txt laden.
    AdressbuchT AB;
    std::ifstream ifs("/Users/paulwirkus/Documents/Git/A4/AB.txt");
    AB_lesen(ifs, AB);
    ifs.close();

    // Ich zu AB hinzufügen.
    AB.push_back(Ich);
    AB_schreiben(cout<<"AB:\n", AB);

    //Einträge mit dem Geburtstag im Januar listen.
    AdressbuchT MonatAB;
    geboren_in(1, AB, MonatAB);
    AB_schreiben(cout<<"MonatAB:\n", MonatAB);

    //Alle gültigen Geburtstage in MonatAB ausgeben.
    cout << "Davon mit gültigem Geburtstag:\n";
    GebListeT geb;
    listeGueltigeGeb(MonatAB, geb);
    for (GebListeT::iterator it = geb.begin(); it != geb.end(); it++)
    {
        cout << *it << std::endl;
    }

    //Nun die Liste MonatAB sortieren.
    geb.sort();
    cout << "Nun die sortierten gültigen Geburtstage:\n";
    for (GebListeT::iterator it = geb.begin(); it != geb.end(); it++)
    {
        cout << *it << std::endl;
    }



    /* Testen, ob Datum_lesen funktioniert
    std::ifstream ifs;
    ifs.open("/Users/paulwirkus/Documents/Git/A4/Datum.txt");
    Datum testdatum;
    Datum_lesen(ifs, testdatum);
    Datum_schreiben(std::cout, testdatum);
    ifs.close();
     */

    /*
    AdressbuchT AB;
    AB_lesen(...);
    cout << "Das Adressbuch hat " << AB.size() << " Eintraege:\n";
    AB_schreiben( cout, AB);
    // ...
    */

    return 0;
}
