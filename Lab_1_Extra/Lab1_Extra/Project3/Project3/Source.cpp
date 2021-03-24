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

	void insertTerm(const Term& term);
	void insertTerm(double coeff, int exp);
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
void Polynomial::insertTerm(const Term& term) {
	// STUDENT ANSWER
	if (this->terms->size() == 0 && term.coeff != 0) this->terms->add(term);
	else if (term.coeff != 0) {
		int i = 0;
		bool t = 0;
		for (SLinkedList<Term>::Iterator it = this->terms->begin(); it != this->terms->end(); it++) {
			Term tmp = this->terms->get(i);
			if (tmp.exp == term.exp) {
				tmp.coeff += term.coeff;
				if (tmp.coeff == 0) { it.remove(); i--; }
				else it.set(tmp);
				t = 1;
			}
			i++;
		}
		if (t == 0) this->terms->add(term);
	}
	for (int i = 0; i < this->terms->size(); i++) {
		for (int j = i + 1; j < this->terms->size(); j++) {
			Term a = this->terms->get(i);
			Term b = this->terms->get(j);
			if (b.exp > a.exp) {
				this->terms->set(j, a);
				this->terms->set(i, b);
			}
		}
	}
}

void Polynomial::insertTerm(double coeff, int exp) {
		// STUDENT ANSWER
		Term term(coeff, exp);
		this->insertTerm(term);
	}
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