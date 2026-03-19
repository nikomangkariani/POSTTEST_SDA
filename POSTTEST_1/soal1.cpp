#include <iostream>
using namespace std;

// fungsi ini tugasnya untuk mencari nilai terkecil dari array
// sekaligus untuk memantau indeksnya lewat parameter referensi
int findMin(int arr[], int n, int &idxMin) {
    int min = arr[0];
    idxMin = 0;

    // mulai dari indeks 1, membandingkan satu-satu sama dengan nilai min saat ini
    for (int i = 1; i <= n - 1; i++) {
        if (arr[i] < min) {
            min = arr[i];
            idxMin = i; // update indeks jika dapat yang lebih kecil
        }
    }

    return min;
}

int main() {
    // isi array menggunakan bilangan Fibonacci yaitu: 1 1 2 3 5 8 13 21
    int fibonacci[8] = {1, 1, 2, 3, 5, 8, 13, 21};
    int n = 8;

    cout << "== Program Mencari Nilai Minimum ==" << endl;

    cout << "Isi array fibonacci: ";
    for (int i = 0; i < n; i++) {
        cout << fibonacci[i];
        if (i < n - 1) cout << ", ";
    }
    cout << endl;

    int idxMin;
    int hasilMin = findMin(fibonacci, n, idxMin);

    cout << "Nilai minimum terdapat di: " << hasilMin << endl;
    cout << "Indeksnya ada di posisi: " << idxMin << endl;

    return 0;
}
