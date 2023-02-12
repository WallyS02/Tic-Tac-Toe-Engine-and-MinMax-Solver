#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define MAX_COMMAND_LENGTH 33
#define MAX_TILES_TO_CHECK 8
#define PLAYER_ONE_NUMBER 1
#define PLAYER_TWO_NUMBER 2
#define MINIMAL_SEQUENCE_BOARD_LENGTH 3

int checkRow(int M, int** tab, int K, int i, int* zeroCount) {
    int counter = 1;
    int selectedPlayer = 0;
    for (int col = 0; col < M; col++) {
        if (zeroCount && tab[i][col] == 0)
            *zeroCount = *zeroCount + 1;
        if (selectedPlayer != 0 && tab[i][col] == selectedPlayer) {
            counter++;
        }
        else {
            counter = 1;
            selectedPlayer = 0;
        }
        if (tab[i][col] != 0) {
            selectedPlayer = tab[i][col];
        }
        if (counter == K)
            break;
    }
    if (counter == K && selectedPlayer == PLAYER_ONE_NUMBER)
        return 0;
    if (counter == K && selectedPlayer == PLAYER_TWO_NUMBER)
        return 1;
    return 2;
}

int checkCol(int N, int** tab, int K, int j) {
    int counter = 1;
    int selectedPlayer = 0;
    for (int row = 0; row < N; row++) {
        if (selectedPlayer != 0 && tab[row][j] == selectedPlayer) {
            counter++;
        }
        else {
            counter = 1;
            selectedPlayer = 0;
        }
        if (tab[row][j] != 0) {
            selectedPlayer = tab[row][j];
        }
        if (counter == K)
            break;
    }
    if (counter == K && selectedPlayer == PLAYER_ONE_NUMBER)
        return 0;
    if (counter == K && selectedPlayer == PLAYER_TWO_NUMBER)
        return 1;
    return 2;
}

int checkAntidiagonal(int N, int M, int** tab, int K, int i, int j) {
    int startingRow = i, startingColumn = j;
    while (startingRow > 0 && startingColumn < M) {
        startingColumn++;
        startingRow--;
    }
    int counter = 1;
    int selectedPlayer = 0;
    while (startingRow < N && startingColumn >= 0) {
        if (selectedPlayer != 0 && tab[startingRow][startingColumn] == selectedPlayer) {
            counter++;
        }
        else {
            counter = 1;
            selectedPlayer = 0;
        }
        if (tab[startingRow][startingColumn] != 0) {
            selectedPlayer = tab[startingRow][startingColumn];
        }
        if (counter == K)
            break;
        startingColumn--;
        startingRow++;
    }
    if (counter == K && selectedPlayer == PLAYER_ONE_NUMBER)
        return 0;
    if (counter == K && selectedPlayer == PLAYER_TWO_NUMBER)
        return 1;
    return 2;
}

int checkDiagonal(int N, int M, int** tab, int K, int i, int j) {
    int startingRow = i, startingColumn = j;
    while (startingRow > 0 && startingColumn > 0) {
        startingColumn--;
        startingRow--;
    }
    int counter = 1;
    int selectedPlayer = 0;
    while (startingRow < N && startingColumn < M) {
        if (selectedPlayer != 0 && tab[startingRow][startingColumn] == selectedPlayer) {
            counter++;
        }
        else {
            counter = 1;
            selectedPlayer = 0;
        }
        if (tab[startingRow][startingColumn] != 0) {
            selectedPlayer = tab[startingRow][startingColumn];
        }
        if (counter == K)
            break;
        startingColumn++;
        startingRow++;
    }
    if (counter == K && selectedPlayer == PLAYER_ONE_NUMBER)
        return 0;
    if (counter == K && selectedPlayer == PLAYER_TWO_NUMBER)
        return 1;
    return 2;
}

