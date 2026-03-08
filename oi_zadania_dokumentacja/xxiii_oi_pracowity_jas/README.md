Link do zadania
https://szkopul.edu.pl/problemset/problem/_cVmDXXn2TjF0dF1rW6eazA0/site/?key=statement

Rozwiązanie:
Te zadanie jest dosyć nietypowe, ponieważ jest w nim dużo obliczeń i trzeba znać własności permutacji. Kolejno w pętli for dla każdego kolejnego wyrazu permutacji obliczamy ilość zmian, która jest narastającą sumą wraz z iteracją pętli. Obliczenia są w kodzie. Do zapamiętywania ile permutacji jest niewykorzystanych i mniejszych od j-tej wykorzystujemy Segment tree (drzewo przedziałowe), które odpowiada na zapytania i jest aktualizowane w czasie logarytmicznym. 

Złożoność:
Główna pętla wykonuje się n razy i w każdym obrocie wykonujemy operacje na drzewie przedziałowym w czasie log(n)
O(n * log(n))