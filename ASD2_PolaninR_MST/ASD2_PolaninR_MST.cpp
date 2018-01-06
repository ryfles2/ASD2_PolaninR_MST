#include <iostream>
#include <string>



using namespace std;
//struktura dla tablicy zawieraj¹cej opis krawêdzi
struct OpisKrawedzi
{
	//identyfikator wierzcho³ka 1
	long kraw_1;
	//identyfikator wierzcho³ka 2
	long kraw_2;
	//waga krawêdzi
	long waga;
};
struct IndexyFlagi
{
	//identyfikator indexu
	long index;
	//identyfikator flagi
	long flaga;
	//nazwa wierzcho³ka
	string nazwa;
};
class Mts
{
public:
	//konstruktor
	Mts();
	//destruktor
	~Mts();
	//dodawanie nazwy elementu do tablicy tabNazw_
	void AddWierz(string _nazwa, long _index);
	//dodawanie identyfikatora do tablicy tabIndexow_
	void AddWierz(long _identyfikator, long _index);
	//tworzenie tablicy o rozmia¿e size_
	void CreatetableWierz();
	//ustalanie rozmiaru tablicy
	void SizeWierz(long _size);
	//wyœwietlanie opisu
	void PrintOpis();

	//dodanie danych do tablicy typu 'OpisKrawedzi'  
	void AddKraw(long _index,long _kraw_1, long _kraw_2, long _waga);
	//tworzenie tablicy
	void CreatetableKraw();
	//ustalanie rozmiary tablicy
	void SizeKraw(long _size);
	//wyœwietlanie tablicy
	void PrintKraw();
	//szybkie sortowanie tablicy typu 'OpisKrawedzi'
	void QuickSort(long lewy, long prawy);
	//Minimalne drzewo rozpinaj¹ce
	void MST();
	//szuka w tablicy indexów krawêdzi
	long Zamiana(long numer);
	//ustawia flagi
	void Flaguj(long _flaga1,long _flaga2);

private:
	//deklarujemy tablice dynamiczn¹ na opis wierzcho³ków
	//rozmiar tablicy
	long sizeWierz_;
	
	//deklaracja wskaŸnika
	IndexyFlagi *tabIndexow_;

