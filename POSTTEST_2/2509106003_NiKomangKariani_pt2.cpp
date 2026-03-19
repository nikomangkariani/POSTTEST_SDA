#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

// 1. Ini Untuk Struct Data Hewan Pawcare Petshop
struct Hewan {
    int id;
    string nama;
    string jenis;
    string layanan;
    int harga;
};

// Fungsi Swap untuk menukar data menggunakan pointer
void swapData(Hewan *a, Hewan *b) {
    Hewan temp = *a;
    *a = *b;
    *b = temp;
}

// Ini Fungsi Header Tabel agar tampilan nya rapi
void tampilkanHeader() {
    cout << "\n==============================================================================" << endl;
    cout << "| " << left << setw(5) << "ID" 
         << "| " << setw(15) << "Nama Hewan" 
         << "| " << setw(15) << "Jenis Hewan" 
         << "| " << setw(20) << "Layanan" 
         << "| " << setw(12) << "Harga (Rp)" << " |" << endl;
    cout << "==============================================================================" << endl;
}

// Ini Fungsi Baris Data menggunakan Pointer Aritmatika
void tampilkanBaris(Hewan* h) {
    cout << "| " << left << setw(5) << h->id 
         << "| " << setw(15) << h->nama 
         << "| " << setw(15) << h->jenis 
         << "| " << setw(20) << h->layanan 
         << "| " << setw(12) << h->harga << " |" << endl;
}

// Menu 1 untuk menampilkan semua data
void tampilkanSemua(Hewan* arr, int n) {
    if (n == 0) {
        cout << "\nData masih kosong." << endl;
        return;
    }
    tampilkanHeader();
    for (int i = 0; i < n; i++) {
        tampilkanBaris(arr + i); 
    }
    cout << "==============================================================================" << endl;
}

// Menu 2 untuk Tambah Data Baru dengan Validasi ID yang unik
void tambahData(Hewan* arr, int &n) {
    int idBaru;
    bool idSudahAda;

    do {
        idSudahAda = false;
        cout << "ID Hewan      : "; cin >> idBaru;

        // Ini untuk mengecek apakah ID sudah digunakan di dalam tabel
        for (int i = 0; i < n; i++) {
            if (arr[i].id == idBaru) {
                idSudahAda = true;
                break;
            }
        }

        if (idSudahAda) {
            cout << "Waduh, ID " << idBaru << " sudah ada di tabel! Coba gunakan ID lain ya." << endl;
        }
    } while (idSudahAda);

    // Lanjut input jika ID unik
    arr[n].id = idBaru;
    cout << "Nama Hewan    : "; cin.ignore(); getline(cin, arr[n].nama);
    cout << "Jenis Hewan   : "; getline(cin, arr[n].jenis);
    cout << "Jenis Layanan : "; getline(cin, arr[n].layanan);
    cout << "Harga (Rp)    : "; cin >> arr[n].harga;
    n++;
    cout << "\nHoree!! Data berhasil ditambahkan." << endl;
}

// Menu 3 untuk Linear Search nama hewan
void linearSearchNama(Hewan* arr, int n, string cari) {
    bool ketemu = false;
    for (int i = 0; i < n; i++) {
        if ((arr + i)->nama == cari) {
            cout << "\nHOREE! DATA DITEMUKAN!" << endl;
            tampilkanHeader(); tampilkanBaris(arr + i);
            cout << "==============================================================================" << endl;
            ketemu = true; break;
        }
    }
    if (!ketemu) cout << "\nWaduh, Nama '" << cari << "' tidak ditemukan." << endl;
}

// Menu 4 untuk Fibonacci Search ID
int fibonacciSearchID(Hewan* arr, int n, int x) {
    int f2 = 0, f1 = 1, fM = f2 + f1; 
    while (fM < n) { f2 = f1; f1 = fM; fM = f2 + f1; }
    int offset = -1;
    while (fM > 1) {
        int i = min(offset + f2, n - 1);
        if ((arr + i)->id < x) { fM = f1; f1 = f2; f2 = fM - f1; offset = i; }
        else if ((arr + i)->id > x) { fM = f2; f1 = f1 - f2; f2 = fM - f1; }
        else return i;
    }
    if (f1 && (arr + offset + 1)->id == x) return offset + 1;
    return -1;
}

