#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <stack>
#include <string>
#include <cstring>
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




/***************************************************************/
/**************************Constants****************************/
/***************************************************************/

const int MAX_POINTS        =   1024;
const bool OBSTACLE         =   true;
const bool VERBOSE          =   true;

char *win_name_string       =   (char*)"X-Monotone Longest Path";
char *icon_name_string      =   (char*)"X-Monotone";
char *incorrect_usage       =   (char*)"Usage: g++ main.cpp brass.tst \n";

/****************Graphics Xlib Code******************************/

Display *display_ptr;
Screen *screen_ptr;
int screen_num;
char *display_name = NULL;
int display_width, display_height;

Window win;
int border_width;
int win_width, win_height;
int win_x, win_y;

XWMHints *wm_hints;
XClassHint *class_hints;
XSizeHints *size_hints;
XTextProperty win_name, icon_name;

XEvent report;

GC gc, gc_yellow, gc_red, gc_grey;
unsigned long valuemask = 0;
XGCValues gc_values, gc_yellow_values, gc_red_values, gc_grey_values;
Colormap color_map;
XColor tmp_color1, tmp_color2;

/***********End Graphics Code****************************************/












/***********Begin Core Program Variable Declaration****************************************/

int l_ptr, p_ptr, ptr, path_ptr, highest, MAX;
char *fileName;
Edge *lineSegments;
Point *points, *path;

void Test();
void LoadFileAndGetIntersections();
void CalculateMinDistance();
void ReadFile();
void PrintDistances();
void PrintFile();
bool PathExistLEQDistance(float pLessThanDistance);

bool ClockWise(Point a, Point b, Point c);
bool IsObstructed(Point a, Point b, Point c, Point d);
bool IsObstructed(Point a, Point b);
Point GetIntersection(Edge pA, Edge pB);
bool IsObstructed(Edge pA, Edge pB);
float CalculateDistance(Point a, Point b);
void Draw();
void InitXLib(int argc, char **argv);
void DrawLine(GC pGC, int a, int b, int c, int d);
void DrawPoint(GC pGC, int a, int b);
void DrawLine(GC pGC, Edge e);
void DrawPoint(GC pGC,Point a);
void DrawImageString(GC pGC, Point p, string msg);
void DrawImageString(GC pGC, int a, int b, string msg);

void PrintLines();
void SortLines();
void PrintPoints();
void SortPoints();

Point FindValue(Point pPoint);
void GetUpdatedValue();
Point GetPoint(int pIndex);


int main(int argc, char **argv)
{
    //Validate Arguments
    if ( argc != 2 )
    {
        cout << incorrect_usage;
        //return -1;
    }

    fileName = argv[1];

    ifstream the_file ( fileName );
    if ( !the_file.is_open() )
    {
        cout<<"Could not open file " << argv[1] << "\n";
        return -1;
    }

    int i,j;

    //Begin Main Program Code
    MAX = -1;
    highest = -1;
    path = new Point[100];

    path_ptr=0;

    //A method that reads file into an array of edges, sorts it and gets intersections
    LoadFileAndGetIntersections();

    //Extract Points
    Point tmp;
    for(i=0;i<ptr; i++)\
    {
        for(j=i+1;j<ptr; j++)
        {
            if (points[j].IsLessThan(points[i]))
            {
                tmp = points[i];
                points[i] = points[j];
                points[j]= tmp;
            }
        }
    }

    for(i=0;i<ptr; i++)
        cout << points[i].GetFull() << endl;

    GetUpdatedValue();

    //Update Values (similar to Djikstra) for each node, to reflect the length of the longest path ending at that node

    if (VERBOSE)
    {
        cout << "Algorithm applied, all points maintain the length of the longest path ending at that point \n";
        cout << "****************************************************************************************** \n";        
        PrintLines();
        cout <<endl;
        PrintPoints();
        cout << endl;
    }

    //Find Longest Path
    for(i=0;i<ptr; i++)
    {
        if (points[i].lengthLongestPath > MAX)
        {
            MAX = points[i].lengthLongestPath;
            highest = points[i].name;
        }
    }

    Point iter = GetPoint(highest);
    cout << "Highest Value is Ending with Path " << iter.name << ",";
    path[path_ptr++] = iter;

    while(iter.lastPath != -1)
    {
        cout << iter.lastPath << ",";
        iter = GetPoint(iter.lastPath);
        path[path_ptr++] = iter;
    }

    cout << endl;
    for(i=0;i<path_ptr;i++)
        cout << path[i].GetFullPath() << endl;

    InitXLib(argc, argv);
    Draw();

    return 0;
}

