#include <iostream>
#include <stdexcept>
#include <cmath>

// Класс исключения, производный от invalid_argument
class GeometricProgressionException : public std::invalid_argument {
private:
    double firstElement;   // первый элемент
    double denominator;    // знаменатель
    int size;              // размер массива
    double* array;         // указатель на массив (недопустимый)

public:
    // Конструктор исключения
    GeometricProgressionException(const std::string& msg,
                                  double first, double denom, int sz, double* arr)
            : std::invalid_argument(msg), firstElement(first), denominator(denom), size(sz) {
        // Копируем массив для хранения в исключении
        array = new double[size];
        for (int i = 0; i < size; ++i) {
            array[i] = arr[i];
        }
    }

    // Метод для печати всех данных
    void printData() const {
        std::cout << "Error: " << what() << std::endl;
        std::cout << "The first element: " << firstElement << std::endl;
        std::cout << "The denominator: " << denominator << std::endl;
        std::cout << "Size of the array: " << size << std::endl;
        std::cout << "Array: ";
        for (int i = 0; i < size; ++i) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }

    ~GeometricProgressionException() {
        delete[] array;
    }
};

// Класс «Массив — геометрическая прогрессия»
class GeometricProgression {
private:
    double firstElement;
    double denominator;
    double* progression;
    int size;

    // Проверка, является ли массив геометрической прогрессией
    bool isValidProgression(double* arr, int n, double first, double denom) const {
        if (n <= 0) return false;
        if (fabs(arr[0] - first) > 1e-9) return false;
        for (int i = 1; i < n; ++i) {
            double expected = first * pow(denom, i);
            if (fabs(arr[i] - expected) > 1e-9) {
                return false;
            }
        }
        return true;
    }

public:
    // Конструктор
    GeometricProgression(double first, double denom, double* arr, int sz) {
        if (sz <= 0 || arr == nullptr) {
            throw GeometricProgressionException(
                    "Incorrect array size or null pointer",
                    first, denom, sz, arr);
        }

        if (!isValidProgression(arr, sz, first, denom)) {
            throw GeometricProgressionException(
                    "The array is not a geometric progression with the specified parameters",
                    first, denom, sz, arr);
        }

        firstElement = first;
        denominator = denom;
        size = sz;
        progression = new double[size];
        for (int i = 0; i < size; ++i) {
            progression[i] = arr[i];
        }
    }

    // Печать прогрессии
    void print() const {
        std::cout << "Geometric progression:" << std::endl;
        std::cout << "The first element: " << firstElement << std::endl;
        std::cout << "The denominator: " << denominator << std::endl;
        std::cout << "Size of the array: " << size << std::endl;
        std::cout << "Array: ";
        for (int i = 0; i < size; ++i) {
            std::cout << progression[i] << " ";
        }
        std::cout << std::endl;
    }

    ~GeometricProgression() {
        delete[] progression;
    }
};

// Демонстрация работы
int main() {
    // Пример 1: корректная прогрессия
    try {
        double arr1[] = {2, 4, 8, 16, 32};
        GeometricProgression gp1(2, 2, arr1, 5);
        gp1.print();
    } catch (GeometricProgressionException& e) {
        e.printData();
    }

    std::cout << "\n---\n\n";

    // Пример 2: некорректная прогрессия
    try {
        double arr2[] = {2, 4, 9, 16, 32}; // 9 вместо 8
        GeometricProgression gp2(2, 2, arr2, 5);
        gp2.print();
    } catch (GeometricProgressionException& e) {
        e.printData();
    }

    std::cout << "\n---\n\n";

    // Пример 3: пустой массив
    try {
        GeometricProgression gp3(3, 2, nullptr, 0);
        gp3.print();
    } catch (GeometricProgressionException& e) {
        e.printData();
    }

    return 0;
}