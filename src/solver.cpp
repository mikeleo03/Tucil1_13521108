/* File utama solver.cpp */
// Impor Modul Eksternal
#include <iostream>
#include "solver.hpp"
#include <cstdlib>
#include <chrono>
#include <fstream>
using namespace std;
using namespace std::chrono;

// Inisialisasi Variabel Global
int a, b, c, d;        // Bilangan yang menjadi masukan untuk pemrosesan
string p, q, r, s;     // Inisialisasi dengan string 1 char untuk mempermudah konversi ke bilangan
// Inisialisasi senarai dengan 25 elemen yang mencakup semua kombinasi, 4! = 24 dengan 1 elemen block
int elem1[25], elem2[25], elem3[25], elem4[25];
int NEffElem = 0;          // Nilai efektif dari senarai kombinasi
// 2 buah senarai untuk menyimpan solusi dan solusi unik
string solution[300];
string solutionunique[300];
// Nilai efektif dari kedua senarai diatas
int NEffSol = 0;      
int NEffSolUni = 0;


// Deklarasi dan Realisasi Fungsi dan Prosedur dari Header

void randomNumber (int* nums) 
// Membangkitkan angka secara acak (random number generator)
// Seeds yang digunakan adalah waktu saat ini, sehingga relatif sulit terulang kembali
{
    // KAMUS LOKAL
    int i;
    int num;
    
    // ALGORITMA
    num = (rand() % 13) + 1;
    *nums = num;
}

void generate4 (int* card1, int* card2, int* card3, int* card4)
// Mengenerate 4 angka random
// Menggunakan prosedur randomNumber yang telah diinisiasi sebelumnya
{
    // KAMUS LOKAL

    // ALGORITMA
    randomNumber(card1);
    randomNumber(card2);
    randomNumber(card3);
    randomNumber(card4); 
}

bool checkNumber (string str)
// Melakukan pengecekan apakah string yang masuk benar merupakan string atau integer 
// Untuk memudahkan perlakuan konversi string ke integer
{
    // KAMUS LOKAL
    int i;

    // ALGORITMA
    for (i = 0; i <= str.length(); i++) {
        if (!isdigit(str[i])) {
            return false;
        } else {
            return true;
        }
    }
}

bool inputNumberValid (string input)
// Melakukan konversi dan validasi input berupa string ke integer
// Apakah valid (bernilai antara 2 - 10)
{
    // KAMUS LOKAL
    int result;

    // ALGORITMA
    result = std::stoi(input);
    if (result >= 2 && result <= 10) {
        return true;
    } else {
        return false;
    }
}

bool inputCharValid (string input)
// Melakukan analisis elemen pertama dari sebuah string
// Apakah valid (bernilai A, K, Q, atau J)
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
    if ((c[0] == 'A' || c[0] == 'K' || c[0] == 'Q' || c[0] == 'J') && input.length() == 1) {
        return true;
    } else {
        return false;
    }
}

int chartoInt (string input)
// Melakukan konversi dari karakter karater yang mungkin dalam sebuah kartu menjadi sebuah integer
{
    // KAMUS LOKAL

    // ALGORITMA
    switch (input[0]) {
        case 'A' : return 1; break;
        case 'J' : return 11; break;
        case 'Q' : return 12; break;
        case 'K' : return 13; break;
    }
}

void inttoChar (int input, string *target)
// Melakukan konversi dari integer yang mungkin dalam sebuah kartu menjadi karakter kartu yang bersesuaian
{
    // KAMUS LOKAL

    // ALGORITMA
    if (input >= 2 && input <= 10) {
        *target = to_string(input);
    } else {
        switch (input) {
            case 1  : *target = 'A'; break;
            case 11 : *target = 'J'; break;
            case 12 : *target = 'Q'; break;
            case 13 : *target = 'K'; break;
        }
    }
}

char operations (int ops) 
// Sebelumnya membuat representasi dari operasi dalam bentuk angka
// Fungsi ini mengembalikan bentuk angka dalam operasi menjadi operasi + - * /
{
    // KAMUS LOKAL

    // ALGORITMA
    switch (ops) {
        case 1 : return ('+');
        case 2 : return ('-');
        case 3 : return ('*');
        case 4 : return ('/');
    }
}

