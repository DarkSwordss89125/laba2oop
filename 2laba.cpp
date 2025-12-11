/**
 * @file main.cpp
 * @brief Программа для работы с квадратными полиномами
 * @author Эльмира
 * @date 2025 декабрь
 * @version 1.0
 * 
 * @details
 * Данная программа реализует класс для работы с квадратными полиномами вида ax² + bx + c.
 * Предоставляет функциональность для:
 * - Вычисления корней уравнений
 * - Выполнения арифметических операций с полиномами
 * - Сравнения полиномов
 * - Сбора статистики вычислений
 * - Управления динамической памятью
 * 
 * Программа включает интерактивное меню для тестирования всех возможностей класса.
 */

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <cstring>
#include <cstdlib>

/**
 * @defgroup PolynomialClass Класс Polynomial
 * @brief Основной класс для работы с квадратными полиномами
 * @{
 */

/**
 * @class Polynomial
 * @brief Класс для представления квадратного полинома вида ax² + bx + c
 * Класс инкапсулирует коэффициенты квадратного полинома и предоставляет:
 * - Арифметические операции (+, -, *, /, +=, -=, *=, /=)
 * - Операции инкремента/декремента (++, --)
 * - Операции сравнения (<, >, <=, >=, ==, !=)
 * - Вычисление корней уравнения
 * - Вычисление значения полинома в точке
 * - Статистику использования класса
 * 
 * @note Все статические данные класса автоматически очищаются при завершении программы
 */
class Polynomial {
private:
    double a; ///< Коэффициент при x²
    double b; ///< Коэффициент при x
    double c; ///< Свободный член
    
    /**
     * @var static int Polynomial::rootCalculationCount
     * @brief Счетчик общего количества вычислений корней
     * @details Увеличивается при каждом вызове метода findRoots()
     */
    static int rootCalculationCount;
    
    /**
     * @var static int Polynomial::instanceCount
     * @brief Счетчик созданных экземпляров класса
     * @details Увеличивается в конструкторах, уменьшается в деструкторе
     */
    static int instanceCount;
    
    /**
     * @var static char** Polynomial::deletedPolynomials
     * @brief Динамический массив для хранения информации об удаленных полиномах
     * @details Используется для финальной статистики
     */
    static char** deletedPolynomials;
    
    /**
     * @var static int Polynomial::deletedCapacity
     * @brief Текущая емкость массива deletedPolynomials
     */
    static int deletedCapacity;
    
    /**
     * @var static int Polynomial::deletedCount
     * @brief Количество элементов в массиве deletedPolynomials
     */
    static int deletedCount;
    
    /**
     * @var static char** Polynomial::rootCalculations
     * @brief Динамический массив для хранения записей о вычислениях корней
     */
    static char** rootCalculations;
    
    /**
     * @var static int Polynomial::rootCalculationsCapacity
     * @brief Текущая емкость массива rootCalculations
     */
    static int rootCalculationsCapacity;
    
    /**
     * @var static int Polynomial::rootCalculationEntries
     * @brief Количество записей в массиве rootCalculations
     */
    static int rootCalculationEntries;
    
    /**
     * @var static bool Polynomial::programFinished
     * @brief Флаг завершения программы
     * @details Используется для определения момента вывода финальной статистики
     */
    static bool programFinished;
    
    /**
     * @brief Добавляет информацию об удалённом полиноме в динамический массив
     * @param polyInfo Строка с информацией о полиноме
     * @private
     */
    static void addDeletedPolynomial(const std::string& polyInfo) {
        if (deletedCount >= deletedCapacity) {
            int newCapacity = (deletedCapacity == 0) ? 2 : deletedCapacity * 2;
            char** newArray = new char*[newCapacity];
            
            for (int i = 0; i < deletedCount; i++) {
                newArray[i] = deletedPolynomials[i];
            }
            
            if (deletedPolynomials != nullptr) {
                delete[] deletedPolynomials;
            }
            
            deletedPolynomials = newArray;
            deletedCapacity = newCapacity;
        }
        
        deletedPolynomials[deletedCount] = new char[polyInfo.length() + 1];
        strcpy(deletedPolynomials[deletedCount], polyInfo.c_str());
        deletedCount++;
    }
    
