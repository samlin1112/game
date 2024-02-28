#include <bits/stdc++.h>
using namespace std;
class tictactoe {
  static const int SIZE = 3; // 棋盤大�?
public:
  enum Player { NONE, PLAYER_X, PLAYER_O }; // ?�家類�?

  struct Move {
    int row;
    int col;
  };
  //輸出棋盤
  void out(Player board[SIZE][SIZE]) {
    for (int i = 0; i < 3; i++) {
      if (board[i][0] == 2) {
        cout << 'O';
      } else if (board[i][0] == 1) {
        cout << 'X';
      } else {
        cout << ' ';
      }
      cout << '|';
      if (board[i][1] == 2) {
        cout << 'O';
      } else if (board[i][1] == 1) {
        cout << 'X';
      } else {
        cout << ' ';
      }
      cout << '|';
      if (board[i][2] == 2) {
        cout << 'O';
      } else if (board[i][2] == 1) {
        cout << 'X';
      } else {
        cout << ' ';
      }
      if (i != 2) {
        cout << "\n-+-+-";
      }
      cout << "\n";
    }
  }
  // ?�斷?�戲?�否结�?
  bool isGameOver(Player board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
      if (board[row][0] != NONE && board[row][0] == board[row][1] &&
          board[row][0] == board[row][2]) {
        return true;
      }
    }
    for (int col = 0; col < SIZE; col++) {
      if (board[0][col] != NONE && board[0][col] == board[1][col] &&
          board[0][col] == board[2][col]) {
        return true;
      }
    }
    if (board[0][0] != NONE && board[0][0] == board[1][1] &&
        board[0][0] == board[2][2]) {
      return true;
    }
    if (board[0][2] != NONE && board[0][2] == board[1][1] &&
        board[0][2] == board[2][0]) {
      return true;
    }

    for (int row = 0; row < SIZE; row++) {
      for (int col = 0; col < SIZE; col++) {
        if (board[row][col] == NONE) {
          return false;
        }
      }
    }

