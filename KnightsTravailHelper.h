#ifndef KNIGHTS_TRAVAIL_HELPER_H
#define KNIGHTS_TRAVAIL_HELPER_H

#include "ChessPiece.h"

//
// this helper class is used to determine when we have reached the goal and also
// generate the successor positions
//
class KnightsTravailHelper : public UniformCostSearch<Position>::SearchHelper
{
public:
    KnightsTravailHelper( const Position& goal) : m_goal(goal) {}
    
    virtual bool isGoal( const Position& s) const
    {
        return s == m_goal;
    }
    
    virtual UniformCostSearch<Position>::States getSuccessors( const Position& s ) const
    {
        Knight theKnight(s);
        return theKnight.getValidMoves();
    }
    
private:
    Position m_goal;
};


#endif