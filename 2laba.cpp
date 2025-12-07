#include <iostream>
#include <cmath>
#include <stdexcept>
#include <cstring>
#include <cstdlib>

class Polynomial {
private:
    double a, b, c;
    static int rootCalculationCount;
    static int instanceCount;
    static bool debugMode;
    
    // Динамические массивы вместо векторов
    static char** deletedPolynomials;
    static int deletedCapacity;
    static int deletedCount;
    
    static char** rootCalculations;
    static int rootCalculationsCapacity;
    static int rootCalculationEntries;
    
    static bool programFinished;

    // Вспомогательные функции для работы с динамическими массивами
    static void addDeletedPolynomial(const std::string& polyInfo) {
        if (deletedCount >= deletedCapacity) {
            // Увеличиваем емкость вдвое
            int newCapacity = (deletedCapacity == 0) ? 2 : deletedCapacity * 2;
            char** newArray = new char*[newCapacity];
            
            // Копируем старые данные
            for (int i = 0; i < deletedCount; i++) {
                newArray[i] = deletedPolynomials[i];
            }
            
            // Освобождаем старый массив указателей
            if (deletedPolynomials != nullptr) {
                delete[] deletedPolynomials;
            }
            
            deletedPolynomials = newArray;
            deletedCapacity = newCapacity;
        }
        
        // Выделяем память для новой строки
        deletedPolynomials[deletedCount] = new char[polyInfo.length() + 1];
        strcpy(deletedPolynomials[deletedCount], polyInfo.c_str());
        deletedCount++;
    }
    
    static void addRootCalculation(const std::string& calcInfo) {
        if (rootCalculationEntries >= rootCalculationsCapacity) {
            // Увеличиваем емкость вдвое
            int newCapacity = (rootCalculationsCapacity == 0) ? 2 : rootCalculationsCapacity * 2;
            char** newArray = new char*[newCapacity];
            
            // Копируем старые данные
            for (int i = 0; i < rootCalculationEntries; i++) {
                newArray[i] = rootCalculations[i];
            }
            
            // Освобождаем старый массив указателей
            if (rootCalculations != nullptr) {
                delete[] rootCalculations;
            }
            
            rootCalculations = newArray;
            rootCalculationsCapacity = newCapacity;
        }
        
        // Выделяем память для новой строки
        rootCalculations[rootCalculationEntries] = new char[calcInfo.length() + 1];
        strcpy(rootCalculations[rootCalculationEntries], calcInfo.c_str());
        rootCalculationEntries++;
    }

public:
    Polynomial() : a(1), b(1), c(1) {
        instanceCount++;
        if (debugMode && !programFinished) {
            std::cout << "Constructor: created polynomial #" << instanceCount 
                      << " (" << a << "x^2 + " << b << "x + " << c << ")" << std::endl;
        }
    }
    
    Polynomial(double constant) : a(0), b(0), c(constant) {
        instanceCount++;
        if (debugMode && !programFinished) {
            std::cout << "Constructor: created polynomial #" << instanceCount 
                      << " (constant: " << c << ")" << std::endl;
        }
    }
    
    Polynomial(double a_val, double b_val, double c_val) 
        : a(a_val), b(b_val), c(c_val) {
        instanceCount++;
        if (debugMode && !programFinished) {
            std::cout << "Constructor: created polynomial #" << instanceCount 
                      << " (" << a << "x^2 + " << b << "x + " << c << ")" << std::endl;
        }
    }
    
    // Копирующий конструктор
    Polynomial(const Polynomial& other) 
        : a(other.a), b(other.b), c(other.c) {
        instanceCount++;
        if (debugMode && !programFinished) {
            std::cout << "Copy constructor: created polynomial #" << instanceCount 
                      << " (copy of: " << a << "x^2 + " << b << "x + " << c << ")" << std::endl;
        }
    }
    
    // Оператор присваивания
    Polynomial& operator=(const Polynomial& other) {
        if (this != &other) {
            a = other.a;
            b = other.b;
            c = other.c;
        }
        return *this;
    }

