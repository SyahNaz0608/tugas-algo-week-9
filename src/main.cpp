#include <iostream>
#include <string>
using namespace std;

// ===================== KONSTANTA =====================
const int MOTOR = 1;
const int MOBIL = 2;

const int NON_MEMBER = 1;
const int SILVER = 2;
const int GOLD = 3;

const int TUNAI = 1;
const int QRIS = 2;

const int BATAS_DURASI_PANJANG = 8; // jam
const int BIAYA_TAMBAHAN_PANJANG = 5000;
const int BATAS_POTONGAN = 30000;
const int POTONGAN_TAMBAHAN = 2000;

// ===================== FUNGSI BANTU =====================

// Mengubah angka menjadi format rupiah, contoh: 12000 -> "Rp12.000"
string formatRupiah(int angka) {
  string s = to_string(angka);
  string hasil = "";
  int hitung = 0;
  for (int i = (int)s.length() - 1; i >= 0; i--) {
    hasil = s[i] + hasil;
    hitung++;
    if (hitung % 3 == 0 && i != 0) {
      hasil = "." + hasil;
    }
  }
  return "Rp" + hasil;
}

string namaKendaraan(int jenis) { return (jenis == MOTOR) ? "Motor" : "Mobil"; }

string namaMember(int member) {
  if (member == GOLD)
    return "Member Gold";
  if (member == SILVER)
    return "Member Silver";
  return "Non-Member";
}

string namaMetode(int metode) { return (metode == TUNAI) ? "Tunai" : "QRIS"; }

// ===================== FUNGSI UTAMA (WAJIB) =====================

// 1. Menghitung tarif berdasarkan kendaraan dan durasi
//    Motor: jam pertama 3.000, berikutnya 2.000/jam
//    Mobil: jam pertama 5.000, berikutnya 3.000/jam
int hitungTarifParkir(int jenisKendaraan, int durasi) {
  int tarifJamPertama, tarifJamBerikutnya;

  if (jenisKendaraan == MOTOR) {
    tarifJamPertama = 3000;
    tarifJamBerikutnya = 2000;
  } else {
    tarifJamPertama = 5000;
    tarifJamBerikutnya = 3000;
  }

  return tarifJamPertama + (durasi - 1) * tarifJamBerikutnya;
}

// 2. Menghitung diskon berdasarkan keanggotaan
//    Gold 20%, Silver 10%, Non-Member 0%
int hitungDiskon(int biaya, int jenisMember) {
  int persen = 0;

  if (jenisMember == GOLD) {
    persen = 20;
  } else if (jenisMember == SILVER) {
    persen = 10;
  }

  return biaya * persen / 100;
}

// 3. Menghitung biaya tambahan jika parkir lebih dari 8 jam
int hitungBiayaTambahan(int durasi) {
  if (durasi > BATAS_DURASI_PANJANG) {
    return BIAYA_TAMBAHAN_PANJANG;
  }
  return 0;
}

// Potongan tambahan Rp2.000 jika total setelah diskon minimal Rp30.000
int hitungPotonganTambahan(int totalSetelahDiskon) {
  if (totalSetelahDiskon >= BATAS_POTONGAN) {
    return POTONGAN_TAMBAHAN;
  }
  return 0;
}

// 4. Menghitung total biaya akhir (tidak boleh negatif)
int hitungTotalBayar(int biayaKotor, int diskon, int potonganTambahan) {
  int total = biayaKotor - diskon - potonganTambahan;
  if (total < 0) {
    total = 0;
  }
  return total;
}

