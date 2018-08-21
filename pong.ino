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
int speed = 1;
bool ballRight = true;
bool ballDown = true;

int paddleWidth = 4;
int paddleHeight = 12;
int playerX = 1 + border;
int playerY = 2;
int distanceFromWall = 1;

int computerX = WIDTH - (border + paddleWidth + distanceFromWall);
int computerY = 2;

int playerScore = 0;
int computerScore = 0;

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

		//ball
		arduboy.fillCircle(ballX, ballY, ballRadius, WHITE);
		if (ballRight == true)
		{
			ballX = ballX + speed;
		} else
		{
			ballX = ballX - speed;
		}

		if (ballDown == true)
		{
			ballY = ballY + speed;
		} else
		{
			ballY = ballY - speed;
		}

		if(ballX == border + distanceFromWall + playerX + paddleWidth && playerY < ballY + ballRadius && playerY + paddleHeight > ballY)
		{
			ballRight = true;
		}
		if(ballX == WIDTH - ballRadius - border - distanceFromWall - paddleWidth && computerY < ballY + ballRadius && computerY + paddleHeight > ballY)
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

		//score and gamestate change
		if(ballX < -20)
		{
			ballX = WIDTH / 2;
			computerScore++;
		}
		if(ballX > 130)
		{
			ballX = WIDTH / 2;
			playerScore++;
		}
		if(playerScore == 5)
		{
			gamestate = 2;
		}
		if(computerScore == 5)
		{
			gamestate = 3;
		}

		arduboy.setCursor(WIDTH / 4, 2);
		arduboy.print(playerScore);
		arduboy.setCursor((WIDTH * 3 / 4), 2);
		arduboy.print(computerScore);

		//player
		arduboy.fillRect(playerX, playerY, paddleWidth, paddleHeight, WHITE);
		if(arduboy.pressed(UP_BUTTON) && playerY > 0 + border)
		{
			playerY = playerY - speed;

		}
		if(arduboy.pressed(DOWN_BUTTON) && playerY < (HEIGHT - (paddleHeight + border)))
		{
			playerY = playerY + speed;
		}

		if (arduboy.pressed(A_BUTTON) == true && aFresh == true)
		{
			aFresh = false;
			gamestate = 2;
		}

		//computer
		arduboy.fillRect(computerX, computerY, paddleWidth, paddleHeight, WHITE);
		if (ballX > 115 || rand() % 20 == 1)
		{
			if (ballY < computerY + (paddleHeight / 2) && computerY > 0 + border)
			{
				computerY = computerY - speed;
			}
			if (ballY > computerY + (paddleHeight / 2) && computerY < (HEIGHT - (paddleHeight + border)))
			{
				computerY = computerY + speed;
			}
		}

		break;
	case 2:
		arduboy.setCursor(WIDTH / 4, 2);
		arduboy.print(playerScore);
		arduboy.setCursor((WIDTH * 3 / 4), 2);
		arduboy.print(computerScore);
		arduboy.setCursor(WIDTH / 2 - 15, HEIGHT / 2);
		arduboy.print("YOU WON!");
		if (arduboy.pressed(A_BUTTON) == true && aFresh == true)
		{
			aFresh = false;
			gamestate = 0;
			ballX = WIDTH / 2;
			playerScore = 0;
			computerScore = 0;
		}
		break;
	case 3:
		arduboy.setCursor(WIDTH / 4, 2);
		arduboy.print(playerScore);
		arduboy.setCursor((WIDTH * 3 / 4), 2);
		arduboy.print(computerScore);
		arduboy.setCursor(WIDTH / 2 - 15, HEIGHT / 2);
		arduboy.print("YOU LOST");
		if (arduboy.pressed(A_BUTTON) == true && aFresh == true)
		{
			aFresh = false;
			gamestate = 0;
			ballX = WIDTH / 2;
			playerScore = 0;
			computerScore = 0;
		}
		break;
	}
	if (arduboy.notPressed(A_BUTTON) == true)
	{
		aFresh = true;
	}

	arduboy.display();
}
