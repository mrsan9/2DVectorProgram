#include"initProg.h"
#include<cstdlib>



void  genPoints(vec2 *a, vec2 C[]);

int s; 

int m = 0;  //Modes switching
bool draw = false;//draw toggle
//No of clicks


vec2 N[20];  //Stores Click Positions


int main()
{		


	//points = NULL;
	click = 0;
	//m = 3;
	//draw = false;
	Init w;
	GLFWwindow* window = w.window;
	GLuint ShaderProg = w.ShaderProg;
	
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetKeyCallback(window,key_button_callback);
	//glfwSetCursorPosCallback(window, cursor_pos_callback);
	
	int size = 20;
	s = size;
	

	int ss = 0;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glUseProgram(ShaderProg);
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
	
	unsigned int VBO[2], VAO[2];
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);


	//Fill buffer [0] with points
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float), NULL, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Fill buffer [1] with mouse positions 
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(N), NULL, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	Shape *l;
	glUseProgram(ShaderProg);
	while (!glfwWindowShouldClose(window))
	{		
		l = new Poly();
		glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
		glLineWidth(3); glPointSize(20.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//double t = glfwGetTime();
		glUseProgram(ShaderProg);
		if (draw)
		{	
			
			if (m == 1)ss = 2;
			else if (m == 2)ss = size;
			else if (m == 3)ss = 4;
			else
				ss = click;
				//vec2 points[size];
				
				//points = new vec2[ss]; 
				//cout << "T3 size: " << sizeof(points) << endl;
				//genPoints(points, N); 
				
				
				//genPoints(points,vec2(0.2,0.2),vec2(0.4,0.4));
			
				
		}
		glBindVertexArray(VAO[0]);
		l->drawShape(N);
		
		
		
		glBindVertexArray(VAO[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(N), N, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		int k = click+1 ;
		//if (m != 4)
			//glDrawArrays(GL_POINTS, 0, 2);
	//	else
			glDrawArrays(GL_POINTS,0,click);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	
	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
	

	glfwTerminate();
	return 0;
}


/*void genPoints(vec2 *a, vec2 C[])
{	
	float rad = sqrt(pow(C[1].x - C[0].x, 2) + pow(C[1].y - C[0].y, 2));
	float angle = 0; int i = 0;

	switch (m)
	{
	case 1:
		*(a+0) = C[0]; *(a+1) = C[1]; 
		for (int i = 0; i < 2; ++i)
			cout << C[i].x << " , " << C[i].y << " ";
		break;
	case 2:
		
		 //cout<<(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
		i = 0;
		while (i < s)
		{
			angle = 2 * 3.1415926f * float(i) / float(s);
			vec2 temp;
			temp.x = C[0].x+cos(angle)*rad;
			temp.y = C[0].y+sin(angle)*rad;
			*(a+i) = temp; 
			++i;
		}
		break;
	case 3:
		//a = 0;
		*a = C[0]; *(a + 1) = vec2(C[0].x, C[1].y); *(a + 2) = C[1]; *(a + 3) = vec2(C[1].x, C[0].y);
		//*a = vec2(0.1, 0.1); *(a + 1) = vec2(0.1, 0.4); *(a + 2) = vec2(0.4, 0.4); *(a + 3) = vec2(0.4,0.1);
		break;
	case 4:
		for (int i = 0; i <= click; ++i)
		{
			*(a + i) = C[i];
		}
		break;
	default:
		cout << "Select any Mode!! (1,2,3,4,5)";
	}

	
}*/

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{	
		cout << "ClickNo: " << click << endl;
		double xpos = 0, ypos = 0;
		glfwGetCursorPos(window, &xpos, &ypos);
		vec2 mp = vec2(xpos,ypos);

		N[click] = screenToWorld(window, mp);
		++click;
		/*
		if (m != 4) {
			if (click < 2)
				N[click] = screenToWorld(window, mp);
			++click;

			if (click > 1)
			draw = true;// cout << "MPos: " << N[click].x << "," << N[click].y << endl;

			if (click > 1)click = 0;
		}
		else
		{
			
			
			draw = true;
		}*/

		
	}
	
	/*if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
	{	
		cout << "N points:";
		for (int i = 0; i <= 2; ++i)
			cout << N[i].x << " , " << N[i].y << " ";
		cout <<endl ;
	}*/
}
void key_button_callback(GLFWwindow* window, int key, int scancode, int action, int mod)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (key == GLFW_KEY_C && action == GLFW_RELEASE)
	{
		//points = NULL; 
		draw = true; m = NULL;
	}

	if (key == GLFW_KEY_1 && action == GLFW_RELEASE)
	{
		m = 1; cout << "Line Mode" << endl;
	}
	if (key == GLFW_KEY_2 && action == GLFW_RELEASE)
	{
		m = 2; cout << "Circle Mode" << endl;
	}
	if (key == GLFW_KEY_3 && action == GLFW_RELEASE)
	{
		m = 3; cout << "Rectangle Mode" << endl;
	}
	if (key == GLFW_KEY_4 && action == GLFW_RELEASE)
	{
		m = 4; cout << "Polygon Mode" << endl; click = 0;
	}

	//cout << "Mode: " << m << endl << "Draw:" << draw;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.

	glViewport(0, 0, width, height);
}



vec2 screenToWorld(GLFWwindow* w,vec2 scr)
{
	//double xpos = 0, ypos = 0;
	int width, height;
	//getting cursor position
	//glfwGetCursorPos(w, &xpos, &ypos);
	glfwGetWindowSize(w, &width, &height);

	vec2 pos = vec2((scr.x - (width / 2)) / (width / 2), -(scr.y- (height / 2)) / (height / 2));
	//NorX1 = (xpos - (width / 2)) / (width / 2);
	//NorY1 = -(ypos - (height / 2)) / (height / 2);
	return pos;
}
