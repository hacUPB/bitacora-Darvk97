# Actividad 1 #

- ¿Qué son los vértices?
R//: Son los puntos que definen la forma de una figura 3D. Cada vértice tiene una posición en el espacio (x, y, z).

- ¿Con qué figura geométrica se dibuja en 3D?
Con triángulos.

- ¿Qué es un shader?
R//: Es un pequeño programa que se ejecuta en la GPU para controlar cómo se dibujan los gráficos.

- ¿Cómo se le llaman a los grupos de píxeles de un mismo triángulo?
R//: Se les llama fragmentos.

- ¿Qué es un fragment shader?
R//: Es el shader que calcula el color final de cada píxel o fragmento.

- ¿Qué es un vertex shader?
R//: Es el shader que procesa cada vértice, calculando su posición en pantalla y otras propiedades.

- ¿Al proceso de determinar qué pixels del display va a cubrir cada triángulo de una mesh se le llama?
R//: Rasterización.

- ¿Qué es el render pipeline?
R//: Es la serie de pasos que sigue la GPU para convertir modelos 3D en imágenes 2D en pantalla.

- ¿Hay alguna diferencia entre aplicar un color a una superficie de una mesh o aplicar una textura?
R//: Sí, el color es un valor fijo, mientras que una textura es una imagen que se aplica sobre la superficie.

- ¿Cuál es la diferencia entre una textura y un material?
R//: La textura es una imagen, y el material combina varias propiedades como color, brillo o textura.

- ¿Qué transformaciones se requieren para mover un vértice del 3D world al View Screen?
R//: Las transformaciones de modelo, vista y proyección.

- ¿Al proceso de convertir los triángulos en fragmentos se le llama?
R//: Rasterización.

- ¿Qué es el framebuffer?
R//: Es una parte de la memoria donde se guarda la imagen final que se mostrará en pantalla.

- ¿Para qué se usa el Z-buffer o depth buffer en el render pipeline?
R//: Se usa para determinar qué objeto está más cerca de la cámara y evitar que se vean los que están detrás.

- Luego de ver el segundo video entiendes por qué la GPU tiene que funcionar tan rápido y de manera paralela. ¿Por qué?
R//: Porque debe procesar miles o millones de vértices y píxeles al mismo tiempo para generar imágenes en tiempo real.

- ¿Te gustaron los videos?
R//: Sí, ayudan mucho a entender cómo funciona la GPU y el proceso de renderizado.

# Actividad 2 #

- ¿Cómo funciona?
R//: El shader toma los datos de los vértices y píxeles para generar el color final en pantalla.

- ¿Qué resultados obtuviste?
R//: Al comentar el shader, se ve un rectángulo blanco. Con el shader activo, se muestran los efectos definidos en el código del shader.
<img width="1024" height="768" alt="Screenshot 27_10_2025 5_17_44 p  m" src="https://github.com/user-attachments/assets/1974beb9-5a4a-4d23-b4da-8767d72d7fbc" />


- ¿Estás usando un vertex shader?
R//: Sip
<img width="1920" height="1032" alt="01_simpleColorQuadExample (Ejecución) - ofApp cpp - Microsoft Visual Studio 27_10_2025 5_19_34 p  m" src="https://github.com/user-attachments/assets/c40ff5bb-7584-4a2a-8e22-cd9f956bc605" />

- ¿Estás usando un fragment shader?
R//: Sip
<img width="1920" height="1032" alt="01_simpleColorQuadExample (Ejecución) - ofApp cpp - Microsoft Visual Studio 27_10_2025 5_19_26 p  m" src="https://github.com/user-attachments/assets/ba6a1fd9-f873-45d0-b877-5794cca7627b" />

- Analiza el código de los shaders. ¿Qué hace cada uno?
R//: El vertex shader calcula la posición de los vértices, y el fragment shader define el color de cada píxel en pantalla.
<img width="1024" height="768" alt="Screenshot 27_10_2025 5_38_20 p  m" src="https://github.com/user-attachments/assets/c6a96e9a-306c-430b-a5ba-6a2dd80b8e49" />

# Actividad 3 #

- ¿Qué es un uniform?
R//: Es una variable que se envía desde la aplicación al shader y mantiene su valor durante todo el dibujo.

- ¿Cómo funciona el código de aplicación, los shaders y cómo se comunican estos?
R//: La aplicación envía datos (como colores o posiciones) a los shaders mediante uniforms. El vertex y fragment shader usan esos datos para generar el resultado visual.

# Actividad 4 #

- ¿Qué hace el código del ejemplo?
R//: Permite que la imagen o el color cambien según la posición del mouse, agregando interactividad.

- ¿Cómo funciona el código de aplicación, los shaders y cómo se comunican estos?
R//: La aplicación captura datos como la posición del mouse y los envía a los shaders con uniforms. Los shaders usan esa información para cambiar los colores o efectos.

- Realiza modificaciones a ofApp.cpp y al vertex shader para conseguir otros comportamientos.
R//: <img width="1920" height="1032" alt="mySketch - ofApp cpp - Microsoft Visual Studio 29_10_2025 3_02_41 p  m" src="https://github.com/user-attachments/assets/59e57804-f057-44c0-b3ed-31563ba616ff" />
<img width="1920" height="1032" alt="mySketch - ofApp cpp - Microsoft Visual Studio 29_10_2025 3_02_18 p  m" src="https://github.com/user-attachments/assets/d1295e00-a666-4413-91ed-93ef4b715a3b" />

- Realiza modificaciones al fragment shader para conseguir otros comportamientos.
R//: <img width="1920" height="1032" alt="mySketch - ofApp cpp - Microsoft Visual Studio 29_10_2025 3_02_18 p  m" src="https://github.com/user-attachments/assets/537d07de-2c4d-44ef-834f-9789d0df5478" />

asi se ve: 
<img width="1024" height="768" alt="Screenshot 29_10_2025 3_04_19 p  m" src="https://github.com/user-attachments/assets/b27626a5-f48c-4673-b42d-ed6030a4fce0" />

ni idea de porque no agarra 😭
