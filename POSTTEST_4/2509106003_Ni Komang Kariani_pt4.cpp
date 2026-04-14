#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX = 100;

// Untuk Struct Data Utama
struct Hewan {
    int    id;
    string nama;
    string jenis;
    string layanan;
    int    harga;
};

// Untuk struct node Queue dengan menggunakan (Single Linked List)
// Untuk menyimpan data pasien dan pointer ke node berikutnya 
struct NodeAntrian {
    int        idHewan;
    string     namaHewan;
    string     jenisHewan;
    string     pemilik;
    NodeAntrian* next;   // Ini untuk pointer ke node berikutnya
};

 // Ini untuk struct Queue berbasis SLL
 // front menunjuk ke kepala (dequeue dari sini)
 // rear milik si  ekor (enqueue ke sini)
 // size merujuk ke jumlah elemen
 
struct Queue {
    NodeAntrian* front;
    NodeAntrian* rear;
    int          size;
};

// Ini untuk struct node stack dengan (Single Linked List)
// Untuk menyimpan data tindakan dan pointer ke node berikutnya
struct NodeRiwayat {
    int          idHewan;
    string       namaHewan;
    string       keterangan;
    NodeRiwayat* next;   // untuk pointer ke node berikutnya
};

// STRUCT STACK berbasis SLL
// top merujuk ke puncak tumpukan
// size merujuk ke jumlah elemen
struct Stack {
    NodeRiwayat* top;
    int          size;
};

// Untuk inisialisasi dengan menerima parameter pointer ke struct
void initQueue(Queue* q) {
    q->front = nullptr;
    q->rear  = nullptr;
    q->size  = 0;
}

void initStack(Stack* s) {
    s->top  = nullptr;
    s->size = 0;
}

// Untuk swap data menggunakan dereferensi pointer
// Menukar nilai field, bukan menukar pointer node
void swapData(Hewan* a, Hewan* b) {
    Hewan temp = *a;   // dereferensi untuk ambil nilai dari pointer
    *a = *b;           // dereferensi untuk tulis nilai via pointer
    *b = temp;
}

// Fungsi input helper
string inputString(const string& prompt) {
    string hasil;
    cout << prompt;
    getline(cin, hasil);
    return hasil;
}

int inputInt(const string& prompt, int minVal = 0) {
    int nilai;
    while (true) {
        cout << prompt;
        if (cin >> nilai && nilai >= minVal) { cin.ignore(); return nilai; }
        cin.clear(); cin.ignore(10000, '\n');
        cout << "  Input tidak valid. Masukkan angka >= " << minVal << ".\n";
    }
}

// Fungsi tampil tabel hewan
void tampilkanHeader() {
    cout << "==============================================================================\n";
    cout << "| " << left << setw(5)  << "ID"
         << "| " << setw(15) << "Nama Hewan"
         << "| " << setw(15) << "Jenis Hewan"
         << "| " << setw(20) << "Layanan"
         << "| " << setw(12) << "Harga (Rp)" << " |\n";
    cout << "==============================================================================\n";
}

void tampilkanBaris(Hewan* h) {
    cout << "| " << left << setw(5)  << h->id
         << "| " << setw(15) << h->nama
         << "| " << setw(15) << h->jenis
         << "| " << setw(20) << h->layanan
         << "| " << setw(12) << h->harga << " |\n";
}

void tampilkanSemua(Hewan* arr, int n) {
    if (n == 0) { cout << "  Waduh, data masih kosong.\n"; return; }
    tampilkanHeader();
    for (int i = 0; i < n; i++) tampilkanBaris(arr + i);
    cout << "==============================================================================\n";
}

