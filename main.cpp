#include <iostream> //untuk fungsi input dan output seperti cout << untuk menampilkan data dan cin >> untuk menerima input dari pengguna
#include <stdlib.h> //untuk pengelolaan memori secara dinamis, yaitu membuat node baru dengan malloc() dan menghapus node dengan free()
#include <string.h> //untuk operasi pada string seperti menyalin string menggunakan strcpy() dan membandingkan string menggunakan strcmp()
#include <time.h> //untuk mengakses tanggal dan waktu seperti menghitung lama peminjaman atau sisa waktu sebelum buku harus dikembalikan
using namespace std;

// STRUKTUR DATA & MENAMBAH BUKU --> ANJAANIE MAFAZA SAHILAH
// STRUCT BUKU
// Menyimpan seluruh informasi buku
typedef struct Buku{
    char id[20];
    char judul[100];
    char pengarang[100];
    int tahunTerbit;
    char kategori[50];
    char penerbit[100];
    int tersedia; // 1 = tersedia, 0 = tidak tersedia
} Buku;

// NODE DOUBLY LINKED LIST
// Setiap node menyimpan satu data buku serta pointer ke node sebelumnya dan berikutnya
typedef struct NodeBuku{
    Buku data;
    struct NodeBuku *prev;
    struct NodeBuku *next;
} NodeBuku;

// POINTER HEAD DAN TAIL
// head = node pertama, tail = node terakhir
NodeBuku *head = NULL;
NodeBuku *tail = NULL;

// PROTOTYPE FUNGSI
NodeBuku* buatNode(Buku dataBaru);
void tambahBuku();

// FUNGSI MEMBUAT NODE BARU
NodeBuku* buatNode(Buku dataBaru){
    NodeBuku *baru = new NodeBuku;
    baru->data = dataBaru;
    baru->prev = NULL;
    baru->next = NULL;
    return baru;
}

// FITUR TAMBAH BUKU
// Menambahkan buku ke akhir Doubly Linked List
void tambahBuku(){
    Buku bukuBaru;

    cout << "\n======================\n";
    cout << "     TAMBAH BUKU\n";
    cout << "========================\n";

    cin.ignore();

    // Input ID Buku
    cout << "ID Buku                : ";
    cin.getline(bukuBaru.id,20);

    // Input Judul Buku
    cout << "Judul Buku             : ";
    cin.getline(bukuBaru.judul,100);

    // Input Pengarang
    cout << "Pengarang              : ";
    cin.getline(bukuBaru.pengarang,100);

    // Input Tahun Terbit
    cout << "Tahun Terbit           : ";
    cin >> bukuBaru.tahunTerbit;

    cin.ignore();

    // Input Kategori
    cout << "Kategori               : ";
    cin.getline(bukuBaru.kategori,50);

    // Input Nama Penerbit
    cout << "Nama Penerbit          : ";
    cin.getline(bukuBaru.penerbit,100);

    // Input Status Ketersediaan
    cout << "Ketersediaan (1/0)     : ";
    cin >> bukuBaru.tersedia;

    // Membuat node baru
    NodeBuku *baru = buatNode(bukuBaru);

    // Jika linked list masih kosong
    if(head == NULL){
        head = baru;
        tail = baru;
    }

    // Jika sudah ada data
    else{
        tail->next = baru;
        baru->prev = tail;
        tail = baru;
    }

    cout << "\nBuku berhasil ditambahkan.\n";
}


typedef struct DataAntrian{
    char idBuku[20]; // ID buku yang dipinjam 
    char judul[100]; // Judul buku
    char namaPeminjam[100]; // Nama Peminjam
    char nim[20]; // Nim Peminjam
    char hari[20]; // Hari peminjam (Senin, Selasa, Rabu, Kamis, Jum'at)

    // Tanggal peminjaman buku
    // Digunakan untuk menghitung sisa waktu peminjaman
    int tanggal;   // Tanggal peminjaman
    int bulan;    // Bulan peminjaman
    int tahun;    // Tahun peminjaman
}DataAntrian;

