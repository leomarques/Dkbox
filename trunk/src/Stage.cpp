#include "Stage.h"

Stage::Stage()
{
    world = new World();
    bodyType = Random;
    debugDrawOn = false;
    bmpDrawOn = true;
    dt = counter;
    createGround();
}

Stage::~Stage()
{
    delete world;
}

bool Stage::step(void)
{
    updateInput();

    menuOn = false;

    if (keys[KEYESC]) return false;

    if (mouse[0])
    {
        switch (bodyType)
        {
        case Random:
            if (RANDOM(0, 1))
                world->makeBox(coordAllegToB2(mouse_x, mouse_y), b2Vec2(RANDBODYSIZE, RANDBODYSIZE));
            else
                world->makeCircle(coordAllegToB2(mouse_x, mouse_y), RANDBODYSIZE);
            break;

        case Box:
            world->makeBox(coordAllegToB2(mouse_x, mouse_y), b2Vec2(RANDBODYSIZE, RANDBODYSIZE));
            break;

        case Circle:
            world->makeCircle(coordAllegToB2(mouse_x, mouse_y), RANDBODYSIZE);
            break;
        }
    }

    if (mouse[1])
    {
        world->makeBomb(coordAllegToB2(mouse_x, mouse_y));
    }

    if (keys[KEY1])
    {
        bodyType = Random;
    }

    if (keys[KEY2])
    {
        bodyType = Box;
    }

    if (keys[KEY3])
    {
        bodyType = Circle;
    }

    if (keys[KEY4])
    {
        pyramidShow();
    }

    if (keys[KEY6]) world->destroyLastBody();

    if (keys[KEY7]) world->toggleStaticMode();

    if (keys[KEY8]) world->toggleSimulation();

    if (keys[KEY9]) toggleMouseLock();

    if (keys[KEY0])
    {
        world->destroyAllBodies();
        createGround();
    }

    if (keys[KEYTAB])
        menuOn = true;

    if (keys[KEYD])
    {
        if (debugDrawOn)
        {
            if (bmpDrawOn)
            {
                bmpDrawOn = false;
            }
            else
            {
                bmpDrawOn = true;
                world->toggleDebugDraw();
                debugDrawOn = false;
            }
        }
        else
        {
            world->toggleDebugDraw();
            debugDrawOn = true;
        }
    }

    world->simulate();

    return true;
}

void Stage::render(void)
{
    if (bmpDrawOn)
        for (vector<Body*>::iterator it = world->bodyList.begin(); it != world->bodyList.end(); ++it)
        {
            Body *b = *it;
            BITMAP *bmp = b->bmp;
            if (!bmp) continue;

            int x = (int) ((b->body->GetPosition().x * SCALE) - (bmp->w / 2) + (SCREEN_W / 2));
            int y = (int) (- ((b->body->GetPosition().y * SCALE) + (bmp->h / 2)) + SCREEN_H);

            rotate_sprite(buffer, bmp, x, y, fixmul(ftofix(- b->body->GetAngle()), radtofix_r));
        }

    /*************************************************************************************************/
    // TODO: Bind this.
    textprintf_centre_ex(buffer, font, SCREEN_W / 2, 40, GREEN, -1, "Hold TAB for menu");

    textprintf_ex(buffer, font, 10, 15, GRAY, -1, "Body type:");
    switch (bodyType)
    {
    case Random:
        textprintf_ex(buffer, font, 100, 15, BLUE, -1, "Random");
        break;

    case Box:
        textprintf_ex(buffer, font, 100, 15, YELLOW, -1, "Box");
        break;

    case Circle:
        textprintf_ex(buffer, font, 100, 15, YELLOW, -1, "Circle");
        break;

    default:
        break;
    }

    textprintf_ex(buffer, font, 200, 15, GRAY, -1, "Static mode:");
    if (world->staticModeOn) textprintf_ex(buffer, font, 310, 15, GREEN, -1, "On");
    else textprintf_ex(buffer, font, 310, 15, RED, -1, "Off");

    textprintf_ex(buffer, font, 400, 15, GRAY, -1, "Mouse lock:");
    if (mouseLockOn) textprintf_ex(buffer, font, 500, 15, GREEN, -1, "On");
    else textprintf_ex(buffer, font, 500, 15, RED, -1, "Off");

    if (!world->simulateOn)
        textprintf_centre_ex(buffer, font, SCREEN_W / 2, 65, YELLOW, -1, "PAUSED");

    textprintf_ex(buffer, font, 10, 40, GRAY, -1, "Bodies:");
    textprintf_ex(buffer, font, 70, 40, world->bodyList.size() > 400 ? RED : GRAY, -1, "%d", world->bodyList.size());

    dt = (int) (counter - dt);
    if (dt == 0) dt = 1;
    int fps = FPS / dt;
    dt = counter;

    textprintf_ex(buffer, font, 10, 65, GRAY, -1, "Approx. FPS:");
textprintf_ex(buffer, font, 110, 65, fps < FPS ? fps < (FPS / 2) ? RED : YELLOW : GREEN, -1, "%d", fps);

    if (menuOn)
    {
        textprintf_ex(buffer, font, 10, 85, BLUE, -1, "Press keys 0-9 to choose options");
        textprintf_ex(buffer, font, 10, 100, BLUE, -1, "0 : Reset");
        textprintf_ex(buffer, font, 10, 110, BLUE, -1, "1 : Random bodies");
        textprintf_ex(buffer, font, 10, 120, BLUE, -1, "2 : Box");
        textprintf_ex(buffer, font, 10, 130, BLUE, -1, "3 : Circle");
        textprintf_ex(buffer, font, 10, 140, BLUE, -1, "4 : Free draw");
        textprintf_ex(buffer, font, 10, 150, BLUE, -1, "5 : Custom box");
        textprintf_ex(buffer, font, 10, 160, BLUE, -1, "6 : Destroy last body");
        textprintf_ex(buffer, font, 10, 170, BLUE, -1, "7 : Toggle static mode");
        textprintf_ex(buffer, font, 10, 180, BLUE, -1, "8 : Pause");
        textprintf_ex(buffer, font, 10, 190, BLUE, -1, "9 : Toggle Mouse lock");
        textprintf_ex(buffer, font, 10, 205, BLUE, -1, "MB1 : Make bodies");
        textprintf_ex(buffer, font, 10, 215, BLUE, -1, "MB2 : Make bombs");
    }
    /*************************************************************************************************/

    draw_sprite(buffer, mouse_sprite, mouse_x, mouse_y);

    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    clear_bitmap(buffer);
}

void Stage::createGround(void)
{
    world->staticModeOn = true;
    world->makeBox(coordAllegToB2(SCREEN_W / 2, SCREEN_H - 15), b2Vec2(6.0f, 0.15f));
    world->staticModeOn = false;
}

void Stage::pyramidShow(void)
{
    float32 size = 0.2f;
    int rows = 15;

    float32 x = -(size * rows) + size, y = 5.0f;

    for (int i = rows; i > 0; i--, x += size, y += (size * 2))
    {
        float32 xl = x;
        for (int j = 0; j < i; j++, xl += (size * 2))
        {
            world->makeBox(b2Vec2(xl, y), b2Vec2(size, size));
        }
    }

    world->makeBomb(b2Vec2(-0.5f, 0.3f));
    world->makeBomb(b2Vec2(0.5f, 0.3f));
    world->makeBomb(b2Vec2(0.0f, 0.3f));
}
