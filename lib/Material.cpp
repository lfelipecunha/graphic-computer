#include "Material.h"

Material::Material(string n) {
  name = n;
  ka = kd = ks = NULL;
  ns = NULL;
  texture = NULL;
}

vector<Material> Material::getMaterials(ifstream &file) {
  string lineBuffer;
  int current = -1;
  vector<Material> materials;

  while(true) {
    if (file.eof()) {
      break;
    }

    getline(file, lineBuffer);

    if (lineBuffer.empty()) {
      continue;
    }

    if (lineBuffer.compare(0,6, "newmtl") == 0) {
      current++;
      materials.push_back(Material(lineBuffer.substr(7)));
    } else if(current >= 0) {
      if (lineBuffer.compare(0,2, "Ka") == 0) {
        materials[current].ka = getVertexFromLine(lineBuffer);
      } else if (lineBuffer.compare(0,2, "Kd") == 0) {
        materials[current].kd = getVertexFromLine(lineBuffer);
      } else if (lineBuffer.compare(0,2, "Ks") == 0) {
        materials[current].ks = getVertexFromLine(lineBuffer);
      } else if (lineBuffer.compare(0,2, "Ns") == 0) {
        materials[current].ns = new float(atof(lineBuffer.substr(3).c_str()));
      } else if (lineBuffer.compare(0,6, "map_Kd") == 0) {
        materials[current].texture = new ImageHandler(lineBuffer.substr(7).c_str());
      }
    }
  }
  return materials;
}

Vertex* Material::getVertexFromLine(string line) {
  // points of vertex
  float points[3];

  // auxiliar variable
  int i =0;

  // stream to analyze data
  stringstream streamLine(line);

  // loop to get information
  while(streamLine.good() && i < 4) {
    string aux;
    streamLine >> aux;
    // to ignore first information
    if (i==0) {
      i++;
      continue;
    }
    // get point of vertex
    points[i-1] = atof(aux.c_str());
    i++;
  }

  // return readed Vertex
  return new Vertex(points[0],points[1], points[2]);
}
