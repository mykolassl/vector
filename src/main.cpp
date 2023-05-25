#include "../libs/lib.h"
#include "../libs/apdorojimas.h"

class Entity {
public:
    int x = 10;

    friend std::ostream& operator<<(std::ostream& out, const Entity& e) {
        out << e.x << " ";
        return out;
    }
};

struct A {
    std::string s;
    A() {}
    explicit A(std::string str) : s(std::move(str))  { std::cout << " constructed\n"; }
    A(const A& o) : s(o.s) { std::cout << " copy constructed\n"; }
    A(A&& o)  noexcept : s(std::move(o.s)) { std::cout << " move constructed\n"; }
    A& operator=(const A& other) {
        s = other.s;
        std::cout << " copy assigned\n";
        return *this;
    }
    A& operator=(A&& other)  noexcept {
        s = std::move(other.s);
        std::cout << " move assigned\n";
        return *this;
    }
};

struct President
{
    std::string name;
    std::string country;
    int year;

    President() {}

    President(std::string p_name, std::string p_country, int p_year)
            : name(std::move(p_name)), country(std::move(p_country)), year(p_year)
    {
        std::cout << "I am being constructed.\n";
    }
    President(President&& other)
            : name(std::move(other.name)), country(std::move(other.country)), year(other.year)
    {
        std::cout << "I am being moved.\n";
    }
    President& operator=(const President& other) = default;
};

void pointer_func(const int* p, size_t size) {
    std::cout << "data = ";
    for (std::size_t i = 0; i < size; ++i)
        std::cout << p[i] << ' ';
    std::cout << std::endl;
}

