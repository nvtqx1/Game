#include <SDL.h>
#include "Game.hpp"
#include <assert.h>
#include <time.h>
#include <fstream>
#include "../Program/Program.hpp"
#include "../Definitions/Rect.hpp"
#include "../Definitions/NumberedRect.hpp"
#include "../Animation/Move.hpp"
#include "../Animation/Spawn.hpp"
#include "../Animation/Merge.hpp"
#include "../Window/StatsWindow.hpp"
#define assert_coords(x, y) assert((x) >= 0 && (x) < Definitions::BLOCK_COUNT_X && (y) >= 0 && (y) < Definitions::BLOCK_COUNT_Y)

Game::Game(GameWindow& window) : m_window(window), m_canplay(false), m_won(false), m_start_time(0), m_score(0), m_stats_global(Definitions::STATS_FILE_NAME, m_window)
{
    m_background.emplace_back(0, 0, Definitions::BACKGROUND_COLOR, Definitions::GAME_WIDTH, Definitions::GAME_HEIGHT);
    for (std::size_t x = 0; x < Definitions::BLOCK_COUNT_X; ++x)
        for (std::size_t y = 0; y < Definitions::BLOCK_COUNT_Y; ++y)
        {
            m_background.emplace_back(Definitions::GAME_X + Definitions::BLOCK_SPACE + x * (Definitions::BLOCK_SIZE_X + Definitions::BLOCK_SPACE),
                Definitions::GAME_Y + Definitions::BLOCK_SPACE + y * (Definitions::BLOCK_SIZE_Y + Definitions::BLOCK_SPACE),
                Definitions::get_block_color(BLOCK_0));
        }

    if (Definitions::GAME_Y > 0)
        m_background.emplace_back(2, 2, Definitions::GREY_COLOR, Definitions::GAME_WIDTH - 4, Definitions::GAME_Y - 4);
    m_rects.resize(Definitions::BLOCK_COUNT_X, std::vector<std::shared_ptr<NumberedRect>>(Definitions::BLOCK_COUNT_Y, nullptr));
}

void Game::event_handler(const SDL_Event& event)
{
    switch (event.type)
    {
        case SDL_QUIT:
        {
            Program::stop(true);
            std::ofstream file(Definitions::STATS_FILE_NAME, std::ofstream::binary);
            m_stats_global += m_stats;
            file << m_stats_global;
            if (file.fail())
                m_window.warning("Could not save stats to " + Definitions::STATS_FILE_NAME + ".");
            break;
        }
        case SDL_KEYDOWN:
            key_handler(event.key);
            break;
        case SDL_MOUSEBUTTONUP:
            if (m_window.stats_button_clicked(event.button))
                show_stats();
            break;
    }
}

void Game::key_handler(const SDL_KeyboardEvent& keyevent)
{
    switch (keyevent.keysym.sym)
    {
        case SDLK_q:
            if (keyevent.keysym.mod & (KMOD_RCTRL | KMOD_LCTRL))
            {
                Program::stop(false);
            }
            break;
        case SDLK_LEFT: play(LEFT); break;
        case SDLK_RIGHT: play(RIGHT); break;
        case SDLK_UP: play(UP); break;
        case SDLK_DOWN: play(DOWN); break;
        case SDLK_r: restart(); break;
    }
}

void Game::start()
{
    for (int i = 0; i < Definitions::DEFAULT_START_BLOCKS; ++i)
        random_block();
    m_canplay = true;
    m_won = false;
    m_start_time = time(0);
    m_score = 0;
    m_window.update_score(std::to_string(m_score));
}

