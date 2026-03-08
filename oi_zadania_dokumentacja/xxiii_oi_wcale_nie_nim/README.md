Link do zadania
https://szkopul.edu.pl/problemset/problem/M5CruI5eCu8elnNFHuiXBrvV/site/?key=statement

Rozwiązanie
Celem gracza 1 jest wygranie w jak najszybszym czasie, więc oczywiste jest, że będzie zawsze zabierał cały stos. A wtedy na odpowiedź gracz 2 zawsze będzie starał się wyrównać stosy po połowie. Sytuacja wygląda jednak inaczej, kiedy pozostało tylko po jednym kamieniu na każdym stosie w parze. Wtedy gracz 2 musi wtedy wykonać ruch, w którym sobie szkodzi, natomiast z dwóch stosów wielkości 1, tworzy jeden z 2 kamieniami, na co gracz 1 może odpowiedzieć zabraniem całego tego stosu. Na początku redukujemy wszystkie pary stosów do (1, 1) lub (1, 2) lub (2, 1) Co robimy w czasie logarytmicznym (z każdym ruchem dzielimy sume słupków na 2 bez reszty). Potem kiedy już mamy zliczone ile jest takich par. Potem robimy końcowe obliczenia z wykorzystanie Segment Tree (drzewa przedziałowego), którego aktualizacja jest wykonywana w czasie logarytmicznym. Celem jest sprowadzić słupki do samych (1, 1), żeby gracz 2 ułatwił zadanie graczowi 1. Wtedy koszt operacji wynosi 2.

Złożoność 
przetwarzanie słupków n * log(n)
końcowe obliczenia n * log(n)
ostateczna złożoność O(n * log(n))