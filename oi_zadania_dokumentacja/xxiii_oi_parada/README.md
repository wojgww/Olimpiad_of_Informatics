Link do zadania
https://szkopul.edu.pl/problemset/problem/1QaUWE_ePAmitZjgAszOVD1U/site/?key=statement

Rozwiązanie
Cel znaleźć ścieżkę, w której będzie trzeba postawić najwięcej bramek. Warto zauważyć, że ścieżki nie opłaca się zaczynać od liści ponieważ, możemy wtedy obciąc ścieżkę o ten liść i wtedy dodamy jedną bramkę, a racji tego, że to był liść żadnych bramek nie będziemy usuwać. Obserwacja: skoro mamy możliwość wydłużenia ścieżki o wierzchołek v, który nie jest liściem, to zawsze powinniśmy to robić, ponieważ stracimy tylko jedną bramkę, a skoro v nie jest liściem to ma syna i bramek ostatecznie wyjdzie co najmniej tyle samo. Zadanie to rozwiążemy przez programowanie dynamiczne na DFS-ie. Będziemy tworzyć dp[u], gdzie u to wierzchołek w grafie i dp[u] będzie miał dwa stany first, second, gdzie first to jest najlepsza ścieżka w poddrzewie prowadząca do wierzchołka u, a second, to jest połączenie dwóch ścieżek z poddrzewa u, gdzie łączą się one w wierzchołu u. Stany są obliczane post-orderowo 

dp[w].first = v1 + graf[w].size() - 2;   //trzeba odjąć 1 stopień z v1(bo dp policzył też bramkę z połączenia z wierzchołkiem w) i jeszcze jeden stopień dlatego, że dodanie stopnia wierzchołka to za dużo, bo już jedno połączenie wykorzystaliśmy 

dp[w].second = max(maks, v1 + v2 + int(graf[w].size()) - 2);

graf[w].size(), to jest stopień wierzchołka
v1 to jest najlepsza ścieżka w poddrzewie w prowadząca do syna wierzchołka w
v2 to jest druga najlepsza ...
maks, to jest maksimum z dp[u].second, gdzie u to jest syn w 
 
v1, v2, maks domyślnie są równe 0

Teraz wystarczy odpalić DFS-a, ale ważne nie można zrobić tego w liściu (1 obserwacja). Na końcu znaleźć maksymalną wartość z wszystkich dp[w] i wszystkich stanów.

Złożoność:
Skoro jest to zwykły DFS z obliczeniami, to złożoność jest liniowa
O(n) 