#ifndef POSITION_H
#define POSITION_H

#include "includes.h"


using namespace std;



//
// represents the position of a chess piece on a chess board in algebraic notation.
// 


class Position
{
    
public:
    //
    // horizontal positions are known as rank and represented by letters A through H
    // internally stored as capital letters, but we convert from lowercase if that was passed in the constructor
    //
    typedef char Rank;
    
    //
    // vertical postion or file represented by numbers 1 through 8
    // (actually stored as ascii values). 
    //
    typedef char File;
    
    //
    // the Delta type is used to represent a move from  position
    // can be a positive or negative offset for rank and file
    //
    struct Delta
    {
        Delta( int rankOffset, int fileOffset ) : rank(rankOffset), file(fileOffset) {}
        int rank;
        int file;
    };

    //
    // define maximum and minimum values for dimension of chessboard.
    // we don't have to actually model a chessboard to solve this problem,
    // however if we needed to deal with other pieces on the chessboard it might be useful to do so
    //
    static const Rank minRank = 'A';
    static const Rank maxRank = 'H';
    static const File minFile = '1';
    static const File maxFile = '8';
    
    //
    // default constructor initializes to "A1"
    //
    Position() : m_rank(minRank), m_file(minFile) {}
    
    //
    // construct from a string as read from input
    // PRECONDITION: pos is a 2 character string representing an chess position in algebraic notation
    // may be uppercase or lowercase
    //
    Position( const char* strPos  )
    {
        if(!strPos)
            throw std::invalid_argument( "strPos must point to a 2 character string in algebraic chess notaion" );
        
        Rank r = toupper(strPos[0]);
        File f = strPos[1];
        
        if( isValidFile(f) && isValidRank(r) )
        {
            m_rank = r;
            m_file = f;
        }
        else
        {
            throw std::invalid_argument( "rank and/or file are out of range" );
        }
    }
    
    //
    // return true if its a legal move, ie: within the bounds of the chessboard
    //
    bool isValidMove( const Delta& delta ) const
    {
        return isValidRank( m_rank + delta.rank ) && isValidFile( m_file + delta.file);
    }
    
    //
    // move by the supplied delta
    //
    Position& move( const Delta& delta )
    {
        if ( isValidMove( delta) )
        {
            //
            // we are relying on the property that ascii values are consecutive
            // for consecutive numbers and letters, which makes the move calculation
            // nice and easy
            //
            m_rank += delta.rank;
            m_file += delta.file;
        }
        else
        {
            throw std::invalid_argument( "move is out of range" );
        }
        
        return *this;
    }
    
    //
    // accessors for rank
    //
    Rank getRank() const
    {
        return m_rank;
    }
    
    //
    // accessors for file
    //
    File getFile() const
    {
        return m_file;
    }
    
    //
    // define equality operator which will be useful for determining when we have reached the goal
    //
    bool operator==(const Position &rhs) const
    {
        return m_rank == rhs.m_rank && m_file == rhs.m_file;
    }
    
    //
    // for completeness, define inequality operator 
    //
    bool operator!=(const Position &rhs) const
    {
        //
        // use equality relationship to avoid duplicating code
        //
        return !( (*this) == rhs);
    }
    
    //
    // and why not an compound addition operator for moving positions by Deltas
    //
    Position& operator+=( const Delta &delta ) 
    {
        return move( delta );
    }
    
    //
    // once again for completeness we can define and addition operator using the above += definition
    // returns a const Position so result cant be used as an lvalue
    //
    const Position operator+( const Delta& delta ) const
    {
        Position newPos = *this;
        newPos += delta;
        return newPos;
    }
    
    //
    // so we can display our positions
    //
    friend std::ostream& operator<< (std::ostream& stream, const Position& pos ) 
    {
        stream << pos.m_rank << pos.m_file;
        return stream;
    }

    //
    // so we can read positions from standard input
    //
    friend std::istream& operator>> (std::istream& stream, Position& pos ) 
    {
	string strPos;
	stream >> strPos;
	Position tempPos( strPos.c_str() );
	pos = tempPos;

        return stream;
    }
    
private:
    
    //
    // range check rank
    //
    bool isValidRank( Rank r ) const
    {
        return r <= maxRank && r >= minRank;
    }
    
    //
    // range check file
    //
    bool isValidFile( File f ) const
    {
        return f <= maxFile && f >= minFile;
    }
    
    Rank m_rank;
    File m_file;
    
};


#endif