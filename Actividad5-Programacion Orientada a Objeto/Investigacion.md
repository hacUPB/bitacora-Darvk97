## Sesion 1 ##
# Intorduccion a los objetos #

- ¿Qué representa la clase Particle?
R//: La clase Particle representa un concepto o entidad que modela una partícula en un programa en términos de programación orientada a objetos (POO), una clase es una plantilla o molde que define atributos y métodos 
que una instancia de esa clase tendrá.

- ¿Cómo interactúan sus atributos y métodos?
R//: Atributos: Son las variables que guardan el estado o las características de cada objeto de la clase. En Particle, por ejemplo, x y y podrían ser atributos que guardan la posición de la partícula en el plano.

Métodos: Son funciones definidas dentro de la clase que describen acciones que un objeto puede realizar o comportamientos asociados. Por ejemplo, el método move podría modificar los valores de x y y para cambiar la posición de la partícula.

- Prompt para ChatGPT: explícame en detalle qué es un objeto en C++ y cómo se relaciona con una clase. Usa el ejemplo de una clase Particle con atributos `x` y `y` y un método `move`.
R//: Clase Particle
Es una plantilla que define una partícula con atributos x y y (posición en 2D) y un método move para cambiar esa posición.

# Explorando la memoria #

- ¿Cómo afectan los datos estáticos al tamaño de la instancia?
R//: No afectan el tamaño de la instancia, ya que se almacenan aparte en la memoria global/estática.

- ¿Qué diferencias hay entre datos estáticos y dinámicos en términos de memoria?
R//: Los estáticos existen una sola vez y son compartidos por la clase; los dinámicos requieren memoria en el heap y deben gestionarse con new y delete.

- Prompt para ChatGPT: explícame cómo el uso de variables estáticas y dinámicas en una clase afecta el tamaño de sus instancias. ¿Las variables estáticas ocupan espacio en cada objeto?
R//: "Las variables estáticas no forman parte de cada objeto, se almacenan en la memoria global/estática y son compartidas por toda la clase, por lo que no aumentan el tamaño de la instancia. En cambio, las variables dinámicas son punteros dentro de la clase (estos sí cuentan en el tamaño del objeto), pero la memoria que apuntan se reserva aparte en el heap y debe gestionarse manualmente con new y delete."

# Reflexión #

- ¿Qué es un objeto desde la perspectiva de la memoria?
R//: Un objeto es una estructura de memoria que contiene espacio para los atributos de la clase. Estos atributos determinan directamente el tamaño en bytes de cada instancia. Los métodos no ocupan espacio dentro de cada objeto, ya que se almacenan en la memoria de código y son compartidos.

- ¿Cómo influyen los atributos y métodos en el tamaño y estructura del objeto?
R//: Los atributos sí afectan el tamaño del objeto, ya que cada instancia debe reservar memoria para sus valores. En contraste, los métodos no influyen en el tamaño de la instancia, pues se almacenan aparte y todas las instancias los comparten.

- Conclusión: resumir los hallazgos y cómo esto impacta el diseño de clases.
R//: El tamaño de los objetos depende solo de sus atributos, no de sus métodos ni de las variables estáticas. Esto implica que, al diseñar clases, es importante minimizar atributos innecesarios y usar referencias o dinámicas cuando se requiera optimizar memoria, evitando crear objetos demasiado pesados.

 ## Sesión 2 ##
# Análisis de la estructura de una clase #

- ¿Dónde se almacenan los datos y métodos de una clase en C++ en la memoria?
R//: Los datos se almacenan en el stack o heap según la instancia, los métodos en la sección de código (text) y las vtables en memoria global/estática.

# Exploración de métodos virtuales #

- ¿Cómo afecta la presencia de métodos virtuales al tamaño del objeto?
R//: Aumenta el tamaño porque cada objeto con virtuales guarda un puntero a la vtable.

- ¿Qué papel juegan las vtables en el polimorfismo?
R//: Permiten que el programa elija en tiempo de ejecución qué método llamar según el tipo real del objeto.

- ¿Cómo se implementan los métodos virtuales en C++?
R//: Con una vtable que contiene punteros a funciones; cada objeto tiene un puntero a su vtable.

# Uso de punteros y referencias #

