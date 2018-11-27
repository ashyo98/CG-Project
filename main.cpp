#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <time.h>
#include <string.h>
#include <glut.h>

int matrix[9][9]; //this matrix stores the x and o and blank box of the game, a value of 0 is blank, 1 is x and 2 is o
int playerturn; //playerturn if it is 1 then 1st players turn else if it is 2 then its second players turn
int result; //result of the game if it is 0 then draw if it is 1 then player 1 wins if it is 2 then player 2 wins
bool gameover = false; //gameover if it is 0 then its not game over else if it is 1 then its game over
int submatrix[3][3]; // to verify the next selection is happening in the correct submatrix
int finalmatrix[3][3]; // stores the wins in each submatrix
int first; // to allow the selection in any submatrix


void initgame()
{
	playerturn = 1; //x starts first
	first = 1;
	for (int i = 0; i < 9; i++) 
		for (int j = 0; j < 9; j++)
			matrix[i][j] = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			submatrix[i][j] = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			finalmatrix[i][j] = 0;
}

//This function is used to draw the 4 lines 2 vertical and 2 horizontal
void drawlines()
{
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	//2 vertical lines
	for (int i = 0;i < 3;i++)
	{
		glVertex2f(100 + i, 50);
		glVertex2f(100 + i, 350);
		glVertex2f(200 + i, 350);
		glVertex2f(200 + i, 50);
	}

	//2 horizontal lines
	for (int i = 0;i < 3;i++)
	{
		glVertex2f(0, 150 + i);
		glVertex2f(300, 150 + i);
		glVertex2f(0, 250 + i);
		glVertex2f(300, 250 + i);
	}

	//top left corner 
	glVertex2f(35, 55);
	glVertex2f(35, 145);
	glVertex2f(65, 55);
	glVertex2f(65, 145);
	glVertex2f(5, 85);
	glVertex2f(95, 85);
	glVertex2f(5, 115);
	glVertex2f(95, 115);

	//top middle 
	glVertex2f(135, 55);
	glVertex2f(135, 145);
	glVertex2f(165, 55);
	glVertex2f(165, 145);
	glVertex2f(105, 85);
	glVertex2f(195, 85);
	glVertex2f(105, 115);
	glVertex2f(195, 115);

	//top right corner
	glVertex2f(235, 55);
	glVertex2f(235, 145);
	glVertex2f(265, 55);
	glVertex2f(265, 145);
	glVertex2f(205, 85);
	glVertex2f(295, 85);
	glVertex2f(205, 115);
	glVertex2f(295, 115);

	//middle left
	glVertex2f(35, 155);
	glVertex2f(35, 245);
	glVertex2f(65, 155);
	glVertex2f(65, 245);
	glVertex2f(5, 185);
	glVertex2f(95, 185);
	glVertex2f(5, 215);
	glVertex2f(95, 215);

	// middle middle
	glVertex2f(135, 155);
	glVertex2f(135, 245);
	glVertex2f(165, 155);
	glVertex2f(165, 245);
	glVertex2f(105, 185);
	glVertex2f(195, 185);
	glVertex2f(105, 215);
	glVertex2f(195, 215);

	//middle right
	glVertex2f(235, 155);
	glVertex2f(235, 245);
	glVertex2f(265, 155);
	glVertex2f(265, 245);
	glVertex2f(205, 185);
	glVertex2f(295, 185);
	glVertex2f(205, 215);
	glVertex2f(295, 215);

	//bottom left corner
	glVertex2f(35, 255);
	glVertex2f(35, 345);
	glVertex2f(65, 255);
	glVertex2f(65, 345);
	glVertex2f(5, 285);
	glVertex2f(95, 285);
	glVertex2f(5, 315);
	glVertex2f(95, 315);

	//bottom middle
	glVertex2f(135, 255);
	glVertex2f(135, 345);
	glVertex2f(165, 255);
	glVertex2f(165, 345);
	glVertex2f(105, 285);
	glVertex2f(195, 285);
	glVertex2f(105, 315);
	glVertex2f(195, 315);

	//bottom right corner
	glVertex2f(235, 255);
	glVertex2f(235, 345);
	glVertex2f(265, 255);
	glVertex2f(265, 345);
	glVertex2f(205, 285);
	glVertex2f(295, 285);
	glVertex2f(205, 315);
	glVertex2f(295, 315);

	glEnd();
}