int checkWinSolveSingle(int N, int M, int K, int** tab, int j, int i, int maxMovesCounter) {
    int resultRow = checkRow(M, tab, K, i, NULL);
    if (resultRow != 2) {
        if (resultRow == 0)
            return 0; // player 1 wins
        else return 1; // player 2 wins
    }
    int resultCol = checkCol(N, tab, K, j);
    if (resultCol != 2) {
        if (resultCol == 0)
            return 0; // player 1 wins
        else return 1; // player 2 wins
    }
    int resultDiag = checkDiagonal(N, M, tab, K, i, j);
    if (resultDiag != 2) {
        if (resultDiag == 0)
            return 0; // player 1 wins
        else return 1; // player 2 wins
    }
    int resultAntidiag = checkAntidiagonal(N, M, tab, K, i, j);
    if (resultAntidiag != 2) {
        if (resultAntidiag == 0)
            return 0; // player 1 wins
        else return 1; // player 2 wins
    }
    if (maxMovesCounter == 0)
        return 2; // tie
    return 3; // nothing
}

int checkWin(int N, int M, int K, int** tab) {
    int zeroCount = 0;
    int result;
    for (int i = 0; i < N; i++) {
        result = checkRow(M, tab, K, i, &zeroCount);
        if (result != 2) {
            if (result == 0)
                return 0;
            else return 1;
        }
    }
    for (int j = 0; j < M; j++) {
        result = checkCol(N, tab, K, j);
        if (result != 2) {
            if (result == 0)
                return 0;
            else return 1;
        }
    }
    for (int j = 0; j < M; j++) {
        result = checkDiagonal(N, M, tab, K, 0, j);
        if (result != 2) {
            if (result == 0)
                return 0;
            else return 1;
        }
    }
    for (int i = 1; i < N; i++) {
        result = checkDiagonal(N, M, tab, K, i, 0);
        if (result != 2) {
            if (result == 0)
                return 0;
            else return 1;
        }
    }
    for (int j = M - 1; j >= 0; j--) {
        result = checkAntidiagonal(N, M, tab, K, 0, j);
        if (result != 2) {
            if (result == 0)
                return 0;
            else return 1;
        }
    }
    for (int i = 1; i < N; i++) {
        result = checkAntidiagonal(N, M, tab, K, i, M - 1);
        if (result != 2) {
            if (result == 0)
                return 0;
            else return 1;
        }
    }
    if (zeroCount == 0)
        return 2;
    return 3;
}

void generateAllMoves(int N, int M, int K, int ActivePlayer, int** tab) {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (tab[i][j] == 0)
                sum++;
        }
    }
    if (checkWin(N, M, K, tab) != 3) {
        printf("%d\n", 0);
        return;
    }
    printf("%d\n", sum);
    int currentPosition[2];
    currentPosition[0] = 0;
    currentPosition[1] = 0;
    for (int p = 0; p < sum; p++) {
        bool turn = true;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (tab[i][j] != 0) {
                    printf("%d ", tab[i][j]);
                    if (i == currentPosition[0] && j == currentPosition[1]) {
                        if (currentPosition[1] == (M - 1)) {
                            currentPosition[1] = 0;
                            currentPosition[0]++;
                        }
                        else currentPosition[1]++;
                    }
                }
                else {
                    if (i == currentPosition[0] && j == currentPosition[1] && turn) {
                        printf("%d ", ActivePlayer);
                        turn = false;
                        if (currentPosition[1] == (M - 1)) {
                            currentPosition[1] = 0;
                            currentPosition[0]++;
                        }
                        else currentPosition[1]++;
                    }
                    else {
                        printf("%d ", tab[i][j]);
                    }
                }
            }
            printf("\n");
        }
    }
}

int* checkWinningIndex(int N, int M, int K, int ActivePlayer, int** tab) {
    static int winningIndex[2];
    winningIndex[0] = -1;
    winningIndex[1] = -1;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (tab[i][j] == 0) {
                static int zeroIndex[2];
                zeroIndex[0] = i;
                zeroIndex[1] = j;
                tab[i][j] = ActivePlayer;
                if (checkWinSolveSingle(N, M, K, tab, j, i, 1) != 3)
                    return zeroIndex;
                else tab[i][j] = 0;
            }
        }
    }
    return winningIndex;
}

void generateAllMovesWinningMove(int N, int M, int K, int ActivePlayer, int** tab) {
    if (checkWin(N, M, K, tab) != 3) {
        printf("%d\n", 0);
        return;
    }
    int* winningIndex = checkWinningIndex(N, M, K, ActivePlayer, tab);
    if (winningIndex[0] == -1 && winningIndex[1] == -1)
        generateAllMoves(N, M, K, ActivePlayer, tab);
    else {
        printf("%d\n", 1);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (i == winningIndex[0] && j == winningIndex[1])
                    printf("%d ", ActivePlayer);
                else printf("%d ", tab[i][j]);
            }
            printf("\n");
        }
    }
}

