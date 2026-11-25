#include "Lab9_TPP.h"
int main()
{
    std::cout << "=== Library BEFORE ===\n";
    before::Library a;
    a.addBook({"The Catcher in the Rye", "J.D. Salinger"});
    a.addBook({"To Kill a Mockingbird", "Harper Lee"});
    a.displayBooks();
    std::cout << "=== Library AFTER ===\n";
    after::MemoryStorage s;
    after::EmailNotifier n;
    after::Library b(s, n);
    b.addBook({"The Catcher in the Rye", "J.D. Salinger"});
    b.addBook({"To Kill a Mockingbird", "Harper Lee"});
    b.displayBooks();
    std::cout << "=== Kata 1 ===\n";
    Approximator app;
    std::cout << "Legacy pi: " << legacyApproximate(3.1415926535, 1e-9) << '\n';
    std::cout << "Refactored pi: " << app.approximate(3.1415926535, 1e-9) << '\n';
    std::cout << "Reduction: 6/8 = " << Fraction(6, 8) << '\n';
    std::cout << "Addition: 1/2 + 1/3 = " << Fraction(1, 2) + Fraction(1, 3) << '\n';
}
