#include <ncurses.h>
#include <string.h>

#define KEY_ESCAPE  27
#define KEY_TAB     9

struct TaskBarItem {
    int         index,
                windows;
    char       *name;
    WINDOW     *win_left,
               *win_right;
};

void draw_taskbar(struct TaskBarItem bar[], int tasks, int active)
{
    move(0, 0);

    int color,
        nb_cols = 0;

    for (int i = 0; i < tasks; i++)
    {
        color = bar[i].index == active ? 2 : 1;
        attron(COLOR_PAIR(color));

        printw(bar[i].name);
        int name_length = strlen(bar[i].name);
        nb_cols += name_length;
        for (int j = 0; j < COLS / tasks - name_length; j++)
        {
            printw(" ");
            nb_cols++;
        }

        attroff(COLOR_PAIR(color));
    }

    attron(COLOR_PAIR(color));

    for (; nb_cols < COLS; nb_cols++)
        printw(" ");

    attroff(COLOR_PAIR(color));

    move (1, 0);
}

int main ()
{
    int _Tasks      = 2,
        _Active     = 1,
        _Key;

    struct TaskBarItem _TaskBar[_Tasks];

    _TaskBar[0].index = 1;
    _TaskBar[0].name = "F1: Shell";
    _TaskBar[0].windows = 1;

    _TaskBar[1].index = 2;
    _TaskBar[1].name = "F2: Overview";
    _TaskBar[1].windows = 2;


    initscr();
    start_color();
    keypad(stdscr, TRUE);
    cbreak();
    noecho();

    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);


    while (true)
    {
        draw_taskbar(_TaskBar, _Tasks, _Active);
        refresh();

        timeout(0);
        _Key = getch();
        if (_Key == KEY_ESCAPE)
            break;
        else if (_Key == KEY_TAB)
            _Active = _Active < _Tasks ? _Active + 1 : 1;
    }

    endwin();

    return 0;
}