int checkRowSequence(int M, int** tab, int K, int i) {
    int insideSequenceLength = K - 1;
    int counter = 1;
    int selectedPlayer = 0;
    bool isCheckingInsideSequence = false;
    for (int col = 0; col < M; col++) {
        if (!isCheckingInsideSequence && tab[i][col] == 0)
            isCheckingInsideSequence = true;
        else if (isCheckingInsideSequence) {
            if (tab[i][col] == 0 && col < M - 2 && tab[i][col + 1] == 0)
                isCheckingInsideSequence = false;
            else if (tab[i][col] != 0) {
                if (selectedPlayer != 0 && tab[i][col] == selectedPlayer) {
                    counter++;
                }
                else {
                    counter = 1;
                    selectedPlayer = 0;
                }
                if (tab[i][col] != 0) {
                    selectedPlayer = tab[i][col];
                }
                if (counter == insideSequenceLength) {
                    if (col + 1 < M && tab[i][col + 1] == 0)
                        break;
                    else counter = 1;
                }
            }
        }
    }
    if (counter == insideSequenceLength && selectedPlayer == PLAYER_ONE_NUMBER)
        return 0;
    if (counter == insideSequenceLength && selectedPlayer == PLAYER_TWO_NUMBER)
        return 1;
    return 2;
}

int checkColSequence(int N, int** tab, int K, int j) {
    int insideSequenceLength = K - 1;
    int counter = 1;
    int selectedPlayer = 0;
    bool isCheckingInsideSequence = false;
    for (int row = 0; row < N; row++) {
        if (!isCheckingInsideSequence && tab[row][j] == 0)
            isCheckingInsideSequence = true;
        else if (isCheckingInsideSequence) {
            if (tab[row][j] == 0 && row < N - 2 && tab[row + 1][j] == 0)
                isCheckingInsideSequence = false;
            else if (tab[row][j] != 0) {
                if (selectedPlayer != 0 && tab[row][j] == selectedPlayer) {
                    counter++;
                }
                else {
                    counter = 1;
                    selectedPlayer = 0;
                }
                if (tab[row][j] != 0) {
                    selectedPlayer = tab[row][j];
                }
                if (counter == insideSequenceLength) {
                    if (row + 1 < N && tab[row + 1][j] == 0)
                        break;
                    else counter = 1;
                }
            }
        }
    }
    if (counter == insideSequenceLength && selectedPlayer == PLAYER_ONE_NUMBER)
        return 0;
    if (counter == insideSequenceLength && selectedPlayer == PLAYER_TWO_NUMBER)
        return 1;
    return 2;
}

int checkAntidiagonalSequence(int N, int M, int** tab, int K, int i, int j) {
    int startingRow = i, startingColumn = j;
    while (startingRow > 0 && startingColumn < M) {
        startingColumn++;
        startingRow--;
    }
    int insideSequenceLength = K - 1;
    int counter = 1;
    int selectedPlayer = 0;
    bool isCheckingInsideSequence = false;
    while (startingRow < N && startingColumn >= 0) {
        if (!isCheckingInsideSequence && tab[startingRow][startingColumn] == 0)
            isCheckingInsideSequence = true;
        else if (isCheckingInsideSequence) {
            if (tab[startingRow][startingColumn] == 0 && startingRow < N - 2 && startingColumn < M - 2 && tab[startingRow + 1][startingColumn + 1] == 0)
                isCheckingInsideSequence = false;
            else if (tab[startingRow][startingColumn] != 0) {
                if (selectedPlayer != 0 && tab[startingRow][startingColumn] == selectedPlayer) {
                    counter++;
                }
                else {
                    counter = 1;
                    selectedPlayer = 0;
                }
                if (tab[startingRow][startingColumn] != 0) {
                    selectedPlayer = tab[startingRow][startingColumn];
                }
                if (counter == insideSequenceLength) {
                    if (startingRow + 1 < N && startingColumn + 1 < M && tab[startingRow + 1][startingColumn + 1] == 0)
                        break;
                    else counter = 1;
                }
            }
        }
        startingColumn--;
        startingRow++;
    }
    if (counter == insideSequenceLength && selectedPlayer == PLAYER_ONE_NUMBER)
        return 0;
    if (counter == insideSequenceLength && selectedPlayer == PLAYER_TWO_NUMBER)
        return 1;
    return 2;
}

