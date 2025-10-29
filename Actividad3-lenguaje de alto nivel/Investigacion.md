# Actividad 1:

R//= se realizo la instalacion correctamente 

# Actividad 2: 

R//= - ¿Qué fue lo que incluimos en el archivo .h?
R: En el archivo .h lo que se hizo fue incluir la librería principal de openFrameworks (ofMain.h) y crear la clase ofApp y dentro de esta clase se agregaron las funciones que maneja la aplicación, como setup, update, draw y las que reaccionan al mouse, también se declararon las variables privadas: un vector para guardar las posiciones de las partículas y un color para pintarlas.

- ¿Cómo funciona la aplicación?
R: La aplicación funciona dibujando círculos que siguen el movimiento del mouse cada vez que mueves el cursor, se guarda su posición, y se dibuja un círculo en ese lugar, sii hay más de 100 posiciones guardadas se borran las más antiguas para que el rastro no sea infinito, tambien cuando se hace clic todas las partículas cambian a un color aleatorio

- ¿Qué hace la función mouseMoved?
R: Se guarda la posición del mouse dentro del vector y, si ya hay más de 100, se borra la primera para mantener solo las últimas.

- ¿Qué hace la función mousePressed?
R: Cambia el color de todas las partículas a un color aleatorio generado con valores al azar de rojo, verde y azul.

- ¿Qué hace la función setup?
R: Configura el fondo en negro y se establece que el color inicial de las partículas sea blanco.

- ¿Qué hace la función update?
R: Sirve para actualizar la lógica de la aplicación, como animaciones o movimientos de los objetos antes de dibujarlos.

- ¿Qué hace la función draw?
R: Se encarga de mostrar las partículas en la pantalla recorriendo todas las posiciones guardadas y dibuja un círculo de color en cada una de ellas con un tamaño fijo de radio 50.

# Actividad 3:

R//= - ¿Qué hace cada función? 
R: setup(): Pone el fondo en negro y deja el color inicial de las partículas en blanco.

update(): No hace nada.

draw(): Dibuja círculos en todas las posiciones guardadas en el vector.

mouseMoved(): Agrega la posición del mouse al vector y borra la más vieja si ya hay más de 100.

mousePressed(): Cambia el color de las partículas a uno aleatorio.

- ¿Qué hace cada línea de código?
R: ofBackground(0): Coloca fondo negro

particleColor = ofColor::white: Color inicial blanco

for(auto &pos: particles){...}: Recorre todas las posiciones guardadas

ofSetColor(particleColor): Pone el color actual para dibujar

ofDrawCircle(pos.x, pos.y, 50): Dibuja un círculo en esa posición con radio 50

particles.push_back(ofVec2f(x, y)): Guarda la posición del mouse en el vector

if (particles.size() > 100) { particles.erase(particles.begin());}: Borra la primera posición si ya hay más de 100

particleColor = ofColor(ofRandom(255), ofRandom(255), ofRandom(255)): Genera un color aleatorio y lo asigna

# Actividad 5:

- ¿Cuál es la definición de un puntero?
R: es una variable que almacena la dirección de memoria de otra variable que en lugar de guardar un valor directamente  guarda la posición en memoria donde está ese valor

- ¿Dónde está el puntero?
R: está guardado en una posición de memoria como cualquier otra variable y su contenido es una dirección de memoria

- ¿Cómo se inicializa el puntero?
R: con el operador &, que obtiene la dirección de memoria de una variable

- ¿Para qué se está usando el puntero?
R: acceder y modificar valores de otras variables, pasar variables por referencia a funciones y recorrer arreglos y estructuras como listas, árboles, etc

- ¿Qué es exactamente lo que está almacenado en el puntero?
R: un puntero almacena una dirección de memoria

# Actividad 6:

R: edicion del archivo ofApp.h:

#pragma once

#include "ofMain.h"

class Sphere {
public:
    Sphere(float x, float y, float radius);
    void draw();
    void update(float x, float y);
    float getX();
    float getY();
    float getRadius();

private:
    float x, y;
    float radius;
    ofColor color;
};