//Used to write text in the opengl window
void drawString(void * font, char *s, float x, float y) {
	unsigned int i;
	glRasterPos2f(x, y);
	for (i = 0; i < strlen(s); i++)
		glutBitmapCharacter(font, s[i]);
}

//this function is called when keyboard button is pressed 
void KeyPress(unsigned char key, int x, int y) {
	switch (key) {
	case 'y':
		if (gameover == true)
		{
			gameover = false;
			initgame();
		}
		break;
	case 'n':
		if (gameover == true)
			exit(0);
		break;
	case 27:
		exit(0);

	}
}

//This function is called when the mouse button is pressed and this function puts the x or o on the blank box 
void click(int button, int state, int x, int y)
{
	cout << endl << "x = " << x << " y = " << y << " first = " << first << endl << endl;
	for (int i = 0;i < 3;i++)
	{
		for (int j = 0;j < 3;j++)
			cout << submatrix[i][j] << " ";
		cout << endl;
	}
	if (first && gameover == false && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		first = 0;
		if (playerturn == 1 && matrix[(y - 50) / 35][x / 35] == 0)
		{
			matrix[(y - 50) / 35][x / 35] = 1;
			playerturn = 2;
			submatrix[((y - 50) / 35) % 3][(x / 35) % 3] = 1;
		}
		else if (playerturn == 2 && matrix[(y - 50) / 35][x / 35] == 0)
		{
			matrix[(y - 50) / 35][x / 35] = 2;
			playerturn = 1;
			submatrix[((y - 50) / 35) % 3][(x / 35) % 3] = 1;
		}
		else
			first = 1;
	}
	else
	{
		if (gameover == false && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if (playerturn == 1)
			{
				if (matrix[(y - 50) / 35][x / 35] == 0 && submatrix[((y - 50) / 35) / 3][(x / 35) / 3] == 1)
				{
					matrix[(y - 50) / 35][x / 35] = 1;
					submatrix[((y - 50) / 35) / 3][(x / 35) / 3] = 0;
					if (submatrix[((y - 50) / 35) % 3][(x / 35) % 3] == 2)
						first = 1;
					//else
					    submatrix[((y - 50) / 35) % 3][(x / 35) % 3] = 1;
					playerturn = 2;
				}
			}
			else
			{
				if (matrix[(y - 50) / 35][x / 35] == 0 && submatrix[((y - 50) / 35) / 3][(x / 35) / 3] == 1)
				{
					matrix[(y - 50) / 35][x / 35] = 2;
					submatrix[((y - 50) / 35) / 3][(x / 35) / 3] = 0;
					if (submatrix[((y - 50) / 35) % 3][(x / 35) % 3] == 2)
						first = 1;
					//else
					    submatrix[((y - 50) / 35) % 3][(x / 35) % 3] = 1;
					playerturn = 1;
				}
			}
		}
	}
}

//This Function Draw the x and o's
void drawxo()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (matrix[i][j] == 1) //if it is 1 then draw x 
			{
				glBegin(GL_LINES);
				glVertex2f(20 + j * 30 - 10 + (j / 3) * 10, 70 + i * 30 - 10 + (i / 3) * 10);
				glVertex2f(20 + j * 30 + 10 + (j / 3) * 10, 70 + i * 30 + 10 + (i / 3) * 10);
				glVertex2f(20 + j * 30 - 10 + (j / 3) * 10, 70 + i * 30 + 10 + (i / 3) * 10);
				glVertex2f(20 + j * 30 + 10 + (j / 3) * 10, 70 + i * 30 - 10 + (i / 3) * 10);
				glEnd();
			}
			else if (matrix[i][j] == 2) //if it is 2 then draw o
			{
				glBegin(GL_LINE_LOOP);
				glVertex2f(20 + j * 30 - 10 + (j / 3) * 10, 70 + i * 30 - 10 + (i / 3) * 10);
				glVertex2f(20 + j * 30 + 10 + (j / 3) * 10, 70 + i * 30 - 10 + (i / 3) * 10);
				glVertex2f(20 + j * 30 + 10 + (j / 3) * 10, 70 + i * 30 + 10 + (i / 3) * 10);
				glVertex2f(20 + j * 30 - 10 + (j / 3) * 10, 70 + i * 30 + 10 + (i / 3) * 10);
				glEnd();
			}
		}
	}
}