    /**
     * @brief Добавляет запись о вычислении корней в статический массив
     * @param calcInfo Строка с информацией о вычислении
     * @private
     */
    static void addRootCalculation(const std::string& calcInfo) {
        if (rootCalculationEntries >= rootCalculationsCapacity) {
            int newCapacity = (rootCalculationsCapacity == 0) ? 2 : rootCalculationsCapacity * 2;
            char** newArray = new char*[newCapacity];
            
            for (int i = 0; i < rootCalculationEntries; i++) {
                newArray[i] = rootCalculations[i];
            }
            
            if (rootCalculations != nullptr) {
                delete[] rootCalculations;
            }
            
            rootCalculations = newArray;
            rootCalculationsCapacity = newCapacity;
        }
        
        rootCalculations[rootCalculationEntries] = new char[calcInfo.length() + 1];
        strcpy(rootCalculations[rootCalculationEntries], calcInfo.c_str());
        rootCalculationEntries++;
    }

public:
    /**
     * @brief Конструктор по умолчанию
     * @details Создает полином с коэффициентами a=1, b=1, c=1
     * @post Увеличивает счетчик instanceCount на 1
     */
    Polynomial() : a(1), b(1), c(1) {
        instanceCount++;
    }
    
    /**
     * @brief Конструктор с одним параметром
     * @param constant Значение константы c
     * @details Создает полином с коэффициентами a=0, b=0, c=constant
     * @post Увеличивает счетчик instanceCount на 1
     */
    Polynomial(double constant) : a(0), b(0), c(constant) {
        instanceCount++;
    }
    
    /**
     * @brief Конструктор с тремя параметрами
     * @param a_val Коэффициент при x²
     * @param b_val Коэффициент при x
     * @param c_val Свободный член
     * @post Увеличивает счетчик instanceCount на 1
     */
    Polynomial(double a_val, double b_val, double c_val) 
        : a(a_val), b(b_val), c(c_val) {
        instanceCount++;
    }
    
    /**
     * @brief Копирующий конструктор
     * @param other Полином для копирования
     * @post Создает глубокую копию полинома
     * @post Увеличивает счетчик instanceCount на 1
     */
    Polynomial(const Polynomial& other) 
        : a(other.a), b(other.b), c(other.c) {
        instanceCount++;
    }
    
    /**
     * @brief Оператор присваивания
     * @param other Полином для копирования
     * @return Ссылка на текущий объект
     * @exception Не генерирует исключений
     */
    Polynomial& operator=(const Polynomial& other) {
        if (this != &other) {
            a = other.a;
            b = other.b;
            c = other.c;
        }
        return *this;
    }

    /**
     * @brief Деструктор
     * @details Добавляет информацию об удаленном полиноме в статический массив
     * @post Уменьшает количество живых экземпляров
     * @post При завершении программы выводит финальную статистику
     */
    ~Polynomial() {
        std::string polyInfo = "Polynomial #" + std::to_string(deletedCount + 1) + 
                              ": " + std::to_string(a) + "x^2 + " + 
                              std::to_string(b) + "x + " + std::to_string(c);
        
        addDeletedPolynomial(polyInfo);
        
        if (programFinished && deletedCount == instanceCount) {
            printFinalStatistics();
        }
    }
    
    /**
     * @defgroup StaticMethods Статические методы
     * @brief Методы для работы со статическими данными класса
     * @{
     */
    
    /**
     * @brief Устанавливает флаг завершения программы
     * @param finished true - программа завершена, false - программа работает
     */
    static void setProgramFinished(bool finished) {
        programFinished = finished;
    }
    
    /**
     * @brief Выводит статистику вычисления корней
     * @details Показывает:
     * - Общее количество вычислений корней
     * - Последнее вычисление
     * - Предыдущее вычисление
     * - Все вычисления в хронологическом порядке
     */
    static void showRootCalculationStats() {
        std::cout << "\n" << std::string(40, '=') << std::endl;
        std::cout << "  STATISTIKA VYCHISLENIYA KORNEY" << std::endl;
        std::cout << std::string(40, '=') << std::endl;
        
        std::cout << "Vsego vychisleniy korney s nachala programmy: " 
                  << rootCalculationCount << std::endl;
        
        if (rootCalculationEntries > 0) {
            std::cout << "\nPoslednee vychislenie:" << std::endl;
            std::cout << rootCalculations[rootCalculationEntries - 1] << std::endl;
            
            if (rootCalculationEntries > 1) {
                std::cout << "\nPredydushchee vychislenie:" << std::endl;
                std::cout << rootCalculations[rootCalculationEntries - 2] << std::endl;
            }
            
            std::cout << "\nVse vychisleniya (" << rootCalculationEntries << "):" << std::endl;
            for (int i = 0; i < rootCalculationEntries; i++) {
                std::cout << i+1 << ". " << rootCalculations[i] << std::endl;
            }
        } else {
            std::cout << "\nFunkciya poiska korney eshche ne ispolzovalas." << std::endl;
        }
        
        std::cout << std::string(40, '=') << std::endl;
    }
    