class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();

        void mouseMoved(int x, int y );
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);

    private:
        vector<Sphere*> spheres;
        Sphere* selectedSphere;
};

edicion del archivo ofApp.cpp: 

#include "ofApp.h"

Sphere::Sphere(float x, float y, float radius) : x(x), y(y), radius(radius) {
    color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
}

void Sphere::draw() {
    ofSetColor(color);
    ofDrawCircle(x, y, radius);
}

void Sphere::update(float x, float y) {
    this->x = x;
    this->y = y;
}

float Sphere::getRadius() {
    return radius;
}

float Sphere::getX() {
    return x;
}

float Sphere::getY() {
    return y;
}

// ----------------------------------------------------
void ofApp::setup(){
    ofBackground(0);

    for (int i = 0; i < 5; i++) {
        float x = ofRandomWidth();
        float y = ofRandomHeight();
        float radius = ofRandom(20, 50);
        spheres.push_back(new Sphere(x, y, radius));
    }
    selectedSphere = nullptr;
}
// ------------------------------------------------------------
void ofApp::update(){
    if (selectedSphere != nullptr) {
        selectedSphere->update(ofGetMouseX(), ofGetMouseY());
    }
}
// --------------------------------------
void ofApp::draw(){
    for (auto sphere : spheres) {
        sphere->draw();
    }
}
// --------------------------------------
void ofApp::mouseMoved(int x, int y ){
    // No se necesita nada aquí
}
// --------------------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if(button == OF_MOUSE_BUTTON_LEFT){
        for (auto sphere : spheres) {
            float distance = ofDist(x, y, sphere->getX(), sphere->getY());
            if (distance < sphere->getRadius()) {
                selectedSphere = sphere;
                break;
            }
        }
    }
}
// ----------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if(button == OF_MOUSE_BUTTON_LEFT){
        selectedSphere = nullptr;
    }
}

el error era que el codigo no tenia el mouseReleased() y al presionar la esfera no la dejaba soltar, lo añadi y ahora la variable selectedSphere deja de seguir al mouse y se queda en nullptr

# Actividad 7:

ofApp.h
#pragma once

#include "ofMain.h"

class Sphere {
public:
    Sphere(float x, float y, float radius);
    void draw() const;

    float x, y;
    float radius;
    ofColor color;
};

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);

    ~ofApp();

private:
    std::vector<Sphere*> globalVector;
    void createObjectInStack(); // (nombre confunde, pero ahora crea en heap)
};

ofApp.cpp
#include "ofApp.h"

Sphere::Sphere(float x, float y, float radius) : x(x), y(y), radius(radius) {
    color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
}

void Sphere::draw() const {
    ofSetColor(color);
    ofDrawCircle(x, y, radius);
}

void ofApp::setup() {
    ofBackground(0);
}

void ofApp::update() {
}

void ofApp::draw() {
    ofSetColor(255);
    for (Sphere* sphere : globalVector) {
        if (sphere != nullptr) {
            ofDrawBitmapString("Objects pointed: " + ofToString(globalVector.size()), 20, 20);
            ofDrawBitmapString("Attempting to draw stored object...", 20, 40);
            ofDrawBitmapString("Stored Object Position: " + ofToString(sphere->x) + ", " + ofToString(sphere->y), 20, 60);
            sphere->draw();
        }
    }
}

void ofApp::keyPressed(int key) {
    if (key == 'c') {
        if (globalVector.empty()) {
            createObjectInStack();
        }
    }
    else if (key == 'd') {
        if (!globalVector.empty()) {
            ofLog() << "Accessing object in global vector: Position (" << globalVector[0]->x << ", " << globalVector[0]->y << ")";
        }
        else {
            ofLog() << "No objects in the global vector.";
        }
    }
}

