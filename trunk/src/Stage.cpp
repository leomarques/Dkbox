#include "Stage.h"

Stage::Stage()
{
    world = new World();
    debugDraw = new DebugDraw(buffer);
    freeDraw = new FreeDraw();

    bodyType = Free_Draw;
    debugDrawOn = false;
    bmpDrawOn = true;
    dt = counter;
    setMouseLock(false);

    createGround();
}

Stage::~Stage()
{
    delete freeDraw;
    delete debugDraw;
    delete world;
}

bool Stage::step(void)
{
    updateInput();

    menuOn = false;

    if (keys[KEYESC])
        return false;

    if (mouse[0])
    {
        switch (bodyType)
        {
        case Random:
            if (RANDOM(0, 1))
                world->makeBox(coordAllegToB2(Point(mouse_x, mouse_y)), b2Vec2(RANDBODYSIZE, RANDBODYSIZE));
            else
                world->makeCircle(coordAllegToB2(Point(mouse_x, mouse_y)), RANDBODYSIZE);
            break;

        case Box:
            world->makeBox(coordAllegToB2(Point(mouse_x, mouse_y)), b2Vec2(RANDBODYSIZE, RANDBODYSIZE));
            break;

        case Circle:
            world->makeCircle(coordAllegToB2(Point(mouse_x, mouse_y)), RANDBODYSIZE);
            break;

        case Free_Draw:
            freeDraw->takePoint(Point(mouse_x, mouse_y));
            break;
        }
    }
    else
    {
        if (freeDraw->On)
            freeDraw->makeBody(world);
    }

    if (mouse[1])
        world->makeBomb(coordAllegToB2(Point(mouse_x, mouse_y)));

    if (keys[KEY1])
        bodyType = Random;

    if (keys[KEY2])
        bodyType = Box;

    if (keys[KEY3])
        bodyType = Circle;

    if (keys[KEY4])
    {
        bodyType = Free_Draw;
        setMouseLock(false);
    }

    if (keys[KEY5])
        pyramidShow();

    if (keys[KEY6])
        world->destroyLastBody();

    if (keys[KEY7])
        world->toggleStaticMode();

    if (keys[KEY8])
        world->toggleSimulation();

    if (keys[KEY9])
        if (bodyType != Free_Draw)
            toggleMouseLock();

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
                toggleDebugDraw();
            }
        }
        else
        {
            toggleDebugDraw();
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
            if (!bmp)
                continue;

            Point p = b->getAllegPosition();
            int x = p.x - (bmp->w / 2);
            int y = p.y - (bmp->h / 2);

            rotate_sprite(buffer, bmp, x, y, b->getAllegAngle());
        }

    if (freeDraw->On)
        draw_sprite(buffer, freeDraw->bmp, 0, 0);

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

    case Free_Draw:
        textprintf_ex(buffer, font, 100, 15, PURPLE, -1, "Free Draw");
        break;

    default:
        break;
    }

    textprintf_ex(buffer, font, 200, 15, GRAY, -1, "Static mode:");
    if (world->staticModeOn)
        textprintf_ex(buffer, font, 310, 15, GREEN, -1, "On");
    else
        textprintf_ex(buffer, font, 310, 15, RED, -1, "Off");

    textprintf_ex(buffer, font, 400, 15, GRAY, -1, "Mouse lock:");
    if (mouseLockOn)
        textprintf_ex(buffer, font, 500, 15, GREEN, -1, "On");
    else
        textprintf_ex(buffer, font, 500, 15, RED, -1, "Off");

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
        textprintf_ex(buffer, font, 10, 150, BLUE, -1, "5 : Pyramid");
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

void Stage::toggleDebugDraw(void)
{
    world->setDebugDraw(debugDrawOn ? NULL : debugDraw);
    debugDrawOn = !debugDrawOn;
}

void Stage::createGround(void)
{
    world->staticModeOn = true;
    world->makeBox(coordAllegToB2(Point(SCREEN_W / 2, SCREEN_H - 15)), b2Vec2(6.0f, 0.15f));
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
            world->makeBox(b2Vec2(xl, y), b2Vec2(size, size));
    }

    world->makeBomb(b2Vec2(-0.5f, 0.3f));
    world->makeBomb(b2Vec2(0.5f, 0.3f));
    world->makeBomb(b2Vec2(0.0f, 0.3f));
}
