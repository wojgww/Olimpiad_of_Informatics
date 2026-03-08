Link do zadania
https://szkopul.edu.pl/problemset/problem/R6kgLB2Xz3fsLFYKA-4P9fzp/site/?key=statement

Rozwiązanie:
Brutalne rozwiązanie tego zadanie jest oczywiste. Wystarczy aktualizować każde ścieżki w grafie, a przy zapytaniu odpowiednio odpalić DFS-a i zbierać ilość niezaktualizowanych ścieżek. 
Rozwiązanie szybki polega na zaimplementowaniu algorytmu Tree Flattening, gdzie spłaszczamy drzewo przy pomocy DFS-a, zapamiętując pre i post order każdego wierzchołka. Warto zauważyć, że na naszym spłaszczonym drzewie w przedziale [preorder[v], postorder[v]] znajdują się wszystkie dzieci od wierzchołka v i on sam. Skoro jeżeli droga przechodzi przez wierzchołek u, to musi przejść też przez jego ojca, więc jeżeli aktualizujemy drogę do jakiegoś wierzchołka v, to każda droga prowadząca do jego dzieci będzie prowadziła przez tą autostradę. Na podstawie tych obserwacji możemy stworzyć Segment Tree (drzewo przedziałowe) i w bardzo prosty sposób aktualizować drogi (czas logarytmiczny od wielkości wierzchołków grafu) i odczytywać informacje (czas logarytmiczny ...).
Skoro jest m zapytań i każde przetwarzamy w czasie logarytmicznym od n i stworzenie grafu zajmuje nam czas n, to
złożoność algorytmu to O(m * log(n) + n)