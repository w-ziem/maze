# maze
## etapy tworzenia programu




### Jak reprezentować labirynt (np. tablica grid + dodatkowe informacje o ścianach).
    ############# ###########
    ############# ###########
    ###         # ###########
    ### ######        #######
    ### ###### ###### #######
    ### ###### ###### #######
    ##########        #######
    ################# #######
    ################# #######

1 to ściana, zera to korytarze

 ### Jak losować sąsiadów.
4 kierunki wiec mozna sobie zrobic typedef enum {left, up, right, down} direction
no i potem losowac srand(time(NULL)) i direction = rand() % 4 aby uzyskac loswy kierunek



### Jak sprawdzać, czy dany sąsiad jest w granicach i czy został odwiedzony.
kazda sprawdzana komorka ma row col, wiec row - 1 to do gory, col -1 to w lewo, kombinacje tego dadza nam wszyskie kierunki, wylosowany sąsiad nie może dotykać granic


### Jak usunąć ścianę między komórkami.
komorka->up == 1 => ściana == 0 brak sciany, chyba tak by to mialo sens, ale znowu wracamy do punktu wyjscia moze dalo by sie jakos latwiej to zrobic, żeby nie trzeba bylo pisac tego jako oddzielnej struktury

Łatwietjsza wersja zakłada po prostu 2 tablice 2D : visited i grid. Jeżeli obok siebie stoją 2 zera (spacje) to nie ma między nimi ściany i tyle


### tworzenie ścieżek DFS

dodatkowa tablica visited o tych samych wymiarach przechowuje informacje o tym czy komórka została odwiedzona

1. wybierz kmórkę i zaznacz ją jako odwiedzoną
2. losuj kolejność sąsiadów
3. jeżeli sąsiad jest w granicach i nieodwiedzony to usun między nim ścianę i przejdź do niego (wywołaj na nim rekurencję)
4. Jak wszyscy sąsiedzi odwiedzeni to wróć do poprzedniej komórki

Base case?????
Zewnętrzna warstwa ma pozostac ścianami (unvisited i guess) - do przemyślenia, żeby nie stworzyły się nowe wyjścia

(m-2)*(n-2) to jest ilosc komorek ktore możemy ustawić jako visited, razem z is_valid_cell zapobiega tworzeniu sie nowych wyjść


#### //think about me:
Ile ścieżek się wygeneruje? Czemu?