#include <ncurses.h>
#include <cdk/cdk.h>
#include <string.h>

#define KEY_ESCAPE  27
#define KEY_Y       121
#define KEY_N       110

struct TaskBarItem {
    int         index,
                windows;
    char       *name;
    WINDOW     *win_left,
               *win_right;
};

struct Node {
    int         r,
                p,
                online;
};

void draw_taskbar(struct TaskBarItem bar[], int tasks, int active)
{
    move(0, 0);

    int color,
        nb_cols = 0;

    for (int i = 0; i < tasks; i++)
    {
        char name[256];
        strcpy(name, bar[i].name);

        if (bar[i].index == active)
        {
            color = 2;
            strcat(name, " (active)");
        }
        else
            color = 1;

        attron(COLOR_PAIR(color));

        printw(name);
        int name_length = strlen(name);
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

    move(1, 0);
}

void task_overview(WINDOW *win)
{
    wmove(win, 1, 1);
    wprintw(win, "Nodes list.");

    wmove(win, 4, 1);

    // Display a node
    wattron(win, COLOR_PAIR(3));
    wprintw(win, "r01p01");
    wattroff(win, COLOR_PAIR(3));

    wmove (win, 6, 1);

    // Display a node
    wattron(win, COLOR_PAIR(4));
    wprintw(win, "r02p01");
    wattroff(win, COLOR_PAIR(4));
}

void draw_windows(struct TaskBarItem task)
{
    int winwidth = COLS;
    if (task.windows == 2)
    {
        winwidth /= 2;
        task.win_right = newwin(LINES - 1, winwidth, 1, winwidth);
        wrefresh(task.win_right);
    }
    task.win_left = newwin(LINES - 1, winwidth, 1, 0);

    switch (task.index)
    {
        case 2:
            task_overview(task.win_left);
            break;
    }

    wrefresh(task.win_left);
}

int main ()
{
    int *_C = 1; // if != 0 => refresh()

    CDKSCREEN *cdkscreen;
    WINDOW *ncurses;

    CDKLABEL *close;
    char *close_text[3];
    close_text[0] = "Do you really want to quit?";
    close_text[1] = "";
    close_text[2] = "Y: yes, N: no";

    int _Tasks      = 3,
        _Active     = 1,
        _Key;

    struct TaskBarItem _TaskBar[_Tasks];

    _TaskBar[0].index = 1;
    _TaskBar[0].name = "F1: Shell";
    _TaskBar[0].windows = 1;

    _TaskBar[1].index = 2;
    _TaskBar[1].name = "F2: Overview";
    _TaskBar[1].windows = 2;

    _TaskBar[2].index = 3;
    _TaskBar[2].name = "F3: About/help";
    _TaskBar[2].windows = 1;


    ncurses = initscr();
    cdkscreen = initCDKScreen(ncurses);
    start_color();
    keypad(stdscr, TRUE);
    cbreak();
    noecho();

    // TaskBar
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    // Overview
    init_pair(3, COLOR_BLACK, COLOR_GREEN);
    init_pair(4, COLOR_WHITE, COLOR_RED);


    showGUI:
    while (true)
    {
        if (_C != 0)
        {
            draw_taskbar(_TaskBar, _Tasks, _Active);
            refresh();
            draw_windows(_TaskBar[_Active - 1]);
            refresh();
        }

        timeout(0);
        _Key = getch();
        _C = 1;
        if (_Key == KEY_ESCAPE)
            break;
        else if (_Key == KEY_TAB)
            _Active = _Active < _Tasks ? _Active + 1 : 1;
        else
            _C = 0;

        goto showGUI;
    }


    close = newCDKLabel(cdkscreen, CENTER, CENTER, close_text, 3, TRUE, FALSE);
    refreshCDKScreen(cdkscreen);
    refresh();

    while (true)
    {
        int k = getch();
        if (k == KEY_N)
        {
            destroyCDKLabel(close);
            refreshCDKScreen(cdkscreen);
            goto showGUI;
        }
        else if (k == KEY_Y)
            break;
    }

    endwin();

    return 0;
}

