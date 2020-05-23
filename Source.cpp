// Lab5
// Nick Flouty
// Finds a pass to the destination in a maze.
#include "EasyBMP.h"
#include "EasyBMP_DataStructures.h"
#include "EasyBMP_BMP.h"
#include "EasyBMP_VariousBMPutilities.h"
#include "EasyBMP.cpp" 
#include <ctime>
#include "Queue.h"
#include<iostream>
#include <cstdlib>
#include<string>
#include <limits>
using namespace std;

bool isBlack(BMP &image, coord x) {
	if ((image(x.x, x.y)->Red == 0) && (image(x.x, x.y)->Blue == 0) && (image(x.x, x.y)->Green == 0))
		return true;
	return false;
}
bool isValid(coord x, BMP &inputMaze) {
	//if start coord is out of picture
	if (x.x >= inputMaze.TellWidth() ||  x.y >= inputMaze.TellHeight() || x.x < 0 || x.y < 0)
		return false;
	//if start or finish coord is on a wall
	if (isBlack(inputMaze, x))
		return false;
	return true;
}

void BFS(BMP & I, BMP & O, coord s, coord t, int count) {
	// s is the start vertex, t is the destination
	// count returns the number of pixels that enter the queue
	// Pre-processing recommended: change I to BW image
	int height = I.TellHeight();
	int width = I.TellWidth();
	int numPixels = height * width;
	Queue Q = Queue(numPixels); 
	Q.insert(s,numPixels); count++;
	//RangedPixelToPixelCopy(I, 0, I.TellWidth(), I.TellHeight(), 0, O, 0, 0);
	coord p[width][height] = { 0 };
	bool visited[width][height] = { false };	// all vertices;
	visited[s.x][s.y] = true;	//v double array 
	int d[width][height] = { int INFINITY };
	d[s.x][s.y] = 0;	

	while (!Q.isEmpty() && !visited[t.x][t.y]) 
	{
		coord u = Q.remove(numPixels);
		
		// Check if Up is a valid move
		coord cUp;
		cUp.x = u.x;
		cUp.y = u.y - 1;
		//above neighbor is a valid point
		if (isValid(cUp,I) && (!visited[cUp.x][cUp.y]))
		{
			visited[cUp.x][cUp.y] = true;
			d[cUp.x][cUp.y] = d[u.x][u.y] + 1;
			p[cUp.x][cUp.y] =u;
			Q.insert(cUp,numPixels);
			count++;
		}//end error checking
		
		// Check if Down is a valid move
		coord cDown;
		cDown.x = u.x;
		cDown.y = u.y + 1;
		if (isValid(cDown, I) && !visited[cDown.x][cDown.y])
		{
			visited[cDown.x][cDown.y] = true;
			d[cDown.x][cDown.y] = d[u.x][u.y] + 1;
			p[cDown.x][cDown.y] = u;
			Q.insert(cDown,numPixels);
			count++;
		}
	
		// Check if Right is a valid move
		coord cR;
		cR.x = u.x+1;
		cR.y = u.y;
		if (isValid(cR, I) && !visited[cR.x][cR.y])	
		{
			visited[cR.x][cR.y] = true;
			d[cR.x][cR.y] = d[u.x][u.y] + 1;
			p[cR.x][cR.y] = u;	
			Q.insert(cR,numPixels);
			count++;
		}
		
		// Check if Left is a valid move
		coord cL;
		cL.x = u.x-1;
		cL.y = u.y;
		if (isValid(cL, I) && !visited[cL.x][cL.y])	
		{
			visited[cL.x][cL.y] = true;
			d[cL.x][cL.y] = d[u.x][u.y] + 1;
			p[cL.x][cL.y] = u;
			Q.insert(cL,numPixels);
			count++;
		}
	} //end-while
	
	if (visited[t.x][t.y])
	{	
		coord temp = t;
		while (temp.x != s.x && temp.y != s.y)
		{
			O(temp.x, temp.y)->Red = 255;
			O(temp.x, temp.y)->Blue = 0;
			O(temp.x, temp.y)->Green = 0;
			temp = p[temp.x][temp.y];
		}
		O.WriteToFile("output.bmp");
		cout<<endl<< "distance: "<<d[t.x][t.y]<<endl <<"count: "<< count<<endl;
	}
	else
		cout<< "no path from s to t. ";
}

int main() {
	//string Mazename;
	//cout << "Enter the name of your maze: ";
	//getline(cin,Mazename);
	BMP inputMaze;
	inputMaze.ReadFromFile("maze2.bmp");
	BMP outputMaze;
	outputMaze.SetSize(inputMaze.TellWidth(), inputMaze.TellHeight());
	outputMaze.ReadFromFile("maze2.bmp");
	outputMaze.SetBitDepth(24);
	int sx, sy, fx, fy;
	cout << "Enter the starting coordinate point with only a space inbetween the values: ";
	cin >> sx >> sy;
	coord start;
	start.x = sx;
	start.y = sy;
	cout << endl << "Enter the desination coordinate point with only a space inbetween the values: ";
	cin >> fx >> fy;	
	coord finish;
	finish.x = fx;
	finish.y = fy;

	bool error = false;
	// Check if start coord is out of picture
	if (start.x > inputMaze.TellWidth() && start.y > inputMaze.TellHeight())
	{
		cout << "starting coordinate point is out of range" << endl;
		error = true;
	}
	// Check if finish coord is out of picture
	if (finish.x > inputMaze.TellWidth() && finish.y > inputMaze.TellHeight())
	{
		cout << "finish coordinate point is out of range" << endl;
		error = true;
	}
	// Check if start coord is on a wall
	if (isBlack(inputMaze, start)
	{
		cout << "Invalid start coordinate point, on maze wall." << endl;
		error = true;
	}
	// Check if finish coord is on a wall
	if (isBlack(inputMaze, finish))
	{
		cout << "Invalid finish coordinate point, on maze wall." << endl;
		error = true;
	}

	if (error != true) 
	{	cout<<"Processing..."<<endl;
		clock_t cl = clock();
		BFS(inputMaze, outputMaze, start, finish, 0 );
		cl=clock() - cl;
		cout<< "Duration: "<<cl/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
		cout<<"Completed!"<<endl;
	}
//	system("PAUSE"); 
	return 0;
}
