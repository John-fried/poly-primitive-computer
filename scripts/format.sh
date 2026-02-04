#!/bin/sh

# Mencari semua file .c secara rekursif
# -linux: Menggunakan style kernel Linux
# -i8: Indentasi 8 karakter (standar Linux)
# -ut: Force menggunakan TABS, bukan spasi
# -l500: Set panjang baris sangat tinggi agar tidak ada auto-wrap
# -nbad -nbap -bap: Opsional, untuk menjaga kebersihan baris kosong

find . -name "*.c" -exec indent -linux -i8 -ut -l500 {} +

# Menghapus file backup (.BAK) yang otomatis dibuat oleh indent
find . -name "*.c~" -delete
