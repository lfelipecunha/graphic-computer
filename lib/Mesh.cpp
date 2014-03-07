#include "Mesh.h"

void Mesh::render() {
  glBegin(GL_POLYGON);
  for (int i=0; i< (long)groups.size(); i++) {
    Group g = groups[i];
    for (int j=0; j < (long)g.faces.size(); j++) {
      Face face = g.faces[j];
      for (int k=0; k < (long)face.vertices.size(); k++) {
        Vertex vertex = allVertices[face.vertices[k]];
        glVertex3fv(vertex.points);
      }
    }
  }
  glEnd();
}
