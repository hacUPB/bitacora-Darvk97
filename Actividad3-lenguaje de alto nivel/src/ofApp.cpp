#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(10);
	generateSpheres();
}

//--------------------------------------------------------------
void ofApp::generateSpheres() {
	spherePositions.clear();
	for (int x = -ofGetWidth() / 2; x < ofGetWidth() / 2; x += xStep) {
		for (int y = -ofGetHeight() / 2; y < ofGetHeight() / 2; y += yStep) {
			float z = cos(ofDist(x, y, 0, 0) / distDiv) * amplitud;
			spherePositions.push_back(glm::vec3(x, y, z));
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {
	// nada por ahora
}

//--------------------------------------------------------------
void ofApp::draw() {
	cam.begin();
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, 0);

	for (int i = 0; i < spherePositions.size(); ++i) {
		if (i == selectedIndex) {
			ofSetColor(255, 0, 0); // roja si está seleccionada
		} else {
			ofSetColor(0, 150, 255);
		}
		ofDrawSphere(spherePositions[i], 5);
	}

	ofPopMatrix();
	cam.end();

	// Mostrar coordenadas
	if (selectedIndex != -1) {
		ofSetColor(255);
		glm::vec3 pos = spherePositions[selectedIndex];
		ofDrawBitmapString("Seleccionada: (" + ofToString(pos.x) + ", " + ofToString(pos.y) + ", " + ofToString(pos.z) + ")",
			20, 20);
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	glm::vec3 rayStart, rayEnd;
	convertMouseToRay(x, y, rayStart, rayEnd);

	selectedIndex = -1;
	float minDist = FLT_MAX;
	for (int i = 0; i < spherePositions.size(); ++i) {
		glm::vec3 intersectionPoint;
		if (rayIntersectsSphere(rayStart, rayEnd - rayStart, spherePositions[i], 5.0, intersectionPoint)) {
			float dist = glm::distance(rayStart, intersectionPoint);
			if (dist < minDist) {
				minDist = dist;
				selectedIndex = i;
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::convertMouseToRay(int mouseX, int mouseY, glm::vec3 & rayStart, glm::vec3 & rayEnd) {
	glm::mat4 modelview = cam.getModelViewMatrix();
	glm::mat4 projection = cam.getProjectionMatrix();
	ofRectangle viewport = ofGetCurrentViewport();

	float x = 2.0f * (mouseX - viewport.x) / viewport.width - 1.0f;
	float y = 1.0f - 2.0f * (mouseY - viewport.y) / viewport.height;

	glm::vec4 rayStartNDC(x, y, -1.0f, 1.0f);
	glm::vec4 rayEndNDC(x, y, 1.0f, 1.0f);

	glm::vec4 rayStartWorld = glm::inverse(projection * modelview) * rayStartNDC;
	glm::vec4 rayEndWorld = glm::inverse(projection * modelview) * rayEndNDC;

	rayStartWorld /= rayStartWorld.w;
	rayEndWorld /= rayEndWorld.w;

	rayStart = glm::vec3(rayStartWorld);
	rayEnd = glm::vec3(rayEndWorld);
}

//--------------------------------------------------------------
bool ofApp::rayIntersectsSphere(const glm::vec3 & rayStart, const glm::vec3 & rayDir,
	const glm::vec3 & sphereCenter, float sphereRadius,
	glm::vec3 & intersectionPoint) {
	glm::vec3 oc = rayStart - sphereCenter;
	float a = glm::dot(rayDir, rayDir);
	float b = 2.0f * glm::dot(oc, rayDir);
	float c = glm::dot(oc, oc) - sphereRadius * sphereRadius;
	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0) return false;

	float t = (-b - sqrt(discriminant)) / (2.0f * a);
	intersectionPoint = rayStart + t * rayDir;
	return true;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case '+':
		amplitud += 5;
		generateSpheres();
		break;
	case '-':
		amplitud -= 5;
		generateSpheres();
		break;
	case 'a':
		distDiv += 5;
		generateSpheres();
		break;
	case 'z':
		distDiv -= 5;
		generateSpheres();
		break;
	case 'x':
		xStep += 5;
		yStep = xStep;
		generateSpheres();
		break;
	case 'c':
		xStep -= 5;
		yStep = xStep;
		generateSpheres();
		break;
	}
}
