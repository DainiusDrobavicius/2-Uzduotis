#include <iostream>
#include <regex>
#include <bits/stdc++.h>
#include <string>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <fstream>

using namespace std;

const int N = 10000;

//------------mokiniu struktura-----------------
struct Mokinys
{
    string vardas;
    string pavarde;
    int egzaminas;
    vector<int> nd;
    double galutinis;
};
//----------------------------------------------

void failoskaitymas(Mokinys mokinys[]);
void nuskaitymas(Mokinys mokinys[], int &mokiniuSK);
void galutinisVidurkis(Mokinys mokinys[], int mokiniuSK);
void galutinisMediana(Mokinys mokinys[], int mokiniuSK);
void spausdinimas(Mokinys mokinys[], int mokiniuSK, string gal1);
void rusiavimas(Mokinys mokinys[], int mokiniuSK);

//internete rasta funkcija atpazistanti ar string yra tik skaiciai--
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
//-----------------------------------------------------------------

int main()
{
    srand(time(NULL));
    Mokinys mokinys[N];
    int mokiniuSK = 0;
    nuskaitymas(mokinys, mokiniuSK);
    bool gal = true;
    string gal1;
    // -------tikrinama ar reikia medianos ar vidurkio---------
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
    // ----------------------------------------------------------
    rusiavimas(mokinys, mokiniuSK);
    spausdinimas(mokinys, mokiniuSK, gal1);
}

