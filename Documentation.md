# Symulacja ¯ycia

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

### Losowe roz³o¿enie ekosystemu

```sh
	./SymulacjaZycia
```

### Roz³o¿enie ekosystemu pobrane z "plik.txt"

```sh
	./SymulacjaZycia plik.txt
```

## Struktury danych

### Rows<T> - tablica dwuwymiarowa
#### plik: Rows.h
#### wymagania: Row<T>

W³asna implementacja tablicy "dwuwymiarowej".

Rows<T> przechowuje dane w tablicy jednowymiarowej
i eksponuje funkcje i przeci¹¿enia operatorów, które pomagaj¹ urzytkownikowi traktowaæ
t¹ klasê jake tablicê dwuwymiarow¹ zachowuj¹æ cache locality.

Aby uzyskaæ jeden rz¹d tablicy "dwuwymiarowej" nale¿y ponownie urzyæ operatora[].

### Row<T> - jeden rz¹d w tablicy dwuwymiarowej
#### plik: Rows.h

Rz¹d uzyskuje siê po urzyciu operatora[] na klasie `Rows<T>`.
Klasa ta eksponuje wycinek jednowymiarowej tablicy (rz¹d), który ma wielkoœæ RowLen.

Aby uzyskaæ wartoœæ `T` nale¿y ponownie urzyæ operatora[]

### Vicinity<T> - S¹siedztwo
#### plik: Vicinity.h
#### wymagania: Rows<T>

S¹siedztwo pobiera po³o¿enie niszy otaczaj¹ce wskazan¹ niszê.

Klasa zwraca szczególn¹ uwagê aby nie pobraæ informacji nie nale¿¹cej do
instancji `Rows<T>`.

Próba dostêpu do pozycji spoza Rows<T> skutkuje w `std::rangeError`.
Algorytm tworzenie s¹siedztwa jest zbytecznie skomplikowany, ale nie mog³em wymyœleæ lepszego.

### std::optional<T>
#### plik: <optional>

Klasa optional mo¿e zawieraæ T lub std::nullopt.
U¿ywana jest w `Cell` poniewa¿ jej konstrukcja nie wymaga kolejnej alokacji na stercie.

## Klasy

### Simulation - Symulacja
#### plik: SymulacjaZycia.cpp
#### wymagania: Grid

Symulacja zawiera `Grid` i zarz¹dza dzia³aniem symulacji.
Szczególnie rozpoczêciem i zakoñczeniem symulacji.

### Grid - Siatka
#### plik: Grid.h
#### wymagania: Rows<T>, Cell

Siatka zawiera tablicê dwuwymiarowa `Rows`, która zawiera instacje `Cell`.
Siatka przekazuje do `Cell` jej `Vicinity`.

### Cell - Nisza
#### plik: Grid.h
#### wymagania: Organism, std::optional 

Nisza zawiera `Organism` lub nic(std::nullopt_t).
Nisza jest g³ówn¹ klas¹ która w pe³ni zarz¹dza `Organism`.
Na podstawie podanego `Vicinity` `Cell` wykonuje krok symulacji.

### Organism - Organizm
#### plik: Organism.h

Organizm to klasa, która zawiera dane organizmu
i eksponuje je w sposób przystosowany do dzia³ania Symulacji.

