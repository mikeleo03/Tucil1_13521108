#include <iostream>
#include "solver.hpp"
#include <cstdlib>
#include <time.h>
using namespace std;

// Inisialisasi Variabel Global
float a, b, c, d;               // Bilangan yang menjadi masukan dari pengguna
int count = 0;                  // Banyaknya pasangan jawaban yang mungkin
// Inisialisasi senarai dengan 25 elemen yang mencakup semua kombinasi, 4! = 24 dengan 1 elemen block
int elem1[25], elem2[25], elem3[25], elem4[25];
int NEff = 0;                   // Nilai efektif dari senarai


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

    while (i < NEff && not found) {
        if (a == elem1[i] && b == elem2[i] && c == elem3[i] && d == elem4[i]) {
            // Jika masing-masing elemen yang bersesuaian sama, sudah ada dalam senarai
            found = true;
        } else {
            // Jika tidak maka akan dilakukan increment hingga ditemukan
            i++;
        }
    }
    // Berhasil keluar dari kalang, kondisi yang mungkin adalah i = NEff atau not found
    // Jika not found, maka akan nilai tersebut akan dimasukkan ke dalam senarai
    if (not found) {
        NEff++;
        elem1[NEff] = a; elem2[NEff] = b; elem3[NEff] = c; elem4[NEff] = d;
    }
}

void processRes (int p, int q, int r, int w, int x, int y, int z)
// Melakukan hasil kalkulasi dengan bilangan masukan w, x, y, z dan operator p, q, r
// Operator p, q, r dihasilkan melalui skema brute force operator yang mungkin untuk mencapai nilai 24
{
    // KAMUS LOKAL
    // ALGORITMA
    // Penanganan terhadap kasus penyusunan dan kombinasi operator yang mungkin
    // ((w ops x) ops y) ops z
    float res = calculate(calculate(calculate((float)w, (float)x, p), (float) y, q), (float)z, r);
    if (a > 23.99999 && a < 24.00001) { // menghandle floating point akibat real division
        count++; // increment jumlah operasi yang ada
        // melakukan outputing hasil sesuai dengan operator terkait
        cout << "((" << w << " " << operations(p) << " " << x << ") " <<
        operations(q) << " " << y << ") " << operations(r) << " " << z << endl;
    }

    // (w ops (x ops y)) ops z
    float res = calculate(calculate((float)w, calculate((float)x, (float)y, q), p), (float) z, r);
    if (a > 23.99999 && a < 24.00001) {
        count++;
        cout << "(" << w << " " << operations(p) << " (" << x << " " << operations(q) <<
        " " << y << ")) " << operations(r) << " " << z << endl;
    }

    // w ops ((x ops y) ops z)
    float res = calculate((float)w, calculate(calculate((float)x, (float)y, q), (float)z, r), p);
    if (a > 23.99999 && a < 24.00001) {
        count++;
        cout << w << " " << operations(p) << " ((" << x << " " << operations(q) << " " <<
        y << ") " << operations(r) << " " << z << ")" << endl;
    }

    // w ops (x ops (y ops z))
    float res = calculate((float)w, calculate((float)x, calculate((float)y, (float)z, r), q), p);
    if (a > 23.99999 && a < 24.00001) {
        count++;
        cout << w << " " << operations(p) << " (" << x << " " << operations(q) << " (" <<
        y << " " << operations(r) << " " << z << "))" << endl;
    }

    // (w ops x) ops (y ops z)
    float res = calculate(calculate((float)w, (float)x, p), calculate((float) y, (float) z, r), q);
    if (a > 23.99999 && a < 24.00001) {
        count++;
        cout << "(" << w << " " << operations(p) << " " << x << ") " <<
        operations(q) << " (" << y << " " << operations(r) << " " << z << ")" << endl;
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

}

void output ()
// Menangani proses output - kembalian ke pengguna
// Pengguna dapat memilih untuk hanya menampilkan di terminak atau menyimpan ke file
{

}

int main() {
    int angka1, angka2, angka3, angka4;
    srand(time(0));
    generate4(&angka1,&angka2,&angka3,&angka4);
    
    return 0;
}