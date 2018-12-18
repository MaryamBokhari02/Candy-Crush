
Conversation opened. 5 messages. All messages read.


Skip to content
Using Gmail with screen readers
You’re running low on storage space. Try freeing up space or purchase additional storage.
candy crush 

3 of 9
PROJECT SUBMISSION LOCKED
Inbox
x

Maryam Bokhari <mbokhari786@gmail.com>
Attachments
Thu, Dec 8, 2016, 1:27 PM
to Rafia, atique.rehman

Respected Sir/Madam,
I uploaded my project at 3 pm on slate and later I did some edits. When I opened slate again it had locked my submission. Is there any way you can re open it. I thought there was an infinite amount of resubmissions allowed then why is this happening. 
I have attached a document of my final code. 

Please provide me with a solution.


Maryam Bokhari- i160050 
Section E 
FAST- NU 
Candy -crush project

Attachments area

Maryam Bokhari <mbokhari786@gmail.com>
Attachments
Sun, Apr 23, 2017, 2:44 AM
to Fam

Oyee... Here's the code XD 

Attachments area

Fam W <fati.wasim@gmail.com>
Attachments
Mon, May 1, 2017, 2:32 PM
to me


Attachments area

Maryam Bokhari <mbokhari786@gmail.com>
Mon, May 1, 2017, 2:53 PM
to Fam

bro submit kera doo 


	Virus-free. www.avast.com


Fam W <fati.wasim@gmail.com>
Mon, May 1, 2017, 3:02 PM
to me

Kar deee


//============================================================================
// Name        : cookie-crush.cpp
// Author      : Maryam Bokhari
// Copyright   : (c) Reserved
// Description : Basic 2D game of Cookie  Crush...
//============================================================================
#ifndef COOKIE_CRUSH_CPP
#define COOKIE_CRUSH_CPP

//#include <GL/gl.h>
//#include <GL/glut.h>
#include <iostream>
#include<string>
#include<cmath>
#include<fstream>
#include "util.h"
#include<unistd.h>
using namespace std;
#define MAX(A,B) ((A) > (B) ? (A):(B)) // defining single line functions....
#define MIN(A,B) ((A) < (B) ? (A):(B))
#define ABS(A) ((A) < (0) ? -(A):(A))
#define FPS 10

#define KEY_ESC 27 // A

// 20,30,30
const int bradius = 30; // Cookie radius in pixels...

int width = 930, height = 660; // i have set my window size to be 800 x 600
int dball = 0; // difference between cookies center of 0 pixels
int byoffset = bradius + dball; // 2 * bradius + dball; // board yoffset
int Array[10][15]={{0}};
int clickx,clicky; 
int score = 0;
int setcolor, psetcolor;
int timerdisplay=120; 

enum GameState { // Use to check different states of game...
	Ready, Shot, Over, RemoveCluster
};
GameState gamestate = Ready;

const int ncookies = 6;
enum Cookies {
	CK_BISCUIT, CK_BURGER, CK_CROISSONT, CK_CUPCAKE, CK_DONUT, CK_STAR
};
GLuint texture[ncookies];
GLuint tid[ncookies];
string tnames[] = { "biscuit.png", "burger.png", "croissont.png", "cupcake.png",
		"donut.png", "star.png" };
GLuint mtid[ncookies];
int cwidth = 60, cheight = 60; // 60x60 pixels cookies width & height...

