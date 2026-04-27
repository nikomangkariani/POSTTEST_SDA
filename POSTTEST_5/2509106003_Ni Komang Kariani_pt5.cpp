#include <iostream>
#include <string>
using namespace std;

// Struktur Node untuk Circular Linked List Toko Sembako
struct BarangNode {
    string namaBarang;
    int stok;
    BarangNode* next;

    // Constructor
    BarangNode(string nama, int jumlah) {
        namaBarang = nama;
        stok = jumlah;
        next = nullptr;
    }
};

// Fungsi insert di akhir Circular Linked List untuk membangun data
BarangNode* tambahBarang(BarangNode* head, string nama, int jumlah) {
    BarangNode* newNode = new BarangNode(nama, jumlah);
    if (head == nullptr) {
        newNode->next = newNode; // Menunjuk ke dirinya sendiri (Sirkuler)
        return newNode;
    }
    
    BarangNode* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = head;
    return head;
}

void tampilkanStokSembako(BarangNode* head) {
    // kalau listnya kosong, langsung bilang gudang kosong
    if (head == nullptr) {
        cout << "Gudang kosong." << endl;
        return;
    }

    BarangNode* temp = head; // mulai dari node pertama

    // pakai do-while supaya node pertama terbaca dulu lalu dicek
    do {
        cout << "- " << temp->namaBarang << ": " << temp->stok << endl; // tampilkan nama sama stoknya
        temp = temp->next; // geser ke node berikutnya
    } while (temp != head); // stop jika sudah balik ke awal
}

int main() {
    BarangNode* head = nullptr;
    
    head = tambahBarang(head, "Beras", 50);
    head = tambahBarang(head, "Minyak Goreng", 30);
    head = tambahBarang(head, "Gula Pasir", 20);
    head = tambahBarang(head, "Tepung Terigu", 15);

    cout << "Daftar Stok Sembako:" << endl;
    tampilkanStokSembako(head); 
    
    return 0;
}