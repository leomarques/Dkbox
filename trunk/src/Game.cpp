#include "Game.h"

b2World *world;
BodyManager *bm;
DebugDraw *debugDraw;
BITMAP *buffer;
int simulate = 1;
bool menuOn = false, customBoxOn = false, freeDrawOn = true, debugDrawOn = true, bmpDrawOn = false;
long long int counter2 = 1;

void gameInit(void)
{
    set_window_title("Dickbox by LeoDick");
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    if (!buffer) exit(-1);
    clear_bitmap(buffer);

    // Creating world.
    b2AABB worldAABB;
    worldAABB.lowerBound.Set(-40.0f, -20.0f);
    worldAABB.upperBound.Set(40.0f, 100.0f);

    // 2nd parameter is gravity, 3rd is for letting bodies sleep.
    world = new b2World(worldAABB, b2Vec2(0.0f, -10.0f), true);

    world->SetBoundaryListener(new BoundaryListener());

    // Initializing DebugDraw.
    // TODO: Bind this.
    debugDraw = new DebugDraw(buffer);
    uint32 flags = 0;
    flags += b2DebugDraw::e_shapeBit;
    flags += b2DebugDraw::e_coreShapeBit;
    debugDraw->SetFlags(flags);
    if (debugDrawOn) world->SetDebugDraw(debugDraw);

    bm = new BodyManager(world);

    srand(time(NULL));
    freeAllInput();
}

bool gameStep(void)
{
    int in = readInput();
    switch (in)
    {
    case NOINPUT: // No input was entered.
        menuOn = false;
        break;

    case QUIT: // ESC was pressed, quits game.
        return false;

    case MOUSE1: // Makes body.
    case MOUSE2: // Makes bomb.
        bm->getInput(in);
        break;

    case 1: // Random body.
    case 2: // Boxes only.
    case 3: // Circles only.
        customBoxOn = false;
        freeDrawOn = false;
        bm->getInput(in);
        break;

    case 4: // Free draw mode.
        mouseLock = -1;
        freeDrawOn = true;
        bm->getInput(in);
        break;

    case 5: // Custom box mode.
        mouseLock = -1;
        customBoxOn = true;
        bm->getInput(in);
        break;

    case 6: // Destroy last body.
    case 7: // Static mode.
    case 0: // Reset.
        bm->getInput(in);
        break;

    case 8: // Play/pause simulation.
        simulate *= -1;
        break;

    case 9: // Turn on/off mouse lock.
        if (!customBoxOn && !freeDrawOn)
            mouseLock *= -1;
        break;

    case KEYTAB: // Menu.
        menuOn = true;
        break;

    case KEYD: // DebugDraw.
        if (debugDrawOn)
        {
            if (bmpDrawOn)
            {
                bmpDrawOn = false;
            }
            else
            {
                bmpDrawOn = true;
                world->SetDebugDraw(NULL);
                debugDrawOn = false;
            }
        }
        else
        {
            world->SetDebugDraw(debugDraw);
            debugDrawOn = true;
        }
        break;

    default:
        break;
    }

    // Now we let Newton do his thing.
    if (simulate == 1)
    {
        world->Step(timeStep, iterations);

        bm->destroyOOBBodies();
        bm->checkBombs();
    }

    bm->checkCustomBox();
    bm->checkFreeDraw();

    return true;
}

