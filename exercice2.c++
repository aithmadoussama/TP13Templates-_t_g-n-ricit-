#include <iostream>
#include <initializer_list>
#include <stdexcept>
using namespace std;

template <typename T, size_t N, size_t M>
class matrice {
private:
    T data[N][M];

public:
    matrice() {
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < M; ++j)
                data[i][j] = 0;
    }

    matrice(initializer_list<initializer_list<T>> vals) {
        size_t i = 0;
        for (auto& ligne : vals) {
            size_t j = 0;
            for (auto& val : ligne) {
                if (i < N && j < M)
                    data[i][j] = val;
                ++j;
            }
            ++i;
        }
    }

    matrice<T, N, M> operator+(const matrice<T, N, M>& other) const {
        matrice<T, N, M> res;
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < M; ++j)
                res.data[i][j] = data[i][j] + other.data[i][j];
        return res;
    }

    template <size_t P>
    matrice<T, N, P> operator*(const matrice<T, M, P>& other) const {
        matrice<T, N, P> res;
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < P; ++j)
                for (size_t k = 0; k < M; ++k)
                    res(i,j) += data[i][k] * other(k,j);
        return res;
    }

    T& operator()(size_t i, size_t j) { return data[i][j]; }
    const T& operator()(size_t i, size_t j) const { return data[i][j]; }

    friend ostream& operator<<(ostream& os, const matrice<T, N, M>& m) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j)
                os << m.data[i][j] << " ";
            os << "\n";
        }
        return os;
    }
};

template <size_t N, size_t M>
class matrice<bool, N, M> {
private:
    bool data[N][M];
public:
    matrice() {
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < M; ++j)
                data[i][j] = false;
    }

    matrice(initializer_list<initializer_list<bool>> vals) {
        size_t i = 0;
        for (auto& ligne : vals) {
            size_t j = 0;
            for (auto& val : ligne) {
                if (i < N && j < M)
                    data[i][j] = val;
                ++j;
            }
            ++i;
        }
    }

    template <size_t P>
    matrice<bool, N, P> operator*(const matrice<bool, M, P>& other) const {
        matrice<bool, N, P> res;
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < P; ++j)
                for (size_t k = 0; k < M; ++k)
                    res(i,j) = res(i,j) || (data[i][k] && other(k,j));
        return res;
    }

    bool& operator()(size_t i, size_t j) { return data[i][j]; }
    const bool& operator()(size_t i, size_t j) const { return data[i][j]; }

    friend ostream& operator<<(ostream& os, const matrice<bool, N, M>& m) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j)
                os << (m.data[i][j] ? 1 : 0) << " ";
            os << "\n";
        }
        return os;
    }
};

int main() {
    std::cout << "test avec int" << std::endl;
    matrice<int, 2, 2> a{{ {1, 2}, {3, 4} }};
    matrice<int, 2, 2> b{{ {5, 6}, {7, 8} }};
    auto c = a + b;
    cout << "addition int:\n" << c << endl;

    
    matrice<int, 2, 3> m1{{ {1, 2, 3}, {4, 5, 6} }};
    matrice<int, 3, 2> m2{{ {7, 8}, {9, 10}, {11, 12} }};
    auto m3 = m1 * m2;
    cout << "produit int:\n" << m3 << endl;

    std::cout << "test avec double" << std::endl;
    matrice<double, 2, 2> d1{{ {1.5, 2.5}, {3.5, 4.5} }};
    matrice<double, 2, 2> d2{{ {0.5, 1.5}, {2.5, 3.5} }};
    auto d3 = d1 + d2;
    cout << "addition double:\n" << d3 << endl;

    std::cout << "test specialisation bool" << std::endl;
    matrice<bool, 2, 2> x{{ {1, 0}, {1, 1} }};
    matrice<bool, 2, 2> y{{ {0, 1}, {1, 0} }};
    auto z = x * y;
    cout << "produit logique:\n" << z << endl;

    return 0;
}