int check3by3matrix(int tempmatrix[][3])
{
	int i, j;

	//check if there are horizontal win i.e if there is any row that has same value
	for (i = 0; i <= 2; i++)
	{
		for (j = 1; j <= 2; j++)
		{
			if (tempmatrix[i][0] != 0 && tempmatrix[i][0] == tempmatrix[i][j])
			{
				if (j == 2)
				{
					if (tempmatrix[i][0] == 1)
						return 1;
					else
						return 2;
				}
			}
			else
				break;
		}
	}

	//check if there are vertical win i.e if there is any column that has same value
	for (i = 0; i <= 2; i++)
	{
		for (j = 1; j <= 2; j++)
		{
			if (tempmatrix[0][i] != 0 && tempmatrix[0][i] == tempmatrix[j][i])
			{
				if (j == 2)
				{
					if (tempmatrix[0][i] == 1)
						return 1; // return x
					else
						return 2; // return o
				}
			}
			else
				break;
		}
	}

	//check if there is any diagonal win i.e. if there is any diagonals that has same value
	for (i = 1; i <= 2; i++)
	{
		if (tempmatrix[0][0] != 0 && tempmatrix[0][0] == tempmatrix[i][i])
		{
			if (i == 2)
			{
				if (tempmatrix[0][0] == 1)
					return 1;
				else
					return 2;
			}
		}
		else
			break;
	}
	for (i = 1; i <= 2; i++)
	{
		if (tempmatrix[2][0] != 0 && tempmatrix[2][0] == tempmatrix[2 - i][i])
		{
			if (i == 2)
			{
				if (tempmatrix[2][0] == 1)
					return 1;
				else
					return 2;
			}
		}
		else
			break;
	}
	return 0;
}

void checkmatrix()
{
	int res, tempmatrix[3][3] = { 0 };
	for (int k = 0;k < 9;k += 3)
		for (int l = 0;l < 9;l += 3)
		{
			for (int i = 0;i < 3;i++)
				for (int j = 0;j < 3;j++)
					tempmatrix[i][j] = matrix[i + k][j + l];
			res = check3by3matrix(tempmatrix);
			if (res == 1)
			{
				glBegin(GL_LINES);
				glColor3f(1, 0, 0);
				glVertex2f(50 + (l / 3) * 100 - 35, 100 + (k / 3) * 100 - 35);
				glVertex2f(50 + (l / 3) * 100 + 35, 100 + (k / 3) * 100 + 35);
				glVertex2f(50 + (l / 3) * 100 - 35, 100 + (k / 3) * 100 + 35);
				glVertex2f(50 + (l / 3) * 100 + 35, 100 + (k / 3) * 100 - 35);
				glEnd();
				finalmatrix[k / 3][l / 3] = 1; 
				submatrix[k / 3][l / 3] = 2; // can't use this submatrix again 
			}
			if (res == 2)
			{
				glBegin(GL_LINE_LOOP);
				glColor3f(1, 0, 0);
				glVertex2f(50 + (l / 3) * 100 - 35, 100 + (k / 3) * 100 - 35);
				glVertex2f(50 + (l / 3) * 100 - 35, 100 + (k / 3) * 100 + 35);
				glVertex2f(50 + (l / 3) * 100 + 35, 100 + (k / 3) * 100 + 35);
				glVertex2f(50 + (l / 3) * 100 + 35, 100 + (k / 3) * 100 - 35);
				glEnd();
				finalmatrix[k / 3][l / 3] = 2;
				submatrix[k / 3][l / 3] = 2;
			}
		}
}