	//deklarujemy tablice dynamiczn¹ na opis krawedzi
	//rozmiar tablicy
	long sizeKraw_;
	//deklaracja wskaŸnika
	OpisKrawedzi *tabKrawedzi_;
};
//konstruktor
Mts::Mts()
{
	//nadawanie wartosci poczatkowych zmiennym
	sizeKraw_ = 0;
	sizeWierz_ = 0;
	tabIndexow_ = 0;
	tabKrawedzi_ = 0;
}
//destruktor
Mts::~Mts()
{
	//usuwanie tablicy dynamicznej
	delete[] tabIndexow_;
	delete[] tabKrawedzi_;
}
//dodawanie nazwy elementu do tablicy tabIndexow_
void Mts::AddWierz(string _nazwa, long _index)
{
	tabIndexow_[_index].nazwa = _nazwa;
}
//dodawanie identyfikatora do tablicy tabIndexow_
void Mts::AddWierz(long _identyfikator, long _index)
{
	tabIndexow_[_index].index = _identyfikator;
	tabIndexow_[_index].flaga = _identyfikator;
}
//tworzenie tablicy o rozmia¿e size_
void Mts::CreatetableWierz()
{
	//jeœli tablica ju¿ istnieje usuwamy j¹
	if (tabIndexow_)
	{
		delete[] tabIndexow_;
	}
	tabIndexow_ = new IndexyFlagi[sizeWierz_];
}
//ustalanie rozmiaru tablicy
void Mts::SizeWierz(long _size)
{
	sizeWierz_ = _size;
	
}
//wyœwietlanie opisu tabIndexow_ i tabNazw_
void Mts::PrintOpis()
{
	for (int i = 0; i < sizeWierz_; i++)
	{
		cout << tabIndexow_[i].index << " " << tabIndexow_[i].nazwa << endl;
	}
}
//dodanie danych do tablicy typu 'OpisKrawedzi'  
void Mts::AddKraw(long _index, long _kraw_1, long _kraw_2, long _waga)
{
	tabKrawedzi_[_index].kraw_1 = _kraw_1;
	tabKrawedzi_[_index].kraw_2 = _kraw_2;
	tabKrawedzi_[_index].waga = _waga;
}
//tworzenie tablicy
void Mts::CreatetableKraw()
{
	if (tabKrawedzi_)
	{
		delete[] tabKrawedzi_;
	}
	tabKrawedzi_ = new OpisKrawedzi[sizeKraw_];

}
//ustalanie rozmiary tablicy
void Mts::SizeKraw(long _size)
{
	sizeKraw_ = _size;
}
//wyœwietlanie tablicy
void Mts::PrintKraw()
{
	for (int i = 0; i < sizeKraw_; i++)
	{
		cout << tabKrawedzi_[i].kraw_1 << " " << tabKrawedzi_[i].kraw_2<<" "<< tabKrawedzi_[i].waga << endl;
	}
}
//szybkie sortowanie tablicy typu 'OpisKrawedzi' (quick sort dla w³asnego typu danych "po mojemu")
void Mts::QuickSort(long lewy, long prawy)
{
	long i, j, piwot, piwot_1, piwot_2;
	
	i = (lewy + prawy) / 2;
	piwot = tabKrawedzi_[i].waga;
	piwot_1 = tabKrawedzi_[i].kraw_1;
	piwot_2 = tabKrawedzi_[i].kraw_2;

	tabKrawedzi_[i].waga = tabKrawedzi_[prawy].waga;
	tabKrawedzi_[i].kraw_1 = tabKrawedzi_[prawy].kraw_1;
	tabKrawedzi_[i].kraw_2 = tabKrawedzi_[prawy].kraw_2;

	for (j = i = lewy; i < prawy; i++)
	{
		if (tabKrawedzi_[i].waga< piwot)
		{
			swap(tabKrawedzi_[i].kraw_1, tabKrawedzi_[j].kraw_1);
			swap(tabKrawedzi_[i].kraw_2, tabKrawedzi_[j].kraw_2);
			swap(tabKrawedzi_[i].waga, tabKrawedzi_[j].waga);
			j++;
		}
	}
	tabKrawedzi_[prawy].waga = tabKrawedzi_[j].waga;
	tabKrawedzi_[prawy].kraw_1 = tabKrawedzi_[j].kraw_1;
	tabKrawedzi_[prawy].kraw_2 = tabKrawedzi_[j].kraw_2;

	
	tabKrawedzi_[j].waga = piwot;
	tabKrawedzi_[j].kraw_1 = piwot_1;
	tabKrawedzi_[j].kraw_2 = piwot_2;
	if (lewy < j - 1)
	{
		QuickSort(lewy, j - 1);
	}
	if (j + 1 < prawy)
	{
		QuickSort(j + 1, prawy);
	}

}
//Minimalne drzewo rozpinaj¹ce
void Mts::MST()
{
	long pom_1 = 0;
	long pom_2 = 0;

	//testowe wyœwietlanie flag
	/*for (int i = 0; i < sizeWierz_; i++)
	{
		cout << tabIndexow_[i].nazwa << " flaga = " << tabIndexow_[i].flaga << endl;
	}
	cout << endl;*/
	for (long i = 0; i < sizeKraw_; i++)
	{
		pom_1 = Zamiana(tabKrawedzi_[i].kraw_1);
		pom_2 = Zamiana(tabKrawedzi_[i].kraw_2);
		if (tabIndexow_[pom_1].flaga != tabIndexow_[pom_2].flaga)
		{
			cout << tabIndexow_[pom_1].nazwa << " ";
			cout << tabIndexow_[pom_2].nazwa << " ";
			cout << tabKrawedzi_[i].waga << endl;

			if (tabIndexow_[pom_1].flaga < tabIndexow_[pom_2].flaga)
			{
				Flaguj(tabIndexow_[pom_1].flaga, tabIndexow_[pom_2].flaga);
			}
			else
			{
				Flaguj(tabIndexow_[pom_2].flaga, tabIndexow_[pom_1].flaga);
			}

		}
	}
	//testowe wyœwietlanie flag
	/*for (int i = 0; i < sizeWierz_; i++)
	{
		cout << tabIndexow_[i].nazwa << " flaga = " << tabIndexow_[i].flaga << endl;
	}
	cout << endl;*/
}
//zamiana identyfikatora na nazwê
long Mts::Zamiana(long numer)
{
	for (long x = 0; x < sizeWierz_; x++)
	{
		if (tabIndexow_[x].index == numer)
		{
			return x;
		}
	}
	return 0;
}

void Mts::Flaguj(long _flaga1, long _flaga2)
{
	for (long x = 0; x < sizeWierz_; x++)
	{
		if (tabIndexow_[x].flaga == _flaga2)
		{
			tabIndexow_[x].flaga = _flaga1;
		}
	}
}





int main()
{
	Mts mts;
	long liczbaWierz = 0;
	cin >> liczbaWierz;
	mts.SizeWierz(liczbaWierz);
	mts.CreatetableWierz();

	long identyfikator = 0;
	string nazwa;
	
	for (long i = 0; i < liczbaWierz; i++)
	{
		cin >> identyfikator;
		cin >> nazwa;
		mts.AddWierz(identyfikator,i);
		mts.AddWierz(nazwa,i);
	}
	//mts.PrintOpis();

	long liczbaKraw = 0;
	cin >> liczbaKraw;
	mts.SizeKraw(liczbaKraw);
	mts.CreatetableKraw();
	long kraw_1 = 0;
	long kraw_2 = 0;
	long waga = 0;

	for (long i = 0; i < liczbaKraw; i++)
	{
		cin >> kraw_1;
		cin >> kraw_2;
		cin >> waga;
		mts.AddKraw(i, kraw_1, kraw_2, waga);
	}

	//mts.PrintKraw();
	mts.QuickSort(0, liczbaKraw-1);
	//cout << endl;
	//mts.PrintKraw();
	mts.MST();


	return 0;
}