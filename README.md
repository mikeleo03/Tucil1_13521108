# 24 Card Game Solver
> *Source Code* ini dibuat untuk memenuhi Tugas Kecil 1 - Strategi Algoritma IF2211 yaitu mengimplementasikan 
> "Penyelesaian Permainan Kartu 24 dengan Algoritma *Brute Force*".

## Daftar Isi
* [Deskripsi Singkat Program](#deskripsi-singkat-program)
* [Sistematika File](#sistematika-file)
* [Requirements](#requirements)
* [Cara Menjalankan Program](#cara-menjalankan-program)
* [Project Status](#project-status)
* [Author](#author)

## Deskripsi Singkat Program
Program untuk mencari semua solusi operasi dari *24 Card Game* dengan menggunakan algoritma *brute force*. Program menerima dua skema masukan, yaitu masukan secara langsung atau pembangkitan 4 buah kartu secara acak. Kemudian program akan mengeluarkan hasil eksekusi berisi jumlah solusi, waktu eksekusi, dan semua solusi yang mungkin untuk mengoperasikan keempat bilangan tersebut menjadi bilangan 24. Adapaun luaran dapat diberikan melalui terminal maupun disimpan dalam sebuah *file*. Program dibangun dengan menggunakan bahasa C++.

## Sistematika File
```bash
.
├─── bin
|   └─── main.exe
├─── doc
├─── src
|   ├─── solver.cpp
|   └─── solver.hpp
├─── test
|   ├─── test1.txt
|   ├─── test2.txt
|   ├─── test3.txt
|   ├─── test4.txt
|   ├─── test5.txt
|   ├─── test6.txt
|   ├─── test7.txt
|   └─── test8.txt
├─── run.bat
└─── README.md
```

## Requirements
* GCC compiler (versi 11.2.0 atau yang lebih baru)

## Cara Menjalankan Program
1. Pastikan GCC versi terbaru sudah terpasang pada mesin eksekusi (Anda dapat mengecek versi GCC dengan menjalankan *command* `gcc --version` pada *command prompt*).
2. Masuk ke dalam folder program dan eksekusi (*run*) `run.bat` untuk menghasilkan *executable file*. Tunggu beberapa saat, maka akan muncul sebuah file bernama `solver.exe` pada folder `bin`.
3. Masukkan perintah `bin/solver` ke dalam terminal untuk menjalankan program.
4. Anda diminta untuk memilih skema masukan, masukan secara langsung atau pembangkitan 4 buah kartu secara acak.
5. Jika Anda memilih masukan secara langsung, maka masukkan 4 buah bilangan ke dalam terminal. Masukan Anda juga akan divalidasi dan Anda akan diminta untuk memberikan masukan ulang jika masukan Anda salah. Jika Anda memilih pembangkitan kartu secara acak, maka Anda hanya perlu menunggu untuk menunggu proses pembangkitan kartu.
6. Selanjutnya program akan secara otomatis melakukan pencarian operator yang memenuhi kondisi permainan kartu 24.
7. Setelah proses eksekusi selesai, Anda akan memperoleh statistik eksekusi berupa waktu eksekusi dan jumlah solusi. Anda juga akan diminta untuk memilih cara memberikan luaran, melalui terminal atau disimpan dalam sebuah file.

## Project Status
Status : *Completed*
| Poin  | Ya | Tidak |
|---|---|---|
| Program berhasil dikompilasi tanpa kesalahan | ✓ |   |
| Program berhasil *running* | ✓ |   |
| Program dapat membaca input / *generate* sendiri dan memberikan luaran | ✓ |   |
| Solusi yang diberikan program memenuhi (berhasil mencapai 24) | ✓ |  |
| Program dapat menyimpan solusi dalam file teks | ✓ |  |

## Author
Nama : Michael Leon Putra Widhi </br>
NIM : 13521108 </br>
Program Studi : Teknik Informatika </br>
Profile Github : [mikeleo03](https://github.com/mikeleo03)