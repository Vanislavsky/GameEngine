//в шейдерах e4.vs тоже нужно дописать код

#pragma once

#include <iostream>
#include<vector>
#include<string>
#include"Core.h"

int main() {

	Core core;
	core.preUpdate();
	// цикл рендера
	bool isgo = true;
	while (isgo) {
		core.upadte();
		core.postUpdate();
	}

	return 0;
}
