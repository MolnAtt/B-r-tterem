#include <iostream>
#include <vector>
#include <map>
using namespace std;


struct Alap {
	public:
		int kod;
		int db;
};

vector<vector<Alap>> Beolvasas_Konzolrol();
void Beolvasas_Diagnosztika(vector<vector<Alap>> matrix);
vector<Alap> Feldolgozas(vector<vector<Alap>> matrix);
void GyorsRendezes(vector<int>& L, int e, int v);
void Csere(int* i, int* j) { int temp = *i; *i = *j; *j = temp; }
void Kimenet_Kiirasa(vector<Alap> lista);

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
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		sor.clear();
		cin >> Alap_db;
		for (size_t j = 0; j < Alap_db; j++)
		{
			cin >> alapanyag.kod;
			cin >> alapanyag.db;
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
		if (a.db != 0)
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
			if ((i<j)!= L[i]<L[j])
			{
				swap(L[i], L[j]);
				swap(i, j);
			}
			j += i - j > 0 ? 1 : -1;
		}
		GyorsRendezes(L, e, i - 1);
		GyorsRendezes(L, i+1, v);
	}
}


void Kimenet_Kiirasa(vector<Alap> lista)
{
	cout << lista.size() << endl;
	for(Alap a : lista)
	{ 
		cout << a.kod << " " << a.db << endl;
	}
}



