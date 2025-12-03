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
    double evaluate(double x) const {
        return a * x * x + b * x + c;
    }
    void print() const {
        std::cout << a << "x^2 + " << b << "x + " << c;
    }
    double getA() const { return a; }
    double getB() const { return b; }
    double getC() const { return c; }
};
int Polynomial::rootCalculationCount = 0;
int main() {
    std::cout << "Testirovanie " << std::endl;
    Polynomial p1;
    std::cout << "p1(standart):";
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
    
    std::cout << "\nTest getter" << std::endl;
    std::cout << "p3.getA() = " << p3.getA() << std::endl;
    std::cout << "p3.getB() = " << p3.getB() << std::endl;
    std::cout << "p3.getC() = " << p3.getC() << std::endl;
    
    std::cout << "\n=== Finish ===" << std::endl;
    
    return 0;
}