#include "Library.h"
#include "Approximator.h"
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <functional>
int main()
{
    int failed = 0;
    auto test = [&](const char *name, auto fn) {
        try
        {
            if (!fn())
                throw std::runtime_error("check failed");
            std::cout << "PASS " << name << '\n';
        }
        catch (...)
        {
            ++failed;
            std::cout << "FAIL " << name << '\n';
        }
    };
    for (double v : {0.5, 0.75, 2.0, 3.1415926535})
    {
        auto good = [&](Fraction f) {
            return std::abs(1.0 - f.numerator() / (v * f.denominator())) <= 1e-9;
        };
        test("Legacy approximation", [&] {
            return good(legacyApproximate(v, 1e-9));
        });
        test("Refactored approximation", [&] {
            return good(Approximator{}.approximate(v, 1e-9));
        });
    }
    test("Reduction", [] {
        return Fraction(6, 8).numerator() == 3 && Fraction(6, 8).denominator() == 4;
    });
    test("Addition", [] {
        auto f = Fraction(1, 2) + Fraction(1, 3);
        return f.numerator() == 5 && f.denominator() == 6;
    });
    test("Zero denominator", [] {
        try
        {
            Fraction f(1, 0);
        }
        catch (const std::invalid_argument &)
        {
            return true;
        }
        return false;
    });
    test("Library output preserved", [] {
        std::ostringstream x, y;
        auto *old = std::cout.rdbuf(x.rdbuf());
        before::Library a;
        a.addBook({"A", "B"});
        a.displayBooks();
        std::cout.rdbuf(y.rdbuf());
        after::MemoryStorage s;
        after::EmailNotifier n;
        after::Library b(s, n);
        b.addBook({"A", "B"});
        b.displayBooks();
        std::cout.rdbuf(old);
        return x.str() == y.str();
    });
    test("Dependency injection", [] {
        struct S : after::IBookStorage
        {
            std::vector<after::Book> data;
            void save(const after::Book &b) override
            {
                data.push_back(b);
            }
            const std::vector<after::Book> &all() const override
            {
                return data;
            }
        } s;
        struct N : after::INotifier
        {
            int calls = 0;
            void notify(const after::Book &) override
            {
                ++calls;
            }
        } n;
        after::Library b(s, n);
        b.addBook({"A", "B"});
        return s.data.size() == 1 && n.calls == 1;
    });
    return failed ? 1 : 0;
}
