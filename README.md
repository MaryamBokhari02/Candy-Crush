# Candy-Crush
----------------------
PROJECT DESCRIIPTION:
----------------------
Candy Crush is a two-dimension game with a GUI which features crushing of candies when a matching pattern of three or more candies is made. The game has six different cookies that randomly appear on the screen at the beginning of execution. The user has 90 seconds to play the game. The timer counts down and score is kept on the number of combinations made. The user has the functionality to swap two candies. The swap can only be made with a cookie adjacent to you. A row swap can shift the cookie to the right or the left while a coloumn swap results in shift with the top or bottom. After the swap has been made, each row and column is scanned for a match. If the same cookies appear more than three times in a row or a column, the cookies burst and the top cookies fall to fill in the space. The missing cookies on the top are replaced by random cookies.   

---------------------
FILES DESCRIPTION 
---------------------
The candy-crush.cpp provides the code for the drawing of the random candies, auto-crushing of candies when a combination is made, as well as auto-falling of candies from top to bottom when candies are crushed. 
The following files are images of candies :biscuit.png, burger.png, cupcake.png, croissont.png, donut.png, star.png  
The file Board.cpp contains the making of the two dimensional board. 
The file util.cpp contains the different functions that provide the graphical shapes. It also contains functions to introduce color library.

---------------------------------
INTRUCTIONS TO EXECUTION PROJECT:
---------------------------------
The project was created on Linux operating system. To execute the game, the following steps must be followed.
1) Download the files that are provided. 
2) Open Linux command line and change directory to the folder where the code is placed. 
3) Write the following command: Makefile candy-crush.o 
4) Followed by this command: ./candy-crush

-------------
CONTRIBUTION: 
-------------
The functionality of the game was implemented by Maryam Bokhari. The graphics of the utilities were provided by Dr.Sib-tul-Hassan. 
