#include <ncurses.h>

#define KEY_ESCAPE 27

int main ()
{
    WINDOW *win_logs, *win_nodes, *win_term;
    int _Key, _Active = 1;

    initscr();
    start_color();
    keypad(stdscr, TRUE);

    win_logs = newwin(LINES, COLS / 2, 0, 0);
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    wattron(win_logs, COLOR_PAIR(1));
    box(win_logs, 0, 0);
    wprintw(win_logs, "Test\n");
    wrefresh(win_logs);
    wattroff(win_logs, COLOR_PAIR(1));
    refresh();

    /*while (true)
    {
        timeout(0);
        _Key = getch();
        if (_Key == KEY_ESCAPE)
            break;

        switch (_Key)
        {
            case KEY_F(1):
                _Active = 1;
                break;
            case KEY_F(2):
                _Active = 2;
                break;
            case KEY_F(3):
                _Active = 3;
                break;
        }

        //wprintw(win_logs, "Test");
        wrefresh(win_logs);
        //printw("Active: %d\n", _Active);
        refresh();
    }*/


    /*cbreak();
    noecho();
    refresh();*/

    getch();
    endwin();

    return 0;
}

