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

//variables
int gamestate = 0;
bool aFresh = true;
int border = 1;

int ballX = 3;
int ballY = 3;
int ballRadius = 2;
int ballDiameter = 4;
int ballSpeed = 1;
bool ballRight = true;
bool ballDown = true;

int paddleWidth = 4;
int paddleHeight = 9;
int playerSpeed = 1;
int playerX = 2;
int playerY = 0;

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
	//Prevent the Arduboy from running too fast
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
		if (arduboy.pressed(A_BUTTON) == true && aFresh == true)
		{
			aFresh = false;
			gamestate = 1;
		}
		break;
	case 1: //Gameplay
		arduboy.drawRect(0, 0, WIDTH, HEIGHT, WHITE);
		arduboy.fillCircle(ballX, ballY, ballRadius, WHITE);
		if (ballRight == true)
		{
			ballX = ballX + ballSpeed;
		} else
		{
			ballX = ballX - ballSpeed;
		}

		if (ballDown == true)
		{
			ballY = ballY + ballSpeed;
		} else
		{
			ballY = ballY - ballSpeed;
		}

		if(ballX == ballRadius + border)
		{
			ballRight = true;
		}
		if(ballX == WIDTH - ballRadius - border)
		{
			ballRight = false;
		}
		if(ballY == ballRadius + border)
		{
			ballDown = true;
		}
		if(ballY == HEIGHT - ballRadius - border)
		{
			ballDown = false;
		}

		arduboy.fillRect(playerX, playerY, paddleWidth, paddleHeight, WHITE);
		if(arduboy.pressed(UP_BUTTON) && playerY > 0 + border)
		{
			playerY = playerY - playerSpeed;

		}
		if(arduboy.pressed(DOWN_BUTTON) && playerY < (HEIGHT - (paddleHeight + border)))
		{
			playerY = playerY + playerSpeed;
		}

		if (arduboy.pressed(A_BUTTON) == true && aFresh == true)
		{
			aFresh = false;
			gamestate = 2;
		}
		break;
	case 2:
		arduboy.setCursor(0, 0);
		arduboy.print("Win Screen");
		if (arduboy.pressed(A_BUTTON) == true && aFresh == true)
		{
			aFresh = false;
			gamestate = 3;
		}
		break;
	case 3:
		arduboy.setCursor(0, 0);
		arduboy.print("Game Over Screen");
		if (arduboy.pressed(A_BUTTON) == true && aFresh == true)
		{
			aFresh = false;
			gamestate = 0;
		}
		break;
	}
	if (arduboy.notPressed(A_BUTTON) == true)
	{
		aFresh = true;
	}

	arduboy.display();
}
