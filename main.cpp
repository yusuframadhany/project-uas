#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

int main() {
    int pilihan;
    int id;
    string namaAlat;
    int jumlahAlat;
    string kondisiAlat;
    string lokasiAlat;

    // Loop utama program
    while (true) {
        cout << "============================" << endl;
        cout << "\t    MENU" << endl;
        cout << "============================" << endl;
        cout << "1. Daftar Data Alat" << endl;
        cout << "2. Tambah Data Alat" << endl;
        cout << "3. Perbarui Data Alat" << endl;
        cout << "4. Hapus Data Alat" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilih Nomor : ";
        cin >> pilihan;
        cin.ignore();  // Mengabaikan newline karakter yang tertinggal setelah pilihan

        // Pilihan untuk Daftar Data Alat
        if (pilihan == 1) {
            ifstream file("data.json");
            json dataArray;

            if (file.is_open()) {
                // Membaca data dari file JSON
                file >> dataArray;
                file.close();

                // Menampilkan header tabel
                cout << "------------------------------------------------------------" << endl;
                cout << "| " 
                    << setw(5) << left << "ID" 
                    << "| " << setw(15) << left << "Nama Alat" 
                    << "| " << setw(12) << left << "Jumlah Alat"
                    << "| " << setw(12) << left << "Kondisi" 
                    << "| " << setw(12) << left << "Lokasi" 
                    << "|" << endl;
                cout << "------------------------------------------------------------" << endl;

                // Menampilkan data dengan ID yang bertambah otomatis
                int id = 1;  // ID mulai dari 1
                for (const auto& item : dataArray) {
                    cout << "| " 
                        << setw(5) << left << id++  // Menampilkan ID dan increment
                        << "| " << setw(15) << left << item["nama"].get<string>() 
                        << "| " << setw(12) << left << item["jumlahAlat"].get<int>()
                        << "| " << setw(12) << left << item["kondisiAlat"].get<string>()
                        << "| " << setw(12) << left << item["lokasiAlat"].get<string>()
                        << "|" << endl;
                }

                cout << "------------------------------------------------------------" << endl;
            } else {
                cerr << "Gagal membuka file JSON." << endl;
            }
        }

        // Pilihan untuk Tambah Data Alat
        else if (pilihan == 2) {
            cout << "\n============================" << endl;
            cout << "      INPUT ALAT MEDIS" << endl;
            cout << "============================" << endl;

            cout << "Nama alat : ";
            getline(cin, namaAlat);  // Menggunakan getline untuk menerima lebih dari satu kata
            cout << "Jumlah alat : ";
            cin >> jumlahAlat;
            cin.ignore();  // Mengabaikan newline karakter setelah input jumlahAlat

            cout << "Kondisi alat : ";
            getline(cin, kondisiAlat);  // Menggunakan getline untuk menerima lebih dari satu kata

            cout << "Lokasi alat : ";
            getline(cin, lokasiAlat);  // Menggunakan getline untuk menerima lebih dari satu kata

            // Membaca data JSON yang sudah ada
            ifstream file("data.json");
            json dataArray;

            if (file.is_open()) {
                file >> dataArray;  // Membaca array JSON dari file
                file.close();
            } else {
                // Jika file tidak ada, inisialisasi array kosong
                cout << "File tidak ditemukan, membuat file baru." << endl;
                dataArray = json::array();  // Membuat array kosong jika file tidak ada
            }

            // Membuat objek JSON untuk data alat
            json data;
            data["nama"] = namaAlat;
            data["jumlahAlat"] = jumlahAlat;
            data["kondisiAlat"] = kondisiAlat;
            data["lokasiAlat"] = lokasiAlat;

            // Menambahkan data baru ke dalam array
            dataArray.push_back(data);

            // Menulis data yang diperbarui ke file JSON
            ofstream fileOut("data.json");
            if (fileOut.is_open()) {
                // Menyimpan data array JSON ke file dengan indentasi 4 spasi
                fileOut << dataArray.dump(4) << endl;
                fileOut.close();
                cout << "Data berhasil dimasukkan ke file JSON." << endl;
            } else {
                cerr << "Gagal membuka file JSON untuk menulis." << endl;
            }
        }

        // Pilihan untuk Perbarui Data Alat
        else if (pilihan == 3) {
            cout << "\n============================" << endl;
            cout << "      PERBARUI ALAT MEDIS" << endl;
            cout << "============================" << endl;
            cout << "Masukkan ID alat yang ingin diperbarui: ";
            cin >> id;
            cin.ignore();  // Mengabaikan newline karakter setelah ID

            // Membaca data JSON yang sudah ada
            ifstream file("data.json");
            json dataArray;

            if (file.is_open()) {
                file >> dataArray;  // Membaca array JSON dari file
                file.close();

                // Memastikan ID yang dimasukkan ada dalam data
                if (id > 0 && id <= dataArray.size()) {
                    // Memperbarui data berdasarkan ID
                    cout << "Nama alat : ";
                    getline(cin, namaAlat);  // Menggunakan getline untuk menerima lebih dari satu kata

                    cout << "Jumlah alat : ";
                    cin >> jumlahAlat;
                    cin.ignore();  // Mengabaikan newline karakter setelah input jumlahAlat

                    cout << "Kondisi alat : ";
                    getline(cin, kondisiAlat);  // Menggunakan getline untuk menerima lebih dari satu kata

                    cout << "Lokasi alat : ";
                    getline(cin, lokasiAlat);  // Menggunakan getline untuk menerima lebih dari satu kata

                    dataArray[id - 1]["nama"] = namaAlat;
                    dataArray[id - 1]["jumlahAlat"] = jumlahAlat;
                    dataArray[id - 1]["kondisiAlat"] = kondisiAlat;
                    dataArray[id - 1]["lokasiAlat"] = lokasiAlat;

                    // Menyimpan data yang telah diperbarui ke file JSON
                    ofstream fileOut("data.json");
                    if (fileOut.is_open()) {
                        fileOut << dataArray.dump(4) << endl;
                        fileOut.close();
                        cout << "Data alat berhasil diperbarui." << endl;
                    } else {
                        cerr << "Gagal membuka file JSON untuk menulis." << endl;
                    }
                } else {
                    cout << "ID tidak valid!" << endl;
                }
            } else {
                cerr << "Gagal membuka file JSON." << endl;
            }
        }

        // Pilihan untuk Hapus Data Alat
        else if (pilihan == 4) {
            cout << "\n============================" << endl;
            cout << "      HAPUS ALAT MEDIS" << endl;
            cout << "============================" << endl;
            cout << "Masukkan ID alat yang ingin dihapus: ";
            cin >> id;
            cin.ignore();  // Mengabaikan newline karakter setelah ID

            // Membaca data JSON yang sudah ada
            ifstream file("data.json");
            json dataArray;

            if (file.is_open()) {
                file >> dataArray;  // Membaca array JSON dari file
                file.close();

                // Memastikan ID yang dimasukkan ada dalam data
                if (id > 0 && id <= dataArray.size()) {
                    // Menghapus data berdasarkan ID
                    dataArray.erase(dataArray.begin() + (id - 1));

                    // Menyimpan data yang telah dihapus ke file JSON
                    ofstream fileOut("data.json");
                    if (fileOut.is_open()) {
                        fileOut << dataArray.dump(4) << endl;
                        fileOut.close();
                        cout << "Data alat berhasil dihapus." << endl;
                    } else {
                        cerr << "Gagal membuka file JSON untuk menulis." << endl;
                    }
                } else {
                    cout << "ID tidak valid!" << endl;
                }
            } else {
                cerr << "Gagal membuka file JSON." << endl;
            }
        }

        // Pilihan untuk keluar dari program
        else if (pilihan == 5) {
            cout << "Terima kasih telah menggunakan program ini!" << endl;
            break;  // Keluar dari loop dan program
        }

        // Pilihan tidak valid
        else {
            cout << "Pilihan tidak valid! Silakan pilih menu yang benar." << endl;
        }
    }

    return 0;
}
