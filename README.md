# 🚀 C++ Module 06 — C++ Casts (Pretty README)

> **Version 6.2** · **Standard:** C++98 · **Focus:** Type conversions & RTTI · **Exercises:** ex00–ex02

<p align="center">
  <img src="docs/hero.png" alt="C++ Module 06 Hero" width="720"/>
</p>

<p align="center">
  <a href="#"><img alt="C++98" src="https://img.shields.io/badge/Standard-C%2B%2B98-1c2540"/></a>
  <a href="#"><img alt="Warnings" src="https://img.shields.io/badge/Flags--Wall%20-Wextra%20-Werror-4f8cff"/></a>
  <a href="#"><img alt="Build" src="https://img.shields.io/badge/Build-passing-22c55e"/></a>
  <a href="#"><img alt="License" src="https://img.shields.io/badge/License-MIT-f59e0b"/></a>
</p>

---

## 🧭 Overview

**Module theme:** mastering **type conversions** with the 4 C++ casts, safe parsing of scalar literals, pointer↔integer round-trips, and runtime type identification (RTTI) without `<typeinfo>`.

**You will implement:**

* **ex00** — `ScalarConverter` (detect, parse, convert, and format output for `char/int/float/double`).
* **ex01** — `Serializer` (pointer ⇄ `uintptr_t` via `reinterpret_cast`).
* **ex02** — `Base/A/B/C` + `generate/identify` using `dynamic_cast`.

> 📌 Constraints: `-Wall -Wextra -Werror -std=c++98`, **no STL containers/algorithms** until Module 08+, no `printf/alloc/free`, no `using namespace`, **OCF** unless the exercise says otherwise.

---

## 🗂️ Contents

