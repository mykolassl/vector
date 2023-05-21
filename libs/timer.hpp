#pragma once

#include "lib.h"

class Timer {
private:
    time_point<high_resolution_clock> m_Pradzia, m_Pabaiga;
    milliseconds m_VisasLaikas, m_Skirtumas;

public:
    Timer()
        : m_VisasLaikas(milliseconds::zero()), m_Skirtumas(milliseconds::zero()) {}

    void start() {
        m_Pradzia = high_resolution_clock::now();
    }

    void end() {
        m_Pabaiga = high_resolution_clock::now();
        m_Skirtumas = duration_cast<milliseconds>(m_Pabaiga - m_Pradzia);
        m_VisasLaikas += m_Skirtumas;
    }

    void print(std::string tekstas) {
        std::cout << tekstas << " " << m_Skirtumas.count() / 1000.0 << "s" << std::endl;
    }

    void print_end(std::string tekstas) {
        std::cout << tekstas << " " << m_VisasLaikas.count() / 1000.0 << "s" << std::endl;
    }
};