#ifndef _GAME_HPP_
#define _GAME_HPP_
#include <SDL.h>
#include <vector>
#include <exception>
#include <iostream>
#include <time.h>
#include "../Definitions/Definitions.hpp"
#include "../Definitions/Rect.hpp"
#include "../Definitions/NumberedRect.hpp"
#include "../Animation/Animator.hpp"
#include "../Window/GameWindow.hpp"
#include "../Stats/Stats.hpp"

/*!
 * \brief Game class handling user events and game state
 */
class Game
{
    public:
        //! Base class constuctor
        //! \param window Reference to window where to draw interface and game state.
        Game(GameWindow& window); 
        
        //! Event handler for SDL_Event.
        //! \param event - const reference to SDL_Event to process.
        void event_handler(const SDL_Event& event);

        //! Event handler for SDL_KeyboardEvent.
        //! \param key - const reference to SDL_KeyboardEvent to process.
        void key_handler(const SDL_KeyboardEvent& key);

        //! Returns reference to vector of Rects used in background.
        //! Used for drawing background from Window::add()
        //! \return Const reference to vector of Rects.
        //! \sa Window::add(), Rect
        const Rects& get_background() const { return m_background; }

        //! Returns reference to vector of NumberedRects used on game field.
        //! Used for drawing game state from Window::add()
        //! \return Const reference to vector of NumberedRect.
        const NumberedRects& get_rects() const { return m_rects; }

        //! Computes real x and y coords of window for given params.
        //! \param x x coord on game field such that 0 <= x < Definitions::BLOCK_COUNT_X
        //! \param y y coord on game field such that 0 <= y < Definitions::BLOCK_COUNT_Y
        //! \return SDL_Point containing computed coords.
        //! \throws std::invalid_argument When either x >= Definitions::BLOCK_COUNT_X or y >= Definitions::BLOCK_COUNT_Y.
        static SDL_Point get_block_coords(unsigned int x, unsigned int y)
        {
            if (x < 0 || x >= Definitions::BLOCK_COUNT_X || y < 0 || y >= Definitions::BLOCK_COUNT_Y)
                throw std::invalid_argument("Invalid coords for Game::get_block_coords(unsigned, unsigned)");
            return { Definitions::GAME_X + Definitions::BLOCK_SPACE + x * (Definitions::BLOCK_SPACE + Definitions::BLOCK_SIZE_X),
                     Definitions::GAME_Y + Definitions::BLOCK_SPACE + y * (Definitions::BLOCK_SPACE + Definitions::BLOCK_SIZE_Y)
                   };
        }

        //! Computes game-field coords on which given Rect exists.
        //! \param rect - Const reference to Rect, for which coords will be computed.
        //! \return std::pair<int, int> of game-field coords.
        static std::pair<int, int> get_coords_block(const Rect& rect)
        {
            return {(rect.get_rect().x - Definitions::GAME_X - Definitions::BLOCK_SPACE) / (Definitions::BLOCK_SPACE + Definitions::BLOCK_SIZE_X), 
                    (rect.get_rect().y - Definitions::GAME_Y - Definitions::BLOCK_SPACE) / (Definitions::BLOCK_SPACE + Definitions::BLOCK_SIZE_Y)};
        }

        //! Starts a new game.
        void start();

        //! Calls animate of Animator
        //! \sa Animator, Animator::animate()
        void animate() { m_animator.animate(); }

        //! Checks whether player can perform a turn.
        //! \return True if player can play, false otherwise.
        bool can_play() const { return m_animator.can_play() && m_canplay; }

        //! Processes player's turn.
        //! \param direction Direction which player decided to play.
        void play(Directions direction);

        //! Inserts block on given coords.
        //! \param block Block to insert.
        //! \param x x coord
        //! \param y y coord
        //! \return True on success, false on failure (Board is full)
        //! \sa Blocks, Game::random_block()
        bool spawn_block(Blocks block, std::size_t x, std::size_t y);

