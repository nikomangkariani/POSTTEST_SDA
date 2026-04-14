#include <iostream>
using namespace std;

// Fungsi untuk menukar nilai dengan menggunakan pointer 
// Parameter dengan dua pointer ke integer
void tukarNilai(int* a, int* b) {
    int temp = *a;  // untuk menyimpan nilai yang ditunjuk pointer a
    *a = *b;        // nilai di alamat a diganti dengan nilai di alamat b
    *b = temp;      // nilai di alamat b diganti dengan nilai sementara
}

int main() {
    int x, y;

    cout << "=== Program Menukar Nilai dengan Pointer ===" << endl;
    cout << "Masukkan nilai yang pertama  : ";
    cin >> x;
    cout << "Masukkan nilai yang kedua    : ";
    cin >> y;

    cout << "\nSebelum ditukar:" << endl;
    cout << "  x = " << x << ", y = " << y << endl;

    // Panggil fungsi dengan mengoper alamat variabel (&x dan &y)
    tukarNilai(&x, &y);

    cout << "\nSesudah ditukar:" << endl;
    cout << "  x = " << x << ", y = " << y << endl;

    return 0;
}