int checkDiagonalSequence(int N, int M, int** tab, int K, int i, int j) {
    int startingRow = i, startingColumn = j;
    while (startingRow > 0 && startingColumn > 0) {
        startingColumn--;
        startingRow--;
    }
    int insideSequenceLength = K - 1;
    int counter = 1;
    int selectedPlayer = 0;
    bool isCheckingInsideSequence = false;
    while (startingRow < N && startingColumn < M) {
        if (!isCheckingInsideSequence && tab[startingRow][startingColumn] == 0)
            isCheckingInsideSequence = true;
        else if (isCheckingInsideSequence) {
            if (tab[startingRow][startingColumn] == 0 && startingRow < N - 2 && startingColumn < M - 2 && tab[startingRow + 1][startingColumn + 1] == 0)
                isCheckingInsideSequence = false;
            else if (tab[startingRow][startingColumn] != 0) {
                if (selectedPlayer != 0 && tab[startingRow][startingColumn] == selectedPlayer) {
                    counter++;
                }
                else {
                    counter = 1;
                    selectedPlayer = 0;
                }
                if (tab[startingRow][startingColumn] != 0) {
                    selectedPlayer = tab[startingRow][startingColumn];
                }
                if (counter == insideSequenceLength) {
                    if (startingRow + 1 < N && startingColumn + 1 < M && tab[startingRow + 1][startingColumn + 1] == 0)
                        break;
                    else counter = 1;
                }
            }
        }
        startingColumn++;
        startingRow++;
    }
    if (counter == insideSequenceLength && selectedPlayer == PLAYER_ONE_NUMBER)
        return 0;
    if (counter == insideSequenceLength && selectedPlayer == PLAYER_TWO_NUMBER)
        return 1;
    return 2;
}

int checkKMinusOneSequence(int N, int M, int** tab, int K, int i, int j) {
    int resultRow = checkRowSequence(M, tab, K, i);
    if (resultRow != 2) {
        if (resultRow == 0)
            return 0; // player 1 wins
        else return 1; // player 2 wins
    }
    int resultCol = checkColSequence(N, tab, K, j);
    if (resultCol != 2) {
        if (resultCol == 0)
            return 0; // player 1 wins
        else return 1; // player 2 wins
    }
    int resultDiag = checkDiagonalSequence(N, M, tab, K, i, j);
    if (resultDiag != 2) {
        if (resultDiag == 0)
            return 0; // player 1 wins
        else return 1; // player 2 wins
    }
    int resultAntidiag = checkAntidiagonalSequence(N, M, tab, K, i, j);
    if (resultAntidiag != 2) {
        if (resultAntidiag == 0)
            return 0; // player 1 wins
        else return 1; // player 2 wins
    }
    return 2; // nothing
}

bool checkIfPlayerOneWinsInNextTurn(int N, int M, int K, int** tab) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (tab[i][j] == 0) {
                tab[i][j] = PLAYER_ONE_NUMBER;
                if (checkWinSolveSingle(N, M, K, tab, j, i, 1) != 3) {
                    tab[i][j] = 0;
                    return true;
                }
                else tab[i][j] = 0;
            }
        }
    }
    return false;
}

bool checkIfPlayerTwoWinsInNextTurn(int N, int M, int K, int** tab) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (tab[i][j] == 0) {
                tab[i][j] = PLAYER_TWO_NUMBER;
                if (checkWinSolveSingle(N, M, K, tab, j, i, 1) != 3) {
                    tab[i][j] = 0;
                    return true;
                }
                else tab[i][j] = 0;
            }
        }
    }
    return false;
}

int minimasePlayerOne(int N, int M, int** tab, int* minScore, int K, bool maximizedPlayer, int alpha, int beta, int maxMovesCounter);
int maximasePlayerOne(int N, int M, int** tab, int* maxScore, int K, bool maximizedPlayer, int alpha, int beta, int maxMovesCounter);

