# Tic-Tac-Toe-Engine-and-MinMax-Solver
## Polish instructions
Zadanie składa się z dwóch części. Pierwszą jest implementacja silnika uogólnionej gry Kółko i Krzyżyk. Drugą jest implementacja programu rozwiązującego te wersje gry przy pomocy algorytmu min-max (https://pl.wikipedia.org/wiki/Algorytm_min-max).

Uogólniona wersja silnika gry Kółko i Krzyżyk czyli rodzina gier NMK (https://en.wikipedia.org/wiki/M,n,k-game) pobiera 3 parametry N, M i K gdzie (N x M) to rozmiar planszy a (K) to liczba nieprzerwanie sąsiadujących ze sobą pól w ciągłej pionowej, poziomej bądź ukośnej linii które są warunkiem wygrania.
Należy zaimplementować deterministyczny generator posunięć, który dodaje pion gracza (np. Kółko bądź Krzyżyk, albo biały bądź czarny pionek) zaczynając od górnego lewego rogu, kontynuując w rzędach a następnie w kolumnach. Na potrzeby naszego zadania posunięcia pierwszego gracza będziemy oznaczać jedynkami a drugiego dwójkami, niezajęte pola będą oznaczone zerami. Zatem w podstawowej grze Kółko i krzyżyk (NMK 3,3,3) wygenerowane możliwe posunięcia dla pustej planszy to (kolejność jest ważna):

- 100 010 001 000 000 000 000 000 000
- 000 000 000 100 010 001 000 000 000
- 000 000 000 000 000 000 100 010 001 

Silnik gry powinien pozwalać na:
1. generowanie wszystkich możliwych posunięć,
2. Ocenę gry w postaci odpowiedźi na pytanie - czy gra się zakończyła i czy gracz wygrał/zremisował/przegrał?

W wersji ulepszonej silnik jeśli jeden z wygenerowanych stanów będzie końcowym (jeden z graczy wygra albo plansza będzie pełna, co oznacza remis) silnik generuje tylko ten jeden stan. Jeśli jest ich kilka to generuje pierwszy wygrywający/remisujący stan. Zauważmy, że nowo wygenerowany stan jeśli będzie wygrywający to tylko dla gracza aktywnego, nie ma możliwości aby gracz spowodował swoim posunięciem natychmiastową wygraną przeciwnika.

Przykładowo wszystkie możliwe stany poniższego (aktywnym graczem jest 1):
- 102
- 012
- 000

to:

- 112 102 102 102 102
- 012 112 012 012 012
- 000 000 100 010 001

Tylko ostatni z nich jest posunięciem wygrywającym dla gracza 1 i w ulepszonej wersji silnika tylko on powinien zostać wygenerowany.

W drugiej części zadania należy zaimplementować algorytm rozwiązujący pewien, niekoniecznie początkowy, stan gry NMK. Można zastosować algorytm Minmax albo Negamax z pewnymi usprawnieniami. Zauważmy, że r przypadku tej rodziny gier, rozwiązanie zawsze będzie deterministyczne ponieważ gra jest 2-osobowa, bez elementów losowych i pozbawiona ukrytej informacji. Zatem będziemy zawsze wiedzieli czy taka rozgrywka (jeśli obydwaj gracze grają optymalnie) zakończy się wygraną, przegraną czy remisem każdego z graczy.

Pierwszym usprawnieniem algorytmu Minmax jest zakończenie poszykiwań min w przypadku otrzymiania wartości -1 albo max w przypadku uzyskania wartości 1 ponieważ tych wyników nie da się już poprawić.

Drugie usprawnienie wynika z faktu, że możliwe jest stworzenie sytuacji w której gracz ma sytuację wygrywającą w następnym posunięciu, no chyba, że przeciwnik stworzył taka sytuację wcześniej. Chodzi o ciągi długości (K-1) którr na końcach posiadają możliwośc dołożenia swojego piona. Jesli jest taki jeden to przeciwnik może sie jeszcze obronić. Jesli są dwa lub więcej to jeśli przeciwnik wcześniej nie stworzył zagrożenia jest juz na przegranej pozycji.

Rozważmy poniższy przykład dla gry (4,4,3):

- 0000
- 0110
- 0200
- 0002

Ruch należy do gracza 1 i widać, że 2 nie może sie już obronić, jeśli postawi swojego piona po lewej stronie:

- 0000
- 2110
- 0200
- 0002

to przeciwnik dostawi po prawej:

- 0000
- 2111
- 0200
- 0002

jeśli postawi go po prawej:

- 0000
- 0112
- 0200
- 0002

to przeciwnik po lewej:

- 0000
- 2110
- 0200
- 0002

Zatem wykrycie takiej sytuacji można oznaczyć jako zagrożenie ze strony jednego z graczy i w przypadku kiedy w przyszłości natrafimy na tak oznaczony stan gry (zawierający takie zagrożenie) a przeciwnik gracza, który stworzył takie zagrożenie nie wygrał we właśnie analizowanym ruchu to mamy pewność, że już nie wygra.

Program powinien obsługiwać 3 komendy:

1. GEN_ALL_POS_MOV N M K ActivePlayer - wygenerowanie wszystkich możliwych posunięć wraz z ich liczbą,

Przykłady:

Wejście:

GEN_ALL_POS_MOV 3 3 3 2
- 1 0 0
- 0 0 0
- 0 0 0

Wyjście:

- 8
- 1 2 0
- 0 0 0
- 0 0 0
<br/><br/>
- 1 0 2
- 0 0 0
- 0 0 0
<br/><br/>
- 1 0 0
- 2 0 0
- 0 0 0
<br/><br/>
- 1 0 0
- 0 2 0
- 0 0 0
<br/><br/>
- 1 0 0
- 0 0 2
- 0 0 0
<br/><br/>
- 1 0 0
- 0 0 0
- 2 0 0
<br/><br/>
- 1 0 0
- 0 0 0
- 0 2 0
<br/><br/>
- 1 0 0
- 0 0 0
- 0 0 2

Wejście:

GEN_ALL_POS_MOV 3 3 3 1
- 1 2 0
- 0 0 0
- 0 0 0

Wyjście:

- 7
- 1 2 1
- 0 0 0
- 0 0 0
<br/><br/>
- 1 2 0
- 1 0 0
- 0 0 0
<br/><br/>
- 1 2 0
- 0 1 0
- 0 0 0
<br/><br/>
- 1 2 0
- 0 0 1
- 0 0 0
<br/><br/>
- 1 2 0
- 0 0 0
- 1 0 0
<br/><br/>
- 1 2 0
- 0 0 0
- 0 1 0
<br/><br/>
- 1 2 0
- 0 0 0
- 0 0 1

2. GEN_ALL_POS_MOV_CUT_IF_GAME_OVER N M K ActivePlayer - wygenerowanie wszystkich możliwych posunięć wraz z ich liczbą, a w przypadku kiedy jedno z nich jest wygrywające albo kończące to wygenerowanie tylko pierwszego z nich

Wejście:

GEN_ALL_POS_MOV_CUT_IF_GAME_OVER 3 3 3 1

- 0 2 1
- 2 2 1
- 0 1 0

Wyjście:

- 1
- 0 2 1
- 2 2 1
- 0 1 1

Wejście:

GEN_ALL_POS_MOV_CUT_IF_GAME_OVER 3 3 3 1

- 1 2 1
- 2 2 1
- 0 1 2

Wyjście:

- 1
- 1 2 1
- 2 2 1
- 1 1 2

3 SOLVE_GAME_STATE N M K ActivePlayer - rozwiązanie gry, oraz podania jednej z trzech możliwych odpowiedzi: FIRST_PLAYER_WINS, SECOND_PLAYER_WINS, BOTH_PLAYERS_TIE.

Przykłady:

Wejście:

SOLVE_GAME_STATE 3 3 3 2
- 1 0 0
- 0 0 0
- 0 0 0

Wyjście:

BOTH_PLAYERS_TIE

Wejście:

SOLVE_GAME_STATE 3 3 3 1
- 1 2 0
- 0 0 0
- 0 0 0

Wyjście:

FIRST_PLAYER_WINS

## English instructions
The task consists of two parts. The first is the implementation of the generalized Tic Tac Toe game engine. The second is the implementation of a program that solves these versions of the game using the min-max algorithm (https://pl.wikipedia.org/wiki/Algorytm_min-max).

The generalized version of the Tic Tac Toe game engine, i.e. the NMK game family (https://en.wikipedia.org/wiki/M,n,k-game) takes 3 parameters N, M and K where (N x M) is the size of the board and (K) is the number of consecutive adjacent fields in a continuous vertical, horizontal or diagonal line that are the condition for winning.
A deterministic move generator must be implemented that adds a player's piece (e.g. Tic Tac Toe or a white or black piece) starting from the upper left corner, continuing in rows and then in columns. For the purposes of our task, we will mark the first player's moves with ones and the second player's with twos, and unoccupied squares will be marked with zeros. So in the basic Tic Tac Toe game (NMK 3,3,3) the possible moves generated for an empty board are (the order is important):

- 100 010 001 000 000 000 000 000 000
- 000 000 000 100 010 001 000 000 000
- 000 000 000 000 000 000 100 010 001

The game engine should allow for:
1. generating all possible moves,
2. Evaluating the game in the form of an answer to the question - has the game ended and has the player won/draw/lost?

In the improved version of the engine, if one of the generated states is the final one (one of the players wins or the board is full, which means a tie), the engine generates only that one state. If there are several of them, it generates the first winning/tied state. Note that the newly generated state, if it is a winning state, is only for the active player, there is no possibility for the player to cause an immediate win for the opponent with his move.

For example, all possible states of the following (active player is 1):
- 102
- 012
- 000

to:

- 112 102 102 102 102
- 012 112 012 012 012
- 000 000 100 010 001

Only the last one is a winning move for player 1 and in the improved version of the engine only it should be generated.

In the second part of the task, an algorithm should be implemented that solves a certain, not necessarily initial, state of the NMK game. You can use the Minmax or Negamax algorithm with some improvements. Note that in the case of this family of games, the solution will always be deterministic because the game is 2-player, without random elements and devoid of hidden information. Therefore, we will always know whether such a game (if both players play optimally) will end in a win, loss or draw for each player.

The first improvement of the Minmax algorithm is to end the search for mins in the case of obtaining the value -1 or max in the case of obtaining the value 1 because these results can no longer be improved.

The second improvement results from the fact that it is possible to create a situation in which the player has a winning situation in the next move, unless the opponent has created such a situation earlier. This concerns sequences of length (K-1) which have the possibility of adding their own pawn at the ends. If there is one such pawn, the opponent can still defend. If there are two or more, then if the opponent has not created a threat earlier, he is already in a lost position.

Consider the following example for the game (4,4,3):

- 0000
- 0110
- 0200
- 0002

Player 1 has a move and it is clear that 2 can no longer defend himself, if he places his pawn on the left:

- 0000
- 2110
- 0200
- 0002

then the opponent will place it on the right:

- 0000
- 2111
- 0200
- 0002

if he places it on the right:

- 0000
- 0112
- 0200
- 0002

then the opponent will place it on the left:

- 0000
- 2110
- 0200
- 0002

Therefore, the detection of such a situation can be marked as a threat from one of the players and in the case when we encounter for such a designated state of the game (containing such a threat) and the opponent of the player who created such a threat did not win in the move being analyzed, then we are sure that he will not win again.

The program should support 3 commands:

1. GEN_ALL_POS_MOV N M K ActivePlayer - generate all possible moves along with their number,

Examples:

Input:

GEN_ALL_POS_MOV 3 3 3 2
- 1 0 0
- ​​0 0 0
- ​​0 0 0

Output:

- 8
- 1 2 0
- 0 0 0
- ​​0 0 0
<br/><br/>
- 1 0 2
- 0 0 0
- ​​0 0 0
<br/><br/>
- 1 0 0
- ​​2 0 0
- ​​0 0 0
<br/><br/>
- 1 0 0
- ​​0 2 0
- 0 0 0
<br/><br/>
- 1 0 0
- 0 0 2
- 0 0 0
<br/><br/>
- 1 0 0
- ​​0 0 0
- ​​2 0 0
<br/><br/>
- 1 0 0
- ​​0 0 0
- ​​0 2 0
<br/><br/>
- 1 0 0
- ​​0 0 0
- ​​0 0 2

Input:

GEN_ALL_POS_MOV 3 3 3 1
- 1 2 0
- 0 0 0
- ​​0 0 0

Output:

- 7
- 1 2 1
- 0 0 0
- ​​0 0 0
<br/><br/>
- 1 2 0
- 1 0 0
- ​​0 0 0
<br/><br/>
- 1 2 0
- 0 1 0
- 0 0 0
<br/><br/>
- 1 2 0
- 0 0 1
- 0 0 0
<br/><br/>
- 1 2 0
- 0 0 0
- ​​1 0 0
<br/><br/>
- 1 2 0
- 0 0 0
- ​​0 1 0
<br/><br/>
- 1 2 0
- 0 0 0
- ​​0 0 1

2. GEN_ALL_POS_MOV_CUT_IF_GAME_OVER N M K ActivePlayer - generate all possible moves along with their number, and in the case when one of them is winning or ending, generate only the first one

Input:

GEN_ALL_POS_MOV_CUT_IF_GAME_OVER 3 3 3 1

- 0 2 1
- 2 2 1
- 0 1 0

Output:

- 1
- 0 2 1
- 2 2 1
- 0 1 1

Input:

GEN_ALL_POS_MOV_CUT_IF_GAME_OVER 3 3 3 1

- 1 2 1
- 2 2 1
- 0 1 2

Output:

- 1
- 1 2 1
- 2 2 1
- 1 1 2

3 SOLVE_GAME_STATE N M K ActivePlayer - solve the game, and provide one of three possible answers: FIRST_PLAYER_WINS, SECOND_PLAYER_WINS, BOTH_PLAYERS_TIE.

Examples:

Input:

SOLVE_GAME_STATE 3 3 3 2
- 1 0 0
- ​​0 0 0
- ​​0 0 0

Output:

BOTH_PLAYERS_TIE

Input:

SOLVE_GAME_STATE 3 3 3 1
- 1 2 0
- 0 0 0
- ​​0 0 0

Output:

FIRST_PLAYER_WINS
