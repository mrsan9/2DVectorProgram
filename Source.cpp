#include"initProg.h"
#include<cstdlib>
#include<algorithm>


//void  genPoints(vec2 *a, vec2 C[]);


int m = 0;  //Modes switching




vec2 *N;  //Stores Click Positions

list<Circle> c;
list<Line> l;
list<Rect> r;
list<Poly> p; Poly pp; bool ren; bool d;
int main()
{		
	N = new vec2[50];
	ren = true; d = false;
	click = 0;
	draw = false;
	Init w;
	GLFWwindow* window = w.window;
	GLuint ShaderProg = w.ShaderProg;
	
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetKeyCallback(window,key_button_callback);
	//glfwSetCursorPosCallback(window, cursor_pos_callback);

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
	
	list <Circle> ::iterator it; 
	list <Line> ::iterator it1;
	list <Rect> ::iterator it2; 
	list <Poly> ::iterator it3;
	//Poly pp; 

	glUseProgram(ShaderProg);
	vec2 pts[2]; 
	while (!glfwWindowShouldClose(window))
	{
		
		glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
		glLineWidth(3); glPointSize(20.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//double t = glfwGetTime();
		glUseProgram(ShaderProg);


		glBindVertexArray(VAO[0]);


		if ((click+2)%2==0 && click>1 && m!=4)
		{
			if (m == 1) {
				Line ll(N[click -2], N[click-1]);
				if (std::find(std::begin(l), std::end(l), ll) == std::end(l))
					l.push_front(ll);
			}
			if (m == 2)
			{
				Circle cc(N[click - 2], N[click - 1]);
				if (std::find(std::begin(c), std::end(c), cc) == std::end(c))
					c.push_front(cc); 
			}
			if (m == 3)
			{
				Rect rr(N[click - 2], N[click - 1]);
				if (std::find(std::begin(r), std::end(r), rr) == std::end(r))
					r.push_front(rr); 
			}

		}

		if (m == 4)
		{
			vec2 fi;
			vec2 ls;
			if (ren) {
				pp.gen(N); pp.draw();

				 fi = N[0];
				 ls = N[click - 1];
			}
			if (sqrt(pow(ls.x - fi.x, 2) + pow(ls.y - fi.y, 2))<=0.06&& click>1)
			{
				ren = false;
				N[click-1] = N[0]; //pp.size -= 1;
				pp.gen(N);
				d = true; click = 0; 
			}

			if (std::find(std::begin(p), std::end(p), pp) == std::end(p) && d == true)
			{
				p.push_front(pp); 
				ren = true; d = false;
			}
			//p.get();
		}
		if(!l.empty())
		for (it1 = l.begin(); it1 != l.end(); ++it1)
		{
			(*it1).gen(); //cout << "No of Lines" << l.size() << endl;
		}
		if (!c.empty())
		for (it = c.begin(); it != c.end(); ++it)
		{
			(*it).gen(); //cout << "No of Circles" << c.size() << endl;
		}
		if (!r.empty())
		for (it2 = r.begin(); it2 != r.end(); ++it2)
		{
			(*it2).gen(); //cout << "No of Rects" << c.size() << endl;
		}
		if (!p.empty())
			for (it3 = p.begin(); it3 != p.end(); ++it3)
			{	
				//(*it3).id = 1;
				(*it3).draw(); //cout << "No of Polys" << p.size() << endl;
				//cout<<(*it3).id;
			}


		if (draw ) {
			pts[0] = (*(N + (click - 2)));
			pts[1] = (*(N + (click - 1)));
			glBindVertexArray(VAO[1]);

			if (m != 4)
			{
				glBufferData(GL_ARRAY_BUFFER, sizeof(pts), pts, GL_STATIC_DRAW);
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
				glDrawArrays(GL_POINTS, 0, 2);

			}
			else {
				glBufferData(GL_ARRAY_BUFFER, sizeof(N)*100, N, GL_STATIC_DRAW);
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
				glDrawArrays(GL_POINTS, 0, click);
			}
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	
	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
	

	glfwTerminate();
	return 0;
}




void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{	
		cout << "ClickNo: " << click << endl;
		double xpos = 0, ypos = 0;
		glfwGetCursorPos(window, &xpos, &ypos);
		vec2 mp = vec2(xpos,ypos);


		//if (pd > 1)pd = 0;
		/*if (m != 4) {
			if (click < 2)
			{
				N[click] = screenToWorld(window, mp);
				++click;
			}

			//if (click > 1)
			//draw = true;// cout << "MPos: " << N[click].x << "," << N[click].y << endl;

			if (click > 1)click = 0;
		}
		else
		{*/
			
			*(N+click) = screenToWorld(window, mp);
			++click;
			//draw = true;
		//}

		//	cout << "First pt: " << (*N).x << "," << (*N).y;
		//	cout << "Last pt: " << (*(N+(click-1))).x << "," << (*(N + (click - 1))).y<<endl;
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
	     m = NULL;
	}

	if (key == GLFW_KEY_1 && action == GLFW_RELEASE)
	{
		m = 1; cout << "Line Mode" << endl; click = 0;
	}
	if (key == GLFW_KEY_2 && action == GLFW_RELEASE)
	{
		m = 2; cout << "Circle Mode" << endl; click = 0;
	}
	if (key == GLFW_KEY_3 && action == GLFW_RELEASE)
	{
		m = 3; cout << "Rectangle Mode" << endl; click = 0;
	}
	if (key == GLFW_KEY_4 && action == GLFW_RELEASE)
	{
		m = 4; cout << "Polygon Mode" << endl; click = 0;
	}
	draw = true;
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