// Fungsi menu
void tampilMenu() {
    cout << "\n==============================================\n";
    cout << "||       MANAGEMENT PAWCARE PETSHOP        ||\n";
    cout << "==============================================\n";
    cout << "||  DATA HEWAN                             ||\n";
    cout << "||  1. Tampil Semua Data Hewan             ||\n";
    cout << "||  2. Tambah Data Hewan Baru              ||\n";
    cout << "||  3. Cari Berdasarkan Nama Hewan         ||\n";
    cout << "||  4. Cari Berdasarkan ID Hewan           ||\n";
    cout << "||  5. Urutkan Berdasarkan Nama (A-Z)      ||\n";
    cout << "||  6. Urutkan Berdasarkan Harga           ||\n";
    cout << "||  ANTRIAN & RIWAYAT (SLL)                ||\n";
    cout << "||  7. Daftarkan Hewan ke Antrian          ||\n";
    cout << "||  8. Panggil Pasien (Dequeue)            ||\n";
    cout << "||  9. Catat Tindakan Medis (Push)         ||\n";
    cout << "|| 10. Batalkan Tindakan Terakhir (Pop)    ||\n";
    cout << "|| 11. Peek (Antrian & Riwayat)            ||\n";
    cout << "|| 12. Tampilkan Semua Antrian             ||\n";
    cout << "|| 13. Tampilkan Semua Riwayat             ||\n";
    cout << "||  0. Keluar                              ||\n";
    cout << "==============================================\n";
    cout << "  Ketik 'm' untuk menampilkan menu awal.\n";
}

// Fungsi data hewan (tidak berubah dari sebelumnya)
void tambahData(Hewan* arr, int& n) {
    if (n >= MAX) { cout << "  Waduh, data penuh!\n"; return; }
    bool idSudahAda; int idBaru;
    do {
        idSudahAda = false;
        idBaru = inputInt("  ID Hewan      : ", 1);
        for (int i = 0; i < n; i++)
            if ((arr + i)->id == idBaru) { idSudahAda = true; break; }
        if (idSudahAda) cout << "  Waduh, ID " << idBaru << " sudah ada!\n";
    } while (idSudahAda);

    (arr + n)->id      = idBaru;
    (arr + n)->nama    = inputString("  Nama Hewan    : ");
    (arr + n)->jenis   = inputString("  Jenis Hewan   : ");
    (arr + n)->layanan = inputString("  Jenis Layanan : ");
    (arr + n)->harga   = inputInt("  Harga (Rp)    : ", 0);
    n++;
    cout << "  Oke, data berhasil ditambahkan!\n";
}

void linearSearchNama(Hewan* arr, int n, const string& cari) {
    int cocok[MAX], jumlahCocok = 0;
    for (int i = 0; i < n; i++)
        if ((arr + i)->nama == cari) cocok[jumlahCocok++] = i;

    if (jumlahCocok == 0) { cout << "  Waduh, nama '" << cari << "' tidak ditemukan.\n"; return; }

    cout << "  Oke, ditemukan " << jumlahCocok << " data:\n";
    tampilkanHeader();
    for (int k = 0; k < jumlahCocok; k++) tampilkanBaris(arr + cocok[k]);
    cout << "==============================================================================\n";

    if (cocok[0] != 0) swapData(arr + cocok[0], arr);
}

void fibonacciSearchID(Hewan* arr, int n, int x) {
    if (n == 0) { cout << "  Data kosong.\n"; return; }
    Hewan temp[MAX];
    for (int i = 0; i < n; i++) *(temp + i) = *(arr + i);

    for (int i = 0; i < n - 1; i++) {
        bool ada_swap = false;
        for (int j = 0; j < n - i - 1; j++)
            if ((temp + j)->id > (temp + j + 1)->id)
                { swapData(temp + j, temp + j + 1); ada_swap = true; }
        if (!ada_swap) break;
    }

    int f2 = 0, f1 = 1, fM = f2 + f1;
    while (fM < n) { f2 = f1; f1 = fM; fM = f2 + f1; }
    int offset = -1, hasil = -1;
    while (fM > 1) {
        int i = min(offset + f2, n - 1);
        if      ((temp + i)->id < x) { fM = f1; f1 = f2; f2 = fM - f1; offset = i; }
        else if ((temp + i)->id > x) { fM = f2; f1 = f1 - f2; f2 = fM - f1; }
        else                         { hasil = i; break; }
    }
    if (hasil == -1 && f1 && (temp + offset + 1)->id == x) hasil = offset + 1;

    if (hasil != -1) {
        cout << "  Oke, data ditemukan:\n";
        tampilkanHeader(); tampilkanBaris(temp + hasil);
        cout << "==============================================================================\n";
    } else cout << "  Waduh, ID " << x << " tidak ditemukan.\n";
}

