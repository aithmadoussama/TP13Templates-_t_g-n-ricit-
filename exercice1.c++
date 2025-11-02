#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

template <typename T>
class arraydyn {
private:
    size_t capacite;
    size_t taille;
    T* tab;

public:
    arraydyn() : capacite(10), taille(0), tab(new T[capacite]) {}
    arraydyn(size_t cap) : capacite(cap), taille(0), tab(new T[capacite]) {}

    arraydyn(const arraydyn& other)
        : capacite(other.capacite), taille(other.taille), tab(new T[other.capacite]) {
        for (size_t i = 0; i < taille; ++i)
            tab[i] = other.tab[i];
    }

    arraydyn& operator=(const arraydyn& other) {
        if (this != &other) {
            delete[] tab;
            capacite = other.capacite;
            taille = other.taille;
            tab = new T[capacite];
            for (size_t i = 0; i < taille; ++i)
                tab[i] = other.tab[i];
        }
        return *this;
    }

    ~arraydyn() {
        delete[] tab;
    }

    void push_back(const T& val) {
        if (taille >= capacite)
            redimensionner(capacite * 2);
        tab[taille++] = val;
    }

    void pop_back() {
        if (taille == 0)
            throw out_of_range("vide");
        --taille;
    }

    T& operator[](size_t i) {
        if (i >= taille)
            throw out_of_range("index");
        return tab[i];
    }

    const T& operator[](size_t i) const {
        if (i >= taille)
            throw out_of_range("index");
        return tab[i];
    }

    size_t size() const { return taille; }

private:
    void redimensionner(size_t ncap) {
        T* nouveau = new T[ncap];
        for (size_t i = 0; i < taille; ++i)
            nouveau[i] = tab[i];
        delete[] tab;
        tab = nouveau;
        capacite = ncap;
    }

public:
    class iterator {
    private:
        T* ptr;
    public:
        iterator(T* p) : ptr(p) {}
        T& operator*() { return *ptr; }
        iterator& operator++() { ++ptr; return *this; }
        iterator& operator--() { --ptr; return *this; }
        bool operator!=(const iterator& other) const { return ptr != other.ptr; }
    };

    iterator begin() { return iterator(tab); }
    iterator end() { return iterator(tab + taille); }
};

struct point {
    int x, y;
    point(int a=0, int b=0) : x(a), y(b) {}
};

int main() {
    std::cout << "test avec des entiers" << std::endl;
    arraydyn<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    for (auto& e : a) cout << e << " ";
    cout << endl;
    std::cout << "test avec des chaines de caracteres" << std::endl;
    arraydyn<string> b;
    b.push_back("hello");
    b.push_back("world");
    for (auto& e : b) cout << e << " ";
    cout << endl;
    std::cout << "test avec un type objet (structure point)" << std::endl;
    arraydyn<point> c;
    c.push_back(point(1,2));
    c.push_back(point(3,4));
    for (auto& e : c) cout << "(" << e.x << "," << e.y << ") ";
    cout << endl;

    return 0;
}
