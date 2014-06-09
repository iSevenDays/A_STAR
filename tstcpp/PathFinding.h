//
//  PathFinding.h
//  tstcpp
//
//  Created by seven on 6/10/14.
//  Copyright (c) 2014 none. All rights reserved.
//

#ifndef tstcpp_PathFinding_h
#define tstcpp_PathFinding_h


#include <vector>
#include "SearchCell.h"
#include "Grid.h"

class PathFinding
{
public:
    PathFinding();
    ~PathFinding();
    // Sets Start and End//
    bool FindPath(COORD CurrentPos, COORD TargetPos );
    //Gets next Position//
    COORD NextPathPos();
    
    bool m_FoundGoal;
    Grid *myGridptr;

private:
    
    typedef std::shared_ptr<COORD> SPv;
    typedef std::shared_ptr<SearchCell> SPsc;
    
    void AddCell(int x, int y, float newCost, SearchCell *_parent);
    
    std::shared_ptr<SearchCell> GetNextCell();
    
    void SearchPath();
    
    SPsc m_StartCell;
    SPsc m_GoalCell;
    
    std::vector<SPsc > m_OpenList;
    std::vector<SPsc > m_ClosedList;
    std::vector<SPv > m_PathToGoal;   
};

#endif
