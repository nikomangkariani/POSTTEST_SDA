#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Untuk konstanta
const int MAX         = 100;
const int MAX_ANTRIAN = 20;
const int MAX_RIWAYAT = 20;

//  Untuk Struck
struct Hewan {
    int    id;
    string nama;
    string jenis;
    string layanan;
    int    harga;
};

struct Pasien {
    int    idHewan;
    string namaHewan;
    string jenisHewan;
    string pemilik;
};

struct Tindakan {
    int    idHewan;
    string namaHewan;
    string keterangan;
};

// Untuk Swap Data
void swapData(Hewan* a, Hewan* b) {
    Hewan temp = *a; *a = *b; *b = temp;
}

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

// Untuk Menampilkan Tabel
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
    if (n == 0) { cout << " Waduh Data masih kosong.\n"; return; }
    tampilkanHeader();
    for (int i = 0; i < n; i++) tampilkanBaris(arr + i);
    cout << "==============================================================================\n";
}

// Untuk Menampilkan Menu
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
    cout << "||  ANTRIAN & RIWAYAT                      ||\n";
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

// Untuk Fungsi Pada Pt 2
void tambahData(Hewan* arr, int& n) {
    if (n >= MAX) { cout << " Waduh Data penuh!\n"; return; }
    bool idSudahAda; int idBaru;
    do {
        idSudahAda = false;
        idBaru = inputInt("  ID Hewan      : ", 1);
        for (int i = 0; i < n; i++)
            if ((arr + i)->id == idBaru) { idSudahAda = true; break; }
        if (idSudahAda) cout << " Waduh ID " << idBaru << " sudah ada!\n";
    } while (idSudahAda);

    (arr + n)->id      = idBaru;
    (arr + n)->nama    = inputString("  Nama Hewan    : ");
    (arr + n)->jenis   = inputString("  Jenis Hewan   : ");
    (arr + n)->layanan = inputString("  Jenis Layanan : ");
    (arr + n)->harga   = inputInt("  Harga (Rp)    : ", 0);
    n++;
    cout << "  Oke Data berhasil ditambahkan!\n";
}

void linearSearchNama(Hewan* arr, int n, const string& cari) {
    int cocok[MAX], jumlahCocok = 0;
    for (int i = 0; i < n; i++)
        if ((arr + i)->nama == cari) cocok[jumlahCocok++] = i;

    if (jumlahCocok == 0) { cout << " Waduh Nama '" << cari << "' tidak ditemukan.\n"; return; }

    cout << " Oke Ditemukan " << jumlahCocok << " data:\n";
    tampilkanHeader();
    for (int k = 0; k < jumlahCocok; k++) tampilkanBaris(arr + cocok[k]);
    cout << "==============================================================================\n";

    // Hasil Swap
    if (cocok[0] != 0) {
        Hewan* pHasil = arr + cocok[0];
        Hewan* pDepan = arr;
        swapData(pHasil, pDepan);
        
    }
}

void fibonacciSearchID(Hewan* arr, int n, int x) {
    if (n == 0) { cout << "  Data kosong.\n"; return; }
    Hewan temp[MAX];
    for (int i = 0; i < n; i++) *(temp + i) = *(arr + i);

    // Untuk Mengurutkan salinan array berdasarkan ID
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
        cout << " Oke Data ditemukan:\n";
        tampilkanHeader(); tampilkanBaris(temp + hasil);
        cout << "==============================================================================\n";
    } else cout << " Waduh ID " << x << " tidak ditemukan.\n";
}

void bubbleSortNama(Hewan* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        bool ada_swap = false;
        for (int j = 0; j < n - i - 1; j++)
            if ((arr + j)->nama > (arr + j + 1)->nama)
                { swapData(arr + j, arr + j + 1); ada_swap = true; }
        if (!ada_swap) break;
    }
    cout << " Oke Diurutkan berdasarkan Nama (A-Z).\n";
    tampilkanSemua(arr, n);
}

void selectionSortHarga(Hewan* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int m = i;
        for (int j = i + 1; j < n; j++)
            if ((arr + j)->harga < (arr + m)->harga) m = j;
        if (m != i) swapData(arr + m, arr + i);
    }
    cout << " Oke Diurutkan berdasarkan Harga (Termurah ke Termahal).\n";
    tampilkanSemua(arr, n);
}

// Untuk Queue
struct Queue { Pasien data[MAX_ANTRIAN]; int front, rear, size; };

void initQueue(Queue* q)     { q->front = 0; q->rear = -1; q->size = 0; }
bool isQueueEmpty(Queue* q)  { return q->size == 0; }
bool isQueueFull (Queue* q)  { return q->size == MAX_ANTRIAN; }

