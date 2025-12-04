#include <iostream>
#include <cmath>
#include <stdexcept>

class Polynomial {
private:
    double a, b, c;
    static int rootCalculationCount;

public:
    Polynomial() : a(1), b(1), c(1) {}
    Polynomial(double constant) : a(0), b(0), c(constant) {}
    Polynomial(double a_val, double b_val, double c_val) : a(a_val), b(b_val), c(c_val) {}

    ~Polynomial() {
        std::cout << "Polynomial " << a << "x^2 + " << b << "x + " << c << " delete" << std::endl;
    }

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

    void findRoots(double& root1, double& root2, int& numRoots) {
        ++rootCalculationCount;
        numRoots = 0;
        
        double discriminant = b * b - 4 * a * c;
        
        if (discriminant > 0) {
            root1 = (-b + sqrt(discriminant)) / (2 * a);
            root2 = (-b - sqrt(discriminant)) / (2 * a);
            numRoots = 2;
        } else if (discriminant == 0) {
            root1 = -b / (2 * a);
            numRoots = 1;
        }
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

void printRoots(double root1, double root2, int numRoots) {
    if (numRoots == 0) {
        std::cout << "Net deystvitelnyh korney" << std::endl;
    } else if (numRoots == 1) {
        std::cout << "Odin koren: x = " << root1 << std::endl;
    } else {
        std::cout << "Dva kornya: x1 = " << root1 << ", x2 = " << root2 << std::endl;
    }
}

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
    
    std::cout << "\nTest unarnih operacii" << std::endl;
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
    
    std::cout << "\n=== Test operacii prisvaivania ===" << std::endl;
    
    Polynomial p8(1.0, -3.0, 2.0);
    Polynomial p9(2.0, 1.0, -3.0);
    
    std::cout << "p8: "; p8.print(); std::cout << std::endl;
    std::cout << "p9: "; p9.print(); std::cout << std::endl;
    
    Polynomial p10 = p8;
    p10 += p9;
    std::cout << "p8 += p9: "; p10.print(); std::cout << std::endl;
    
    Polynomial p11 = p8;
    p11 -= p9;
    std::cout << "p8 -= p9: "; p11.print(); std::cout << std::endl;
    
    Polynomial p12 = p8;
    p12 *= 2.0;
    std::cout << "p8 *= 2: "; p12.print(); std::cout << std::endl;
    
    Polynomial p13 = p12;
    p13 /= 2.0;
    std::cout << "p12 /= 2: "; p13.print(); std::cout << std::endl;
    
    std::cout << "\nNahozhdenie kornei" << std::endl;
    
    double root1, root2;
    int numRoots;
    
    std::cout << "Korni p8 (x^2 - 3x + 2): ";
    p8.findRoots(root1, root2, numRoots);
    printRoots(root1, root2, numRoots);
    
    std::cout << "Korni p9 (2x^2 + x - 3): ";
    p9.findRoots(root1, root2, numRoots);
    printRoots(root1, root2, numRoots);
    
    Polynomial p14(1.0, 0.0, 1.0);
    std::cout << "Korni p14 (x^2 + 1): ";
    p14.findRoots(root1, root2, numRoots);
    printRoots(root1, root2, numRoots);
    
    Polynomial p15(1.0, -2.0, 1.0);
    std::cout << "Korni p15 (x^2 - 2x + 1): ";
    p15.findRoots(root1, root2, numRoots);
    printRoots(root1, root2, numRoots);
    
    std::cout << "\n6. Testirovanie staticheskogo polya:" << std::endl;
    std::cout << "Podchet korney: " << Polynomial::getRootCalculationCount() << std::endl;
    
    std::cout << "\n7. Testirovanie obrabotki oshibok:" << std::endl;
    try {
        Polynomial p16 = p8;
        p16 /= 0.0;
        std::cout << "Isklyuchenie ne bylo vybrosheno!" << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "Isklyuchenie perehvacheno: " << e.what() << std::endl;
    }
    
    std::cout << "\nFinish" << std::endl;
    
    return 0;
}