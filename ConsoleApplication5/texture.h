#pragma once

class texture
{
public:
	texture(char const* path);
	texture(int texture_block);

	void bind(int texture_block = -1);
	unsigned int get_id();

private:
	unsigned int ID;
};