    // Деструктор
    ~Polynomial() {
        std::string polyInfo = "Polynomial #" + std::to_string(deletedCount + 1) + 
                              ": " + std::to_string(a) + "x^2 + " + 
                              std::to_string(b) + "x + " + std::to_string(c);
        
        addDeletedPolynomial(polyInfo);
        
        if (debugMode && !programFinished) {
            std::cout << "Destructor: deleted " << polyInfo << std::endl;
        }
        
        if (programFinished && deletedCount == instanceCount) {
            printFinalStatistics();
        }
    }
    
    static void setProgramFinished(bool finished) {
        programFinished = finished;
    }
    
    static void setDebugMode(bool mode) {
        debugMode = mode;
    }
    
    // Новая функция для просмотра статистики вычисления корней
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
            std::cout << "No root calculations were performed." << std::endl;
        } else {
            for (int i = 0; i < rootCalculationEntries; i++) {
                std::cout << i+1 << ". " << rootCalculations[i] << std::endl;
            }
            std::cout << "\nTotal root calculations: " << rootCalculationEntries << std::endl;
        }
        
        std::cout << std::string(50, '=') << std::endl;
    }
    
    static void cleanupStaticData() {
        // Освобождаем память для удаленных полиномов
        for (int i = 0; i < deletedCount; i++) {
            delete[] deletedPolynomials[i];
        }
        delete[] deletedPolynomials;
        deletedPolynomials = nullptr;
        deletedCapacity = 0;
        deletedCount = 0;
        
        // Освобождаем память для записей вычислений
        for (int i = 0; i < rootCalculationEntries; i++) {
            delete[] rootCalculations[i];
        }
        delete[] rootCalculations;
        rootCalculations = nullptr;
        rootCalculationsCapacity = 0;
        rootCalculationEntries = 0;
        
        // Сбрасываем счетчики
        rootCalculationCount = 0;
        instanceCount = 0;
        programFinished = false;
    }

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
                calcInfo += " -> Linear equation, root: " + std::to_string(root1);
            } else {
                calcInfo += " -> Constant, no roots";
            }
        } else {
            double discriminant = b * b - 4 * a * c;
            
            if (discriminant > 0) {
                root1 = (-b + sqrt(discriminant)) / (2 * a);
                root2 = (-b - sqrt(discriminant)) / (2 * a);
                numRoots = 2;
                calcInfo += " -> Two roots: " + std::to_string(root1) + 
                           ", " + std::to_string(root2);
            } else if (discriminant == 0) {
                root1 = -b / (2 * a);
                numRoots = 1;
                calcInfo += " -> One root: " + std::to_string(root1);
            } else {
                calcInfo += " -> No real roots (discriminant < 0)";
            }
        }
        
        addRootCalculation(calcInfo);
    }

    // Остальные операторы остаются без изменений...
    Polynomial& operator++() {
        ++a; ++b; ++c;
        return *this;
    }

    Polynomial operator++(int) {
        Polynomial temp = *this;
        ++(*this);
        return temp;
    }

    Polynomial& operator--() {
        --a; --b; --c;
        return *this;
    }

    Polynomial operator--(int) {
        Polynomial temp = *this;
        --(*this);
        return temp;
    }

    Polynomial& operator+=(const Polynomial& other) {
        a += other.a;
        b += other.b;
        c += other.c;
        return *this;
    }

    Polynomial& operator-=(const Polynomial& other) {
        a -= other.a;
        b -= other.b;
        c -= other.c;
        return *this;
    }

    Polynomial& operator*=(double scalar) {
        a *= scalar;
        b *= scalar;
        c *= scalar;
        return *this;
    }

    Polynomial& operator/=(double scalar) {
        if (scalar == 0) {
            throw std::invalid_argument("Delenie na nol!");
        }
        a /= scalar;
        b /= scalar;
        c /= scalar;
        return *this;
    }

    friend Polynomial operator+(Polynomial lhs, const Polynomial& rhs) {
        lhs += rhs;
        return lhs;
    }

    friend Polynomial operator-(Polynomial lhs, const Polynomial& rhs) {
        lhs -= rhs;
        return lhs;
    }

    friend Polynomial operator*(Polynomial lhs, double scalar) {
        lhs *= scalar;
        return lhs;
    }

    friend Polynomial operator*(double scalar, const Polynomial& rhs) {
        Polynomial result = rhs;
        result *= scalar;
        return result;
    }

    friend Polynomial operator/(Polynomial lhs, double scalar) {
        lhs /= scalar;
        return lhs;
    }

    friend bool operator<(const Polynomial& lhs, const Polynomial& rhs) {
        return lhs.evaluate(2) < rhs.evaluate(2);
    }

    friend bool operator>(const Polynomial& lhs, const Polynomial& rhs) {
        return lhs.evaluate(2) > rhs.evaluate(2);
    }

    friend bool operator<=(const Polynomial& lhs, const Polynomial& rhs) {
        return lhs.evaluate(2) <= rhs.evaluate(2);
    }

    friend bool operator>=(const Polynomial& lhs, const Polynomial& rhs) {
        return lhs.evaluate(2) >= rhs.evaluate(2);
    }

    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
        return lhs.evaluate(2) == rhs.evaluate(2);
    }

    friend bool operator!=(const Polynomial& lhs, const Polynomial& rhs) {
        return lhs.evaluate(2) != rhs.evaluate(2);
    }

    double evaluate(double x) const {
        return a * x * x + b * x + c;
    }

    void print() const {
        std::cout << a << "x^2 + " << b << "x + " << c;
    }

    static int getRootCalculationCount() {
        return rootCalculationCount;
    }

    static int getInstanceCount() {
        return instanceCount;
    }

    static void resetStatistics() {
        cleanupStaticData();
    }

    double getA() const { return a; }
    double getB() const { return b; }
    double getC() const { return c; }
};