    return true;
  }

  // 計�?模擬?�??�??�??�數
  int evaluateBoard(Player board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
      if (board[row][0] != NONE && board[row][0] == board[row][1] &&
          board[row][0] == board[row][2]) {
        if (board[row][0] == PLAYER_X) {
          return 1;
        } else {
          return -1;
        }
      }
    }

    for (int col = 0; col < SIZE; col++) {
      if (board[0][col] != NONE && board[0][col] == board[1][col] &&
          board[0][col] == board[2][col]) {
        if (board[0][col] == PLAYER_X) {
          return 1;
        } else {
          return -1;
        }
      }
    }

    if (board[0][0] != NONE && board[0][0] == board[1][1] &&
        board[0][0] == board[2][2]) {
      if (board[0][0] == PLAYER_X) {
        return 1;
      } else {
        return -1;
      }
    }
    if (board[0][2] != NONE && board[0][2] == board[1][1] &&
        board[0][2] == board[2][0]) {
      if (board[0][2] == PLAYER_X) {
        return 1;
      } else {
        return -1;
      }
    }

    return 0;
  }

  // ?�??�小�?大�?�?
  int minimax(Player board[SIZE][SIZE], int alpha, int beta, bool isMaximizer) {
    // �ˬd�C�O�_�Ψ�F�̤j�`�
    if (isGameOver(board)) {
      int s = evaluateBoard(board);
      return s;
    }

    if (isMaximizer) {
      int maxScore = INT_MIN;
      for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
          if (board[row][col] == NONE) {
            board[row][col] = PLAYER_X;
            int score = minimax(board, alpha, beta, false);
            board[row][col] = NONE;
            maxScore = max(maxScore, score);
            alpha = max(alpha, score);
            if (beta <= alpha)
              break; // Beta �ŪK
          }
        }
      }
      return maxScore;
    } else {
      int minScore = INT_MAX;
      for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
          if (board[row][col] == NONE) {
            board[row][col] = PLAYER_O;
            int score = minimax(board, alpha, beta, true);
            board[row][col] = NONE;
            minScore = min(minScore, score);
            beta = min(beta, score);
            if (beta <= alpha)
              break; // Alpha �ŪK
          }
        }
      }
      return minScore;
    }
  }

  // ?�腦?�?佳移??
  Move getComputerMove(Player board[SIZE][SIZE]) {
    int maxScore = INT_MIN;
    Move bestMove;
    int ra = rand() % 2;
    int nd = rand() % 2;
    if (ra) {
      for (int row = 0; row < SIZE; row++) {
        if (nd) {
          for (int col = 0; col < SIZE; col++) {
            if (board[row][col] == NONE) {
              board[row][col] = PLAYER_X;
              int score = minimax(board, INT_MIN, INT_MAX, false);
              board[row][col] = NONE;
              if (score > maxScore) {
                maxScore = score;
                bestMove.row = row;
                bestMove.col = col;
              }
            }
          }
        } else {
          for (int col = SIZE - 1; col >= 0; col--) {
            if (board[row][col] == NONE) {
              board[row][col] = PLAYER_X;
              int score = minimax(board, INT_MIN, INT_MAX, false);
              board[row][col] = NONE;
              if (score > maxScore) {
                maxScore = score;
                bestMove.row = row;
                bestMove.col = col;
              }
            }
          }
        }
      }
    } else {
      for (int row = SIZE - 1; row >= 0; row--) {
        if (nd) {
          for (int col = 0; col < SIZE; col++) {
            if (board[row][col] == NONE) {
              board[row][col] = PLAYER_X;
              int score = minimax(board, INT_MIN, INT_MAX, false);
              board[row][col] = NONE;
              if (score > maxScore) {
                maxScore = score;
                bestMove.row = row;
                bestMove.col = col;
              }
            }
          }
        } else {
          for (int col = SIZE - 1; col >= 0; col--) {
            if (board[row][col] == NONE) {
              board[row][col] = PLAYER_X;
              int score = minimax(board, INT_MIN, INT_MAX, false);
              board[row][col] = NONE;
              if (score > maxScore) {
                maxScore = score;
                bestMove.row = row;
                bestMove.col = col;
              }
            }
          }
        }
      }
    }

    return bestMove;
  }
  // ?�戲主循??
  void playGame() {
    Player board[SIZE][SIZE];
    // ?�??�???
    for (int row = 0; row < SIZE; row++) {
      for (int col = 0; col < SIZE; col++) {
        board[row][col] = NONE;
      }
    }
    Player currentPlayer;
    bool gameOver = false;
    int a;
    do {
      int ra = rand() % 2;
      if (ra) {
        cout << "Do you want (1) first or (2) last?";
      } else {
        cout << "Enter 1 for first and 2 for last.";
      }
      cin >> a;
      if (cin.fail()) {
        cin.clear();
        cin.ignore(2048, '\n');
      }
    } while (a != 1 && a != 2);
    if (a == 1) {
      currentPlayer = PLAYER_O;
    } else {
      currentPlayer = PLAYER_X;
    }
    while (!gameOver) {
      // ?�家移�?
      if (currentPlayer == PLAYER_O) {
        int row, col;
        cout << "Enter(row col)";
        cin >> row >> col;

        // 檢查移�??�否?�?
        if (row - 1 >= 0 && row - 1 < SIZE && col - 1 >= 0 && col - 1 < SIZE &&
            board[row - 1][col - 1] == NONE) {
          board[row - 1][col - 1] = currentPlayer;
          currentPlayer = PLAYER_X;
        } else {
          if (cin.fail()) {
            cin.clear();
            cin.ignore(2048, '\n');
          }
          int ra = rand() % 3;
          if (ra == 1) {
            cout << "you cannot do that. ";
          } else if (ra == 2) {
            cout << "that's too bad! ";
          }
          cout << "cin again" << endl;
        }
      } else {
        // ?�腦移动
        Move computerMove = getComputerMove(board);
        board[computerMove.row][computerMove.col] = currentPlayer;
        currentPlayer = PLAYER_O;
        out(board);
      }

      // 檢查?�戲?�??
      if (isGameOver(board)) {
        gameOver = true;
        int score = evaluateBoard(board);

        out(board);
        if (score == 1) {
          cout << "computer win" << endl;
        } else if (score == -1) {
          cout << "you win" << endl;
        } else {
          cout << "tie" << endl;
        }
      }
    }
  }
  void play() {
    string bye[9] = {"bye bye",
                     "thank you for using",
                     "Goodbye",
                     "Have a nice day",
                     "Looking forward to meeting next time",
                     "Farewell",
                     "Let?�s play again next time",
                     "You did very well",
                     "I'm great, right?"};
    srand(time(0));
    string a;
    cout << "Enter rules:\n1 1|1 2|1 2\n---+---+---\n2 1|2 2|2 "
            "3\n---+---+---\n3 "
            "1|3 2|3 3\nYou are 'O',I am 'X'\n\n";
    playGame();
    cout << bye[rand() % 9] << '\n';
  }
};
class bingo {
public:
  int nums[5][5] = {{0}, {0}, {0}, {0}, {0}};
  int count = 0;
  int row;
  int col;
  int turn = 0;
  int level[5][5] = {{1, 1, 1, 1, 1},
                     {1, 1, 1, 1, 1},
                     {1, 1, 1, 1, 1},
                     {1, 1, 1, 1, 1},
                     {1, 1, 1, 1, 1}};
  int line = 0;

