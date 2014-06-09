#include "PathFinding.h"
#include <algorithm>

PathFinding::PathFinding()
{
    m_StartCell.reset();
    m_GoalCell.reset();
    m_FoundGoal = false;
    myGridptr = new Grid;
    m_OpenList.reserve( myGridptr->GetWidth() * myGridptr->GetHeight() );
}

PathFinding::~PathFinding() { }

bool PathFinding::FindPath(COORD CurrentPos, COORD TargetPos )
{
    
    if( m_FoundGoal )
    {
        m_OpenList.clear();
        m_ClosedList.clear();
        m_PathToGoal.clear();
    }
    
    m_StartCell.reset( new SearchCell(CurrentPos.X, CurrentPos.Y,CurrentPos.X+CurrentPos.Y*myGridptr->GetWidth(), 0));
    m_GoalCell.reset( new SearchCell(TargetPos.X, TargetPos.Y,TargetPos.X+TargetPos.Y*myGridptr->GetWidth(), 0));
    
    m_StartCell->H = m_StartCell->heuristic(m_GoalCell.get());
    
    m_OpenList.push_back(m_StartCell);
    
    m_FoundGoal = false;
    
    SearchPath();
    return m_FoundGoal;
}

std::shared_ptr<SearchCell> PathFinding::GetNextCell()
{
    // Find the lowest F score.
    //Using std::make_heap without push_heap and pop_heap is probably worthless.
    //But I can't use push_heap and pop_heap with the way I have this class designed.
    //I probably could just use std::min_element and it would work just as well.
    std::make_heap( m_OpenList.begin(), m_OpenList.end(), [] (SPsc a, SPsc b )
                   {
                       return a->GetF() > b->GetF();
                   } );
    
    SPsc nextCell = m_OpenList.front();
    m_ClosedList.push_back(nextCell);
    m_OpenList.erase( m_OpenList.begin() );
    
    return nextCell;
}

void PathFinding::AddCell(int x, int y, float newCost, SearchCell *_parent)
{
    if( !(myGridptr->Grid_Boundry(x, y)) )
        return;
    
    int id = y * myGridptr->GetWidth() + x;
    
    if( !(myGridptr->Grid_isWall( id)) )
        return;
    
    for(auto it = m_ClosedList.cbegin(); it != m_ClosedList.cend(); it++)
    {
        if( id == (*it)->m_id )
        {
            return;
        }
    }
    
    for(auto it = m_OpenList.cbegin(); it != m_OpenList.cend(); ++it)
    {
        if( id == (*it)->m_id )
        {
            if((*it)->G <= newCost)
            {
                return;
            }
            else
            {
                m_OpenList.erase(it);
                break;
            }
        }
    }
    
    SPsc newChild(new SearchCell(x, y, id, _parent));
    newChild->G = newCost;
    newChild->H = newChild->heuristic(m_GoalCell.get());
    m_OpenList.push_back(newChild);
    
}

void PathFinding::SearchPath()
{
    
    while (!m_OpenList.empty() )
    {
        SPsc currentCell = GetNextCell();
        
        if(currentCell->m_id == m_GoalCell->m_id )
        {
            m_GoalCell->parent = currentCell->parent;
            
            SearchCell *getPath = m_GoalCell.get();
            
            
            while(getPath->parent != NULL)
            {
                m_PathToGoal.push_back(SPv( new COORD) );
                m_PathToGoal.back()->X = getPath->m_xcoord;
                m_PathToGoal.back()->Y = getPath->m_ycoord;
                getPath = getPath->parent;
            }
            
            m_FoundGoal = true;
            return;
        }
        else
        {
            //right cell
            AddCell(currentCell->m_xcoord + 1, currentCell->m_ycoord, currentCell->G +1, currentCell.get());
            
            //Left side cell
            AddCell(currentCell->m_xcoord - 1, currentCell->m_ycoord, currentCell->G +1, currentCell.get());
            
            //Up
            AddCell(currentCell->m_xcoord, currentCell->m_ycoord -1, currentCell->G +1, currentCell.get());
            
            //Down
            AddCell(currentCell->m_xcoord, currentCell->m_ycoord +1, currentCell->G +1, currentCell.get());
            
            //Left up Diag
            AddCell(currentCell->m_xcoord - 1, currentCell->m_ycoord -1, currentCell->G +1.414f, currentCell.get());
            
            //Right up Diag
            AddCell(currentCell->m_xcoord + 1, currentCell->m_ycoord -1, currentCell->G +1.414f, currentCell.get());
            
            //Left Down Diag
            AddCell(currentCell->m_xcoord - 1, currentCell->m_ycoord +1, currentCell->G +1.414f, currentCell.get());
            
            //Right Down Diag
            AddCell(currentCell->m_xcoord + 1, currentCell->m_ycoord +1, currentCell->G +1.414f, currentCell.get()); 
            
        }
    }/// while
    m_FoundGoal = false;
    m_OpenList.clear();
    m_ClosedList.clear();
}

COORD PathFinding::NextPathPos()
{
    COORD nextPos ={0,0};
    
    nextPos = (*m_PathToGoal.back());
    m_PathToGoal.pop_back();
    
    if(m_PathToGoal.empty())
    {
        m_OpenList.clear();
        m_ClosedList.clear();
        m_FoundGoal = false;
    }
    
    return nextPos;   
}