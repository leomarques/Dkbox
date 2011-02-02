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
    _keys[KEYP] = Key(&key[KEY_P]);
    _keys[KEYH] = Key(&key[KEY_H]);
    _keys[KEYA] = Key(&key[KEY_A]);
    _keys[KEYC] = Key(&key[KEY_C]);
    _keys[KEYN] = Key(&key[KEY_N]);
    _keys[KEYM] = Key(&key[KEY_M]);
    _keys[KEYX] = Key(&key[KEY_X]);
    _keys[KEYS] = Key(&key[KEY_S]);
    _keys[KEYUP] = Key(&key[KEY_UP]);
    _keys[KEYDOWN] = Key(&key[KEY_DOWN]);
    _keys[KEYLEFT] = Key(&key[KEY_LEFT]);
    _keys[KEYRIGHT] = Key(&key[KEY_RIGHT]);
    _keys[KEYESC] = Key(&key[KEY_ESC]);
    _keys[KEYTAB] = Key(&key[KEY_TAB]);
    _keys[KEYV] = Key(&key[KEY_V]);

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
