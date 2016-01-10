//
//  main.cpp
//  OpenGLSnack
//
//  Created by ZhaoPeiWei on 16/1/10.
//  Copyright © 2016年 ZhaoPeiWei. All rights reserved.


#include "../glut.h"
#include <stdio.h>
#include <math.h>
#include "Matrix.h"
#include <stdlib.h>
#include <random>
#include <list>

using std::list;

static const float PI = 3.1415926535;
// 16∫¡√Î “ª√ÎÀ¢–¬60
static const int timeInterval = 200;


void getVerticleCenterPoint();
void isInsidePologn();
void snake();
// key∂‘”¶µƒ «ascii¬Î
void keyboard(unsigned char key, int x, int y);
void special(int key, int x, int y);
void timeout(int value);
void idleFunc();
void initialSnackBody();
void generateFood();
int main(int argc, char*argv[]){

	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(400, 400);
	glutCreateWindow(argv[0]);
	
	
	initialSnackBody();

	
	glutKeyboardFunc(keyboard);

	glutSpecialFunc(special);

	glutTimerFunc(timeInterval, timeout, 0);

	
	//glutIdleFunc(idleFunc);

	glutDisplayFunc(snake);

	
	glutMainLoop();

	return 0;
}


#pragma mark - Ã∞≥‘…ﬂ

static const float delta = 0.05; //µ„÷Æº‰µƒº‰∏Ù

typedef enum{
	UP = 0,
	DOWN,
	LEFT,
	RIGHT
}DIRECTION;

DIRECTION direction = RIGHT;//ƒ¨»œœÚ”““∆∂Ø

typedef struct Point{

	float x;
	float y;

}Point;

list<Point> snackBodies;
Point food;

void initialSnackBody(){
	Point p;
	p.x = 0;
	p.y = 0;

	Point p2;
	p2.x = delta;
	p2.y = 0;
	snackBodies.push_back(p);
	snackBodies.push_back(p2);

	generateFood();
}

void generateFood(){
	
	food.x = (rand() % 90 / 100.0f );
	food.y = (rand() % 90 / 100.0f);

}

#pragma mark Action

void run(){

		Point head = snackBodies.front();
		Point back = snackBodies.back();
		Point newP;

		if (direction == RIGHT){
			newP.x = head.x + delta;
			newP.y = head.y;
		}
		else if (direction == LEFT){
			newP.x = head.x - delta;
			newP.y = head.y;
		}
		else if (direction == UP){
			newP.x = head.x;
			newP.y = head.y + delta;
		}
		else if (direction == DOWN){
			newP.x = head.x;
			newP.y = head.y - delta;
		}
		snackBodies.pop_back();
		snackBodies.push_front(newP);
		int range = 20;
		head = snackBodies.front();
		float foodX = (int)(food.x * 1000);
		float foodY = (int)(food.y * 1000);
		float headX = (int)(head.x * 1000);
		float headY = (int)(head.y * 1000);

		if (abs(head.x) > 1.0 || abs(head.y) > 1.0){
			//ÕÀ≥ˆ
			exit(0);
		}
		else if (headX >= (foodX - range) && (headX <= (foodX + range) && (headY >= (foodY - range) && (headY <= (foodY + range))))){
			if (direction == RIGHT){
				newP.x = head.x + delta;
				newP.y = head.y;
			}
			else if (direction == LEFT){
				newP.x = head.x - delta;
				newP.y = head.y;
			}
			else if (direction == UP){
				newP.x = head.x;
				newP.y = head.y + delta;
			}
			else if (direction == DOWN){
				newP.x = head.x;
				newP.y = head.y - delta;
			}

			snackBodies.push_back(newP);
			
			generateFood();
		}

		glutPostRedisplay();
		//À¢–¬“≥√Ê
	
}

void moveUp(){
	
	direction = UP;
}
void moveDown(){
	direction = DOWN;
}
void moveLeft(){
	direction = LEFT;
}
void moveRight(){
	direction = RIGHT;
}

//Ã∞≥‘…ﬂ
void snake(){

	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(4);

	glBegin(GL_LINE_STRIP);
	{
		for (list<Point>::iterator i = snackBodies.begin(); i != snackBodies.end(); ++i){

			Point& point = *i;
			glVertex2f(point.x, point.y);
		}
	}
	glEnd();

	//…Ë÷√ ≥ŒÔµƒ¥Û–°
	glPointSize(6);
	glBegin(GL_POINTS);
	{
		glColor3f(1, 0, 0);
		glVertex2f(food.x,food.y);
	}
	glEnd();
	glPointSize(1);

	// ∞—√¸¡Óœ¬∑¢µΩ∑˛ŒÒ∆˜∂À
	glFlush();
}

void timeout(int value)
{
	run();
	glutTimerFunc(timeInterval, timeout, 0);
}

void idleFunc()
{
	//ø’œ– ±∫Úµ˜”√
}

void special(int key, int x, int y)
{
	if (GLUT_KEY_DOWN == key)
	{
		printf("down is press\n");
		moveDown();
	}
	else if (GLUT_KEY_UP == key){
		printf("up is press\n");
		moveUp();
	}
	else if (GLUT_KEY_LEFT == key){
		printf("left is press\n");
		moveLeft();
	}
	else if (GLUT_KEY_RIGHT == key){
		printf("right is press\n");
		moveRight();
	}
}


// key∂‘”¶µƒ «ascii¬Î
void keyboard(unsigned char key, int x, int y)
{
	if (key == 'w' || key == 'W')
	{
		printf("w is press\n");

		moveUp();
	}

	else if (key == 'a' || key == 'A')
	{
		printf("a is press\n");
		moveLeft();
	}
	else if (key == 's' || key == 'S')
	{
		printf("s is press\n");
		moveDown();
	}
	else if (key == 'd' || key == 'D')
	{
		printf("d is press\n");
		moveRight();
	}
	else if (key == 0x1b)
	{
		printf("esc....\n");
		exit(0);
	}
}