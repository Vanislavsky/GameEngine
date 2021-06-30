#include "Core.h"

Core::Core() : 
	geometry_shader("g_buffer.vs", "g_buffer.fs"), 
	lighting_shader("deferred_shading.vs", "deffered_shading.fs"),
	light_cube_shader("defered_light_box.vs", "deferred_light_box.fs"),
	gPosition(0),
	gNormal(1), 
	gAlbedoSpec(2) {
	unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, attachments);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	gBuffer.bind(GL_FRAMEBUFFER, 0);
}

void Core::preUpdate() {
	scene.getCamera().set_fov(glm::radians(45.0f));
	scene.getCamera().set_ratio((GLfloat)1800 / (GLfloat)1600);
	scene.getCamera().set_near(0.1f);
	scene.getCamera().set_far(100.0f);
	scene.getCamera().set_postion({ 0.0f, 0.0f,  3.0f });
	scene.getCamera().set_front({ 0.0f, 0.0f, -1.0f });
	scene.getCamera().set_up({ 0.0f, 1.0f, 0.0f });

	window.setCamera(&scene.getCamera());

	lighting_shader.use();
	lighting_shader.set_int("gPosition", 0);
	lighting_shader.set_int("gNormal", 1);
	lighting_shader.set_int("gAlbedoSpec", 2);

	scene.addObject({"C:/Users/79242/Desktop/backpack/backpack.obj", vec3(-0.7f, 0.0f, 0.0f) });
	scene.addObject({ "C:/Users/79242/Desktop/backpack/backpack.obj", vec3(0.0f, 0.0f, 0.0f) });
	scene.addObject({ "C:/Users/79242/Desktop/backpack/backpack.obj", vec3(0.7f, 0.0, 0.0f) });

	srand(13);
	for (unsigned int i = 0; i < 13; i++)
	{
		// calculate slightly random offsets
		float xPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
		float yPos = ((rand() % 100) / 100.0) * 6.0 - 4.0;
		float zPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
		// also calculate random color
		float rColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
		float gColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
		float bColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
		scene.addLightObject({ vec3(rColor, gColor, bColor), vec3(xPos, yPos, zPos) });
	}
}


void Core::upadte() {
	window.checkWindowEvents();
}

void Core::postUpdate() {
	render.rendering(&scene.getCamera(), scene.getObjects(), scene.getLightObjects(),
		&gBuffer, &gPosition, &gNormal, &gAlbedoSpec, 
		&geometry_shader, &lighting_shader, &light_cube_shader);

	window.display();
}
