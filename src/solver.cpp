#include <iostream>
#include "solver.hpp"
#include <cstdlib>
#include <time.h>
#include <string>
#include <fstream>
using namespace std;

// Inisialisasi Variabel Global
// Bilangan yang menjadi masukan, inisialisasi dengan char untuk mempermudah konversi dengan ASCII
int a, b, c, d;
int count = 0;         // Banyaknya pasangan jawaban yang mungkin
// Inisialisasi senarai dengan 25 elemen yang mencakup semua kombinasi, 4! = 24 dengan 1 elemen block
int elem1[25], elem2[25], elem3[25], elem4[25];
string solution[300];
int NEffElem = 0;          // Nilai efektif dari senarai kombinasi
int NEffSol = 0;           // Nilai efektif dari senarai solusi


// Deklarasi dan Realisasi Fungsi dan Prosedur dari Header
void randomNumber (int* nums) 
// Menciptakan angka secara anak (random number generator)
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
// Menggunakan prosedur randomNumber yang telah diinisiasi sebelumnnya
// Juga melakukan pencetakan angka hasil pembangkitan angka
{
    // KAMUS LOKAL
    // ALGORITMA
    randomNumber(card1);
    randomNumber(card2);
    randomNumber(card3);
    randomNumber(card4);

    cout << *card1 << " " << *card2 << " " << *card3 << " " << *card4 << endl;   
}

