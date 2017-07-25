#ifndef Color_H

#define Color_H

class Color
{
	char color;
	int position;

public:
	Color();
	Color(char c, int p);
	virtual ~Color();

	// getters
	char getColor() { return color; }
	int getPosition() { return position; }

	// setters
	void setColor(char c) { color = c; }
	void setPosition(int p) { position = p; }

};

#endif // !Color_H




