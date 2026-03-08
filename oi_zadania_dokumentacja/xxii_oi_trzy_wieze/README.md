Link do zadania
https://szkopul.edu.pl/problemset/problem/Grfouq9u3g_TYktFXO2sNjCU/site/?key=statement

Rozwiązanie
Algorytm jest bardzo prosty, polega on na zrozumieniu ważnej obserwacji, że zawsze przedział będzie zawierał się z liczb [a, b], gdzie a należy do {0, 1, 2} lub b należy {n - 3, n - 2, n - 1}. Udowodnić to można w ten sposób, że jeżeli mamy jakiś przedział, który nie spełnia tych wymogów, czyli mamy co najmniej 3 wolne miejsca z prawej i z lewej, to kombinatorycznie możemy rozpisać sobie wszysckie przypadki (jest ich 9) i zawsze wyjdzie na to, że ten przedział będzie można powiększyć.

Złożoność:
O(n)