    /**
     * @brief Выводит финальную статистику программы
     * @details Вызывается автоматически при завершении программы
     * Показывает:
     * - Все удаленные полиномы
     * - Все вычисления корней
     * - Итоговую статистику
     */
    static void printFinalStatistics() {
        std::cout << "\n" << std::string(50, '=') << std::endl;
        std::cout << "          FINAL STATISTICS" << std::endl;
        std::cout << std::string(50, '=') << std::endl;
        
        std::cout << "\n=== ALL DELETED POLYNOMIALS ===" << std::endl;
        if (deletedCount == 0) {
            std::cout << "No polynomials were deleted." << std::endl;
        } else {
            for (int i = 0; i < deletedCount; i++) {
                std::cout << i+1 << ". " << deletedPolynomials[i] << std::endl;
            }
            std::cout << "\nTotal deleted polynomials: " << deletedCount << std::endl;
        }
        
        std::cout << "\n=== ROOT CALCULATIONS SUMMARY ===" << std::endl;
        if (rootCalculationEntries == 0) {
            std::cout << "Ni odnogo kornya ne bili vichisleni." << std::endl;
        } else {
            for (int i = 0; i < rootCalculationEntries; i++) {
                std::cout << i+1 << ". " << rootCalculations[i] << std::endl;
            }
            std::cout << "\nTotal root calculations: " << rootCalculationEntries << std::endl;
        }
        
        std::cout << std::string(50, '=') << std::endl;
    }
    
    /**
     * @brief Очищает все статические данные класса
     * @details Освобождает динамическую память, сбрасывает счетчики
     * @warning Должен вызываться только при завершении программы
     */
    static void cleanupStaticData() {
        for (int i = 0; i < deletedCount; i++) {
            delete[] deletedPolynomials[i];
        }
        delete[] deletedPolynomials;
        deletedPolynomials = nullptr;
        deletedCapacity = 0;
        deletedCount = 0;
        
        for (int i = 0; i < rootCalculationEntries; i++) {
            delete[] rootCalculations[i];
        }
        delete[] rootCalculations;
        rootCalculations = nullptr;
        rootCalculationsCapacity = 0;
        rootCalculationEntries = 0;
        
        rootCalculationCount = 0;
        instanceCount = 0;
        programFinished = false;
    }

    /**
     * @brief Возвращает количество вычислений корней
     * @return Количество вызовов findRoots()
     */
    static int getRootCalculationCount() {
        return rootCalculationCount;
    }

    /**
     * @brief Возвращает количество созданных экземпляров
     * @return Общее количество созданных объектов Polynomial
     */
    static int getInstanceCount() {
        return instanceCount;
    }

    /**
     * @brief Сбрасывает всю статистику
     * @details Очищает все статические данные и сбрасывает счетчики
     */
    static void resetStatistics() {
        cleanupStaticData();
    }
    
    /** @} */ // конец группы StaticMethods

    /**
     * @brief Находит корни квадратного уравнения
     * @param[out] root1 Первый корень (если существует)
     * @param[out] root2 Второй корень (если существует)
     * @param[out] numRoots Количество действительных корней (0, 1 или 2)
     * @details Вычисляет корни уравнения ax² + bx + c = 0
     * Обрабатывает случаи:
     * - a = 0 (линейное уравнение)
     * - Дискриминант > 0 (два корня)
     * - Дискриминант = 0 (один корень)
     * - Дискриминант < 0 (нет действительных корней)
     * @post Увеличивает rootCalculationCount на 1
     * @post Добавляет запись в rootCalculations
     */
    void findRoots(double& root1, double& root2, int& numRoots) {
        ++rootCalculationCount;
        numRoots = 0;
        
        std::string calcInfo = "Calculation #" + std::to_string(rootCalculationCount) + 
                              " for " + std::to_string(a) + "x^2 + " + 
                              std::to_string(b) + "x + " + std::to_string(c);
        
        if (a == 0) {
            if (b != 0) {
                root1 = -c / b;
                numRoots = 1;
                calcInfo += " -> Lineinoe uravnenie, koren: " + std::to_string(root1);
            } else {
                calcInfo += " -> Constant, net kornei";
            }
        } else {
            double discriminant = b * b - 4 * a * c;
            
            if (discriminant > 0) {
                root1 = (-b + sqrt(discriminant)) / (2 * a);
                root2 = (-b - sqrt(discriminant)) / (2 * a);
                numRoots = 2;
                calcInfo += " -> Dva kornya: " + std::to_string(root1) + 
                           ", " + std::to_string(root2);
            } else if (discriminant == 0) {
                root1 = -b / (2 * a);
                numRoots = 1;
                calcInfo += " -> Odin koren: " + std::to_string(root1);
            } else {
                calcInfo += " -> Net deistvitelnih korney (discriminant < 0)";
            }
        }
        
        addRootCalculation(calcInfo);
    }