char operations (int ops) 
// Sebelumnya membuat operationsasi dari operasi dalam bentuk angka
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
// Melakukan operasi bilangan real antara dua bilangan yang operationsasi nya diubah
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

    while (i < NEffElem && not found) {
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
    if (not found) {
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
    string sol;
    // Konversi bilangan ke string
    string bil1 = to_string(w);
    string bil2 = to_string(x);
    string bil3 = to_string(y);
    string bil4 = to_string(z);

    // ALGORITMA
    // Penanganan terhadap kasus penyusunan dan kombinasi operator yang mungkin
    // ((w ops x) ops y) ops z
    res = calculate(r, calculate(q, calculate(p, (float) w, (float) x), (float) y),(float) z);
    if (res > 23.99999 && res < 24.00001) { // menghandle floating point akibat real division
        count++; // increment jumlah operasi yang ada
        // melakukan outputing hasil sesuai dengan operator terkait
        // cout << "((" << w << " " << operations(p) << " " << x << ") " <<
        // operations(q) << " " << y << ") " << operations(r) << " " << z << endl;
        // Membuat solusi dalam bentuk string dan memasukkannya ke dalam senarai solusi
        sol = "((" + bil1 + " " + operations(p) + " " + bil2 + ") " +
        operations(q) + " " + bil3 + ") " + operations(r) + " " + bil4;
        NEffSol++;
        solution[NEffSol] = sol;
    }

    // (w ops (x ops y)) ops z
    res = calculate(r, calculate(p, (float) w, calculate(q, (float (x)), (float) y)), (float) z);
    if (res > 23.99999 && res < 24.00001) {
        count++;
        // cout << "(" << w << " " << operations(p) << " (" << x << " " << operations(q) <<
        // " " << y << ")) " << operations(r) << " " << z << endl;
        sol = "(" + bil1 + " " + operations(p) + " (" + bil2 + " " + operations(q) +
        " " + bil3 + ")) " + operations(r) + " " + bil4;
        NEffSol++;
        solution[NEffSol] = sol;
    }

    // w ops ((x ops y) ops z)
    res = calculate(p, (float) w, calculate(r, calculate(q, (float) x, (float) y), float (z)));
    if (res > 23.99999 && res < 24.00001) {
        count++;
        // cout << w << " " << operations(p) << " ((" << x << " " << operations(q) << " " <<
        // y << ") " << operations(r) << " " << z << ")" << endl;
        sol = bil1 + " " + operations(p) + " ((" + bil2 + " " + operations(q) + " " +
        bil3 + ") " + operations(r) + " " + bil4 + ")";
        NEffSol++;
        solution[NEffSol] = sol;
    }

    // w ops (x ops (y ops z))
    res = calculate(p, (float) w, calculate(q, (float) x, calculate(r, (float) y, (float) z)));
    if (res > 23.99999 && res < 24.00001) {
        count++;
        // cout << w << " " << operations(p) << " (" << x << " " << operations(q) << " (" <<
        // y << " " << operations(r) << " " << z << "))" << endl;
        sol = bil1 + " " + operations(p) + " (" + bil2 + " " + operations(q) + " (" +
        bil3 + " " + operations(r) + " " + bil4 + "))";
        NEffSol++;
        solution[NEffSol] = sol;
    }

    // (w ops x) ops (y ops z)
    res = calculate(q, calculate(p, (float) w, (float) x), calculate(r, (float) y, (float) z)); 
    if (res > 23.99999 && res < 24.00001) {
        count++;
        // cout << "(" << w << " " << operations(p) << " " << x << ") " <<
        // operations(q) << " (" << y << " " << operations(r) << " " << z << ")" << endl;
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
    int com;

    // ALGORITMA
    do {
        cout << "Tentukan cara membuat masukan" << endl;
        cout << " 1. Berdasarkan input" << endl;
        cout << " 2. Lakukan generate random" << endl;
        cout << "" << endl;
        cout << "Pilih mode: ";
        cin >> com;
    } while (com != 1 && com != 2);
    // Keluar dari kalang, artinya input 1 atau 2
    // Pemrosesan berdasarkan kondisi
    if (com == 1) {
        cout << "Masukkan 4 buah kartu" << endl;
        cin >> a >> b >> c >> d;
        cout << "Cek hasil input :" << endl;
        cout << a << " " << b << " " << c << " " << d << endl;
    } else {
        cout << "Kartu hasil generate :" << endl;
        srand(time(0));
        generate4(&a,&b,&c,&d);
    }
}

void output ()
// Menangani proses output - kembalian ke pengguna
// Pengguna dapat memilih untuk hanya menampilkan di terminak atau menyimpan ke file
{
    // KAMUS LOKAL
    int com;

    // ALGORITMA
    cout << "Pemrosesan selesai dilaksanakan" << endl;
    cout << " " << endl;
    do {
        cout << "Tentukan cara menerima hasil" << endl;
        cout << " 1. Keluarkan di terminal" << endl;
        cout << " 2. Simpan ke dalam file" << endl;
        cout << "" << endl;
        cout << "Pilih mode: ";
        cin >> com;
    } while (com != 1 && com != 2);
    // Keluar dari kalang, artinya input 1 atau 2
    // Pemrosesan berdasarkan kondisi
    if (com == 1) {
        cout << "Terdapat " << NEffSol << " buah solusi" << endl;
        for (int i = 0; i <= NEffSol; i++) {
            cout << solution[i] << endl;
        }
    } else {
        ofstream MyFile("doc/result.txt");
        MyFile << "Pasangan Kartu : " << a << " " << b << " " << c << " " << d << endl;
        MyFile << "Terdapat " << NEffSol << " buah solusi" << endl;
        for (int i = 0; i <= NEffSol; i++) {
            MyFile << solution[i] << endl;
        }
        cout << "Hasil telah tersimpan dalam file doc/result.txt" << endl;
    }
}


// Program Utama
int main() {
    cout << "Tugas Kecil 1 - IF2211 Strategi Algoritma" << endl;
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

    // Proses pencarian solusi dimulai
    cout << " " << endl;
    cout << "Mencari penyelesaian..." << endl;
    clock_t start = clock();   // Menggunakan atribut start pada jam

    // Semua elemen yang dimasukkan ke dalam senarai diproses dengan berbagai operasi hingga
    // ditemukan pasangan yang memenuhi
    for (int i = 1; i <= NEffElem; i++) {
        bruteForce(elem1[i], elem2[i], elem3[i], elem4[i]);
    }
    cout << endl << "Terdapat " << count << " buah solusi" << endl;

    // Proses pencarian solusi selesai
    clock_t finish = clock();   // Menggunakan atribut finish pada jam

    // Pencetakan waktu eksekusi
    printf("Waktu eksekusi: %.5f sekon\n", (float)(finish - start)/CLOCKS_PER_SEC);

    // Outputting
    output();

    return 0;
}