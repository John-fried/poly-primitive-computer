# Poly Primitive Computer

Apa itu **Poly Primitive Computer**?, **Poly Primitive Computer** atau bisa disingkat **PPC** adalah bahasa program esoterik (esolang) atau alat komputasi esoterik yang sedikit memiliki sedikit kemiripan dengan bahasa program **BASIC** (untuk cara mengkomputasinya) dan **Assembly**.

# Hello World!

**PPC** sama sekali tidak mendukung string, dan hanya mendukung **ASCII Value**, tanpa basa-basi ini dia contoh untuk menggambar pesan `Hello World!` di **PPC**:

```
10 mov 0, [trans H]
20 mov 1, [trans e]
30 mov gpr0, [trans l]  ; Simpan 'l' di gpr0
40 mov 2, gpr0          ; Pakai gpr0 (l)
50 mov 3, gpr0          ; Pakai gpr0 (l)
60 mov gpr1, [trans o]  ; Simpan 'o' di gpr1
70 mov 4, gpr1          ; Pakai gpr1 (o)
80 mov 5, 32            ; Space ' '
90 mov 6, [trans W]
100 mov 7, gpr1         ; Pakai gpr1 (o)
110 mov gpr2, [trans r] ; Simpan 'r' di gpr2
120 mov 8, gpr2         ; Pakai gpr2 (r)
130 mov 9, gpr0         ; Pakai gpr0 (l)
140 mov 10, [trans d]
150 mov 11, [trans !]
160 print 0..11		: Gambar indeks 0-11
```

Setelah itu jalankan perintah `run`:
```
] run
```

maka akan muncul pesan `Hello World!` di layar.

# Sintaks

Untuk sintaks, seperti diatas diperkenalkan:

**1. Line number**:
	dengan menambahkan angka pada awal instruksi (contoh: `10 mov 0, 65`) secara langsung perintah yang ditulis akan disimpan ke memori code dan bisa dijalankan melalui instruksi `run` di mode DIRECT, dan instruksi `run` otomatis membuat mode menjadi CODE (menjalankan code)

**2. Subevaluate**:
	dengan membuat dua tutup **"["** dan **"]"**, maka isi dari subevaluate tersebut akan di eksekusi dan setelah itu hasil dari eksekusi akan dikembalikan, contoh proses:

	* `mov 0, [trans A]`
	* `mov 0, 65` <-- Hasil dari instruksi `trans A`
	> `trans` adalah instruksi untuk menerjemahkan satu karakter ke nilai **ASCII**-nya

**3. Komentar**:
	Yaitu dengan menambahkan semi-colon ";" seperti di **Assembly**
