#include <iostream>
#include <stdexcept>

class VectorInt {
private:
    int* data;
    size_t size;
    int codeError;
    static int objectCount;

public:
    //Конструктори
    VectorInt() : size(1), codeError(0) {
        data = new(std::nothrow) int[size];
        if (!data) {
            codeError = 1;
            size = 0;
        } else {
            data[0] = 0;
        }
        ++objectCount;
    }

    VectorInt(size_t sz) : size(sz), codeError(0) {
        data = new(std::nothrow) int[size];
        if (!data) {
            codeError = 1;
            size = 0;
        } else {
            std::fill(data, data + size, 0);
        }
        ++objectCount;
    }

    VectorInt(size_t sz, int value) : size(sz), codeError(0) {
        data = new(std::nothrow) int[size];
        if (!data) {
            codeError = 1;
            size = 0;
        } else {
            std::fill(data, data + size, value);
        }
        ++objectCount;
    }

    VectorInt(const VectorInt& other) : size(other.size), codeError(0) {
        data = new(std::nothrow) int[size];
        if (!data) {
            codeError = 1;
            size = 0;
        } else {
            std::copy(other.data, other.data + size, data);
        }
        ++objectCount;
    }

    ~VectorInt() {
        delete[] data;
        --objectCount;
    }

    // Перевантаження операцій
    VectorInt& operator=(const VectorInt& other) {
        if (this == &other) return *this;
        delete[] data;
        size = other.size;
        data = new(std::nothrow) int[size];
        if (!data) {
            codeError = 1;
            size = 0;
            return *this;
        }
        std::copy(other.data, other.data + size, data);
        return *this;
    }

    // Унарні операції
    VectorInt& operator++() { 
        for (size_t i = 0; i < size; ++i) {
            data[i]++;
        }
        return *this;
    }

    VectorInt operator++(int) {
        VectorInt temp(*this);
        ++(*this);
        return temp;
    }

    VectorInt& operator--() { 
        for (size_t i = 0; i < size; --i) {
            data[i]--;
        }
        return *this;
    }

    VectorInt operator--(int) { 
        VectorInt temp(*this);
        --(*this);
        return temp;
    }

    bool operator!() const {
        return size == 0;
    }

    VectorInt operator~() const {
        VectorInt temp(size);
        for (size_t i = 0; i < size; ++i) {
            temp.data[i] = ~data[i];
        }
        return temp;
    }

    VectorInt operator-() const {
        VectorInt temp(size);
        for (size_t i = 0; i < size; ++i) {
            temp.data[i] = -data[i];
        }
        return temp;
    }

    // Бінарні арифметичні операції
    VectorInt operator+(const VectorInt& rhs) const {
        if (size != rhs.size) throw std::invalid_argument("Vectors of different sizes");
        VectorInt result(size);
        for (size_t i = 0; i < size; ++i) {
            result.data[i] = data[i] + rhs.data[i];
        }
        return result;
    }

    // Елемент доступу
    int& operator[](size_t index) {
        if (index >= size) {
            codeError = 2;
            return data[size - 1];
        }
        return data[index];
    }

    // Порівняння
    bool operator==(const VectorInt& rhs) const {
        if (size != rhs.size) return false;
        for (size_t i = 0; i < size; ++i) {
            if (data[i] != rhs.data[i]) return false;
        }
        return true;
    }

    // Операції вводу виводу
    friend std::ostream& operator<<(std::ostream& os, const VectorInt& vec);
    friend std::istream& operator>>(std::istream& is, VectorInt& vec);

    static int getObjectCount() {
        return objectCount;
    }
};

int VectorInt::objectCount = 0;

std::ostream& operator<<(std::ostream& os, const VectorInt& vec) {
    for (size_t i = 0; i < vec.size; ++i) {
        os << vec.data[i] << " ";
    }
    return os;
}

std::istream& operator>>(std::istream& is, VectorInt& vec) {
    for (size_t i = 0; i < vec.size; ++i) {
        is >> vec.data[i];
    }
    return is;
}

int main() {
    VectorInt v1(3), v2(3, 5);
    std::cout << "Initial vector v1: " << v1 << std::endl;
    std::cout << "Initial vector v2: " << v2 << std::endl;

    v1 = v2;
    std::cout << "After assignment, v1: " << v1 << std::endl;

    std::cout << "Total objects: " << VectorInt::getObjectCount() << std::endl;

    system("pause");
    return 0;
}
