#ifndef UNIFORM_COST_SEARCH_H
#define UNIFORM_COST_SEARCH_H


#include "includes.h"
//
// utility class for finding shortest path to goal utilizing Uniform Cost Search,
// also known as Least Cost Search, a variation of Bredth First Search.
// template argument must support operator= otherwise it wont compile ;)
//


template<class State>
class UniformCostSearch
{
public:
    
    //
    // path to our goal state is represented as a list of states
    //
    typedef vector<State> States;
    
    //
    // abstract helper class which provide goal test function and
    // successor states for the search
    //
    class SearchHelper
    {
    public:
        
        //
        // override this function to return true if we have reached the goal
        //
        virtual bool isGoal( const State& s) const = 0;
        
        //
        // override this function to return a list of successor states from the current state
        //
        virtual States getSuccessors( const State& s ) const = 0;
        
    };
    
    //
    // constructor takes the start state and a helper function object
    //
    UniformCostSearch( const State& start, const SearchHelper& helper ) : m_start(start), m_helper(helper) {}
    
    //
    // initiates a uniform cost search to find the shortest path to the goal state.
    // if no path is found then it returns an empty list
    //
    States findShortestPathToGoal()
    {
        
        //
        // the frontier is an ordered list of paths we have blazed fro mthe start state (from shortest to longest),
        // since every action has the same cost there is no need to use a priority queue
        //
        typedef queue<States> Frontier;
        
        //
        // keep track of states which have already been explored.
        // for larger searches a set would be better, but it requires State to support
        // operator< so lets use a list even though search time is linear
        //
        typedef vector<State> Explored;
        
        //
        // first check if we are already at the goal. If so we're done
        //
        if( m_helper.isGoal(m_start))
        {
            States result;
            result.push_back(m_start);
            return result;
        }
        
        //
        // set of states we have visited so far
        //
        Explored explored;
        
        //
        // ordered list of paths which have already been blazed.
        // Start with the path containing the start state only.
        //
        Frontier frontier;
        States initialPath;
        initialPath.push_back( m_start );
        frontier.push(initialPath);
        
        //
        // keep going whilst there are still unexplored paths
        //
        while( !frontier.empty() )
        {
            //
            // expand the shortest path in the frontier first
            //
            States path = frontier.front();
            frontier.pop();
            State s = path.back();
            
            //
            // now explore the successor states
            //
            States successors = m_helper.getSuccessors( s );
            for( typename States::const_iterator i = successors.begin(); i != successors.end(); i++)
            {
                const State& state = *i;
                
                //
                // has this state been explored already?
                //
                if( find( explored.begin(), explored.end(), state ) == explored.end() )
                {
                    //
                    // no... mark it as explored
                    //
                    explored.push_back(state);
                    //
                    // construct a new path with the current state at the end
                    //
                    States exploredPath(path);
                    exploredPath.push_back(state);
                    if( m_helper.isGoal(state))
                    {
                        //
                        // return the path to the goal
                        //
                        return exploredPath;
                    }
                    else
                    {
                        //
                        // haven't found the path to the goal yet so add this path to the frontier and keep exploring
                        //
                        frontier.push( exploredPath );
                    }
                }
            }
        }
        
        //
        // if we got here we couldn't find a path to the goal
        //
        States emptyPath;
        return emptyPath;
    }

    
private:
    
    //
    // start state
    //
    State m_start;
    
    //
    // search helper
    //
    const SearchHelper& m_helper;
    
};




#endif