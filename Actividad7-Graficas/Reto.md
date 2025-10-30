# RAE1 #

1. construcción de la aplicación que propone el reto.
R//: Se creó una aplicación que al hacer uso de los shaders vertex y fragment se crea una malla 3D que genera colores y ondas que al hacer clic se intensifican.
- El vertex shader mueve los vértices para generar ondas.
- El fragment shader cambia los colores de los píxeles según el tiempo y la posición del mouse.
<img width="1920" height="1009" alt="Screenshot 29_10_2025 9_51_23 p  m" src="https://github.com/user-attachments/assets/69a61f36-7699-49fb-8688-2f80b75939e7" />

2. la app funciona asi:
- ofApp.cpp crea una malla de 100×100 vértices.
- El vertex shader usa esos datos para deformar la malla con ondas.
<img width="1920" height="1032" alt="REto7y8 - shader vert - Microsoft Visual Studio 29_10_2025 9_53_53 p  m" src="https://github.com/user-attachments/assets/9ba3ca98-5eea-4f07-befd-0d682d01febf" />

- El fragment shader usa el mouse y el tiempo para pintar colores animados.
<img width="1920" height="1032" alt="REto7y8 - shader vert - Microsoft Visual Studio 29_10_2025 9_53_53 p  m" src="https://github.com/user-attachments/assets/1dabba09-2819-4b87-a97d-d8cdc5d1f014" />

- Todo se ve con una cámara 3D (ofEasyCam) para observar la superficie y tiene una "linterna" para fijarse en una parte en especifico
<img width="1920" height="1009" alt="Screenshot 29_10_2025 9_52_24 p  m" src="https://github.com/user-attachments/assets/3a1a2c8b-83c6-4da4-a4ea-40ce262066a7" />

3. Codigo entero

## ofApp.cpp ##

    void ofApp::setup() {
	    ofBackground(0);
	    shader.load("shader.vert", "shader.frag");

	int cols = 100;
	int rows = 100;
	float spacing = 10.0f;

	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			mesh.addVertex(glm::vec3(x * spacing, y * spacing, 0));
			mesh.addTexCoord(glm::vec2(x / (float)cols, y / (float)rows));
		}
	}

	for (int y = 0; y < rows - 1; y++) {
		for (int x = 0; x < cols - 1; x++) {
			int i1 = x + y * cols;
			int i2 = (x + 1) + y * cols;
			int i3 = x + (y + 1) * cols;
			int i4 = (x + 1) + (y + 1) * cols;

			mesh.addIndex(i1);
			mesh.addIndex(i2);
			mesh.addIndex(i3);
			mesh.addIndex(i2);
			mesh.addIndex(i4);
			mesh.addIndex(i3);
		}
	}

	for (auto & v : mesh.getVertices()) {
		v.x -= (cols * spacing) / 2.0f;
		v.y -= (rows * spacing) / 2.0f;
	}

	mesh.setMode(OF_PRIMITIVE_TRIANGLES);

	cam.setDistance(800);
    }

    //--------------------------------------------------------------
    void ofApp::update() { }

    //--------------------------------------------------------------
    void ofApp::draw() {
	    cam.begin();
	    shader.begin();

	shader.setUniform1f("time", ofGetElapsedTimef());
	shader.setUniform2f("mouse", ofGetMouseX(), ofGetMouseY());
	shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	shader.setUniform1i("mousePressed", isMousePressed ? 1 : 0);

	mesh.draw(); 
	shader.end();
	cam.end();
    }

    //--------------------------------------------------------------
    void ofApp::mousePressed(int x, int y, int button) {
	    isMousePressed = true;
    }
    
    //--------------------------------------------------------------
    void ofApp::mouseReleased(int x, int y, int button) {
    	isMousePressed = false;
    }


## ofApp.cpp ##

    #pragma once
    #include "ofMain.h"
    
    class ofApp : public ofBaseApp {
    public:
    	void setup();
    	void update();
    	void draw();
    
    	void mousePressed(int x, int y, int button);
    	void mouseReleased(int x, int y, int button);
    
    	ofShader shader;
    	ofMesh mesh;
    	ofEasyCam cam;
    
    	bool isMousePressed = false;
    };

## shader.vert ##

    #version 120
    
    uniform float time;
    uniform vec2 mouse;
    uniform vec2 resolution;
    uniform int mousePressed;
    
    void main() {
        vec4 pos = gl_Vertex;
    
        float wave = sin(pos.x * 0.05 + time) * 20.0;
        pos.z += wave;
    
        vec2 mouseWorld = (mouse / resolution - 0.5) * 1000.0;
        float dist = distance(vec2(pos.x, pos.y), mouseWorld);
    
        if (mousePressed == 1) {
            pos.z += cos(dist * 0.05 - time * 5.0) * 60.0;
        }
    
        gl_Position = gl_ModelViewProjectionMatrix * pos;
    }

## shader.frag ##

    #version 120
    
    uniform vec2 resolution;
    uniform vec2 mouse;
    uniform float time;
    uniform int mousePressed;
    
    void main() {
        vec2 st = gl_FragCoord.xy / resolution.xy;
        float dist = distance(st, mouse / resolution);
    
        vec3 color;
    
        if (mousePressed == 1) {
            color = vec3(
                1.0,
                0.3 + 0.7 * abs(sin(time * 3.0)),
                0.2 + 0.3 * cos(time * 2.0)
            );
        } else {
            color = vec3(
                0.2 + 0.2 * sin(time),
                0.5 + 0.5 * cos(time * 2.0),
                0.8
            );
        }
    
        color *= smoothstep(0.6, 0.0, dist);
    
        gl_FragColor = vec4(color, 1.0);
    }

 video explicando todo: https://youtu.be/NtLNDIIqPP4

 4. - Explica y muestra cómo probaste la aplicación en ofApp.cpp.
R//: Probé la aplicación verificando que los valores enviados a los shaders (posición del mouse y clic) se actualizaran correctamente.

- Explica y muestra cómo probaste el vertex shader.
R//: Probé el vertex shader observando si los vértices se movían como una onda al mover el mouse y ajusté la intensidad y frecuencia para comprobar que las deformaciones respondían al clic y que no generaran errores visuales.

      pos.z += sin(pos.x * 0.05 + time) * 20.0; <--- la linea que modifique 

- Explica y muestra cómo probaste el fragment shader.
R//: Probe el fragment shader cambiando los colores con el mouse y el clic, tambien comprobe que los tonos variaran correctamente y que no se produjeran zonas negras o sin color.

      vec3 color = vec3(1.0, 0.0, 0.0); <---- esta fue

- Explica y muestra cómo probaste toda la aplicación completa.
R//: Ejecuté toda la aplicación para confirmar que los shaders y el código trabajaran juntos y que funcionaran bien, para eso lo verifique todo otra vez: el movimiento de ondas, los cambios de color y  la respuesta fluida al mouse y al clic y si agarro :D (por fin y sin errores de compilacion).