float calculate (int ops, float x, float y)
// Melakukan operasi bilangan real antara dua bilangan yang representasi nya diubah
// menjadi bilangan real (untuk memudahkan real division) dan operator dalam angka
{
    // KAMUS LOKAL

    // ALGORITMA
    switch (ops) {
        case 1 : return (x + y);
        case 2 : return (x - y);
        case 3 : return (x * y);
        case 4 : return ((float) x / (float) y);
    }
}

void checkCombination (int a, int b, int c, int d)
// Melakukan pengecekan terhadap semua kombinasi yang mungkin dari masukan a, b, c, d
// Kombinasi yang sudah ada tidak dimasukkan ke dalam senarai
// Adapun kombinasi yang belum ada akan dimasukkan ke dalam senarai analisis
{
    // KAMUS LOKAL
    int i;
    bool found;

    // ALGORITMA
    // Inisialisasi
    i = 1, found= false;

    while (i < NEffElem && !found) {
        if (a == elem1[i] && b == elem2[i] && c == elem3[i] && d == elem4[i]) {
            // Jika masing-masing elemen yang bersesuaian sama, sudah ada dalam senarai
            found = true;
        } else {
            // Jika tidak maka akan dilakukan increment hingga ditemukan
            i++;
        }
    }
    // Berhasil keluar dari kalang, kondisi yang mungkin adalah i = NEffElem atau not found
    // Jika not found, maka akan nilai tersebut akan dimasukkan ke dalam senarai
    if (!found) {
        NEffElem++;
        elem1[NEffElem] = a; elem2[NEffElem] = b; elem3[NEffElem] = c; elem4[NEffElem] = d;
    }
}

void processRes (int p, int q, int r, int w, int x, int y, int z)
// Melakukan hasil kalkulasi dengan bilangan masukan w, x, y, z dan operator p, q, r
// Operator p, q, r dihasilkan melalui skema brute force operator yang mungkin untuk mencapai nilai 24
{
    // KAMUS LOKAL
    float res;
    string sol, bil1, bil2, bil3, bil4;
    // Konversi bilangan ke string
    inttoChar(w, &bil1);
    inttoChar(x, &bil2);
    inttoChar(y, &bil3);
    inttoChar(z, &bil4);

    // ALGORITMA
    // Penanganan terhadap kasus penyusunan dan kombinasi operator yang mungkin
    // ((w ops x) ops y) ops z
    res = calculate(r, calculate(q, calculate(p, (float) w, (float) x), (float) y),(float) z);
    if (res > 23.99999 && res < 24.00001) { // menghandle floating point akibat real division
        // Membuat solusi dalam bentuk string dan memasukkannya ke dalam senarai solusi
        sol = "((" + bil1 + " " + operations(p) + " " + bil2 + ") " +
        operations(q) + " " + bil3 + ") " + operations(r) + " " + bil4;
        NEffSol++;
        solution[NEffSol] = sol;
    }

    // (w ops (x ops y)) ops z
    res = calculate(r, calculate(p, (float) w, calculate(q, (float (x)), (float) y)), (float) z);
    if (res > 23.99999 && res < 24.00001) {
        sol = "(" + bil1 + " " + operations(p) + " (" + bil2 + " " + operations(q) +
        " " + bil3 + ")) " + operations(r) + " " + bil4;
        NEffSol++;
        solution[NEffSol] = sol;
    }

    // w ops ((x ops y) ops z)
    res = calculate(p, (float) w, calculate(r, calculate(q, (float) x, (float) y), float (z)));
    if (res > 23.99999 && res < 24.00001) {
        sol = bil1 + " " + operations(p) + " ((" + bil2 + " " + operations(q) + " " +
        bil3 + ") " + operations(r) + " " + bil4 + ")";
        NEffSol++;
        solution[NEffSol] = sol;
    }

    // w ops (x ops (y ops z))
    res = calculate(p, (float) w, calculate(q, (float) x, calculate(r, (float) y, (float) z)));
    if (res > 23.99999 && res < 24.00001) {
        sol = bil1 + " " + operations(p) + " (" + bil2 + " " + operations(q) + " (" +
        bil3 + " " + operations(r) + " " + bil4 + "))";
        NEffSol++;
        solution[NEffSol] = sol;
    }

    // (w ops x) ops (y ops z)
    res = calculate(q, calculate(p, (float) w, (float) x), calculate(r, (float) y, (float) z)); 
    if (res > 23.99999 && res < 24.00001) {
        sol = "(" + bil1 + " " + operations(p) + " " + bil2 + ") " +
        operations(q) + " (" + bil3 + " " + operations(r) + " " + bil4 + ")";
        NEffSol++;
        solution[NEffSol] = sol;
    }
}

