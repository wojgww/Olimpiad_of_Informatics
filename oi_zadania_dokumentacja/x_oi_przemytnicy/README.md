Link do zadania:
https://szkopul.edu.pl/problemset/problem/l8-ujU0a7HQFxy8UY32B4Kk_/site/?key=statement
rozwiązanie:
Na wejściu mamy podany skierowany graf przemian surowców. Warto zauważyć, że ten graf nie jest drzewem, ponieważ mogą wystąpić duplikaty krawędzi i cykle. Skoro jest to graf ważony. Intuicja nakazuje nam wykorzystać algorytm djikstry do znalezienia najmniej kosztownej przemiany z złota (wierzchołka n) do innego dowolnego metalu (wierzchołka i). Skoro najpierw musimy przekształcić złoto do tańszego metalu, a potem znowu, to musimy zrobić djikstrę po grafie zwykłym jak i po transponowanym. Jak już to zrobimy, to wystarczy znaleźć taki metal, który będzie miał najtańszy koszt przejścia po dwóch grafach + 50% kosztu metalu.

Złożoność 
Djikstra O(n * log(n))
znalezienie wyniku O(n)

złożoność O(n * log(n))
