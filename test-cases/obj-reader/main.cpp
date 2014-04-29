  #include "../../lib/ObjReader.h"
  #include "../../lib/Mesh.h"
  #include "../../lib/Camera.h"

  Mesh m;
  vector<Material> materials;

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



    GLfloat light_position[] = { m.maxVertex->x+1, m.maxVertex->y, m.maxVertex->z, 0.0 };
    GLfloat light_specular[] = {1.0, 1.0, 1.0,1.0};
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0,1.0};
    GLfloat light_position2[] = { m.minVertex->x-1, m.minVertex->y, m.minVertex->z, 0.0 };

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
    m.render(materials);
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

  void keyboard(unsigned char key, int x, int y) {
    switch (key) {
      case 'w':
        camera->move(Object::FRONT);
        break;
      case 's':
        camera->move(Object::BACK);
        break;
      case 'a':
        camera->rotate(-10);
        break;
      case 'd':
        camera->rotate(10);
        break;
      case 'z':
        camera->getPosition()->y++;
        break;
      case 'x':
        camera->getPosition()->y--;
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

void pick(int button, int state, int x, int y) {
  if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
      return;
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluPickMatrix ((GLdouble) x, (GLdouble) (viewport[3] - y),
                     .1, .1, viewport);
  camera->look(false);
  m.render(materials,true);
  glPopMatrix();
  glFlush();
}


int main(int argc, char** argv) {
  string filePath = "";
  ifstream file;
  if (argc > 1) {
    filePath = argv[1];
  }

  file.open(filePath.c_str());


  while(!file && filePath != "exit") {
    cout << "Digite o caminho para o arquivo (ou exit para sair): ";
    cin >> filePath;
    file.open(filePath.c_str());
    if (!file && filePath != "exit") {
      cout << "\n\nCaminho Inválido!\n\n";
    }
  }

  if (filePath != "exit") {
    m = ObjReader::getMesh(file);
    string material_file = filePath.substr(0, filePath.length()-3) + "mtl";
    ifstream m_file;
    m_file.open(material_file.c_str());
    if (m_file) {
      materials = Material::getMaterials(m_file);
    }
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    int w = 500, h = 500;
    camera = new Camera(w,h);
    glutInitWindowSize (w, h);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutIdleFunc(display);
    glutMouseFunc(pick);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
  }
  return 0;
}

