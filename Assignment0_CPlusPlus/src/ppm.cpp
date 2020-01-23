#include "PPM.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


// Read all PPM tokens from the (open) file stream.
// Because the only data we want to save are ints, ignore anything else.
std::vector<int> tokenize(std::ifstream& inFile) {
    std::vector<int> tokens;
		std::string currentLine;
		std::string currentToken;

		while(std::getline(inFile, currentLine)) {
				std::istringstream from(currentLine);
				while (std::getline(from, currentToken, ' ')) {
					  if (currentToken == "#") {
					  	  break; // ignore everything else on a comment line.
						}
						try {
								tokens.push_back(std::stoi(currentToken));
						} catch (const std::invalid_argument& ia) {
								// Fine, it wasn't an int.
						}
				}
		}

		return tokens;
}

// Constructor loads a filename with the .ppm extension
PPM::PPM(std::string fileName){
    std::ifstream inFile(fileName);
    if(inFile.is_open()) {
    	  std::vector<int> allTokens = tokenize(inFile);
    	  int maxPixelValue = 0;
    	  int currentPixelData = 0;

    	  for(int i : allTokens) {
    	  	  if (!m_width) {
    	  	  	  m_width = i;
						} else if (!m_height) {
							  m_height = i;
							  m_PixelData = new unsigned char[m_width*m_height*3];
						} else if (!maxPixelValue) {
							  maxPixelValue = i;
						} else {
								// scale each pix.
							  m_PixelData[currentPixelData] = (char) (i * (255 / maxPixelValue));
							  currentPixelData++;
						}
				}
    }
    inFile.close();
}

// Destructor clears any memory that has been allocated
PPM::~PPM(){
    delete[] m_PixelData; 
}

// Saves a PPM Image to a new file.
void PPM::savePPM(std::string outputFileName){
    std::ofstream outFile;
    outFile.open(outputFileName);

    // Header
    outFile << "P3" << std::endl;
    // Comment line
    outFile << "# CREATOR: ppm.cpp" << std::endl;
    // height width
    outFile << m_width << " " <<  m_height << std::endl;
    
    // max pixel value. We always normalize to 255.
    outFile << "255" << std::endl;
    for (int i = 0; i < m_height; i++) {
        for (int j = 0; j < m_width; j++) {
            int idx = (i * m_width + j) * 3;
            outFile << (int) m_PixelData[idx] << " " << (int) m_PixelData[idx+1] << " " << (int) m_PixelData[idx+2] << " ";
				}
				outFile << std::endl;
    }
    outFile.close();
}

// Darken subtracts 50 from each of the red, green
// and blue color components of all of the pixels
// in the PPM. Note that no values may be less than
// 0 in a ppm.
void PPM::darken(){
    for (int i = 0; i < m_width * m_height; i++) {
		    for (int j = 0; j < 3; j++) {
            int currentPixelValue = (int) m_PixelData[i*3+j];
            if (currentPixelValue <= 50) {
            	  m_PixelData[i*3+j] = (char) 0;
						} else {
                m_PixelData[i*3+j] = (char) (currentPixelValue - 50);
						}
				}
		}
}

// Sets a pixel to a specific R,G,B value.
// Conditions: x and y must be within the bounds of this PPM image.
void PPM::setPixel(int x, int y, int R, int G, int B){
    int first_index = (y * m_width + x) * 3;
    m_PixelData[first_index] = (char) R;
    m_PixelData[first_index + 1] = (char) G;
    m_PixelData[first_index + 2] = (char) B;
}
