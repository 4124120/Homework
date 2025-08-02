#include <iostream>
#include <cmath>
using namespace std;

class Term;

class Polynomial;

class Term {
    friend class Polynomial;
    friend ostream& operator<<(ostream&, Polynomial&);
    friend istream& operator>>(istream&, Polynomial&);

private:
    int coef;
    int exp;
    Term* link;
};

class Polynomial {
private:
    Term* head;

    void Attach(int coef, int exp) {
        Term* newTerm = new Term;
        newTerm->coef = coef;
        newTerm->exp = exp;
        newTerm->link = nullptr;

        Term* curr = head;
        while (curr->link && curr->link->exp > exp)
            curr = curr->link;

        newTerm->link = curr->link;
        curr->link = newTerm;
    }

public:
    Polynomial() {
        head = new Term;
        head->link = nullptr;
    }

    Polynomial(const Polynomial& a) {
        head = new Term;
        head->link = nullptr;
        Term* curr = a.head->link;
        while (curr) {
            Attach(curr->coef, curr->exp);
            curr = curr->link;
        }
    }

    ~Polynomial() {
        Term* curr = head;
        while (curr) {
            Term* temp = curr;
            curr = curr->link;
            delete temp;
        }
    }

    const Polynomial& operator=(const Polynomial& a) {
        if (this == &a) return *this;

        this->~Polynomial();
        head = new Term;
        head->link = nullptr;

        Term* curr = a.head->link;
        while (curr) {
            Attach(curr->coef, curr->exp);
            curr = curr->link;
        }
        return *this;
    }

    float Evaluate(float x) const {
        float result = 0.0;
        Term* curr = head->link;
        while (curr) {
            result += curr->coef * pow(x, curr->exp);
            curr = curr->link;
        }
        return result;
    }

    Polynomial operator+(const Polynomial& b) const {
        Polynomial result;
        Term* aTerm = this->head->link;
        Term* bTerm = b.head->link;

        while (aTerm && bTerm) {
            if (aTerm->exp == bTerm->exp) {
                int sum = aTerm->coef + bTerm->coef;
                if (sum != 0) result.Attach(sum, aTerm->exp);
                aTerm = aTerm->link;
                bTerm = bTerm->link;
            } else if (aTerm->exp > bTerm->exp) {
                result.Attach(aTerm->coef, aTerm->exp);
                aTerm = aTerm->link;
            } else {
                result.Attach(bTerm->coef, bTerm->exp);
                bTerm = bTerm->link;
            }
        }

        while (aTerm) {
            result.Attach(aTerm->coef, aTerm->exp);
            aTerm = aTerm->link;
        }

        while (bTerm) {
            result.Attach(bTerm->coef, bTerm->exp);
            bTerm = bTerm->link;
        }

        return result;
    }

    Polynomial operator-(const Polynomial& b) const {
        Polynomial negB;
        Term* bTerm = b.head->link;
        while (bTerm) {
            negB.Attach(-bTerm->coef, bTerm->exp);
            bTerm = bTerm->link;
        }
        return *this + negB;
    }

    Polynomial operator*(const Polynomial& b) const {
        Polynomial result;
        for (Term* aTerm = head->link; aTerm; aTerm = aTerm->link) {
            Polynomial temp;
            for (Term* bTerm = b.head->link; bTerm; bTerm = bTerm->link) {
                temp.Attach(aTerm->coef * bTerm->coef, aTerm->exp + bTerm->exp);
            }
            result = result + temp;
        }
        return result;
    }

    friend istream& operator>>(istream& is, Polynomial& x) {
        int n, coef, exp;
        is >> n;
        for (int i = 0; i < n; ++i) {
            is >> coef >> exp;
            x.Attach(coef, exp);
        }
        return is;
    }

    friend ostream& operator<<(ostream& os, Polynomial& x) {
        Term* curr = x.head->link;
        if (!curr) return os << "0";
        bool first = true;
        while (curr) {
            if (!first && curr->coef > 0)
                os << " + ";
            else if (curr->coef < 0)
                os << " - ";

            if (abs(curr->coef) != 1 || curr->exp == 0)
                os << abs(curr->coef);
            if (curr->exp != 0) {
                os << "x";
                if (curr->exp != 1)
                    os << "^" << curr->exp;
            }

            first = false;
            curr = curr->link;
        }
        return os;
    }
};