int minimaxPlayerOne(int N, int M, int K, int** tab, bool maximizedPlayer, int alpha, int beta, int j, int i, int maxMovesCounter) {
    int check = checkWinSolveSingle(N, M, K, tab, j, i, maxMovesCounter);
    if (check != 3) {
        if (check == 2)
            return 0;
        if (check == 0)
            return 1;
        if (check == 1)
            return -1;
    }
    if ((N > MINIMAL_SEQUENCE_BOARD_LENGTH || M > MINIMAL_SEQUENCE_BOARD_LENGTH) && (K < N || K < M)) {
        int checkSequence = checkKMinusOneSequence(N, M, tab, K, i, j);
        if (checkSequence != 2) {
            if (checkSequence == 1)
                if (!checkIfPlayerOneWinsInNextTurn(N, M, K, tab))
                    return -1;
            if (checkSequence == 0)
                if (!checkIfPlayerTwoWinsInNextTurn(N, M, K, tab))
                    return 1;
        }
    }
    if (maximizedPlayer) {
        int maxScore = -1000;
        maxScore = maximasePlayerOne(N, M, tab, &maxScore, K, maximizedPlayer, alpha, beta, maxMovesCounter);
        return maxScore;
    }
    else {
        int minScore = 1000;
        minScore = minimasePlayerOne(N, M, tab, &minScore, K, maximizedPlayer, alpha, beta, maxMovesCounter);
        return minScore;
    }
}

int minimasePlayerOne(int N, int M, int** tab, int* minScore, int K, bool maximizedPlayer, int alpha, int beta, int maxMovesCounter) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (tab[i][j] == 0) {
                tab[i][j] = PLAYER_TWO_NUMBER;
                maxMovesCounter--;
                int score = minimaxPlayerOne(N, M, K, tab, !maximizedPlayer, alpha, beta, j, i, maxMovesCounter);
                maxMovesCounter++;
                tab[i][j] = 0;
                if (score == -1)
                    return score;
                if (score < *minScore)
                    *minScore = score;
                if (score < beta)
                    beta = score;
                if (beta <= alpha)
                    break;
            }
        }
    }
    return *minScore;
}

int maximasePlayerOne(int N, int M, int** tab, int* maxScore, int K, bool maximizedPlayer, int alpha, int beta, int maxMovesCounter) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (tab[i][j] == 0) {
                tab[i][j] = PLAYER_ONE_NUMBER;
                maxMovesCounter--;
                int score = minimaxPlayerOne(N, M, K, tab, !maximizedPlayer, alpha, beta, j, i, maxMovesCounter);
                maxMovesCounter++;
                tab[i][j] = 0;
                if (score == 1)
                    return score;
                if (score > *maxScore)
                    *maxScore = score;
                if (score > alpha)
                    alpha = score;
                if (beta <= alpha)
                    break;
            }
        }
    }
    return *maxScore;
}

int minimasePlayerTwo(int N, int M, int** tab, int* minScore, int K, bool maximizedPlayer, int alpha, int beta, int maxMovesCounter);
int maximasePlayerTwo(int N, int M, int** tab, int* maxScore, int K, bool maximizedPlayer, int alpha, int beta, int maxMovesCounter);

int minimaxPlayerTwo(int N, int M, int K, int** tab, bool maximizedPlayer, int alpha, int beta, int j, int i, int maxMovesCounter) {
    int check = checkWinSolveSingle(N, M, K, tab, j, i, maxMovesCounter);
    if (check != 3) {
        if (check == 2)
            return 0;
        if (check == 0)
            return -1;
        if (check == 1)
            return 1;
    }
    if ((N > MINIMAL_SEQUENCE_BOARD_LENGTH || M > MINIMAL_SEQUENCE_BOARD_LENGTH) && (K < N || K < M)) {
        int checkSequence = checkKMinusOneSequence(N, M, tab, K, i, j);
        if (checkSequence != 2) {
            if (checkSequence == 1)
                if (!checkIfPlayerOneWinsInNextTurn(N, M, K, tab))
                    return 1;
            if (checkSequence == 0)
                if (!checkIfPlayerTwoWinsInNextTurn(N, M, K, tab))
                    return -1;
        }
    }
    if (maximizedPlayer) {
        int maxScore = -1000;
        maxScore = maximasePlayerTwo(N, M, tab, &maxScore, K, maximizedPlayer, alpha, beta, maxMovesCounter);
        return maxScore;
    }
    else {
        int minScore = 1000;
        minScore = minimasePlayerTwo(N, M, tab, &minScore, K, maximizedPlayer, alpha, beta, maxMovesCounter);
        return minScore;
    }
}