    /**
     * @defgroup UnaryOperators Унарные операторы
     * @brief Операции инкремента и декремента
     * @{
     */
    
    /**
     * @brief Префиксный инкремент
     * @return Ссылка на измененный полином
     * @post Увеличивает все коэффициенты на 1
     */
    Polynomial& operator++() {
        ++a; ++b; ++c;
        return *this;
    }

    /**
     * @brief Постфиксный инкремент
     * @return Копия полинома до изменения
     * @post Увеличивает все коэффициенты на 1
     */
    Polynomial operator++(int) {
        Polynomial temp = *this;
        ++(*this);
        return temp;
    }

    /**
     * @brief Префиксный декремент
     * @return Ссылка на измененный полином
     * @post Уменьшает все коэффициенты на 1
     */
    Polynomial& operator--() {
        --a; --b; --c;
        return *this;
    }

    /**
     * @brief Постфиксный декремент
     * @return Копия полинома до изменения
     * @post Уменьшает все коэффициенты на 1
     */
    Polynomial operator--(int) {
        Polynomial temp = *this;
        --(*this);
        return temp;
    }
    
    /** @} */ // конец группы UnaryOperators

    /**
     * @defgroup CompoundAssignment Составные операторы присваивания
     * @brief Операторы вида @c operator@=
     * @{
     */
    
    /**
     * @brief Оператор сложения с присваиванием
     * @param other Полином для сложения
     * @return Ссылка на текущий объект
     */
    Polynomial& operator+=(const Polynomial& other) {
        a += other.a;
        b += other.b;
        c += other.c;
        return *this;
    }

    /**
     * @brief Оператор вычитания с присваиванием
     * @param other Полином для вычитания
     * @return Ссылка на текущий объект
     */
    Polynomial& operator-=(const Polynomial& other) {
        a -= other.a;
        b -= other.b;
        c -= other.c;
        return *this;
    }

    /**
     * @brief Оператор умножения на скаляр с присваиванием
     * @param scalar Скаляр для умножения
     * @return Ссылка на текущий объект
     */
    Polynomial& operator*=(double scalar) {
        a *= scalar;
        b *= scalar;
        c *= scalar;
        return *this;
    }

    /**
     * @brief Оператор деления на скаляр с присваиванием
     * @param scalar Скаляр для деления
     * @return Ссылка на текущий объект
     * @throws std::invalid_argument если scalar = 0
     */
    Polynomial& operator/=(double scalar) {
        if (scalar == 0) {
            throw std::invalid_argument("Delenie na nol!");
        }
        a /= scalar;
        b /= scalar;
        c /= scalar;
        return *this;
    }
    
    /** @} */ // конец группы CompoundAssignment

    /**
     * @defgroup ArithmeticOperations Арифметические операции
     * @brief Бинарные арифметические операторы
     * @{
     */
    
    /**
     * @brief Сложение двух полиномов
     * @param lhs Левый операнд
     * @param rhs Правый операнд
     * @return Новый полином - сумма lhs и rhs
     */
    friend Polynomial operator+(Polynomial lhs, const Polynomial& rhs) {
        lhs += rhs;
        return lhs;
    }

    /**
     * @brief Вычитание двух полиномов
     * @param lhs Левый операнд
     * @param rhs Правый операнд
     * @return Новый полином - разность lhs и rhs
     */
    friend Polynomial operator-(Polynomial lhs, const Polynomial& rhs) {
        lhs -= rhs;
        return lhs;
    }

    /**
     * @brief Умножение полинома на скаляр
     * @param lhs Полином
     * @param scalar Скаляр
     * @return Новый полином - произведение lhs и scalar
     */
    friend Polynomial operator*(Polynomial lhs, double scalar) {
        lhs *= scalar;
        return lhs;
    }

    /**
     * @brief Умножение скаляра на полином
     * @param scalar Скаляр
     * @param rhs Полином
     * @return Новый полином - произведение scalar и rhs
     */
    friend Polynomial operator*(double scalar, const Polynomial& rhs) {
        Polynomial result = rhs;
        result *= scalar;
        return result;
    }

    /**
     * @brief Деление полинома на скаляр
     * @param lhs Полином
     * @param scalar Скаляр
     * @return Новый полином - частное lhs и scalar
     * @throws std::invalid_argument если scalar = 0
     */
    friend Polynomial operator/(Polynomial lhs, double scalar) {
        lhs /= scalar;
        return lhs;
    }
    
    /** @} */ // конец группы ArithmeticOperations

    /**
     * @defgroup ComparisonOperations Операции сравнения
     * @brief Операторы сравнения полиномов
     * @details Все операторы сравнения работают на основе значения полинома в точке x=2
     * @{
     */
    
