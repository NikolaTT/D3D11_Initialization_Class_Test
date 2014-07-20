#include "StringManipulator.h"
#include <vector>

void divideString(const std::string& input, const char condition, std::vector<std::string>& stringVector){

	int lastPos = 0;
	int currentTokenPos = 0;
	for (int i = 0; i < input.length(); i++){
		if (input[i] == condition){
			stringVector.push_back(input.substr(lastPos, i - lastPos));
			lastPos = i + 1;
			currentTokenPos++;
		}
	}	
	stringVector.push_back(input.substr(lastPos, std::string::npos));
}