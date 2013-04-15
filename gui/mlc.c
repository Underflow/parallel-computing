#include <ncurses.h>
#include <cdk/cdk.h>
#include <string.h>

#define KEY_ESCAPE  27
#define KEY_Y       121
#define KEY_N       110
#define NODE_NLEN   7 // strlen("r00p00\s")

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
                room,
                online;
};

int _C = 1; // if != 0 => refresh()

int _Rooms[6];
int _CurrentRoom;

struct Node _Nodes[30];

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
    // Temp
    _Nodes[0].r = 1;
    _Nodes[0].p = 1;
    _Nodes[0].room = 304;
    _Nodes[0].online = 1;

    _Nodes[1].r = 1;
    _Nodes[1].p = 2;
    _Nodes[1].room = 304;
    _Nodes[1].online = 1;

    _Nodes[2].r = 1;
    _Nodes[2].p = 3;
    _Nodes[2].room = 304;
    _Nodes[2].online = 0;

    _Nodes[3].r = 1;
    _Nodes[3].p = 4;
    _Nodes[3].room = 304;
    _Nodes[3].online = 1;

    _Nodes[4].r = 1;
    _Nodes[4].p = 1;
    _Nodes[4].room = 306;
    _Nodes[4].online = 1;

    _Nodes[5].r = 2;
    _Nodes[5].p = 1;
    _Nodes[5].room = 304;
    _Nodes[5].online = 1;

    _Nodes[6].r = 2;
    _Nodes[6].p = 2;
    _Nodes[6].room = 304;
    _Nodes[6].online = 1;

    _Nodes[7].r = 1;
    _Nodes[7].p = 2;
    _Nodes[7].room = 306;
    _Nodes[7].online = 1;

    _Nodes[8].r = 3;
    _Nodes[8].p = 1;
    _Nodes[8].room = 304;
    _Nodes[8].online = 0;

    _Nodes[9].r = 3;
    _Nodes[9].p = 2;
    _Nodes[9].room = 304;
    _Nodes[9].online = 1;

    _Nodes[10].r = 3;
    _Nodes[10].p = 3;
    _Nodes[10].room = 304;
    _Nodes[10].online = 1;

    _Nodes[11].r = 2;
    _Nodes[11].p = 1;
    _Nodes[11].room = 306;
    _Nodes[11].online = 1;


    wmove(win, 1, 1);
    /*wprintw(win, "Nodes list. Total: %d", sizeof(_Nodes) / sizeof(struct Node));
    wmove(win, 3, 1);*/
    wprintw(win, "Current room: %d. Nodes: %d.", _Rooms[_CurrentRoom],
        sizeof(_Nodes) / sizeof(struct Node));

    for (int i = 0; i < sizeof(_Nodes) / sizeof(struct Node); i++)
    {
        if (_Nodes[i].r != 0 && _Nodes[i].p != 0 && _Rooms[_CurrentRoom] == _Nodes[i].room)
        {
            wmove(win,
                1 + 2 * _Nodes[i].r,
                1 + (_Nodes[i].p - 1) * NODE_NLEN);

            int color = 3 + _Nodes[i].online;
            wattron(win, COLOR_PAIR(color));
            wprintw(win, "r%02dp%02d", _Nodes[i].r, _Nodes[i].p);
            wattroff(win, COLOR_PAIR(color));
        }
    }
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

    _Rooms[0] = 301;
    _Rooms[1] = 302;
    _Rooms[2] = 303;
    _Rooms[3] = 304;
    _Rooms[4] = 305;
    _Rooms[5] = 306;
    _CurrentRoom = 0;

    ncurses = initscr();
    cdkscreen = initCDKScreen(ncurses);
    start_color();
    initCDKColor();
    keypad(stdscr, TRUE);
    cbreak();
    noecho();

    // TaskBar
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    // Overview
    init_pair(3, COLOR_WHITE, COLOR_RED);
    init_pair(4, COLOR_BLACK, COLOR_GREEN);


    int cache_cols = COLS,
        cache_lines = LINES;

    showGUI:
    while (true)
    {
        if (_C != 0)
        {
            draw_taskbar(_TaskBar, _Tasks, _Active);
            refresh();
            draw_windows(_TaskBar[_Active - 1]);
            refresh();
            _C = 0;
        }

        timeout(0);
        _Key = getch();
        if (_Key == KEY_ESCAPE)
            break;
        else if (_Key == KEY_TAB)
        {
            _C = 1;
            _Active = _Active < _Tasks ? _Active + 1 : 1;
        }

        // Shell
        if (_Active == 1)
        {
        }
        // Overview
        else if (_Active == 2)
        {
            switch (_Key)
            {
                case KEY_RIGHT:
                    if (_CurrentRoom + 1 < sizeof(_Rooms) / sizeof(int))
                        _CurrentRoom++;
                    _C = 1;
                    break;
                case KEY_LEFT:
                    if (_CurrentRoom - 1 >= 0)
                        _CurrentRoom--;
                    _C = 1;
                    break;
            }
        }

        if (cache_cols != COLS || cache_lines != LINES)
        {
            _C = 1;
            cache_cols = COLS;
            cache_lines = LINES;
        }
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