void bubbleSortNama(Hewan* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        bool ada_swap = false;
        for (int j = 0; j < n - i - 1; j++)
            if ((arr + j)->nama > (arr + j + 1)->nama)
                { swapData(arr + j, arr + j + 1); ada_swap = true; }
        if (!ada_swap) break;
    }
    cout << "  Oke, diurutkan berdasarkan Nama (A-Z).\n";
    tampilkanSemua(arr, n);
}

void selectionSortHarga(Hewan* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int m = i;
        for (int j = i + 1; j < n; j++)
            if ((arr + j)->harga < (arr + m)->harga) m = j;
        if (m != i) swapData(arr + m, arr + i);
    }
    cout << "  Oke, diurutkan berdasarkan Harga (Termurah ke Termahal).\n";
    tampilkanSemua(arr, n);
}

// Queue - Single Linked List

// Enqueue – buat node baru, sambung ke rear
void enqueue(Queue* q, int idH, const string& namaH,
             const string& jenisH, const string& pemilik) {
    // Buat node baru di heap
    NodeAntrian* newNode = new NodeAntrian;
    newNode->idHewan    = idH;
    newNode->namaHewan  = namaH;
    newNode->jenisHewan = jenisH;
    newNode->pemilik    = pemilik;
    newNode->next       = nullptr;

    if (q->rear == nullptr) {
        // Antrian kosong: front dan rear tunjuk node baru
        q->front = newNode;
        q->rear  = newNode;
    } else {
        // Sambung node baru ke belakang rear
        q->rear->next = newNode;
        q->rear       = newNode;
    }
    q->size++;
    cout << "  Oke, " << namaH << " (ID:" << idH
         << ") berhasil masuk antrian. Posisi ke-" << q->size << ".\n";
}

// Dequeue – hapus node dari front, dan kembalikan datanya lewat parameter
bool dequeue(Queue* q, int& idH, string& namaH,
             string& jenisH, string& pemilik) {
    if (q->front == nullptr) {
        // Underflow  antrian kosong
        cout << "  Waduh, antrian kosong!\n";
        return false;
    }
    // Salin data dari node front
    NodeAntrian* temp = q->front;
    idH    = temp->idHewan;
    namaH  = temp->namaHewan;
    jenisH = temp->jenisHewan;
    pemilik= temp->pemilik;

    // Geser front ke node berikutnya
    q->front = q->front->next;
    if (q->front == nullptr) q->rear = nullptr; // antrian jadi kosong
    delete temp;   // bebaskan memori
    q->size--;
    return true;
}

// Peek Queue – lihat node terdepan tanpa menghapus
void peekQueue(Queue* q) {
    if (q->front == nullptr) {
        cout << "  Waduh, antrian kosong.\n";
        return;
    }
    NodeAntrian* p = q->front;
    cout << "  Terdepan: " << p->namaHewan << " (ID:" << p->idHewan
         << ") - " << p->jenisHewan << " | Pemilik: " << p->pemilik << "\n";
}

// Untuk menampilkan antrian – traversal dari front ke rear
void tampilQueue(Queue* q) {
    if (q->front == nullptr) {
        cout << "  Waduh, antrian kosong.\n";
        return;
    }
    cout << "  Jumlah antrian: " << q->size << " pasien\n";
    cout << "  ┌─ Antrian Pemeriksaan (SLL) ────────────────────────\n";
    NodeAntrian* curr = q->front;
    int urutan = 1;
    while (curr != nullptr) {
        cout << "  │ [" << urutan++ << "] "
             << curr->namaHewan << " (ID:" << curr->idHewan
             << ") - " << curr->jenisHewan
             << " | Pemilik: " << curr->pemilik;
        if (curr->next != nullptr) cout << " -> next";
        cout << "\n";
        curr = curr->next;
    }
    cout << "  │     └── NULL (akhir antrian)\n";
    cout << "  └────────────────────────────────────────────────────\n";
}

// Stack - Single Linked List

