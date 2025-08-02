## C++’ta Olmazsa Olmaz Temeller

Aşağıdaki başlıklar, C++’ta “olmaması durumunda sıkıntı yaratacak” temel konuları ve profesyonel bir yazılımcının bilmesi gereken pratikleri içerir:

### 1. RAII ve Akıllı İşaretçiler

**Neden Önemli?**  
Kaynak (bellek, dosya, kilit) yönetimini nesnenin yaşam döngüsüne bağlayarak sızıntıları ve çakışmaları engeller.

**Özellikle Bilmen Gerekenler:**

- `std::unique_ptr<T>`: Tek sahiplik; `std::make_unique` kullanımı
- `std::shared_ptr<T>` ve `std::weak_ptr<T>`: Paylaşımlı sahiplik ve döngüsel referans sorunları
- Kendi RAII sınıfını yazma (ör. bir dosyayı açıp kapatan `FileHandle`)

### 2. Move Semantics, Rule of Zero/Three/Five

**Neden Önemli?**  
Kopyalamak yerine taşıyarak gereksiz bellek ve performans maliyetini önler, modern container’larla uyumlu hale getirir.



**Özellikler:**

- Taşıyıcı kurucu (`T(T&&)`) ve taşıma atama (`T& operator=(T&&)`)
- `= default` ve `= delete` kullanımı
- Mümkünse “Rule of Zero”: Kendi kaynak yönetimini değil, akıllı işaretçileri kullanarak hiçbir özel üye fonksiyona ihtiyaç duymamak

### 3. İstisna Güvenliği (Exception Safety)

**Neden Önemli?**  
Kodun beklenmedik bir hata karşısında tutarlı kalmasını sağlar.

**Dereceler:**

- No‐throw guarantee: Asla exception fırlatmaz
- Strong guarantee: Hata olursa değişiklik yok sayılır
- Basic guarantee: Hata sonrası nesne tutarlı kalır, ama değişiklik olabilir

`noexcept` kullanımı ve standard library sınıflarının exception‐safe özelliklerini bilmek önemlidir.

### 4. Şablonlar (Templates) ve Generic Programming

**Neden Önemli?**  
Tür bağımsız algoritmalar/yapılar yazmanı sağlar.

**Özellikler:**

- Fonksiyon ve sınıf şablonları, şablon özel durumları (specialization)
- `typename` vs `class` sözdizimi
- Temel metaprogramlama: `std::enable_if`, SFINAE, `std::is_integral` gibi type‐traits

### 5. Concurrency ve Çok İş Parçacıklı Programlama

**Neden Önemli?**  
Modern donanımı verimli kullanmak için eşzamanlılık bilgisi şart.

**Özellikler:**

- `std::thread`, `std::mutex`, `std::lock_guard`, `std::condition_variable`
- Atomic işlemler (`std::atomic<T>`) ve bellek düzenlemesi (memory model)
- Thread‐safe container ve “data race” önleme

### 6. Design Patterns ve Yazılım Mimarisi

**Neden Önemli?**  
Karmaşık sistemleri sürdürülebilir, test edilebilir ve genişletilebilir kılar.

**Temeller:**

- Yaratımsal (Creational): Singleton, Factory, Builder
- Yapısal (Structural): Adapter, Facade, Decorator
- Davranışsal (Behavioral): Observer, Strategy, Command

SOLID ilkelerini uygulamaya koymak önemlidir.

### 7. Test Etme ve CI/CD

**Neden Önemli?**  
Kod kalitesini korumak ve hataları erken yakalamak için.

**Araçlar:**

- Birim test: GoogleTest (gtest), Catch2
- Entegrasyon testi, mocking (GoogleMock)
- CI araçları: GitHub Actions, GitLab CI, Jenkins
- Kod kapsam ölçüm (code coverage)

### 8. Build Sistemleri ve Paket Yönetimi

**Neden Önemli?**  
Projeyi farklı makinelerde derlenebilir, bağımlılıkları yönetilebilir hale getirir.

**Araçlar:**

- CMake (en yaygın) – `CMakeLists.txt`, hedef ayarları, konfigürasyon
- Conan veya vcpkg ile üçüncü parti kütüphaneleri yönetmek

### 9. Performans Analizi ve Profiling

**Neden Önemli?**  
Gerçek darboğazları bulup optimize etmek, gereksiz bellek kullanımlarını tespit etmek için.

**Araçlar:**

- Valgrind (Memory leaks), sanitizers (`-fsanitize=address,undefined,thread`)
- Perf, VTune, gprof gibi profiller

### 10. Kod Tarama ve Statik Analiz

**Neden Önemli?**  
Güvenlik açıklarını, hatalı kullanımları derlemeden önce yakalamak için.

**Araçlar:**

- `clang-tidy`, `clang-format` (stil ve statik analiz)
- SonarQube, Cppcheck

---

Bu konuları derinleştirmek, sadece dil bilgini değil, profesyonel iş akışını da olgunlaştırır. Hangi başlığa öncelik vermek istersin? O doğrultuda örnekler ve alıştırmalar hazırlayabiliriz.
