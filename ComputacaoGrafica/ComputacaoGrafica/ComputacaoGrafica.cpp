#include <iostream>
#include <GL/freeglut.h>
#include <vector>

using vertice = std::pair<double, double>;
using lista_vertices = std::vector<vertice>;
using aresta = std::pair<int, int>;
using lista_arestas = std::vector<aresta>;



struct Vertice {
	GLfloat x = 0.0;
	GLfloat y = 0.0;
	GLfloat z = 0.0;

	Vertice() {};
	Vertice(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) {}
};

class Cube
{
public:
	Vertice pos;
	std::vector<Vertice> vertices;
	GLint edges[12][2] = { {0,1}, {1,2}, {2,3}, {3,0}, {4,5}, {5,6}, {6,7}, {7,4}, {0,4}, {1,5}, {2,6}, {3,7} };

	
	int velocidade;
	float tamanho;

	void subir()
	{
		this->pos.y += this->velocidade;

		for (int i = 0; i < 8; i++) {
			this->vertices[i].y += this->velocidade;
		}
	};
	void descer()
	{
		this->pos.y -= this->velocidade;

		for (int i = 0; i < 8; i++) {
			this->vertices[i].y -= this->velocidade;
		}
	};
	void moverEsquerda()
	{
		this->pos.x -= this->velocidade;

		for (int i = 0; i < 8; i++) {
			this->vertices[i].x -= this->velocidade;
		}
	};
	void moverDireita()
	{
		this->pos.x += this->velocidade;

		for (int i = 0; i < 8; i++) {
			this->vertices[i].x += this->velocidade;
		}
	};
	void moverFrente()
	{
		this->pos.z -= this->velocidade;

		for (int i = 0; i < 8; i++) {
			this->vertices[i].z -= this->velocidade;
		}
	};
	void moverTras()
	{
		this->pos.z += this->velocidade;

		for (int i = 0; i < 8; i++) {
			this->vertices[i].z += this->velocidade;
		}
	};
	void escalarAumentar()
	{
		for (int i = 0; i < 8; i++) {
			float x = this->vertices[i].x - this->pos.x;
			float y = this->vertices[i].y - this->pos.y;
			float z = this->vertices[i].z - this->pos.z;

			this->vertices[i].x = (x * 1.1) + this->pos.x;
			this->vertices[i].y = (y * 1.1) + this->pos.y;
			this->vertices[i].z = (z * 1.1) + this->pos.z;
		}
	};
	void escalarDiminuir()
	{
		for (int i = 0; i < 8; i++) {
			float x = this->vertices[i].x - this->pos.x;
			float y = this->vertices[i].y - this->pos.y;
			float z = this->vertices[i].z - this->pos.z;

			this->vertices[i].x = (x / 1.1) + this->pos.x;
			this->vertices[i].y = (y / 1.1) + this->pos.y;
			this->vertices[i].z = (z / 1.1) + this->pos.z;
		}
	};
	void rotacionarX(float angle)
	{
		float radian = angle * 3.1415926536 / 180.0;

		for (int i = 0; i < 8; i++) {
			float y = this->vertices[i].y - this->pos.y;
			float z = this->vertices[i].z - this->pos.z;

			this->vertices[i].y = this->pos.y + (y * cos(radian)) + (z * -sin(radian));
			this->vertices[i].z = this->pos.z + (y * sin(radian)) + (z * cos(radian));
		}
		
	};
	void rotacionarY(float angle)
	{
		float radian = angle * 3.1415926536 / 180.0;

		for (int i = 0; i < 8; i++) {
			float x = this->vertices[i].x - this->pos.x;
			float z = this->vertices[i].z - this->pos.z;
			this->vertices[i].x = this->pos.x + (x * cos(radian)) + (z * sin(radian));
			this->vertices[i].z = this->pos.z + (x * -sin(radian)) + (z * cos(radian));
		}
	};
	void rotacionarZ(float angle)
	{
		float radian = angle * 3.1415926536 / 180.0;

		for (int i = 0; i < 8; i++) {
			float x = this->vertices[i].x - this->pos.x;
			float y = this->vertices[i].y - this->pos.y;
			this->vertices[i].x = this->pos.x + (x * cos(radian)) + (y * sin(radian));
			this->vertices[i].y = this->pos.y + (x * -sin(radian)) + (y * cos(radian));
		}
	};	
};
Cube cubo;