- ¿Qué diferencia hay entre punteros a funciones y punteros a métodos miembro en C++?
R//: Los punteros a funciones almacenan direcciones de funciones libres o estáticas; los punteros a métodos miembro necesitan ligarse a un objeto específico.

- ¿Cómo afectan al tamaño de los objetos y al rendimiento?
R//: Un puntero a función ocupa lo mismo que una dirección; los punteros a métodos miembro pueden ocupar más y son ligeramente más lentos de invocar.

- Prompt para ChatGPT: ¿Qué diferencia hay entre punteros a funciones y punteros a métodos miembro en C++? ¿Cómo afectan al tamaño de los objetos y al rendimiento?
R//: "Un puntero a función es una dirección simple en memoria que apunta a una función global o estática; su tamaño suele ser el de una dirección de memoria estándar. En cambio, un puntero a método miembro incluye información adicional para poder asociar la función con un objeto específico (a través de this), lo que lo hace más complejo y en algunos compiladores más grande que un puntero a función normal. Ninguno de los dos afecta el tamaño de las instancias de objetos, ya que son entidades externas al objeto. Sin embargo, los punteros a métodos miembro pueden implicar un ligero costo de rendimiento adicional por la necesidad de resolución en tiempo de ejecución al invocar el método sobre un objeto."

# Reflexion #

- ¿Dónde residen los datos y métodos de una clase en la memoria?
R//: Los datos de instancia residen en el heap o la pila, dependiendo de cómo se cree el objeto. Los datos estáticos se almacenan en la memoria global/estática, compartidos por todas las instancias. Los métodos se guardan en la sección de código del programa y no duplican espacio por objeto.

- ¿Cómo interactúan las diferentes partes en tiempo de ejecución?
R//: Al ejecutar, cada objeto reserva memoria para sus atributos de instancia. Cuando se llama a un método, el objeto pasa como referencia implícita (this), lo que permite que el método acceda y modifique sus atributos. Las variables estáticas se acceden directamente desde la memoria global, y los métodos se ejecutan desde el código sin duplicarse.

- Conclusión: cómo esta comprensión afecta el diseño de sistemas.
R//: Conocer cómo se distribuyen datos y métodos en memoria permite optimizar el diseño: usar estáticos para información compartida, minimizar atributos innecesarios para reducir el tamaño de los objetos, y aprovechar métodos comunes sin desperdiciar memoria. Esto conduce a sistemas más eficientes y escalables.

## sesion 3 ##
# Profundizando en el encapsulamiento #

- Prompt para ChatGPT: ¿Cómo implementa el compilador el encapsulamiento en C++? Si los miembros privados aún ocupan espacio en el objeto, ¿Qué impide que se acceda a ellos desde fuera de la clase?
R//: "El compilador implementa el encapsulamiento mediante reglas de acceso en tiempo de compilación. Aunque los miembros privados ocupan espacio físico dentro del objeto igual que los públicos, el compilador prohíbe su acceso directo desde fuera de la clase generando errores al compilar si se intenta. No existe una barrera física en memoria, sino una restricción del lenguaje. Solo métodos de la propia clase (o amigos autorizados) pueden leer o modificar esos miembros."

# Hagamos un poco de hackers y rompamos el encapsulamiento #

- ¿Qué es el encapsulamiento y cuál es su propósito en la programación orientada a objetos?
R//: Es ocultar la implementación interna de una clase y exponer solo lo necesario, protegiendo los datos y mejorando la modularidad.

- ¿Por qué es importante proteger los datos de una clase y restringir el acceso desde fuera de la misma?
R//: Para mantener la integridad de los datos y evitar modificaciones indebidas.

- ¿Qué significa reinterpret_cast y cómo afecta la seguridad del programa?
R//: Permite tratar memoria como otro tipo; puede romper la encapsulación y causar vulnerabilidades.

- ¿Por qué se pudo acceder a los miembros privados de MyClass en el experimento?
R//: Porque en memoria los datos están presentes y accesibles con punteros; el compilador solo impide accesos directos.

- ¿Cuáles podrían ser las consecuencias de utilizar técnicas como las mostradas en este experimento en un programa real?
R//: Corrupción de datos, fallos de ejecución y problemas de seguridad.

