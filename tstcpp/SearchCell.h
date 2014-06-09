//
//  SearchCell.h
//  tstcpp
//
//  Created by seven on 6/10/14.
//  Copyright (c) 2014 none. All rights reserved.
//

#ifndef tstcpp_SearchCell_h
#define tstcpp_SearchCell_h
#include <cmath>

class SearchCell
{
public:
    int m_xcoord, m_ycoord, m_id;
    
    SearchCell *parent;
    
    float G;
    float H;
    
    SearchCell() : parent(0) { };
    SearchCell(int x, int y, int id, SearchCell *_parent) :
    m_xcoord(x),
    m_ycoord(y),
    parent(_parent),
    m_id( id),
    G(0.0f),
    H(0.0f)
    {  };
    
    float GetF() { return G + H; }
    float heuristic(SearchCell *NodeEnd)
    {
        float x = (float)(fabs((float)this->m_xcoord - NodeEnd->m_xcoord));
        float y = (float)(fabs((float)this->m_ycoord - NodeEnd->m_ycoord));
        
        //Good
        return x + y ;
        
        // Better
        // return sqrt(x*x+y*y);
        
        //Best
        // return std::max(x,y);
        
        //Allway The shortest path
        //return 0.0f;
    }
};


#endif