void Game::play(Directions direction)
{
    if (!can_play())
        return;

    bool played = false;

    switch (direction)
    {
        case LEFT:
            for (std::size_t y = 0; y < Definitions::BLOCK_COUNT_Y; ++y)
            {
                for (std::size_t x = 1; x < Definitions::BLOCK_COUNT_X; ++x)
                {
                    if (m_rects[x][y] == nullptr)
                        continue;
                    std::size_t i = x;
                    while (i > 0 && m_rects[--i][y] == nullptr); // find closest block
                    if (can_merge(m_rects[x][y], m_rects[i][y]))
                    {
                        merge_to(x, y, i, y);
                        played = true;
                    }
                    else if (m_rects[i][y] == nullptr || m_rects[++i][y] == nullptr)
                    {
                        move_to(x, y, i, y);
                        played = true;
                    }
                }
            }
            break;
        case RIGHT:
            for (std::size_t y = 0; y < Definitions::BLOCK_COUNT_Y; ++y)
            {
                for (int x = Definitions::BLOCK_COUNT_X - 2; x >= 0; --x)
                {
                    if (m_rects[x][y] == nullptr)
                        continue;
                    std::size_t i = x;
                    while (i < Definitions::BLOCK_COUNT_X - 1 && m_rects[++i][y] == nullptr);
                    if (can_merge(m_rects[x][y], m_rects[i][y]))
                    {
                        merge_to(x, y, i, y);
                        played = true;
                    }
                    else if (m_rects[i][y] == nullptr || m_rects[--i][y] == nullptr)
                    {
                        move_to(x, y, i, y);
                        played = true;
                    }
                }
            }
            break;
        case UP:
            for (std::size_t x = 0; x < Definitions::BLOCK_COUNT_X; ++x)
            {
                for (std::size_t y = 1; y < Definitions::BLOCK_COUNT_Y; ++y)
                {
                    if (m_rects[x][y] == nullptr)
                        continue;
                    std::size_t i = y;
                    while (i > 0 && m_rects[x][--i] == nullptr); // find closest block
                    if (can_merge(m_rects[x][y], m_rects[x][i]))
                    {
                        merge_to(x, y, x, i);
                        played = true;
                    }
                    else if (m_rects[x][i] == nullptr || m_rects[x][++i] == nullptr)
                    {
                        move_to(x, y, x, i);
                        played = true;
                    }
                }
            }
            break;
        case DOWN:
            for (std::size_t x = 0; x < Definitions::BLOCK_COUNT_X; ++x)
            {
                for (int y = Definitions::BLOCK_COUNT_Y - 2; y >= 0; --y)
                {
                    if (m_rects[x][y] == nullptr)
                        continue;
                    std::size_t i = y;
                    while (i < Definitions::BLOCK_COUNT_Y - 1 && m_rects[x][++i] == nullptr);
                    if (can_merge(m_rects[x][y], m_rects[x][i]))
                    {
                        merge_to(x, y, x, i);
                        played = true;
                    }
                    else if (m_rects[x][i] == nullptr || m_rects[x][--i] == nullptr)
                    {
                        move_to(x, y, x, i);
                        played = true;
                    }
                }
            }
            break;
    }


    if (played)
        m_stats.play(direction);

    on_turn_end(played);
}

void Game::on_turn_end(bool played /* = true*/)
{
    if (played)
        random_block();

    if (is_game_over())
        game_over();
    m_window.update_score(std::to_string(m_score) + (m_won ? " (Won)" : ""));
}

void Game::move_to(std::size_t from_x, std::size_t from_y, std::size_t to_x, std::size_t to_y)
{
    assert_coords(from_x, from_y);
    assert_coords(to_x, to_y);
    assert(m_rects[from_x][from_y] != nullptr && m_rects[to_x][to_y] == nullptr);
    m_animator.add<Move>(*m_rects[from_x][from_y], get_block_coords(to_x, to_y));
    m_rects[to_x][to_y] = m_rects[from_x][from_y];
    m_rects[from_x][from_y] = nullptr;

    m_stats.move();
}

void Game::merge_to(std::size_t from_x, std::size_t from_y, std::size_t to_x, std::size_t to_y)
{
    assert_coords(from_x, from_y);
    assert_coords(to_x, to_y);
    assert(m_rects[from_x][from_y] != nullptr && m_rects[to_x][to_y] != nullptr);
    m_animator.add<Merge>(*m_rects[to_x][to_y]);
    int number = m_rects[to_x][to_y]->next_number();
    m_rects[from_x][from_y] = nullptr;
    
    m_score += number;
    m_stats.score(number);
    m_stats.highest_score(m_score);
    m_stats.maximal_block(number);

    if (!m_won && number == Definitions::GAME_WIN_NUMBER)
        won();
    m_stats.merge();
}

