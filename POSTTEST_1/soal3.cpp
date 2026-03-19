#include <iostream>
using namespace std;

// Fungsinya untuk menampilkan array beserta alamat memorinya
void tampilkanArray(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << "  Elemen[" << i << "] = " << *(arr + i)
             << "  Alamat: " << (arr + i) << endl;
    }
}

void reverseArray(int* arr, int n) {
    int* kiri  = arr;           // untuk pointer ke elemen pertama
    int* kanan = arr + (n - 1); // untuk pointer ke elemen terakhir

    while (kiri < kanan) {
        // Tukar nilai menggunakan pointer (tanpa indeks)
        int temp = *kiri;
        *kiri  = *kanan;
        *kanan = temp;

        kiri++;   // untuk geser maju
        kanan--;  // untuk geser mundur
    }
}

int main() {
    // Array yang berisi 7 bilangan prima
    int prima[7] = {2, 3, 5, 7, 11, 13, 17};
    int n = 7;

    cout << "=== Program reverseArray - Bilangan Prima ===" << endl;

    cout << "\nArray sebelum dibalik:" << endl;
    tampilkanArray(prima, n);

    reverseArray(prima, n);

    cout << "\nArray sesudah dibalik:" << endl;
    tampilkanArray(prima, n);

    return 0;
}
