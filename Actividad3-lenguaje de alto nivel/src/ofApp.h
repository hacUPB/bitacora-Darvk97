
	#pragma once

#include "ofMain.h"

	class ofApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mousePressed(int x, int y, int button);

		void convertMouseToRay(int mouseX, int mouseY, glm::vec3 & rayStart, glm::vec3 & rayEnd);
		bool rayIntersectsSphere(const glm::vec3 & rayStart, const glm::vec3 & rayDir,
			const glm::vec3 & sphereCenter, float sphereRadius,
			glm::vec3 & intersectionPoint);

		void generateSpheres();

		ofEasyCam cam;

		vector<glm::vec3> spherePositions;
		int xStep = 50;
		int yStep = 50;
		float distDiv = 100.0;
		float amplitud = 100.0;

		int selectedIndex = -1; // índice de la esfera seleccionada
	};
