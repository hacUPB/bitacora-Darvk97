# Actividad 1 #
esto fue lo que respondio chatgpt: 

## Qué es cada clase ##

Node: Representa un segmento de la serpiente.

Campos: - float x, y; posición del segmento.

- Node* next; puntero al siguiente nodo de la lista (lista simplemente enlazada).

Constructor: inicializa x, y y pone next = nullptr.

Destructor: vacío (no gestiona recursos adicionales).

LinkedList: Administra la lista enlazada de nodos que forman la serpiente.

Campos: - Node* head; primer nodo (la “cabeza” visual).

- Node* tail; último nodo (la “cola”).

- int size; cantidad de nodos.

LinkedList(): - Crea un nodo inicial centrado: head = new Node(ofGetWidth()/2, ofGetHeight()/2);

- tail = head; size = 1;

⚠️ Esto ya agrega 1 segmento de entrada.

~LinkedList(): Llama a clear() para liberar memoria.

clear(): - Recorre desde head, hace delete de cada Node, y al final deja head = tail = nullptr; size = 0;

- Seguro si la lista ya está vacía.

addNode(float x, float y): - Crea un Node y lo engancha al final: tail->next = newNode; tail = newNode; size++;

- Si la lista está vacía (tail == nullptr), inicializa head = tail = newNode.

- update(float x, float y):

Shifting: - hace que cada nodo copie la posición que tenía el anterior en el frame pasado.

Lógica: - Guarda en prevX, prevY la posición objetivo que recibe (aquí, el mouse).

- Recorre la lista current = head -> next -> ....

- Para cada nodo: guarda su posición actual (tempX, tempY), la reemplaza por prevX, prevY, y actualiza prev con la posición que tenía el nodo.

Resultado: el head toma la posición de (x,y) y cada segmento “persigue” al anterior.

display(): - Recorre la lista y dibuja cada segmento como un círculo rojo de radio 10. 
- Usa ofSetColor(ofColor(255,0,0)) + ofDrawCircle(x, y, 10).ofApp

LinkedList snake; es la serpiente como una lista enlazada.

setup(): Pone fondo blanco una vez (ofBackground(255,255,255)). Añade 10 nodos más, todos en el centro.

Importante: como el constructor de LinkedList ya creó 1 nodo, terminas con 11 segmentos (1 + 10).

update(): Llama a snake.update(ofGetMouseX(), ofGetMouseY()); Es decir, la cabeza se mueve al mouse y el resto se “desplaza” siguiendo la estela de frames anteriores.

draw(): Pone fondo gris claro cada frame (ofBackground(220);) y dibuja la serpiente.

Nota: el fondo blanco de setup() queda sobrescrito desde el primer draw(); no afecta visualmente.

keyPressed(int key): Si pulsas 'c', snake.clear() borra todos los segmentos (la serpiente desaparece hasta que vuelvas a añadir nodos en algún lugar).



## Flujo de ejecución en openFrameworks ##

main.cpp (no lo muestras, pero típico):

- Configura ventana con ofSetupOpenGL(...).

- Llama ofRunApp(new ofApp()); → se construye ofApp.

Construcción de miembros:

- Al construir ofApp, también se construye snake.

- En el constructor de LinkedList se usa ofGetWidth()/ofGetHeight() para colocar el primer nodo al centro.

- En la práctica suele ser seguro porque la ventana ya está creada al momento de construir ofApp (después de ofSetupOpenGL). Aun así, es más claro crear nodos en setup().

Ciclo principal:

- Llama setup() una vez → añades 10 nodos más.

- En cada frame: update() → draw().

- Eventos (teclado, mouse) llaman a sus callbacks cuando ocurren.



## Comportamiento visual ##

- Tienes una serpiente de 11 círculos rojos.

- La cabeza (el primer Node) salta a la posición del mouse cada frame.

- Cada segmento toma la posición previa del segmento anterior → efecto de “cadena” que sigue la trayectoria, con distancia entre segmentos igual al desplazamiento del mouse entre frames.