void gameRender(int counter1)
{
    // Drawing bodies
    int count = 0, bodyCount = world->GetBodyCount() - 1;
    if (bmpDrawOn)
        for (b2Body* body = world->GetBodyList(); count < bodyCount; body = body->GetNext(), count++)
        {
            BITMAP* bmp = (BITMAP*) (body->GetUserData());
            if (!bmp) continue;

            int x = (int) ((body->GetPosition().x * SCALE) - (bmp->w / 2) + (SCREEN_W / 2));
            int y = (int) (- ((body->GetPosition().y * SCALE) + (bmp->h / 2)) + SCREEN_H);

            rotate_sprite(buffer, bmp, x, y, fixmul(ftofix(- body->GetAngle()), radtofix_r));
            //printf("%f %f\n", body->GetPosition().x, body->GetPosition().y);
        }

    // Drawing custom box.
    if (bm->customModeOn)
    {
        rect(buffer, bm->cusX1, bm->cusY1, bm->cusX2, bm->cusY2, GREEN);
    }

    // Drawing free draw.
    if (bm->freeDrawModeOn && bm->freeDrawPoints.size() >= 2)
    {
        Point p0 = bm->freeDrawPoints[0], p1;
        for (int i = 1; i < (int) bm->freeDrawPoints.size(); i++)
        {
            p1 = bm->freeDrawPoints[i];

            line(buffer, p0.x, p0.y, p1.x, p1.y, BLUE);

            p0 = p1;
        }
    }

    // Drawing menu.
    // TODO: Fix hardcoded coordinates.
    textprintf_centre_ex(buffer, font, SCREEN_W / 2, 40, GREEN, -1, "Hold TAB for menu");

    textprintf_ex(buffer, font, 10, 15, GRAY, -1, "Body type:");
    switch (bm->bodyType)
    {
    case 1:
        textprintf_ex(buffer, font, 100, 15, BLUE, -1, "Random");
        break;

    case 2:
        textprintf_ex(buffer, font, 100, 15, YELLOW, -1, "Boxes");
        break;

    case 3:
        textprintf_ex(buffer, font, 100, 15, YELLOW, -1, "Circles");
        break;

    case 4:
        textprintf_ex(buffer, font, 100, 15, RED, -1, "Free draw");
        break;

    case 5:
        textprintf_ex(buffer, font, 100, 15, PURPLE, -1, "Custom box");
        break;

    default:
        break;
    }

    textprintf_ex(buffer, font, 200, 15, GRAY, -1, "Static mode:");
    if (bm->staticMode == 1) textprintf_ex(buffer, font, 310, 15, GREEN, -1, "On");
    else textprintf_ex(buffer, font, 310, 15, RED, -1, "Off");

    textprintf_ex(buffer, font, 400, 15, GRAY, -1, "Mouse lock:");
    if (mouseLock == 1) textprintf_ex(buffer, font, 500, 15, GREEN, -1, "On");
    else textprintf_ex(buffer, font, 500, 15, RED, -1, "Off");

    if (simulate == -1)
        textprintf_centre_ex(buffer, font, SCREEN_W / 2, 65, YELLOW, -1, "PAUSED");

    textprintf_ex(buffer, font, 10, 45, GRAY, -1, "Bodies:");
    textprintf_ex(buffer, font, 70, 45, bodyCount > 400 ? RED : GRAY, -1, "%d", bodyCount);
    textprintf_ex(buffer, font, 10, 55, GRAY, -1, "Bombs: %d", bm->GetBombCount());

    // Calculate FPS.
    counter2 = (int) (counter1 - counter2);
    if (counter2 == 0) counter2 = 1;
    int fps = 60 / counter2;
    counter2 = counter1;

    textprintf_ex(buffer, font, 10, 65, GRAY, -1, "Approx. FPS:");
    textprintf_ex(buffer, font, 110, 65, fps < 60 ? fps < 30 ? RED : YELLOW : GREEN, -1, "%d", fps);

    if (menuOn)
    {
        textprintf_ex(buffer, font, 10, 85, BLUE, -1, "Press keys 0-9 to choose options");
        textprintf_ex(buffer, font, 10, 100, BLUE, -1, "0 : Reset");
        textprintf_ex(buffer, font, 10, 110, BLUE, -1, "1 : Random bodies");
        textprintf_ex(buffer, font, 10, 120, BLUE, -1, "2 : Boxes");
        textprintf_ex(buffer, font, 10, 130, BLUE, -1, "3 : Circles");
        textprintf_ex(buffer, font, 10, 140, BLUE, -1, "4 : Free draw");
        textprintf_ex(buffer, font, 10, 150, BLUE, -1, "5 : Custom boxes");
        textprintf_ex(buffer, font, 10, 160, BLUE, -1, "6 : Destroy last body");
        textprintf_ex(buffer, font, 10, 170, BLUE, -1, "7 : Static mode");
        textprintf_ex(buffer, font, 10, 180, BLUE, -1, "8 : Pause");
        textprintf_ex(buffer, font, 10, 190, BLUE, -1, "9 : Mouse lock");
        textprintf_ex(buffer, font, 10, 205, BLUE, -1, "MB1 : Make bodies");
        textprintf_ex(buffer, font, 10, 215, BLUE, -1, "MB2 : Make bombs");
    }

    draw_sprite(buffer, mouse_sprite, mouse_x, mouse_y);

    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    clear_bitmap(buffer);
}

void gameEnd(void)
{
    delete bm;
    delete world;
    show_mouse(NULL);
    destroy_bitmap(buffer);
}