  void check() {
    line = 0;
    bool bingo = true;
    for (int i = 0; i < 5; i++) {
      bingo = true;                 // 每次迭代都重置 bingo
      for (int k = 0; k < 5; k++) { // 添加 k 的初始值
        if (nums[i][k] != 0) {
          bingo = false;
        }
      }
      if (bingo) {
        line += 1;
      }
    }

    for (int i = 0; i < 5; i++) {
      bingo = true;                 // 每次迭代都重置 bingo
      for (int k = 0; k < 5; k++) { // 添加 k 的初始值
        if (nums[k][i] != 0) {
          bingo = false;
        }
      }
      if (bingo) {
        line += 1;
      }
    }

    // 檢查斜線是否都為0
    bingo = true;
    for (int i = 0; i < 5; i++) {
      if (nums[i][i] != 0) {
        bingo = false;
        break;
      }
    }
    if (bingo) {
      line += 1;
    }

    bingo = true;
    for (int i = 0; i < 5; i++) {
      if (nums[i][4 - i] != 0) {
        bingo = false;
        break;
      }
    }
    if (bingo) {
      line += 1;
    }
    return;
  }
  //更改等級
  void change() {
    for (int i = 0; i < 5; i++) {
      if (level[i][col] != -1) {
        level[i][col] += 1;
      }
    }
    for (int i = 0; i < 5; i++) {
      if (level[row][i] != -1) {
        level[row][i] += 1;
      }
    }
    if (row == col) {
      for (int i = 0; i < 5; i++) {
        if (level[i][i] != -1) {
          level[i][i] += 1;
        }
      }
    }
    if (row == 4 - col) {
      for (int i = 0; i < 5; i++) {
        if (level[i][4 - i] != -1) {
          level[i][4 - i] += 1;
        }
      }
    }
    level[row][col] = -1;
  }
  //找最大
  void findmax() {
    int maxscore = 0;
    for (int i = 0; i < 5; i++) {
      for (int z = 0; z < 5; z++) {
        if (nums[i][z] != 0) {
          if (maxscore < level[i][z]) {
            maxscore = level[i][z];
            row = i;
            col = z;
          }
        }
      }
    }
  }
  void play() {
    cout << "Five lines will win\nDo you want to go first (0) or last (1)";

    while (true) {
      cin >> turn;
      if (turn == 0 || turn == 1) {
        break;
      } else {
        cout << "Do you want to go first (0) or last (1)";
      }
    }

    srand(time(0));
    char player;
    while (count < 25) {
      row = rand() % 5;
      col = rand() % 5;
      if (nums[row][col] == 0) {
        nums[row][col] = count + 1;
        count++;
      }
    }

    while (line < 5) {
      if (turn == 1) {
        turn = 0;
      } else {
        turn = 1;
      }
      if (turn == 0) {
        findmax();

        cout << "computer chose:" << nums[row][col] << endl;
        nums[row][col] = 0;
      } else {
        int a;
        bool findit = false;
        do {
          cout << "Enter the number you want to cross out";
          cin >> a;
          for (row = 0; row < 5; row++) {
            for (col = 0; col < 5; col++) {
              if (a == nums[row][col]) {
                nums[row][col] = 0;
                findit = true;
                break;
              }
            }
            if (a == nums[row][col]) {
              nums[row][col] = 0;
              findit = true;
              break;
            }
          }
        } while (!findit || a == 0);
      }
      level[row][col] = -1;
      change();
      //顯示
      for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
          if (nums[i][j] != 0) {
            cout << "*\t";
          } else {
            cout << "0\t";
          }
        }
        cout << endl;
      }
      check();
      //檢查
      cout << "Are you bingo(Y/N)";
      while (true) {
        cin >> player;
        if (player == 'Y' || player == 'y' || player == 'N' || player == 'n') {
          break;
        } else {
          cout << "Are you bingo(Y/N)";
        }
      }
      if (player == 'y') {
        player = 'Y';
      }
      if (line >= 5 && player == 'Y') {
        cout << "tie\n";
        break;
      } else if (line >= 5) {
        cout << "bingo, computer wins\n";
        break;
      } else if (player == 'Y') {
        cout << "you win\n";
        break;
      }
    }
  }
};
class Backgammon {
public:
  int sum;
  int D3;
  int P2D3;
  int AIAI;
  string map_c;
  int Map[17][17];
  int AI_Map[17][17];
  int P2[2];
  int A;
  int B;
  int END;
  int i;
  int checknumber;
  int P2checknumber;
  int dx[17][17];
  int AIdx[17][17];
  int P2dx[17][17];
  int AIP2dx[17][17];
  stack<vector<vector<int>>> lastdx;
  int thebest;
  int thebbest;
  int thebestX;
  int thebestY;
  int best;
  int bestX;
  int bestY;
  int timess;
  int xx;
  int yy;
  int numb;

