// Polynomial.cpp
#include <iostream>
#include <cmath>
using namespace std;

class Term {
public:
    float coef;
    int exp;
};

class Polynomial {
private:
    Term* termArray;
    int capacity;
    int terms;

    void NewTerm(float c, int e);

public:
    Polynomial(int cap = 10);
    ~Polynomial();

    Polynomial Add(Polynomial b);
    Polynomial Mult(Polynomial b);
    float Eval(float f);

    friend istream& operator>>(istream& in, Polynomial& p);
    friend ostream& operator<<(ostream& out, Polynomial& p);
};

// ====== Implementation ======

Polynomial::Polynomial(int cap) {
    capacity = cap;
    terms = 0;
    termArray = new Term[capacity];
}

Polynomial::~Polynomial() {
    delete[] termArray;
}

void Polynomial::NewTerm(float c, int e) {
    if (terms == capacity) {
        capacity *= 2;
        Term* temp = new Term[capacity];
        for (int i = 0; i < terms; ++i)
            temp[i] = termArray[i];
        delete[] termArray;
        termArray = temp;
    }
    termArray[terms].coef = c;
    termArray[terms++].exp = e;
}

Polynomial Polynomial::Add(Polynomial b) {
    Polynomial c;
    int aPos = 0, bPos = 0;
    while (aPos < terms && bPos < b.terms) {
        if (termArray[aPos].exp == b.termArray[bPos].exp) {
            float sum = termArray[aPos].coef + b.termArray[bPos].coef;
            if (sum != 0)
                c.NewTerm(sum, termArray[aPos].exp);
            aPos++, bPos++;
        } else if (termArray[aPos].exp > b.termArray[bPos].exp) {
            c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        } else {
            c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
            bPos++;
        }
    }

    for (; aPos < terms; aPos++)
        c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
    for (; bPos < b.terms; bPos++)
        c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
    return c;
}

Polynomial Polynomial::Mult(Polynomial b) {
    Polynomial c;
    for (int i = 0; i < terms; i++) {
        for (int j = 0; j < b.terms; j++) {
            float coef = termArray[i].coef * b.termArray[j].coef;
            int exp = termArray[i].exp + b.termArray[j].exp;
            bool found = false;

            for (int k = 0; k < c.terms; k++) {
                if (c.termArray[k].exp == exp) {
                    c.termArray[k].coef += coef;
                    found = true;
                    break;
                }
            }
            if (!found) c.NewTerm(coef, exp);
        }
    }
    return c;
}

float Polynomial::Eval(float f) {
    float result = 0;
    for (int i = 0; i < terms; i++) {
        result += termArray[i].coef * pow(f, termArray[i].exp);
    }
    return result;
}

istream& operator>>(istream& in, Polynomial& p) {
    cout << "Enter number of terms: ";
    in >> p.terms;
    p.termArray = new Term[p.terms];
    for (int i = 0; i < p.terms; i++) {
        cout << "Enter coef and exp: ";
        in >> p.termArray[i].coef >> p.termArray[i].exp;
    }
    return in;
}

ostream& operator<<(ostream& out, Polynomial& p) {
    for (int i = 0; i < p.terms; i++) {
        out << p.termArray[i].coef << "x^" << p.termArray[i].exp;
        if (i != p.terms - 1)
            out << " + ";
    }
    return out;
}

