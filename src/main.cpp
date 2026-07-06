#include "float64.h"
#include <iostream>

int main()
{
    // Test 1: simple addition
    Float64 x1(2), y1(3);
    Float64 z1 = x1 + y1;
    z1.backward(1);
    std::cout << "Test 1 (addition):" << std::endl;
    std::cout << "z = x + y, x=2, y=3" << std::endl;
    std::cout << "  z   = " << z1.value() << " (expected 5)" << std::endl;
    std::cout << "  dz/dx = " << x1.gradient() << " (expected 1)" << std::endl;
    std::cout << "  dz/dy = " << y1.gradient() << " (expected 1)" << std::endl;
    std::cout << std::boolalpha << (z1.value() == 5 && x1.gradient() == 1 && y1.gradient() == 1) << std::endl;
    std::cout << std::endl;

    // Test 2: simple multiplication
    Float64 x2(2), y2(3);
    Float64 z2 = x2 * y2;
    z2.backward(1);
    std::cout << "Test 2 (multiplication):" << std::endl;
    std::cout << "z = x * y, x=2, y=3" << std::endl;
    std::cout << "  z   = " << z2.value() << " (expected 6)" << std::endl;
    std::cout << "  dz/dx = " << x2.gradient() << " (expected 3)" << std::endl;
    std::cout << "  dz/dy = " << y2.gradient() << " (expected 2)" << std::endl;
    std::cout << std::boolalpha << (z2.value() == 6 && x2.gradient() == 3 && y2.gradient() == 2) << std::endl;
    std::cout << std::endl;

    // Test 3: chain: z = (x + y) * w
    Float64 x3(2), y3(3), w3(4);
    Float64 z3 = (x3 + y3) * w3;
    z3.backward(1);
    std::cout << "Test 3 (chain):" << std::endl;
    std::cout << "z = (x + y) * w, x=2, y=3, w=4" << std::endl;
    std::cout << "  z    = " << z3.value() << " (expected 20)" << std::endl;
    std::cout << "  dz/dx = " << x3.gradient() << " (expected 4)" << std::endl;
    std::cout << "  dz/dy = " << y3.gradient() << " (expected 4)" << std::endl;
    std::cout << "  dz/dw = " << w3.gradient() << " (expected 5)" << std::endl;
    std::cout << std::boolalpha << (z3.value() == 20 && x3.gradient() == 4 && y3.gradient() == 4 && w3.gradient() == 5) << std::endl;
    std::cout << std::endl;

    // Test 4: reused variable (BUG): z = x * x
    Float64 x4(3);
    Float64 z4 = x4 * x4;
    z4.backward(1);
    std::cout << "Test 4 (reused variable, known bug):" << std::endl;
    std::cout << "z = x * x, x=3" << std::endl;
    std::cout << "  z    = " << z4.value() << " (expected 9)" << std::endl;
    std::cout << "  dz/dx = " << x4.gradient() << " (expected 6, got " << x4.gradient() << ")" << std::endl;
    std::cout << std::boolalpha << (x4.gradient() == 6) << " (expected: true)" << std::endl;
    std::cout << std::endl;

    // Test 5: reused expression (BUG): t = x + y, z = t * t
    Float64 x5(2), y5(3);
    Float64 t5 = x5 + y5;
    Float64 z5 = t5 * t5;
    z5.backward(1);
    std::cout << "Test 5 (reused expression, known bug):" << std::endl;
    std::cout << "t = x + y, z = t * t, x=2, y=3" << std::endl;
    std::cout << "  t    = " << t5.value() << " (expected 5)" << std::endl;
    std::cout << "  z    = " << z5.value() << " (expected 25)" << std::endl;
    std::cout << "  dz/dx = " << x5.gradient() << " (expected 10, got " << x5.gradient() << ")" << std::endl;
    std::cout << "  dz/dy = " << y5.gradient() << " (expected 10, got " << y5.gradient() << ")" << std::endl;
    std::cout << std::boolalpha << (x5.gradient() == 10 && y5.gradient() == 10) << " (expected: true)" << std::endl;
    std::cout << std::endl;

    return 0;
}
