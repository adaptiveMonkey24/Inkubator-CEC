## Project Inkubator (IoT) - Sistem Otomasi Industri (ELK3271)

Controll Engineering Community (CEC) Batch of 2024

Team :
1. Imanuel Stefanus Pesak (Programming)
2. Divine Fillio Moses Kaligis (Programming)
3. Injilli Virginia Ndruru (Web Developer)
4. Maria C. Yohanesia Kalase (Electrical)
5. Yohanes Clauss Rais (Mechanical)
6. Vanesya Angely Lumintang (Management)
7. Moh. Fathirrahman Binol (Management)
8. Tiara Maria Carbelita Tioho (Documentation & Report)

Supervisor :
1. Jeremy D. I. Daud, ST.
2. Ekaralan Maitulung

---

# 5-Layer Automated Egg Incubator System with PID Dimming Control & Smart Airflow

Sistem inkubator telur otomatis berbasis mikrokontroler dengan 5 tingkat (*layer*) rak penetasan. Dilengkapi dengan pemantauan suhu dan kelembapan presisi tinggi menggunakan sensor DHT22, pemanas lampu pijar berdaya variabel via kontroler PID (*Proportional-Integral-Derivative*) untuk pemanasan stabil, serta sistem sirkulasi udara ganda (*exhaust fan* bawah untuk *inhale* dan atas untuk *exhale*).

![Gambar Tidak Ditemukan](/Design/Design.png)

---

## Fitur Utama
* **5-Layer Independent Capacity:** Desain bertingkat untuk memaksimalkan kapasitas penetasan dalam satu unit boks.
* **Sensor Presisi Tinggi (DHT22):** Membaca parameter suhu dan kelembapan secara akurat di ruang inkubator.
* **PID Automatic Dimming Control:** Mengatur intensitas cahaya lampu pijar secara halus menggunakan modul *AC dimmer* berbasis *zero-crossing interrupt* untuk menjaga stabilitas suhu tanpa fluktuasi ekstrem.
* **Smart Exhaust & Inhale System:** Kipas bawah (*inhale*) menyuplai udara segar, sementara kipas atas/atap (*exhale*) membuang kelebihan panas saat suhu melewati ambang batas maksimal (*threshold*).
* **Serial & Display Monitoring:** Antarmuka pemantauan data secara *real-time*.

---

## Spesifikasi Perangkat Keras
* **Mikrokontroler:** ESP32 / STM32 / Arduino (sesuaikan dengan unit Anda)
* **Sensor Suhu/Kelembapan:** DHT22 (AM2302)
* **Elemen Pemanas:** Lampu Pijar dengan Modul *AC Dimmer* (5 Channel / Triac Dimmer)
* **Aktuator Kipas:** 
  * Kipas *Inhale* (Bawah): Sirkulasi udara masuk
  * Kipas *Exhale* (Atas/Atap): Pembuangan panas berlebih
* **Catu Daya:** PSU 5V & Jalur AC 220V (dengan isolasi optocoupler yang aman)

---

##  PID Control & Airflow Logic

### 1. Kontrol Pemanas (PID Dimming)
Algoritma PID membaca *error* antara suhu target ($Setpoint$) dan suhu aktual dari sensor ($Feedback$). Keluaran PID dikonversi menjadi nilai sudut fasa (*phase angle*) untuk memicu penyalaan Triac pada modul *AC dimmer*, mengatur kecerahan lampu pijar secara proporsional.

### 2. Logika Ventilasi Udara
* **Kondisi Normal / Pemanasan:** Kipas *inhale* menyala kontinu atau berkala untuk menjaga suplai oksigen embrio, kipas *exhale* mati/standby.
* **Kondisi Overheat (Suhu > Setpoint + Toleransi):** Kipas *exhale* (atas) diaktifkan secara otomatis untuk membuang akumulasi panas berlebih dengan cepat keluar sistem.
