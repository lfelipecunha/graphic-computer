
  #include "../../lib/ObjReader.h"
  #include "../../lib/Camera.h"
  #include "../../lib/Curve.h"
  #include "Pista.h"
  #include "Car.h"

  bool car_view = false;

  Car* car;
  vector<Material> materials;

  Pista* pista;

  Camera* camera;

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
    camera->look();
    car->render();
    pista->render();

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

  void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    camera->setWindowSize(w, h);
    camera->look();
    glMatrixMode (GL_MODELVIEW);
  }

void set_top_view() {
  float w = pista->getWidth();
  float h = pista->getHeight();
  float cateto;
  if (w > h) {
    cateto = w;
  } else {
    cateto = h;
  }
  camera->setDirectionAngle(0.0);
  camera->setPosition(new Point(0,pista->getScale() * cateto / 0.55785173935,0));
  camera->directionY = 0;
}

  void keyboard(unsigned char key, int x, int y) {
    switch (key) {
      case 's':
        car_view = false;
        set_top_view();
        break;
      case 'c':
        car_view = true;
        break;
      case 'u':
        glDisable(GL_LIGHTING);
        break;
      case 'l':
        glEnable(GL_LIGHTING);
        break;
      case 'q':
        exit(0);
    }
  }

void background(int interval) {
  car->move();
  if (car_view) {
    camera->setPosition(new Point(0,car->pos.y,0));
    camera->directionY = car->pos.y;
    camera->lookAt(&car->pos);
  }
  glutTimerFunc(interval, background, interval);
}

int main(int argc, char** argv) {
  string filePath = "files/car.obj";
  ifstream file, pista_file;
  if (argc > 1) {
    filePath = argv[1];
  }

  pista_file.open("files/pista.obj");

  file.open(filePath.c_str());
  pista = new Pista(ObjReader::getMesh(pista_file), "files/pista.curve", &materials);

  if (file) {
    car = new Car(ObjReader::getMesh(file), &materials, pista);
    pista->scale(car, 5);
    string material_file = filePath.substr(0, filePath.length()-3) + "mtl";
    ifstream m_file;
    if (m_file) {
      materials = Material::getMaterials(material_file);
    }
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    int w = 500, h = 500;
    camera = new Camera(w,h);
    set_top_view();
    glutInitWindowSize (w, h);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    background(10);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
  }
  return 0;
}