Point GetPoint(int pIndex)
{
    int i=0;
    for (i=0;i<ptr; i++)
    {
        if (points[i].name == pIndex)
            return points[i];
    }
    cout << "Error Occurred, for Control should not Reach Here \n";
    return Point();
}

void GetUpdatedValue()
{    
    int i,j, sweep, lastPath;
    float MaxDist;
    bool PathFound;

    MaxDist = -1;
    lastPath = -1;
    PathFound = false;

    for(sweep=0;sweep< ptr; sweep++)
    {
        PathFound = false;

        //Loop through Lines
        for(i=0;i<l_ptr; i++)
        {
            if (PathFound)
                continue;

            Edge curEdge = lineSegments[i];

            //If Sweep Point == Start Point (A) of Line (AB)
            if (curEdge._start.Equals(points[sweep]))
            {
                points[sweep].lastPath = -1;
                points[sweep].lengthLongestPath = 0;
                PathFound = true;
            }
            //If End point (B) of Line (AB)
            else if (curEdge._end.Equals(points[sweep]))
            {
                //Default Best Point, is Start Point of Line, but that can change, as we can check intersections
                lastPath    = curEdge._start.name;
                MaxDist     = curEdge._distance;

                //Check All Intersections for Current Edge
                for(j=0;j<curEdge._countIntersections; j++)
                {
                    //Lookup Latest Value of Intersection Point as it may have changed
                    Point intPoint  = GetPoint(curEdge._intersections[j].name);
                    int dist        = curEdge.CalculateDistance(intPoint,points[sweep]) + intPoint.lengthLongestPath;

                    if (dist > MaxDist)
                    {
                        MaxDist     = dist;
                        lastPath    = intPoint.name;
                    }
                }

                points[sweep].lastPath = lastPath;
                points[sweep].lengthLongestPath = MaxDist;

                PathFound = true;
            }
            //Must be an intersection Point
            else if (curEdge.PointExists(points[sweep]))
            {
                //Default Best Point, is Start Point of Line, but that can change, as we can check intersections
                lastPath    = curEdge._start.name;
                MaxDist     = curEdge._distance;

                //Check All Intersections for Current Edge
                for(j=0;j<curEdge._countIntersections; j++)
                {
                    //Lookup Latest Value of Intersection Point as it may have changed
                    Point intPoint  = GetPoint(curEdge._intersections[j].name);
                    int dist        = curEdge.CalculateDistance(intPoint, points[sweep]) + intPoint.lengthLongestPath;;

                    //Caveat: Since this is an intersection, point and its a Sweep Algorithm
                    //          we must ensure that only points LESS THAN sweep point are considered.
                    if (!intPoint.IsLessThan(points[sweep]))
                        continue;

                    if (dist > MaxDist)
                    {
                        MaxDist     = dist;
                        lastPath    = intPoint.name;
                    }
                }

                points[sweep].lastPath = lastPath;
                points[sweep].lengthLongestPath = MaxDist;

                PathFound = true;
            }
            else
            {
                continue;
            }
        }

    }
}








