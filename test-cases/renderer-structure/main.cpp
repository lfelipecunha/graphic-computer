#include "../../lib/includes.h"
#include "../../lib/OpenGLRenderer.h"
#include "../../lib/Object.h"

using namespace std;
Object *o;

int w = 500, h = 500;
void init(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClearDepth(1.0);
  glEnable(GL_DEPTH_TEST);
  glDepthRange(0.0, 1.0);
  glEnable(GL_CULL_FACE);

  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHTING);

  glEnable(GL_COLOR_MATERIAL);

  glShadeModel(GL_SMOOTH);

  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  GLfloat light_position[] = { 1,1 ,1, 0.0 };
  GLfloat light_specular[] = {1.0, 1.0, 1.0,1.0};
  GLfloat light_diffuse[] = {1.0, 1.0, 1.0,1.0};
  GLfloat light_position2[] = { -1, -1, -1, 0.0 };

  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

  glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
  glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColorMaterial(GL_FRONT, GL_DIFFUSE);
  glColor3f (1.0, 1.0, 1.0);
  glLoadIdentity ();         /* clear the matrix */
  /* viewing transformation  */
  gluPerspective(45, w / (double) h, 0.2, 1000);
  gluLookAt(3, 1, 3,  0, 0, 0,  0, 1, 0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  o->render();
  glLoadIdentity();
  glBegin(GL_LINE_STRIP);
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(100,0,0);
  glEnd();
  glBegin(GL_LINE_STRIP);
    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,100,0);
  glEnd();
  glBegin(GL_LINE_STRIP);
    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,100);
  glEnd();

  glutSwapBuffers();
  glFlush();
}
void reshape (int x, int y) {
  w = x; h = y;
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, w / (double) h, 0.2, 1000);
  gluLookAt(3, 1, 3,  0, 0, 0,  0, 1, 0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int main(int argc, char** argv) {
    o = new Object(new OpenGLRenderer(GL_POLYGON));
    vector<vector<Point> > pts1;
    vector<Point> pts;
    pts.push_back(Point(0,0,0));
    pts.push_back(Point(1,0,0));
    pts.push_back(Point(1,1,0));
    pts.push_back(Point(0,1,0));
    pts1.push_back(pts);
    o->setPoints(pts1);
    o->setAngle(45,Object::ANGLE_Y);

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize (w, h);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init();
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
}
