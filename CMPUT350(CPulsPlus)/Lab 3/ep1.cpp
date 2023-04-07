#include <iostream>
using namespace std;

class Expr {
public:
	Expr() {}
	virtual ~Expr() {}
	virtual int value() const = 0;

private:
	Expr(const Expr&) = delete;
	Expr& operator=(const Expr&) = delete;
};

class ConstExpr : public Expr
{
public:

	ConstExpr(int v)
		: f(v)
	{ }

	int value() const override
	{
		return f;
	}

private:
	int f;
};

class ParenExpr : public Expr
{
public:

	ParenExpr(Expr* v)
		: f((v->value()))
	{ }

	int value() const override
	{
		return f;
	}

private:
	int f;
};

class PlusExpr : public Expr
{
public:

	PlusExpr(Expr* v, Expr* n)
		: f(v->value() + n->value())
	{ }

	int value() const override
	{
		return f;
	}

private:
	int f;
};

class MinusExpr : public Expr
{
public:

	MinusExpr(Expr* v, Expr* n)
		: f(v->value() - n->value())
	{ }

	int value() const override
	{
		return f;
	}

private:
	int f;
};

class TimesExpr : public Expr
{
public:

	TimesExpr(Expr* v, Expr* n)
		: f(v->value()* n->value())
	{ }

	int value() const override
	{
		return f;
	}

private:
	int f;
};

class DivExpr : public Expr
{
public:

	DivExpr(Expr* v, Expr* n)
		: f(v->value() / n->value())
	{ }

	int value() const override
	{
		return f;
	}

private:
	int f;
};

int main() {
	Expr* A = new ConstExpr(5);   // 5
	Expr* B = new ConstExpr(3);   // 3
	Expr* C = new MinusExpr(A, B); // A->value()-B->value() = 2
	Expr* D = new ParenExpr(C);   // C->value() = 2  
	Expr* E = new ConstExpr(30);  // 30
	Expr* F = new TimesExpr(E, D); // E->value()*D->value() = 60
	Expr* G = new ConstExpr(10);  // 10
	Expr* H = new PlusExpr(G, F);  // G->value()+F->value() = 70
	Expr* I = new DivExpr(E, A); // E->value() / A->value() = 6

	cout << A->value() << " " << B->value() << " " << C->value() << " " << D->value() << " " << E->value() << " " << F->value() << " " << G->value() << " " << H->value() << " " << I->value() << endl;

	delete A; delete B; delete C; delete D; delete E; delete F; delete G; delete H; delete I;

	return 0;
}