//
//  main.cpp
//  Abgabe A3
//
//  Created by Paul Wirkus on 02.12.20.
//

#include <iostream>

void Ausgabe( const double *feld, int n );
double Durchschnitt (const double *feld, int n);
int min_pos(const double *feld, int n);
void sortiere(double *feld, int n);
void umdrehen(double *feld, int n);
double* glue( const double *feld1, int n1, const double *feld2, int n2);

int main() {
    // insert code here...
    double feld[] = {47, 1.1, 0, 8, 1.5};
    double feld1[] = {66, 44, 2, 3.1415};
    double *glued = glue(feld, 5, feld1, 4);
    Ausgabe(glued, 9);
    delete [] glued;
    return 0;
}

void Ausgabe( const double *feld, int n )
{
    for (int i=0; i<n; i++)
        std::cout << i << " " << feld[i] << std::endl;
}

double Durchschnitt (const double *feld, int n)
{
    double avg = 0;
    for (int i= 0; i<n; i++)
        avg += feld[i]/n;
    return avg;
}

int min_pos(const double *feld, int n)
{
    int minpos = 0;
    double min=feld[0];
    for (int i=0; i<n; i++)
    {
        if (feld[i]<min)
        {
            min = feld[i];
            minpos = i;
        }
    }
    return minpos;
}

void sortiere(double *feld, int n)
{
    double old;
    for (int i=0; i<n; i++)
    {
        old = feld[i];
        int minpos = min_pos(feld+i, n-i)+i;
        feld[i]=feld[minpos];
        feld[minpos] = old;
    }
}

void umdrehen(double *feld, int n)
{
    double buffer;
    for (int i = 0; i<floor(n/2); i++)
    {
        buffer = feld[i];
        feld[i] = feld[n-i-1];
        feld[n-i-1] = buffer;
    }
}

double* glue( const double *feld1, int n1, const double *feld2, int n2)
{
    double *feld = new double[n1+n2];
    for (int i = 0; i < n1; i++)
    {
        feld[i] = feld1[i];
    }
    for (int i = 0; i < n2; i++)
    {
        feld[n1+i] = feld2[i];
    }
    return feld;
}
