#include "../../lib/Mesh.h"
#include "../../lib/Curve.h"

#define X 20
#define Y 20

Curve *c, *c2, *c3;
using namespace std;

vector<Point> points;

Mesh m = Mesh();

bool editing = true;


void createMesh() {
  string name = "default";
  Group g = Group(name);
  vector<Point> p1, p2;
  p1 = c2->getPoints();
  p2 = c3->getPoints();
  int size = p1.size();
  int total = size * 2;
  for (int i=0; i< size; i++) {
    m.addVertex(p1[i]);
    m.addVertex(p2[i]);
  }

  for (int i=0; i<size; i++) {
    int pt0 = 2*i;
    int pt1 = (pt0+1) % total;
    int pt2 = (pt1+1) % total;
    int pt3 = (pt2+1) % total;

    Face f1 = Face();
    f1.vertices.push_back(pt0);
    f1.normals.push_back(-1);
    f1.textures.push_back(-1);

    f1.vertices.push_back(pt2);
    f1.normals.push_back(-1);
    f1.textures.push_back(-1);

    f1.vertices.push_back(pt1);
    f1.normals.push_back(-1);
    f1.textures.push_back(-1);
    g.faces.push_back(f1);

    Face f2 = Face();
    f2.vertices.push_back(pt1);
    f2.normals.push_back(-1);
    f2.textures.push_back(-1);

    f2.vertices.push_back(pt2);
    f2.normals.push_back(-1);
    f2.textures.push_back(-1);

    f2.vertices.push_back(pt3);
    f2.normals.push_back(-1);
    f2.textures.push_back(-1);
    g.faces.push_back(f2);
  }
  m.groups.push_back(g);
  m.toObj("files/pista.obj");
}

void mouse(int button, int state, int x, int y) {
  if (state != GLUT_DOWN) {
    return;
  }
  if (button == GLUT_LEFT_BUTTON && editing) {
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);

    y = windowHeight - y;
    float y0 = y / (double)windowHeight * Y;
    float x0 = x / (double)windowWidth * X;
    points.push_back(Point(x0,y0,0));
    c = new Curve(points);
  } else if (button == GLUT_RIGHT_BUTTON && editing) {
    editing = false;

    for (int i=0; i<3; i++) {
      points.push_back(points[i]);
    }
    c = new Curve(points);
    c2 = c->scale(0.8,true);
    c3 = c->scale(0.8, false);
    createMesh();
    c->save("files/pista.curve");
  }
  glutPostRedisplay();
}

void init(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0);
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f (1.0, 1.0, 1.0);
  glLoadIdentity ();         /* clear the matrix */
  /* viewing transformation  */
  glMatrixMode (GL_PROJECTION);
  glOrtho(0.0, X, 0.0, Y, 0.0, 10.0);

  c->render();
  c2->render();
  c3->render();
  glFlush();
}

void reshape (int w, int h) {
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
  glOrtho(0, X, 0, Y, 0, 10);
}



int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
  int w = 500, h = 500;

  c = new Curve(points);
  c2 = new Curve(points);
  c3 = new Curve(points);

  glutInitWindowSize (w, h);
  glutInitWindowPosition (100, 100);
  glutCreateWindow (argv[0]);
  init ();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutMainLoop();
  return 0;
}