// nuskaito duomenis---------------------------------------------
void nuskaitymas(Mokinys mokinys[], int &mokiniuSK)
{
    int skM;
    bool mok = true;
    bool good = true;
    string failas;
    //tikrina ar norima nuskaityti duomenis is failo ir irasyti paciam ir ar nera blogu simboliu
    while (good)
    {
        cout << "Ar norite duomenis nuskaityti is failo [taip/ne] ";
        cin >> failas;
        // jei pasirinkta "taip" prasides failo nuskaitymas
        if (failas == "taip")
        {
            mokiniuSK = N;
            failoskaitymas(mokinys);
            good = false;
        }
        // jei pasirinkta "ne" prasides duomenu ivedimas
        else if (failas == "ne")
        {
            while (mok)
            {
                cout << "Iveskite kiek bus skirtingu mokiniu [maz. 1] ";
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
                // patikrina ar ivesta taip/ne ir ar neivesta netinkamu simboliu arba kitu zodziu
                while (zodis)
                {
                    cout << "Ar norite, kad siam mokiniui egzamino ir namu darbu rezultatai butu generuojami atsitiktinai? [taip/ne] ";
                    cin >> patikrinti;
                    // jei ivesta ne pradeda klausineti rezultatu
                    if (patikrinti == "ne")
                    {
                        cout << "Iveskite mokinio egzamino rezultata ";
                        // praso egzamino rezultato ir tikrina ar ivestas teisingas simbolis
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
                        //tikrina kiek namu darbu reiks ivesti siam mokiniui arba pasirenkama, kad nezino ir tikrina ar neivesta netinkamu simboliu
                        while (patikrinimas)
                        {
                            string ats;
                            cin >> ats;
                            if (isNumber(ats))
                            {
                                int sk = stoi(ats);
                                int j = 0;
                                string ats1;
                                while (j < sk)
                                {
                                    bool paz = true;
                                    while (paz)
                                    {
                                        cout << "Iveskite " << j + 1 << " namu darbo pazymi ";
                                        cin >> ats1;
                                        if (isNumber(ats1))
                                        {
                                            int ats11 = stoi(ats1);
                                            mokinys[i].nd.push_back(ats11);
                                            paz = false;
                                            j++;
                                        }
                                        else
                                        {
                                            cout << "Ivedete bloga simboli" << endl;
                                        }
                                    }
                                }

                                patikrinimas = false;
                            }
                            // jei buvo pasirinkta kad nezino kiek namu darbu pazymiu reiks ivesti pradeda juos ivedineti tol, kol bus parasyta 'viskas'
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
                                        mokinys[i].nd.push_back(stoi(nddd));
                                        ndSK++;
                                    }
                                    else if (nddd == "viskas")
                                    {
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
                    // jei buvo pasirinkta generuoti pazymius
                    else if (patikrinti == "taip")
                    {
                        mokinys[i].egzaminas = rand() % 10 + 1;
                        int pazymiuKiekis = rand() % 20;
                        for (int k = 0; k < pazymiuKiekis; k++)
                        {
                            mokinys[i].nd.push_back(rand() % 10 + 1);
                        }
                        zodis = false;
                    }
                    else
                    {
                        cout << "Ivedete bloga simboli" << endl;
                    }
                }
            }

            good = false;
        }
        else
        {
            cout << "Ivedete bloga simboli";
        }
    }
}
//----------------------------------------------------------------------------------------

// ---------------------apskaiciuoja galutini vidurki-------------------------------------
void galutinisVidurkis(Mokinys mokinys[], int mokiniuSK)
{
    for (int i = 0; i < mokiniuSK; i++)
    {
        double sum = 0;
        for (int j = 0; j < mokinys[i].nd.size(); j++)
        {
            sum += mokinys[i].nd[j];
        }
        mokinys[i].galutinis = 0.4 * (sum / mokinys[i].nd.size()) + 0.6 * mokinys[i].egzaminas;
    }
}
//------------------------------------------------------------------------------------------

//------------------------apskaiciuoja galutine mediana-------------------------------------
void galutinisMediana(Mokinys mokinys[], int mokiniuSK)
{
    for (int i = 0; i < mokiniuSK; i++)
    {
        sort(mokinys[i].nd.begin(), mokinys[i].nd.end());
        if (mokinys[i].nd.size() % 2 != 0)
        {
            mokinys[i].galutinis = 0.4 * mokinys[i].nd[mokinys[i].nd.size() / 2] + 0.6 * mokinys[i].egzaminas;
        }
        else
        {
            mokinys[i].galutinis = 0.4 * ((mokinys[i].nd[mokinys[i].nd.size() / 2] + mokinys[i].nd[(mokinys[i].nd.size() - 1) / 2]) / 2.0) + 0.6 * mokinys[i].egzaminas;
        }
    }
}
//--------------------------------------------------------------------------------------------

//----------------------spausdina duomenis----------------------------------------------------
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
//--------------------------------------------------------------------------------------------

//-----------------------nuskaito duomenis is failo-------------------------------------------
void failoskaitymas(Mokinys mokinys[])
{
    string laikinas;
    int pazymiuSK = 0;
    ifstream GET("kursiokai.txt");
    GET >> laikinas >> laikinas;
    GET >> laikinas;
    while (laikinas.rfind("ND", 0) == 0)
    {
        pazymiuSK++;
        GET >> laikinas;
    }
    for (int i = 0; i < N; i++)
    {
        GET >> laikinas;
        mokinys[i].vardas = laikinas;
        GET >> laikinas;
        mokinys[i].pavarde = laikinas;
        for (int j = 0; j < pazymiuSK; j++)
        {
            GET >> laikinas;
            mokinys[i].nd.push_back(stoi(laikinas));
        }
        GET >> laikinas;
        mokinys[i].egzaminas = stoi(laikinas);
    }
    GET.close();
}
//--------------------------------------------------------------------------------------------

//--------------------mokiniu rusiavimas------------------------------------------------------
void rusiavimas(Mokinys mokinys[], int mokiniuSK)
{
    for (int i = 0; i < mokiniuSK - 1; i++)
    {
        for (int j = 0; j < mokiniuSK - i - 1; j++)
        {
            if (mokinys[j].pavarde > mokinys[j + 1].pavarde)
            {
                swap(mokinys[j], mokinys[j + 1]);
            }
        }
    }
}
//--------------------------------------------------------------------------------------------