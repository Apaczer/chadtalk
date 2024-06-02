#include <iostream>
#include <fstream>
#include <vector>

#include "assets.h"

// Function to save byte array as .png file
void saveToPNG(const std::vector<unsigned char>& byteArray, const std::string& fileName) {
    std::ofstream outFile(fileName, std::ios::binary);
    if (!outFile) {
        std::cerr << "Failed to open file for writing: " << fileName << std::endl;
        return;
    }
    outFile.write(reinterpret_cast<const char*>(byteArray.data()), byteArray.size());
    outFile.close();
    if (!outFile) {
        std::cerr << "Error occurred while writing to file: " << fileName << std::endl;
    }
}

int main() {
    // Example byte array (in a real scenario, you would have actual PNG data here)
    std::vector<unsigned char> byteArray = { /*paste byte array here*/ };

    // Name of the output file
    std::string fileName = "output.png";

    // Save the byte array to a .png file
    saveToPNG(byteArray, fileName);

    return 0;
}
