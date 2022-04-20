#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H


#include "includes.h"
#include "Position.h"
using namespace std;



//
// all valid moves for a knight
//
static Position::Delta deltas[] = {
    Position::Delta(1,2), Position::Delta(2,1),
    Position::Delta(2,-1), Position::Delta(1,-2),
    Position::Delta(-2,-1), Position::Delta(-1,-2),
    Position::Delta(-2,1), Position::Delta(-1,2)
};


//
// base class representing chess pieces basic functionality
//
class ChessPiece
{

protected:
    
    //
    // we don't want anyone instantiating this class directly,
    // they must derived from it and call initDeltas() to setup
    // the allowable moves for the piece
    //
    ChessPiece( const Position& pos ) : m_currentPos(pos)
    {}
    
public:
    
    //
    // list of Deltas representing the directions and distances this piece is allowed to move
    //
    typedef vector<Position::Delta> Deltas;
    
    //
    // return the rank and file offsets determining this pieces relative movements
    //
    const Deltas& getDeltas() const
    {
        return m_deltas;
    }

    //
    // list of positions used to represent where this piece can move to
    //
    typedef vector<Position> Moves;
    
    //
    // returns a list of valid moves from the current position
    //
    const Moves& getValidMoves() const
    {
        if( !m_validMoves.size() )
        {
            //
            // lazily calculate valid moves from current position
            //
            Deltas deltas = getDeltas();
            for( Deltas::const_iterator i = getDeltas().begin(); i != getDeltas().end(); i++ )
            {
                const Position::Delta& delta = *i;
                if( m_currentPos.isValidMove( delta ) )
                {
                    Position newPos = m_currentPos + delta;
                    m_validMoves.push_back( newPos );
                }
            }
        }
        return m_validMoves;
    }
    
    //
    // return current position
    //
    const Position& getPosition() const
    {
        return m_currentPos;
    }
    
protected:
    
    //
    // helper so derived classes can initialize m_deltas from a
    // plain old c style array
    //
    void initDeltas( const Position::Delta * d, size_t numberOfDeltas)
    {
        m_deltas = Deltas( d, d + numberOfDeltas );
    }
    
    //
    // current position
    //
    Position m_currentPos;
    
    //
    // list of directions and distances the chess piece can move.
    // Should be initialized by any derived classes
    //
    Deltas m_deltas;
    
    //
    // all the moves in relation to the current position.
    // it is defined as mutable to allow for lazy evaluation
    //
    mutable Moves m_validMoves;
    
};

//
// Knight is an instance of ChessPiece with movement deltas which allow it to move
// 2 squares horizontaly and 1 square vertically and vice versa
//
class Knight : public ChessPiece
{
    
public:
        
    Knight( const Position& pos) : ChessPiece(pos)
    {
        //
        // setup the valid moves
        //
        initDeltas( deltas ,  sizeof(deltas)/sizeof(deltas[0]) );
    }
    
};


#endif