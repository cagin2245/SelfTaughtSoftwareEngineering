# `constexpr` Kullanımı

`constexpr` ile işaretlenmiş ifadeler veya fonksiyonlar, derleyici tarafından derleme zamanında hesaplanabilir. Aşağıdaki durumlarda `constexpr` kullanılması önerilir:

## Dizi Boyutları

C++’ta sabit bir tamsayı ifadenin derleme zamanında bilinmesi gerekir.

```cpp
constexpr int SIZE = 128;
int buffer[SIZE]; // Derleyici SIZE’ı derleme zamanında bilir
```

Eğer `SIZE` sadece `const` olsaydı, bazı derleyiciler bunu derleme zamanında dizi boyutu olarak kabul etmeyebilir.

## Template Non-Type Parametreleri

```cpp
template<int N>
struct StaticVector {
    int data[N];
};

constexpr int DIM = 16;
StaticVector<DIM> v; // DIM constexpr olduğu için derleme zamanı sabiti
```

Burada `DIM` sadece `const` olsaydı, `StaticVector<DIM>` hatalı olurdu.

Çünkü C++’ta şablonları (“template”leri) derleme zamanında somutlaştırırken (instantiate ederken), derleyicinin o şablonu hangi boyut, sabit veya değeri kullanarak kod üreteceğini tam bir kesinlikle bilmesi gerekir. Eğer şablona gelen parametre çalışma zamanında değişebilecek bir değer olsaydı, derleyici o kodu derleme aşamasında oluşturamazdı.

“Structural constant expression” terimi de bu kesinliği sağlar:

    Derleyici ona baktığında, hiçbir koşula veya çalışma zamanı girdisine bağlı kalmadan, tamamen sabit bir sonuç döneceğini garanti eder.

    Sadece constexpr olarak işaretlenen ifadeler ve derleme zamanında mutlak olarak çözümlenebilen işlemler bu tanıma girer.

Örneğin bir dizi boyutu veya template<int N> gibi bir parametre, derlemeye taştığı anda kodun bellekteki yerleşimini, tipini ve fonksiyon imzalarını belirler. Eğer bu değer derleme zamanında bilinmezse:

    Kod jenerasyonu yapılamaz,

    Link aşamasında hangi sembollerin üretilmesi gerektiği belirsiz kalır,

    Derleyici “template argument is not a constant expression” hatası vererek sizi uyarır.

Bu yüzden C++ standardı, şablon non-type parametreleri için “structural constant expression” zorunluluğu getirir: ancak tamamen derleme zamanı sabiti olduğu kesin olan değerleri kabul eder.

## `static_assert` Kontrolleri

Derleme zamanında koşul doğrulamak için:

```cpp
constexpr int LOG2(int x) {
    return (x <= 1) ? 0 : 1 + LOG2(x/2);
}

static_assert(LOG2(16) == 4, "LOG2 hesaplaması yanlış!");
```

`LOG2` constexpr olmasa, derleyici bu assert’i değerlendiremezdi.

## Derleme Zamanı Sabitleri Gerektiren API’ler

- `std::array<T, N>` gibi kapsayıcılar
- `alignas(...)`, `alignof` parametreleri
- `noexcept` bağıntıları
- `switch` içindeki `case` etiketleri

## Performans Avantajı İçin

Karmaşık hesaplamaları her çağırışta değil, derleyicide bir kez çözmek için:

```cpp
constexpr long factorial(long n) {
    return (n < 2) ? 1 : (n * factorial(n - 1));
}

constexpr long F5 = factorial(5); // F5 == 120
```

Eğer `factorial` sadece `const` olsaydı, her `factorial(5)` çağrısında hesaplama yapılacaktı.

## Hangi İfadeler Derleyici Tarafından Hesaplanmalı?

- Sabit tablo değerleri: trigonometrik sabitler, π gibi
- Bit işlemleri: `constexpr uint32_t mask = (1u << k) - 1;`
- Küçük algoritmalar: dizi uzunluğu, kayıt ofsetleri, sabit çeviriler
- Meta-programlama: tip çıkarımları, `std::integral_constant` temelli kodlar

---

Özetle, “asla değişmeyecek, derleme zamanında karar verilmesi gereken” her yerde `constexpr` kullan. Böylece:

- Derleyici bu değerleri tek seferde hesaplayıp makine koduna sabit gömer.
- Runtime’da bu hesaplamaların yükünü ortadan kaldırırsın.
- Kodun güvenilirliği ve okunabilirliği artar (niyet açıkça “sabit” olarak işaretlenir).