//This function checks if the match is a draw i.e it returns false if there is atleast one empty box else returns true 
bool checkifdraw(int tempmatrix[][3])
{
	for (int i = 0; i <= 2; i++)
		for (int j = 0; j <= 2; j++)
		{
			if (tempmatrix[i][j] == 0)
				return false;
		}
	return true;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	glColor3f(0, 0, 0);
	gameover = false;
	char p1[] = "Player1's turn";
	char p2[] = "Player2's turn";
	char over[] = "Game Over";
	char draw[] = "Its a draw";
	char ask[] = "Do you want to continue (y/n)";
	char w1[] = "Player1 won";
	char w2[] = "Player2 won";
	if (playerturn == 1)
		drawString(GLUT_BITMAP_HELVETICA_18, p1, 100, 30);
	else
		drawString(GLUT_BITMAP_HELVETICA_18, p2, 100, 30);
	drawlines();
	drawxo();
	checkmatrix();
	int res = check3by3matrix(finalmatrix);
	if (res == 1 || res == 2)
	{
		gameover = true;
		result = res;

		//horizontal line
		for (int i = 0;i < 3;i++)
			if (finalmatrix[i][0] != 0 && finalmatrix[i][0] == finalmatrix[i][1] && finalmatrix[i][1] == finalmatrix[i][2])
			{
				glBegin(GL_LINES);
				for (int k = 0;k < 3;k++)
				{
					glVertex2f(10, 100 - i * 100 + k);
					glVertex2f(290, 100 - i * 100 + k);
				}
				glEnd();
			}

		//vertical line
		for (int j = 0;j < 3;j++)
			if (finalmatrix[0][j] != 0 && finalmatrix[0][j] == finalmatrix[1][j] && finalmatrix[1][j] == finalmatrix[2][j])
			{
				glBegin(GL_LINES);
				for (int k = 0;k < 3;k++)
				{
					glVertex2f(50 + j * 100 + k, 40);
					glVertex2f(50 + j * 100 + k, 340);
				}
				glEnd();
			}

		//diagonal line 
		if (finalmatrix[0][0] != 0 && finalmatrix[0][0] == finalmatrix[1][1] && finalmatrix[1][1] == finalmatrix[2][2])
		{
			glBegin(GL_LINES);
			for (int k = 0;k < 3;k++)
			{
				glVertex2f(10 + k, 40 - k);
				glVertex2f(290 + k, 340 + k);
			}
			glEnd();
		}

		if (finalmatrix[0][2] != 0 && finalmatrix[0][2] == finalmatrix[1][1] && finalmatrix[1][1] == finalmatrix[2][0])
		{
			glBegin(GL_LINES);
			for (int k = 0;k < 3;k++)
			{
				glVertex2f(290 - k, 40 - k);
				glVertex2f(10 - k, 340 + k);
			}
			glEnd();
		}
	}
	else if (checkifdraw(finalmatrix))
	{
		gameover = true;
		result = 0;
	}

	glColor3f(0, 0, 0);
	if (gameover == true)
	{
		drawString(GLUT_BITMAP_HELVETICA_18, over, 100, 160);

		if (result == 0)
			drawString(GLUT_BITMAP_HELVETICA_18, draw, 110, 185);

		if (result == 1)
			drawString(GLUT_BITMAP_HELVETICA_18, w1, 95, 185);

		if (result == 2)
			drawString(GLUT_BITMAP_HELVETICA_18, w2, 95, 185);

		drawString(GLUT_BITMAP_HELVETICA_18, ask, 40, 210);
	}

	/*cout << endl << endl << endl << endl;
	for (int i = 0;i < 9;i++)
	{
		for (int j = 0;j < 9;j++)
			cout << matrix[i][j] << "  ";
		cout << endl;
	}
	for (int i = 0;i < 3;i++)
	{
		for (int j = 0;j < 3;j++)
			cout << submatrix[i][j] << " ";
		cout << endl;
	}*/
	//Sleep(2000);
	glutSwapBuffers();
	glFlush();
}

//This function is called on windows resize
void reshape(int x, int y)
{
	//glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, x, y, 0);
}

//main function of the program
int main(int argc, char **argv)
{
	initgame();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(300, 350);
	glutCreateWindow("Tic Tac Toe");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0, 300, 0, 350);
	gluOrtho2D(0, 300, 350, 0);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutKeyboardFunc(KeyPress);
	glutMouseFunc(click);
	glutMainLoop();
	return 0;
}