#include "Mesh.h"

void Mesh::render(vector<Material> materials) {
  for (int i=0; i< (long)groups.size(); i++) {
    Group g = groups[i];
    for (int h=0; h < (long)materials.size(); h++) {
      Material m = materials[h];
      if (g.material.compare(0,g.material.length(), m.name)) {
        if (m.ka != NULL) {
          glMaterialfv(GL_FRONT, GL_AMBIENT, m.ka->points);
        }
        if (m.kd != NULL) {
          glMaterialfv(GL_FRONT, GL_DIFFUSE, m.kd->points);
        }
        if (m.ks != NULL) {
          glMaterialfv(GL_FRONT, GL_SPECULAR, m.ks->points);
        }
        if (m.ns != NULL) {
          glMaterialfv(GL_FRONT, GL_SHININESS, m.ns);
        }
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
        break;
      }
    }
    for (int j=0; j < (long)g.faces.size(); j++) {
      Face face = g.faces[j];
      glBegin(GL_POLYGON);
      for (int k=0; k < (long)face.vertices.size(); k++) {
        Vertex vertex = allVertices[face.vertices[k]];
        if (face.normals[k] > -1) {
          glNormal3fv(allNormals[face.normals[k]].points);
        }


        if (face.textures[k] > -1) {
          Vertex v = allTextures[face.textures[k]];
          glTexCoord2f(v.points[0], v.points[1]);
        }
        glVertex3fv(vertex.points);
      }
      glEnd();
    }
  }
}

void Mesh::addVertex(Vertex v) {
  float x, y, z;
  x = v.points[0];
  y = v.points[1];
  z = v.points[2];

  allVertices.push_back(v);

  if (minVertex->points[0] > x) {
    minVertex->points[0] = x;
  }
  if (minVertex->points[1] > y) {
    minVertex->points[1] = y;
  }
  if (minVertex->points[2] > z) {
    minVertex->points[2] = z;
  }

  if (maxVertex->points[0] < x) {
    maxVertex->points[0] = x;
  }
  if (maxVertex->points[1] < y) {
    maxVertex->points[1] = y;
  }
  if (maxVertex->points[2] < z) {
    maxVertex->points[2] = z;
  }

}

Mesh::Mesh() {
  minVertex = new Vertex(0,0,0);
  maxVertex = new Vertex(0,0,0);
}