// Push – buat node baru, letakkan di atas top
void push(Stack* s, int idH, const string& namaH, const string& ket) {
    // Buat node baru di heap
    NodeRiwayat* newNode = new NodeRiwayat;
    newNode->idHewan    = idH;
    newNode->namaHewan  = namaH;
    newNode->keterangan = ket;
    newNode->next       = s->top;  // node baru menunjuk ke top lama
    s->top  = newNode;             // top sekarang adalah node baru
    s->size++;
    cout << "  Oke, tindakan untuk " << namaH << " berhasil dicatat.\n";
}

// POP untuk hapus node dari top
void pop(Stack* s) {
    if (s->top == nullptr) {
        // Underflow stack kosong
        cout << "  Waduh, riwayat kosong! Tidak ada yang bisa dibatalkan.\n";
        return;
    }
    NodeRiwayat* temp = s->top;
    cout << "  Oke, tindakan berhasil dihapus, nama : "
         << temp->namaHewan << " (ID:" << temp->idHewan
         << ") : " << temp->keterangan << "\n";
    s->top = s->top->next;  // top turun ke node di bawahnya
    delete temp;            // bebaskan memori
    s->size--;
}

// Peek Stack untuk lihat node paling atas tanpa menghapus
void peekStack(Stack* s) {
    if (s->top == nullptr) {
        cout << "  Waduh, riwayat kosong.\n";
        return;
    }
    NodeRiwayat* t = s->top;
    cout << "  Terakhir: " << t->namaHewan << " (ID:" << t->idHewan
         << ") -> " << t->keterangan << "\n";
}

// Tampil riwayat untuk traversal dari top ke bawah
void tampilStack(Stack* s) {
    if (s->top == nullptr) {
        cout << "  Waduh, riwayat kosong.\n";
        return;
    }
    cout << "  Jumlah riwayat: " << s->size << " tindakan\n";
    cout << "  ┌─ Riwayat Tindakan (Terbaru ke Terlama / SLL) ──────\n";
    NodeRiwayat* curr = s->top;
    int urutan = 1;
    while (curr != nullptr) {
        cout << "  │ [" << urutan++ << "] "
             << curr->namaHewan << " (ID:" << curr->idHewan
             << ") -> " << curr->keterangan;
        if (curr->next != nullptr) cout << " -> next";
        cout << "\n";
        curr = curr->next;
    }
    cout << "  │     └── NULL (akhir riwayat)\n";
    cout << "  └────────────────────────────────────────────────────\n";
}

