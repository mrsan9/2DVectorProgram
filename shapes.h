#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <iostream>
using namespace std;
#include "shader.h"


typedef glm::vec2 vec2;
typedef glm::vec3 vec3;

static int click;

class Shape
{
	public:
		int size;
		vec2 *p ;
		virtual void drawShape(vec2 C[])=0;
		
};

class Line : public Shape
{
	public:
		
		void drawShape(vec2 C[])
		{	
			size = 2;
			p = new vec2[size];
			p[0] = C[0]; 
			p[1] = C[1]; 

			glBufferData(GL_ARRAY_BUFFER, sizeof(p)*(size) * 2, p, GL_STATIC_DRAW);// draw = false;
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0); glEnableVertexAttribArray(0);
			glDrawArrays(GL_LINE_LOOP, 0, size);
		}

};

class Circle : public Shape
{
public:
	
	
	void drawShape(vec2 C[])
	{		
		int size = 20;
		float rad = sqrt(pow(C[1].x - C[0].x, 2) + pow(C[1].y - C[0].y, 2));
		float angle = 0; int i = 0;
		p = new vec2[20];
		i = 0;
		while (i < 20)
		{
			angle = 2 * 3.1415926f * float(i) / float(20);
			vec2 temp;
			temp.x = C[0].x + cos(angle)*rad;
			temp.y = C[0].y + sin(angle)*rad;
			*(p + i) = temp;
			++i;
		}

		glBufferData(GL_ARRAY_BUFFER, sizeof(p)*(size) * 2, p, GL_STATIC_DRAW);// draw = false;
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0); glEnableVertexAttribArray(0);
		glDrawArrays(GL_LINE_LOOP, 0, size);
	}

};


class Rect : public Shape
{
public:
	

	void drawShape(vec2 C[])
	{	
		int size = 4;
		p = new vec2[size];
		*p = C[0]; *(p + 1) = vec2(C[0].x, C[1].y); *(p + 2) = C[1]; *(p + 3) = vec2(C[1].x, C[0].y);

		glBufferData(GL_ARRAY_BUFFER, sizeof(p)*(size) * 2, p, GL_STATIC_DRAW);// draw = false;
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0); glEnableVertexAttribArray(0);
		glDrawArrays(GL_LINE_LOOP, 0, size);
	}

};
 
class Poly : public Shape
{
public:
	
	void drawShape(vec2 C[])
	{
		size = click;
		p = new vec2[size];
		for (int i = 0; i <= click; ++i)
		{
			*(p + i) = C[i];
		}
		glBufferData(GL_ARRAY_BUFFER, sizeof(p)*(size) * 2, p, GL_STATIC_DRAW);// draw = false;
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0); glEnableVertexAttribArray(0);
		glDrawArrays(GL_LINE_STRIP, 0, size);
	}

};