void bruteForce (int w, int x, int y, int z) 
// Melakukan brute-force untuk menemukan pasangan solusi operator yang mungkin bagi bilangan 
// w, x, y, dan z untuk mendapatkan nilai 24.
// Digunakan operator p, q, dan r dengan 3 kalang bersarang
{
    // KAMUS LOKAL
    int p, q, r;

    // ALGORITMA
    for (p = 1; p < 5; p++) {
        for (q = 1; q < 5; q++) {
            for (r = 1; r < 5; r++) {
                // Melakukan pemrosesan hasil untuk setiap operator yang mungkin
                processRes (p, q, r, w, x, y, z);
            }
        }
    }
}

void input ()
// Menangani proses input - masukan dari pengguna
// Pengguna dapat memilih untuk memasukkan input atau membangkitkan bilangan secara acak
{
    // KAMUS LOKAL
    string com;
    int pil;
    bool valid = false;

    // ALGORITMA
    cout << "====================  INPUT  ====================" << endl;
    while (!valid) {
        cout << "Tentukan cara membuat masukan" << endl;
        cout << " 1. Berdasarkan masukan dari pengguna" << endl;
        cout << " 2. Lakukan pembangkitan pasangan kartu acak" << endl;
        cout << "" << endl;
        cout << "Pilih mode" << endl << ">> ";
        cin >> com;
        if (checkNumber(com)) {
            pil = std::stoi(com);
            if (pil != 1 && pil != 2) {
                cout << "Masukan salah, ulangi!" << endl;
                cout << "-------------------------------------------------" << endl;
                valid = false;
            } else {
                valid = true;
            }
        } else {
            cout << "Masukan salah, ulangi!" << endl;
            cout << "-------------------------------------------------" << endl;
            valid = false;
        }
    }

    // Keluar dari kalang, artinya input 1 atau 2
    // Pemrosesan berdasarkan kondisi
    if (pil == 1) {
        bool valid1 = false;
        bool valid2 = false;
        bool valid3 = false;
        bool valid4 = false;
        bool validful = valid1 && valid2 && valid3 && valid4;
        // Handling input lebih banyak dari 4 melalui analisis konversi panjang string
        char input4[100];
        string inputlast;
        cout << " " << endl;
        cout << "============  MASUKAN DARI PENGGUNA  ============" << endl;
        while (!validful) {
            cout << "Masukkan 4 buah kartu (A, 2-10, J, Q, atau K)" << endl << ">> ";
            cin >> p >> q >> r;
            // Skema berbeda saat meminta kartu keempat
            cin.getline(input4,100);

            // Melakukan handling spacing di awal pada fungsi getline dengan mendefinisikan
            // array of character yang baru
            char* input5;
            input5 = (char*)malloc(100);
            for (int i = 0; input4[i] != '\0'; i++) {
                input5[i] = input4[i + 1];
            }
            // Melakukan konversi array of char ke string s untuk divalidasi
            s = input5;

            // Skema validasi per input p, q, r, s
            // Validasi input p
            if (checkNumber(p)) {
                if (inputNumberValid(p)) {
                    a = std::stoi(p);
                    valid1 = true;
                } else {
                    cout << "> Masukan angka pertama tidak valid" << endl;
                    valid1 = false;
                }
            } else {
                if (inputCharValid(p)){
                    a = chartoInt(p);
                    valid1 = true;
                } else {
                    cout << "> Masukan karakter pertama tidak valid" << endl;
                    valid1 = false;
                }
            }
            // Validasi input q
            if (checkNumber(q)) {
                if (inputNumberValid(q)) {
                    b = std::stoi(q);
                    valid2 = true;
                } else {
                    cout << "> Masukan angka kedua tidak valid" << endl;
                    valid2 = false;
                }
            } else {
                if (inputCharValid(q)){
                    b = chartoInt(q);
                    valid2 = true;
                } else {
                    cout << "> Masukan karakter kedua tidak valid" << endl;
                    valid2 = false;
                }
            }
            // Validasi input r
            if (checkNumber(r)) {
                if (inputNumberValid(r)) {
                    c = std::stoi(r);
                    valid3 = true;
                } else {
                    cout << "> Masukan angka ketiga tidak valid" << endl;
                    valid3 = false;
                }
            } else {
                if (inputCharValid(r)){
                    c = chartoInt(r);
                    valid3 = true;
                } else {
                    cout << "> Masukan karakter ketiga tidak valid" << endl;
                    valid3 = false;
                }
            }
            // Validasi input s
            // Validasi input berlebih yang ditangani di variabel terakhir
            if (s.length() > 2) {
                cout << "> Jumlah input lebih dari 4" << endl;
                valid4 = false;
            } else {
                if (checkNumber(s)) {
                    if (inputNumberValid(s)) {
                        d = std::stoi(s);
                        valid4 = true;
                    } else {
                        cout << "> Masukan angka keempat tidak valid" << endl;
                        valid4 = false;
                    }
                } else {
                    if (inputCharValid(s)){
                        d = chartoInt(s);
                        valid4 = true;
                    } else {
                        cout << "> Masukan karakter keempat tidak valid" << endl;
                        valid4 = false;
                    }
                }
            }
            validful = valid1 && valid2 && valid3 && valid4;
            if (!validful) {
                cout << "Masukan salah, ulangi!" << endl;
                cout << "-------------------------------------------------" << endl;
            }
        }
        cout << "Cek hasil input :" << endl;
        cout << a << " " << b << " " << c << " " << d << endl;
    } else {
        cout << " " << endl;
        cout << "===========  PEMBANGKITAN KARTU ACAK  ===========" << endl;
        cout << "Kartu hasil generate" << endl << ">> ";
        srand(time(0));
        generate4(&a,&b,&c,&d);
        // Pengisian karakter untuk masing-masing kartu
        inttoChar (a, &p);
        inttoChar (b, &q);
        inttoChar (c, &r);
        inttoChar (d, &s);
        cout << p << " " << q << " " << r << " " << s << endl;  
    }
}