// Untuk fungsi Main
int main() {
    Hewan dataHewan[MAX];
    int   n = 5;
    dataHewan[0] = {21, "Pusi",    "Kucing",  "Grooming",      150000};
    dataHewan[1] = {22, "Boby",    "Anjing",  "Vaksin Rabies", 250000};
    dataHewan[2] = {23, "Tralili", "Kelinci", "Check-up Gigi",  75000};
    dataHewan[3] = {24, "Micky",   "Kucing",  "Mandi Jamur",   120000};
    dataHewan[4] = {25, "Jecky",   "Anjing",  "Titip Sehari",  100000};

    Queue antrian;
    Stack riwayat;
    initQueue(&antrian);   // ini untuk parameter pointer ke struct 
    initStack(&riwayat);   // ini untuk parameter pointer ke struct 

    tampilMenu();

    string inputRaw;
    while (true) {
        cout << "\n  Pilih menu [0-13] ya: ";
        getline(cin, inputRaw);

        if (inputRaw == "m" || inputRaw == "M") { tampilMenu(); continue; }

        bool valid = !inputRaw.empty();
        for (char c : inputRaw) if (!isdigit(c)) { valid = false; break; }
        if (!valid) { cout << "  Masukkan angka 0-13 atau 'm' untuk menu.\n"; continue; }

        int pilihan = stoi(inputRaw);
        if (pilihan < 0 || pilihan > 13) {
            cout << "  Waduh, pilihan tidak ada. Coba angka 0-13.\n"; continue;
        }

        cout << "  ──────────────────────────────────────\n";

        // PILIHAN 0: KELUAR
        if (pilihan == 0) {
            cout << "  Terima kasih telah menggunakan Pawcare Petshop kami!\n";
            break;
        }
        // PILIHAN 1: TAMPIL SEMUA 
        else if (pilihan == 1) {
            tampilkanSemua(dataHewan, n);
        }
        // PILIHAN 2: TAMBAH DATA
        else if (pilihan == 2) {
            tambahData(dataHewan, n);
        }
        // PILIHAN 3: CARI NAMA
        else if (pilihan == 3) {
            string cari = inputString("  Ketik Nama Hewan: ");
            linearSearchNama(dataHewan, n, cari);
        }
        // PILIHAN 4: CARI ID 
        else if (pilihan == 4) {
            int idC = inputInt("  Ketik ID Hewan: ", 1);
            fibonacciSearchID(dataHewan, n, idC);
        }
        // PILIHAN 5: SORT NAMA
        else if (pilihan == 5) {
            bubbleSortNama(dataHewan, n);
        }
        // PILIHAN 6: SORT HARGA
        else if (pilihan == 6) {
            selectionSortHarga(dataHewan, n);
        }
        // PILIHAN 7: ENQUEUE
        else if (pilihan == 7) {
            cout << "  Gunakan data hewan yang ada? (y/n): ";
            string jawab; getline(cin, jawab);
            int    idH; string namaH, jenisH, pemilik;
            if (jawab == "y" || jawab == "Y") {
                tampilkanSemua(dataHewan, n);
                idH = inputInt("  Masukkan ID hewan: ", 1);
                bool ditemukan = false;
                for (int i = 0; i < n; i++)
                    if ((dataHewan + i)->id == idH) {
                        namaH  = (dataHewan + i)->nama;
                        jenisH = (dataHewan + i)->jenis;
                        ditemukan = true; break;
                    }
                if (!ditemukan) { cout << "  Waduh, ID tidak ditemukan.\n"; continue; }
            } else {
                idH    = inputInt("  ID Hewan   : ", 1);
                namaH  = inputString("  Nama Hewan : ");
                jenisH = inputString("  Jenis Hewan: ");
            }
            pemilik = inputString("  Nama Pemilik: ");
            enqueue(&antrian, idH, namaH, jenisH, pemilik);
        }
        // PILIHAN 8: DEQUEUE
        else if (pilihan == 8) {
            int    idH; string namaH, jenisH, pemilik;
            if (dequeue(&antrian, idH, namaH, jenisH, pemilik)) {
                cout << "  Pasien dipanggil:\n"
                     << "    Nama    : " << namaH   << "\n"
                     << "    ID      : " << idH     << "\n"
                     << "    Jenis   : " << jenisH  << "\n"
                     << "    Pemilik : " << pemilik << "\n"
                     << "    Status  : Siap diperiksa dokter.\n";
                cout << "  Catat tindakan sekarang? (y/n): ";
                string tanya; getline(cin, tanya);
                if (tanya == "y" || tanya == "Y") {
                    string ket = inputString("  Keterangan tindakan: ");
                    push(&riwayat, idH, namaH, ket);
                }
            }
        }
        // PILIHAN 9: PUSH
        else if (pilihan == 9) {
            int    idH = inputInt("  ID Hewan   : ", 1);
            string namaH = inputString("  Nama Hewan : ");
            string ket   = inputString("  Keterangan : ");
            push(&riwayat, idH, namaH, ket);
        }
        // PILIHAN 10: POP
        else if (pilihan == 10) {
            pop(&riwayat);
        }
        // PILIHAN 11: PEEK KEDUANYA
        else if (pilihan == 11) {
            cout << "  [Antrian Pemeriksaan]\n"; peekQueue(&antrian);
            cout << "  [Riwayat Tindakan]\n";   peekStack(&riwayat);
        }
        // PILIHAN 12: TAMPIL ANTRIAN
        else if (pilihan == 12) {
            tampilQueue(&antrian);
        }
        // PILIHAN 13: TAMPIL RIWAYAT
        else if (pilihan == 13) {
            tampilStack(&riwayat);
        }

        cout << "  ──────────────────────────────────────\n";
        cout << "  (Ketik angka pilihan atau 'm' untuk lihat menu)\n";
    }

    return 0;
}