bool Game::spawn_block(Blocks block, std::size_t x, std::size_t y)
{
    assert_coords(x, y);
    if (m_rects[x][y])
        return false;
    m_rects[x][y] = std::make_shared<NumberedRect>(get_block_coords(x, y), block, 0, 0);
    m_animator.add<Spawn>(*m_rects[x][y], get_block_coords(x, y));

    return true;
}

bool Game::random_block(Blocks block)
{
    std::vector<int> poss;
    for (std::size_t i = 0; i < Definitions::BLOCK_COUNT_X * Definitions::BLOCK_COUNT_Y; ++i)
        if (m_rects[i / Definitions::BLOCK_COUNT_X][i % Definitions::BLOCK_COUNT_Y] == nullptr)
            poss.push_back(i);
    if (poss.size() == 0)
        return false;

    size_t pos = poss[rand() % poss.size()];
    return spawn_block(block, pos / Definitions::BLOCK_COUNT_X, pos % Definitions::BLOCK_COUNT_Y);
}

void Game::restart()
{
    m_canplay = false;
    m_stats.restart(m_start_time);
    m_animator.clear();
    m_rects = NumberedRects(Definitions::BLOCK_COUNT_X, std::vector<std::shared_ptr<NumberedRect>>(Definitions::BLOCK_COUNT_Y, nullptr));
    start();
}

bool Game::is_game_over()
{
    for (auto i = m_rects.begin(); i != m_rects.end(); ++i)
        for (auto j = i->begin(); j != i->end(); ++j)
            if ((*j) == nullptr)
                return false;

    // Board is full, looking for merge.
    for (std::size_t x = 0; x < Definitions::BLOCK_COUNT_X - 1; ++x)
        for (std::size_t y = 0; y < Definitions::BLOCK_COUNT_Y - 1; ++y)
        {
            if (can_merge(m_rects[x][y], m_rects[x][y + 1]))
                return false;
            if (can_merge(m_rects[x][y], m_rects[x + 1][y]))
                return false;
        }
    for (std::size_t x = 0; x < Definitions::BLOCK_COUNT_X - 1; ++x)
        if (can_merge(m_rects[x][Definitions::BLOCK_COUNT_Y - 1], m_rects[x + 1][Definitions::BLOCK_COUNT_Y - 1]))
            return false;
    for (std::size_t y = 0; y < Definitions::BLOCK_COUNT_Y - 1; ++y)
        if (can_merge(m_rects[Definitions::BLOCK_COUNT_X - 1][y], m_rects[Definitions::BLOCK_COUNT_X - 1][y + 1]))
            return false;
    
    return true;
}

void Game::show_stats()
{
    time_t now = time(0);
    m_stats.update_time(now - m_start_time);
    Stats tmp_stats = m_stats + m_stats_global;
    m_start_time = now;

    TTF_Font* font = TTF_OpenFont(Definitions::DEFAULT_FONT_NAME.c_str(), Definitions::STATS_FONT_SIZE);
    int adv; /* = */ TTF_GlyphMetrics(font, 'a', NULL, NULL, NULL, NULL, &adv); // Letter width, since font is monospaced, all letters share the same width 
    std::size_t width = (tmp_stats.max_name_size() + Definitions::STATS_DELIMITER.size() + tmp_stats.max_value_size()) * adv;
    std::size_t heigth = StatTypes::MAX_STATS * TTF_FontLineSkip(font); // Line height
    StatsWindow stats_window(width, heigth + Definitions::STATS_BUTTON_HEIGHT, Definitions::STATS_WINDOW_NAME, m_stats, std::move(tmp_stats));
    m_window.hide();
    stats_window.wait_for_close();
    m_window.show();
}