void enqueue(Queue* q, Pasien* p) {
    if (isQueueFull(q)) { cout << " Maaf Antrian penuh!\n"; return; }
    q->rear = (q->rear + 1) % MAX_ANTRIAN;
    *(q->data + q->rear) = *p;
    q->size++;
    cout << " Oke " << p->namaHewan << " (ID:" << p->idHewan
         << ") Berhasil masuk antrian. Posisi ke-" << q->size << ".\n";
}

bool dequeue(Queue* q, Pasien* hasil) {
    if (isQueueEmpty(q)) { cout << " Waduh Antrian kosong!\n"; return false; }
    *hasil = *(q->data + q->front);
    q->front = (q->front + 1) % MAX_ANTRIAN;
    q->size--;
    return true;
}

void peekQueue(Queue* q) {
    if (isQueueEmpty(q)) { cout << " Waduh Antrian kosong.\n"; return; }
    Pasien* p = q->data + q->front;
    cout << "  Terdepan: " << p->namaHewan << " (ID:" << p->idHewan
         << ") - " << p->jenisHewan << " | Pemilik: " << p->pemilik << "\n";
}

void tampilQueue(Queue* q) {
    if (isQueueEmpty(q)) { cout << " Waduh Antrian kosong.\n"; return; }
    cout << "  ┌─ Antrian Pemeriksaan ──────────────\n";
    for (int i = 0; i < q->size; i++) {
        Pasien* p = q->data + (q->front + i) % MAX_ANTRIAN;
        cout << "  │ [" << (i+1) << "] " << p->namaHewan
             << " (ID:" << p->idHewan << ") - " << p->jenisHewan
             << " | Pemilik: " << p->pemilik << "\n";
    }
    cout << "  └───────────────────────────────────────────────────\n";
}

// Untuk Stack
struct Stack { Tindakan data[MAX_RIWAYAT]; int top; };

void initStack(Stack* s)    { s->top = -1; }
bool isStackEmpty(Stack* s) { return s->top == -1; }
bool isStackFull (Stack* s) { return s->top == MAX_RIWAYAT - 1; }

void push(Stack* s, Tindakan* t) {
    if (isStackFull(s)) { cout << " Riwayat penuh!\n"; return; }
    *(s->data + (++s->top)) = *t;
    cout << " Oke Tindakan untuk " << t->namaHewan << " berhasil dicatat.\n";
}

void pop(Stack* s) {
    if (isStackEmpty(s)) { cout << " Riwayat kosong!\n"; return; }
    Tindakan* t = s->data + s->top--;
    cout << " Oke Tindakan berhasil dihapus -> " << t->namaHewan
         << " (ID:" << t->idHewan << ") : " << t->keterangan << "\n";
}

void peekStack(Stack* s) {
    if (isStackEmpty(s)) { cout << " Waduh Riwayat kosong.\n"; return; }
    Tindakan* t = s->data + s->top;
    cout << "  Terakhir: " << t->namaHewan << " (ID:" << t->idHewan
         << ") → " << t->keterangan << "\n";
}

void tampilStack(Stack* s) {
    if (isStackEmpty(s)) { cout << " Waduh Riwayat kosong.\n"; return; }
    cout << "  ┌─ Riwayat Tindakan (Terbaru ke Terlama) ────────────\n";
    for (int i = s->top; i >= 0; i--) {
        Tindakan* t = s->data + i;
        cout << "  │ [" << (s->top - i + 1) << "] "
             << t->namaHewan << " (ID:" << t->idHewan
             << ") → " << t->keterangan << "\n";
    }
    cout << "  └───────────────────────────────────────────────────\n";
}