//This function does the following :-
//1) reads in the file's points, obstacles and boundaries into local variables
//2) calculates the edge distances (with or without obstacle detection)
//3) Prints out the file as read into the local data structures (if Verbose option is set)
void LoadFileAndGetIntersections()
{
    FILE *input;
    int i,j, ret, c1, c2,c3,c4;

    l_ptr=0;

    lineSegments = new Edge[100];

    //*******************BEGIN FILE READ**********************************//
    input= fopen(fileName, "r+");

    if (input==NULL)
        perror ("Error opening file");

    ret = fscanf(input, "[%d,%d]x[%d,%d]\n", &c1, &c2, &c3, &c4);

    while(feof(input)== 0)
    {
        ret = fscanf(input,"S (%d,%d) (%d,%d)\n",
                     &lineSegments[l_ptr]._start.x,
                     &lineSegments[l_ptr]._start.y,
                     &lineSegments[l_ptr]._end.x,
                     &lineSegments[l_ptr]._end.y);
        if (ret == 0)
            break;


        lineSegments[l_ptr]._name       = l_ptr;

        if (l_ptr==0)
        {
            lineSegments[l_ptr]._start.name = l_ptr;
            lineSegments[l_ptr]._end.name   = l_ptr+1;            
        }
        else
        {
            lineSegments[l_ptr]._start.name = lineSegments[l_ptr-1]._end.name + 1;
            lineSegments[l_ptr]._end.name   = lineSegments[l_ptr-1]._end.name + 2;;                                               
        }

        lineSegments[l_ptr].CalculateDistance();
        l_ptr++;
    }
    fclose(input);

    //*******************END FILE READ**********************************//

    p_ptr = lineSegments[l_ptr-1]._end.name + 1 ;

    points = new Point[100];

    ptr=0;

    cout << "\nSearching for Intersection Points\n";
    cout << "****************************************************************************************** \n";

    for(i=0;i< l_ptr; i++)
    {
        points[ptr++] = Point(lineSegments[i]._start);
        points[ptr++] = Point(lineSegments[i]._end);
        for(j=i+1; j< l_ptr; j++)
        {
            Edge a = lineSegments[i];
            Edge b = lineSegments[j];

            if (IsObstructed(a, b))
            {
                Point p = GetIntersection(a,b);
                p.name = p_ptr++;

                lineSegments[i].AddPoint(p);
                lineSegments[j].AddPoint(p);

                points[ptr++] = Point(p);

            }
        }
    }

}



//Determines if theree points are clockwise
bool ClockWise(Point a, Point b, Point c)
{
    int side1 = (c.y - a.y) * (b.x-a.x) ;
    int side2 = (c.x-a.x)   * (b.y-a.y);

    if (side1 > side2)
        return false;
    else
        return true;
}

//Determines if the Line (a,b) is obstructed by the Line (c,d)
bool IsObstructed(Point a, Point b, Point c, Point d)
{
    bool acd = ClockWise(a,c,d);
    bool bcd = ClockWise(b,c,d);
    bool abc = ClockWise(a,b,c);
    bool abd = ClockWise(a,b,d);

    bool isOb;
    if (acd != bcd && abc != abd)
        isOb = true;
    else
        isOb = false;

    return  isOb;
}


//Determines if the Line (a,b) is obstructed by the Line (c,d)
bool IsObstructed(Edge pA, Edge pB)
{
    return IsObstructed(pA._start, pA._end, pB._start, pB._end);
}


//Determines if the Line (a,b) is obstructed by the Line (c,d)
Point GetIntersection(Edge pA, Edge pB)
{
    int x1, y1,x2,y2, A1, B1, C1, A2, B2, C2;
    double det;
    Point intersection;

    x1 = pA._start.x;
    y1 = pA._start.y;
    x2 = pA._end.x;
    y2 = pA._end.y;

    A1 = y2-y1;
    B1 = x1-x2;
    C1 = A1*x1+B1*y1;

    x1 = pB._start.x;
    y1 = pB._start.y;
    x2 = pB._end.x;
    y2 = pB._end.y;

    A2 = y2-y1;
    B2 = x1-x2;
    C2 = A2*x1+B2*y1;

    det = A1*B2 - A2*B1;
    if(det == 0)
    {
        cout << "Lines are Parallel";
        return intersection;
    }
    else
    {
        intersection.x = (B2*C1 - B1*C2)/det;
        intersection.y = (A1*C2 - A2*C1)/det;
        return intersection;
    }
}




void PrintPoints()
{
    int i;
    cout << "#\tPoint \t\tLast\tLongestPath\n";
    for(i=0;i<ptr; i++)
        cout << i << "\t" << points[i].GetFullPath() << endl;
}

