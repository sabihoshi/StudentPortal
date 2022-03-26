#include <string>

#include "console.h"

struct BoxSet
{
	std::string Vertical;
	std::string Horizontal;

	std::string TopLeft;
	std::string TopRight;
	std::string Center;
	std::string BottomLeft;
	std::string BottomRight;

	std::string TopJunction;
	std::string LeftJunction;
	std::string RightJunction;
	std::string BottomJunction;
};

void FancyBox(int width, int height) { }