void RegisterTextures()
/*Function is used to load the textures from the files and display*/
// Please do not change it...
{
	// allocate a texture name
	glGenTextures(ncookies, tid);

	vector<unsigned char> data;
	ifstream ifile("image-data.bin", ios::binary | ios::in);
	if (!ifile) {
		cout << " Couldn't Read the Image Data file ";
		exit(-1);
	}
	// now load each cookies data...
	int length;
	ifile.read((char*) &length, sizeof(int));
	data.resize(length, 0);
	for (int i = 0; i < ncookies; ++i) {

		// Read current cookie

		ifile.read((char*) &data[0], sizeof(char) * length);

		mtid[i] = tid[i];
		// select our current texture
		glBindTexture( GL_TEXTURE_2D, tid[i]);

		// select modulate to mix texture with color for shading
		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		// when texture area is small, bilinear filter the closest MIP map
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_NEAREST);
		// when texture area is large, bilinear filter the first MIP map
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// if wrap is true, the texture wraps over at the edges (repeat)
		//       ... false, the texture ends at the edges (clamp)
		bool wrap = true;
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
				wrap ? GL_REPEAT : GL_CLAMP);
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
				wrap ? GL_REPEAT : GL_CLAMP);

		// build our texture MIP maps
		gluBuild2DMipmaps( GL_TEXTURE_2D, 3, cwidth, cheight, GL_RGB,
		GL_UNSIGNED_BYTE, &data[0]);
	}
	ifile.close();
}
void DrawCookie(const Cookies &cname, int sx, int sy, int cwidth = 60,
		int cheight = 60)
		/*Draws a specfic cookie at given position coordinate
		 * sx = position of x-axis from left-bottom
		 * sy = position of y-axis from left-bottom
		 * cwidth= width of displayed cookie in pixels
		 * cheight= height of displayed cookiei pixels.
		 * */
		{
	float fwidth = (float) cwidth / width * 2, fheight = (float) cheight
			/ height * 2;
	float fx = (float) sx / width * 2 - 1, fy = (float) sy / height * 2 - 1;

	glPushMatrix();
	glEnable( GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, mtid[cname]);
//	glTranslatef(0, 0, 0);
//	glRotatef(-M_PI / 2, 0, 0, 1);
	glBegin( GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex2d(fx, fy);
	glTexCoord2d(1.0, 0.0);
	glVertex2d(fx + fwidth, fy);
	glTexCoord2d(1.0, 1.0);
	glVertex2d(fx + fwidth, fy + fheight);
	glTexCoord2d(0.0, 1.0);
	glVertex2d(fx, fy + fheight);
	glEnd();

	glColor4f(1, 1, 1, 1);

//	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//glutSwapBuffers();
}

float Distance(float x1, float y1, float x2, float y2) {
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}
int Random()
{
  int x;
x=rand()%6;  
return x; 

}
void Pixels2Cell(int px, int py, int & cx, int &cy)
{  cx=(px-10)/60;
   cy=(py-10)/60;


}
void Cell2Pixels(int cx, int cy, int & px, int &py)
{  px=(cx*60)+10;
   py=(cy*60)+10;	
}
void GetCookie(int Array[10][15])
{    	
 int xx,yy; 
 for( int i=0;i<10;i++)
	{ int j;
	for(j=0;j<15;j++)
	 {	Cell2Pixels(j,i,xx,yy);
           { if(Array[i][j]==0)
	     { DrawCookie(Cookies(0),xx,yy,cwidth,cheight);  }
           else if(Array[i][j]==1)
	     { DrawCookie(Cookies(1),xx,yy,cwidth,cheight); }
	   else if(Array[i][j]==2)
	     { DrawCookie(Cookies(2),xx,yy,cwidth,cheight); }
	   else if(Array[i][j]==3)
	     { DrawCookie(Cookies(3),xx,yy,cwidth,cheight); }
	   else if(Array[i][j]==4)
	     { DrawCookie(Cookies(4),xx,yy,cwidth,cheight); }
	   else if(Array[i][j]==5)
	     { DrawCookie(Cookies(5),xx,yy,cwidth,cheight); } 
           }
	}
	}

}

void autofalling(int Array[10][15])
{
  for(int i=9;i>=0;i--)
  {  int j;
     for(j=0;j<15;j++)
       { 
	if(Array[i][j]==8)
	{ for(int fill=i;fill<9;fill++)
            {int temp = Array[fill][j]; 
             Array[fill][j] = Array[fill+1][j];
             Array[fill+1][j] = temp;
	    }
        }
       }
  }
}

void autofillingafterfalling(int Ck[10][15])
{ 
  for(int row=0;row<10;row++)
  {  int col;
     for(col=0;col<15;col++)
   { 
	if(Ck[row][col]==8)
       {      
	int Autofilled=Random();
        Ck[row][col]=Autofilled;   
       }
   }
  }
	

}


int autocrushing(int Arr[10][15])
{   int swapscore=0;

/*cout << endl << "array before auto crsushing" << endl;
	for(int i=0; i<10;i++)
          { for(int j=0;j<15;j++)
          { cout<<Array[i][j]<<" "; }
	cout<<endl;}  */
//creating a temporary array which is a copy of all the elements in the arugument array 
	int temparray[10][15]; 
	for(int x=0;x<10;x++)
	 { for(int y=0;y<15;y++)
	{  
	  temparray[x][y]=Arr[x][y];
	}
	}


 //Comparison by rows and columns 
 {for(int row=0;row<10;row++)
   for(int col=0;col<15;col++) 
   { 
	int currentvalue = Arr[row][col];
	int valuesToCrushInRows = 0;
	int valuesToCrushInColumns = 0;
	 //condition for columns	
	for (int j=col;j<15;j++)
	{
		if (currentvalue == Arr[row][j])
		{	valuesToCrushInColumns++;  }
		else
		{       break;	}
	}

	// Crush if greater than 2
	if (valuesToCrushInColumns > 2)
	{  for (int x=0;x<valuesToCrushInColumns;x++)
		{ //cout  << endl<< "crushing rox/col:" << row << "/" << (x+col) << "cuz x:" << x << "and current value:" << currentvalue << endl;
			temparray[row][x+col]=8;
			//swapscore++; 
		}
	}
	 //condition for rows
	for (int k=row;k<10;k++)
	{  if (currentvalue == Arr[k][col])
		{  valuesToCrushInRows++;  }
		else
		{  break;  }
	}

	// Crush if greater than 2
	if (valuesToCrushInRows > 2)
	{  for (int x=0;x<valuesToCrushInRows;x++)
		{ //cout  << endl<< "crushing rox/col:" << (row+x) << "/" << col << "cuz x:" << x << "and current value:" << currentvalue << endl;
			temparray[row+x][col]=8;
			//swapscore++;
		}
	}   
    } 
	//Copying all the elements of temp. array into the argument array to insure all the combinations in cross work as well 
	for(int i=0;i<10;i++)
	 { for(int j=0;j<15;j++)
		{  
	  	Arr[i][j]=temparray[i][j];
		if(Arr[i][j]==8)
		{ swapscore++;
		}
		}
	 }
 return swapscore; 
	      
}
    
/*cout << endl << "array after auto crsushing" << endl;
	for(int i=0; i<10;i++)
          { for(int j=0;j<15;j++)
          { cout<<Array[i][j]<<" "; } 
	cout<<endl;}  */                        
}  

void mainstart(int Array[10][15])
{ 
cout<<"Randomly Generated Array"<<endl;  
  int rd,n; 
   for(n=0;n<10;n++)
    { 	int m;
	for (m=0;m<15;m++)
	{rd=Random();      
	Array[n][m]=rd;
	cout<<Array[n][m]<<" ";
	}    
	cout<<endl;     
    }
}



void DisplayFunction() {
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim red and 1 means pure red and so on.
//#if 0
	glClearColor(0.7/*Red Component*/, 0.9/*Green Component*/,
			1.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT); //Update the colors

// #----------------- Write your code here ----------------------------#
	//write your drawing commands here or call your drawing functions...

	// draw cookies..;
	GetCookie(Array);
	// Pass time so we can see the Random Cookies first Generated   	

	
	//AutoCrushing random generated cookies
   	autocrushing(Array);
	cout<<endl;
	// Pass time so we can see the AutoCrushing Effects  	
       
	cout<<"AutoCrushing Array"<<endl; 
	for(int i=0; i<10;i++)
          { for(int j=0;j<15;j++)
             { 	
		cout<<Array[i][j]<<" "; 
	     }
        	cout<<endl;
	  } 
	cout<<endl;
	//glutPostRedisplay();
	//AutoFalling  
	autofalling(Array);
	//Check Array 
	cout<<"AutoFalling Array"<<endl; 
	for(int i=0; i<10;i++)
          { for(int j=0;j<15;j++)
             { 	
		cout<<Array[i][j]<<" "; 
	     }
        	cout<<endl;
	  } 
	cout<<endl;
	autofillingafterfalling(Array);
	cout<<"AutoFillingAfter Array"<<endl; 
	for(int i=0; i<10;i++)
          { for(int j=0;j<15;j++)
             { 	
		cout<<Array[i][j]<<" "; 
	     }
        	cout<<endl;
	  } 
	cout<<endl;
	//When timer runs out completely 
	if(timerdisplay>0)
	{  DrawString(width / 2 - 20, height - 20, width, height,
			"Score " + Num2Str(score), colors[BLUE_VIOLET]);
	
	   DrawString(20, height - 20, width, height,
			"Timer " + Num2Str(timerdisplay), colors[BLUE_VIOLET]);
	}
	else
	{
	
	for(int i=0; i<10;i++)
          { for(int j=0;j<15;j++)
             { 	
		Array[i][j]=100; 
	     }
	  } 
	DrawString(width / 2 - 80, height-330 , width, height,
			"GAME OVER", colors[BLUE_VIOLET]);
	DrawString(width / 2 - 100, height-630, width, height,
			"Press Escape to exit", colors[GOLD]);
	DrawString(width / 2 - 100, height - 60, width, height,
			"FINAL SCORE:" + Num2Str(score), colors[ORANGE]);
	}

	//DrawString(width / 2 - 20, height - 20, width, height,"Score " + Num2Str(score), colors[BLUE_VIOLET]);
	
	//DrawString(20, height - 20, width, height,"Timer " + Num2Str(timerdisplay), colors[BLUE_VIOLET]);

// #----------------- Write your code till here ----------------------------#
	// do not modify below this
	glutSwapBuffers(); // do not modify this line..

}
/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
width=930; 
    height=660; 	

/*glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.*/
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	int cellx,celly;          
	Pixels2Cell(y,x,cellx,celly);
	if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...
	} else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {

	} else if (key == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
	} else if (key == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/
	/*
	 glutPostRedisplay();
	 */
}
/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
 

