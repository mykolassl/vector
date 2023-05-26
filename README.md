# STL Vector konteinerio realizacija C++

## Vektoriaus veikimo pavyzdžiai
Visi galimi vektoriaus pavyzdžiai pateikti `src/main.cpp` faile. Keletas jų:

1. Vektoriaus sukūrimas
```c++
    Vector<std::string> words1 { "123", "321", "213" };
    std::cout << words1 << std::endl;
    // Spausdina: 123 321 213
    
    Vector<std::string> words2(words1.begin(), words1.end());
    std::cout << words2 << std::endl;
    // Spausdina: 123 321 213
    
    Vector<std::string> words3(words1);
    std::cout << words3 << std::endl;
    // Spausdina: 123 321 213
    
    Vector<std::string> words4(5, "Hello");
    std::cout << words4 << std::endl;
    // Spausdina: Hello Hello Hello Hello Hello
```

2. Elementų įterpimas į vektoriaus galą.
```c++
   Vector<std::string> letters;

   letters.push_back("abc");
   std::string s{"def"};
   letters.push_back(std::move(s));

   std::cout << "Vector `letters` holds: ";
   for (auto&& e : letters) std::cout << std::quoted(e) << ' ';
   // Spausdina: Vector `letters` holds: "abc" "def"

   std::cout << "\nMoved-from string `s` holds: " << std::quoted(s) << '\n';
   // Spausdina: Moved-from string `s` holds: ""
```

3. Vektoriaus padidinimas
```c++
    const int maxElements = 32;
    int reallocationCount = 0;
    Vector<int> v1;
    v1.reserve(maxElements);
    // Vektoriaus maksimalus dydis tampa 32, tačiau jis neužpildomas.
    
    for (int i = 0; i < maxElements; i++) {
        if (v1.size() == v1.capacity()) reallocationCount++;
        v1.push_back(i);
    }
    std::cout << v1 << std::endl;
    // Spausdina elementus nuo 0 iki 31.
    
    std::cout << "Vector memory was reallocated " << reallocationCount << " times (reserve was used)." << std::endl;
    // Spausdina: Vector memory was reallocated 0 times (reserve was used).
```

4. Elementų kūrimas vietoje (in-place) naudojant 'emplace' metodą
```c++
    struct A {
        std::string s;
    };
        
    Vector<A> c3;
    c3.reserve(10);
    A two { "two" };
    A three { "three" };
    
    c3.emplace(c3.end(), "one");
    c3.emplace(c3.end(), two);
    c3.emplace(c3.end(), std::move(three));
    for (auto & i : c3) std::cout << ' ' << i.s;
    // Spausdina: one two three
```

5. Elementų trynimas iš vektoriaus galo
```c++
    Vector<int> container;
    std::cout << container << std::endl;
    // Nespausdina nieko, vektorius tuščias.
    
    c4.push_back(5);
    c4.push_back(3);
    c4.push_back(4);
    std::cout << container << std::endl;
    // Spausdina: 5 3 4, 'size' tampa lygus 3.
    
    c4.pop_back();
    std::cout << c4 << std::endl;
    // Spausdina: 5 3, 'size' sumažėja iki 2.
```

## Spartos analizė

Vektorių užpildymas skaičiais naudojant 'push_back' metodą.

| Elementų kiekis | std::vector laikas | Vector laikas |
|-----------------|--------------------|---------------|
| 10 000          | 1.7ms              | 1.07ms        |
| 100 000         | 2.03ms             | 1.5ms         |
| 1 000 000       | 0.005s             | 0.006s        |
| 10 000 000      | 0.053s             | 0.073s        |
| 100 000 000     | 0.477s             | 0.443s        |

Vektorių užpildymas studento objektais naudojant 'push_back' metodą.

| Elementų kiekis | std::vector laikas | Vector laikas |
|-----------------|--------------------|---------------|
| 10 000          | 9.2ms              | 6.9ms         |
| 100 000         | 41.7ms             | 48.9ms        |
| 1 000 000       | 0.34s              | 0.29s         |
| 10 000 000      | 3.8s               | 4.6s          |

Programos veikimo laikas apdorojant studentų duomenis. Studentų kiekis - 100 000, laikas sekundėmis.

| Vektoriaus tipas | Failo skaitymas | Failo apdorojimas | Studentų rūšiavimas | Studentų atskyrimas | Išvedimas | Visas laikas |
|------------------|-----------------|-------------------|---------------------|---------------------|-----------|--------------|
| std::vector      | 0.043           | 0.13              | 12.8                | 0.017               | 0.16      | 13.16        |
| Vector           | 0.075           | 0.16              | 14.5*               | 0.075               | 0.27      | 15.2         |

*Naudotas bubble sort rikiavimo metodas.

## Perskirstymų skaičius

| Elementų kiekis | std::vector perskirstymai | Vector perskirstymai |
|-----------------|---------------------------|----------------------|
| 100 000 000     | 28                        | 28                   |

