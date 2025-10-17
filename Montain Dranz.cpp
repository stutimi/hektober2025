#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // Untuk std::find
#include <limits>    // Untuk std::numeric_limits

// --- Status Global Game ---
// Variabel ini akan melacak progres pemain di seluruh permainan.
std::vector<std::string> inventaris;
bool punyaPeta = false;
bool batuCahayaDitemukan = false;
bool tekaTekiTerpecahkan = false;
bool penjagaKunoTerpecahkan = false;
int lokasiSekarang = 0; // 0: Kaki Gunung, 1: Hutan Kabut, 2: Goa Misteri, 3: Puncak Berangin, 4: Kuil Kuno

// --- Fungsi Bantu ---

// Fungsi untuk membersihkan layar (cross-platform)
void bersihkanLayar() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Fungsi untuk menampilkan garis pemisah
void garisPemisah() {
    std::cout << "\n--------------------------------------------------\n";
}

// Fungsi untuk mendapatkan input pemain dan mengubahnya menjadi huruf kecil
std::string dapatkanInput() {
    std::cout << "\n> ";
    std::string input;
    std::getline(std::cin, input);
    for (char &c : input) {
        c = tolower(c);
    }
    return input;
}

// Fungsi untuk memeriksa apakah item ada di inventaris
bool adaDiInventaris(const std::string& item) {
    return std::find(inventaris.begin(), inventaris.end(), item) != inventaris.end();
}

// Fungsi untuk menambahkan item ke inventaris
void tambahKeInventaris(const std::string& item) {
    inventaris.push_back(item);
    std::cout << "Kamu mendapatkan: " << item << "!\n";
}

