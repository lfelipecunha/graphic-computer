#include "Mesh.h"
int BUFSIZE = 255;
void Mesh::render(vector<Material> materials) {
  render(materials, false);
}
void Mesh::render(vector<Material> materials, bool selection) {
  GLuint selectBuf[BUFSIZE];
  GLint hits;
  if (selection) {
    glSelectBuffer(BUFSIZE, selectBuf);
    (void) glRenderMode(GL_SELECT);
    glInitNames();
    glPushName(0);
  }

  for (int i=0; i< (long)groups.size(); i++) {
    glPushMatrix();
    Group g = groups[i];
    if (!g.isActive()) {
      continue;
    }

    if (g.isSelected()) {
      glColor3f(1,0,0);
    } else {
      glColor3f(1,1,1);
    }
    if (selection) {
      glLoadName(i);
    }
    for (int h=0; h < (long)materials.size(); h++) {
      Material m = materials[h];
      if (g.material.compare(0,g.material.length(), m.name)) {
        if (m.ka != NULL) {
          float aux[] = { m.ka->x, m.ka->y, m.ka->z };
          glMaterialfv(GL_FRONT, GL_AMBIENT, aux);
        }
        if (m.kd != NULL) {
          float aux[] = { m.kd->x, m.kd->y, m.kd->z };
          glMaterialfv(GL_FRONT, GL_DIFFUSE, aux);
        }
        if (m.ks != NULL) {
          float aux[] = { m.ks->x, m.ks->y, m.ks->z };
          glMaterialfv(GL_FRONT, GL_SPECULAR, aux);
        }
        if (m.ns != NULL) {
          glMaterialfv(GL_FRONT, GL_SHININESS, m.ns);
        }
        if (m.texture != NULL) {
          glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            m.texture->getWidth(),
            m.texture->getHeight(),
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            m.texture->getPixels()
          );
        }
        break;
      }
    }
    for (int j=0; j < (long)g.faces.size(); j++) {
      Face face = g.faces[j];
      glBegin(GL_POLYGON);
      for (int k=0; k < (long)face.vertices.size(); k++) {
        Point* vertex = &allVertices[face.vertices[k]];
        if (face.normals[k] > -1) {
          Point* p = &allNormals[face.normals[k]];
          glNormal3f(p->x, p->y, p->z);
        }


        if (face.textures[k] > -1) {
          Point* v = &allTextures[face.textures[k]];
          glTexCoord2f(v->x, v->y);
        }
        glVertex3f(vertex->x, vertex->y, vertex->z);
      }
      glEnd();
    }
    glPopMatrix();
  }
  if (selection) {
    hits = glRenderMode(GL_RENDER);
    proccessHits(hits,selectBuf);
  }
}

void Mesh::proccessHits(GLint hits, GLuint buffer[]) {
  unsigned int j;
  int i, g;
  GLuint names, *ptr;

  ptr = (GLuint *) buffer;
  for (i = 0; i < hits; i++) { /*  for each hit  */
    names = *ptr;
    ptr++;
    ptr++;
    ptr++;
    for (j = 0; j < names; j++) {     /*  for each name */
      g = (int)*ptr;
      ptr++;
    }
  }
  if (hits > 0) {
    Group* gr = &groups[g];
    if (gr->isSelected()) {
      gr->toogle();
    } else {
      selectGroup(g);
    }
  }
}

void Mesh::selectGroup(int g) {
  for (int i=0; i < (long)groups.size(); i++) {
    if (i == g) {
      groups[g].select();
    } else {
      groups[i].deselect();
    }
  }
}

void Mesh::addVertex(Point v) {
  float x, y, z;
  x = v.x;
  y = v.y;
  z = v.z;

  allVertices.push_back(v);

  if (minVertex->x > x) {
    minVertex->x = x;
  }
  if (minVertex->y > y) {
    minVertex->y = y;
  }
  if (minVertex->y > z) {
    minVertex->y = z;
  }

  if (maxVertex->x < x) {
    maxVertex->x = x;
  }
  if (maxVertex->y < y) {
    maxVertex->y = y;
  }
  if (maxVertex->z < z) {
    maxVertex->z = z;
  }

}

Mesh::Mesh() {
  minVertex = new Point(0,0,0);
  maxVertex = new Point(0,0,0);
}

void Mesh::toObj(const char* filePath) {
  ofstream file (filePath);
  for (int i=0; i< (long)allVertices.size(); i++) {
    Point p = allVertices[i];
    file << "v " << p.x << " " << p.y << " " << p.z << "\n";
  }

  for (int i=0; i < (long)groups.size(); i++) {
    Group g = groups[i];
    file << "g " << g.name << "\n";
    for (int j=0; j < (long)g.faces.size(); j++) {
      Face f = g.faces[j];
      file << "f ";
      for (int k=0; k < (long)f.vertices.size(); k++) {
        file << f.vertices[k]+1 << "//";
        if (k < (long)f.vertices.size()) {
          file << " ";
        }
      }
      file << "\n";
    }
  }
}
