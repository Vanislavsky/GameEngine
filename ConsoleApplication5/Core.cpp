#include "Core.h"




void Core::init() {

	Components::init();

	unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, attachments);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	Components::gBuffer.bind(GL_FRAMEBUFFER, 0);

	inputManager.setWindow(&window);

	Components::lighting_shader.use();
	Components::lighting_shader.set_int("gPosition", 0);
	Components::lighting_shader.set_int("gNormal", 1);
	Components::lighting_shader.set_int("gAlbedoSpec", 2);

	//add backpacks
	Object obj1(1, vec3(-0.7f, 0.0f, 0.0f));
	Components::addModelComponent(1);
	scene.addObject(obj1);
	Object obj2(2, vec3(0.0f, 0.0f, 0.0f));
	Components::addModelComponent(2);
	scene.addObject(obj2);
	Object obj3(3, vec3(0.7f, 0.0, 0.0f));
	Components::addModelComponent(3);
	scene.addObject(obj3);


	srand(13);
	for (unsigned int i = 0; i < 13; i++)
	{
		// calculate slightly random offsets
		float xPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
		float yPos = ((rand() % 100) / 100.0) * 6.0 - 4.0;
		float zPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
		Object obj(4+i, vec3(xPos, yPos, zPos));
		Components::addColorComponent(4 + i);
		scene.addObject(obj);
	}
}


void Core::update() {
	inputManager.checkWindowEvents();
}

void Core::postUpdate() {
	render.rendering(scene.getObjects());

	window.display();
}