    /**
     * @brief Оператор "меньше"
     * @details Сравнивает значения полиномов в точке x=2
     */
    friend bool operator<(const Polynomial& lhs, const Polynomial& rhs) {
        return lhs.evaluate(2) < rhs.evaluate(2);
    }

    /**
     * @brief Оператор "больше"
     * @details Сравнивает значения полиномов в точке x=2
     */
    friend bool operator>(const Polynomial& lhs, const Polynomial& rhs) {
        return lhs.evaluate(2) > rhs.evaluate(2);
    }

    /**
     * @brief Оператор "меньше или равно"
     * @details Сравнивает значения полиномов в точке x=2
     */
    friend bool operator<=(const Polynomial& lhs, const Polynomial& rhs) {
        return lhs.evaluate(2) <= rhs.evaluate(2);
    }

    /**
     * @brief Оператор "больше или равно"
     * @details Сравнивает значения полиномов в точке x=2
     */
    friend bool operator>=(const Polynomial& lhs, const Polynomial& rhs) {
        return lhs.evaluate(2) >= rhs.evaluate(2);
    }

    /**
     * @brief Оператор равенства
     * @details Сравнивает значения полиномов в точке x=2
     */
    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
        return lhs.evaluate(2) == rhs.evaluate(2);
    }

    /**
     * @brief Оператор неравенства
     * @details Сравнивает значения полиномов в точке x=2
     */
    friend bool operator!=(const Polynomial& lhs, const Polynomial& rhs) {
        return lhs.evaluate(2) != rhs.evaluate(2);
    }
    
    /** @} */ // конец группы ComparisonOperations

    /**
     * @brief Вычисляет значение полинома в заданной точке
     * @param x Точка для вычисления
     * @return Значение полинома в точке x: a*x² + b*x + c
     */
    double evaluate(double x) const {
        return a * x * x + b * x + c;
    }

    /**
     * @brief Выводит полином в читаемом формате
     * @details Формат вывода: "ax^2 + bx + c"
     * Пример: "3.5x^2 + -2x + 1"
     */
    void print() const {
        std::cout << a << "x^2 + " << b << "x + " << c;
    }

    /**
     * @defgroup GetterMethods Геттеры
     * @brief Методы для получения значений коэффициентов
     * @{
     */
    
    /**
     * @brief Возвращает коэффициент a
     * @return Коэффициент при x²
     */
    double getA() const { return a; }
    
    /**
     * @brief Возвращает коэффициент b
     * @return Коэффициент при x
     */
    double getB() const { return b; }
    
    /**
     * @brief Возвращает коэффициент c
     * @return Свободный член
     */
    double getC() const { return c; }
    
    /** @} */ // конец группы GetterMethods
};

/** @} */ // конец группы PolynomialClass

// Инициализация статических членов класса Polynomial
int Polynomial::rootCalculationCount = 0;
int Polynomial::instanceCount = 0;

char** Polynomial::deletedPolynomials = nullptr;
int Polynomial::deletedCapacity = 0;
int Polynomial::deletedCount = 0;

char** Polynomial::rootCalculations = nullptr;
int Polynomial::rootCalculationsCapacity = 0;
int Polynomial::rootCalculationEntries = 0;

bool Polynomial::programFinished = false;

/**
 * @defgroup HelperStructures Вспомогательные структуры
 * @brief Структуры для поддержки работы программы
 * @{
 */

/**
 * @struct PolynomialArray
 * @brief Динамический массив для хранения полиномов
 * 
 * @details
 * Реализует динамический массив с автоматическим управлением памятью.
 * Поддерживает добавление элементов и автоматическое расширение при необходимости.
 */
struct PolynomialArray {
    Polynomial* data;   ///< Указатель на массив полиномов
    int capacity;       ///< Текущая емкость массива
    int count;          ///< Количество элементов в массиве
    
    /**
     * @brief Конструктор по умолчанию
     * @post Инициализирует пустой массив
     */
    PolynomialArray() : data(nullptr), capacity(0), count(0) {}
    
