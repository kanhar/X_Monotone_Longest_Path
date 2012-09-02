#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <stack>
#include <string>
#include <math.h>
#include <sstream>

#include <stdio.h>
#include <stdlib.h>

using namespace std;


/***************************************************************/
/**************************Classes******************************/
/***************************************************************/

/***************************************************************/
// Class Used a data structure to hold a Cartesian Point (x,y)
/***************************************************************/
class Point {
public:
   int x;
   int y;
   int name;
   float lengthLongestPath;
   int lastPath;

   Point(){
       x=-1;
       y=-1;
       name = -1;
       lastPath = -1;
       lengthLongestPath = -1;
   }

   Point(int pName){
       x=0;
       y=0;       
       name = pName;
       lastPath = 0;
       lengthLongestPath = 0.0;
   }

   Point(const Point& p1)
   {
        x =      p1.x;
        y =      p1.y;
        name =   p1.name;
        lastPath = p1.lastPath;
        lengthLongestPath = p1.lengthLongestPath;
   }

   bool Equals(Point p)
   {
       return p.name == name? true: false;
   }

   bool IsLessThan(Point p)
   {
       if (x < p.x)
           return true;
       else
           return false;
   }

   string toString(int num)
   {
        std::stringstream ss;
        ss << num;
        return ss.str();
   }

   void Print()
   {
       cout << "P" << name;
   }

   string GetName()
   {
       return toString(name);
   }

   string GetFull()
   {
       string tmp= "";
       tmp+= "P";
       tmp+= toString(name);
       tmp+= "(";
       tmp+= toString(x);
       tmp+= ",";
       tmp+= toString(y);
       tmp +=")";

       return tmp;
   }

   string GetFullPath()
   {
       string tmp= GetFull();
       tmp+="\t\tLastPath:" + toString(lastPath);
       tmp+="\tlength:" + toString(lengthLongestPath);
       return tmp;
   }
};




/***************************************************************/
// Class Used to represent an Edge(or Line) between two Points**
/***************************************************************/

class Edge  {
public:
    Point _start;
    Point _end;
    float _distance;
    int _name;

    Point* _intersections;
    int _countIntersections;

    Edge()
    {
        _start = Point();
        _end = Point();
        _distance = 0.0;
        _name = -1;
        _countIntersections = 0;
        _intersections = new Point[100];
    }

    Edge(const Edge& l1)
    {
        _start = Point(l1._start);
        _end = Point(l1._end);
        _distance = l1._distance;
        _name = l1._name;
        _intersections = l1._intersections;
        _countIntersections = l1._countIntersections;
    }


    bool PointExists(Point p)
    {
        for(int i=0;i<_countIntersections; i++)
            if (_intersections[i].Equals(p))
                return true;
        return false;
    }

    void AddPoint(Point p)
    {
         if( !PointExists(p))
             _intersections[_countIntersections++] = Point(p);
    }


    Point GetHeadPoint()
    {
         return Point(_intersections[_countIntersections-1]);
    }


    string GetPath()
    {
        string tmp = "";
        for(int i=0;i<_countIntersections; i++)
        {
            if (i+1 == _countIntersections)
            {
                tmp+= _intersections[i].GetFull();
                break;
            }

            Edge l;
            l._start = Point(_intersections[i]);
            l._end   = Point(_intersections[i+1]);
            l._name  = i;
            l.CalculateDistance();
            tmp+= l.GetLine();
        }
        return tmp;
    }

    void DeleteAll()
    {
        _countIntersections = 0;
    }

    string toString(float num)
    {
         std::stringstream ss;
         ss << num;
         return ss.str();
    }

    string toString(int num)
    {
         std::stringstream ss;
         ss << num;
         return ss.str();
    }

    string getName()
    {
        return toString(_name);
    }

    bool IsLessThan(Edge b)
    {
        if (_start.x < b._start.x)
            return true;
        else
            return false;
    }


    float CalculateDistance(Point a, Point b){
        return sqrt (pow(b.y - a.y, 2) + pow(b.x - a.x,2) );
    }

    void CalculateDistance()
    {
        _distance = CalculateDistance(_start,_end);
    }

    string GetLine()
    {
        string tmp = "";
        tmp+= "Line " + toString(_name) + "\t";
        tmp+= _start.GetFull();
        tmp+= "\t";
        tmp+= _end.GetFull();
        tmp+= "\t\t DIST: ";
        tmp+= toString(_distance);        
        return tmp;
    }

};


