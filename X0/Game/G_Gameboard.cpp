/******************************************************************************
 * ==> G_Gameboard -----------------------------------------------------------*
 ******************************************************************************
 * Description : Gameboard class                                              *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#include "G_Gameboard.h"
#include "E_Random.h"

//------------------------------------------------------------------------------
#define M_GameboardWidth  3
#define M_GameboardHeight 3
//------------------------------------------------------------------------------
// G_Gameboard::ICell
//------------------------------------------------------------------------------
G_Gameboard::ICell::ICell() :
    m_Pawn(IE_Pa_None),
    m_X(0),
    m_Y(0),
    m_PlayerCanWinOnNextMove(false),
    m_ComputerCanWinOnNextMove(false),
    m_CanTrapOnNextMove(false),
    m_OffensiveScore(0),
    m_DefensiveScore(0)
{}
//------------------------------------------------------------------------------
void G_Gameboard::ICell::Reset()
{
    m_Pawn                     = IE_Pa_None;
    m_PlayerCanWinOnNextMove   = false;
    m_ComputerCanWinOnNextMove = false;
    m_CanTrapOnNextMove        = false;
    m_OffensiveScore           = 0;
    m_DefensiveScore           = 0;
}
//------------------------------------------------------------------------------
bool G_Gameboard::ICell::IsOnLeftDiagonal() const
{
    return (m_X == m_Y);
}
//------------------------------------------------------------------------------
bool G_Gameboard::ICell::IsOnRightDiagonal() const
{
    return (m_X + m_Y == 2);
}
//------------------------------------------------------------------------------
// G_Gameboard
//------------------------------------------------------------------------------
G_Gameboard::G_Gameboard() :
    m_AILevel(IE_AI_Normal),
    m_Player(IE_Pl_Player1),
    m_Player1Pawn(IE_Pa_Cross),
    m_Player2Pawn(IE_Pa_Round),
    m_Player2IsComputer(true),
    m_LastPlayedIndex(-1),
    m_fOnPlayed(NULL)
{
    // iterate through gameboard columns and lines
    for (unsigned i = 0; i < M_GameboardHeight; ++i)
        for (unsigned j = 0; j < M_GameboardWidth; ++j)
        {
            // create and populate cell
            ICell cell;
            cell.m_X = j;
            cell.m_Y = i;

            // add cell to list
            m_Cells.push_back(cell);
        }
}
//------------------------------------------------------------------------------
void G_Gameboard::Reset()
{
    // iterate through gameboard cells
    for (unsigned i = 0; i < m_Cells.size(); ++i)
        // reset cell
        m_Cells[i].Reset();

    // reset player
    m_Player = IE_Pl_Player1;
}
//------------------------------------------------------------------------------
void G_Gameboard::SetAI(IEAILevel level)
{
    m_AILevel = level;
}
//------------------------------------------------------------------------------
bool G_Gameboard::IsEmpty(unsigned x, unsigned y)
{
    // get cell at x and y position
    const ICell* pCell = GetCell(x, y);

    // found it?
    if (!pCell)
        return false;

    // check and return if pawn already occupy this cell
    return (pCell->m_Pawn == IE_Pa_None);
}
//------------------------------------------------------------------------------
void G_Gameboard::SetPlayer1Pawn(IEPawn pawn)
{
    m_Player1Pawn = pawn;
    m_Player2Pawn = (m_Player1Pawn == IE_Pa_Cross) ? IE_Pa_Round : IE_Pa_Cross;
}
//------------------------------------------------------------------------------
void G_Gameboard::SetPlayer2IsComputer(bool value)
{
    m_Player2IsComputer = value;
}
//------------------------------------------------------------------------------
void G_Gameboard::ComputerBegins()
{
    // is player playing against computer?
    if (!m_Player2IsComputer)
        return;

    // let computer set the first pawn
    SetComputerMove((m_Player == IE_Pl_Player1) ? IE_Pl_Player2 : IE_Pl_Player1);
}
//------------------------------------------------------------------------------
void G_Gameboard::SetUserMove(unsigned x, unsigned y)
{
    // get cell at x and y position
    ICell* pCell = GetCell(x, y);

    // found it?
    if (!pCell)
        return;

    // cell is not empty?
    if (!IsEmpty(x, y))
        return;

    // set pawn in cell
    pCell->m_Pawn = (m_Player == IE_Pl_Player1) ? m_Player1Pawn : m_Player2Pawn;

    // notify that a player has played, and check if game should be stopped
    if (m_fOnPlayed)
        if (!m_fOnPlayed(m_Player, pCell->m_Pawn, false))
            return;

    // get other player (e.g. if player 1 has played, then other player is played 2)
    IEPlayer otherPlayer = (m_Player == IE_Pl_Player1) ? IE_Pl_Player2 : IE_Pl_Player1;

    // is player playing against computer?
    if (m_Player2IsComputer)
        SetComputerMove(otherPlayer);
    else
        // change player
        m_Player = otherPlayer;
}
//------------------------------------------------------------------------------
void G_Gameboard::SetComputerMove(IEPlayer computerPlayer)
{
    // first checks
    // - check if player will win on next row and block it if yes
    // - check if can win on next row and close line if yes
    // - check if player can trap the computer
    //
    // then, for each cell
    // - increase offensive score by 1 for each open line (i.e. containing no pawns)
    // - increase offensive score by 2 for each line already containing a computer pawn
    // - increase defensive score by 1 for each line containing a player pawn

    // get computer pawn
    IEPawn computerPawn = (computerPlayer == IE_Pl_Player1) ? m_Player1Pawn : m_Player2Pawn;

    // get empty cell count
    unsigned emptyCellCount = GetEmptyCellCount();
    
    std::vector<ICell*> cells;

    // is AI disabled or do open extra-hard game?
    if (m_AILevel == IE_AI_None || (m_AILevel == IE_AI_ExtraHard && emptyCellCount == 9))
    {
        // iterate through cells
        for (unsigned i = 0; i < m_Cells.size(); ++i)
        {
            // get cell
            ICell* pCell = GetCell(i);

            // is cell free?
            if (pCell->m_Pawn == IE_Pa_None)
                cells.push_back(pCell);
        }

        // select cell to play
        SelectCell(cells, computerPlayer, computerPawn, emptyCellCount);

        return;
    }

    // is AI at max level?
    if (m_AILevel == IE_AI_ExtraHard)
    {
        ICell* pBestCell = NULL;

        // get best cell for computer
        MiniMax(computerPlayer, pBestCell);

        //get next move
        pBestCell->m_Pawn = computerPawn;

        return;
    }

    // iterate through cells
    for (unsigned i = 0; i < m_Cells.size(); ++i)
    {
        // get cell
        ICell* pCell = GetCell(i);

        // calculate score on current cell
        CalculateScore(pCell, computerPawn, emptyCellCount);
    }

    unsigned maxScore = 0;

    // iterate through cells
    for (unsigned i = 0; i < m_Cells.size(); ++i)
    {
        // get cell
        ICell* pCell = GetCell(i);

        // calculate score on current cell and get max
        maxScore = std::max(pCell->m_OffensiveScore + pCell->m_DefensiveScore, maxScore);
    }

    ICell* pDangerousCell = NULL;

    // iterate through cells
    for (unsigned i = 0; i < m_Cells.size(); ++i)
    {
        // get cell
        ICell* pCell = GetCell(i);

        // opponent can trap the computer?
        if (m_AILevel >= IE_AI_Hard && pCell->m_CanTrapOnNextMove)
        {
            // get position to play to block trap
            unsigned posX = (!pCell->m_X ? 2 : 0);
            unsigned posY = (!pCell->m_Y ? 2 : 0);
            
            // get cell to play
            ICell* pCellToPlay = GetCell(posX, posY);
            
            // found it?
            if (!pCellToPlay)
                continue;
            
            // block trap
            pCellToPlay->m_Pawn = computerPawn;
            
            // notify that computer has played
            if (m_fOnPlayed)
                m_fOnPlayed(computerPlayer, computerPawn, true);
            
            return;
        }

        // cell contains pawn?
        if (pCell->m_Pawn != IE_Pa_None)
            continue;

        // computer or player can win on next move or cell contains highest score?
        if (m_AILevel >= IE_AI_Normal && pCell->m_ComputerCanWinOnNextMove)
        {
            // computer can win on next move, set computer pawn in cell
            pCell->m_Pawn = computerPawn;

            // notify that computer has played
            if (m_fOnPlayed)
                m_fOnPlayed(computerPlayer, computerPawn, true);

            return;
        }
        else
        if (m_AILevel >= IE_AI_Normal && pCell->m_PlayerCanWinOnNextMove)
        {
            // player can win on next move, keep it
            pDangerousCell = pCell;
            continue;
        }
        else
        if (pCell->m_OffensiveScore + pCell->m_DefensiveScore == maxScore)
            // cell contains highest score, keep it as candidate for next move
            cells.push_back(pCell);
    }

    // user can win on next move?
    if (pDangerousCell)
    {
        // set computer pawn in cell
        pDangerousCell->m_Pawn = computerPawn;

        // notify that computer has played
        if (m_fOnPlayed)
            m_fOnPlayed(computerPlayer, computerPawn, true);

        return;
    }

    // select cell to play
    SelectCell(cells, computerPlayer, computerPawn, emptyCellCount);
}
//------------------------------------------------------------------------------
G_Gameboard::ICell* G_Gameboard::GetCell(unsigned x, unsigned y)
{
    // calculate cell index and get it
    return GetCell((y * M_GameboardWidth) + x);
}
//------------------------------------------------------------------------------
G_Gameboard::ICell* G_Gameboard::GetCell(unsigned index)
{
    // index is out of bounds?
    if (index >= m_Cells.size())
        return NULL;

    // return cell at index
    return &m_Cells[index];
}
//------------------------------------------------------------------------------
G_Gameboard::ICells G_Gameboard::GetWinCells()
{
    ICells winCells;

    // iterate through cells
    for (unsigned i = 0; i < m_Cells.size(); ++i)
    {
        // get cell
        ICell* pCell = GetCell(i);
        
        // found it?
        if (!pCell)
            continue;
        
        // check if cell is part of a line completed by player 1
        if (IsOnCompleteLine(pCell, m_Player1Pawn))
            winCells.push_back(*pCell);
        
        // check if cell is part of a line completed by player 2
        if (IsOnCompleteLine(pCell, m_Player2Pawn))
            winCells.push_back(*pCell);
    }

    return winCells;
}
//------------------------------------------------------------------------------
unsigned G_Gameboard::GetCellCount() const
{
    return m_Cells.size();
}
//------------------------------------------------------------------------------
bool G_Gameboard::IsPlayer2Computer()
{
    return m_Player2IsComputer;
}
//------------------------------------------------------------------------------
bool G_Gameboard::IsGameOver()
{
    unsigned occupiedCell = 0;

    // iterate through cells
    for (unsigned i = 0; i < m_Cells.size(); ++i)
    {
        // get cell
        ICell* pCell = GetCell(i);

        // is cell occupied by pawn?
        if (pCell->m_Pawn != IE_Pa_None)
            ++occupiedCell;
    }

    // are all cells occupied?
    return (occupiedCell >= 9);
}
//------------------------------------------------------------------------------
G_Gameboard::IEPlayer G_Gameboard::HasWin()
{
    // iterate through cells
    for (unsigned i = 0; i < m_Cells.size(); ++i)
    {
        // get cell
        ICell* pCell = GetCell(i);

        // found it?
        if (!pCell)
            continue;

        // check if player 1 has win (i.e. if he has completed a line)
        if (IsOnCompleteLine(pCell, m_Player1Pawn))
            return IE_Pl_Player1;

        // check if player 2 has win (i.e. if he has completed a line)
        if (IsOnCompleteLine(pCell, m_Player2Pawn))
            return IE_Pl_Player2;
    }

    return IE_Pl_None;
}
//------------------------------------------------------------------------------
void G_Gameboard::Set_OnPlayed(ITfOnPlayed fHandler)
{
    m_fOnPlayed = fHandler;
}
//------------------------------------------------------------------------------
void G_Gameboard::SelectCell(const std::vector<ICell*>& cells, IEPlayer computerPlayer, IEPawn computerPawn,
        unsigned emptyCellCount)
{
    // no cell selected for next move, only one cell is possible, or there are many cells?
    if (!cells.size())
        // no cell, nothing to do
        return;
    else
    if (cells.size() == 1)
        // only one cell, set pawn into
        cells[0]->m_Pawn = computerPawn;
    else
    {
        E_Random::Initialize();

        bool   canUse;
        ICell* pCellToPlay;

        do
        {
            // many cells, select one randomly
            unsigned index = E_Random::GetNumber(9999) % (cells.size() - 1);

            // get next cell to play
            pCellToPlay = cells[index];

            // can use cell?
            canUse = emptyCellCount < 8 ||
                     (((pCellToPlay->m_Y * M_GameboardWidth) + pCellToPlay->m_X) != m_LastPlayedIndex);
        }
        while (!canUse);

        if (emptyCellCount >= 8)
            m_LastPlayedIndex = ((pCellToPlay->m_Y * M_GameboardWidth) + pCellToPlay->m_X);

        // set computer pawn
        pCellToPlay->m_Pawn = computerPawn;
    }

    // notify that computer has played
    if (m_fOnPlayed)
        m_fOnPlayed(computerPlayer, computerPawn, true);
}
//------------------------------------------------------------------------------
void G_Gameboard::CalculateScore(ICell* pCell, IEPawn pawn, unsigned emptyCellCount)
{
    // no cell?
    if (!pCell)
        return;

    // reset cell
    pCell->m_PlayerCanWinOnNextMove   = false;
    pCell->m_ComputerCanWinOnNextMove = false;
    pCell->m_CanTrapOnNextMove        = false;
    pCell->m_OffensiveScore           = 0;
    pCell->m_DefensiveScore           = 0;

    // is cell already occupied?
    if (pCell->m_Pawn != IE_Pa_None)
    {
        // check if computer can be trapped 
        if (emptyCellCount == 8 && pCell->m_Pawn != IE_Pa_None && (pCell->m_X == 0 || pCell->m_X == 2)
                && (pCell->m_Y == 0 || pCell->m_Y == 2))
            pCell->m_CanTrapOnNextMove = true;

        return;
    }

    unsigned playerHoriz       = 0;
    unsigned playerVert        = 0;
    unsigned playerRDiagonal   = 0;
    unsigned playerLDiagonal   = 0;
    unsigned computerHoriz     = 0;
    unsigned computerVert      = 0;
    unsigned computerRDiagonal = 0;
    unsigned computerLDiagonal = 0;
    unsigned freeHoriz         = 0;
    unsigned freeVert          = 0;
    unsigned freeRDiagonal     = 0;
    unsigned freeLDiagonal     = 0;

    // iterate through cells
    for (unsigned i = 0; i < m_Cells.size(); ++i)
    {
        // get cell to check
        ICell* pCellToCheck = GetCell(i);

        // found it?
        if (!pCellToCheck)
            continue;

        // check if cell is on same line as reference cell
        if (pCellToCheck->m_X == pCell->m_X)
            // check if cell is occupied by player, computer, or is free
            if (pCellToCheck->m_Pawn == pawn)
                ++computerHoriz;
            else
            if (pCellToCheck->m_Pawn == IE_Pa_None)
                ++freeHoriz;
            else
                ++playerHoriz;

        // check if cell is on same column as reference cell
        if (pCellToCheck->m_Y == pCell->m_Y)
            // check if cell is occupied by player, computer, or is free
            if (pCellToCheck->m_Pawn == pawn)
                ++computerVert;
            else
            if (pCellToCheck->m_Pawn == IE_Pa_None)
                ++freeVert;
            else
                ++playerVert;

        // check if cell and reference cell are on left diagonal
        if (pCell->IsOnLeftDiagonal() && pCellToCheck->IsOnLeftDiagonal())
            // check if cell is occupied by player, computer, or is free
            if (pCellToCheck->m_Pawn == pawn)
                ++computerLDiagonal;
            else
            if (pCellToCheck->m_Pawn == IE_Pa_None)
                ++freeLDiagonal;
            else
                ++playerLDiagonal;

        // check if cell and reference cell are on right diagonal
        if (pCell->IsOnRightDiagonal() && pCellToCheck->IsOnRightDiagonal())
            // check if cell is occupied by player, computer, or is free
            if (pCellToCheck->m_Pawn == pawn)
                ++computerRDiagonal;
            else
            if (pCellToCheck->m_Pawn == IE_Pa_None)
                ++freeRDiagonal;
            else
                ++playerRDiagonal;
    }

    // check if player can win on next move
    if ((playerHoriz == 2 && freeHoriz == 1) || (playerVert == 2 && freeVert == 1)
            || (playerLDiagonal == 2 && freeLDiagonal == 1)
            || (playerRDiagonal == 2 && freeRDiagonal == 1))
        pCell->m_PlayerCanWinOnNextMove = true;

    // check if computer can win on next move
    if ((computerHoriz == 2 && freeHoriz == 1) || (computerVert == 2 && freeVert == 1)
            || (computerLDiagonal == 2 && freeLDiagonal == 1)
            || (computerRDiagonal == 2 && freeRDiagonal == 1))
        pCell->m_ComputerCanWinOnNextMove = true;

    // calculate offensive score on horizontal line
    if (computerHoriz == 1 && freeHoriz == 2)
        ++pCell->m_OffensiveScore;

    // calculate offensive score on vertical line
    if (computerVert == 1 && freeVert == 2)
        ++pCell->m_OffensiveScore;

    // calculate offensive score on left diagonal line
    if (computerLDiagonal == 1 && freeLDiagonal == 2)
        ++pCell->m_OffensiveScore;

    // calculate offensive score on right diagonal line
    if (computerRDiagonal == 1 && freeRDiagonal == 2)
        ++pCell->m_OffensiveScore;

    // calculate defensive score on horizontal line
    if (playerHoriz == 1 && freeHoriz == 2)
        ++pCell->m_DefensiveScore;

    // calculate defensive score on vertical line
    if (playerVert == 1 && freeVert == 2)
        ++pCell->m_DefensiveScore;

    // calculate defensive score on left diagonal line
    if (playerLDiagonal == 1 && freeLDiagonal == 2)
        ++pCell->m_DefensiveScore;

    // calculate defensive score on right diagonal line
    if (playerRDiagonal == 1 && freeRDiagonal == 2)
        ++pCell->m_DefensiveScore;
}
//------------------------------------------------------------------------------
bool G_Gameboard::IsOnCompleteLine(const ICell* pCell, IEPawn pawn)
{
    // no cell?
    if (!pCell)
        return false;

    unsigned horiz     = 0;
    unsigned vert      = 0;
    unsigned lDiagonal = 0;
    unsigned rDiagonal = 0;

    // iterate through cells
    for (unsigned i = 0; i < m_Cells.size(); ++i)
    {
        // get cell to check
        ICell* pCellToCheck = GetCell(i);

        // found it?
        if (!pCellToCheck)
            continue;

        // check if cell is on same line as reference cell and if cell contains pawn
        if (pCellToCheck->m_X == pCell->m_X && pCellToCheck->m_Pawn == pawn)
            ++horiz;

        // check if cell is on same column as reference cell and if cell contains pawn
        if (pCellToCheck->m_Y == pCell->m_Y && pCellToCheck->m_Pawn == pawn)
            ++vert;

        // check if cell and reference cell are on left diagonal and if cell contains pawn
        if (pCell->IsOnLeftDiagonal() && pCellToCheck->IsOnLeftDiagonal() && pCellToCheck->m_Pawn == pawn)
            ++lDiagonal;

        // check if cell and reference cell are on right diagonal and if cell contains pawn
        if (pCell->IsOnRightDiagonal() && pCellToCheck->IsOnRightDiagonal() && pCellToCheck->m_Pawn == pawn)
            ++rDiagonal;
    }

    // a line is complete if all cells of line, column or diagonal contains same pawn
    return (horiz == 3 || vert == 3 || rDiagonal == 3 || lDiagonal == 3);
}
//------------------------------------------------------------------------------
unsigned G_Gameboard::GetEmptyCellCount()
{
    unsigned emptyCellCount = 0;

    // iterate through cells
    for (unsigned i = 0; i < m_Cells.size(); ++i)
    {
        // get cell to check
        ICell* pCellToCheck = GetCell(i);
    
        // found it?
        if (!pCellToCheck)
            continue;

        // is cell empty?
        if (pCellToCheck->m_Pawn == IE_Pa_None)
            ++emptyCellCount;
    }

    return emptyCellCount;
}
//------------------------------------------------------------------------------
int G_Gameboard::MiniMax(IEPlayer player, ICell*& pBestCell, int deep)
{
    // calculate min and max sum
    int sum = (1 << 20);
    int max = -sum;
    int min =  sum;

    // any player has win?
    IEPlayer winner = HasWin();

    // is game over?
    if (winner == IE_Pl_Player1)
        return IE_Pl_Player1;
    else
    if (winner == IE_Pl_Player2)
        return IE_Pl_Player2;
    else
    if (IsGameOver())
        return 0;

    // iterate through cells
    for (unsigned i = 0; i < m_Cells.size(); ++i)
    {
        // get cell to check
        ICell* pCell = GetCell(i);

        // found it?
        if (!pCell)
            continue;

        // is cell already occupied?
        if (pCell->m_Pawn != IE_Pa_None)
            continue;

        // search for player to check
        switch (player)
        {
            case IE_Pl_Player1:
            {
                // simulate player 1 move
                pCell->m_Pawn = m_Player1Pawn;

                // check next opposite player move
                int result = MiniMax(IE_Pl_Player2, pBestCell, deep + 1);

                // revert cell to original value
                pCell->m_Pawn = IE_Pa_None;

                // do update max?
                if (result > max)
                {
                    max = result;

                    // first level?
                    if (!deep)
                        // get best cell
                        pBestCell = pCell;
                }

                continue;
            }

            case IE_Pl_Player2:
            {
                // simulate player 2 move
                pCell->m_Pawn = m_Player2Pawn;

                // check next opposite player move
                int result = MiniMax(IE_Pl_Player1, pBestCell, deep + 1);

                // revert cell to original value
                pCell->m_Pawn = IE_Pa_None;

                // do update min?
                if (result < min)
                {
                    min = result;

                    // first level?
                    if (!deep)
                        // get best cell
                        pBestCell = pCell;
                }

                continue;
            }

            default:
                continue;
        }
    }

    // is player 1?
    if (player == IE_Pl_Player1)
        return max;

    return min;
}
//------------------------------------------------------------------------------
