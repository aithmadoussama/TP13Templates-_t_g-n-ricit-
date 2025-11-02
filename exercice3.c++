#include <iostream>
#include <memory>
#include <stdexcept>
#include <iterator>
#include <vector>
using namespace std;

class stackoverflow : public runtime_error
{
public:
    stackoverflow() : runtime_error("stack overflow") {}
};

class stackunderflow : public runtime_error
{
public:
    stackunderflow() : runtime_error("stack underflow") {}
};

template <typename T>
class stack
{
private:
    size_t capacity;
    size_t top_index;
    unique_ptr<T[]> data;

public:
    explicit stack(size_t cap = 10)
        : capacity(cap), top_index(0), data(make_unique<T[]>(cap)) {}

    template <typename InputIt>
    stack(InputIt begin, InputIt end)
    {
        capacity = distance(begin, end);
        top_index = 0;
        data = make_unique<T[]>(capacity);
        for (auto it = begin; it != end; ++it)
            push(*it);
    }

    void push(const T &val)
    {
        if (top_index >= capacity)
            throw stackoverflow();
        data[top_index++] = val;
    }

    void pop()
    {
        if (empty())
            throw stackunderflow();
        --top_index;
    }

    const T &peek() const
    {
        if (empty())
            throw stackunderflow();
        return data[top_index - 1];
    }

    bool empty() const
    {
        return top_index == 0;
    }

    size_t size() const
    {
        return top_index;
    }

    size_t max_capacity() const
    {
        return capacity;
    }
};

int main()
{
    try
    {
        std::cout << "test basique" << std::endl;
        stack<int> s(5);
        s.push(10);
        s.push(20);
        s.push(30);
        cout << "top: " << s.peek() << endl;
        s.pop();
        cout << "apres pop, top: " << s.peek() << endl;

        for (int i = 0; i < 5; ++i)
            s.push(i + 1);

        vector<string> mots = {"un", "deux", "trois"};
        stack<string> st(mots.begin(), mots.end());
        while (!st.empty())
        {
            cout << st.peek() << " ";
            st.pop();
        }
        cout << endl;

        stack<int> big(1000000);
        for (int i = 0; i < 1000000; ++i)
            big.push(i);
        cout << "stack ok, aucune fuite memoire" << endl;
    }
    catch (const exception &e)
    {
        cerr << "erreur: " << e.what() << endl;
    }

    return 0;
}
