link do zadania
https://szkopul.edu.pl/problemset/problem/PSqCh5o1-Gyl1WaQSGXjxkZN/site/?key=statement

Rozwiązanie
Od razu po przeczytaniu zadania może nasuwać się nam myśl o rozwiązaniu tego zadania programowaniem dynamicznym. Obliczamy dp[i][j], gdzie i ilość sprawdzeń biletów, a j, to stacja, na której wykonaliśmy ostatnie sprawdzenie. dla każdego dp[i][j] pamiętamy jeszcze na jakiej stacji ostatnio były sprawdzane bilety (tablica used), abyśmy mogli wszystkie stacje, na których sprawdziliśmy bilety. dp[i][j] obliczamy z pomocą sumy prefiksowej prostokaty. Obliczenia są zapisane w kodzie.

Złożoność:
obliczenie tablicy prostokąty następuje w czasie kwadratowym od ilości stacji, czyli 
Obliczenie każdego stanu dp[i][j] jest wykonywane w czasie liniowym od n, czyli  (k * n) * n = k * n^2
cały algorytm działa w czasie O(k * n^2 + n^2) = O(n^2 * k) 