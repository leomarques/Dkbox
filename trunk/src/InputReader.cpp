#include "InputReader.h"

bool mouse1Free, mouse2Free, keyFree[10];
int mouseLock;

int readInput(void)
{
    if (mouse_b == 1)
    {
        if (mouseLock == -1) return MOUSE1;
        else
        {
            if (mouse1Free)
            {
                mouse1Free = false;
                return MOUSE1;
            }
        }
    }
    else mouse1Free = true;

    if (mouse_b == 2)
    {
        if (mouseLock == -1) return MOUSE2;
        else
        {
            if (mouse2Free)
            {
                mouse2Free = false;
                return MOUSE2;
            }
        }
    }
    else mouse2Free = true;

    for (int i = 0; i < 10; i++)
    {
        if (key[i + 27])
        {
            if (keyFree[i])
            {
                keyFree[i] = false;
                return i;
            }
        }
        else keyFree[i] = true;
    }

    if (key[KEY_TAB]) return TAB;

    if (key[KEY_ESC]) return QUIT;

    return NOINPUT;
}

void freeAllInput(void)
{
    mouse1Free = true;
    mouse2Free = true;
    mouseLock = 1;
    for (int i = 0; i < 10; i++) keyFree[i] = true;
}
