#include "Engine.h"

volatile int counter, fpsControl, closeButtonPressed;

void startEngine(void)
{
    init();
    playGame();
    gameEnd();
}

void init(void)
{
    if (allegro_init() ||
            install_keyboard() ||
            install_mouse() == -1)
        abortOnError();

    push_config_state();
    set_config_file("config.ini");

    int resX = get_config_int(NULL, "resX", DEFAULTRESX);
    int resY = get_config_int(NULL, "resY", DEFAULTRESY);

    set_color_depth(get_config_int(NULL, "color depth", DEFAULTCOLORDEPTH));

    if (ustricmp(get_config_string(NULL, "fullscreen", "false"), "true") == 0)
    {
        if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, resX, resY, 0, 0))
            abortOnError();
    }
    else
    {
        if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, resX, resY, 0, 0))
            abortOnError();
    }

    pop_config_state();

    set_window_title(WINTITLE);

    inputInit();
    srand(time(NULL));

    closeButtonPressed = FALSE;
    LOCK_FUNCTION(closeButtonHandler);
    set_close_button_callback(closeButtonHandler);

    counter = fpsControl = 0;
    LOCK_VARIABLE(counter);
    LOCK_FUNCTION(timer);
    install_int_ex(timer, BPS_TO_TIMER(FPS));
}

void playGame(void)
{
    gameInit();

    while (!closeButtonPressed)
    {
        if (counter >= fpsControl)
        {
            if (!gameStep())
                break;

            BITMAP *bmp = gameRender();
            blit(bmp, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
			clear_bitmap(bmp);

            fpsControl = counter + 1;
        }
    }
}

void abortOnError(void)
{
    allegro_message("Error: %s =(", allegro_error);
    exit(1);
}

void closeButtonHandler(void)
{
    closeButtonPressed = TRUE;
}
END_OF_FUNCTION(closeButtonHandler)

void timer(void)
{
    counter++;
}
END_OF_FUNCTION(timer)