void PrintLines()
{
    int i,j;
    cout << "\n";
    cout << "Line " << "\t" << "Start " << "\t" << "End" << "\t\t\t\tIntersection Information"<<endl;
    for(i=0;i<l_ptr; i++)
    {
        cout << lineSegments[i].GetLine() << "\t";
        for(j=0;j<lineSegments[i]._countIntersections; j++)
            cout << lineSegments[i]._intersections[j].GetFull() << ", ";
        cout << "\n";
    }
}



/***************************************************************/
/****************Graphics Xlix Code******************************/
/***************************************************************/
void InitXLib(int argc, char **argv)
{
/* opening display: basic connection to X Server */
  if( (display_ptr = XOpenDisplay(display_name)) == NULL )
    { printf("Could not open display. \n"); exit(-1);}

  printf("Connected to X server  %s\n", XDisplayName(display_name) );

  screen_num 	 = DefaultScreen( display_ptr );
  screen_ptr 	 = DefaultScreenOfDisplay( display_ptr );
  color_map  	 = XDefaultColormap( display_ptr, screen_num );
  display_width  = DisplayWidth( display_ptr, screen_num );
  display_height = DisplayHeight( display_ptr, screen_num );

  printf("Width %d, Height %d, Screen Number %d\n",
           display_width, display_height, screen_num);

  /* creating the window */
  border_width = 10;
  win_x = 100; win_y = 100;
  win_width = display_width/2;
  win_height = (int) (win_width / 1.7); /*rectangular window*/


  win= XCreateSimpleWindow( display_ptr, RootWindow( display_ptr, screen_num),
                            win_x, win_y, win_width, win_height, border_width,
                            BlackPixel(display_ptr, screen_num),
                            WhitePixel(display_ptr, screen_num) );

  /* now try to put it on screen, this needs cooperation of window manager */
  size_hints 	= XAllocSizeHints();
  wm_hints 	= XAllocWMHints();
  class_hints 	= XAllocClassHint();

  if( size_hints == NULL || wm_hints == NULL || class_hints == NULL )
    { printf("Error allocating memory for hints. \n"); exit(-1);}

  size_hints -> flags = PPosition | PSize | PMinSize  ;
  size_hints -> min_width = 60;
  size_hints -> min_height = 60;

  XStringListToTextProperty( &win_name_string,1,&win_name);
  XStringListToTextProperty( &icon_name_string,1,&icon_name);

  wm_hints -> flags = StateHint | InputHint ;
  wm_hints -> initial_state = NormalState;
  wm_hints -> input = False;

  class_hints -> res_name = (char*)"x_use_example";
  class_hints -> res_class = (char*)"examples";

  XSetWMProperties( display_ptr, win, &win_name, &icon_name, argv, argc,
                    size_hints, wm_hints, class_hints );

  /* what events do we want to receive */
  XSelectInput( display_ptr, win,            ExposureMask | StructureNotifyMask | ButtonPressMask );

  /* finally: put window on screen */
  XMapWindow( display_ptr, win );

  XFlush(display_ptr);

  /* create graphics context, so that we may draw in this window */
  gc = XCreateGC( display_ptr, win, valuemask, &gc_values);
  XSetForeground( display_ptr, gc, BlackPixel( display_ptr, screen_num ) );
  XSetLineAttributes( display_ptr, gc, 1,LineOnOffDash, CapRound, JoinRound);

  //Yellow
  gc_yellow = XCreateGC( display_ptr, win, valuemask, &gc_yellow_values);
  XSetLineAttributes(display_ptr, gc_yellow, 1, LineSolid,CapRound, JoinRound);
  if( XAllocNamedColor( display_ptr, color_map, "yellow", &tmp_color1, &tmp_color2 ) == 0 )
    {printf("failed to get color yellow\n"); exit(-1);}
  else
    XSetForeground( display_ptr, gc_yellow, tmp_color1.pixel );

  //Red
  gc_red = XCreateGC( display_ptr, win, valuemask, &gc_red_values);
  XSetLineAttributes( display_ptr, gc_red, 2, LineSolid, CapRound, JoinRound);
  if( XAllocNamedColor( display_ptr, color_map, "red",&tmp_color1, &tmp_color2 ) == 0 )
    {printf("failed to get color red\n"); exit(-1);}
  else
    XSetForeground( display_ptr, gc_red, tmp_color1.pixel );

  //Grey
  gc_grey = XCreateGC( display_ptr, win, valuemask, &gc_grey_values);
  if( XAllocNamedColor( display_ptr, color_map, "light grey", &tmp_color1, &tmp_color2 ) == 0 )
    {printf("failed to get color grey\n"); exit(-1);}
  else
    XSetForeground( display_ptr, gc_grey, tmp_color1.pixel );

}