// Node Queue untuk setiap node menyimpan satu data peminjam serta pointer menuju node berikutnya
typedef struct NodeQueue{
    DataAntrian data; 
    struct NodeQueue *next;
}NodeQueue; 
typedef struct{
    NodeQueue *first;
    NodeQueue *last;
}Queue; 
// Prototype Fungsi
// Sorting Buku
void sortingJudulAZ();
void sortingStatus();
// Queue
void createQueue(Queue *Q);
int isEmpty(Queue Q);
void enqueue(Queue *Q, DataAntrian dataBaru);
void dequeue(Queue *Q);
// Peminjaman dan Pengembalian
void pinjamBuku(Queue *Q);
void kembalikanBuku(Queue *Q);
// Tampilan 
void tampilDaftarTunggu(Queue Q);
// Perhitungan waktu peminjaman
void hitungSisaPeminjaman(DataAntrian data);

// HAPUS & MENCARI BUKU --> CHRISTINNA BATA

// pencarian buku berdasarkan id buku
void cariBuku(Queue Q) {
    if (isEmpty(Q)) {
        cout << "\nDaftar buku di sistem kosong. Tidak ada buku yang terdaftar saat ini.\n";
        return;
    }

    char cariID[20];
    cout << "\n==============================\n";
    cout << "         CARI BUKU BY ID";
    cout << "\n==============================\n";
    cout << "Masukkan ID buku yang dicari: ";
    cin >> cariID;

    NodeQueue *bantu = Q.first;
    int ditemukan = 0;

    // menelusuri seluruh daftar buku di sistem
    while (bantu != NULL) {
        // membandingkan id buku yang dicari
        if (strcmp(bantu->data.idBuku, cariID) == 0) {
            ditemukan = 1;
            cout << "\n== Buku ditemukan! ==\n";
            cout << "ID Buku    : " << bantu->data.idBuku << "\n";
            cout << "Judul Buku : " << bantu->data.judul << "\n";
            if (strlen(bantu->data.nim) == 0 || strcmp(bantu->data.nim, "-") == 0) {
                cout << "Status    : Available / Tersedia\n";
            } else {
                cout << "Status    : Sedang dipinjam/antri oleh " << bantu->data.namaPeminjam << " (NIM: " << bantu->data.nim << ")\n";
            }
        }
        bantu = bantu->next;
    }

    if (!ditemukan) {
        cout << "\nBuku dengan ID tersebut tidak ditemukan di dalam sistem.\n";
    }
    cout << "=======================================================\n";
}

// penghapusan data buku berdasarkan id buku
delBuku(Queue *Q) {
    if (isEmpty(*Q)) {
        cout << "\nDaftar buku di sistem kosong. Tidak ada buku untuk dihapus.\n";
        return;
    }

    char delID[20];
    cout << "\n==============================\n";
    cout << "        HAPUS BUKU BY ID";
    cout << "\n==============================\n";
    cout << "Masukkan ID buku yang ingin dihapus: ";
    cin >> delID;

    NodeQueue *bantu = Q->first;
    NodeQueue *prev = NULL;
    int ditemukan = 0;

    while (bantu != NULL) {
        if (strcmp(bantu->data.idBuku, delID) == 0) {
            ditemukan = 1;

            // jika buku berada di urutan pertama
            if (bantu == Q->first) {
                Q->first = Q->first->next;
                if (Q->first == NULL) {
                    Q->last = NULL;
                }
            }

            // jika buku berada di urutan terakhir
            else if (bantu == Q->last) {
                Q->last = prev;
                Q->last->next = NULL;
            }
            // jika buku berada di tengah daftar
            else {
                prev->next = bantu->next;
            }

            NodeQueue *hapus = bantu;
            bantu = bantu->next;  
            free(hapus);  

            cout << "\nBuku dengan ID " << delID << " berhasil dihapus dari sistem.\n";
            break;
        } else {
            prev = bantu;
            bantu = bantu->next;
        }
    }
    
    if (!ditemukan) {
        cout << "\nBuku dengan ID tersebut tidak ditemukan di dalam sistem.\n";
    }
    cout << "=======================================================\n";
}

