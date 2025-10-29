## Sesion 1 ##

- Factory Method: El patrón Factory Method encapsula la creación de objetos, permitiendo crear instancias sin especificar su clase concreta.
- Observer: El patrón Observer permite que un objeto (Subject) notifique automáticamente a otros objetos (Observers) cuando ocurre un cambio o evento.
- State: El patrón State permite que un objeto cambie su comportamiento cuando cambia su estado interno.

## Sesion 2 ##

¿Que hace en el caso de estudio?

Factory Method: ParticleFactory tiene un método estático createParticle(type) que recibe un string y devuelve un puntero a una Particle ya configurada y según el tipo ("star", "shooting_star", "planet"), la fábrica personaliza tamaño, color y velocidad.

Observer: - La clase ofApp hereda de Subject.
- Cada Particle implementa la interfaz Observer.
- ofApp mantiene una lista de partículas como observadores mediante addObserver().
- Cuando el usuario presiona una tecla (keyPressed()), ofApp llama a notify(evento), y todas las partículas reciben el evento en su método onNotify().
- Según el evento ("stop", "attract", "repel", "normal"), cada partícula cambia su estado.

State: - la clase State es una interfaz con métodos virtuales como update() y onEnter().
- Las subclases (NormalState, AttractState, RepelState, StopState) implementan comportamientos diferentes.
- Cada Particle tiene un puntero a su estado actual (state), y delega el comportamiento a ese objeto.
- Cuando se recibe un evento (onNotify), la partícula cambia su estado usando setState().


Cambios en el codigo:

1. Añadir un nuevo tipo de partícula:
else if (type == "comet") {
    particle->size = ofRandom(4, 7);
    particle->color = ofColor::orangeRed;
    particle->velocity *= 4;
}


Y en setup():

for (int i = 0; i < 3; ++i) {
    Particle* p = ParticleFactory::createParticle("comet");
    particles.push_back(p);
    addObserver(p);
}


2. Añadir un nuevo estado:
OscillateState (para hacer vibrar a las partículas)

class OscillateState : public State {
public:
    void update(Particle* particle) override {
        float time = ofGetElapsedTimef();
        particle->position.x += sin(time * 10) * 0.5;
        particle->position.y += cos(time * 10) * 0.5;
    }
};


En onNotify():

else if (event == "oscillate") {
    setState(new OscillateState());
}


En keyPressed():

else if (key == 'o') {
    notify("oscillate");
}


3. Modificar el comportamiento de las partículas ( en este caso para que crescan mientras se acercan )
void AttractState::update(Particle* particle) {
    ofVec2f mousePosition(((ofApp*)ofGetAppPtr())->mouseX, ((ofApp*)ofGetAppPtr())->mouseY);
    ofVec2f direction = mousePosition - particle->position;
    direction.normalize();
    particle->velocity += direction * 0.05;
    particle->size = ofClamp(particle->size + 0.05, 2, 10); // Aumenta tamaño
    particle->position += particle->velocity * 0.2;
}


4. Crear otros eventos para notificar a las partículas (evento “explode” para que las partículas se alejen rápidamente del centro de la pantalla)
class ExplodeState : public State {
public:
    void update(Particle* particle) override {
        ofVec2f center(ofGetWidth() / 2, ofGetHeight() / 2);
        ofVec2f direction = particle->position - center;
        direction.normalize();
        particle->velocity += direction * 0.2;
        particle->position += particle->velocity;
    }
};


Y en onNotify():

else if (event == "explode") {
    setState(new ExplodeState());
}


Y en keyPressed():

else if (key == 'e') {
    notify("explode");
}
