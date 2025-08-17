# SelfLearningSoftwareEngineering

Bu depo, C++ ve C dillerinde veri yapıları, algoritmalar, temel yazılım mühendisliği kavramları ve pratik uygulamalar içeren bir öğrenme ve deneme alanıdır.

## Klasör Yapısı

- **COPL/**  
  C dilinde sanal makine ve ilgili başlık dosyaları (`COPL.c`, `memory.h`, `object.h`, `vm.h`).

- **Scanner/**  
  (Detaylar için ilgili klasöre bakınız.)

- **includes/**  
  Ortak başlık dosyaları (ör. `calculator.hpp`).

- **src/**  
  C++ ile yazılmış örnekler ve uygulamalar:
  - `data_types.cpp`, `functions.cpp`, `hello.cpp`: Temel C++ örnekleri.
  - **calculator/**: Basit hesap makinesi uygulaması.
  - **hashmap/**: Kendi `HashMap` implementasyonu ([`hashmap.hpp`](src/hashmap/hashmap.hpp)), örnek kullanım ve testler.
  - **StudentManagement/**: Öğrenci yönetim sistemi örneği.

- **notlar/**  
  C++ ve yazılım mühendisliği konularında Türkçe notlar:
  - `constexpr.md`, `integral_constant.md`: Derleme zamanı sabitleri ve meta-programlama.
  - `giris.md`: VS Code, GCC/GDB kurulumu ve temel kullanım.
  - `ÖNEMLİ_temeller.md`, `ÖNEMLİ_Teorik_Temeller.md`: Temel C++ ve bilgisayar bilimi kavramları.

- **.vscode/**  
  VS Code için derleme (`tasks.json`) ve debug (`launch.json`) ayarları.

## Derleme ve Çalıştırma

### C Dosyaları

- Derlemek için:  
  **Ctrl+Shift+B** (veya terminalde `gcc dosya.c -g -o dosya.exe`)
- Debug için:  
  **F5** (VS Code debug başlat)

### C++ Dosyaları

- Her alt klasörde (`src/calculator/`, `src/hashmap/`, `src/StudentManagement/`) kendi `main.cpp` ve derlenmiş `.exe` dosyaları bulunur.
- CMake kullanılan projeler için ilgili klasörde `CMakeLists.txt` mevcuttur.

## Notlar ve Kaynaklar

- [notlar/giris.md](notlar/giris.md): VS Code, GCC/GDB kurulumu ve sık karşılaşılan hatalar.
- [notlar/constexpr.md](notlar/constexpr.md): `constexpr` ve derleme zamanı sabitleri.
- [notlar/integral_constant.md](notlar/integral_constant.md): `std::integral_constant` ve meta-programlama.
- [notlar/ÖNEMLİ_temeller.md](notlar/ÖNEMLİ_temeller.md): C++’ta bilinmesi gereken temel konular.
- [notlar/ÖNEMLİ_Teorik_Temeller.md](notlar/ÖNEMLİ_Teorik_Temeller.md): Yazılım mühendisliği ve bilgisayar bilimi temelleri.

## Katkı ve Lisans

Bu depo kişisel öğrenme ve deneme amaçlıdır. Katkıda bulunmak isterseniz, lütfen bir pull request açın.