// MENAMPILKAN BUKU & SORTING -- Jelli Wanti Eriska Pardosi
// sorting  buku berdasarkan judul dari A-Z
void sortingJudulAZ(){

    if(head == NULL){ // Jika data buku kosong
        return;
    }
   //pointer untuk membantu proses perbandigan 
    Node *i, *j; //i untuk di periksa, j = pembannding 
    

    // Membandingkan setiap judul buku
    for(i = head; i != NULL; i = i->next){

        for(j = i->next; j != NULL; j = j->next){ //pointer j selalu dimulai dari i

            // Jika judul pada node i lebih besar
            if(i->data.judul > j->data.judul){

                // Tukar data buku
                Buku temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

// Mengurutkan buku berdasarkan status ketersediaan
void sortingStatus(){

    // Jika data buku kosong
    if(head == NULL){
        return;
    }

    Node *i, *j;

    for(i = head; i != NULL; i = i->next){

        for(j = i->next; j != NULL; j = j->next){

            // Buku tersedia ditempatkan di atas
            if(i->data.tersedia < j->data.tersedia){

                Buku temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}
// Menampilkan seluruh data buku
void tampilkanBuku(){

    if(head == NULL){
        cout << "\nBelum ada data buku.\n";
        return;
    }

    Node *current = head; //Membuat pointer bantu bernama current untuk berjalan dari node pertama ke node terakhir.

    cout << "\n============================================================================================\n";
    cout << "ID\tJudul\t\tPengarang\tKategori\tStatus\n";
    cout << "==============================================================================================\n";

    while(current != NULL){  //buku akan ditampilkan selama current belum null

        cout << current->data.id << "\t"
             << current->data.judul << "\t\t"
             << current->data.pengarang << "\t\t"
             << current->data.kategori << "\t\t"
             << (current->data.tersedia ? "Tersedia" : "tidak tersedia")
             << endl;

        current = current->next;
    }
}

// Menu menampilkan buku
void menuTampilkanBuku(){

    int pilihan;

    cout << "\n===== TAMPILKAN BUKU =====\n";
    cout << "1. Urut Berdasarkan Judul (A-Z)\n";
    cout << "2. Urut Berdasarkan Status Ketersediaan\n";
    cout << "Pilihan : ";
    cin >> pilihan;

    switch(pilihan){

        case 1: //jika user memilih sorting berdasarkan abjad
            sortingJudulAZ();
            tampilkanBuku();
            break;

        case 2: //jika user mimilih sorting berdasarkan status 
            sortingStatus();
            tampilkanBuku();
            break;

        default:
            cout << "Pilihan tidak valid.\n";
    }
}


// QUEUE, PEMINJAMAN, & PENGEMBALIAN --> FITRI AULIA
// Membuat queue kosong 
// Saat pertama kali program dijalankan, first dan last bernilai Null
void createQueue(Queue *Q){
    Q->first = NULL;
    Q->last = NULL;
}
// Mengecek apakah queue masih kosong 
// Return:
// 1 = Kosong
// 0 = Tidak kosong
int isEmpty(Queue Q){
    if(Q.first == NULL)
        return 1;
    else
        return 0;
}

// Menambahkan peminjam ke daftar tunggu
// Konsep FIFO
// Orang yang masuk lebih dulu akan mendapatkan buku lebih dulu
void enqueue(Queue *Q, DataAntrian dataBaru) {
    // Membuat node baru
    NodeQueue *baru;
    baru = (NodeQueue*)malloc(sizeof(NodeQueue));
    // Mengisi data node 
    baru->data = dataBaru;
    baru->next = NULL;
    // Jika queue masih kosong 
    if(isEmpty(*Q)){
        // Node baru menjadi fisrt dan last
        Q->first = baru;
        Q->last = baru;
    }
    // Jika Queue sudah memiliki isi
    else{
        // Node baru disambungkan di belakang
        Q->last->next = baru;
        // Last dipindahkan ke node baru
        Q->last = baru; 
    }
    cout << "\nPeminjam berhasil masuk ke daftar tunggu.\n";
}

// Menghapus peminjam paling depan 
// Orang pertama dalam antrian akan keluar terlebih dahulu
void dequeue(Queue *Q){
    // Queue kosong
    if(isEmpty(*Q)){
        printf("\nDaftar tunggu kosong.\n");
        return;
    }
    NodeQueue *hapus = Q->first;
    // Jika hanya ada satu orang
    if(Q->first == Q->last){
        Q->first = NULL;
        Q->last = NULL;
    }
    // Jika lebih dari satu orang 
    else{
        // first berpindah ke node berikutnya
        Q->first = Q->first->next;
    }
    // Menghapus node dari memori
    free(hapus);
}

// Fungsi untuk meminjam buku
// Data peminjam akan dimasukkan ke dalam queue
// Sesuai kosep FIFO (First In First Out)
void pinjamBuku(Queue *Q){
    // Membuat variabel sementara untuk menyimpan data input
    DataAntrian data;
    cout << "\n========================================================\n";
    cout << "                    PINJAM BUKU\n";
    cout << "========================================================\n";
    // Meminta pengguna memasukkan data peminjaman
    cout << "ID Buku                             : ";
    cin >> "%s", data.idBuku;

    cout << "Judul Buku                          : ";
    cin >> " %[^\n]", data.judul;

    cout << "Nama Peminjam                       : ";
    cin >> " %[^\n]", data.namaPeminjam;

    cout << "NIM                                 : ";
    cin >> "%s", data.nim;

    cout << "Hari                                : ";
    cin >> " %[^\n]", data.hari;

    cout << "Tanggal                             :";
    cin >> "%d", &data.tanggal;

    cout << "Bulan                               :";
    cin >> "%d", &data.bulan;

    cout << "Tahun                               :";
    cin >> "%d", &data.tahun;

    // Memasukkan data peminjam ke queue
    enqueue(Q, data);
}
// Fungsi untuk mengembalikan buku
// Peminjam paling depan akan dikeluarkan dari queue
void kembalikanBuku(Queue *Q){
    // Mengecek apakah queue masih kosong
    if(isEmpty(*Q)){
        cout("\nDaftar tunggu kosong.\n");
        return;
    }

    cout << "\n=======================================================\n";
    cout << "                    PENGEMBALIAN BUKU\n";
    cout << "==========================================================\n"; 

    // Menampilkan data peminjam yang mengembalikan buku
    cout << "ID Buku             : %s\n",Q->first->data.idBuku;
    cout << "Judul Buku          : %s\n",Q->first->data.judul;
    cout << "Nama Peminjam       : %s\n",Q->first->data.namaPeminjam;
    cout << "NIM                 : %s\n",Q->first->data.nim;

    // Menghapus data peminjam dari queue
    dequeue(Q);
    cout << "\nBuku berhasil dikembalikan.\n";
}
// Fungsi untuk menampilkan seluruh isi queue
// Data ditampilkan dalam bentuk tabel
void tampilDaftarTunggu(Queue Q){
    // Pointer bantu untuk traversal queue
    NodeQueue *bantu;
    // Nomor urut data
    int no = 1;
    // Mengecek apakah queue kosong 
    if(isEmpty(Q)){
        cout("\nDaftar tunggu kosong.\n");
        return;
    }
    // Pointer bantu dimulai dari elemen pertama
    bantu = Q.first;
    cout << "\n=============================================================================================================\n";
    cout << "| No | ID Buku | Judul Buku        | Nama Peminjam         | NIM     | Hari  | Tanggal | Bulan | Tahun |\n";
    cout << "=============================================================================================================\n";
    // Menampilkan seluruh isi queue
    while(bantu != NULL){
        cout("| %-2d | %-7s | %-25s | %-21s | %-10s | %-8s | %-7d | %-5d | %-5d |\n", 
                no,
                bantu->data.idBuku,
                bantu->data.judul,
                bantu->data.namaPeminjam,
                bantu->data.nim,
                bantu->data.hari,
                bantu->data.tanggal,
                bantu->data.bulan,
                bantu->data.tahun);
        // Berpisah ke node berikutnya
        bantu = bantu->next;
        // Menambah nomor urut
        no++;
    }

    cout << "=============================================================================================================\n";
    cout << "\n");
    cout << "========================================================\n";
    cout << "            SISA WAKTU PEMINJAMAN\n");
    cout << "========================================================\n";

    // Pointer bantu di-reset ke awal queue
    bantu = Q.first;
    // Menelusuri ulang seluruh data untuk menampilkan detail sisa waktu
    while(bantu != NULL){
        cout << "\nNama Peminjam : %s\n", bantu->data.namaPeminjam;
        cout << "Judul Buku      : %s\n", bantu->data.judul;
    // Memanggil fungsi untuk menghitung sisa waktu peminjaman
    hitungSisaPeminjaman(bantu->data);

    cout("---------------------------------------------------------\n");
    bantu = bantu->next;
    }
}
// Fungsi untuk menghitung sisa waktu peminjaman buku 
// Ketentuan: 
// 1. Masa peminjaman buku adalah 7 hari
// 2. Program akan menghitung berapa hari lagi sebelum buku harus dikembalikan 
// 3. Jika melewati batas waktu, program akan menampilkan jumlah hari keterlambatan
void hitungSisaPeminjaman(DataAntrian data){
    // Struktur untuk menyimpan tanggak peminjaman 
    struct tm tanggalPinjam = {0};

    // Mengatur detik, menit, dan jam ke pukul 12:00:00 (siang)
    tanggalPinjam.tm_sec = 0;
    tanggalPinjam.tm_min = 0;
    tanggalPinjam.tm_hour = 12;
    // Mengisi data tanggal peminjam dari input pengguna
    tanggalPinjam.tm_mday = data.tanggal;
    // Mengisi bulan peminjaman
    // Pada struct tm, Januari = 0 dan Desember = 11
    tanggalPinjam.tm_mon = data.bulan - 1;
    // Mengisi tahun peminjaman 
    //mengurangi 1900 karena baris perhitungan struct tm dimulai dari tahun 1900
    tanggalPinjam.tm_year = data.tahun - 1900;
    // Mengatur DST (Daylight Saving Time) ke -1 agar sistem operasi menentukan secara otomatis berdasarkan lokal waktu
    tanggalPinjam.tm_isdst = -1;

    // Mengubah ke format waktu sistem 
    time_t waktuPinjam = mktime(&tanggalPinjam);
    // Jika mktime mengembalikan nilai -1, berarti input tanggal dari user tidak valid
    if(waktuPinjam == -1) {
        cout << "Gagal memproses tanggal peminjaman.\n";
        return;
    }

    // Menentukan batas peminjaman selama 7 hari ke dalam detik (7 hari * 24 jam * 60 menit * 60 detik) untuk mendapatkan deadline
    time_t batasPinjam = waktuPinjam + (7 * 24 * 60 * 60);

    // Mengambil waktu real-time saat ini dari sistem komputer
    time_t sekarang = time(NULL);

    // Menghitung selisih dalam hari
    // difftime() mencari selisih antara batas akhir pinjam dengan waktu saat ini (dalam satuan detik)
    double selisihHari = difftime(batasPinjam, sekarang) / (60 * 60 * 24); 

    // Menampilkan hasil perhitungan 
    // Jika selisih hari di atas 0, berarti tanggal sekarang belum melewati batas deadline (belum jatuh tempo)
    if(selisihHari > 0){
        // %.0f digunakan untuk membulatkan bilangan desimal ke integer terdekat
        cout << "Sisa Waktu Peminjaman : %.0f hari lagi\n", selisihHari;
    }
    // Jika selisih hari bernilai 0 atau negatif, berarti peminjam sudah telat mengembalikan buku
    else{
        // // Variabel selisihHari diubah menjadi positif dengan tanda minus (-) di depannya agar jumlah hari terlambat tidak tertulis minus
        cout << "Status Peminjaman      : Terlambat %.0f hari\n", -selisihHari;
    }
}
// Program Utama
int main(){
    // Membuat queue daftar tunggu
    Queue daftarTunggu;
    // Menginisialisasi queue menjadi kosong
    createQueue(&daftarTunggu);
    // Variabel pilihan menu
    int pilihan;
    do{
        cout << "\n========================================================\n";
        cout << "           SISTEM MANAJEMEN PERPUSTAKAAN\n";
        cout << "========================================================\n";
        cout << "| 1 | Pinjam Buku                                    |\n";
        cout << "| 2 | Kembalikan Buku                                |\n";
        cout << "| 3 | Lihat Daftar Tunggu                            |\n";
        cout << "| 4 | Keluar                                         |\n";
        cout << "========================================================\n";

        // Meminta pengguna memilih menu
        cout("Masukkan Pilihan : ");
        cin("%d",&pilihan);

        switch(pilihan){

            // Menu pinjam buku
            case 1:
                pinjamBuku(&daftarTunggu);
                break;

            // Menu pengembalian buku
            case 2:
                kembalikanBuku(&daftarTunggu);
                break;

            // Menu melihat daftar tunggu
            case 3:
            if (!isEmpty(daftarTunggu)){
                cout << "========================================================\n";
                cout << "            SISA WAKTU PEMINJAMAN\n";
                cout << "========================================================\n";
                
                // Mengambil data dari antrian paling depan (first)
                DataAntrian dataDepan = daftarTunggu.first->data;
                // Memanggil fungsi
                hitungSisaPeminjaman(dataDepan);
                cout << "=========================================================\n";
            }
            tampilDaftarTunggu(daftarTunggu);
            break;
            // Keluar dari program 
            case 4:
                 cout << "\n=====================================================\n";
                 cout << "Terima kasih telah menggunakan\n";
                 cout << "Sistem Manajemen Perpustakaan.\n";
                 cout << "Program selesai.\n";
                 cout << "=====================================================\n";
                 break; 

            // Jika pilihan tidak tersedia
            default:
                cout << "\nPilihan tidak tersedia!\n";
        }
    }while(pilihan != 4);
}