- Si mueves el mouse rápido, aparecen huecos entre segmentos.

- Si lo mueves lento, los segmentos quedan casi superpuestos.



## Complejidad y memoria ##

- update() y display() son O(n) por frame (n = número de nodos).

- clear() es O(n) y libera toda la memoria de nodos.

- addNode() es O(1) amortizado (insertas al final vía tail).



## Detalles/posibles gotchas ##

1. Doble “background”:

Pones fondo blanco en setup() y gris en draw(). El de setup() no se llega a ver persistentemente porque draw() repinta gris cada frame. No es un problema, pero es redundante.

2. 11 nodos (no 10):

Constructor de LinkedList crea 1, y en setup() agregas 10 → total 11. Si esperabas 10, mueve la creación del nodo inicial a setup() y deja el constructor sin añadir nada.

3. clear() deja la lista vacía:

Tras pulsar 'c', update()/display() no hacen nada (está bien), pero no vuelves a crear la serpiente. Si quieres re-crear, añade una tecla como 'r' que añada nodos otra vez.

4. Uso de ofGetWidth()/ofGetHeight() en constructores:

En openFrameworks normalmente funciona si la ventana ya está lista, pero por legibilidad y para evitar “orden de inicialización” dudoso, es mejor no depender de tamaño de ventana en el constructor de un miembro; hazlo en setup().

5. Render y estilo:

ofSetColor(ofColor(255,0,0)) dentro del bucle está bien. Si quisieras gradiente o cabeza diferente del cuerpo, cambia el color por nodo (p.ej., primero distinto).

6. Sin crecimiento dinámico:

La serpiente no “crece” con el tiempo; su longitud queda fija. Si quisieras crecimiento, podrías addNode() cada cierto tiempo o al presionar una tecla.

7. Espaciado uniforme:

Con este enfoque, el espaciado depende de cuánto se mueve el mouse entre frames. Si quieres segmentos equidistantes, necesitas una lógica distinta (seguir una polilínea de posiciones históricas y colocar cada segmento a una distancia fija sobre esa curva, o usar “easing” por segmento con una distancia objetivo).



## Mejoras opcionales (ideas rápidas): ##

Crear todo en setup() para evitar el nodo del constructor:

- Constructor: head = tail = nullptr; size = 0;

- En setup(): añadir los 10 (o los que quieras) nodos.


Resetear con tecla:

void ofApp::keyPressed(int key){
    if(key == 'c'){
        snake.clear();
    } else if(key == 'r'){
        for(int i=0;i<10;i++) snake.addNode(ofGetWidth()/2, ofGetHeight()/2);
    }
}


- Cabeza distinta: En display(), dibuja el primer nodo con tamaño/color distinto para destacar la cabeza.

- Movimiento suave: En vez de copiar posiciones exactas, usa interpolación:

- Para cada nodo: current->x += (prevX - current->x) * easing; (y lo mismo para y), con easing ~ 0.2.

- Contenedor STL: Podrías simplificar usando std::deque<ofVec2f> en lugar de una lista manual con new/delete (menos propenso a errores de memoria).

# Actividad 2 #
- Pregunta: ¿Qué sucede si insertas un nuevo nodo entre dos nodos ya existentes?
- Hipótesis: El nuevo nodo debe tomar el puntero `next` del nodo anterior, y el nodo anterior debe apuntar al nuevo nodo
- Verificación: Usar el depurador para observar si los punteros cambian correctamente. Comprobar si se pierde algún nodo o si hay referencias incorrectas.

# Actividad 3 #
1. Una lista enlazada es una estructura de datos compuesta por nodos conectados entre sí mediante punteros. Cada nodo contiene un valor y un puntero al siguiente nodo.
2. Diferencias:
- En un arreglo, los elementos están almacenados de forma contigua en memoria.
- En una lista enlazada, los nodos están dispersos en memoria y se conectan mediante punteros.
- Las listas enlazadas permiten inserciones y eliminaciones eficientes en cualquier posición, mientras que en un arreglo puede requerirse mover varios elementos.

