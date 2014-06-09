//
//  Grid.h
//  tstcpp
//
//  Created by seven on 6/10/14.
//  Copyright (c) 2014 none. All rights reserved.
//

#ifndef tstcpp_Grid_h
#define tstcpp_Grid_h
struct COORD {int X; int Y;};
class Grid{
public:
    int GetWidth(){ return width; }
    int GetHeight(){ return height; }
    bool Grid_Boundry(int x, int y)
    {
        if( x < 0 || x >= width || y < 0 || y >= height )
            return false;
        return true;
    }
    bool Grid_isWall(int id)
    {
        return false;
      //  if( GridTiles[id] >= 1)
            return false;
        return true;
    }
    int width, height;
};
#endif