void initGL() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //Coloca a cor de background para branco
	glClearDepth(1.0f);                   
	glEnable(GL_DEPTH_TEST);   
	glDepthFunc(GL_LEQUAL);   
}

void redraw(int value) {
	glutPostRedisplay();
	glutTimerFunc(10, redraw, 0);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);

	float nextI = 0;

	for (int i = 0; i < 4; i++) {
		nextI = i + 1;

		if (nextI == 4) {
			nextI = 0;
		}


		glVertex3f(
			cubo.vertices[i].x,
			cubo.vertices[i].y,
			cubo.vertices[i].z
		);
		glVertex3f(
			cubo.vertices[nextI].x,
			cubo.vertices[nextI].y,
			cubo.vertices[nextI].z
		);
		float novoI = i + 4;
		glVertex3f(
			cubo.vertices[novoI].x,
			cubo.vertices[novoI].y,
			cubo.vertices[novoI].z
		);
		float proximoI = nextI + 4;
		glVertex3f(
			cubo.vertices[proximoI].x,
			cubo.vertices[proximoI].y,
			cubo.vertices[proximoI].z
		);
	}

	for (int i = 0; i < 4; i++) {
		nextI = i + 4;
		glVertex3f(
			cubo.vertices[i].x,
			cubo.vertices[i].y,
			cubo.vertices[i].z
		);
		glVertex3f(
			cubo.vertices[nextI].x,
			cubo.vertices[nextI].y,
			cubo.vertices[nextI].z
		);
	}

	glEnd();

	glutSwapBuffers();
}


void reshape(GLsizei width, GLsizei height) {
	if (height == 0) height = 1;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, aspect, 0.1f, 500.0f);
}

void keyboard(unsigned char key, int x, int y) {
	std::cout << key;
	switch (key) {
	case 27:
		exit(0);
		break;
	case 'w':
	case 'W':	
		cubo.subir();
		break;
	case 's':
	case 'S':	
		cubo.descer();
		break;
	case 'd':
	case 'D':	
		cubo.moverDireita();
		break;
	case 'a':
	case 'A':
		cubo.moverEsquerda();
		break;
	case 'f':
	case 'F':
		cubo.moverFrente();
		break;
	case 't':
	case 'T':
		cubo.moverTras();
		break;
	case 'x':
		cubo.rotacionarX(-3.0);
		break;
	case 'X':
		cubo.rotacionarX(3.0);
		break;
	case 'y':
		cubo.rotacionarY(3.0);
		break;
	case 'Y':
		cubo.rotacionarY(-3.0);
		break;
	case 'z':
		cubo.rotacionarZ(3.0);
		break;
	case 'Z':
		cubo.rotacionarZ(-3.0);
		break;
	case 'e':
		cubo.escalarDiminuir();
		break;
	case 'E':
		cubo.escalarAumentar();
		break;
	}
}

void keyboard_special(int key, int x, int y) {
	std::cout << key;
	switch (key) {

	}
}

void criandoCubo() {
	cubo.pos.x = 25.0;
	cubo.pos.y = 0.0;
	cubo.pos.z = -75.0;

	cubo.vertices.push_back(Vertice(0.0, 25.0, -100.0));
	cubo.vertices.push_back(Vertice(50.0, 25.0, -100.0));
	cubo.vertices.push_back(Vertice(50.0, -25.0, -100.0));
	cubo.vertices.push_back(Vertice(0.0, -25.0, -100.0));

	cubo.vertices.push_back(Vertice(0.0, 25.0, -50.0));
	cubo.vertices.push_back(Vertice(50.0, 25.0, -50.0));
	cubo.vertices.push_back(Vertice(50.0, -25.0, -50.0));
	cubo.vertices.push_back(Vertice(0.0, -25.0, -50.0));

	cubo.velocidade = 1;
}

int main(int argc, char** argv) {
	
	criandoCubo();

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE);

	glutInitWindowSize(800, 500);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Cubo");

	glutDisplayFunc(display);

	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboard_special);
	glutTimerFunc(10, redraw, 0);
	glutReshapeFunc(reshape);
	initGL();
	glutMainLoop();

	return 0;
}