int minimasePlayerTwo(int N, int M, int** tab, int* minScore, int K, bool maximizedPlayer, int alpha, int beta, int maxMovesCounter) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (tab[i][j] == 0) {
                tab[i][j] = PLAYER_ONE_NUMBER;
                maxMovesCounter--;
                int score = minimaxPlayerTwo(N, M, K, tab, !maximizedPlayer, alpha, beta, j, i, maxMovesCounter);
                maxMovesCounter++;
                tab[i][j] = 0;
                if (score == -1)
                    return score;
                if (score < *minScore)
                    *minScore = score;
                if (score < beta)
                    beta = score;
                if (beta <= alpha)
                    break;
            }
        }
    }
    return *minScore;
}

int maximasePlayerTwo(int N, int M, int** tab, int* maxScore, int K, bool maximizedPlayer, int alpha, int beta, int maxMovesCounter) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (tab[i][j] == 0) {
                tab[i][j] = PLAYER_TWO_NUMBER;
                maxMovesCounter--;
                int score = minimaxPlayerTwo(N, M, K, tab, !maximizedPlayer, alpha, beta, j, i, maxMovesCounter);
                maxMovesCounter++;
                tab[i][j] = 0;
                if (score == 1)
                    return score;
                if (score > *maxScore)
                    *maxScore = score;
                if (score > alpha)
                    alpha = score;
                if (beta <= alpha)
                    break;
            }
        }
    }
    return *maxScore;
}


int countMaxMovesNumber(int N, int M, int** tab) {
    int maxMovesCounter = N * M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (tab[i][j] != 0)
                maxMovesCounter--;
        }
    }
    return maxMovesCounter;
}

bool Move(int N, int M, int K, int ActivePlayer, int** tab, int maxMovesCounter) {
    int bestScore = -1000;
    int bestMove[2];
    bestMove[0] = -1;
    bestMove[1] = -1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (tab[i][j] == 0) {
                tab[i][j] = ActivePlayer;
                int result = checkWinSolveSingle(N, M, K, tab, j, i, maxMovesCounter);
                if (result != 3) {
                    if (result == 0) {
                        printf("FIRST_PLAYER_WINS\n");
                        return false;
                    }
                    else if (result == 1) {
                        printf("SECOND_PLAYER_WINS\n");
                        return false;
                    }
                    else if (result == 2) {
                        printf("BOTH_PLAYERS_TIE\n");
                        return false;
                    }
                }
                int score;
                maxMovesCounter--;
                if (ActivePlayer == PLAYER_TWO_NUMBER)
                    score = minimaxPlayerTwo(N, M, K, tab, false, -1000, 1000, j, i, maxMovesCounter);
                else score = minimaxPlayerOne(N, M, K, tab, false, -1000, 1000, j, i, maxMovesCounter);
                maxMovesCounter++;
                tab[i][j] = 0;
                if (score > bestScore) {
                    bestScore = score;
                    bestMove[0] = i;
                    bestMove[1] = j;
                }
            }
        }
    }
    if (bestMove[0] != -1 && bestMove[1] != -1)
        tab[bestMove[0]][bestMove[1]] = ActivePlayer;
    return true;
}

void solveGameState(int N, int M, int K, int ActivePlayer, int** tab) {
    int maxMovesCounter = countMaxMovesNumber(N, M, tab);
    int resultBefore = checkWin(N, M, K, tab);
    if (resultBefore == 2) {
        printf("BOTH_PLAYERS_TIE\n");
        return;
    }
    else if (resultBefore == 1) {
        printf("SECOND_PLAYER_WINS\n");
        return;
    }
    else if (resultBefore == 0) {
        printf("FIRST_PLAYER_WINS\n");
        return;
    }
    while (maxMovesCounter > 0) {
        if (Move(N, M, K, ActivePlayer, tab, maxMovesCounter) == false)
            return;
        maxMovesCounter--;
        ActivePlayer = 3 - ActivePlayer;
    }
    int resultAfter = checkWin(N, M, K, tab);
    if (resultAfter == 2) {
        printf("BOTH_PLAYERS_TIE\n");
        return;
    }
    else if (resultAfter == 1) {
        printf("SECOND_PLAYER_WINS\n");
        return;
    }
    else if (resultAfter == 0) {
        printf("FIRST_PLAYER_WINS\n");
        return;
    }
}