  int YES;
  int P2YES;

  int point[2];
  int AIpoint[2];

  int testXcheck;
  int testYcheck;

  string bye[9];

  void playGame() {
    out();
    cout << "我的AI很廢 請讓AI先開始\n\n\n";
    vector<vector<int>> wait(17, vector<int>(17));
    for (int i = 0; i < 17; i++) {
      for (int j = 0; j < 17; j++) {
        wait[i][j] = Map[i][j];
      }
    }
    lastdx.push(wait);
    do {

      cobeMap();
      QusAI();
      sum++;
      m();
      check();
      if (END == 0) {
        Qus2();
        if (P2[0] == 0 && P2[1] == 0) {
          lastdx.pop();
          for (int i = 0; i < 17; i++) {
            for (int j = 0; j < 17; j++) {
              Map[i][j] = lastdx.top()[i][j];
            }
          }
          cout << "\033[0;0H\033[2J";
          sum -= 3;
          continue;
        }
        sum++;
        m();
        check();
      }
      if (END) {
        break;
      }
      vector<vector<int>> wait(17, vector<int>(17));
      for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 17; j++) {
          wait[i][j] = Map[i][j];
        }
      }
      lastdx.push(wait);
      cout << "\033[0;0H\033[2J";
      out();
    } while (END == 0);
    cout << "\n共下了" << sum << "次\n";
  }
  void out() {
    cout << "歡迎來到五子棋AI遊戲室\n規則同五子棋\n一共15 * 15 "
            "不得輸入超過15,程式將停止\n輸入方式 如:3 5\n輸入方式 如:13 "
            "5\n輸入方式 如:13 15\n悔棋輸入方式 0 0\n\n";
  }
  int QusAI(void) {
    thebest = 0;
    thebbest = 0;
    if (numb == 0) {
      Map[8][8] = 1;
      numb = 1;
    } else {
      for (int y = 1; y < 16; y++) {
        for (int x = 1; x < 16; x++) {
          AIdx[x][y] = 0;
        }
      }
      for (yy = 1; yy < 16; yy++) {
        for (xx = 1; xx < 16; xx++) {
          for (int y = 1; y < 16; y++) {
            for (int x = 1; x < 16; x++) {
              dx[x][y] = 0;
            }
          }
          for (int y = 1; y < 16; y++) {
            for (int x = 1; x < 16; x++) {
              P2dx[x][y] = 0;
            }
          }
          for (int y = 1; y < 16; y++) {
            for (int x = 1; x < 16; x++) {
              AIP2dx[x][y] = 0;
            }
          }
          cobeMap();
          if (AI_Map[xx][yy] == 0) {
            AIAI = 0;
            timess = 1;
            AI();
            if (AIAI == 1) {
              return 0;
            } else {
              timess = 0;
            }
            AI_Map[xx][yy] = 1;
            AI();
            thebest = 0;
            thebbest = 0;
            for (int y = 1; y < 16; y++) {
              for (int x = 1; x < 16; x++) {
                if (P2dx[x][y] > thebest) {
                  thebestX = x;
                  thebestY = y;
                  thebest = P2dx[x][y];
                }
              }
            }
            AIdx[xx][yy] = dx[thebestX][thebestY];
          }
        }
      }
      best = INT_MAX;
      for (int y = 1; y < 16; y++) {
        for (int x = 1; x < 16; x++) {
          if (AIdx[x][y] < best && AIdx[x][y] != 0) {
            bestX = x;
            bestY = y;
            best = AIdx[x][y];
          }
        }
      }

      Map[bestX][bestY] = 1;
      cout << "AI 下在" << bestX << ' ' << bestY << '\n';
    }
    return 0;
  }
  int check(void) {
    for (int y = 1; y < 16; y++) {
      for (int x = 1; x < 16; x++) {
        checknumber = 0;
        testXcheck = 1;
        testYcheck = 0;
        if (Map[x][y] == 1) {
          for (i = 0; i < 4; i++) {
            checknumber = 0;
            if (testP1(x, y) == 5) {
              cout << "\nAI win!!";
              END = 1;
              return 0;
            }
            if (i == 0) {
              testXcheck = 0;
              testYcheck = 1;
            }
            if (i == 1) {
              testXcheck = 1;
              testYcheck = 1;
            }
            if (i == 2) {
              testXcheck = 1;
              testYcheck = -1;
            }
          }
        }
        testXcheck = 1;
        testYcheck = 0;
        if (Map[x][y] == 2) {
          for (i = 0; i < 4; i++) {
            checknumber = 0;
            if (testP2(x, y) == 5) {
              cout << "\nP2 win!!";
              END = 1;
              return 0;
            }
            if (i == 0) {
              testXcheck = 0;
              testYcheck = 1;
            }
            if (i == 1) {
              testXcheck = 1;
              testYcheck = 1;
            }
            if (i == 2) {
              testXcheck = 1;
              testYcheck = -1;
            }
          }
        }
      }
    }
    return 0;
  }
  int AI(void) {
    for (int y = 1; y < 16; y++) {
      for (int x = 1; x < 16; x++) {
        if (AI_Map[x][y] == 0) {
          point[0] = 0;
          AIpoint[0] = 0;
          point[1] = 0;
          AIpoint[1] = 0;
          D3 = 0;
          P2D3 = 0;
          for (i = 0; i < 4; i++) {
            P2checknumber = 0;
            checknumber = 0;
            YES = 0;
            P2YES = 0;
            if (i == 0) {
              testXcheck = 1;
              testYcheck = 0;
              AI_testP1(x, y);
              AI_testP2(x, y);
              testXcheck = -1;
              testYcheck = 0;
              AI_testP1(x, y);
              AI_testP2(x, y);
            }
            if (i == 1) {
              testXcheck = 1;
              testYcheck = 1;
              AI_testP1(x, y);
              AI_testP2(x, y);
              testXcheck = -1;
              testYcheck = -1;
              AI_testP1(x, y);
              AI_testP2(x, y);
            }
            if (i == 2) {
              testXcheck = 1;
              testYcheck = -1;
              AI_testP1(x, y);
              AI_testP2(x, y);
              testXcheck = -1;
              testYcheck = 1;
              AI_testP1(x, y);
              AI_testP2(x, y);
            }
            if (i == 3) {
              testXcheck = 0;
              testYcheck = -1;
              AI_testP1(x, y);
              AI_testP2(x, y);
              testXcheck = 0;
              testYcheck = 1;
              AI_testP1(x, y);
              AI_testP2(x, y);
            }
            checknumber--;
            P2checknumber--;
            if (checknumber >= 5) { //贏定了
              point[0] += 100000;
              AIpoint[0] += 150000;
              if (timess == 1) {
                Map[x][y] = 1;
                AIAI = 1;
                bestX = x;
                bestY = y;
                return 0;
              }
            } else if (checknumber == 4) { // 4子
              if (YES == 2) {              //活4
                point[0] += 51000;
                AIpoint[0] += 58000;
              } else if (D3 == 1) { //雙死四
                point[0] += 51000;
                AIpoint[0] += 58000;
              }
              // D3=1;
              else if (YES > 0) { //死四以上 計算一次
                point[0] += 1000;
                AIpoint[0] += 1500;
                D3 = 1;
              }
            } else if (checknumber == 3) { // 3子
              if (YES == 2) {              //活三
                point[0] += 1000;
                AIpoint[0] += 1500;
              } else if (D3 == 1) { //雙活三
                point[0] += 8000;
                AIpoint[0] += 10000;
              }
              // D3=1;

              else if (YES > 0) { //死3
                point[0] += 100;
                AIpoint[0] += 150;
                D3 = 1;
              }                            //死三
            } else if (checknumber == 2) { // 2子
              if (YES == 2) {              //活2
                point[0] += 100;
                AIpoint[0] += 150;
              } else {
                point[0] += 10;
                AIpoint[0] += 15;
              }
            }
            //------------------------------
            if (P2checknumber >= 5) { //贏定了
              AIpoint[1] += 100000;
              point[1] += 200000;
            } else if (P2checknumber == 4) { // 4子
              if (P2YES == 2) {              //活4
                AIpoint[1] += 51000;
                point[1] += 58000;
              } else if (P2D3 == 1) { //雙死四
                AIpoint[1] += 51000;
                point[1] += 58000;
              }
              // D3=1;
              else if (P2YES > 0) { //死四以上 計算一次
                AIpoint[1] += 1000;
                point[1] += 1500;
                P2D3 = 1;
              }
            } else if (P2checknumber == 3) { // 3子
              if (P2YES == 2) {              //活三
                AIpoint[1] += 1000;
                point[1] += 1500;
                P2D3 = 1;
              } else if (P2D3 == 1) { //雙活三
                AIpoint[1] += 8000;
                point[1] += 10000;
              }
              // D3=1;

              else if (YES > 0) { //死3
                AIpoint[1] += 100;
                point[1] += 150;

              }                              //死三
            } else if (P2checknumber == 2) { // 2子
              if (P2YES == 2) {              //活2
                AIpoint[1] += 100;
                point[1] += 150;
              } else {
                AIpoint[1] += 10;
                point[1] += 15;
              }
            }
          }
          if (timess == 1) {
            dx[x][y] += AIpoint[0];
          } else {
            P2dx[x][y] += point[0];
          }

          if (timess == 1) {
            dx[x][y] += AIpoint[1];
          } else {
            AIP2dx[x][y] += point[1];
            P2dx[x][y] += point[1];
            dx[x][y] = AIP2dx[x][y] - dx[xx][yy];
          }
        }
      }
    }

    return 0;
  }
  int Qus2(void) {
    cout << "玩家請輸入:";
    cin >> A >> B;
    if (A < 16 && B < 16) {
      while (Map[A][B] == 1 || Map[A][B] == 2) {
        cout << "已被佔據! 請從新一次:";
        cin >> A >> B;
      }
      P2[0] = A;
      P2[1] = B;
      Map[P2[0]][P2[1]] = 2;
    } else {
      cout << "你違反了規則 , 再見!\n";
    }
    return 0;
  }
  int m(void) {
    for (int a = 0; a < 16; a++) {
      Map[a][0] = a;
      Map[a][16] = a;
    }
    for (int a = 0; a < 16; a++) {
      Map[0][a] = a;
      Map[16][a] = a;
    }
    cout << '\n';

    for (int y = 0; y < 16; y++) {
      for (int x = 0; x < 16; x++) {
        if (x == 0 || y == 0) {
          printf("%3d", Map[x][y]);
        } else {
          if (x == bestX && y == bestY)
            cout << "  @";
          else
            cout << "  " << map_c[Map[x][y]];
        }
      }
      cout << '\n';
    }
    return 0;
  }
  int testP1(int x, int y) {
    if (x < 1 || y < 1 || x > 15 || y > 15) {
      return checknumber;
    }
    checknumber++;
    if (Map[x + testXcheck][y + testYcheck] == 1) {
      return (testP1(x + testXcheck, y + testYcheck));
    }
    return (checknumber);
  }
  int testP2(int x, int y) {
    if (x < 1 || y < 1 || x > 15 || y > 15) {
      return (checknumber);
    }
    checknumber++;
    if (Map[x + testXcheck][y + testYcheck] == 2) {
      return (testP2(x + testXcheck, y + testYcheck));
    }
    return (checknumber);
  }
  int cobeMap(void) {
    for (int y = 0; y < 16; y++) {
      for (int x = 0; x < 16; x++) {
        AI_Map[x][y] = Map[x][y];
      }
    }
    return 0;
  }
  int AI_testP1(int x, int y) {
    if (x < 1 || y < 1 || x > 15 || y > 15) {
      checknumber++;
      return 0;
    }
    checknumber++;
    if (AI_Map[x + testXcheck][y + testYcheck] == 1) {
      return (AI_testP1(x + testXcheck, y + testYcheck));
    } else {
      if (AI_Map[x + testXcheck][y + testYcheck] == 0) {
        YES++;
      }
    }
    return 0;
  }
  int AI_testP2(int x, int y) {
    if (x < 1 || y < 1 || x > 15 || y > 15) {
      P2checknumber++;
      return (P2checknumber);
    }
    P2checknumber++;
    if (AI_Map[x + testXcheck][y + testYcheck] == 2) {
      return (AI_testP2(x + testXcheck, y + testYcheck));
    } else {
      if (AI_Map[x + testXcheck][y + testYcheck] == 0) {
        P2YES++;
      }
    }
    return 0;
  }
  void play(void) {
    srand(time(NULL));
    playGame();
    cout << bye[rand() % 9] << '\n';
  }
};
class landmines {
  static const int size = 9; //大小
  static const int num = 10; //地雷數量
public:
  int a[size][size] = {{0}};  //正確棋盤
  bool f[size][size] = {{0}}; //是否顯示
  //找0
  void bfs(int x, int y) {
    queue<pair<int, int>> q;
    q.push(make_pair(x, y));
    while (!q.empty()) {
      x = q.front().first;
      y = q.front().second;
      q.pop();
      if (x + 1 < size && a[x + 1][y] == 0 && f[x + 1][y] == 0) {
        q.push(make_pair(x + 1, y));
        f[x + 1][y] = 1;
      }
      if (x - 1 >= 0 && a[x - 1][y] == 0 && f[x - 1][y] == 0) {
        q.push(make_pair(x - 1, y));
        f[x - 1][y] = 1;
      }
      if (y + 1 < size && a[x][y + 1] == 0 && f[x][y + 1] == 0) {
        q.push(make_pair(x, y + 1));
        f[x][y + 1] = 1;
      }
      if (y - 1 >= 0 && a[x][y - 1] == 0 && f[x][y - 1] == 0) {
        q.push(make_pair(x, y - 1));
        f[x][y - 1] = 1;
      }
    }
  }
  //輸出
  void out() {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        if (f[i][j]) {
          if (a[i][j] == -1) {
            cout << '*';
          } else {
            cout << a[i][j];
          }
        } else {
          cout << '-';
        }
        cout << ' ';
      }
      cout << '\n';
    }
  }
  //判斷遊戲結束
  bool over() {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        if (!f[i][j] && a[i][j] != -1) {
          return false;
        }
      }
    }
    return true;
  }
  void play() {
    srand(time(0));
    out();
    //第一次，避免立即死亡
    for (int i = 0; i < 1; i++) {
      int row, col;
      do {
        if (cin.fail()) {
          cin.clear();
          cin.ignore(2048, '\n');
        }
        cout << "輸入row col";
        cin >> row >> col;
      } while (row > size || col > size || row <= 0 || col <= 0 || cin.fail());
      row--;
      col--;
      for (int i = 0; i < num; i++) {
        int r = rand() % size, c = rand() % size;
        if (abs(r - row) + abs(c - col) <= 2) {
          i--;
        } else if (a[r][c] == 0) {
          a[r][c] = -1;
        } else {
          i--;
        }
      }
      for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
          if (a[i][j] == -1) {
            continue;
          }
          int sum = 0;
          if (i + 1 < size && a[i + 1][j] == -1) {
            sum++;
          }
          if (i - 1 >= 0 && a[i - 1][j] == -1) {
            sum++;
          }
          if (j + 1 < size && a[i][j + 1] == -1) {
            sum++;
          }
          if (j - 1 >= 0 && a[i][j - 1] == -1) {
            sum++;
          }
          if (i + 1 < size && j + 1 < size && a[i + 1][j + 1] == -1) {
            sum++;
          }
          if (i - 1 >= 0 && j + 1 < size && a[i - 1][j + 1] == -1) {
            sum++;
          }
          if (i + 1 < size && j - 1 >= 0 && a[i + 1][j - 1] == -1) {
            sum++;
          }
          if (i - 1 >= 0 && j - 1 >= 0 && a[i - 1][j - 1] == -1) {
            sum++;
          }
          a[i][j] = sum;
        }
      }
      f[row][col] = true;
      if (a[row][col] == 0) {
        bfs(row, col);
        for (int i = 0; i < 50; i++) {
          for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
              if (i + 1 < size && a[i + 1][j] == 0 && f[i + 1][j] == 1) {
                f[i][j] = 1;
              }
              if (i - 1 >= 0 && a[i - 1][j] == 0 && f[i - 1][j] == 1) {
                f[i][j] = 1;
              }
              if (j + 1 < size && a[i][j + 1] == 0 && f[i][j + 1] == 1) {
                f[i][j] = 1;
              }
              if (j - 1 >= 0 && a[i][j - 1] == 0 && f[i][j - 1] == 1) {
                f[i][j] = 1;
              }
              if (i + 1 < size && j + 1 < size && a[i + 1][j + 1] == 0 &&
                  f[i + 1][j + 1] == 1) {
                f[i][j] = 1;
              }
              if (i + 1 < size && j - 1 >= 0 && a[i + 1][j - 1] == 0 &&
                  f[i + 1][j - 1] == 1) {
                f[i][j] = 1;
              }
              if (i - 1 >= 0 && j + 1 < size && a[i - 1][j + 1] == 0 &&
                  f[i - 1][j + 1] == 1) {
                f[i][j] = 1;
              }
              if (i - 1 >= 0 && j - 1 >= 0 && a[i - 1][j - 1] == 0 &&
                  f[i - 1][j - 1] == 1) {
                f[i][j] = 1;
              }
            }
          }
        }
      }
    }
    //迴圈
    while (!over()) {
      out();
      int row, col;
      do {
        if (cin.fail()) {
          cin.clear();
          cin.ignore(2048, '\n');
        }
        cout << "輸入row col";
        cin >> row >> col;
      } while (row > size || col > size || row <= 0 || col <= 0 || cin.fail());
      row--;
      col--;
      if (a[row][col] == -1) {
        break;
      }
      f[row][col] = true;
      if (a[row][col] == 0) {
        bfs(row, col);
        for (int i = 0; i < size; i++) {
          for (int j = 0; j < size; j++) {
            if (i + 1 < size && a[i + 1][j] == 0 && f[i + 1][j] == 1) {
              f[i][j] = 1;
            }
            if (i - 1 >= 0 && a[i - 1][j] == 0 && f[i - 1][j] == 1) {
              f[i][j] = 1;
            }
            if (j + 1 < size && a[i][j + 1] == 0 && f[i][j + 1] == 1) {
              f[i][j] = 1;
            }
            if (j - 1 >= 0 && a[i][j - 1] == 0 && f[i][j - 1] == 1) {
              f[i][j] = 1;
            }
            if (i + 1 < size && j + 1 < size && a[i + 1][j + 1] == 0 &&
                f[i + 1][j + 1] == 1) {
              f[i][j] = 1;
            }
            if (i + 1 < size && j - 1 >= 0 && a[i + 1][j - 1] == 0 &&
                f[i + 1][j - 1] == 1) {
              f[i][j] = 1;
            }
            if (i - 1 < size && j + 1 < size && a[i - 1][j + 1] == 0 &&
                f[i - 1][j + 1] == 1) {
              f[i][j] = 1;
            }
            if (i - 1 < size && j - 1 >= 0 && a[i - 1][j - 1] == 0 &&
                f[i + 1][j - 1] == 1) {
              f[i][j] = 1;
            }
          }
        }
      }
    }
    //輸出完整棋盤
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        if (a[i][j] == -1) {
          cout << '*' << ' ';
        } else {
          cout << a[i][j] << ' ';
        }
      }
      cout << '\n';
    }
    //結果
    if (over()) {
      cout << "you win\n";
    } else {
      cout << "you die\n";
    }
  }
};
int main() {
  bingo bingo;
  tictactoe three;
  Backgammon five;
  landmines mine;
  int chose;
  cout << "你要玩什麼呢?\n井字棋按1\n五子棋按2\nbingo按3\n踩地雷按4\n離開按5\n";
  while (cin >> chose) {
    if (chose == 1) {
      three.play();
    } else if (chose == 2) {
      five.play();
    } else if (chose == 3) {
      bingo.play();
    } else if (chose == 4) {
      mine.play();
    } else if (chose == 5) {
      break;
    }
    cout << "\n\n你要玩什麼呢?\n井字棋按1\n五子棋按2\nbingo按3\n踩地雷按4\n離開按5\n";
  }
}
