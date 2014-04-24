  #include "../../lib/ObjReader.h"
  #include "../../lib/Mesh.h"

  Mesh m;
  vector<Material> materials;
  float eye[] = {-5, 5, 5};

  void init(void) {
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);

    glEnable(GL_CULL_FACE);

    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glCullFace(GL_BACK);

    glutSetCursor(GLUT_CURSOR_NONE);


    GLfloat light_position[] = { m.maxVertex->points[0]+1, m.maxVertex->points[1], m.maxVertex->points[2], 0.0 };
    GLfloat light_specular[] = {1.0, 1.0, 1.0,1.0};
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0,1.0};
    GLfloat light_position2[] = { m.minVertex->points[0]-1, m.minVertex->points[1], m.minVertex->points[2], 0.0 };

    glShadeModel (GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
  }

  void display(void) {
    glClear (GL_COLOR_BUFFER_BIT);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glColor3f (1.0, 1.0, 1.0);
    glLoadIdentity ();         /* clear the matrix */
    /* viewing transformation  */
    gluLookAt (eye[0], eye[1], eye[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    m.render(materials);

    glFlush ();
  }

  void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
      glFrustum (-1, 1, -1.0, 1.0, 1.5, 20.0);
    glMatrixMode (GL_MODELVIEW);
  }

  void keyboard(unsigned char key, int x, int y) {
    switch (key) {
      case 'w':
        eye[2] += 1;
        break;
      case 's':
        eye[2] -= 1;
        break;
    }
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
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
  }
  return 0;
}