int** commandGEN_ALL_POS_MOV(int N, int M, int K, int ActivePlayer, int** tab, bool* initialisedWhole, bool* initialisedRows, int* lastN, int* lastM) {
    scanf("%d%d%d%d", &N, &M, &K, &ActivePlayer);
    if (!*initialisedWhole || *lastN != N) {
        tab = new int* [N];
        *initialisedWhole = true;
        *lastN = N;
    }
    for (int i = 0; i < N; i++) {
        if (!*initialisedRows || *lastM != M)
            tab[i] = new int[M];
        for (int j = 0; j < M; j++) {
            scanf("%d", &tab[i][j]);
        }
    }
    *initialisedRows = true;
    *lastM = M;
    generateAllMoves(N, M, K, ActivePlayer, tab);
    return tab;
}

int** commandGEN_ALL_POS_MOV_CUT_IF_GAME_OVER(int N, int M, int K, int ActivePlayer, int** tab, bool* initialisedWhole, bool* initialisedRows, int* lastN, int* lastM) {
    scanf("%d%d%d%d", &N, &M, &K, &ActivePlayer);
    if (!*initialisedWhole || *lastN != N) {
        tab = new int* [N];
        *initialisedWhole = true;
        *lastN = N;
    }
    for (int i = 0; i < N; i++) {
        if (!*initialisedRows || *lastM != M)
            tab[i] = new int[M];
        for (int j = 0; j < M; j++) {
            scanf("%d", &tab[i][j]);
        }
    }
    *initialisedRows = true;
    *lastM = M;
    generateAllMovesWinningMove(N, M, K, ActivePlayer, tab);
    return tab;
}

int** commandSOLVE_GAME_STATE(int N, int M, int K, int ActivePlayer, int **tab, bool *initialisedWhole, bool* initialisedRows, int *lastN, int *lastM) {
    scanf("%d%d%d%d", &N, &M, &K, &ActivePlayer);
    if (!*initialisedWhole || *lastN != N) {
        tab = new int* [N];
        *initialisedWhole = true;
        *lastN = N;
    }
    for (int i = 0; i < N; i++) {
        if (!*initialisedRows || *lastM != M)
            tab[i] = new int[M];
        for (int j = 0; j < M; j++) {
            scanf("%d", &tab[i][j]);
        }
    }
    *initialisedRows = true;
    *lastM = M;
    solveGameState(N, M, K, ActivePlayer, tab);
    return tab;
}

int main() {
    char* command = new char[MAX_COMMAND_LENGTH];
    int N = 0, M = 0, K = 0, ActivePlayer = 0, lastN = 0, lastM = 0;
    int** tab = NULL;
    bool initialisedWhole = false;
    bool initialisedRows = false;
    while (scanf("%s", command) != EOF) {
        if (strcmp(command, "GEN_ALL_POS_MOV") == 0) {
            tab = commandGEN_ALL_POS_MOV(N, M, K, ActivePlayer, tab, &initialisedWhole, &initialisedRows, &lastN, &lastM);
        }

        else if (strcmp(command, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER") == 0) {
            tab = commandGEN_ALL_POS_MOV_CUT_IF_GAME_OVER(N, M, K, ActivePlayer, tab, &initialisedWhole, &initialisedRows, &lastN, &lastM);
        }

        else if (strcmp(command, "SOLVE_GAME_STATE") == 0) {
            tab = commandSOLVE_GAME_STATE(N, M, K, ActivePlayer, tab, &initialisedWhole, &initialisedRows, &lastN, &lastM);
        }
    }
    for (int i = 0; i < N; i++)
         delete[] tab[i];
    delete[] tab;
    delete[] command;
    return 0;
}