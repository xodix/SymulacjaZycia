# Symulacja Życia

## Budowa projektu

```sh
	mkdir symulacjazycia
	cd symulacjazycia
	cmake -DCMAKE_BUILD_TYPE=Release ..
	cmake --build .
```

## Wykonywanie testów (po budowie)

```sh
	ctest
```

## Uruchomianie Projektu

### Losowe rozłożenie ekosystemu

```sh
	./SymulacjaZycia
```

### Rozłożenie ekosystemu pobrane z "plik.txt"

```sh
	./SymulacjaZycia plik.txt
```

## Struktury danych

### Rows<T> - tablica dwuwymiarowa

#### plik: Rows.h

Własna implementacja tablicy "dwuwymiarowej".

Rows<T> przechowuje dane w tablicy jednowymiarowej
i eksponuje funkcje i przeciążenia operatorów, które pomagają użytkownikowi traktować
tą klasę jake tablicę dwuwymiarową zachowując cache locality.

Aby uzyskać jeden rząd tablicy "dwuwymiarowej" należy ponownie użyć operatora[].

### Row<T> - jeden rząd w tablicy dwuwymiarowej

#### plik: Rows.h

Rząd uzyskuje się po użyciu operatora[] na klasie `Rows<T>`.
Klasa ta eksponuje wycinek jednowymiarowej tablicy (rząd), który ma wielkość RowLen.

Aby uzyskać wartość `T` należy ponownie użyć operatora[]

### Vicinity<T> - Sąsiedztwo

#### plik: Vicinity.h

Sąsiedztwo pobiera nisze otaczające wskazaną niszę.

Klasa zwraca szczególną uwagę aby nie pobrać informacji nie należącej do
instancji `Rows<T>`.

Próba dostępu do pozycji spoza `Rows<T>` skutkuje w `std::range_error`.

### std::optional<T>

#### plik: \<optional\>

Klasa optional może zawierać T lub std::nullopt.
Używana jest w `Cell` ponieważ jej konstrukcja nie wymaga kolejnej alokacji na stercie.
Dodatkowo lepiej wskazuje intencję parametru m_contents niż wskaźnik.

## Klasy

### RandomGenerator - Generator liczb pseudolosowych

#### plik: RandomGenerator.h

Generator to klasa singelton, która posiada tylko i wyłącznie jedną instancję
klasy `std::random_device` jako parametr. `RandomGenerator` eksponuje funkcje związane z
generacją funkcji losowych.

### Simulation - Symulacja

#### plik: SymulacjaZycia.cpp

Symulacja zawiera `Grid` i zarządza działaniem symulacji.
Szczególnie rozpoczęciem i zakończeniem symulacji.
Dodatkowo przekazuje stan ekosystemu użytkownikowi programu.

### Grid - Siatka

#### plik: Grid.h

Siatka zawiera tablicę dwuwymiarowa `Rows`, która zawiera instancje `Cell`.
Siatka przekazuje do `Cell` jej `Vicinity`.

### Cell - Nisza

#### plik: Grid.h

Nisza zawiera `Organism` lub nic(`std::nullopt_t`).
Nisza jest główną klasą która w pełni zarządza jej instancją `Organism`.
Na podstawie podanego `Vicinity` `Cell` wykonuje krok symulacji.

### Organism - Organizm

Organizm to klasa, która zawiera dane organizmu
i eksponuje je w sposób przystosowany do działania Symulacji.
Modyfikacja i przeglądanie danych organizmu jest ograniczone
za pomocą funkcji getter i setter np. organizm może zostać postarzony
o tylko jeden krok symulacji i nakarmiony tylko jednym pokarmem.

## Możliwe drogi rozwoju

### Własny system IO

System IO posiada kilka wad:

1. std::stringstream nie ma łatwej opcji korzystania z prealokowanego buforu
2. std::cout << std::stringstream zajmuje aż 85% działania symulacji.

Rozwiązaniem byłby własny system io który przechowywałby całą reprezentację tekstową ekosystemu
i używałby niskopoziomowych funkcji do pisania stdout

### Wielowątkowość

Wielowątkowość jest w tym przypadku ciężka i nieefektywna do zastosowania.
Jedna nisza potrafi zmienić swoje sąsiedztwo co wpływa na następne.

W "Game of live" jedna komórka jest bytem, który tylko i wyłącznie czyta swoje otoczenie.
Dlatego algorytm tej symulacji łatwo można rozbić na wiele wątków. A tego programu nie.