// Untuk Fungsi Main
int main() {
    Hewan dataHewan[MAX];
    int   n = 5;
    dataHewan[0] = {21, "Pusi",    "Kucing",  "Grooming",      150000};
    dataHewan[1] = {22, "Boby",    "Anjing",  "Vaksin Rabies", 250000};
    dataHewan[2] = {23, "Tralili", "Kelinci", "Check-up Gigi",  75000};
    dataHewan[3] = {24, "Micky",   "Kucing",  "Mandi Jamur",   120000};
    dataHewan[4] = {25, "Jecky",   "Anjing",  "Titip Sehari",  100000};

    Queue antrian; initQueue(&antrian);
    Stack riwayat; initStack(&riwayat);

    // Untuk Menampilkan menu sekali di awal
    tampilMenu();

    string inputRaw;
    while (true) {
        // Prompt input
        cout << "\n  Pilih menu [0-13] ya: ";
        getline(cin, inputRaw);

        // Kalau user ketik 'm', menampilkan menu lagi
        if (inputRaw == "m" || inputRaw == "M") {
            tampilMenu();
            continue;
        }

        // Untuk Validasi angka
        bool valid = !inputRaw.empty();
        for (char c : inputRaw) if (!isdigit(c)) { valid = false; break; }
        if (!valid) { cout << "  Masukkan angka 1-13 atau ketik 'm' untuk ke menu.\n"; continue; }

        int pilihan = stoi(inputRaw);
        if (pilihan < 0 || pilihan > 13) {
            cout << " Waduh Pilihan tidak ada. Coba masukkan angka 1-14.\n"; continue;
        }

    
        cout << "  ──────────────────────────────────────\n";

        // Eksekusi
        if (pilihan == 0) {
            cout << "  Terima kasih telah menggunakan Pawcare Petshop!\n";
            break;
        }
        else if (pilihan == 1) {
            tampilkanSemua(dataHewan, n);
        }
        else if (pilihan == 2) {
            tambahData(dataHewan, n);
        }
        else if (pilihan == 3) {
            string cari = inputString("  Ketik Nama Hewan: ");
            linearSearchNama(dataHewan, n, cari);
        }
        else if (pilihan == 4) {
            int idC = inputInt("  Ketik ID Hewan: ", 1);
            fibonacciSearchID(dataHewan, n, idC);
        }
        else if (pilihan == 5) {
            bubbleSortNama(dataHewan, n);
        }
        else if (pilihan == 6) {
            selectionSortHarga(dataHewan, n);
        }
        else if (pilihan == 7) {
            cout << "  Gunakan data hewan yang ada? (y/n): ";
            string jawab; getline(cin, jawab);
            Pasien p;
            if (jawab == "y" || jawab == "Y") {
                tampilkanSemua(dataHewan, n);
                p.idHewan = inputInt("  Masukkan ID hewan: ", 1);
                bool ditemukan = false;
                for (int i = 0; i < n; i++)
                    if ((dataHewan + i)->id == p.idHewan)
                        { p.namaHewan = (dataHewan+i)->nama; p.jenisHewan = (dataHewan+i)->jenis; ditemukan = true; break; }
                if (!ditemukan) { cout << " Waduh ID tidak ditemukan.\n"; continue; }
            } else {
                p.idHewan    = inputInt("  ID Hewan   : ", 1);
                p.namaHewan  = inputString("  Nama Hewan : ");
                p.jenisHewan = inputString("  Jenis Hewan: ");
            }
            p.pemilik = inputString("  Nama Pemilik: ");
            enqueue(&antrian, &p);
        }
        else if (pilihan == 8) {
            Pasien dipanggil;
            if (dequeue(&antrian, &dipanggil)) {
                cout << "  Pasien dipanggil:\n"
                     << "    Nama    : " << dipanggil.namaHewan  << "\n"
                     << "    ID      : " << dipanggil.idHewan    << "\n"
                     << "    Jenis   : " << dipanggil.jenisHewan << "\n"
                     << "    Pemilik : " << dipanggil.pemilik    << "\n"
                     << "    Status  : Siap diperiksa dokter.\n";
                cout << "  Catat tindakan sekarang? (y/n): ";
                string jawab; getline(cin, jawab);
                if (jawab == "y" || jawab == "Y") {
                    Tindakan t;
                    t.idHewan    = dipanggil.idHewan;
                    t.namaHewan  = dipanggil.namaHewan;
                    t.keterangan = inputString("  Keterangan tindakan: ");
                    push(&riwayat, &t);
                }
            }
        }
        else if (pilihan == 9) {
            Tindakan t;
            t.idHewan    = inputInt("  ID Hewan   : ", 1);
            t.namaHewan  = inputString("  Nama Hewan : ");
            t.keterangan = inputString("  Keterangan : ");
            push(&riwayat, &t);
        }
        else if (pilihan == 10) {
            pop(&riwayat);
        }
        else if (pilihan == 11) {
            cout << "  [Antrian Pemeriksaan]\n"; peekQueue(&antrian);
            cout << "  [Riwayat Tindakan]\n";   peekStack(&riwayat);
        }
        else if (pilihan == 12) {
            tampilQueue(&antrian);
        }
        else if (pilihan == 13) {
            tampilStack(&riwayat);
        }

        cout << "  ──────────────────────────────────────\n";
        cout << "  (Ketik angka pilihan atau ketik 'm' untuk lihat menu)\n";
    }

    return 0;
}
