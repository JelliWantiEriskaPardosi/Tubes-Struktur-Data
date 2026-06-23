#include <iostream> //untuk fungsi input dan output seperti printf() untuk menampilkan data dan scanf() untuk menerima input dari pengguna
#include <stdlib.h> //untuk pengelolaan memori secara dinamis, yaitu membuat node baru dengan malloc() dan menghapus node dengan free()
#include <string.h> //untuk operasi pada string seperti menyalin string menggunakan strcpy() dan membandingkan string menggunakan strcmp()
#include <time.h> //untuk mengakses tanggal dan waktu seperti menghitung lama peminjaman atau sisa waktu sebelum buku harus dikembalikan
using namespace std;
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
    char idBuku[20];
    char judul[100];
    char namaPeminjam[100];
    char nim[20];
     char hari[20];

    // Tanggal saat melakukan peminjaman 
    int bulan;
    int tahun;
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

// HAPUS & MENCARI BUKU --> CHRISTINNA BATA

// MENAMPILKAN BUKU & SORTING -- JELLI PARDOSI
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

    cout << "\n====================================================================================================\n";
    cout << "ID\tJudul\t\tPengarang\tKategori\tStatus\n";
    cout << "====================================================================================================\n";

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
    printf("| No | ID Buku | Judul Buku                | Nama Peminjam         | NIM        | Hari   | Bulan | Tahun |\n");
    printf("=============================================================================================================\n");
    // Menampilkan seluruh isi queue
    while(bantu != NULL){
        printf("| %-2d | %-7s | %-25s | %-21s | %-10s | %-8s | %-5d | %-5d |\n", 
                no,
                bantu->data.idBuku,
                bantu->data.judul,
                bantu->data.namaPeminjam,
                bantu->data.nim,
                bantu->data.hari,
                bantu->data.bulan,
                bantu->data.tahun);
        // Berpisah ke node berikutnya
        bantu = bantu->next;
        // Menambah nomor urut
        no++;
    }

    printf("=============================================================================================================\n");
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
                printf("\nPilihan tidak valid!\n");
        }
    }while(pilihan != 4);
}