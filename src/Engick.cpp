#include "Engick.h"

volatile long long int counter;
volatile int closeButtonPressed;
long long int speedControl = 0;

///////////////////
// Start engine. //
///////////////////

void engickStart(void)
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

    // Reads configurations from config.ini, if not found, uses default.
    push_config_state();
    set_config_file("config.ini");

    int resX = get_config_int(NULL, "resX", DEFAULTRESX);
    int resY = get_config_int(NULL, "resY", DEFAULTRESY);

    set_color_depth(get_config_int(NULL, "color depth", DEFAULTCOLORDEPTH));

    if (ustricmp(get_config_string(NULL, "fullscreen", "false"), "true") == 0)
    {
        if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, resX, resY, 0, 0)) abortOnError();
    }
    else
    {
        if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, resX, resY, 0, 0)) abortOnError();
    }

    pop_config_state();

    // Sets the window close button to actually close the window.
    closeButtonPressed = FALSE;
    LOCK_FUNCTION(closeButtonHandler);
    set_close_button_callback(closeButtonHandler);

    // Sets up the timer to control game speed.
    counter = 0;
    LOCK_VARIABLE(counter);
    LOCK_FUNCTION(timer);
    install_int_ex(timer, BPS_TO_TIMER(FPS));
}

////////////////////
// Play the game. //
////////////////////

void playGame(void)
{
    gameInit();

    //Game loop.
    while (!closeButtonPressed)
    {
        if (counter >= speedControl)
        {
            if (!gameStep()) return;
            gameRender(counter);

            speedControl = counter + 1;
        }
    }
}

//////////////////////////////
// Close-related functions. //
//////////////////////////////

void abortOnError(void)
{
    allegro_message("Error: %s =(", allegro_error);
    exit(-1);
}

void closeButtonHandler(void)
{
    closeButtonPressed = TRUE;
}
END_OF_FUNCTION(closeButtonHandler)

/////////////////////
// Timer function. //
/////////////////////

void timer(void)
{
    if (++counter < 0)
    {
        counter = 0;
        speedControl = 0;
    }
}
END_OF_FUNCTION(timer)
