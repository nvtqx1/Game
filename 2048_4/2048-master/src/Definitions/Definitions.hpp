#ifndef _DEFINITIONS_HPP_
#define _DEFINITIONS_HPP_
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <math.h>
#include <vector>
#include <memory>
class Rect;
class NumberedRect;

typedef std::vector<Rect> Rects;
typedef std::vector<std::vector<std::shared_ptr<NumberedRect> > > NumberedRects;

//! Enum of playable directions.
//! \sa Game::play()
enum Directions
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

//! Enum of Blocks for easier referencing.
//! \sa Game::spawn_block(), Game::random_block()
enum Blocks
{
    BLOCK_0 = 0,
    BLOCK_2 = 1,
    BLOCK_4,
    BLOCK_8,
    BLOCK_16,
    BLOCK_32,
    BLOCK_64,
    BLOCK_128,
    BLOCK_256,
    BLOCK_512,
    BLOCK_1024,
    BLOCK_2048,
    BLOCK_4096,
    BLOCK_8192,
    BLOCK_16384,
    BLOCK_32768,
    BLOCK_65536,
    BLOCK_131072, // Theoretical maximum on 4x4 board.

    MAX_BLOCKS,
};

//! Defines operator++ for Enum Blocks.
//! \param block Block to apply operator++ to.
//! \return Incremented block.
//! \throws std::invalid_argument if block was too big.
//! \sa Blocks
inline Blocks& operator++(Blocks& block)
{
    block = static_cast<Blocks>(static_cast<int>(block) + 1);
    if (block == Blocks::MAX_BLOCKS)
        throw std::invalid_argument("Invalid argument for Blocks::operator++");
    return block;
}

/*!
 * \brief Abstract class containing definitions used throughout the program.
 */
class Definitions
{
    public:
        static const std::string GAME_WINDOW_NAME;                      //!< Game window name.
        static const std::size_t GAME_WINDOW_WIDTH;                     //!< Total game window width.
        static const std::size_t GAME_WINDOW_HEIGHT;                    //!< Total game window height.

        static const std::string STATS_WINDOW_NAME;                     //!< Stats window name.
        static const std::size_t STATS_FONT_SIZE;                       //!< Font size used in stats window.
        static const std::string STATS_DELIMITER;                       //!< Delimiter used in stats window.
        static const std::size_t STATS_BUTTON_HEIGHT;                   //!< Height of Global/Current stats switching button.
        static const std::string STATS_FILE_NAME;                       //!< File name, where stats are saved.

        static const std::size_t GAME_X;                                //!< X-Coord where Game begins.
        static const std::size_t GAME_Y;                                //!< Y-Coord where Game begins.

        static const std::size_t GAME_WIDTH;                            //!< Game width.
        static const std::size_t GAME_HEIGHT;                           //!< Game height.

        static const std::size_t BLOCK_COUNT_X;                         //!< Number of blocks in each horizontal line.
        static const std::size_t BLOCK_COUNT_Y;                         //!< Number of blocks in each vertical line.
        static const std::size_t BLOCK_SIZE_X;                          //!< Horizontal size of a single block. 
        static const std::size_t BLOCK_SIZE_Y;                          //!< Vertical size of a single block.
        static const std::size_t BLOCK_SPACE;                           //!< Space between blocks.
        static const std::vector<SDL_Color> BLOCK_COLORS;               //!< Colors of blocks based on their values.
        static const int GAME_WIN_NUMBER;                               //!< Required number to achieve in order to win the game.

        static const SDL_Color BACKGROUND_COLOR;                        //!< Background color of the window.

        static const int DEFAULT_MOVE_SPEED;                            //!< Default move speed of blocks in pixels per frame
        static const int DEFAULT_SPAWN_SPEED;                           //!< Default spawn speed of blocks in pixels per frame
        static const int DEFAULT_MERGE_SPEED;                           //!< Default merge speed of blocks in pixels per frame
        static const int DEFAULT_MERGE_ENLARGEMENT;                     //!< Default percentual enlargement of merged block.

        static const int BLOCK_4_SPAWN_CHANCE;                          //!< Chance of spawning BLOCK_4 instead of BLOCK_2
        static const int DEFAULT_START_BLOCKS;                          //!< Blocks given to player at start.

        static const SDL_Color WHITE_COLOR;                             //!< White color.
        static const SDL_Color BLACK_COLOR;                             //!< Black color.
        static const SDL_Color GREY_COLOR;                              //!< Grey color.
        static const std::string DEFAULT_FONT_NAME;                     //!< Default font name used in program.
        static const std::size_t DEFAULT_GAME_FONT_SIZE;                //!< Default font size used in Game Window
        
        //! Returns color of given blcok
        //! \param block Block for which the color whould be returned.
        //! \return SDL_Color of given block, or last defined if block is too big.
        //! \sa Blocks
        static SDL_Color get_block_color(Blocks block) { return block < (int) BLOCK_COLORS.size() ? BLOCK_COLORS[block] : BLOCK_COLORS[BLOCK_COLORS.size() - 1]; }


    private:
        // To make it abstract
        Definitions() = delete;
        Definitions(const Definitions&) = delete;
        Definitions(Definitions&&) = delete;
        Definitions& operator=(const Definitions&) = delete;
        Definitions& operator=(Definitions&&) = delete;
};

//! Computes binary logarithm of given integer value
//! \param val Value to compute the logarithm of.
//! \return Log_2(val)
inline int logb(unsigned int val) { return (unsigned int) trunc(log2(val)); }

//! Computes 2 to the power of argument.
//! \param block exponent of pow function.
//! \return Result of the computation.
inline int pow2(Blocks block) { return (int) pow(2, (int) block); }

//! Simulates rolling of <0, 100> chance.
//! If c >= 100, then the function always returns true.
//! If c <= 0, then the function always returns false.
//! \param c Chance to simulate.
//! \return True if chance happened, false otherwise.
inline bool chance(int c) { return rand() % 100 < c; }

#endif // _DEFINITIONS_HPP_