* [🛠️ Tooling & Rules](#️-tooling--rules)
* [🧪 Quick Start](#-quick-start)
* [🎯 The 4 Casts — When & Why](#-the-4-casts--when--why)
* [📦 ex00 — ScalarConverter](#-ex00--scalarconverter)
* [📦 ex01 — Serializer](#-ex01--serializer)
* [📦 ex02 — Identify Real Type](#-ex02--identify-real-type)
* [🧩 Test Matrix](#-test-matrix)
* [🛡️ Defense Cheat Sheet](#️-defense-cheat-sheet)
* [🖼️ Screenshots](#️-screenshots)
* [📁 Project Tree](#-project-tree)
* [📜 License](#-license)

---

## 🛠️ Tooling & Rules

* **Compiler:** `c++ -Wall -Wextra -Werror -std=c++98`
* **No STL containers/algorithms** before Module 08
* **Forbidden:** `printf`, `malloc/calloc/realloc/free`, `using namespace`, `<typeinfo>` (ex02)
* **Design:** Orthodox Canonical Form (OCF) unless explicitly exempted
* **Headers:** self-sufficient with include guards; no inline non-template impls in headers

> ✨ Tip: keep formatting consistent; evaluators love clarity.

---

## 🧪 Quick Start

```bash
# Build each exercise
make -C ex00 && ./ex00/convert 42.0f
make -C ex01 && ./ex01/serializer_demo
make -C ex02 && ./ex02/identify_demo
```

---

## 🎯 The 4 Casts — When & Why

| Cast                     | Purpose                         | Use For                                                               | Avoid For                        |
| ------------------------ | ------------------------------- | --------------------------------------------------------------------- | -------------------------------- |
| `static_cast<T>(x)`      | Compile-time checked conversion | numeric up/down casts; void*→T*; known safe up/down in same hierarchy | Cross-family pointer tricks      |
| `dynamic_cast<T>(x)`     | RTTI-checked downcast           | `Base*`/`&` → `Derived*`/`&` in polymorphic types                     | Non-polymorphic types; hot loops |
| `const_cast<T>(x)`       | Add/remove const/volatile       | Fixing API constness mismatch                                         | Mutating truly const objects     |
| `reinterpret_cast<T>(x)` | Bit reinterpretation            | pointer ⇄ `uintptr_t`, very low-level tasks                           | Regular value conversions        |

> 🧠 Rule of thumb: prefer **`static_cast`**; use **`dynamic_cast`** for safe downcasts; keep **`reinterpret_cast`** as the last resort.

---

## 📦 ex00 — ScalarConverter

**Goal:** parse one literal (CLI arg), detect type, convert to **char/int/float/double**, and print with strict formatting.

### ✅ Inputs to support

* **char:** single printable char (e.g., `a`)
* **int:** `0`, `-42`, `42`
* **float:** `4.2f`, `-inff`, `+inff`, `nanf`
* **double:** `4.2`, `-inf`, `+inf`, `nan`

### 🧩 Approach

1. **Classify** the string (char/int/float/double/pseudo).
2. **Parse** to native type (use `strtol/strtod` + range checks).
3. **Convert** to others using `static_cast`.
4. **Print** with exact formatting (`x.0f`, `x.0`, `impossible`, `Non displayable`).

### 🔒 Non-instantiable class

```cpp
class ScalarConverter {
public:
  static void convert(const std::string& s);
private:
  ScalarConverter();
  ScalarConverter(const ScalarConverter&);
  ScalarConverter& operator=(const ScalarConverter&);
  ~ScalarConverter();
};
```

### 🧪 Edge Cases

* `nan`, `nanf`, `+inf`, `-inff`
* Overflow: `2147483648` → `int: impossible`
* Non-displayable char after numeric cast

> 📏 Always print one decimal for integral floats/doubles.

---

## 📦 ex01 — Serializer

**Goal:** turn a `Data*` into `uintptr_t` and back.

```cpp
struct Data {
  std::string name; // ok in modules < 08 (not a container)
  int score;
};

class Serializer {
public:
  static uintptr_t serialize(Data* ptr) {
    return reinterpret_cast<uintptr_t>(ptr);
  }
  static Data* deserialize(uintptr_t raw) {
    return reinterpret_cast<Data*>(raw);
  }
private:
  Serializer(); Serializer(const Serializer&);
  Serializer& operator=(const Serializer&);
  ~Serializer();
};
```

> ⚠️ No cloning occurs. Don’t dereference after the original `Data` dies.

---

## 📦 ex02 — Identify Real Type

**Goal:** `Base` with **virtual dtor**, 3 derived classes, random `generate()`, and `identify()` via `dynamic_cast` (no `<typeinfo>`).

```cpp
class Base { public: virtual ~Base() {} };
class A : public Base {}; class B : public Base {}; class C : public Base {};

Base* generate();
void   identify(Base* p);
void   identify(Base& p);
```

**Pointer version:** test `dynamic_cast<A*>(p)` etc.

**Reference version:** `dynamic_cast<A&>(p)` in `try/catch` (`std::bad_cast`).

> 🔑 `dynamic_cast` requires a polymorphic base (virtual member).

---

## 🧩 Test Matrix

| Case              | ex00 Expected                                                          |
| ----------------- | ---------------------------------------------------------------------- |
| `./convert 0`     | `char: Non displayable` · `int: 0` · `float: 0.0f` · `double: 0.0`     |
| `./convert nan`   | `char: impossible` · `int: impossible` · `float: nanf` · `double: nan` |
| `./convert 42.0f` | `char: '*'` · `int: 42` · `float: 42.0f` · `double: 42.0`              |

For ex01: ensure pointer equality after round-trip. For ex02: loop `generate()` and verify variety and correct identification.

---

## 🛡️ Defense Cheat Sheet

* ex00: **`static_cast`** everywhere; checked ranges; pseudo-literals handled; exact print formatting.
* ex01: **`reinterpret_cast`** only for pointer⇄`uintptr_t` because it’s the canonical low-level conversion.
* ex02: **`dynamic_cast`** works since `Base` is polymorphic (virtual dtor); pointer version checks null; reference version uses exceptions.
* Global rules followed: no STL containers pre-08, no `typeinfo`, OCF where required.

---

## 🖼️ Screenshots

> Place your assets in `docs/` and update paths below.

<p align="center">
  <img src="docs/ex00-demo.png" alt="ex00 demo" width="720"/>
</p>

<p align="center">
  <img src="docs/ex02-identify.png" alt="ex02 identify" width="720"/>
</p>

---

## 📜 License

This project is released under the **MIT License**. See `LICENSE` for details.

---
