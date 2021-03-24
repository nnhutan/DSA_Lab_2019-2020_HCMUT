#include "Header.h"
#include <iostream>
#include <string>
#include <sstream>
#include <assert.h>
using namespace std;
class Polynomial;

class Term {
private:
    double coeff;
    int exp;
    friend class Polynomial;

public:
    Term(double coeff = 0.0, int exp = 0) {
        this->coeff = coeff;
        this->exp = exp;
    }

    bool operator==(const Term& rhs) const {
        return this->coeff == rhs.coeff && this->exp == rhs.exp;
    }

    friend ostream& operator<<(ostream& os, const Term& term) {
        cout << endl;
        cout << "Term: " << "(" << term.coeff << " " << term.exp << ")";
        return os;
    }
};

class Polynomial {
private:
    SLinkedList<Term>* terms;

public:
    Polynomial() {
        this->terms = new SLinkedList<Term>();
    }

    ~Polynomial() {
        this->terms->clear();
    }

    void insertTerm(const Term& term) {
        this->terms->add(term);
    }
    void insertTerm(double coeff, int exp) {
        Term term(coeff, exp);
        insertTerm(term);
    }
    // Polynomial operator+(const Polynomial& rhs);

    void print() {
        SLinkedList<Term>::Iterator it;
        cout << "[";
        for (it = this->terms->begin(); it != this->terms->end(); it++) {
            cout << (*it);
        }
        cout << endl << "]";
    }
};
int main() {
    Polynomial* poly = new Polynomial();
    poly->insertTerm(6.0, 2);
    poly->insertTerm(4.0, 5);
    poly->insertTerm(4.0, 3);
    poly->insertTerm(6.0, 5);
    poly->insertTerm(-1.0, 0);
    poly->insertTerm(-6.0, 6);
    poly->insertTerm(6.0, 6);
    poly->print();
}