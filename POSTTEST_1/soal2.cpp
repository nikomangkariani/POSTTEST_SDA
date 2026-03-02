#include <iostream>
#include <string>
using namespace std;

// struct ini untuk menampung satu data mahasiswa
// isinya ada tiga bagian yaitu: nama, nim, dan ipk
struct Mahasiswa {
    string nama;
    string nim;
    float ipk;
};

int main() {
    const int JUMLAH = 5;
    Mahasiswa mhs[JUMLAH];

    // Kita isi datanya satu persatu sesuai dengan data yang ada
    mhs[0] = {"hizkia",   "030", 3.8};
    mhs[1] = {"komang",   "003", 3.9};
    mhs[2] = {"husanata", "006", 3.7};
    mhs[3] = {"kariani",  "021", 3.6};
    mhs[4] = {"husai",    "001", 3.5};

    // tampilikan semua data mahasiswa dalam bentuk tabel
    cout << "=== Data Seluruh Mahasiswa ===" << endl;
    cout << "No | Nama       | NIM   | IPK " << endl;
    cout << "-- |------------|-------|-----" << endl;
    for (int i = 0; i < JUMLAH; i++) {
        cout << (i + 1) << "  | " << mhs[i].nama << "\t| "
             << mhs[i].nim << "   | " << mhs[i].ipk << endl;
    }

    // Kemudian cari siapa yang IPK nya paling tinggi
    int idxTertinggi = 0;
    for (int i = 1; i < JUMLAH; i++) {
        if (mhs[i].ipk > mhs[idxTertinggi].ipk) {
            idxTertinggi = i; // update jika ketemu yang lebih tinggi
        }
    }

    // tampilkan hasil akhirnya
    cout << "\n=== Mahasiswa dengan IPK Tertinggi ===" << endl;
    cout << "Nama : " << mhs[idxTertinggi].nama << endl;
    cout << "NIM  : " << mhs[idxTertinggi].nim << endl;
    cout << "IPK  : " << mhs[idxTertinggi].ipk << endl;

    return 0;
}