//Draws a line between point(a,b) and point(c,d)
void DrawImageString(GC pGC, Point p, string msg)
{
    DrawImageString(pGC, p.x, p.y, msg);
}

//Draws a line between point(a,b) and point(c,d)
void DrawImageString(GC pGC, int a, int b, string msg)
{
    XDrawImageString(display_ptr, win, pGC, a,win_height -  b, msg.c_str(), msg.length());
}

//Draws a line between point(a,b) and point(c,d)
void DrawLine(GC pGC, Edge e)
{
    DrawLine(pGC, e._start.x, e._start.y, e._end.x, e._end.y);
    if (VERBOSE)
    {
        DrawImageString(gc_grey,    e._start,     e._start.GetFull() );
        DrawImageString(gc_grey,    e._end,       e._end.GetFull() );
    }
}

//Draws a line between point(a,b) and point(c,d)
void DrawLine(GC pGC, int a, int b, int c, int d)
{
    XDrawLine(display_ptr, win, pGC, a,win_height -  b,c,win_height -  d);
}

//Draws a circle centered at P(a,b)
//Note: The bounding rectangle of an arc refers to the smallest rectangle that completely contains the arc)
void DrawPoint(GC pGC,Point a)
{
    DrawPoint(pGC, a.x, a.y);
    if (VERBOSE)
    {
        DrawImageString(gc_grey,   a, a.GetFull() );
    }
}

//Draws a circle centered at P(a,b)
//Note: The bounding rectangle of an arc refers to the smallest rectangle that completely contains the arc)
void DrawPoint(GC pGC, int a, int b)
{
    //DrawPoint(gc_red, 100, H-100);
    //DrawPoint(gc_red, 0, H-0);
    b = win_height -  b;

    //Two unsigned integers to specify the width and height of the bounding rectangle of the arc
    unsigned int widthBoundingRect = 10;
    unsigned int heightBoundingRect = 10;

    //Two integers that specify the upper left corner of the bounding rectangle of the arc
    //Note: as the function is required to center the circle at a,b, we need to calculate the values of the upperlefCorner
    // as below
    int upperLeftCornerBoundingRecta = a-widthBoundingRect/2;
    int upperLeftCornerBoundingRectb = b-widthBoundingRect/2;

    //finally two integers to specify the start and extent of the arc.
    int startArc = 0;
    int extentArc = 360*64;

    XFillArc( display_ptr, win, pGC, upperLeftCornerBoundingRecta,upperLeftCornerBoundingRectb,widthBoundingRect,heightBoundingRect, startArc, extentArc);
}




//Draws all Obstacles, Points, and Edges
void Draw()
{
    while(1)
    {
        XNextEvent( display_ptr, &report );
        if (report.type == Expose)
        {
            int i, j;

            for(i=0;i<l_ptr; i++)
            {
                DrawLine(gc_grey, lineSegments[i]);
                for(j=0;j<lineSegments[i]._countIntersections; j++)
                {
                    DrawPoint(gc_yellow,lineSegments[i]._intersections[j]);
                }
            }

            if (path_ptr > 1)
            {
                for(i=0;i<path_ptr-1;i++)
                {
                    Edge e ;
                    e._start = GetPoint(path[i].name);
                    e._end = GetPoint(path[i+1].name);
                    DrawLine(gc_red , e);
                }
            }
        }

    }
}



