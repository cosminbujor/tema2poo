#include <iostream>
using namespace std;

class Nod {
protected:
	char info;
	Nod* next;

public:
	Nod();
	Nod(char info1, Nod* next1);
	Nod(const Nod& n);
	~Nod();
	Nod & operator=(const Nod& n);
	friend ostream& operator<<(ostream& o, const Nod& n);
	friend istream& operator>>(istream& i, Nod& n);
	friend class Coada;
	friend class DEQUE;
};

class Coada
{
protected:
	Nod* prim;
	Nod* ultim;
	int dim_max;

public:
	friend istream& operator>>(istream& i, Coada &c);
	virtual void push(char x);
	virtual void pop();
	virtual void afis();

	Coada();
	Coada(int dim_max1, Nod* prim1, Nod* ultim1);
	Coada(const Coada& c);
	~Coada();
	Coada & operator=( Coada c);
};

class DEQUE : public Coada
{
public:
	DEQUE():Coada(){}
	DEQUE(int dim_max1, Nod* prim1, Nod* ultim1):Coada(dim_max1, prim1, ultim1) {}
	DEQUE(const DEQUE& d):Coada(d){}
	~DEQUE();
	friend istream& operator>>(istream& i, DEQUE& d);
	void push(char val);
	DEQUE& operator=(const DEQUE& d);
	void pop();
	void afis();
};

Nod::Nod()
{
	info = '\0';
	next = NULL;
}
Nod::Nod(char info1, Nod* next1)
{
	info = info1;
	next = next1;
}
Nod::Nod(const Nod& n)
{
	this->info = n.info;
	this->next = n.next;
}
ostream& operator<<(ostream& o, const Nod& n)
{
	o << "info = " << n.info;
	return o;
}
istream& operator>>(istream& i, Nod& n)
{
	i >> n.info;
	return i;
}
Nod::~Nod()
{
}
Nod & Nod::operator=(const Nod& n)
{
	this->next = n.next;
	this->info = n.info;
	return *this;
}




Coada::Coada()
{
	dim_max = 0;
	prim = NULL;
	ultim = NULL;
}
Coada::Coada(int dim_max1, Nod* prim1, Nod* ultim1)
{
	dim_max = dim_max1;
	prim = prim1;
	ultim = ultim1;
}
Coada::Coada(const Coada& c)
{
	dim_max = c.dim_max;
	prim = NULL;
	Nod* nou = c.prim;
	while (nou != NULL)
	{
		this->push(nou->info);
		if (nou == c.ultim)
			break;
		nou = nou->next;
	}
	ultim = nou;
}
void Coada::afis()
{
	if (prim == NULL)
		cout << "Coada e goala." << endl;

	else
	{

		Nod* nou = prim;

		while (nou != NULL) {
			cout << nou->info << ' ';
			nou = nou->next;
		}
	}
}
Coada::~Coada()
{
}
istream& operator>>(istream & i, Coada&  c)
{
	cout << "Numarul de caractere ale cozii:";
	int n;
	i >> n;
	char caracter;

	for (int k = 0; k < n; k++)
	{
		i >> caracter;
		c.push(caracter);
	}

	return i;

}
void Coada::push(char x) {

	if (prim == NULL) {
		prim = new Nod;
		prim->info = x;
		prim->next = NULL;
		ultim = prim;
	}

	else {
		Nod* nou;
		nou = new Nod;
		nou->info = x;
		nou->next = NULL;
		ultim->next = nou;
		ultim = nou;
	}
}
void Coada::pop()
{

	if (prim == NULL)
			cout << "Coada e goala.";

		else
		{

		Nod* nou = prim;
		nou->next = prim->next;
		prim=prim->next;
		delete nou;
		}
}
Coada & Coada:: operator=( Coada c)
{
	this->prim = c.prim;
	this->ultim = c.ultim;
	this->dim_max = c.dim_max;
	return *this;
}




