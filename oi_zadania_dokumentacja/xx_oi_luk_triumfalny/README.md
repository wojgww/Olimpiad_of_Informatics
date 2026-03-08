Link do zadania
https://szkopul.edu.pl/problemset/problem/jgCcEjQu3kdpM4BmxA6GujfX/site/?key=statement

Rozwiązanie
Ilość grup budowniczych będziemy wybierać binary_searchem. Zawężać przedział będziemy na podstawie funkcji wykorzystującej dynamiczne programowanie obliczane z kolejnością post-order DFS-a. Zadaniem króla jest wybranie dla nas możliwie najcięższej ścieżki. Łatwo zauważyć, że królowi nie oplaca się cofać ponieważ dodaje nam dodatkowe tury budowania łuków. Dp[w] oblicza ile łuków triumfalnych nie możemy zbudować w poddrzewie wierzchołka w. Dla liści dp zwróci 0, a dla wierzchołka v dp = suma dp jego dzieci + ilość dzieci - ilość ekip budowlanych. Jeżeli dp[w] jest dodatni, to znaczy, że ilość dzieci w przekracza ilość ekip budowlanych, lub w poddrzewie jakiegoś syna w następnych ruchach króla nie będzie się dało zbudować wszystkich potrzebnych łuków triumfalnych.

Złożoność:
logarytmicznie wiele razy od ilości ekip budowlanych(n) robimy dp, który jest prostym DFS-em, czyli
O(n * log(n))