void ofApp::createObjectInStack() {
    Sphere* heapSphere = new Sphere(ofRandomWidth(), ofRandomHeight(), 30); 
    globalVector.push_back(heapSphere);
    ofLog() << "Object created in heap: Position (" << heapSphere->x << ", " << heapSphere->y << ")";
    heapSphere->draw();
}

ofApp::~ofApp() {
    for (Sphere* sphere : globalVector) {
        delete sphere;
    }
    globalVector.clear();
}

- ¿Qué sucede cuando presionas la tecla “c”?
R: el programa crea un nuevo objeto Sphere en el heap usando new y lo guarda en el vector globalVector

- ¿Por qué ocurre esto?
R: porque antes el código creaba la esfera en el stack como una variable local (Sphere localSphere) y al salir de la función, esa variable se destruía automáticamente y el puntero quedaba apuntando a memoria inválida.

# Actividad 8:

#pragma once
#include "ofMain.h"

Sphere globalSphere(100, 100, 40); 

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);

private:

    std::vector<Sphere*> heapSpheres;

    std::vector<Sphere> stackSpheres;  

    void createHeapObject();
    void createStackObject();
};

#include "ofApp.h"

Sphere::Sphere(float x, float y, float radius) : x(x), y(y), radius(radius) {
    color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
}

void Sphere::draw() const {
    ofSetColor(color);
    ofDrawCircle(x, y, radius);
}

void ofApp::setup() {
    ofBackground(0);
}

void ofApp::update() {}

void ofApp::draw() {
    ofSetColor(255);
    ofDrawBitmapString("Presiona H (heap), S (stack), G (global)", 20, 20);

    globalSphere.draw();

    for (auto* s : heapSpheres) {
        if (s) s->draw();
    }

    for (auto& s : stackSpheres) {
        s.draw();
    }
}

void ofApp::keyPressed(int key) {
    if (key == 'h') {
        createHeapObject();
    } 
    else if (key == 's') {
        createStackObject();
    } 
    else if (key == 'g') {
        globalSphere.x = ofRandomWidth();
        globalSphere.y = ofRandomHeight();
        ofLog() << "Esfera global movida.";
    }
}

void ofApp::createHeapObject() {
    Sphere* heapSphere = new Sphere(ofRandomWidth(), ofRandomHeight(), 30);
    heapSpheres.push_back(heapSphere);
    ofLog() << "Esfera creada en HEAP (" << heapSphere->x << ", " << heapSphere->y << ")";
}

void ofApp::createStackObject() {
    Sphere stackSphere(ofRandomWidth(), ofRandomHeight(), 25);
    stackSpheres.push_back(stackSphere); 
    ofLog() << "Esfera creada en STACK (" << stackSphere.x << ", " << stackSphere.y << ")";
}

¿Cuándo debo crear objetos en el heap y cuándo en memoria global?
R:se usa heap para cosas dinámicas y flexibles y la memoria global para objetos permanentes y esenciales.

# Actividad 9:

#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void mousePressed(int x, int y, int button);

private:
    vector<ofVec2f*> heapObjects;
};


#include "ofApp.h"

void ofApp::setup(){
    ofBackground(0);
}

void ofApp::update(){
}

void ofApp::draw(){
    ofSetColor(0, 0, 255); // Color azul para los objetos del heap
    for(auto& pos : heapObjects) {
        ofDrawCircle(pos->x, pos->y, 20);
        ofDrawBitmapString("Heap Memory", pos->x - 40, pos->y - 40);
    }
}

void ofApp::keyPressed(int key){
    if(key == 'f') {
        if(!heapObjects.empty()) {
            delete heapObjects.back();
            heapObjects.pop_back();
        }
    }
}

void ofApp::mousePressed(int x, int y, int button){
    heapObjects.push_back(new ofVec2f(x, y));
}

- ¿Qué sucede cuando presionas la tecla “f”?
R: Se elimina el último objeto creado en el heap: primero se libera su memoria con delete y luego se quita su puntero del vector heapObjects con pop_back() y si esta vacio se deja de ver el círculo azul porque ya no está en el contenedor