# Actividad 4 #
1.
struct Node {
    int data;
    Node* next;
};
2. Cada nodo tiene un puntero (`next`) que apunta al siguiente nodo en la lista. Esta conexión entre nodos se hace usando punteros en C++

# Actividad 5 #

1. Node* nuevo = new Node;  // Crea un nodo
delete nodo;             // Libera la memoria del nodo
2. Los nodos se crean con el operador `new` y se eliminan con `delete`. Es importante liberar los nodos manualmente para evitar fugas de memoria

# Actividad 6 #

- En una lista enlazada, insertar o eliminar elementos en posiciones intermedias solo requiere cambiar algunos punteros.
- En un arreglo, estas operaciones pueden implicar mover múltiples elementos, lo que es más costoso en tiempo.

# Actividad 7 #

1. LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}
2. El destructor libera todos los nodos uno por uno para evitar fugas de memoria al destruir la lista.

# Actividad 8
- Se empieza desde el nodo `head`.
- Se guarda el puntero al siguiente nodo.
- Se elimina el nodo actual con `delete`.
- Se avanza al siguiente nodo.
- Se repite el proceso hasta llegar a `nullptr`.
- Finalmente, `head` se establece en `nullptr`.

# Actividad 9
1. - Se recorre la lista hasta llegar al último nodo.
- Se crea un nuevo nodo con `new`.
- El último nodo apunta al nuevo nodo con su puntero `next`.

2. Impacto en rendimiento: Es una operación O(n) si no se tiene un puntero al último nodo. Puede optimizarse con un puntero `tail`.

# Actividad 10
En una aplicación como un editor de texto, donde se insertan y eliminan caracteres constantemente, una lista enlazada es más eficiente que un arreglo.

Justificación:
- Permite insertar y eliminar en cualquier posición sin necesidad de mover elementos.
- Usa memoria dinámicamente, lo que evita redimensionar estructuras como en los arreglos.

# Actividad 11
1. Podría usarse en un motor de animación donde cada nodo representa un objeto en movimiento (como una partícula).

2. - Uso eficiente de `new` y `delete`.
- Implementar correctamente el destructor para liberar todos los nodos.
- Usar punteros inteligentes si es posible (como `std::unique_ptr`).
- Evitar ciclos de referencias para prevenir fugas de memoria.

# Actividad 12
1. C++:
- Gestión manual de memoria con `new` y `delete`.
- Mayor control, pero mayor riesgo de fugas de memoria si se omite `delete`.

C#:
- Tiene un recolector de basura (GC) que libera memoria automáticamente.
- Menos control sobre cuándo se libera la memoria, pero es más seguro.

2. Ventajas de C++: - control total 
- potencialmente más eficiencia.

Desventajas: - mayor responsabilidad 
- complejidad al liberar memoria.

# Actividad 13
- Liberar nodos correctamente cuando ya no se usan.
- Usar `clear()` o destructores para evitar fugas de memoria.
- Monitorear el uso de memoria si los elementos visuales son temporales.
- Optimizar inserciones y eliminaciones frecuentes en tiempo real.

# Actividad 14
    
    int main() {
        LinkedList lista;
        lista.insertAtEnd(10);
        lista.insertAtEnd(20);
        lista.insertAtEnd(30);
        lista.print(); // Esperado: 10 -> 20 -> 30

        lista.remove(20);
        lista.print(); // Esperado: 10 -> 30
    
        lista.clear();
        lista.print(); // Esperado: lista vacía
    }

Pruebas:
- Insertar nodos al inicio, medio y final.
- Eliminar nodos en diferentes posiciones.
- Verificar comportamiento al eliminar en lista vacía.
- Usar herramientas como Valgrind para asegurarte de que no hay fugas de memoria.
