#include <iostream>
#include "solver.hpp"
#include <cstdlib>
#include <time.h>
using namespace std;

bool check_number(string str) {
    for (int i = 0; i < str.length(); i++) {
        if (!isdigit(str[i])) {
            return false;
        } else {
            
        }
    }
}

bool inputCharValid (string input)
// Melakukan konversi dan validasi input berupa string ke integer
// Apakah valid (bernilai antara 2 - 10)
{
    // KAMUS LOKAL
    char c[input.length()];
    int i=0;

    // ALGORITMA
    // Instansiasi for loop
    while (i < input.length()) {
        c[i] = input[i];
        i++;
    }

    // Validasi input
    if (c[0] == 'A' || c[0] == 'K' || c[0] == 'Q' || c[0] == 'J') {
        return true;
    } else {
        return false;
    }
}

int main() {
    string val = "3";
    string p;
    bool valid = false;
    auto result = std::stoi(val);
    do {
        cout << "Masukkan 4 buah kartu" << endl;
        cin >> p;
        cout << p[0];
        if (inputCharValid(p)) {
            valid = true;
            break;
        }
    } while (!valid);
    cout << "sudah valid" << endl;
}