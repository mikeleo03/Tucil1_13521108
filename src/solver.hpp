/* Header File solver.hpp */
#include <iostream>
using namespace std;

void randomNumber(int* nums);
// Menciptakan angka secara anak (random number generator)
// Seeds yang digunakan adalah waktu saat ini, sehingga relatif sulit terulang kembali

void generate4(int* card1, int* card2, int* card3, int* card4);
// Mengenerate 4 angka random
// Menggunakan prosedur randomNumber yang telah diinisiasi sebelumnnya
// Juga melakukan pencetakan angka hasil pembangkitan angka

char operations(int ops); 
// Sebelumnya membuat representasi dari operasi dalam bentuk angka
// Fungsi ini mengembalikan bentuk angka dalam operasi menjadi operasi + - * /

float calculate (int ops, float x, float y);
// Melakukan operasi bilangan real antara dua bilangan yang representasi nya diubah
// menjadi bilangan real (untuk memudahkan real division) dan operator dalam angka

void checkCombination (int a, int b, int c, int d);
// Melakukan pengecekan terhadap semua kombinasi yang mungkin dari masukan a, b, c, d
// Kombinasi yang sudah ada tidak dimasukkan ke dalam senarai
// Adapun kombinasi yang belum ada akan dimasukkan ke dalam senarai analisis

void processRes (int p, int q, int r, int w, int x, int y, int z);
// Melakukan hasil kalkulasi dengan bilangan masukan w, x, y, z dan operator p, q, r
// Operator p, q, r dihasilkan melalui skema brute force operator yang mungkin untuk mencapai nilai 24

void bruteForce (int w, int x, int y, int z);
// Melakukan brute-force untuk menemukan pasangan solusi operator yang mungkin bagi bilangan 
// w, x, y, dan z untuk mendapatkan nilai 24.
// Digunakan operator p, q, dan r dengan 3 kalang bersarang

void input ();
// Menangani proses input - masukan dari pengguna
// Pengguna dapat memilih untuk memasukkan input atau membangkitkan bilangan secara acak

void output ();
// Menangani proses output - kembalian ke pengguna
// Pengguna dapat memilih untuk hanya menampilkan di terminak atau menyimpan ke file