void swapping(int movedx,int movedy)
{      
       cout<<"Random numbers corresponding to both cells"<<endl;
       cout<<Array[clickx][clicky]<<","<<Array[movedx][movedy]<<endl;   
	//swapping function 
	  int temp=Array[clickx][clicky]; 
	  Array[clickx][clicky]=Array[movedx][movedy];
	  Array[movedx][movedy]=temp;
	  cout<<"Randomly swapped numbers corresponding to both cells"<<endl;
	  cout<<Array[clickx][clicky]<<","<<Array[movedx][movedy]<<endl;
	//minimun 3 combinations exist At any Direction 
         cout<<"Swapped Array:"<<endl;
	 int before[10][15];
	  for(int i=0;i<10;i++)
	   { for(int j=0;j<15;j++)
	    { before[i][j]=Array[i][j]; 
		cout<<before[i][j]<<" ";
		 
	    }
		cout<<endl;
	   }
	int swappingscore=autocrushing(Array);
	//bool answer=comparingArrays(before,Array);
	cout<<"Swapped Autocrushed Array:"<<endl;
	  for(int i=0;i<10;i++)
	   { for(int j=0;j<15;j++)
	    { 
		cout<<Array[i][j]<<" ";
		 
	    }
		cout<<endl;
	   }
	score=score+swappingscore;
	cout<<"Current Score"<<score<<endl; 
	if(swappingscore==0)
	{	

		DisplayFunction();
		//usleep(1*1000*1000*5);
		
	
		
		int temp1=Array[movedx][movedy];
		Array[movedx][movedy]=Array[clickx][clicky];
	        Array[clickx][clicky]=temp1;

		DisplayFunction();
		//usleep(1*1000*1000*5);

		cout<<"Swapping was not successful:swap back"<<endl;
		 int before[10][15];
		  for(int i=0;i<10;i++)
		   { for(int j=0;j<15;j++)
		    { before[i][j]=Array[i][j]; 
			cout<<before[i][j]<<" ";
			 
		    }
			cout<<endl;
		   }

	}
	  




}



