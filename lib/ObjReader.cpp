#include "ObjReader.h"

/**
 * Read an OBJ file and create mesh
 *
 * @param ifstream Opened file with information
 * @return Mesh
 */
Mesh ObjReader::getMesh(ifstream &file) {
  // buffer analyze information
  string buffer;

  // result
  Mesh m = Mesh();

  // auxiliar to control actual work group
  int actualGroup = -1;

  // read all file
  while(true) {
    // break loop at end of file
    if (file.eof()) {
      break;
    }
    // read line
    getline(file, buffer);

    // ignore empty lines
    if (buffer.empty()) {
      continue;
    }

    // get information from type
    switch(buffer.at(0)) {
      // Vertex and Normal Vertex
      case 'v':
        // it's a normal vertex?
        if (buffer.at(1) == 'n') {
          Vertex v = getVertex(buffer);
          m.allNormals.push_back(v);
        // create a vertex
        } else if(buffer.at(1) == 't') {
          m.allTextures.push_back(getVertex(buffer));
        } else {
          Vertex v = getVertex(buffer);
          m.addVertex(v);
        }
        break;
      // Face
      case 'f':
        // doesn't exists an actual group?
        if(actualGroup < 0) {
          // create a new group
          actualGroup++;
          m.groups.push_back(Group("default"));
        }
        // create and setup a new face
        m.groups[actualGroup].faces.push_back(getFace(buffer));
        break;
      // Group
      case 'g':
        //create a new group and setup on mesh
        actualGroup++;
        m.groups.push_back(getGroup(buffer));
        break;
      case 'u':
        if (buffer.compare(0,6,"usemtl") == 0) {
          if(actualGroup < 0) {
            // create a new group
            actualGroup++;
            m.groups.push_back(Group("default"));
          }
          m.groups[actualGroup].material = buffer.substr(7);
        }
        break;
    }
  }

  // return readed mesh
  return m;
}

/**
 * Obtain vertex
 *
 * @param string line Line to be parsed
 * @return Vertex
 **/
Vertex ObjReader::getVertex(string line) {
  // points of vertex
  float points[3] = {0,0,0};

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
  return Vertex(points[0],points[1], points[2]);
}

/**
 * Create group from line
 *
 * @param string line
 * @return Group
**/
Group ObjReader::getGroup(string line) {
  string name;
  if ((long)line.size() > 2) {
    name = line.substr(2);
  } else {
    name = "default";
  }
  return Group(name);
}

/**
 * Create face
 *
 * @param string line
 * @return Face
 */
Face ObjReader::getFace(string line) {
  Face f = Face();
  int i =0;
  stringstream streamLine(line);


  // read line
  while(streamLine.good()) {
    // auxiliar variables
    string aux;
    string buffer;

    // informations to each vertice
    int infos[3];
    infos[0] = infos[1] = infos[2] = -1;

    // get information from line
    streamLine >> aux;

    // to ignore first information
    if (i==0) {
      i++;
      continue;
    }

    // read available informations
    int k = 0;
    for (int j=0; j<(long)aux.size(); j++) {
      if (aux.at(j) == '/') {
        if (!buffer.empty()) {
          infos[k] = atoi(buffer.c_str())-1;
        }
        k++; buffer = "";
      } else {
        buffer += aux.at(j);
      }
    }
    // has any information?
    if (!buffer.empty()) {
      infos[k] = atoi(buffer.c_str())-1;
    }

    // create vertex
    if (infos[0] > -1) {
      f.vertices.push_back(infos[0]);
    }

    //@todo create Texture with infos[1]
    if (infos[1] > -1) {
      f.textures.push_back(infos[1]);
    } else if (infos[0] > -1) {
      f.textures.push_back(-1);
    }

    // create normals
    if (infos[2] > -1) {
      f.normals.push_back(infos[2]);
    } else if (infos[0] > -1) {
      f.normals.push_back(-1);
    }
  }

  return f;
}
