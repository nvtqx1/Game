# Game 2048
## Introduction
2048 is a logic game played usually on 4x4 board. The board contains
blocks of various values. In each turn, the player choses the direction
(up, down, left, right) in which all blocks on the board will move.
During the turn, a collision of two blocks can happen. If they are
of same value, they will be merged together to form single block
of doubled value. After the turn, a random spot on the board is chosen
and a new block with value of 2 (rarely 4) will spawn on that spot.
At the beginning, there are two blocks of values 2 (rarely 4).
The player is winner if he manages to combine blocks into a block with
value of 2048. If there is no direction, in which there would be a movement
of at least one block, then the player is declared as a loser.

This is its implementation in C++ and it uses [SDL](https://www.libsdl.org)
and [SDL_TTF](https://www.libsdl.org/projects/SDL_ttf/) libraries
to produce graphical output. It uses [Monofonto](http://www.dafont.com/monofonto.font)
font for displaying text throughout the program. 

##Supported Platforms
The program is currently capable of running only on **Windows** with
[**Visual C++ Redistributable 2013 32-bit**](https://www.microsoft.com/en-us/download/details.aspx?id=40784) installed.

##Download
You can download source codes from this repository and build it using Microsoft
Visual Studio. Also you have to donwload runtime [SDL](https://www.libsdl.org/release/SDL2-2.0.3-win32-x86.zip)
and [SDL_TTF](https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.12-win32-x86.zip)
DLLs. Repository already contains Development Libraries in *lib* folder.
DoxyGen generated documentation can be found accessed by clicking [this](http://www.zereges.cz/2048/doc/) link

You can download binary containing everything required (except for Visual C++
Redistributable 2013) to run the program from [this](http://www.zereges.cz/2048/2048.zip) mirror.

##Installation
The program does not need to be installed at all. Only requirement is to
preserve folder structure, so that 2048.exe are in the same folder as
SDL2.dll, SDL2_ttf.dll, libfreetype-6.dll, zlib1.dll, monofonto.ttf.

##Program Start
Program can be started by executing **2048.exe**.

##Controls
In the top left corner of the game window, there is an indicator showing
current score. If there is a "W" symbol after numeric value of the score,
it means, that the player managed to win this game and is only hunting higher
score. In the top right corner, one can click "Show Stats" button, which will
pop stats window showing interesting statistics about the play, such as Total
Moves or Highest Score. The statistics are preserved during multiple runs
of the program (saved in Stats.dat file). User can click "Switch to
Global/Current Stats" in the stats window to see statstics regarding current
game, or global statistics of all previous playthroughs.

The game is controlled using keyboard. By pressing directional arrows, one can
perform turn in given direction. Pressing "R" button restarts current game
progress. You can close the game by clicking top right cross, pressing
Alt+F4 or Ctrl+Q.

Written by Filip Kliber (zereges<at>gmail.com) in 2014/2015 as Semester Assignment  
Link to [GitHub](https://github.com/Zereges/2048) repository.