void MouseMoved(int x, int y) {
	cout << "Current Mouse Coordinates X=" << x << " Y= " << height - y << endl;
	
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */

void MouseClicked(int button, int state, int x, int y) 
{
  int movedx,movedy; 
	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
	{

		if (state == GLUT_DOWN && gamestate == Ready) {
			cout << "Left Mouse Button PRESSED at Coordinates X=" << x << " Y= "
					<< height - y << endl;
		        Pixels2Cell(height-y,x,clickx,clicky);
			cout<<clickx<<"  "<<clicky<<endl;
			
		}
		if (state == GLUT_UP && gamestate == Ready) {
		  cout << "Left Mouse Button RELEASED at Coordinates X=" << x << " Y= "
					<< height - y << endl;
			Pixels2Cell(height-y,x,movedx,movedy);
			cout<<movedx<<"  "<<movedy<<endl;
			cout<<clickx<<","<<clicky<<"   "<<movedx<<","<<movedy<<" "<<endl;
				//moved to the right 
			    if( clickx==movedx && clicky==(movedy+1))
			     {    cout<<"Moved right";
				swapping(movedx,movedy); 
			     }

				//MOVED TO THE LEFT
			    else if(clickx==movedx && clicky==(movedy-1))
			    { 	cout<<"Moved left";  
				swapping(movedx,movedy);
			    }
				//moved up one space
			    

			    else if(clickx==(movedx+1) && clicky==(movedy))
			    { 	cout<<"Moved up";
				swapping(movedx,movedy); 
			    }
				//moved down one space 

			    else if(clickx==(movedx-1) && clicky==(movedy))
			    { 	cout<<"Moved down";
				swapping(movedx,movedy); 
			    }
			    else
			    {
				cout<<"wrong swapping:Moused moved to unacceptable location";  
			    } 
		}
	//cout<<cellx<<celly<<movedx<<movedy; 
	//MouseDirection(cellx,celly,movedx,movedy);
 
	else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
	{

	}    
	}
	glutPostRedisplay();
}
/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == KEY_ESC/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}
}

