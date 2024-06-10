# Symulacja Życia

## Budowa projektu

```sh
	cd symulacjazycia
	mkdir build
	cd build
	cmake ..
	make
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

#### wymagania: Row<T>

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

#### wymagania: Rows<T>

Sąsiedztwo pobiera położenie niszy otaczające wskazaną niszę.

Klasa zwraca szczególną uwagę aby nie pobrać informacji nie należącej do
instancji `Rows<T>`.

Próba dostępu do pozycji spoza Rows<T> skutkuje w `std::rangeError`.
Algorytm tworzenie sąsiedztwa jest zbytecznie skomplikowany, ale nie mogłem wymyślić lepszego.

### std::optional<T>

#### plik: <optional>

Klasa optional może zawierać T lub std::nullopt.
Używana jest w `Cell` ponieważ jej konstrukcja nie wymaga kolejnej alokacji na stercie.

## Klasy

### RandomGenerator - Generator liczb pseudolosowych

#### plik: RandomGenerator.h

Generator to klasa singelton, która posiada tylko i wyłącznie jedną instancję
klasy std::random_device jako parametr. `RandomGenerator` eksponuje funkcje związane z
generacją funkcji losowych.

### Simulation - Symulacja

#### plik: SymulacjaZycia.cpp

#### wymagania: Grid

Symulacja zawiera `Grid` i zarządza działaniem symulacji.
Szczególnie rozpoczęciem i zakończeniem symulacji.

### Grid - Siatka

#### plik: Grid.h

#### wymagania: Rows<T>, Cell

Siatka zawiera tablicę dwuwymiarowa `Rows`, która zawiera instancje `Cell`.
Siatka przekazuje do `Cell` jej `Vicinity`.

### Cell - Nisza

#### plik: Grid.h

#### wymagania: Organism, std::optional

Nisza zawiera `Organism` lub nic(std::nullopt_t).
Nisza jest główną klasą która w pełni zarządza `Organism`.
Na podstawie podanego `Vicinity` `Cell` wykonuje krok symulacji.

### Organism - Organizm

#### plik: Organism.h

Organizm to klasa, która zawiera dane organizmu
i eksponuje je w sposób przystosowany do działania Symulacji.
