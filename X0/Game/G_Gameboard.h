/******************************************************************************
 * ==> G_Gameboard -----------------------------------------------------------*
 ******************************************************************************
 * Description : Gameboard class                                              *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#ifndef G_Gameboard_h
#define G_Gameboard_h

#include <vector>

/**
* Gameboard class
*@author Jean-Milost Reymond
*/
class G_Gameboard
{
    public:
        /**
        * Players enumeration
        */
        enum IEPlayer
        {
            IE_Pl_Player2 = -1,
            IE_Pl_None    =  0,
            IE_Pl_Player1 =  1,
        };

        /**
        * Pawns enumeration
        */
        enum IEPawn
        {
            IE_Pa_None = 0,
            IE_Pa_Round,
            IE_Pa_Cross,
        };

        /**
        * Artificial intelligency level
        */
        enum IEAILevel
        {
            IE_AI_None = 0,
            IE_AI_Easy,
            IE_AI_Normal,
            IE_AI_Hard,
            IE_AI_ExtraHard,
        };

        /**
        * Gameboard cell
        */
        struct ICell
        {
            IEPawn   m_Pawn;
            unsigned m_X;
            unsigned m_Y;
            bool     m_PlayerCanWinOnNextMove;
            bool     m_ComputerCanWinOnNextMove;
            bool     m_CanTrapOnNextMove;
            unsigned m_OffensiveScore;
            unsigned m_DefensiveScore;

            /**
            * Constructor
            */
            ICell();

            /**
            * Resets cell to initial state
            */
            void Reset();

            /**
            * Checks if cell is on left diagonal
            *@returns true if cell is on left diagonal, otherwise false
            */
            bool IsOnLeftDiagonal() const;

            /**
            * Checks if cell is on right diagonal
            *@returns true if cell is on right diagonal, otherwise false
            */
            bool IsOnRightDiagonal() const;
        };

        typedef std::vector<ICell> ICells;

        /**
        * Called when a player has played
        *@param player - player
        *@param pawn - pawn used by player
        *@param isComputer - if true, player is computer
        *@returns true if game should continue, false if game should be stopped
        */
        typedef bool (*ITfOnPlayed)(IEPlayer player, IEPawn pawn, bool isComputer);

        /**
        * Constructor
        */
        G_Gameboard();

        /**
        * Resets gameboard to initial state
        */
        void Reset();

        /**
        * Set artificial intelligence level
        *@param level - AI level
        */
        void SetAI(IEAILevel level);

        /**
        * Checks if cell is empty
        *@param x - x position on grid
        *@param y - y position on grid
        *@returns true if cell is empty, otherwise false
        */
        bool IsEmpty(unsigned x, unsigned y);

        /**
        * Set pawns used by player 1
        *@param pawn - pawn
        *@note player 2 will automatically takes remaining pawns
        */
        void SetPlayer1Pawn(IEPawn pawn);

        /**
        * Set player 2 is computer
        *@param value - if true, player 2 is computer
        */
        void SetPlayer2IsComputer(bool value);

        /**
        * Run game allowing computer to set the first pawn
        */
        void ComputerBegins();

        /**
        * Sets user move
        *@param x - x position on grid
        *@param y - y position on grid
        */
        void SetUserMove(unsigned x, unsigned y);

        /**
        * Sets computer move
        *@param computerPlayer - player used by computer
        */
        void SetComputerMove(IEPlayer computerPlayer);

        /**
        * Gets gameboard cell at x and y positions
        *@param x - x position
        *@param y - y position
        *@returns cell, NULL if not found
        */
        ICell* GetCell(unsigned x, unsigned y);

        /**
        * Gets gameboard cell at x and y positions
        *@param index - cell index
        *@returns cell, NULL if not found
        */
        ICell* GetCell(unsigned index);

        /**
        * Get cells containing winning pawns
        *@returns cells containing winning pawns
        */
        ICells GetWinCells();

        /**
        * Gets gameboard cell count
        *@returns cell count
        */
        unsigned GetCellCount() const;

        /**
        * Checks if player 2 is computer
        *@returns true if player 2 is computer, otherwise false
        */
        bool IsPlayer2Computer();

        /**
        * Checks if game is over
        *@returns true if game is over, otherwise false
        */
        bool IsGameOver();

        /**
        * Checks if a player has win
        *@returns player who has won, IE_Pl_None if nobody won
        */
        IEPlayer HasWin();

        /**
        * Sets OnPlayed callback
        *@param fHandler - function handler
        */
        void Set_OnPlayed(ITfOnPlayed fHandler);

    private:
        ICells      m_Cells;
        IEAILevel   m_AILevel;
        IEPlayer    m_Player;
        IEPawn      m_Player1Pawn;
        IEPawn      m_Player2Pawn;
        bool        m_Player2IsComputer;
        int         m_LastPlayedIndex;
        ITfOnPlayed m_fOnPlayed;

        /**
        * Selects cell to play
        *@param cells - cell list
        *@param computerPlayer - player used by computer
        *@param computerPawn - pawn used by computer
        *@param emptyCellCount - empty cell count
        */
        void SelectCell(const std::vector<ICell*>& cells, IEPlayer computerPlayer, IEPawn computerPawn,
                unsigned emptyCellCount);

        /**
        * Calculates score on current cell, to determine next computer move
        *@param pCell - cell for which score should be calculated
        *@param pawn - pawn used by computer
        *@param emptyCellCount - empty cell count
        */
        void CalculateScore(ICell* pCell, IEPawn pawn, unsigned emptyCellCount);

        /**
        * Checks if cell containing pawn is on a complete line of same pawns
        *@param pCell - cell to check
        *@param pawn - pawn to check
        *@returns true if cell is on a complete line
        */
        bool IsOnCompleteLine(const ICell* pCell, IEPawn pawn);

        /**
        * Get empty cell count
        *@returns empty cell count
        */
        unsigned GetEmptyCellCount();

        /**
        * Apply minimax algorithm to determine which is the best cell to move for player
        *@param player - player for which best cell should be found
        *@param pBestCell - best cell found
        *@param deep - minimax deep
        *@returns minimax score
        */
        int MiniMax(IEPlayer player, ICell*& pBestCell, int deep = 0);
};

#endif