/*
 * This function is called after every 1000.0 milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
float dt = 0, lastframe = 0;
void Timer(int m) {
	dt = (m - lastframe) / 1000.0;
	lastframe = m;

	// dt is time elapsed between two frames..
	glutPostRedisplay();
	timerdisplay--; 


	// implement your functionality here

	glutTimerFunc(1000, Timer, m + 1);
}
/*
 * our gateway main function
 * */

int main(int argc, char*argv[]) {
	InitRandomizer(); // seed the random number generator...
	//Write your code here for filling the canvas with different Cookies. You can use the GetCookie function for getting the random shaped cookies

	
	mainstart(Array);

	glutInit(&argc, argv); // initialize the graphics library...

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("COOKIE CRUSH"); // set the title of our game window
	SetCanvasSize(930, 660); // set the number of pixels...
	// Load the textures from the file..;
	RegisterTextures();
	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.

	glutDisplayFunc(DisplayFunction); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	glutMouseFunc(MouseClicked);

//// This function tells the library to call our Timer function after 1000.0 milliseconds...
	if (timerdisplay>=0)
	{  glutTimerFunc(1000, Timer, 0);
	}
//// now handle the control to library and it will call our registered functions when
//// it deems necessary...

	glutMainLoop();

	return 1;
}
#endif /* */
candy-crush.cpp
Displaying candy-crush.cpp.