void output ()
// Menangani proses output - kembalian ke pengguna
// Pengguna dapat memilih untuk hanya menampilkan di terminak atau menyimpan ke file
{
    // KAMUS LOKAL
    string com, path, output;
    int pil;
    bool valid = false;

    // ALGORITMA
    cout << " " << endl;
    cout << "====================  OUTPUT  ===================" << endl;
    while (!valid) {
        cout << "Tentukan cara menerima hasil" << endl;
        cout << " 1. Keluarkan hasil pada terminal" << endl;
        cout << " 2. Simpan hasil ke dalam file" << endl;
        cout << "" << endl;
        cout << "Pilih mode" << endl << ">> ";
        cin >> com;
        if (checkNumber(com)) {
            pil = std::stoi(com);
            if (pil != 1 && pil != 2) {
                cout << "Masukan salah, ulangi!" << endl;
                cout << "-------------------------------------------------" << endl;
                valid = false;
            } else {
                valid = true;
            }
        } else {
            cout << "Masukan salah, ulangi!" << endl;
            cout << "-------------------------------------------------" << endl;
            valid = false;
        }
    }
    
    // Keluar dari kalang, artinya input 1 atau 2
    // Pemrosesan berdasarkan kondisi
    if (pil == 1) {
        cout << " " << endl;
        cout << "==============  HASIL DI TERMINAL  ==============" << endl;
        cout << "Pasangan Kartu : " << p << " " << q << " " << r << " " << s << endl;
        // Handling tidak ada solusi
        if (NEffSolUni == 0) {
            cout << "Tidak terdapat solusi." << endl;
        } else {
            cout << "Terdapat " << NEffSolUni << " buah solusi" << endl;
            for (int i = 0; i <= NEffSolUni; i++) {
                cout << solutionunique[i] << endl;
            }
        }
        cout << endl;
    } else {
        cout << " " << endl;
        cout << "================  HASIL DI FILE  ================" << endl;
        cout << "Masukkan path letak file txt akan disimpan" << endl << ">> test/";
        cin >> path;
        output = "test/" + path;
        ofstream MyFile(output);
        MyFile << "Pasangan Kartu : " << p << " " << q << " " << r << " " << s << endl;
        // Handling tidak ada solusi
        if (NEffSolUni == 0) {
            MyFile << "Tidak terdapat solusi.";
        } else {
            MyFile << "Terdapat " << NEffSolUni << " buah solusi" << endl;
            for (int i = 0; i < NEffSolUni; i++) {
                MyFile << solutionunique[i] << endl;
            }
            MyFile << solutionunique[NEffSolUni];
        }
        cout << "Hasil telah tersimpan dalam path yang telah diberikan" << endl;
        cout << endl;
    }
}


