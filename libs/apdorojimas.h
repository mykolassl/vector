#pragma once

#include "studentas.h"
#include "lib.h"


void ivesti_ranka();
void generuoti_failus();
void pildyti(Studentas& , bool& , int );
void spausdinti(const Studentas );

void isvesti_faila(std::vector<Studentas>& grupe, string failoPav);

void skaityti_faila();

void dalinimas_1(std::vector<Studentas>& grupe, std::vector<Studentas>& vargsai, std::vector<Studentas>& protingi);

void dalinimas_2(std::vector<Studentas>& grupe, std::vector<Studentas>& protingi);