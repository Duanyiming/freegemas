#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include "GameHint.h"
#include "GameBoardSounds.h"

#include "Board.h"
#include "FloatingScore.h"
#include "ParticleSystem.h"
#include "ScoreTable.h"

#include <Gosu/Gosu.hpp>

class Game;
class StateGame;

/// Visual representation of a Board
class GameBoard
{
public:
    void setGame(Game *, StateGame *);
    void resetGame();
    void endGame(int score);

    void loadResources();

    void update();
    void draw();
    void mouseButtonDown(int, int);
    void mouseButtonUp(int, int);

    void showHint();

private:

    /// Tests if the mouse is over a gem
    bool overGem (int mx, int my);

    /// Returns the coords of the gem the mouse is over
    Coord getCoord (int mx, int my);

    // Checks if the newly selected square has formed a matching groups
    bool checkClickedSquare(int mx, int my);

    /// Creates a small label that indicates the points generated by a match
    void createFloatingScores();

    /// Plays the proper match sound depending on the current multiplier
    void playMatchSound();

    /// Parent game
    Game * mGame;

    /// Parent state game
    StateGame * mStateGame;

    enum tState
    {
        eNoBoard,

        eBoardAppearing,
        eBoardFilling,
        eBoardDisappearing,

        eSteady,

        eGemSelected,
        eGemSwitching,
        eGemDisappearing,

        eTimeFinished,
        eShowingScoreTable
    };

    tState mState = eNoBoard;


    /// Coordinates for the selected square (if any)
    Coord mSelectedSquareFirst;

    /// Coordinates for the second selected square
    Coord mSelectedSquareSecond;

    /// Container for the grouped squares
    MultipleMatch mGroupedSquares;

    /// The game board
    Board mBoard;

    /// Hint
    GameHint mHint;

    /// Sounds controller
    GameBoardSounds mGameBoardSounds;

    /// Image for the gem selector
    std::unique_ptr<Gosu::Image> mImgSelector;

    std::unique_ptr<Gosu::Image> mImgWhite;
    std::unique_ptr<Gosu::Image> mImgRed;
    std::unique_ptr<Gosu::Image> mImgPurple;
    std::unique_ptr<Gosu::Image> mImgOrange;
    std::unique_ptr<Gosu::Image> mImgGreen;
    std::unique_ptr<Gosu::Image> mImgYellow;
    std::unique_ptr<Gosu::Image> mImgBlue;

    /// Animation current step
    int mAnimationCurrentStep = 0;

    /// Long animation total steps
    int mAnimationLongTotalSteps = 50;

    /// Short animation total steps
    int mAnimationShortTotalSteps = 17;

    /// Current score multiplier
    int mMultiplier = 1;

    /// Group of floating scores. There may be some at the same time.
    std::vector<FloatingScore> mFloatingScores;

    /// Group of particle systems
    std::vector<ParticleSystem> mParticleSet;

    /// Reference to the score table
    std::shared_ptr<ScoreTable> scoreTable;
};

#endif