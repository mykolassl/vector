#include "../libs/lib.h"
#include "../libs/studentas.h"

const int varduKiekis = 16;

const string vardaiVyr[varduKiekis] = {
    "Lukas", "Matas", "Jokubas", "Jonas", 
    "Nojus", "Kajus", "Dominykas", "Joris", 
    "Mantas", "Rokas", "Tomas", "Tauras", 
    "Martynas", "Danielius", "Emilis", "Teodoras"};
const string pavardesVyr[varduKiekis] = {
    "Gricius", "Baranauskas", "Kazlauskas", "Balcius", 
    "Stankevicius", "Balciunas", "Butkus", "Morkunas", 
    "Pocius", "Savickas", "Stonkus", "Petrauskas", 
    "Paulauskas", "Jankauskas", "Zukauskas", "Simkunas"};

const string vardaiMot[varduKiekis] = {
    "Leja", "Emilija", "Liepa", "Amelija", 
    "Gabija", "Lukne", "Kamile", "Ema",
    "Sofija", "Patricija", "Austeja", "Vilte", 
    "Ugne", "Urte", "Saule", "Igle"};
const string pavardesMot[varduKiekis] = {
    "Baranauskaite", "Kazlauskaite", "Balciunaite", "Stankeviciute",
    "Cicenaite", "Simkute", "Butkaite", "Morkunaite", 
    "Pociute", "Savickaite", "Stonkaite", "Petrauskaite",
    "Paulauskaite", "Jankauskaite", "Zukauskaite", "Vasiliauskaite"};

double apskaiciuoti_vidurki(std::vector<int> ndPazymiai) {
    int sum = accumulate(ndPazymiai.begin(), ndPazymiai.end(), 0);
    
    return (double)sum / ndPazymiai.size();
}

double apskaiciuoti_mediana(std::vector<int> ndPazymiai) {
    sort(ndPazymiai.begin(), ndPazymiai.end());

    if (ndPazymiai.size() % 2 == 1) {
        return ndPazymiai[ndPazymiai.size() / 2];
    } else {
        return (ndPazymiai[ndPazymiai.size() / 2] + ndPazymiai[ndPazymiai.size() / 2 - 1]) / 2.0;
    }
}

void generuoti_pazymius(std::vector<int>& ndPazymiai, int& egzaminas) {
    random_device r_d;
    mt19937 mt(r_d());
    uniform_int_distribution<int> dist(1, 10);

    for (auto& i : ndPazymiai) i = dist(mt);
    egzaminas = dist(mt);
}

void generuoti_faila(int studKiekis, int ndKiekis) {
    random_device r_d;
    mt19937 mt(r_d());
    uniform_int_distribution<int> distLytis(0, 1), distVardai(0, varduKiekis - 1), distPazymiai(1, 10);

    stringstream ssOut;
    ssOut << left << setw(20) << "Vardas"  << setw(20) << "Pavarde";
    for (int i = 1; i <= ndKiekis; i++) ssOut << right << setw(10) << ("ND" + to_string(i));
    ssOut << setw(10) << "Egz." << endl;

    for (int i = 0; i < studKiekis; i++) {
        int lytis = distLytis(mt);

        if (lytis == 0) {
            ssOut << left << setw(20) << vardaiVyr[distVardai(mt)] << setw(20) << pavardesVyr[distVardai(mt)];
        } else {
            ssOut << left << setw(20) << vardaiMot[distVardai(mt)] << setw(20) << pavardesMot[distVardai(mt)];
        }

        for (int i = 0; i < ndKiekis; i++) ssOut << right << setw(10) << distPazymiai(mt);        
        ssOut << setw(10) << distPazymiai(mt) << (i != studKiekis - 1 ? "\n" : "");
    }

    ofstream fOut("studentai_" + to_string(studKiekis) + ".txt");
    fOut << ssOut.rdbuf();
    fOut.close();
}