int main() {
    // Pagr. funkcijos

    /*

    // Constructors
    std::cout << std::endl << "Constructor tests:" << std::endl;

    Vector<std::string> words1 { "123", "321", "213" };
    std::cout << words1 << std::endl;

    Vector<std::string> words2(words1.begin(), words1.end());
    std::cout << words2 << std::endl;

    Vector<std::string> words3(words1);
    std::cout << words3 << std::endl;

    Vector<std::string> words4(5, "Hello");
    std::cout << words4 << std::endl;

    // Assignments
    std::cout << std::endl << "Assignment tests: " << std::endl;

    Vector<int> x { 1, 2, 3 }, y, z;
    const auto w = { 4, 5, 6, 7 };

    std::cout << "x = " << x << std::endl;
    std::cout << "y = " << y << std::endl;
    std::cout << "z = " << z << std::endl;

    y = x;
    std::cout << "x = " << x << std::endl;
    std::cout << "y = " << y << std::endl;

    z = std::move(x);
    std::cout << "x = " << x << std::endl;
    std::cout << "z = " << z << std::endl;

    z = w;
    std::cout << "w = ";
    for (auto i : w) std::cout << i << " ";
    std::cout << std::endl;
    std::cout << "z = " << z << std::endl;

    // Assign method
    std::cout << std::endl << "Assign method tests:" << std::endl;

    Vector<char> characters;
    characters.assign(5, 'a');
    std::cout << characters << std::endl;

    Vector<char> extraCharacters(6, 'b');
    characters.assign(extraCharacters.begin(), extraCharacters.end());
    std::cout << characters << std::endl;

    characters.assign({'L', 'a', 'b', 'a', 's'});
    std::cout << characters << std::endl;

    // At method
    std::cout << std::endl << "At method tests:" << std::endl;

    Vector<int> data = { 1, 2, 4, 5, 5, 6 };
    data.at(1) = 88;

    std::cout << "Element at index 2 has value " << data.at(2) << std::endl;
    std::cout << "data size = " << data.size() << std::endl;

    try {
        data.at(6) = 666;
    } catch (std::out_of_range const& exc) {
        std::cout << exc.what() << std::endl;
    }

    std::cout << data << std::endl;

    // Front and back methods
    std::cout << std::endl << "Front and back method tests:" << std::endl;

    Vector<char> letters {'a', 'b', 'c', 'd', 'e', 'f'};
    if (!letters.empty()) {
        std::cout << "The first letter is " << letters.front() << std::endl;
        std::cout << "The last letter is " << letters.back() << std::endl;
    }

    // Data method
    std::cout << std::endl << "Data method tests:" << std::endl;

    Vector<int> container {1, 2, 3, 4};
    pointer_func(container.data(), container.size());

    // Begin and end methods
    std::cout << std::endl << "Begin and end method tests:" << std::endl;

    Vector<int> nums {1, 2, 4, 8, 16};
    Vector<std::string> fruits {"orange", "apple", "raspberry"};
    Vector<char> empty;

    std::for_each(nums.begin(), nums.end(), [](const int n) { std::cout << n << ' '; });
    std::cout << std::endl;

    std::cout << "Sum of nums: " << std::accumulate(nums.begin(), nums.end(), 0) << std::endl;

    if (!fruits.empty()) std::cout << "First fruit: " << *fruits.begin() << std::endl;

    if (empty.begin() == empty.end()) std::cout << "vector 'empty' is indeed empty." << std::endl;

    // Empty method
    std::cout << std::endl << "Empty method tests:" << std::endl << std::boolalpha;

    Vector<int> numbers;
    std::cout << "Initially, numbers.empty(): " << numbers.empty() << std::endl;

    numbers.push_back(42);
    std::cout << "After adding elements, numbers.empty(): " << numbers.empty() << std::endl;

    // Size method
    std::cout << std::endl << "Size and max_size method tests:" << std::endl;

    Vector<int> ns {1, 3, 5, 7};

    std::cout << "'ns' contains " << ns.size() << " elements." << std::endl;

    // Reserve method
    std::cout << std::endl << "Reserve method tests:" << std::endl;

    const int maxElements = 32;
    {
        int reallocationCount = 0;
        Vector<int> v1;
        v1.reserve(maxElements);

        for (int i = 0; i < maxElements; i++) {
            if (v1.size() == v1.capacity()) reallocationCount++;
            v1.push_back(i);
        }
        std::cout << v1 << std::endl;

        std::cout << "Vector memory was reallocated " << reallocationCount << " times (reserve was used)." << std::endl;
    }
    {
        int reallocationCount = 0;
        Vector<int> v1;

        for (int i = 0; i < maxElements; i++) {
            if (v1.size() == v1.capacity()) reallocationCount++;
            v1.push_back(i);
        }
        std::cout << v1 << std::endl;

        std::cout << "Vector memory was reallocated " << reallocationCount << " times (reserve wasn't used)." << std::endl;
    }

    // Capacity method
    std::cout << std::endl << "Capacity method tests:" << std::endl;

    int sz = 100;
    Vector<int> v;

    auto cap = v.capacity();
    std::cout << "Initial size: " << v.size() << ", capacity: " << cap << '\n';

    std::cout << "\nDemonstrate the capacity's growth policy."
                 "\nSize:  Capacity:  Ratio:\n" << std::left;
    while (sz-- > 0) {
        v.push_back(sz);
        if (cap != v.capacity()) {
            std::cout << std::setw( 7) << v.size()
                      << std::setw(11) << v.capacity()
                      << std::setw(10) << v.capacity() / static_cast<float>(cap) << '\n';
            cap = v.capacity();
        }
    }

    std::cout << "\nFinal size: " << v.size() << ", capacity: " << v.capacity() << '\n';

    // Shrink_to_fit method
    std::cout << std::endl << "Shrink_to_fit method tests:" << std::endl;

    Vector<int> v1;
    std::cout << "Default-constructed capacity is " << v1.capacity() << '\n';
    v1.resize(100);
    std::cout << "Capacity of a 100-element vector is " << v1.capacity() << '\n';
    v1.resize(50);
    std::cout << "Capacity after resize(50) is " << v1.capacity() << '\n';
    v1.shrink_to_fit();
    std::cout << "Capacity after shrink_to_fit() is " << v1.capacity() << '\n';
    v1.clear();
    std::cout << "Capacity after clear() is " << v1.capacity() << '\n';
    v1.shrink_to_fit();
    std::cout << "Capacity after shrink_to_fit() is " << v1.capacity() << '\n';
    for (int i = 1000; i < 1300; ++i) v1.push_back(i);
    std::cout << "Capacity after adding 300 elements is " << v1.capacity() << '\n';
    v1.shrink_to_fit();
    std::cout << "Capacity after shrink_to_fit() is " << v1.capacity() << '\n';
    std::cout << v1 << std::endl;

    // Clear method
    std::cout << std::endl << "Clear method tests:" << std::endl;

    Vector<int> v3{1, 2, 3};

    std::cout << "Before clear: ";
    std::cout << v3;
    std::cout << "\nSize=" << v3.size() << ", Capacity=" << v3.capacity() << '\n';

    std::cout << "Clear\n";
    v3.clear();

    std::cout << "After clear:";
    std::cout << v3;
    std::cout << "\nSize=" << v3.size() << ", Capacity=" << v3.capacity() << '\n';

    // Insert method
    std::cout << std::endl << "Insert method tests:" << std::endl;

    Vector<int> c1(3, 100);
    std::cout << c1 << std::endl;

    c1.insert(c1.begin(), 200);
    std::cout << c1 << std::endl;

    c1.insert(c1.begin(), 2, 300);
    std::cout << c1 << std::endl;

    Vector<int> c2(2, 400);
    c1.insert(c1.begin() + 2, c2.begin(), c2.end());
    std::cout << c1 << std::endl;

    int arr[] = {501, 502, 503};
    c1.insert(c1.begin(), arr, arr + std::size(arr));
    std::cout << c1 << std::endl;

    c1.insert(c1.end(), {601, 602, 603});
    std::cout << c1 << std::endl;

    // Emplace method
    std::cout << std::endl << "Emplace method tests:" << std::endl;

    Vector<A> c3;
    c3.reserve(10);
    std::cout << "construct 2 times A:\n";
    A two { "two" };
    A three { "three" };

    std::cout << "emplace:\n";
    c3.emplace(c3.end(), "one");
    std::cout << "\nSize=" << c3.size() << ", Capacity=" << c3.capacity() << '\n';

    std::cout << "emplace with A&:\n";
    c3.emplace(c3.end(), two);
    std::cout << "\nSize=" << c3.size() << ", Capacity=" << c3.capacity() << '\n';

    std::cout << "emplace with A&&:\n";
    c3.emplace(c3.end(), std::move(three));
    std::cout << "\nSize=" << c3.size() << ", Capacity=" << c3.capacity() << '\n';

    std::cout << "content:\n";
    for (auto & i : c3) std::cout << ' ' << i.s;
    std::cout << '\n';

    // Erase method
    std::cout << std::endl << "Erase method tests:" << std::endl;

    Vector<int> c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << c << std::endl;

    c.erase(c.begin());
    std::cout << c << std::endl;

    c.erase(c.begin() + 2, c.begin() + 5);
    std::cout << c << std::endl;

    // Erase all even numbers
    for (Vector<int>::iterator it = c.begin(); it != c.end();)
    {
        if (*it % 2 == 0)
            it = c.erase(it);
        else
            ++it;
    }
    std::cout << c << std::endl;

    // Emplace_back method
    std::cout << std::endl << "Emplace_back method tests:" << std::endl;
    
    Vector<President> elections;
    std::cout << "emplace_back:\n";
    auto& ref = elections.emplace_back("Nelson Mandela", "South Africa", 1994);

    Vector<President> reElections;
    std::cout << "\npush_back:\n";
    reElections.push_back(President("Franklin Delano Roosevelt", "the USA", 1936));

    std::cout << "\nContents:\n";
    for (President const& president: elections) {
        std::cout << president.name << " was elected president of "
                  << president.country << " in " << president.year << ".\n";
    }
    for (President const& president: reElections) {
        std::cout << president.name << " was re-elected president of "
                  << president.country << " in " << president.year << ".\n";
    }

    // Push_back method
    std::cout << std::endl << "Push_back method tests: " << std::endl;

    Vector<std::string> letts;

    letts.push_back("abc");
    std::string s{"def"};
    letts.push_back(std::move(s));

    std::cout << "Vector `letters` holds: ";
    for (auto&& e : letts) std::cout << std::quoted(e) << ' ';

    std::cout << "\nMoved-from string `s` holds: " << std::quoted(s) << '\n';

    // Pop_back method
    std::cout << std::endl << "Pop_back method tests:" << std::endl;

    Vector<int> c4;
    std::cout << c4 << std::endl;

    c4.push_back(5);
    c4.push_back(3);
    c4.push_back(4);
    std::cout << c4 << std::endl;

    c4.pop_back();
    std::cout << c4 << std::endl;

    // Resize method
    std::cout << std::endl << "Resize method tests:" << std::endl;

    Vector<int> con = {1, 2, 3};
    std::cout << "The vector holds: ";
    std::cout << con << std::endl;

    con.resize(5);
    std::cout << "After resize up to 5: ";
    std::cout << con << std::endl;

    con.resize(2);
    std::cout << "After resize down to 2: ";
    std::cout << con << std::endl;

    con.resize(6, 4);
    std::cout << "After resize up to 6 (initializer = 4): ";
    std::cout << con << std::endl;

    // Swap method
    std::cout << std::endl << "Swap method tests:" << std::endl;

    Vector<int> a1{1, 2, 3}, a2{4, 5};

    auto it1 = std::next(a1.begin());
    auto it2 = std::next(a2.begin());

    int& ref1 = a1.front();
    int& ref2 = a2.front();

    std::cout << "{ " << a1 << "}" << " { " << a2 << "} " << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';
    a1.swap(a2);
    std::cout << "{ " << a1 << "}" << " { " << a2 << "} " << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';

    // Comparison operators
    std::cout << std::endl << "Comparison operator tests:" << std::endl;
    Vector<int> alice{1, 2, 3};
    Vector<int> bob{7, 8, 9, 10};
    Vector<int> eve{1, 2, 3};

    std::cout << std::boolalpha;

    // Compare non equal containers
    std::cout << "alice == bob returns " << (alice == bob) << '\n';
    std::cout << "alice != bob returns " << (alice != bob) << '\n';
    std::cout << "alice <  bob returns " << (alice < bob) << '\n';
    std::cout << "alice <= bob returns " << (alice <= bob) << '\n';
    std::cout << "alice >  bob returns " << (alice > bob) << '\n';
    std::cout << "alice >= bob returns " << (alice >= bob) << '\n';

    std::cout << '\n';

    // Compare equal containers
    std::cout << "alice == eve returns " << (alice == eve) << '\n';
    std::cout << "alice != eve returns " << (alice != eve) << '\n';
    std::cout << "alice <  eve returns " << (alice < eve) << '\n';
    std::cout << "alice <= eve returns " << (alice <= eve) << '\n';
    std::cout << "alice >  eve returns " << (alice > eve) << '\n';
    std::cout << "alice >= eve returns " << (alice >= eve) << '\n';

    */

    // Int push

    /*

    unsigned int size = 100000000;
    std::vector<int> vec1;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < size; i++) {
        vec1.push_back(i);
    }
    std::cout << "\nSize=" << vec1.size() << ", Capacity=" << vec1.capacity() << '\n';

    auto end = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "STL vektoriaus uzpildymas " << size << " elementu uztruko " << diff.count() / 1000.0 << std::endl;

    Vector<int> vec2;

    auto start2 = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < size; i++) {
        vec2.push_back(i);
    }
    std::cout << "\nSize=" << vec2.size() << ", Capacity=" << vec2.capacity() << '\n';

    auto end2 = std::chrono::high_resolution_clock::now();
    auto diff2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
    std::cout << "Vektoriaus uzpildymas " << size << " elementu uztruko " << diff2.count() / 1000.0 << std::endl;

    */

    // Studentu push

    /*

    unsigned int size = 10000;
    Vector<int> pazymiai(5, 10);
    Studentas studentas;
    studentas.vardas("Vardas");
    studentas.pavarde("Vardas");
    studentas.pazymiai(pazymiai);

    std::vector<Studentas> vec1;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < size; i++) {
        vec1.push_back(studentas);
    }
    std::cout << "\nSize=" << vec1.size() << ", Capacity=" << vec1.capacity() << '\n';

    auto end = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "STL vektoriaus uzpildymas " << size << " elementu uztruko " << diff.count() / 1000.0 << std::endl;

    Vector<Studentas> vec2;

    auto start2 = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < size; i++) {
        vec2.push_back(studentas);
    }
    std::cout << "\nSize=" << vec2.size() << ", Capacity=" << vec2.capacity() << '\n';

    auto end2 = std::chrono::high_resolution_clock::now();
    auto diff2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
    std::cout << "Vektoriaus uzpildymas " << size << " elementu uztruko " << diff2.count() / 1000.0 << std::endl;

    */

    // Main programa



    char ivestiesBudas;
    std::cout << "Kaip norite vykdyti studentu duomenu ivesti? (r - ivesti ranka, f - skaityti is failo, g - generuoti failus) "; std::cin >> ivestiesBudas;
    while (ivestiesBudas != 'r' && ivestiesBudas != 'f' && ivestiesBudas != 'g') {
        std::cout << "Neteisinga ivestis, bandykite dar karta: ";

        std::cin.ignore(80, '\n');
        std::cin.clear();

        std::cin >> ivestiesBudas;
    }

    if (ivestiesBudas == 'r') ivesti_ranka();
    else if (ivestiesBudas == 'f') skaityti_faila();
    else generuoti_failus();



    // Perskirstymai

    /*

    std::vector<int> vec1;
    size_t perskirstymuSk1 = 0;

    for (int i = 0; i < 100000000; i++) {
        if (vec1.size() == vec1.capacity()) perskirstymuSk1++;
        vec1.push_back(i);
    }
    cout << "Pildant " << vec1.size() << " dydzio vektoriu, ivyko " << perskirstymuSk1 << " perskirstymu." << endl;

    Vector<int> vec2;
    size_t perskirstymuSk2 = 0;

    for (int i = 0; i < 100000000; i++) {
        if (vec2.size() == vec2.capacity()) perskirstymuSk2++;
        vec2.push_back(i);
    }
    cout << "Pildant " << vec2.size() << " dydzio vektoriu, ivyko " << perskirstymuSk2 << " perskirstymu." << endl;

     */

    return 0;
}
