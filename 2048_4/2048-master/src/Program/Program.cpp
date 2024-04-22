#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Program.hpp"
#include "../Window/GameWindow.hpp"
#include "../Game/Game.hpp"
#include "../Animation/Animator.hpp"
bool Program::m_is_running = false;
int Program::m_ret_value = EXIT_SUCCESS;

int Program::start(const std::vector<std::string>& args)
{
    GameWindow window(Definitions::GAME_WINDOW_WIDTH, Definitions::GAME_WINDOW_HEIGHT, Definitions::GAME_WINDOW_NAME);
    NumberedRect::init_numbers(window);
    Game game(window);
    game.start();
    m_is_running = true;
    SDL_Event event;

    while (is_running())
    {
        while (SDL_PollEvent(&event))
        {
            game.event_handler(event);
        }
        game.animate();
        window.clear();
        window.add(game.get_background());
        window.add(game.get_rects());
        window.display_game_over(game.display_game_over());
        window.display_score();
        window.display_stats_button();
        window.render_finish();
    }
    return m_ret_value;
}

void Program::stop(bool force)
{
    m_is_running = false;
}