void DEQUE::afis()
{

		if (prim == NULL)
			cout << "Coada  DEQUE e goala." << endl;

		else
		{

			Nod* nou = prim;

			while (nou != NULL) {
				cout << nou->info << ' ';
				nou = nou->next;
			}
		}
}
DEQUE::~DEQUE()
{
}
DEQUE & DEQUE::operator=(const DEQUE& d)
{
	this->prim = d.prim;
	this->ultim = d.ultim;
	this->dim_max = d.dim_max;
	return *this;
}
void DEQUE::push(char val)
{
	int choice;
	cout << "1.INCEPUT\n2.SFARSIT\n";
	cin >> choice;
	switch (choice)
	{

	case 2:
	{
		if (prim == NULL) {
			prim = new Nod;
			prim->info = val;
			prim->next = NULL;
			ultim = prim;
		}

		else {
			Nod* nou;
			nou = new Nod;
			nou->info = val;
			nou->next = NULL;
			ultim->next = nou;
			ultim = nou;
		}
		break;
	}
	case 1:
	{
		Nod* p = new Nod;
		p->info = val;
		if (prim == NULL)
		{
			prim = p;
			ultim = p;
			ultim->next= NULL;
		}
		else
		{
			p->next = prim;
			prim = p;
		}
		break;
	}
	default:
	{
		cout << "Eroare\n";
		break;
	}
	}
}
istream& operator>>(istream& i, DEQUE& d)
{
	int choice, dim;
	char val;

	cout << "Cate noduri vrei sa aiba coada ?";
	i >> dim;
	for (int i = 0; i < dim; i++)
	{
		cout << "Introdu valoare nodului " << i + 1 << ":";

		cin >> val;

		d.push(val);
	}
	return i;
}
void DEQUE::pop()
{
	int choice;
	cout << "1.STERG INCEPUT\n2.STERG SFARSIT\n";
	cin >> choice;
	switch (choice)
	{

	case 1:
	{
		if (prim == NULL)
			cout << "Coada  DEQUE e goala.";

		else {
			Nod* nou = prim;
			nou->next = prim->next;
			prim = prim->next;

			delete nou;

		}
		break;
	}
	case 2:
	{
		if (prim == NULL)
			cout << "Coada e goala.";

		else {
			Nod* nou = prim;
			while(nou->next->next!=NULL)
				nou = nou->next;
			nou->next = NULL;

		}
		break;
	}
	default:
	{
		cout << "Eroare\n";
		break;
	}
	}
}
int main()
{
	cout << "Tastati 1 pentru citire coada.\n";
	cout << "Tastati 2 pentru push coada.\n";
	cout << "Tastati 3 pentru pop coada.\n";
	cout << "Tastati 4 pentru afisare coada.\n";
	cout << "Tastati 2 pentru push coada.\n";
	cout << "Tastati 5 pentru citire DEQUE.\n";
	cout << "Tastati 6 pentru push DEQUE.\n";
	cout << "Tastati 7 pentru pop DEQUE.\n";
	cout << "Tastati 8 pentru afisare DEQUE.\n";

	Coada c,e;
	DEQUE d;

		int cerinta;
	cout << endl << "Alege cerinta:" << endl;
	cin >> cerinta;


	do
	{

		switch (cerinta) {

		case 1:
		{

			cin >> c;
			break;
		}
		case 2:
		{
			cout << "Adaugam elementul cu valoarea:";
			char x;
			cin >> x;
			c.push(x);
			cout << "Am adaugat " << x << " la finalul cozii.";
			break;
		}
		case 3:
		{
			c.pop();
			cout << "Am apelat functia pop.";
			break;
		}

		case 4:
		{
			cout << "Coada este ";
			c.afis();
			break;
		}
		case 5:
		{

			cin >> d;
			break;
		}
		case 6:
		{
			cout << "Adaugam elementul cu valoarea:";
			char x;
			cin >> x;
			d.push(x);
			cout << "Am adaugat " << x << " .";
			break;
		}
		case 7:
		{	cout << "Stergem." << endl;
			d.pop();
			break;
		}

		case 8:
		{
			cout << "Coada DEQUE este ";
			d.afis();
			break;
		}
		default:
		{
			break;
		}
		}
		cout << endl;
		cout << "Alege cerinta:" << endl;
		cin >> cerinta;
	} while (cerinta >= 1 && cerinta <= 8);


	return 0;
}
