#pragma once

#include "studentas.h"
#include "lib.h"


void ivesti_ranka();
void generuoti_failus();
void pildyti(Studentas& , bool& , int );
void spausdinti(const Studentas );

void isvesti_faila(Vector<Studentas>& grupe, string failoPav);

void skaityti_faila();

void dalinimas_1(Vector<Studentas>& grupe, Vector<Studentas>& vargsai, Vector<Studentas>& protingi);

void dalinimas_2(Vector<Studentas>& grupe, Vector<Studentas>& protingi);