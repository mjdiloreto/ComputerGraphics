#include "Obj.h"
#include <stdio.h>
#include <string.h>

std::vector<std::string> tokenize(std::string s, std::string delimiter) {
	std::vector<std::string> tokens;
	size_t last = 0; 
	size_t next = 0;
	while ((next = s.find(delimiter, last)) != std::string::npos) { 
		tokens.push_back(s.substr(last, next - last));
		last = next + 1;
	}
	tokens.push_back(s.substr(last, s.length()-1)); // ignore the newline
	return tokens;
}

Obj::Obj(std::string filename) {
    std::ifstream inFile(filename);
    if(inFile.is_open()) {
        std::string currentLine;
        while(std::getline(inFile, currentLine)) {
			std::vector<std::string> tokens = tokenize(currentLine, " ");
			if (!tokens[0].compare("v"))
				parseVertex(tokens);
			else if (!tokens[0].compare("vn"))
				parseNormal(tokens);
			else if (!tokens[0].compare("f"))
				parseFace(tokens);
		}
    }
    inFile.close();
}

void Obj::parseVertex(std::vector<std::string> tokens) {
	for(int i = 1; i < tokens.size(); i++) {
		vertices.push_back(stof(tokens[i]));
	}
}

void Obj::parseNormal(std::vector<std::string> tokens) {
	for(int i = 1; i < tokens.size(); i++) {
		normals.push_back(stof(tokens[i]));
	}
}

void print(std::string msg) {
	std::cout << msg << std::endl;
}

void Obj::parseFace(std::vector<std::string> tokens) {
	//std::vector<int> verts;
	//std::vector<int> norms;
	for(int i = 1; i < tokens.size(); i++) {
		int firstDelimIndex = tokens[i].find("/", 0);
		std::string vert = tokens[i].substr(0, firstDelimIndex);
		std::string afterVert = tokens[i].substr(firstDelimIndex+1);
		int secondDelimIndex = afterVert.find("/", 0);
		std::string texture = afterVert.substr(0, secondDelimIndex); 
		std::string norm = afterVert.substr(secondDelimIndex+1); 
		//verts.push_back(stoi(vert)-1);
		//norms.push_back(stoi(norm)-1);
		faceVertices.push_back(stoi(vert)-1);
	 	try {
	 	  faceTextures.push_back(stoi(texture)-1);
	 	} catch (const std::invalid_argument& ia) {
	 	  // ignore
	 	}
		faceNormals.push_back(stoi(norm)-1);
	}
	//faceVertices.push_back(verts);
	//faceNormals.push_back(norms);
}

Obj::~Obj() {
    vertices.clear();
    normals.clear();
    faceVertices.clear();
    faceTextures.clear();
    faceNormals.clear();
}

