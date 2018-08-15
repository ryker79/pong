// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       pong.ino
    Created:	8/15/2018 7:03:25 AM
    Author:     Alan Ryker
*/

// Define User Types below here or use a .h file
//
#include <Arduboy.h>
Arduboy arduboy;
int gamestate = 0;
bool a_fresh = true;


// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//

// The setup() function runs once each time the micro-controller starts
void setup()
{
	arduboy.begin();
	srand(7 / 8);
	arduboy.setFrameRate(60);

	arduboy.clear();
}

// Add the main program code into the continuous loop() function
void loop()
{
	if(!arduboy.nextFrame())
	{
		return;
	}
	arduboy.clear();
	switch(gamestate)
	{
	case 0:
		arduboy.setCursor(0, 0);
		arduboy.print("Title Screen");
		if (arduboy.pressed(A_BUTTON) == true && a_fresh == true)
		{
			a_fresh = false;
			gamestate = 1;
		}
		break;
	case 1:
		arduboy.setCursor(0, 0);
		arduboy.print("Gameplay");
		if (arduboy.pressed(A_BUTTON) == true && a_fresh == true)
		{
			a_fresh = false;
			gamestate = 2;
		}
		break;
	case 2:
		arduboy.setCursor(0, 0);
		arduboy.print("Win Screen");
		if (arduboy.pressed(A_BUTTON) == true && a_fresh == true)
		{
			a_fresh = false;
			gamestate = 3;
		}
		break;
	case 3:
		arduboy.setCursor(0, 0);
		arduboy.print("Game Over Screen");
		if (arduboy.pressed(A_BUTTON) == true && a_fresh == true)
		{
			a_fresh = false;
			gamestate = 1;
		}
		break;
	}
	if (arduboy.notPressed(A_BUTTON) == true)
	{
		a_fresh = true;
	}

	arduboy.display();
}
