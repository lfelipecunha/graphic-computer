  #include "../../lib/ObjReader.h"
  #include "../../lib/Mesh.h"

  Mesh m;

  void init(void) {
    glClearColor (0.0, 0.0, 0.0, 0.0);
   // glEnable(GL_LIGHTING);
   // glEnable(GL_LIGHT0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    // glEnable(GL_COLOR_MATERIAL);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glCullFace(GL_BACK);

    glutSetCursor(GLUT_CURSOR_NONE);


    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat light_specular[] = {1.0, 1.0, 1.0,1.0};
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0,1.0};

    glShadeModel (GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  }

  void display(void) {
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    glLoadIdentity ();         /* clear the matrix */
    /* viewing transformation  */
    gluLookAt (-10.0, 10.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    m.render();

    glFlush ();
  }

  void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
    glMatrixMode (GL_MODELVIEW);
  }


int main(int argc, char** argv) {
  string filePath;
  ifstream file;
  do {
    cout << "Digite o caminho para o arquivo (ou exit para sair): ";
    cin >> filePath;
    file.open(filePath.c_str());
    if (!file && filePath != "exit") {
      cout << "\n\nCaminho Inválido!\n\n";
    }
  } while(!file && filePath != "exit");

  if (filePath != "exit") {
    m = ObjReader::getMesh(file);
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
  }
  return 0;
}