// Fungsi untuk menampilkan inventaris
void tampilkanInventaris() {
    if (inventaris.empty()) {
        std::cout << "Inventarismu kosong.\n";
    } else {
        std::cout << "Inventarismu: ";
        for (size_t i = 0; i < inventaris.size(); ++i) {
            std::cout << inventaris[i];
            if (i < inventaris.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << ".\n";
    }
}

// Fungsi untuk menjeda layar
void jeda() {
    std::cout << "(Tekan Enter untuk melanjutkan...)";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Membersihkan buffer
    std::cin.get();
}

// --- Deklarasi Fungsi Lokasi ---
void kakiGunung();
void hutanKabut();
void goaMisteri();
void puncakBerangin();
void kuilKuno();


// --- Implementasi Fungsi Lokasi ---

// LOKASI 0: Kaki Gunung Gema
void kakiGunung() {
    bersihkanLayar();
    garisPemisah();
    std::cout << "Kamu berada di kaki Gunung Gema. Udara dingin menyambutmu.\n";
    std::cout << "Ada jalan setapak samar ke utara, mengarah ke hutan lebat.\n";
    if (!punyaPeta) {
        std::cout << "Di dekat semak-semak, kamu melihat sesuatu yang berkilau.\n";
    }
    garisPemisah();
    std::cout << "Apa yang akan kamu lakukan?\n";
    std::cout << "[1] Ikuti jalan setapak ke utara\n";
    if (!punyaPeta) {
        std::cout << "[2] Periksa kilauan di semak-semak\n";
    }
    std::cout << "[3] Periksa inventaris\n";
    std::cout << "[4] Menyerah dan kembali pulang (Keluar)\n";

    std::string pilihan = dapatkanInput();

    if (pilihan == "1" || pilihan == "utara") {
        std::cout << "\nKamu melangkah maju, memasuki hutan yang semakin gelap.\n";
        lokasiSekarang = 1;
    } else if ((pilihan == "2" || pilihan == "periksa kilauan") && !punyaPeta) {
        std::cout << "\nKamu menemukan sebuah peta kuno yang digulung rapi! Mungkin ini akan membantumu di gunung.\n";
        punyaPeta = true;
        tambahKeInventaris("Peta Kuno");
        jeda();
    } else if (pilihan == "3" || pilihan == "inventaris") {
        tampilkanInventaris();
        jeda();
    }
     else if (pilihan == "4" || pilihan == "menyerah") {
        std::cout << "\nPetualangan ini terlalu menakutkan. Kamu memutuskan untuk kembali ke peradaban.\n";
        std::cout << "--- GAME OVER ---\n";
        lokasiSekarang = -1;
    } else {
        std::cout << "\nPilihan tidak valid. Coba lagi.\n";
        jeda();
    }
}

// LOKASI 1: Hutan Kabut
void hutanKabut() {
    bersihkanLayar();
    garisPemisah();
    std::cout << "Kabut tebal menyelimuti hutan ini. Sangat sulit melihat.\n";
    std::cout << "Kamu mendengar suara aneh dari kedalaman hutan.\n";
    std::cout << "Ada sebuah gua gelap di barat yang tampak menjanjikan.\n";
    std::cout << "Kembali ke selatan akan membawamu ke kaki gunung.\n";
    garisPemisah();
    std::cout << "Apa yang akan kamu lakukan?\n";
    std::cout << "[1] Masuk ke gua gelap (barat)\n";
    std::cout << "[2] Kembali ke kaki gunung (selatan)\n";
    std::cout << "[3] Periksa inventaris\n";

    std::string pilihan = dapatkanInput();

    if (pilihan == "1" || pilihan == "barat") {
        std::cout << "\nKamu memasuki gua. Kegelapan pekat menyelimutimu.\n";
        lokasiSekarang = 2;
    } else if (pilihan == "2" || pilihan == "selatan") {
        std::cout << "\nKamu mundur dari kabut, kembali ke jalan setapak.\n";
        lokasiSekarang = 0;
    } else if (pilihan == "3" || pilihan == "inventaris") {
        tampilkanInventaris();
        jeda();
    } else {
        std::cout << "\nPilihan tidak valid. Coba lagi.\n";
        jeda();
    }
}

// LOKASI 2: Goa Misteri
void goaMisteri() {
    bersihkanLayar();
    garisPemisah();
    std::cout << "Di dalam Goa Misteri, kelembaban terasa dingin. Suara tetesan air menggema.\n";
    if (!batuCahayaDitemukan) {
        std::cout << "Di pojok, sebuah batu aneh berkilau redup.\n";
    }
    if (batuCahayaDitemukan && !tekaTekiTerpecahkan) {
        std::cout << "Ada sebuah altar kuno dengan ukiran simbol-simbol aneh.\n";
    }
    std::cout << "Sebuah lorong sempit ke utara mungkin mengarah lebih dalam ke gunung.\n";
    std::cout << "Jalan kembali ke timur akan membawamu keluar dari gua.\n";
    garisPemisah();
    std::cout << "Apa yang akan kamu lakukan?\n";
    if (!batuCahayaDitemukan) {
        std::cout << "[1] Ambil batu yang berkilau\n";
    }
    if (batuCahayaDitemukan && !tekaTekiTerpecahkan) {
        std::cout << "[2] Periksa altar kuno\n";
    }
    std::cout << "[3] Lanjutkan ke lorong utara\n";
    std::cout << "[4] Kembali ke hutan (timur)\n";
    std::cout << "[5] Periksa inventaris\n";

    std::string pilihan = dapatkanInput();

    if ((pilihan == "1" || pilihan == "ambil batu") && !batuCahayaDitemukan) {
        std::cout << "\nKamu mengambil 'Batu Cahaya'. Batu ini mengeluarkan cahaya lembut, mungkin berguna!\n";
        batuCahayaDitemukan = true;
        tambahKeInventaris("Batu Cahaya");
        jeda();
    } else if ((pilihan == "2" || pilihan == "periksa altar") && batuCahayaDitemukan && !tekaTekiTerpecahkan) {
        std::cout << "\nAltar itu memiliki celah berbentuk seperti Batu Cahaya. Haruskah kamu menaruhnya?\n";
        std::cout << "[ya/tidak]?\n";
        std::string jawab = dapatkanInput();
        if (jawab == "ya") {
            std::cout << "\nKamu menempatkan Batu Cahaya di altar. Simbol-simbol menyala, dan sebuah pintu rahasia terbuka di dinding!\n";
            std::cout << "Teka-teki Goa Misteri terpecahkan!\n";
            tekaTekiTerpecahkan = true;
            inventaris.erase(std::remove(inventaris.begin(), inventaris.end(), "Batu Cahaya"), inventaris.end());
            std::cout << "(Batu Cahaya telah digunakan)\n";
            jeda();
        } else {
            std::cout << "\nKamu memutuskan untuk tidak menaruhnya dulu.\n";
            jeda();
        }
    } else if (pilihan == "3" || pilihan == "utara") {
        if (tekaTekiTerpecahkan) {
            std::cout << "\nKamu melewati pintu rahasia dan menemukan sebuah tangga yang menuju ke atas gunung.\n";
            lokasiSekarang = 3;
        } else {
            std::cout << "\nLorong ke utara terlalu gelap dan sempit. Kamu tidak bisa melanjutkannya.\n";
            std::cout << "Mungkin ada cara lain untuk membuka jalan?\n";
            jeda();
        }
    } else if (pilihan == "4" || pilihan == "timur") {
        std::cout << "\nKamu keluar dari gua, kembali ke kabut hutan.\n";
        lokasiSekarang = 1;
    } else if (pilihan == "5" || pilihan == "inventaris") {
        tampilkanInventaris();
        jeda();
    } else {
        std::cout << "\nPilihan tidak valid. Coba lagi.\n";
        jeda();
    }
}

// LOKASI 3: Puncak Berangin
void puncakBerangin() {
    bersihkanLayar();
    garisPemisah();
    std::cout << "Kamu telah mencapai Puncak Berangin. Angin menderu kencang.\n";
    std::cout << "Dari sini, kamu bisa melihat seluruh lanskap di bawah. Sebuah kuil kuno terlihat di utara.\n";
    std::cout << "Sebuah jalan menurun kembali ke selatan, ke lorong gua.\n";
    garisPemisah();
    std::cout << "Apa yang akan kamu lakukan?\n";
    std::cout << "[1] Lanjutkan ke utara menuju kuil kuno\n";
    std::cout << "[2] Kembali ke selatan menuju gua\n";
    std::cout << "[3] Periksa inventaris\n";

    std::string pilihan = dapatkanInput();

    if (pilihan == "1" || pilihan == "utara") {
        std::cout << "\nDengan susah payah, kamu berjalan melawan angin menuju kuil.\n";
        lokasiSekarang = 4;
    } else if (pilihan == "2" || pilihan == "selatan") {
        std::cout << "\nKamu memutuskan untuk kembali ke dalam gua yang lebih tenang.\n";
        lokasiSekarang = 2;
    } else if (pilihan == "3" || pilihan == "inventaris") {
        tampilkanInventaris();
        jeda();
    } else {
        std::cout << "\nPilihan tidak valid. Coba lagi.\n";
        jeda();
    }
}

// LOKASI 4: Kuil Kuno
void kuilKuno() {
    bersihkanLayar();
    garisPemisah();
    std::cout << "Kamu memasuki Kuil Kuno. Udara terasa berat, dipenuhi energi kuno.\n";
    std::cout << "Di tengah ruangan, sebuah patung penjaga besar menghalangi jalan menuju permata.\n";
    if (!penjagaKunoTerpecahkan) {
        std::cout << "Mata patung itu menyala, seolah mengamatimu.\n";
        std::cout << "Sebuah ukiran di dasar patung berbunyi: 'Hanya yang melihat masa lalu, akan melihat masa depan.'\n";
    } else {
        std::cout << "Patung penjaga kini diam, jalannya terbuka.\n";
    }
    garisPemisah();
    std::cout << "Apa yang akan kamu lakukan?\n";
    if (!penjagaKunoTerpecahkan) {
        std::cout << "[1] Coba melewati patung (bahaya!)\n";
        std::cout << "[2] Coba pecahkan teka-teki patung (perlu Peta Kuno)\n";
    } else {
        std::cout << "[1] Ambil permata legendaris!\n";
    }
    std::cout << "[3] Kembali ke Puncak Berangin\n";
    std::cout << "[4] Periksa inventaris\n";

    std::string pilihan = dapatkanInput();

    if ((pilihan == "1" || pilihan == "lewat") && !penjagaKunoTerpecahkan) {
        std::cout << "\nKamu mencoba menyelinap melewati patung, tapi ia bergerak cepat!\n";
        std::cout << "Tangan batu raksasanya menghantammu. Kamu terluka parah.\n";
        std::cout << "--- GAME OVER ---\n";
        lokasiSekarang = -1;
    } else if ((pilihan == "2" || pilihan == "pecahkan teka-teki") && !penjagaKunoTerpecahkan) {
        if (adaDiInventaris("Peta Kuno")) {
            std::cout << "\nKamu memeriksa Peta Kuno dengan seksama. Di baliknya, kamu menemukan tulisan tersembunyi yang menjelaskan sejarah kuil.\n";
            std::cout << "Tulisan itu berbicara tentang 'penjaga waktu' dan 'jalur bintang'.\n";
            std::cout << "Tiba-tiba, mata patung berputar, dan tubuhnya bergeser, membuka jalan!\n";
            std::cout << "Kamu berhasil memecahkan teka-teki penjaga kuno!\n";
            penjagaKunoTerpecahkan = true;
            jeda();
        } else {
            std::cout << "\nKamu memikirkan teka-teki itu, tapi tidak ada petunjuk. Kamu merasa ada sesuatu yang kurang.\n";
            jeda();
        }
    } else if ((pilihan == "1" || pilihan == "ambil permata") && penjagaKunoTerpecahkan) {
        std::cout << "\nDi balik patung, sebuah pedestal emas menopang 'Permata Gema' yang bersinar!\n";
        std::cout << "Kamu mengambilnya. Cahayanya menerangi seluruh kuil.\n";
        std::cout << "Kamu telah menemukan permata legendaris! Misi berhasil!\n";
        std::cout << "--- SELAMAT! KAMU MENANG! ---\n";
        lokasiSekarang = -1;
    }
    else if (pilihan == "3" || pilihan == "kembali") {
        lokasiSekarang = 3;
    } else if (pilihan == "4" || pilihan == "inventaris") {
        tampilkanInventaris();
        jeda();
    } else {
        std::cout << "\nPilihan tidak valid. Coba lagi.\n";
        jeda();
    }
}


// --- Fungsi Main (Loop Utama Game) ---
int main() {
    // Memastikan cin.ignore bekerja dengan benar di awal
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    bersihkanLayar();
    std::cout << "=======================================\n";
    std::cout << "||     MISTERI GUNUNG GEMA         ||\n";
    std::cout << "=======================================\n";
    std::cout << "Selamat datang, penjelajah! Legenda Permata Gema menantimu.\n";
    std::cout << "(Tekan Enter untuk memulai...)\n";
    std::cin.get();

    while (lokasiSekarang != -1) {
        switch (lokasiSekarang) {
            case 0:
                kakiGunung();
                break;
            case 1:
                hutanKabut();
                break;
            case 2:
                goaMisteri();
                break;
            case 3:
                puncakBerangin();
                break;
            case 4:
                kuilKuno();
                break;
            default:
                std::cout << "Terjadi kesalahan, lokasi tidak ditemukan.\n";
                lokasiSekarang = -1;
                break;
        }
    }

    std::cout << "\nTerima kasih telah bermain!\n";

    return 0;
}
