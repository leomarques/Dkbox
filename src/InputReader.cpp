#include "InputReader.h"

bool keyFree[NKEYS];
int mouseLock;

int readInput(void)
{
    if (mouse_b == 1)
    {
        if (mouseLock == -1) return MOUSE1;
        else
        {
            if (key[MOUSE1])
            {
                key[MOUSE1] = false;
                return MOUSE1;
            }
        }
    }
    else key[MOUSE1] = true;

    if (mouse_b == 2)
    {
        if (mouseLock == -1) return MOUSE2;
        else
        {
            if (key[MOUSE2])
            {
                key[MOUSE2] = false;
                return MOUSE2;
            }
        }
    }
    else key[MOUSE2] = true;

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

    if (key[KEY_D])
    {
        if (keyFree[KEYD])
        {
            keyFree[KEYD] = false;
            return KEYD;
        }
    }
    else keyFree[KEYD] = true;

    if (key[KEY_TAB]) return KEYTAB;

    if (key[KEY_ESC]) return QUIT;


    return NOINPUT;
}

void freeAllInput(void)
{
    mouseLock = -1;
    for (int i = 0; i < NKEYS; i++) keyFree[i] = true;
}
