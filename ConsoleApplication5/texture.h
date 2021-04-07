#pragma once

class texture
{
public:
	texture(char const* path);

	void bind(int texture_block = -1);

private:
	unsigned int ID;
};

