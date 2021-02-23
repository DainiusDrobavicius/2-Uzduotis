#include <iostream>
#include <regex>
#include <bits/stdc++.h>
#include <string>
#include <iomanip>
#include <stdlib.h>
using namespace std;

const int N = 1000;
struct Mokinys
{
    string vardas;
    string pavarde;
    int egzaminas;
    int nd[100];
    int ndSK;
    double galutinis;
};

void nuskaitymas(Mokinys mokinys[], int &mokiniuSK);
void galutinisVidurkis(Mokinys mokinys[], int mokiniuSK);
void galutinisMediana(Mokinys mokinys[], int mokiniuSK);
void spausdinimas(Mokinys mokinys[], int mokiniuSK, string gal1);

template <typename T>
bool isNumber(T x)
{
    std::string s;
    std::regex e("^-?\\d+");
    std::stringstream ss;
    ss << x;
    ss >> s;
    if (std::regex_match(s, e))
        return true;
    else
        return false;
}

int main()
{
    srand(time(NULL));
    Mokinys mokinys[N];
    int mokiniuSK = 0;
    nuskaitymas(mokinys, mokiniuSK);
    bool gal = true;
    string gal1;
    while (gal)
    {
        cout << "Norite medianos ar vidurkio ? [mediana/vidurkis] ";
        string galutinis;
        cin >> galutinis;
        if (galutinis == "vidurkis")
        {
            galutinisVidurkis(mokinys, mokiniuSK);
            gal1 = "Galutinis (Vid.)";
            gal = false;
        }
        else if (galutinis == "mediana")
        {
            galutinisMediana(mokinys, mokiniuSK);
            gal1 = "Galutinis (Med.)";
            gal = false;
        }
        else
        {
            cout << "Ivedete bloga simboli" << endl;
        }
    }
    spausdinimas(mokinys, mokiniuSK, gal1);
}