    /**
     * @brief Добавляет полином в массив
     * @param p Полином для добавления
     * @post Массив автоматически расширяется при необходимости
     */
    void add(const Polynomial& p) {
        if (count >= capacity) {
            int newCapacity = (capacity == 0) ? 2 : capacity * 2;
            Polynomial* newData = new Polynomial[newCapacity];
            
            for (int i = 0; i < count; i++) {
                newData[i] = data[i];
            }
            
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
        
        data[count] = p;
        count++;
    }
    
    /**
     * @brief Очищает массив
     * @post Освобождает всю занятую память
     */
    void clear() {
        delete[] data;
        data = nullptr;
        capacity = 0;
        count = 0;
    }
    
    /**
     * @brief Деструктор
     * @post Автоматически вызывает clear()
     */
    ~PolynomialArray() {
        clear();
    }
};

/** @} */ // конец группы HelperStructures

/**
 * @defgroup HelperFunctions Вспомогательные функции
 * @brief Функции для поддержки работы программы
 * @{
 */

/**
 * @brief Выводит корни уравнения в читаемом формате
 * @param root1 Первый корень
 * @param root2 Второй корень
 * @param numRoots Количество корней (0, 1 или 2)
 * 
 * @details
 * Форматированный вывод корней:
 * - 0 корней: "Net deystvitelnyh korney"
 * - 1 корень: "Odin koren: x = value"
 * - 2 корня: "Dva kornya: x1 = value1, x2 = value2"
 */
void printRoots(double root1, double root2, int numRoots) {
    if (numRoots == 0) {
        std::cout << "Net deystvitelnyh korney" << std::endl;
    } else if (numRoots == 1) {
        std::cout << "Odin koren: x = " << root1 << std::endl;
    } else {
        std::cout << "Dva kornya: x1 = " << root1 << ", x2 = " << root2 << std::endl;
    }
}

/**
 * @brief Тестирует все операции для заданного полинома
 * @param p Полином для тестирования
 * @return true - вернуться в главное меню, false - продолжить тестирование
 * 
 * @details
 * Предоставляет интерактивное меню для тестирования:
 * 1. Унарные операции (++, --)
 * 2. Бинарные операции (+, -, *, /)
 * 3. Операции сравнения
 * 4. Нахождение корней
 * 5. Вычисление значения
 * 6. Вернуться к выбору полинома
 * 7. Вернуться в главное меню
 */
bool testAllOperations(Polynomial& p) {
    std::cout << "\n----- Test vseh operaciy dlya polynoma: ";
    p.print();
    std::cout << " -----" << std::endl;
    
    Polynomial original_p = p;
    
    int testChoice;
    do {
        std::cout << "\nViberite operaciyu:" << std::endl;
        std::cout << "1. Unarnye operacii (++, --)" << std::endl;
        std::cout << "2. Binarnye operacii (+, -, *, /)" << std::endl;
        std::cout << "3. Operacii sravneniya (<, >, ==, !=)" << std::endl;
        std::cout << "4. Nahozhdenie korney" << std::endl;
        std::cout << "5. Vychislit znachenie" << std::endl;
        std::cout << "6. Vernutsya k viboru polynoma" << std::endl;
        std::cout << "7. Vernutsya v glavnoe menu" << std::endl;
        std::cout << "Vash vibor: ";
        std::cin >> testChoice;
        
        if (testChoice == 1) {
            std::cout << "\n--- Unarnye operacii ---" << std::endl;
            std::cout << "Tekushiy polynom: ";
            p.print();
            std::cout << std::endl;
            
            std::cout << "\n1. ++p (prefix increment)" << std::endl;
            std::cout << "   Do: "; p.print(); std::cout << std::endl;
            Polynomial& result_pre_inc = ++p;
            std::cout << "   Posle ++p: "; p.print(); std::cout << std::endl;
            std::cout << "   Rezultat (ssylka): "; result_pre_inc.print(); std::cout << std::endl;
            
            std::cout << "\n2. p++ (postfix increment)" << std::endl;
            std::cout << "   Do: "; p.print(); std::cout << std::endl;
            Polynomial result_post_inc = p++;
            std::cout << "   Posle p++: "; p.print(); std::cout << std::endl;
            std::cout << "   Rezultat (kopiya): "; result_post_inc.print(); std::cout << std::endl;
            
            std::cout << "\n3. --p (prefix decrement)" << std::endl;
            std::cout << "   Do: "; p.print(); std::cout << std::endl;
            Polynomial& result_pre_dec = --p;
            std::cout << "   Posle --p: "; p.print(); std::cout << std::endl;
            std::cout << "   Rezultat (ssylka): "; result_pre_dec.print(); std::cout << std::endl;
            
            std::cout << "\n4. p-- (postfix decrement)" << std::endl;
            std::cout << "   Do: "; p.print(); std::cout << std::endl;
            Polynomial result_post_dec = p--;
            std::cout << "   Posle p--: "; p.print(); std::cout << std::endl;
            std::cout << "   Rezultat (kopiya): "; result_post_dec.print(); std::cout << std::endl;
            
            p = original_p;
            
        } else if (testChoice == 2) {
            std::cout << "\n--- Binarnye operacii ---" << std::endl;
            
            std::cout << "Vvedite vtoroy polynom (a b c): ";
            double a, b, c;
            std::cin >> a >> b >> c;
            Polynomial other(a, b, c);
            
            std::cout << "\nOperacii s polynomami:" << std::endl;
            std::cout << "p1: "; p.print(); std::cout << std::endl;
            std::cout << "p2: "; other.print(); std::cout << std::endl;
            
            std::cout << "\n1. p1 + p2 = "; (p + other).print(); std::cout << std::endl;
            std::cout << "2. p1 - p2 = "; (p - other).print(); std::cout << std::endl;
            
            double scalar;
            std::cout << "\nVvedite chislo dlya umnozheniya/deleniya: ";
            std::cin >> scalar;
            
            std::cout << "3. p1 * " << scalar << " = "; (p * scalar).print(); std::cout << std::endl;
            std::cout << "4. " << scalar << " * p1 = "; (scalar * p).print(); std::cout << std::endl;
            
            if (scalar != 0) {
                std::cout << "5. p1 / " << scalar << " = "; (p / scalar).print(); std::cout << std::endl;
            } else {
                std::cout << "5. p1 / 0 = Nelzya delit na nol!" << std::endl;
            }
            
        } else if (testChoice == 3) {
            std::cout << "\n--- Operacii sravneniya ---" << std::endl;
            
            std::cout << "Vvedite vtoroy polynom (a b c): ";
            double a, b, c;
            std::cin >> a >> b >> c;
            Polynomial other(a, b, c);
            
            double x = 2.0;
            
            std::cout << "\nSravnenie polynomov pri x = " << x << ":" << std::endl;
            std::cout << "p1: "; p.print(); 
            std::cout << " = " << p.evaluate(x) << std::endl;
            std::cout << "p2: "; other.print(); 
            std::cout << " = " << other.evaluate(x) << std::endl;
            
            std::cout << "\nRezultaty sravneniya:" << std::endl;
            
            double val1 = p.evaluate(x);
            double val2 = other.evaluate(x);
            
            std::cout << "p1 < p2: " << (p < other ? "DA" : "NET") << std::endl;
            std::cout << "p1 > p2: " << (p > other ? "DA" : "NET") << std::endl;
            std::cout << "p1 <= p2: " << (p <= other ? "DA" : "NET") << std::endl;
            std::cout << "p1 >= p2: " << (p >= other ? "DA" : "NET") << std::endl;
            std::cout << "p1 == p2: " << (p == other ? "DA" : "NET") << std::endl;
            std::cout << "p1 != p2: " << (p != other ? "DA" : "NET") << std::endl;
            
            std::cout << "\nItog:" << std::endl;
            if (val1 > val2) {
                std::cout << "p1 > p2" << std::endl;
            } else if (val1 < val2) {
                std::cout << "p1 < p2" << std::endl;
            } else {
                std::cout << "p1 = p2" << std::endl;
            }
            
        } else if (testChoice == 4) {
            std::cout << "\n--- Nahozhdenie korney ---" << std::endl;
            std::cout << "Polynom: "; p.print(); std::cout << std::endl;
            
            double root1, root2;
            int numRoots;
            p.findRoots(root1, root2, numRoots);
            std::cout << "Korni: ";
            printRoots(root1, root2, numRoots);
            
        } else if (testChoice == 5) {
            std::cout << "\n--- Vychislenie znacheniya ---" << std::endl;
            double x;
            std::cout << "Vvedite x: ";
            std::cin >> x;
            std::cout << "p(" << x << ") = " << p.evaluate(x) << std::endl;
            
        } else if (testChoice == 6) {
            std::cout << "Vozvrashchenie k viboru polynoma..." << std::endl;
            p = original_p;
            return false;
            
        } else if (testChoice == 7) {
            std::cout << "Vozvrashenie v glavnoe menu..." << std::endl;
            p = original_p;
            return true;
            
        } else {
            std::cout << "Nekorrektny vibor!" << std::endl;
        }
        
    } while (true);
}

/** @} */ // конец группы HelperFunctions

/**
 * @brief Главная функция программы
 * @return 0 при успешном завершении
 * 
 * @details
 * Реализует интерактивное меню:
 * 1. Создать полином (ручной ввод)
 * 2. Протестировать все операции
 * 3. Узнать статистику вычисления корней
 * 4. Выход
 * 
 * При выходе автоматически выводится статистика и очищается память.
 */
int main() {
    std::cout << "=== Quadratic Polynomial Calculator ===" << std::endl;
    
    PolynomialArray polynomials;
    
    int choice;
    do {
        std::cout << "\n===== MENU =====" << std::endl;
        std::cout << "1. Sozdat polynom (ruchnoy vvod)" << std::endl;
        std::cout << "2. Testirovat vse operaciy" << std::endl;
        std::cout << "3. Uznat statistiku vychisleniya korney" << std::endl;
        std::cout << "4. Vihod" << std::endl;
        std::cout << "Viberite deystvie: ";
        std::cin >> choice;
        
        if (choice == 1) {
            std::cout << "\n----- Sozdanie polynoma -----" << std::endl;
            std::cout << "Viberite tip konstruktora:" << std::endl;
            std::cout << "1. Konstruktor po umolchaniyu (1,1,1)" << std::endl;
            std::cout << "2. Konstruktor s odnim parametrom (c)" << std::endl;
            std::cout << "3. Konstruktor s tremya parametrami (a,b,c)" << std::endl;
            std::cout << "Vash vibor: ";
            
            int constrChoice;
            std::cin >> constrChoice;
            
            if (constrChoice == 1) {
                polynomials.add(Polynomial());
                std::cout << "\nSozdan polynom: ";
                polynomials.data[polynomials.count - 1].print();
                std::cout << std::endl;
                
            } else if (constrChoice == 2) {
                double c;
                std::cout << "Vvedite c: ";
                std::cin >> c;
                
                polynomials.add(Polynomial(c));
                std::cout << "\nSozdan polynom: ";
                polynomials.data[polynomials.count - 1].print();
                std::cout << std::endl;
                
            } else if (constrChoice == 3) {
                double a, b, c;
                std::cout << "Vvedite a: ";
                std::cin >> a;
                std::cout << "Vvedite b: ";
                std::cin >> b;
                std::cout << "Vvedite c: ";
                std::cin >> c;
                
                polynomials.add(Polynomial(a, b, c));
                std::cout << "\nSozdan polynom: ";
                polynomials.data[polynomials.count - 1].print();
                std::cout << std::endl;
            }
            
        } else if (choice == 2) {
            std::cout << "\n===== Testirovanie vseh operaciy =====" << std::endl;
            
            if (polynomials.count == 0) {
                std::cout << "Net sozdannyh polynomov. Sozdadim standartnye..." << std::endl;
                
                polynomials.add(Polynomial());
                polynomials.add(Polynomial(5.0));
                polynomials.add(Polynomial(1.0, -3.0, 2.0));
            }
            
            while (true) {
                std::cout << "\nViberite polynom dlya testirovaniya:" << std::endl;
                std::cout << "1. Vvesti novyy polynom" << std::endl;
                
                for (int i = 0; i < polynomials.count; i++) {
                    std::cout << i+2 << ". ";
                    polynomials.data[i].print();
                    std::cout << std::endl;
                }
                
                int lastOption = polynomials.count + 2;
                std::cout << lastOption << ". Vernutsya v glavnoe menu" << std::endl;
                
                std::cout << "\nVash vibor: ";
                int polyChoice;
                std::cin >> polyChoice;
                
                if (polyChoice == lastOption) {
                    std::cout << "\nVozvrashenie v glavnoe menu..." << std::endl;
                    break;
                }
                else if (polyChoice == 1) {
                    double a, b, c;
                    std::cout << "Vvedite a b c: ";
                    std::cin >> a >> b >> c;
                    
                    polynomials.add(Polynomial(a, b, c));
                    std::cout << "\nSozdan novyy polynom: ";
                    polynomials.data[polynomials.count - 1].print();
                    std::cout << std::endl;
                    
                    bool backToMain = testAllOperations(polynomials.data[polynomials.count - 1]);
                    
                    if (backToMain) {
                        break;
                    }
                }
                else if (polyChoice >= 2 && polyChoice <= polynomials.count + 1) {
                    bool backToMain = testAllOperations(polynomials.data[polyChoice - 2]);
                    if (backToMain) {
                        break;
                    }
                }
                else {
                    std::cout << "Nekorrektny vibor!" << std::endl;
                }
            }
            
        } else if (choice == 3) {
            Polynomial::showRootCalculationStats();
            
            std::cout << "\nNazhmite Enter dlya prodolzheniya...";
            std::cin.ignore();
            std::cin.get();
            
        } else if (choice == 4) {
            std::cout << "\n=== Zavershenie programmy ===" << std::endl;
            
            Polynomial::showRootCalculationStats();
            
            Polynomial::setProgramFinished(true);
            
            std::cout << "\nUdalyayu vse sozdannye polynomy..." << std::endl;
            
            polynomials.clear();
            
            Polynomial::cleanupStaticData();
            
            std::cout << "\nProgramma zavershaet rabotu." << std::endl;
            
        } else {
            std::cout << "Nekorrektny vibor!" << std::endl;
        }
        
    } while (choice != 4);
    
    return 0;
}