// Menu 5 untuk Bubble Sort Nama (A-Z)
void bubbleSortNama(Hewan* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].nama > arr[j + 1].nama) swapData(&arr[j], &arr[j + 1]);
        }
    }
    cout << "\nData diurutkan berdasarkan Nama (A-Z)." << endl;
    tampilkanSemua(arr, n);
}

// Menu 6 untuk Selection Sort Harga (Termurah ke Termahal)
void selectionSortHarga(Hewan* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int m = i;
        for (int j = i + 1; j < n; j++) if (arr[j].harga < arr[m].harga) m = j;
        swapData(&arr[m], &arr[i]);
    }
    cout << "\nData diurutkan berdasarkan Harga Termurah ke Termahal." << endl;
    tampilkanSemua(arr, n);
}

int main() {
    Hewan dataHewan[100];
    int jumlahData = 5;
    int pilihan;

    // Ini untuk data awal Pawcare Petshop
    dataHewan[0] = {21, "Pusi", "Kucing", "Grooming", 150000};
    dataHewan[1] = {22, "Boby", "Anjing", "Vaksin Rabies", 250000};
    dataHewan[2] = {23, "Tralili", "Kelinci", "Check-up Gigi", 75000};
    dataHewan[3] = {24, "Micky", "Kucing", "Mandi Jamur", 120000};
    dataHewan[4] = {25, "Jecky", "Anjing", "Titip Sehari", 100000};

    do {
        cout << "\n==========================================" << endl;
        cout << "||      MANAGEMENT PAWCARE PETSHOP      ||" << endl;
        cout << "==========================================" << endl;
        cout << "|| 1. Tampil Semua Data Hewan           ||" << endl;
        cout << "|| 2. Tambah Data Hewan Baru            ||" << endl;
        cout << "|| 3. Cari Berdasarkan Nama Hewan       ||" << endl;
        cout << "|| 4. Cari Berdasarkan ID Hewan         ||" << endl;
        cout << "|| 5. Urutkan Berdasarkan Nama (A-Z)    ||" << endl;
        cout << "|| 6. Urutkan Berdasarkan Harga         ||" << endl;
        cout << "|| 7. Keluar                            ||" << endl;
        cout << "==========================================" << endl;
        cout << "Pilihan: "; cin >> pilihan;

        // Logika menggunakan IF-ELSE-IF selang-seling
        if (pilihan == 1) {
            tampilkanSemua(dataHewan, jumlahData);
        } 
        else if (pilihan == 2) {
            tambahData(dataHewan, jumlahData);
        } 
        else if (pilihan == 3) {
            string cari; cout << "Ketik Nama: "; cin.ignore(); getline(cin, cari);
            linearSearchNama(dataHewan, jumlahData, cari);
        } 
        else if (pilihan == 4) {
            // Ini untuk urutan ID wajib untuk Fibonacci Search
            for(int i=0; i<jumlahData-1; i++) {
                for(int j=0; j<jumlahData-i-1; j++) {
                    if(dataHewan[j].id > dataHewan[j+1].id) swapData(&dataHewan[j], &dataHewan[j+1]);
                }
            }
            int idC; cout << "Ketik ID: "; cin >> idC;
            int h = fibonacciSearchID(dataHewan, jumlahData, idC);
            if (h != -1) {
                cout << "\nHOREE! DATA DITEMUKAN!" << endl;
                tampilkanHeader(); tampilkanBaris(&dataHewan[h]);
                cout << "==============================================================================" << endl;
            } else cout << "\nWaduh, ID tersebut tidak ditemukan." << endl;
        } 
        else if (pilihan == 5) {
            bubbleSortNama(dataHewan, jumlahData);
        } 
        else if (pilihan == 6) {
            selectionSortHarga(dataHewan, jumlahData);
        } 
        else if (pilihan == 7) {
            cout << "\n================================================" << endl;
            cout << "||   Terima kasih telah menggunakan layanan   ||" << endl;
            cout << "||            PAWCARE PETSHOP!                ||" << endl;
            cout << "================================================" << endl;
        } 
        // Pesan error jika input di luar angka 1-7
        else {
            cout << "\nWaduh, menu " << pilihan << " tidak ditemukan! Pilih menu 1-7 ya." << endl;
        }

    } while (pilihan != 7);

    return 0;
}