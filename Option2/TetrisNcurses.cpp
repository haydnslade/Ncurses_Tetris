/*
*
 */
#include "TetrisNcurses.h"

TetrisDrawerNcurses::TetrisDrawerNcurses(Tetris *tetris)
  : TetrisDrawer(tetris)
{
  initscr();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  bkgd(COLOR_PAIR(1));
  curs_set(false);
  noecho();
  refresh();
  keypad(stdscr, true);
  nodelay(stdscr, true);
  //Colors for blocks
  init_pair(11, COLOR_RED, COLOR_RED);
  init_pair(12, COLOR_GREEN, COLOR_GREEN);
  init_pair(13, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(14, COLOR_BLUE, COLOR_BLUE);
  init_pair(15, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(16, COLOR_CYAN, COLOR_CYAN);
  init_pair(17, COLOR_WHITE, COLOR_WHITE);
}

TetrisDrawerNcurses::~TetrisDrawerNcurses()
{
  endwin();
}

void TetrisDrawerNcurses::drawGrid(int x, int y, const char *dot)
{
  move(x, y);
  addstr(dot);
}

void TetrisDrawerNcurses::drawGrid(int x, int y, const char dot)
{
  move(x, y);
  addch(dot);
}

void TetrisDrawerNcurses::drawGrid(int x, int y, BarType type)
{
  switch(type) {
    case BAR_TYPE_I:
        attron(COLOR_PAIR(11));
        break;
    case BAR_TYPE_J:
        attron(COLOR_PAIR(12));
        break;
    case BAR_TYPE_L:
        attron(COLOR_PAIR(13));
        break;
    case BAR_TYPE_O:
        attron(COLOR_PAIR(14));
        break;
    case BAR_TYPE_S:
        attron(COLOR_PAIR(15));
        break;
    case BAR_TYPE_T:
        attron(COLOR_PAIR(16));
        break;
    case BAR_TYPE_Z:
        attron(COLOR_PAIR(17));
        break;
  }  
  drawGrid(x, y, (char) type);
  attron(COLOR_PAIR(1));
}

void TetrisDrawerNcurses::drawGrid(int x, int y, unsigned value)
{
  static const char number[] = "0123456789";
  int digit = 0;
  unsigned remain = value;

  while (remain >= 10) {
    remain /= 10;
    digit++;
  }

  while (digit >= 1) {
    drawGrid(x, y + digit, number[value % 10]);
    value /= 10;
    digit--;
  }

  drawGrid(x, y, number[value % 10]);
}

void TetrisDrawerNcurses::drawFrameTopOrButtom(int row, int col, int baseCol)
{
  drawGrid(row, baseCol, "+");//left corners
  for (int c = 1; c < col + 1; ++c)
    drawGrid(row, baseCol + c, "-");//top and bottom
  drawGrid(row, baseCol + col + 1, "+");//right norders
}

void TetrisDrawerNcurses::drawFrameInner(int row, int col, int baseCol)
{
  drawGrid(row, baseCol, "|");//walls left
  drawGrid(row, baseCol + col + 1, "|");//right
}

void TetrisDrawerNcurses::drawFrame(TetrisField * field, int baseCol)
{
  int row = field->getRow();
  int col = field->getCol();
  drawFrameTopOrButtom(0, col, baseCol);
  for (int r = 1; r < row + 1; ++r)
    drawFrameInner(r, col, baseCol);
  drawFrameTopOrButtom(row + 1, col, baseCol);
}

void TetrisDrawerNcurses::drawField(TetrisField *field, int baseCol)
{
  int row = field->getRow();
  int col = field->getCol();
  for (int r = 0; r < row; ++r)
    for (int c = 0; c < col; ++c)
      drawGrid(r + 1, baseCol + c + 1, field->getGrid(r, c));
}

void TetrisDrawerNcurses::drawBar(const TetrisBar *bar, int rot, int r, int c)
{
  BarType type = bar->getType();
  int indexSize = bar->getIndexSize();
  for (int pos = 0; pos < indexSize; ++pos) {
    TetrisIndex index = bar->getIndex(pos, rot);
    drawGrid(r + index.r, c + index.c, type);
  }
}

void TetrisDrawerNcurses::drawBar(TetrisField *field, int baseCol)
{
  const TetrisBar *bar = field->getBar();
  TetrisIndex index = field->getBarIndex();
  int rot = field->getBarRot();
  drawBar(bar, rot, index.r + 1, baseCol + index.c + 1);
}

#define TETRIS_DRAW(field, name, r, c)              \
  do {                                              \
    static const char prefix[] = #name ": ";        \
    static const size_t size = sizeof(prefix);      \
    drawGrid(r, c + 1, prefix);                     \
    drawGrid(r, c + 1 + size, field->get##name());  \
  } while (0)

void TetrisDrawerNcurses::drawLevel(TetrisField *field, int baseCol) //mine
{
  TETRIS_DRAW(field, Level, 10, 31); //mine where level is displayed
}

void TetrisDrawerNcurses::drawScore(TetrisField *field, int baseCol)
{
  //TETRIS_DRAW(field, Score, TETRIS_FIELD_ROW + 3, baseCol);
  TETRIS_DRAW(field, Score, 5, 31); //mine where score is displayed
}

void TetrisDrawerNcurses::drawNextBar(TetrisField *field, int baseCol)
{
  const TetrisBar *nextBar = field->getNextBar();
  int nextRot = field->getNextBarRot();
  //drawBar(nextBar, nextRot, 2, TETRIS_FIELD_COL + 5 + baseCol);
  drawBar(nextBar, nextRot, 2, 35);//mine
}

void TetrisDrawerNcurses::gameover()
{
  ::erase();
  drawGrid(10, 15, "Game Over");//10 and 15 is row and column
  refresh();
  sleep(1);// added so you can see message
  curs_set(true);
  keypad(stdscr, false);
  nodelay(stdscr, false);
  standend();
  endwin();
}

TetrisInputerNcurses::TetrisInputerNcurses(Tetris *tetris)
  : TetrisInputer(tetris)
{

}

InputType TetrisInputerNcurses::input()
{
  int ch = getch();
  if (ch < 0)
    return INPUT_TYPE_EMPTY;
  switch (ch) {
#define CASE(key, type) case key: { return type; }
    //CASE(KEY_UP, INPUT_TYPE_UP); //got rid of up here
    CASE(KEY_DOWN, INPUT_TYPE_DOWN);
    CASE(KEY_RIGHT, INPUT_TYPE_RIGHT);
    CASE(KEY_LEFT, INPUT_TYPE_LEFT);
    CASE('z', INPUT_TYPE_ROT_LEFT);
    CASE('x', INPUT_TYPE_ROT_RIGHT);
    CASE('q', INPUT_TYPE_QUIT); // added so you can quit
  }
  return INPUT_TYPE_EMPTY;
}

TetrisNcurses::TetrisNcurses()
{
  registerDrawer(mDrawer = new TetrisDrawerNcurses(this));
  registerInputer(mInputer = new TetrisInputerNcurses(this));
  registerTimer(mTimer = new TetrisTimerPthread(this));
}

TetrisNcurses::~TetrisNcurses()
{
  delete mDrawer;
  delete mInputer;
  delete mTimer;
}
