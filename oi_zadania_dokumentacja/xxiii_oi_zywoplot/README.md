Link do zadania
https://szkopul.edu.pl/problemset/problem/dABzva_j1-BvzKMsyxkuRoue/site/?key=statement

Rozwiązanie:
W zadaniu musimy utworzyć labirynt z jak największej ilości żywopłotów cisu, a dopiero potem posadzić tuje. Na początku posadźmy wszystkie możliwe do posadzenia żywopłoty cisu, i odpalmy BFS-a (funkcja bfsss) w każdym rozłącznym wierzchołku aby znaleźć wszystkie Silne Spójne Składowe (SSS). Do przechowywania informacji w jakiej SSS znajduje się wierzchołek będziemy korzystać z algorytmu Find and Union, który będzie obsługiwał operacje w czasie logarytmicznym. Skoro w zadaniu jest powiedziane, że z każdego wierzchołka musi dać się dojść do wszystkich wierzchołków, to oznacza, że może być tylko jedna SSS. Ważna obserwacja aby połączyć dwie sąsiadujące ze sobą, różne SSS to wystarczy usunąć jedną krawędź, więc jeżeli mamy n SSS, to usuniemy n-1 krawędzi. Korzystając z tej obserwacji sprawdzamy wszystkie krawędzi, jeżeli krawędź łączy dwie różne SSS, czyli korzystamy z algorytmu Find_and_Union i funkcji find dla wierzchołków a, b, które są połączone tą krawędzią, to wtedy usuwamy tą krawędź i korzystamu z Union i łączymy dwie SSS w jedną. Pozostało nam jedynie dodać tuje do naszego żywopłotu co robimy za pomącą również BFS-a (funkcja bfs_t). Wyjaśnienie funkcji bfs_t jest to zwykły BFS, ale kiedy napotkamy już odwiedzoną krawędź, która nie jest ojcem, to znaczy, że istnieje do niej inna ścieżka niż tą którą przyszliśmy, to po prostu dodajemy wtedy tuje. W ten sposób zmaksymalizowaliśmy ilość cisów, a potem tui.

Złożoność:
algorytm znalezienia SSS: BFS-liniowy (w kontekście liniowości chodzi o ilość wierzchołków), ale w każdej iteracji BFS-A wykonujemy Find, Union czyli czas logarytmiczny
O((n * m) * log(n *m))

sprawdzanie wszystkich krawędzi w celu usunięcia cisów 
ilość krawędzi * Find, Union
O((n * m) * log(n *m))

BFS do tui jest wykonywany w czasie liniowym

ostateczna złożoność algorytmu
O((n * m) * log(n *m))