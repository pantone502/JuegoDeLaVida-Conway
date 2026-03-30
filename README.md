# JuegoDeLaVida-Conway
Tarea de Programación I - Implementación del Juego de la Vida de Conway en C++ con interfaz de consola.
# 🧬 Tarea: El Juego de la Vida (Conway) en C++

Este repositorio contiene mi implementación del **Juego de la Vida** para la clase de Programación I. No es solo una matriz de texto; diseñé la interfaz para que parezca una terminal de simulación real con un estilo retro "hacker".

## 🧠 Lógica del Juego
El sistema se basa en un autómata celular donde cada celda evoluciona según estas reglas:
- **Nacimiento:** Una celda muerta con exactamente 3 vecinos vivos nace.
- **Muerte:** Una celda viva con menos de 2 (soledad) o más de 3 (sobrepoblación) vecinos muere.
- **Supervivencia:** Una celda viva con 2 o 3 vecinos vivos permanece viva.

## 🛠️ Notas de mi proceso (Autoevaluación y Aprendizaje)

Para esta tarea, me enfoqué en resolver problemas técnicos que surgieron durante el desarrollo:

* **Simetría Visual (El truco de los "Pixeles"):** Al principio, las células se veían como rectángulos altos debido al espaciado de la terminal. Para que se vieran como cuadrados reales, decidí **imprimir el carácter ASCII 219 dos veces seguidas**. Esto ajustó la relación de aspecto y logré que el mapa se vea perfectamente simétrico.

* **El problema de la Sincronización (Matriz Espejo):** Me di cuenta de que si actualizaba las células directamente en el tablero principal, los cambios de una celda afectaban el conteo de vecinos de la siguiente en el mismo turno. Para solucionar esto, use una **copia del tablero (proximaGen)**. Así, proceso toda la generación "en el aire" y luego actualizo el tablero principal de un solo golpe.

* **Gestión de Memoria Dinámica:** Use `std::vector<std::vector<int>>` en lugar de arreglos estáticos. Esto me permitió que el usuario defina el tamaño del mapa en tiempo de ejecución, haciendo el programa mucho más flexible.

* **Inspiración y Teoría:** Investigué en el canal de **Dot CSV** sobre la lógica de este juego. Me llamó mucho la atención el concepto de **Mundo Toroidal** (bordes conectados como en Pac-Man). Aunque para esta tarea mantuve los bordes fijos por las instrucciones, aprendí cómo el operador módulo `%` ayuda a conectar los límites del mapa.

## 💻 Detalles Técnicos
- **Modularidad:** El código está separado en funciones claras: `inicializar`, `calcular`, `actualizar` e `imprimir`.
- **Control de Consola:** Apliqué `system("color 0A")` para el color verde neón y la librería `<windows.h>` para usar `Sleep()`, controlando la fluidez de la animación.
- **Nomenclatura:** Respeté el estándar pedido: `snake_case` para funciones y `camelCase` para variables locales.

---
*Tarea realizada por Leo - Estudiante de Programación I*