// Program Utama
int main() {
    system("CLS"); // clear screen
    cout << endl << "Tugas Kecil 1 - IF2211 Strategi Algoritma" << endl;
    cout << "Michael Leon Putra W / 13521108 / K-02" << endl;
    cout << "24 Card Game Solver" << endl;
    cout << " " << endl;

    // Pemanggilan prosedur input
    input();

    // Memasukkan semua kemungkinan pasangan bilangan untuk dicari menggunakan brute force
    // Melakukan pemanggilan prosedur check combination, adapun terdapat 24 kemungkinan
    checkCombination(a, b, c, d);
    checkCombination(a, b, d, c);
    checkCombination(a, c, b, d);
    checkCombination(a, c, d, b);
    checkCombination(a, d, b, c);
    checkCombination(a, d, c, b);
    checkCombination(b, a, c, d);
    checkCombination(b, a, d, c);
    checkCombination(b, c, a, d);
    checkCombination(b, c, d, a);
    checkCombination(b, d, a, c);
    checkCombination(b, d, c, a);
    checkCombination(c, a, b, d);
    checkCombination(c, a, d, b);
    checkCombination(c, b, a, d);
    checkCombination(c, b, d, a);
    checkCombination(c, d, a, b);
    checkCombination(c, d, b, a);
    checkCombination(d, a, b, c);
    checkCombination(d, a, c, b);
    checkCombination(d, b, a, c);
    checkCombination(d, b, c, a);
    checkCombination(d, c, a, b);
    checkCombination(d, c, b, a);

    // Semua elemen yang dimasukkan ke dalam senarai diproses dengan berbagai operasi hingga
    // ditemukan pasangan yang memenuhi
    cout << " " << endl;
    cout << "Mencari penyelesaian..." << endl;
    cout << " " << endl;
    // Proses pencarian solusi dimulai
    cout << "===============  HASIL EKSEKUSI  ================" << endl;
    auto start = high_resolution_clock::now();   // Menggunakan atribut start pada jam
    for (int i = 1; i <= NEffElem; i++) {
        bruteForce(elem1[i], elem2[i], elem3[i], elem4[i]);
    }
    // Proses pencarian solusi selesai
    auto finish = high_resolution_clock::now();   // Menggunakan atribut finish pada jam

    // Unifikasi jawaban
    for (int i = 0; i <= NEffSol; i++) {
        for (int j = 0; j <= i; j++) {
            if (solution[i] == solution[j] && i != j) {
                break;
            } if (i == j && i != 0) {
                NEffSolUni++;
                solutionunique[NEffSolUni] = solution[i];
            }
        }
    }
    cout << "Pemrosesan selesai dilaksanakan" << endl;
    cout << "> Terdapat " << NEffSolUni << " buah solusi" << endl;

    // Pencetakan waktu eksekusi
    std::chrono::duration<double> diff = finish - start;
    cout << "> Waktu eksekusi: " << diff.count() << " sekon" << endl;

    // Outputting
    output();

    return 0;
}