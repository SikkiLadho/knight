
#include "includes.h"
#include "Position.h"
#include "UniformCostSearch.h"
#include "ChessPiece.h"
#include "KnightsTravailHelper.h"

using namespace std;
void solveKnightsTravail( const Position& start, const Position& end)
{
    Position posStart(start), posEnd(end);
    KnightsTravailHelper helper(posEnd);
    
    UniformCostSearch<Position> solver( posStart, helper );
    
    UniformCostSearch<Position>::States result = solver.findShortestPathToGoal();
    
    for(UniformCostSearch<Position>::States::const_iterator i = result.begin(); i != result.end(); i++)
    {
            cout << *i << " ";
    }
    
    cout << endl;
}



int main()
{

    Position start, end;
  
    try
    {

        cout<<"Enter start position in algebraic notation:";
        cin >> start;
        cout<<"Enter end position in algebraic notation:";
        cin >> end;    
        solveKnightsTravail( start, end );         
    }
    catch( exception& ex)
    {
        ///
        // something bad happened - probably invalid arguments
        //
        cout << "error: " << ex.what() << endl;
        return 1;
    }
    
    return 0;
}