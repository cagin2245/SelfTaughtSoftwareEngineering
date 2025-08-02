# `std::integral_constant` Nedir?

`std::integral_constant`, C++'ta tipik olarak `<type_traits>` başlık dosyasında tanımlı, derleme zamanı sabit değerleri türler üzerinden temsil eden bir yardımcı (utility) yapıdır.

## Tanım

```cpp
template<class T, T v>
struct integral_constant {
    static constexpr T value = v;
    using value_type = T;
    using type = integral_constant;  // C++11
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }
};
```

- **T**: Taşınacak değer tipi (örneğin `int`, `bool`, `char`).
- **v**: `T` tipinde derleme zamanı sabit bir değer.

---

## Neden Kullanılır?

### Tip Tabanlı Sabitler

- `std::integral_constant<bool, true>` → `std::true_type`
- `std::integral_constant<bool, false>` → `std::false_type`

Şablon parametreleri veya metaprogramlama bağlamında, bir değer yerine “bir tür” üzerinden bilgi taşımak için kullanılır.

### Tag Dispatch / Overload Seçimi

Fonksiyon şablonlarını derleme zamanında farklılaştırmak (dispatch) için:

```cpp
#include <type_traits>
#include <iostream>

// Genel (fallback)
template<class T>
void process(T, std::false_type) {
  std::cout << "Not integral\n";
}

// Tamsayılar için özel
template<class T>
void process(T, std::true_type) {
  std::cout << "Integral type\n";
}

template<class T>
void process(T x) {
  // is_integral<T> bir integral_constant<bool, ...> döner
  process(x, std::is_integral<T>{});
}

int main() {
  process(3);      // Integral type
  process(3.14);   // Not integral
}
```

### Derleme Zamanı Koşulları

```cpp
static_assert(std::is_same<A, B>::value, "A ve B farklı");
```
Burada `is_same<A,B>::value` bir `constexpr bool` ve `is_same` tip olarak `integral_constant<bool, ...>` döner.

---

## İlgili Alias’lar

```cpp
using true_type = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;
```

---

## Avantajları

- **Tamamen derleme zamanı:** Hiçbir runtime maliyeti yoktur.
- **Tip tabanlı bilgi taşır:** Şablon seçimini, metaprogramlamayı kolaylaştırır.
- **Bütünleşik operatör:** `operator T()` ile doğrudan bir değer gibi kullanılabilir.

---

## Özet

`std::integral_constant`, derleme zamanı sabitlerini “tür” şeklinde sarmalayarak güçlü C++ metaprogramlama ve şablon tabanlı dispatch teknikleri kullanmanızı sağlar.