#include <iostream>
#include <cmath>

class Polynomial {
private:
    double a, b, c;
    static int rootCalculationCount;

public:
    Polynomial() : a(0), b(0), c(0) {}
    Polynomial(double constant) : a(0), b(0), c(constant) {}
    Polynomial(double a_val, double b_val, double c_val) : a(a_val), b(b_val), c(c_val) {}

    ~Polynomial() {
        std::cout << "Polynomial " << a << "x^2 + " << b << "x + " << c << " delete" << std::endl;
    }

    Polynomial& operator++() {
        ++a;
        ++b;
        ++c;
        return *this;
    }

    Polynomial operator++(int) {
        Polynomial temp = *this;
        ++(*this);
        return temp;
    }

    Polynomial& operator--() {
        --a;
        --b;
        --c;
        return *this;
    }

    Polynomial operator--(int) {
        Polynomial temp = *this;
        --(*this);
        return temp;
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

    double getA() const { return a; }
    double getB() const { return b; }
    double getC() const { return c; }
};

int Polynomial::rootCalculationCount = 0;

int main() {
    std::cout << "=== Testing ===" << std::endl;
    
    Polynomial p1;
    std::cout << "p1(standart): ";
    p1.print();
    std::cout << std::endl;
    
    Polynomial p2(5.0);
    std::cout << "p2 (1 parametr): ";
    p2.print();
    std::cout << std::endl;
    
    Polynomial p3(1.0, -3.0, 2.0);
    std::cout << "p3 (3 parametra): ";
    p3.print();
    std::cout << std::endl;
    
    std::cout << "\nTest method evaluate():" << std::endl;
    double test_x = 2.0;
    double result = p3.evaluate(test_x);
    std::cout << "p3(" << test_x << ") = " << result << std::endl;
    
    if (result == 0.0) {
        std::cout << "Verno" << std::endl;
    } else {
        std::cout << "Oshibka" << std::endl;
    }
    
    std::cout << "\nTest getter:" << std::endl;
    std::cout << "p3.getA() = " << p3.getA() << std::endl;
    std::cout << "p3.getB() = " << p3.getB() << std::endl;
    std::cout << "p3.getC() = " << p3.getC() << std::endl;
    
    std::cout << "\nTest unarnih operacii " << std::endl;
    
    std::cout << "\nOriginal polynomial p3: ";
    p3.print();
    std::cout << std::endl;
    
    std::cout << "\n1. Testing ++p3:" << std::endl;
    Polynomial p4 = ++p3;
    std::cout << "Posle ++p3: ";
    p3.print();
    std::cout << std::endl;
    std::cout << "Resultat p4 = ++p3: ";
    p4.print();
    std::cout << std::endl;
    
    std::cout << "\n2. Testing p3++:" << std::endl;
    Polynomial p5 = p3++;
    std::cout << "Znachenie p5 (old znachenie): ";
    p5.print();
    std::cout << std::endl;
    std::cout << "Znachenie p3 posle p3++: ";
    p3.print();
    std::cout << std::endl;
    
    std::cout << "\n3. Testing --p3:" << std::endl;
    Polynomial p6 = --p3;
    std::cout << "Posle --p3: ";
    p3.print();
    std::cout << std::endl;
    std::cout << "Resultat p6 = --p3: ";
    p6.print();
    std::cout << std::endl;
    
    std::cout << "\n4. Testing p3--:" << std::endl;
    Polynomial p7 = p3--;
    std::cout << "Znachenie p7 (old znachenie): ";
    p7.print();
    std::cout << std::endl;
    std::cout << "Znachenie p3 posle p3--: ";
    p3.print();
    std::cout << std::endl;
    
    std::cout << "\n5. Testirovanie evaluate() posle vseh operacii:" << std::endl;
    double x = 1.0;
    std::cout << "p3(" << x << ") = " << p3.evaluate(x) << std::endl;
    std::cout << "p7(" << x << ") = " << p7.evaluate(x) << std::endl;
    
    std::cout << "\n6. Testirovanie staticheskogo polya:" << std::endl;
    std::cout << "Podchet korney" << Polynomial::getRootCalculationCount() << std::endl;
    
    std::cout << "\nFinish" << std::endl;
    
    return 0;
}