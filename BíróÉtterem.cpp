#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;


struct Alap {
	public:
		int kod;
		int db;
};

vector<vector<Alap>> Beolvasas_Konzolrol();
void Beolvasas_Diagnosztika(vector<vector<Alap>>);
vector<Alap> Feldolgozas(vector<vector<Alap>>);
void GyorsRendezes(vector<int>& , int, int);
void Csere(int* i, int* j) { int temp = *i; *i = *j; *j = temp; }
void Kimenet_Kiirasa(vector<Alap>);
int Int_bekerese(string, int, int);

int main()
{
	// Deklarációk

	vector<vector<Alap>> matrix;
	vector<Alap> kimenet;

	// Beolvasás
	matrix = Beolvasas_Konzolrol();

	// Beolvasás ellenőrzése
//	Beolvasas_Diagnosztika(matrix);

	// Feldolgozás
	kimenet = Feldolgozas(matrix);

	Kimenet_Kiirasa(kimenet);

}


vector<vector<Alap>> Beolvasas_Konzolrol()
{
	int N, Alap_db;
	Alap alapanyag;
	vector<Alap> sor;
	vector<vector<Alap>> result;
	N = Int_bekerese("Adja meg az etkezesek szamat!", 1, 100);
	for (int i = 0; i < N; i++)
	{
		sor.clear();
		Alap_db = Int_bekerese("A kovetkezo etel alapanyagainak a szama ", 0, 100);
		for (int j = 0; j < Alap_db; j++)
		{
			alapanyag.kod = Int_bekerese("  A kovetkezo alapanyag kodja ", 1, 100000);
			alapanyag.db = Int_bekerese("  Ennek a mennyisege ", 1, 100000);
			sor.push_back(alapanyag);
		}
		result.push_back(sor);
	}
	return result;
}

bool Tartalmaz(int keresendo, vector<int> lista)
{
	for (int elem : lista)
	{
		if (elem == keresendo)
			return true;
	}
	return false;
}

void Beolvasas_Diagnosztika(vector<vector<Alap>> matrix)
{
	cout << "igy neznek ki a bejott adatok:" << endl;
	
	for (vector<Alap> sor : matrix)
	{
		for (Alap adat: sor)
		{
			cout << "(" << adat.kod << ";" << adat.db << ") ";
		}
		cout << endl;
	}
}

vector<Alap> Feldolgozas(vector<vector<Alap>> matrix)
{
	map<int, int> nyilvantartas;
	vector<int> alapanyagkodok;
	vector<Alap> result;
	
	for (vector<Alap> sor : matrix)
	{
		for (Alap elem : sor)
		{
			if (Tartalmaz(elem.kod, alapanyagkodok))
				nyilvantartas[elem.kod] += elem.db;
			else
			{
				nyilvantartas.insert(pair<int, int>{elem.kod, elem.db});
				alapanyagkodok.push_back(elem.kod);
			}
		}
	}

	GyorsRendezes(alapanyagkodok, 0, alapanyagkodok.size()-1);

	size_t meret = alapanyagkodok.size();

	Alap a;
	for (int e: alapanyagkodok)
	{
		a.kod = e;
		a.db = nyilvantartas[e];
		if (a.db != 0) // elméletileg egyébként sem jöhet be ilyen adat, de a Bíró így kéri/így ad adatot!
			result.push_back(a);
	}

	return result;
}


void GyorsRendezes(vector<int>& L, int e, int v)
{
	if (e<v) 
	{
		int i = e;
		int j = v;
		while (i!=j)
		{
			if ((i<j)!= L[i]<L[j]) // ha az indexek sorrendje nem egyezik meg az értékek sorrendjével...
			{
				swap(L[i], L[j]); // ... akkor az értékeket cserélni kell  ÉS ...
				swap(i, j); // ... az indexeket is velük kell cserélni
			}
			j += i - j > 0 ? 1 : -1; // és j-t az i felé kell mozgatni.
		}
		GyorsRendezes(L, e, i - 1);
		GyorsRendezes(L, i+1, v);
	}
}


void Kimenet_Kiirasa(vector<Alap> lista)
{
	cout << "Tehat osszesen "<< lista.size() << "-fele alapanyag volt:" << endl;
	for(Alap a : lista)
	{ 
		cout << "  a " << a.kod << " kodubol " << a.db << " egyseg. "<< endl;
	}
}

int Int_bekerese(string keres, int a, int f)
{
	string nyers;
	int result ;
	cout << keres;
	cout << " (" << a << " <= X <= " << f << "): ";

	bool szame = false;
	bool jo = false;

	do
	{
		cin >> nyers;

		try
		{
			result = stoi(nyers);
			szame = true;
		}
		catch (...)
		{
			cout << " HIBA! Nem egesz szamot adott meg. Probalkozzon ujra!\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			szame = false;
		}

		if (szame)
		{
			if (result < a)
				cout << " HIBA! Tul kicsi szamot adott meg. Probalkozzon ujra!\n";
			else if (result > f)
				cout << " HIBA! Tul nagy szamot adott meg. Probalkozzon ujra!\n";
			else jo = true;
		}
	}
	while (!jo);
	return result;
}