// Инициализация статических членов
int Polynomial::rootCalculationCount = 0;
int Polynomial::instanceCount = 0;
bool Polynomial::debugMode = false;

char** Polynomial::deletedPolynomials = nullptr;
int Polynomial::deletedCapacity = 0;
int Polynomial::deletedCount = 0;

char** Polynomial::rootCalculations = nullptr;
int Polynomial::rootCalculationsCapacity = 0;
int Polynomial::rootCalculationEntries = 0;

bool Polynomial::programFinished = false;

// Структура для динамического массива полиномов в main
struct PolynomialArray {
    Polynomial* data;
    int capacity;
    int count;
    
    PolynomialArray() : data(nullptr), capacity(0), count(0) {}
    
    void add(const Polynomial& p) {
        if (count >= capacity) {
            int newCapacity = (capacity == 0) ? 2 : capacity * 2;
            Polynomial* newData = new Polynomial[newCapacity];
            
            // Копируем существующие полиномы
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
    
    void clear() {
        delete[] data;
        data = nullptr;
        capacity = 0;
        count = 0;
    }
    
    ~PolynomialArray() {
        clear();
    }
};

void printRoots(double root1, double root2, int numRoots) {
    if (numRoots == 0) {
        std::cout << "Net deystvitelnyh korney" << std::endl;
    } else if (numRoots == 1) {
        std::cout << "Odin koren: x = " << root1 << std::endl;
    } else {
        std::cout << "Dva kornya: x1 = " << root1 << ", x2 = " << root2 << std::endl;
    }
}

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

int main() {
    std::cout << "=== Quadratic Polynomial Calculator ===" << std::endl;
    
    Polynomial::setDebugMode(false);
    
    // Используем динамический массив
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
            
            Polynomial::setDebugMode(true);
            Polynomial::setProgramFinished(true);
            
            std::cout << "\nUdalyayu vse sozdannye polynomy..." << std::endl;
            
            polynomials.clear();
            
            // Очищаем статические данные
            Polynomial::cleanupStaticData();
            
            std::cout << "\nProgramma zavershaet rabotu." << std::endl;
            
        } else {
            std::cout << "Nekorrektny vibor!" << std::endl;
        }
        
    } while (choice != 4);
    
    return 0;
}