#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

struct Mahasiswa {
    char nama[100];
    char nim[15];
    char jurusan[50];
    int tm;
    float ipk;
};

void tambahMhs() {
    system("cls");
    Mahasiswa mhs;
    FILE *file = fopen("MahasiswaData.dat", "ab");
    if (!file) {
        cout << "Gagal membuka file!" << endl;
        return;
    }
    
    cout << "Masukkan Nama: "; cin.ignore(); 
    cin.getline(mhs.nama, 100);
    cout << "Masukkan NIM: "; 
    cin >> mhs.nim;
    cout << "Masukkan Jurusan: "; cin.ignore(); 
    cin.getline(mhs.jurusan, 50);
    cout << "Masukkan Tahun Masuk: "; 
    cin >> mhs.tm;
    mhs.ipk = 0.0;
    
    fwrite(&mhs, sizeof(Mahasiswa), 1, file);
    fclose(file);
    cout << "Mahasiswa berhasil ditambahkan!" << endl;
    system("pause");
}

void quickSort(Mahasiswa arr[], int low, int high) {
    if (low < high) {
        Mahasiswa pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (strcmp(arr[j].nim, pivot.nim) < 0) {
                i++;
                Mahasiswa temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        Mahasiswa temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        int pi = i + 1;
        
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void tampilMhs() {
    system("cls");
    FILE *file = fopen("MahasiswaData.dat", "rb");
    if (!file) {
        cout << "Gagal membuka file!" << endl;
        return;
    }
    
    Mahasiswa data[100];
    int count = 0;
    while (fread(&data[count], sizeof(Mahasiswa), 1, file)) {
        count++;
    }
    fclose(file);
    
    quickSort(data, 0, count - 1);
    for (int i = 0; i < count; i++) {
        cout << "Data ke- " << i+1 << "\nNama: " << data[i].nama << "\nNIM: " << data[i].nim << "\nJurusan: " << data[i].jurusan
        << "\nTahun Masuk: " << data[i].tm << "\nIPK: " << data[i].ipk << "\n";
        cout << endl;
    }
    system("pause");
}

int binarySearch(Mahasiswa arr[], int left, int right, const char* nim) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(arr[mid].nim, nim);
        if (cmp == 0) return mid;
        else if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

void cariNIM() {
    system("cls");
    char crnim[15];
    cout << "Masukkan NIM: ";
    cin >> crnim;

    FILE *file = fopen("MahasiswaData.dat", "rb");
    if (!file) {
        cout << "Gagal membuka file!" << endl;
        return;
    }
    
    Mahasiswa data[100];
    int count = 0;
    while (fread(&data[count], sizeof(Mahasiswa), 1, file)) {
        count++;
    }
    fclose(file);
    
    quickSort(data, 0, count - 1);
    int hasil = binarySearch(data, 0, count - 1, crnim);
    if (hasil != -1) {
        Mahasiswa mhs = data[hasil];
        cout << "Nama: " << mhs.nama << "\nNIM: " << mhs.nim << "\nJurusan: " << mhs.jurusan
        << "\nTahun Masuk: " << mhs.tm << "\nIPK: " << mhs.ipk << "\n";
    } else {
        cout << "Mahasiswa dengan NIM " << crnim << " tidak ditemukan!" << endl;
    }
    system("pause");
}

void cariJurusan() {
    system("cls");
    char crjur[50];
    cout << "Masukkan jurusan: ";
    cin.ignore();
    cin.getline(crjur, 50);

    FILE *file = fopen("MahasiswaData.dat", "rb");
    if (!file) {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    Mahasiswa mhs;
    bool find = false;
    cout << "\n>> Mahasiswa dari Jurusan " << crjur << " <<\n";
    while (fread(&mhs, sizeof(Mahasiswa), 1, file)) {
        if (strcmp(mhs.jurusan, crjur) == 0) {
            cout << "Nama: " << mhs.nama << "\nNIM: " << mhs.nim
            << "\nTahun Masuk: " << mhs.tm << "\nIPK: " << mhs.ipk << "\n\n";
            find = true;
        }
    }
    fclose(file);

    if (!find) {
        cout << "Mahasiswa dengan jurusan " << crjur << " tidak ditemukan!" << endl;
    }
    system("pause");
}

void updateIPK() {
    system("cls");
    char crnim[15];
    cout << "Masukkan NIM mahasiswa yang ingin diperbarui IPK-nya: ";
    cin >> crnim;

    FILE *file = fopen("MahasiswaData.dat", "rb+");
    if (!file) {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    Mahasiswa mhs;
    bool find = false;
    while (fread(&mhs, sizeof(Mahasiswa), 1, file)) {
        if (strcmp(mhs.nim, crnim) == 0) {
            cout << "Nama: " << mhs.nama << "\nNIM: " << mhs.nim << "\nJurusan: " << mhs.jurusan
            << "\nTahun Masuk: " << mhs.tm << "\nIPK: " << mhs.ipk << "\n";
            cout << "Masukkan IPK baru (0.0 - 4.0): ";
            float inputipk;
            cin >> inputipk;
            if (inputipk < 0.0 || inputipk > 4.0) {
                cout << "IPK tidak valid!" << endl;
                fclose(file);
                return;
            }
            mhs.ipk = inputipk;
            fseek(file, -sizeof(Mahasiswa), SEEK_CUR);
            fwrite(&mhs, sizeof(Mahasiswa), 1, file);
            cout << "IPK mahasiswa dengan NIM " << crnim << " berhasil diperbarui!" << endl;
            find = true;
            break;
        }
    }
    fclose(file);

    if (!find) {
        cout << "Mahasiswa tidak ditemukan!" << endl;
    }
    system("pause");
}

void hapusMhs() {
    system("cls");
    char crnim[15];
    cout << "Masukkan NIM mahasiswa yang ingin dihapus: ";
    cin >> crnim;

    FILE *file = fopen("MahasiswaData.dat", "rb");
    FILE *tempFile = fopen("Temp.dat", "wb");

    if (!file || !tempFile) {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    Mahasiswa mhs;
    bool find = false;
    while (fread(&mhs, sizeof(Mahasiswa), 1, file)) {
        if (strcmp(mhs.nim, crnim) == 0) {
            find = true;
        } else {
            fwrite(&mhs, sizeof(Mahasiswa), 1, tempFile);
        }
    }
    fclose(file);
    fclose(tempFile);

    remove("MahasiswaData.dat");
    rename("Temp.dat", "MahasiswaData.dat");

    if (find) {
        cout << "Mahasiswa dengan NIM " << crnim << " berhasil dihapus!" << endl;
    } else {
        cout << "Mahasiswa tidak ditemukan!" << endl;
    }
    system("pause");
}

void exitPrg() {
    system("cls");
    cout << "Terima kasih telah menggunakan SmartCampus++! Semoga sukses dalam studi Anda!" << endl;
    exit(0);
}

int main() {
    system("cls");
    int pil;
    do {
        system("cls");
        cout << "\n=== Menu SmartCampus++ ===\n";
        cout << "1. Tambah Data Mahasiswa\n";
        cout << "2. Tampilkan Semua Data Mahasiswa\n";
        cout << "3. Cari Mahasiswa Berdasarkan Jurusan\n";
        cout << "4. Cari Mahasiswa Berdasarkan NIM\n";
        cout << "5. Perbarui IPK Mahasiswa\n";
        cout << "6. Hapus Data Mahasiswa\n";
        cout << "7. Keluar\n";
        cout << "Pilih(1-7): ";
        cin >> pil;
        switch (pil) {
            case 1: tambahMhs(); break;
            case 2: tampilMhs(); break;
            case 3: cariJurusan(); break;
            case 4: cariNIM(); break;
            case 5: updateIPK(); break;
            case 6: hapusMhs(); break;
            case 7: exitPrg(); break;
            default: cout << "Pilihan tidak valid!" << endl;
        }
    } while (pil != 7);
    return 0;
}