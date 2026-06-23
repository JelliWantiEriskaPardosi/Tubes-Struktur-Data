#include <iostream> //untuk fungsi input dan output seperti printf() untuk menampilkan data dan scanf() untuk menerima input dari pengguna
#include <stdlib.h> //untuk pengelolaan memori secara dinamis, yaitu membuat node baru dengan malloc() dan menghapus node dengan free()
#include <string.h> //untuk operasi pada string seperti menyalin string menggunakan strcpy() dan membandingkan string menggunakan strcmp()
#include <time.h> //untuk mengakses tanggal dan waktu seperti menghitung lama peminjaman atau sisa waktu sebelum buku harus dikembalikan
// STRUKTUR DATA & MENAMBAH BUKU --> AJAANIE MAFAZA SAHILAH
typedef struct Buku{
    char id[20];
    char judul[100];
    char pengarang[100];
    int tahunTerbit;
    char kategori[50];
    char penerbit[100];
    int tersedia;
} Buku;

typedef struct NodeBuku{
    Buku data;
    struct NodeBuku *prev;
    struct NodeBuku *next;
} NodeBuku;

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

// MENAMPILKAN BUKU & SORTING --> JELLI WANTI ERISKA PARDOSI
// sorting  buku berdasarkan judul dari A-Z
void sortingJudulAZ(){

    // Jika data buku kosong
    if(head == NULL){
        return;
    }

    Node *i, *j;

    // Membandingkan setiap judul buku
    for(i = head; i != NULL; i = i->next){

        for(j = i->next; j != NULL; j = j->next){

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
    printf("\nPeminjam berhasil masuk ke daftar tunggu.\n");
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
   printf("\n========================================================\n");
   printf("                    PINJAM BUKU\n");
   printf("========================================================\n");;
    // Meminta pengguna memasukkan data peminjaman
    printf("ID Buku                             : ");
    scanf("%s", data.idBuku);

    printf("Judul Buku                          : ");
    scanf(" %[^\n]", data.judul);

    printf("Nama Peminjam                       : ");
    scanf(" %[^\n]", data.namaPeminjam);

    printf("NIM                                 : ");
    scanf("%s", data.nim);

    printf("Hari                                : ");
    scanf(" %[^\n]", data.hari);

    printf("Tanggal                             :");
    scanf("%d", &data.tanggal);

    printf("Bulan                               : ");
    scanf("%d", &data.bulan);

    printf("Tahun                               : ");
    scanf("%d", &data.tahun);

    // Memasukkan data peminjam ke queue
    enqueue(Q, data);
}
// Fungsi untuk mengembalikan buku
// Peminjam paling depan akan dikeluarkan dari queue
void kembalikanBuku(Queue *Q){
    // Mengecek apakah queue masih kosong
    if(isEmpty(*Q)){
        printf("\nDaftar tunggu kosong.\n");
        return;
    }

    printf("\n=======================================================\n");
    printf("                    PENGEMBALIAN BUKU\n");
    printf("==========================================================\n");

    // Menampilkan data peminjam yang mengembalikan buku
    printf("ID Buku             : %s\n",Q->first->data.idBuku);
    printf("Judul Buku          : %s\n",Q->first->data.judul);
    printf("Nama Peminjam       : %s\n",Q->first->data.namaPeminjam);
    printf("NIM                 : %s\n",Q->first->data.nim);

    // Menghapus data peminjam dari queue
    dequeue(Q);
    printf("\nBuku berhasil dikembalikan.\n");
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
        printf("\nDaftar tunggu kosong.\n");
        return;
    }
    // Pointer bantu dimulai dari elemen pertama
    bantu = Q.first;
    printf("\n=============================================================================================================\n");
    printf("| No | ID Buku | Judul Buku        | Nama Peminjam         | NIM     | Hari  | Tanggal | Bulan | Tahun |\n");
    printf("=============================================================================================================\n");
    // Menampilkan seluruh isi queue
    while(bantu != NULL){
        printf("| %-2d | %-7s | %-25s | %-21s | %-10s | %-8s | %-7d | %-5d | %-5d |\n", 
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

    printf("=============================================================================================================\n");
    printf("\n");
    printf("========================================================\n");
    printf("            SISA WAKTU PEMINJAMAN\n");
    printf("========================================================\n");

    // Pointer bantu di-reset ke awal queue
    bantu = Q.first;
    // Menelusuri ulang seluruh data untuk menampilkan detail sisa waktu
    while(bantu != NULL){
        printf("\nNama Peminjam : %s\n", bantu->data.namaPeminjam);
        printf("Judul Buku      : %s\n", bantu->data.judul);
    // Memanggil fungsi untuk menghitung sisa waktu peminjaman
    hitungSisaPeminjaman(bantu->data);

    printf("---------------------------------------------------------\n");
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
        printf("Gagal memproses tanggal peminjaman.\n");
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
        printf("Sisa Waktu Peminjaman : %.0f hari lagi\n", selisihHari);
    }
    // Jika selisih hari bernilai 0 atau negatif, berarti peminjam sudah telat mengembalikan buku
    else{
        // // Variabel selisihHari diubah menjadi positif dengan tanda minus (-) di depannya agar jumlah hari terlambat tidak tertulis minus
        printf("Status Peminjaman      : Terlambat %.0f hari\n", -selisihHari);
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
        printf("\n========================================================\n");
        printf("           SISTEM MANAJEMEN PERPUSTAKAAN\n");
        printf("========================================================\n");
        printf("| 1 | Pinjam Buku                                    |\n");
        printf("| 2 | Kembalikan Buku                                |\n");
        printf("| 3 | Lihat Daftar Tunggu                            |\n");
        printf("| 4 | Keluar                                         |\n");
        printf("========================================================\n");

        // Meminta pengguna memilih menu
        printf("Masukkan Pilihan : ");
        scanf("%d",&pilihan);

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
                printf("========================================================\n");
                printf("            SISA WAKTU PEMINJAMAN\n");
                printf("========================================================\n");
                
                // Mengambil data dari antrian paling depan (first)
                DataAntrian dataDepan = daftarTunggu.first->data;
                // Memanggil fungsi
                hitungSisaPeminjaman(dataDepan);
                printf("=========================================================\n");
            }
            tampilDaftarTunggu(daftarTunggu);
            break;
            // Keluar dari program 
            case 4:
                 printf("\n=====================================================\n");
                 printf(" Terima kasih telah menggunakan\n");
                 printf(" Sistem Manajemen Perpustakaan.\n");
                 printf(" Program selesai.\n");
                 printf("=====================================================\n");
                 break; 

            // Jika pilihan tidak tersedia
            default:
                printf("\nPilihan tidak tersedia!\n");
        }
    }while(pilihan != 4);
}