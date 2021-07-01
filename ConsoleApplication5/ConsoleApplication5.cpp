//в шейдерах e4.vs тоже нужно дописать код

#pragma once

#include <iostream>
#include<vector>
#include<string>
#include"Core.h"

int main() {

	Core core;
	core.init();
	// цикл рендера
	bool isgo = true;
	while (isgo) {
		core.update();
		core.postUpdate();
	}

	return 0;
}
