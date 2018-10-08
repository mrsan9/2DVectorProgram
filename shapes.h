#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <list>
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
		virtual void gen()=0;
				
};

class Line : public Shape
{
	public:
	   
		vec2 C[2];

		Line() {}

		 Line(vec2 f, vec2 s)
		{	
			C[0] = f;
			C[1] = s;
		}
		void gen()
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

class Circle :public Shape
{
public:
	vec2 C[2];

	Circle() {}

	Circle(vec2 f, vec2 s)
	{
		C[0] = f;
		C[1] = s;
	}
	void gen()
	{	
		
		int size = 20;
		float rad = sqrt(pow(C[1].x - C[0].x, 2) + pow(C[1].y - C[0].y, 2));
		float angle = 0; int i = 0;
		p = new vec2[size];
		i = 0;
		while (i < 20)
		{
			angle = 2 * 3.1415926f * float(i) / float(20);
			vec2 temp;
			temp.x = C[0].x + cos(angle)*rad;
			temp.y = C[0].y + sin(angle)*rad;
			*(this->p + i) = temp;
			++i;
		}
		glBufferData(GL_ARRAY_BUFFER, sizeof(p)*(size) * 2, this->p, GL_STATIC_DRAW);// draw = false;
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0); glEnableVertexAttribArray(0);
		glDrawArrays(GL_LINE_LOOP, 0, size);
				
	}
	
	
};


class Rect : Shape
{
public:
	
	void gen(vec2 f, vec2 s)
	{
		int size = 4;
		p = new vec2[size];
		*p = f; *(p + 1) = vec2(f.x, s.y); *(p + 2) = s; *(p + 3) = vec2(s.x, f.y);
		glBufferData(GL_ARRAY_BUFFER, sizeof(p)*(size) * 2, this->p, GL_STATIC_DRAW);// draw = false;
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0); glEnableVertexAttribArray(0);
		glDrawArrays(GL_LINE_LOOP, 0, size);
		
	}



};
 
class Poly 
{
public:
	int size;
	vec2 *p;
	void drawPoly(vec2 C[])
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