// 5. Menampilkan rincian transaksi
void tampilkanStruk(int jenisKendaraan, int jenisMember, int durasi,
                    int tarifParkir, int biayaTambahan, int diskon,
                    int potonganTambahan, int totalBayar, int metode,
                    int uangDibayar, bool berhasil) {

  cout << "\n==================================\n";
  cout << "        STRUK PARKIR PUSAT\n";
  cout << "          PERBELANJAAN\n";
  cout << "==================================\n";
  cout << "Kendaraan        : " << namaKendaraan(jenisKendaraan) << "\n";
  cout << "Keanggotaan      : " << namaMember(jenisMember) << "\n";
  cout << "Durasi           : " << durasi << " jam\n";
  cout << "----------------------------------\n";
  cout << "Tarif parkir     : " << formatRupiah(tarifParkir) << "\n";
  cout << "Biaya tambahan   : " << formatRupiah(biayaTambahan) << "\n";
  cout << "Diskon           : -" << formatRupiah(diskon) << "\n";
  cout << "Potongan tambahan: -" << formatRupiah(potonganTambahan) << "\n";
  cout << "----------------------------------\n";
  cout << "TOTAL BAYAR      : " << formatRupiah(totalBayar) << "\n";
  cout << "Metode bayar     : " << namaMetode(metode) << "\n";

  if (metode == TUNAI) {
    cout << "Uang dibayarkan  : " << formatRupiah(uangDibayar) << "\n";
    if (berhasil) {
      cout << "Kembalian        : " << formatRupiah(uangDibayar - totalBayar)
           << "\n";
    } else {
      cout << "Kekurangan       : " << formatRupiah(totalBayar - uangDibayar)
           << "\n";
    }
  }

  cout << "----------------------------------\n";
  if (berhasil) {
    cout << "STATUS           : TRANSAKSI BERHASIL\n";
  } else {
    cout << "STATUS           : TRANSAKSI GAGAL (uang kurang)\n";
  }
  cout << "==================================\n";
}

// ===================== PROGRAM UTAMA =====================
int main() {
  int jenisKendaraan, jenisMember, durasi, metode;
  int uangDibayar = 0;

  cout << "=== SISTEM PARKIR OTOMATIS ===\n\n";

  // Input jenis kendaraan (validasi)
  do {
    cout << "Jenis kendaraan (1. Motor / 2. Mobil): ";
    cin >> jenisKendaraan;
    if (jenisKendaraan != MOTOR && jenisKendaraan != MOBIL) {
      cout << "Pilihan tidak valid, coba lagi.\n";
    }
  } while (jenisKendaraan != MOTOR && jenisKendaraan != MOBIL);

  // Input durasi (validasi minimal 1 jam)
  do {
    cout << "Durasi parkir (jam, minimal 1): ";
    cin >> durasi;
    if (durasi < 1) {
      cout << "Durasi harus minimal 1 jam.\n";
    }
  } while (durasi < 1);

  // Input keanggotaan (validasi)
  do {
    cout << "Keanggotaan (1. Non-Member / 2. Silver / 3. Gold): ";
    cin >> jenisMember;
    if (jenisMember < NON_MEMBER || jenisMember > GOLD) {
      cout << "Pilihan tidak valid, coba lagi.\n";
    }
  } while (jenisMember < NON_MEMBER || jenisMember > GOLD);

  // Input metode pembayaran (validasi)
  do {
    cout << "Metode pembayaran (1. Tunai / 2. QRIS): ";
    cin >> metode;
    if (metode != TUNAI && metode != QRIS) {
      cout << "Pilihan tidak valid, coba lagi.\n";
    }
  } while (metode != TUNAI && metode != QRIS);

  // ----- Proses perhitungan -----
  int tarifParkir = hitungTarifParkir(jenisKendaraan, durasi);
  int biayaTambahan = hitungBiayaTambahan(durasi);
  int biayaKotor = tarifParkir + biayaTambahan;
  int diskon = hitungDiskon(biayaKotor, jenisMember);
  int totalSetelahDiskon = biayaKotor - diskon;
  int potonganTambahan = hitungPotonganTambahan(totalSetelahDiskon);
  int totalBayar = hitungTotalBayar(biayaKotor, diskon, potonganTambahan);

  cout << "\nTotal yang harus dibayar: " << formatRupiah(totalBayar) << "\n";

  // ----- Proses pembayaran -----
  bool berhasil = true;

  if (metode == TUNAI) {
    cout << "Masukkan uang pembayaran: Rp";
    cin >> uangDibayar;

    if (uangDibayar < totalBayar) {
      berhasil = false;
    }
  }
  // QRIS dianggap selalu sesuai tagihan

  tampilkanStruk(jenisKendaraan, jenisMember, durasi, tarifParkir,
                 biayaTambahan, diskon, potonganTambahan, totalBayar, metode,
                 uangDibayar, berhasil);

  return 0;
}