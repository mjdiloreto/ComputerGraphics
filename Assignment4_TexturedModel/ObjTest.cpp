#include "Obj.h"
#include <stdio.h>

int main() {
	std::cout << "Beginning ObjTest" << std::endl;
	Obj myObj("./objects/house/house_obj.obj");
	std::cout << myObj.vertices[0] << std::endl;
	std::cout << myObj.diffuseTextureFilename << std::endl;
	std::cout << myObj.combinedIndexes.size() << std::endl;
	std::cout << myObj.vertexData.size() << std::endl;
	std::cout << "End ObjTest" << std::endl;
	return 0;
}
