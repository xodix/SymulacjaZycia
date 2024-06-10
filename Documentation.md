# Symulacja �ycia

## Budowa projektu

```sh
	cd symulacjazycia
	mkdir build
	cd build
	cmake ..
	make
```

## Wykonywanie test�w (po budowie)

```sh
	ctest
```

## Uruchomianie Projektu

### Losowe roz�o�enie ekosystemu

```sh
	./SymulacjaZycia
```

### Roz�o�enie ekosystemu pobrane z "plik.txt"

```sh
	./SymulacjaZycia plik.txt
```

## Struktury danych

### Rows<T> - tablica dwuwymiarowa
#### plik: Rows.h
#### wymagania: Row<T>

W�asna implementacja tablicy "dwuwymiarowej".

Rows<T> przechowuje dane w tablicy jednowymiarowej
i eksponuje funkcje i przeci��enia operator�w, kt�re pomagaj� urzytkownikowi traktowa�
t� klas� jake tablic� dwuwymiarow� zachowuj�� cache locality.

Aby uzyska� jeden rz�d tablicy "dwuwymiarowej" nale�y ponownie urzy� operatora[].

### Row<T> - jeden rz�d w tablicy dwuwymiarowej
#### plik: Rows.h

Rz�d uzyskuje si� po urzyciu operatora[] na klasie `Rows<T>`.
Klasa ta eksponuje wycinek jednowymiarowej tablicy (rz�d), kt�ry ma wielko�� RowLen.

Aby uzyska� warto�� `T` nale�y ponownie urzy� operatora[]

### Vicinity<T> - S�siedztwo
#### plik: Vicinity.h
#### wymagania: Rows<T>

S�siedztwo pobiera po�o�enie niszy otaczaj�ce wskazan� nisz�.

Klasa zwraca szczeg�ln� uwag� aby nie pobra� informacji nie nale��cej do
instancji `Rows<T>`.

Pr�ba dost�pu do pozycji spoza Rows<T> skutkuje w `std::rangeError`.
Algorytm tworzenie s�siedztwa jest zbytecznie skomplikowany, ale nie mog�em wymy�le� lepszego.

### std::optional<T>
#### plik: <optional>

Klasa optional mo�e zawiera� T lub std::nullopt.
U�ywana jest w `Cell` poniewa� jej konstrukcja nie wymaga kolejnej alokacji na stercie.

## Klasy

### Simulation - Symulacja
#### plik: SymulacjaZycia.cpp
#### wymagania: Grid

Symulacja zawiera `Grid` i zarz�dza dzia�aniem symulacji.
Szczeg�lnie rozpocz�ciem i zako�czeniem symulacji.

### Grid - Siatka
#### plik: Grid.h
#### wymagania: Rows<T>, Cell

Siatka zawiera tablic� dwuwymiarowa `Rows`, kt�ra zawiera instacje `Cell`.
Siatka przekazuje do `Cell` jej `Vicinity`.

### Cell - Nisza
#### plik: Grid.h
#### wymagania: Organism, std::optional 

Nisza zawiera `Organism` lub nic(std::nullopt_t).
Nisza jest g��wn� klas� kt�ra w pe�ni zarz�dza `Organism`.
Na podstawie podanego `Vicinity` `Cell` wykonuje krok symulacji.

### Organism - Organizm
#### plik: Organism.h

Organizm to klasa, kt�ra zawiera dane organizmu
i eksponuje je w spos�b przystosowany do dzia�ania Symulacji.