void nuskaitymas(Mokinys mokinys[], int &mokiniuSK)
{
    int skM;
    bool mok = true;
    cout << "Iveskite kiek bus skirtingu mokiniu [maz. 1] ";
    while (mok)
    {
        string skMM;
        cin >> skMM;
        if (isNumber(skMM) && stoi(skMM) >= 1)
        {
            skM = stoi(skMM);
            mokiniuSK = skM;
            mok = false;
        }
        else
        {
            cout << "Ivedete bloga simboli arba maziau 1" << endl;
            cout << "Iveskite kiek bus skirtingu mokiniu [maz. 1] ";
        }
    }
    for (int i = 0; i < skM; i++)
    {
        int skEGZ;
        bool patikrinimas = true;
        string patikrinti;
        cout << "Iveskite mokinio varda ";
        cin >> mokinys[i].vardas;
        cout << "Iveskite mokinio pavarde ";
        cin >> mokinys[i].pavarde;
        bool zodis = true;
        while (zodis)
        {
            cout << "Ar norite, kad siam mokiniui egzamino ir namu darbu rezultatai butu generuojami atsitiktinai? [taip/ne] ";
            cin >> patikrinti;
            if (patikrinti == "ne")
            {
                cout << "Iveskite mokinio egzamino rezultata ";
                while (patikrinimas)
                {
                    string ats;
                    cin >> ats;
                    if (isNumber(ats))
                    {
                        skEGZ = stoi(ats);
                        mokinys[i].egzaminas = skEGZ;
                        patikrinimas = false;
                    }
                    else
                    {
                        cout << "Ivedete bloga simboli" << endl;
                        cout << "Iveskite mokinio egzamino rezultata ";
                    }
                }
                cout << "Iveskite kiek namu darbu pazymiu norite ivesti, jei nezinote kiek - iveskite zodi [nezinau] ";
                patikrinimas = true;
                while (patikrinimas)
                {
                    string ats;
                    cin >> ats;
                    if (isNumber(ats))
                    {
                        int sk = stoi(ats);
                        mokinys[i].ndSK = sk;
                        for (int j = 0; j < sk; j++)
                        {
                            bool paz = true;
                            cout << "Iveskite " << j + 1 << " namu darbo pazymi ";
                            while (paz)
                            {
                                string ats1;
                                cin >> ats1;
                                if (isNumber(ats1))
                                {
                                    int ats11 = stoi(ats1);
                                    mokinys[i].nd[j] = ats11;
                                    paz = false;
                                }
                                else
                                {
                                    cout << "Ivedete bloga simboli" << endl;
                                    cout << "Iveskite " << j + 1 << " namu darbo pazymi ";
                                }
                            }
                        }
                        patikrinimas = false;
                    }
                    else if (ats == "nezinau")
                    {
                        bool baigta = true;
                        int ndSK = 0;
                        while (baigta)
                        {
                            cout << "Iveskite " << ndSK + 1 << " namu darbu pazymi, jei norite baigti - Iveskite zodi [viskas] ";
                            string nddd;
                            cin >> nddd;
                            if (isNumber(nddd) && stoi(nddd) <= 10 && stoi(nddd) >= 1)
                            {
                                mokinys[i].nd[ndSK] = stoi(nddd);
                                ndSK++;
                            }
                            else if (nddd == "viskas")
                            {
                                mokinys[i].ndSK = ndSK;
                                baigta = false;
                            }
                            else
                            {
                                cout << "Ivedete bloga simboli" << endl;
                            }
                        }
                        patikrinimas = false;
                    }
                    else
                    {
                        cout << "Ivedete bloga simboli" << endl;
                        cout << "Iveskite kiek namu darbu pazymiu norite ivesti, jei nezinote kiek - Iveskite zodi [nezinau] ";
                    }
                }
                zodis = false;
            }
            else if (patikrinti == "taip")
            {
                mokinys[i].egzaminas = rand() % 10 + 1;
                int pazymiuKiekis = rand() % 20;
                mokinys[i].ndSK = pazymiuKiekis;
                for (int k = 0; k < pazymiuKiekis; k++)
                {
                    mokinys[i].nd[k] = rand() % 10 + 1;
                }
                zodis = false;
            }
            else
            {
                cout << "Ivedete bloga simboli" << endl;
            }
        }
    }
}

void galutinisVidurkis(Mokinys mokinys[], int mokiniuSK)
{
    for (int i = 0; i < mokiniuSK; i++)
    {
        double sum = 0;
        for (int j = 0; j < mokinys[i].ndSK; j++)
        {
            sum += mokinys[i].nd[j];
        }
        mokinys[i].galutinis = 0.4 * (sum / mokinys[i].ndSK) + 0.6 * mokinys[i].egzaminas;
    }
}

void galutinisMediana(Mokinys mokinys[], int mokiniuSK)
{
    for (int i = 0; i < mokiniuSK; i++)
    {
        sort(mokinys[i].nd, mokinys[i].nd + mokinys[i].ndSK);
        if (mokinys[i].ndSK % 2 != 0)
        {
            mokinys[i].galutinis = 0.4 * mokinys[i].nd[mokinys[i].ndSK / 2] + 0.6 * mokinys[i].egzaminas;
        }
        else
        {
            mokinys[i].galutinis = 0.4 * ((mokinys[i].nd[mokinys[i].ndSK / 2] + mokinys[i].nd[(mokinys[i].ndSK - 1) / 2]) / 2.0) + 0.6 * mokinys[i].egzaminas;
        }
    }
}

void spausdinimas(Mokinys mokinys[], int mokiniuSK, string gal1)
{
    cout << setw(15) << left << "Pavarde";
    cout << setw(15) << left << "Vardas";
    cout << setw(15) << left << gal1;
    cout << endl;
    for (int i = 0; i < mokiniuSK; i++)
    {
        cout << setw(15) << left << mokinys[i].pavarde;
        cout << setw(15) << left << mokinys[i].vardas;
        cout << setw(15) << left << fixed << setprecision(2) << mokinys[i].galutinis;
        cout << endl;
    }
}