- ¿Qué implicaciones tiene este experimento sobre la confianza en las barreras de encapsulamiento que proporciona C++?
R//: El encapsulamiento en C++ es lógico, no físico; depende de la disciplina del programador respetarlo.

# Herencia y la Relación en Memoria #

- ¿Cómo se organiza en memoria un objeto de una clase derivada en C++?
R//: Primero se almacenan los atributos de la clase base y después los de la clase derivada.

- ¿Qué sucede si agregamos más niveles de herencia?
R//: Cada nivel añade sus propios atributos después de los de la base, extendiendo el layout de memoria.

- Prompt para ChatGPT: explícame cómo se organiza en memoria un objeto de una clase derivada en C++. ¿Cómo se almacenan los atributos de la clase base y de la derivada?
R//: "En C++, un objeto de una clase derivada se organiza de forma lineal en memoria. Primero se colocan los atributos de la clase base, respetando alineación y padding del compilador, y a continuación se añaden los atributos propios de la clase derivada. De esta forma, la parte de la base siempre está al inicio del objeto, lo que permite que un puntero o referencia a la base pueda apuntar directamente al subobjeto base dentro de la derivada. Si hay herencia múltiple o virtual, el compilador agrega punteros internos (como vptr) para manejar la estructura, lo que puede aumentar el tamaño del objeto."

# Polimorfismo y Vtables en detalle #

- ¿Cómo utiliza el programa las vtables para el polimorfismo?
R//: Usa el puntero a la vtable del objeto para decidir en tiempo de ejecución qué función llamar.

- ¿Cuál es el impacto del polimorfismo en el rendimiento?
R//: Añade una pequeña sobrecarga por la llamada indirecta, pero ofrece gran flexibilidad.

- Prompt para ChatGPT: ¿Cómo funciona el polimorfismo en C++ a nivel interno? Explica cómo se utilizan las vtables para resolver métodos virtuales en una jerarquía de herencia.
R//: "El polimorfismo en C++ se implementa mediante tablas virtuales (vtables). Cuando una clase declara métodos virtuales, el compilador genera una vtable con punteros a las implementaciones de esos métodos. Cada objeto de esa clase contiene un puntero oculto (vptr) que apunta a la vtable correspondiente a su tipo dinámico. En tiempo de ejecución, cuando se invoca un método virtual a través de un puntero o referencia a la clase base, el programa consulta el vptr del objeto, sigue hasta la vtable y ejecuta el método que realmente corresponde a la clase derivada. Esto permite el despacho dinámico de funciones, aunque añade un pequeño costo en memoria (un vptr por objeto) y en rendimiento (un nivel de indirección extra al llamar al método)."

# Reflexion #

- ¿Cómo se implementan internamente el encapsulamiento, la herencia y el polimorfismo?
R//: - Encapsulamiento: se implementa a través de reglas del compilador que controlan el acceso a los miembros (públicos, protegidos, privados). Los miembros privados siguen existiendo en memoria, pero solo pueden ser accedidos por código autorizado.

- Herencia: los atributos de la clase base se colocan primero en memoria, seguidos por los de la derivada. Esto garantiza compatibilidad entre punteros/referencias a la base y a la derivada. En herencia múltiple o virtual, el compilador agrega punteros internos y ajustes de dirección para mantener la coherencia.

- Polimorfismo: se maneja con punteros a tablas virtuales (vtables). Cada objeto con métodos virtuales guarda un puntero oculto (vptr) a la vtable que contiene las direcciones de los métodos concretos que debe ejecutar en tiempo de ejecución.

- Análisis: ventajas y desventajas en términos de eficiencia y complejidad.
R//: Ventajas:
- Encapsulamiento mejora la seguridad y la mantenibilidad del código.
- Herencia promueve la reutilización y organización jerárquica.
- Polimorfismo facilita la extensibilidad y el diseño basado en interfaces.

Desventajas:
- Encapsulamiento no reduce el uso de memoria, solo añade restricciones de acceso.
- Herencia múltiple puede incrementar la complejidad de la memoria y dificultar el mantenimiento.
- Polimorfismo introduce un pequeño costo en memoria (punteros vptr) y en rendimiento (indirección extra en llamadas).