        //! Inserts random block on board.
        //! \param block Block to insert. Default: BLOCK_4 with BLOCK_4_SPAWN_CHANCE, otherwise BLOCK_2.
        //! \return True on success, false on failure (Board is full).
        //! \sa Blocks, Game::spawn_block()
        bool random_block(Blocks block = chance(Definitions::BLOCK_4_SPAWN_CHANCE) ? BLOCK_4 : BLOCK_2);

        //! Removes all progress in current game and starts new one.
        void restart();

        //! Is called after player's turn is processed.
        //! \param played Indicates, whether player made a move this turn.
        //! \sa Game::play()
        void on_turn_end(bool played = true);

        //! Checks whether two NumberedRects can be merged together.
        //! Two NumberedRects can be merged together if they are of the same value.
        //! \param r1 First NumberedRect to check.
        //! \param r2 Second NumberedRect to check.
        //! \return True if possible, false otherwise.
        //! \sa Game::can_merge(std::shared_ptr<NumberedRect>, std::shared_ptr<NumberedRect>)
        bool can_merge(const NumberedRect& r1, const NumberedRect& r2) const { return r1.get_number() == r1.get_number(); }

        //! Checks whether two NumberedRects can be merged together.
        //! Two NumberedRects can be merged together if they are of the same value.
        //! \param r1 Smart pointer to NumberedRect 1 to check
        //! \param r2 Smart pointer to NumberedRect 2 to check
        //! \return True if possible, false otherwise.
        //! \sa Game::can_merge(const NumberedRect&, const NumberedRect&)
        bool can_merge(std::shared_ptr<NumberedRect> r1, std::shared_ptr<NumberedRect> r2) const
        {
            return r1 != nullptr && r2 != nullptr && r1->get_number() == r2->get_number();
        }

        //! Checks whether player's turned caused Game Over.
        //! \return True if no other move can be performed, false otherwise.
        bool is_game_over();

        //! Handles end of the game, when player loses.
        void game_over()
        {
            if (m_won)
                return;

            m_stats.lose(m_start_time);
            m_canplay = false;
        }

        //! Handles winning of the game.
        void won()
        {
            m_won = true;
            m_stats.win(m_start_time);
        }

        //! Stops the game play.
        void stop() { m_canplay = false; }
        
        //! Shows stats window
        //! \sa StatsWindow
        void show_stats();

        //! Indicates whether Game Over message should be displayed.
        //! \return True if message should be displayed, false otherwise.
        //! \sa Game::game_over()
        bool display_game_over() const
        {
            return !m_canplay && !m_won;
        }

    private:
        Rects m_background;     //!< Rectangles which forms a background of game.
        NumberedRects m_rects;  //!< Definitions::BLOCK_COUNT_X * Definitions::BLOCK_COUNT_Y field of NumberedRects forming state of a game.
        Animator m_animator;    //!< Animator class handling movement animtions.
        bool m_canplay;         //!< Tells whether player game is being played.
        bool m_won;             //!< Indicates, that player managed to win this game.
        GameWindow& m_window;   //!< Reference to Window class showing current game.
        Stats m_stats;          //!< Stats regarding current game.
        Stats m_stats_global;   //!< Global stats for player.
        time_t m_start_time;    //!< Time of latest m_stats update.
        long long m_score;      //!< Score earned in current game.

        //! Passes movement request to animator class and updates inner state.
        //! \param from_x x coord of Rect on field.
        //! \param from_y y coord of Rect on field.
        //! \param to_x x coord where to move.
        //! \param to_y y coord where to move.
        void move_to(std::size_t from_x, std::size_t from_y, std::size_t to_x, std::size_t to_y);

        //! Passes merge request to animator class and updates inner state.
        //! \param from_x x coord of Rect on field.
        //! \param from_y y coord of Rect on field.
        //! \param to_x x coord where to move.
        //! \param to_y y coord where to move.
        void merge_to(std::size_t from_x, std::size_t from_y, std::size_t to_x, std::size_t to_y);
};
#endif // _GAME_HPP_
