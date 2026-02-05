# Poly Primitive Computer

Apa itu **Poly Primitive Computer**?, **Poly Primitive Computer** atau bisa disingkat **PPC** adalah bahasa program esoterik (esolang) atau alat komputasi esoterik yang sedikit memiliki sedikit kemiripan dengan bahasa program **Assembly**.

# Hello World!

**PPC** sama sekali tidak mendukung string, dan hanya mendukung **ASCII Value**, tanpa basa-basi ini dia contoh untuk menggambar pesan `Hello World!` di **PPC**:

```
mov 0, [trans H]
mov 1, [trans e]
mov gpr0, [trans l]  ; Simpan 'l' di gpr0
mov 2, gpr0          ; Pakai gpr0 (l)
mov 3, gpr0          ; Pakai gpr0 (l)
mov gpr1, [trans o]  ; Simpan 'o' di gpr1
mov 4, gpr1          ; Pakai gpr1 (o)
mov 5, 32            ; Space ' '
mov 6, [trans W]
mov 7, gpr1         ; Pakai gpr1 (o)
mov gpr2, [trans r] ; Simpan 'r' di gpr2
mov 8, gpr2         ; Pakai gpr2 (r)
mov 9, gpr0         ; Pakai gpr0 (l)
mov 10, [trans d]
mov 11, [trans !]
print 0..11		; Gambar indeks 0-11
```

Simpan file tersebut sebagai `Hello.ppc` dan jalankan
```
$ ppc ./Hello.ppc
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
