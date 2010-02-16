#include "Input.h"

bool keys[NKEYS];
bool mouse[2];

Key _keys[NKEYS];
Mouse _mouse[2];

bool mouseLockOn;

void initKeys(void)
{
    for (int i = 0; i < 10; i++)
        _keys[i] = Key(&key[i + 27]);

    _keys[KEYD] = Key(&key[KEY_D]);
    _keys[KEYESC] = Key(&key[KEY_ESC]);
    _keys[KEYTAB] = Key(&key[KEY_TAB]);

    setKeyLock(KEYTAB, false);
}

void initMouse(void)
{
    _mouse[0] = Mouse(1);
    _mouse[1] = Mouse(2);

    mouseLockOn = false;
}

void updateKeys(void)
{
    for (int i = 0; i < NKEYS; i++)
        keys[i] = _keys[i].isPressed();
}

void updateMouse(void)
{
    mouse[0] = _mouse[0].isPressed();
    mouse[1] = _mouse[1].isPressed();
}

void inputInit(void)
{
    initKeys();
    initMouse();
    updateInput();
}

void updateInput(void)
{
    updateKeys();
    updateMouse();
}

Key::Key(volatile char *end)
{
    this->end = end;
    hasLock = true;
    isLocked = false;
}

Mouse::Mouse(volatile int b)
{
    this->b = b;
    this->end = &mouse_b;
    hasLock = true;
    isLocked = false;
}

bool Key::isPressed()
{
    if (*end)
    {
        if (hasLock)
        {
            if (isLocked)
            {
                return false;
            }
            else
            {
                isLocked = true;
                return true;
            }
        }
        return true;
    }

    isLocked = false;
    return false;
}

bool Mouse::isPressed()
{
    if (*end == b)
    {
        if (hasLock)
        {
            if (isLocked)
            {
                return false;
            }
            else
            {
                isLocked = true;
                return true;
            }
        }
        return true;
    }

    isLocked = false;
    return false;
}

void setKeyLock(int k, bool hasLock)
{
    _keys[k].hasLock = hasLock;
}

void setMouseLock(bool hasLock)
{
    _mouse[0].hasLock = hasLock;
    _mouse[1].hasLock = hasLock;
    mouseLockOn = hasLock;
}

void toggleMouseLock(void)
{
    _mouse[0].hasLock = !(_mouse[0].hasLock);
    _mouse[1].hasLock = !(_mouse[1].hasLock);
    mouseLockOn = !mouseLockOn;
}
