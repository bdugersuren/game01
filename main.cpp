#include <GL/glut.h>
#include <cmath>
#include <mmsystem.h>

GLfloat x=2,y=0,z=0, p=-0.1;
void oXYZ();
void tire();
void car(GLfloat x,GLfloat y,GLfloat z);
void pyramid(GLfloat x,GLfloat y,GLfloat z);
void paravol();
void draw();
void display();
void timer(int v);
void reshape(int w, int h);
void init();
void myKeyboard(unsigned char key, int x, int y);

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutCreateWindow("The RGB Color Cube");
  glutReshapeFunc(reshape);
  //glutTimerFunc(0, timer, 0);
  glutKeyboardFunc(myKeyboard);
  glutDisplayFunc(display);
  init();
  glutMainLoop();
}


//=============================Functions =============================================
void tire(){
    int a,i,r=1;
	int triangleAmount = 20;
	GLfloat twicePi = 2.0f * 3.14;
	glColor3f(1.0,1.0,0.2);
	glBegin(GL_LINE_STRIP);
		glVertex3f(x, y,0);
		for(a = 0; a <= 360;a++) {
			glVertex3f(x+(r*cos(a*twicePi/triangleAmount)),
			    y+(r*sin(a*twicePi/triangleAmount)),0
			);
		}
	glEnd();
}
void car(GLfloat x,GLfloat y,GLfloat z){

    //Left Green
    glColor3f(0,1,0);
    glBegin(GL_POLYGON);
        glVertex3f(x+1.5,y,z);
        glVertex3f(x+1.5,y+2,z);
        glVertex3f(x+1.5,y+2,z+2.5);
        glVertex3f(x+1.5,y+1,z+2.5);
        glVertex3f(x+1.5,y+1,z+3);
        glVertex3f(x+1.5,y,z+3);
    glEnd();

    //Right Green
    glColor3f(0,1,0);
    glBegin(GL_POLYGON);
        glVertex3f(x,y,z);
        glVertex3f(x,y,z+3);
        glVertex3f(x,y+1,z+3);
        glVertex3f(x,y+1,z+2.5);
        glVertex3f(x,y+2,z+2.5);
        glVertex3f(x,y+2,z);

    glEnd();


    //Front Green
    glColor3f(1,1,0);
    glBegin(GL_TRIANGLE_STRIP);
        //bottom
        glVertex3f(x,y,z);
        glVertex3f(x+1.5,y,z);

        glVertex3f(x,y,z+3);
        glVertex3f(x+1.5,y,z+3);
        //front -1
        glVertex3f(x,y+1,z+3);
        glVertex3f(x+1.5,y+1,z+3);
        //top 1
        glVertex3f(x,y+1,z+2.5);
        glVertex3f(x+1.5,y+1,z+2.5);

        glVertex3f(x,y+2,z+2.5);
        glVertex3f(x+1.5,y+2,z+2.5);

        glVertex3f(x,y+2,z);
        glVertex3f(x+1.5,y+2,z);

        glVertex3f(x,y,z);
        glVertex3f(x+1.5,y,z);

    glEnd();

}

void pyramid(GLfloat x,GLfloat y,GLfloat z){

    //Red
    glColor3f(1.0,0.0,0);
    glBegin(GL_TRIANGLES);
        glVertex3f(x+0.5,y+1,z+0.5);
        glVertex3f(x+1,y,z);
        glVertex3f(x,y,z);
    glEnd();

    //Green
    glColor3f(0,1,0);
    glBegin(GL_TRIANGLES);
        glVertex3f(x+0.5,y+1,z+0.5);
        glVertex3f(x+1,y,z+1);
        glVertex3f(x+1,y,z);

    glEnd();

    //Blue
    glColor3f(0,0,1);
    glBegin(GL_TRIANGLES);
        glVertex3f(x+0.5,y+1,z+0.5);
        glVertex3f(x,y,z+1);
        glVertex3f(x+1,y,z+1);
    glEnd();

    //Yellow
    glColor3f(1,1,0);
    glBegin(GL_TRIANGLES);
        glVertex3f(x+0.5,y+1,z+0.5);
        glVertex3f(x,y,z);
        glVertex3f(x,y,z+1);
    glEnd();

    //
    glColor3f(0.45,0.85,0.4);
    glBegin(GL_POLYGON);
        glVertex3f(x,y,z);
        glVertex3f(x+1,y,z);
        glVertex3f(x+1,y,z+1);
        glVertex3f(x,y,z+1);
    glEnd();
}


void oXYZ(){
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINES);
        glVertex3f(-10.0f,0.f,0.0f);
        glVertex3f(10.0f,0.0f,0.0f);

        glVertex3f(0.0f,-10.0f,0.0f);
        glVertex3f(0.0f,10.0f,0.0f);

        glVertex3f(0.0f,0.0f,-10.0f);
        glVertex3f(0.0f,0.0f,10.0f);

    glEnd();
}

void paravol(){
    //y=x^2+3x x=[-6;3]
    int n=10;
    double y;
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINE_STRIP);
        for(int x=-600;x<300;x++){
            y=x*x+3*x;
            glVertex3f(x/float(100),y/100,0);
        }
    glEnd();

}

void draw(){
    oXYZ();
    paravol();
    tire();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  draw();
  glFlush();
  glutSwapBuffers();
}

void timer(int v) {
  static GLfloat u = 0.0;
  u += 0.01;
  glLoadIdentity();
  gluLookAt(8*cos(u), 7*cos(u)-1, 4*cos(u/3)+2, .5, .5, .5, cos(u), 1, 0);
  glutPostRedisplay();
  glutTimerFunc(1000/60.0, timer, v);
  x+=p;
  if(x<-5)p=0.1;
  if(x>5)p=-0.1;

}

void myKeyboard(unsigned char key, int x, int y){
    static GLfloat u = 0.0;

    switch (key){
        case '.':PlaySound("aa.wav",NULL,SND_SYNC);
        case '+': u += 0.01; break;
        case '-': u -= 0.01; break;
        case 27: exit(0); break;
        default: break;
    }
  glLoadIdentity();
  gluLookAt(8*cos(u), 7*cos(u)-1, 4*cos(u/3)+2, .5, .5, .5, cos(u), 1, 0);
  glutPostRedisplay();
}

void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, GLfloat(w) / GLfloat(h), 0.5, 40.0);
  glMatrixMode(GL_MODELVIEW);
}

void init() {
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);
}
