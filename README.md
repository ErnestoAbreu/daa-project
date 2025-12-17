# Proyecto de Diseño y Análisis de Algoritmos

## Conectando la UH

La Universidad de La Habana (UH), en su constante búsqueda de la excelencia académica y la innovación, se ha embarcado en un proyecto crucial para modernizar y expandir su infraestructura de red. Nuestro objetivo es dotar a todas nuestras facultades, centros de investigación y edificios administrativos con conectividad de fibra óptica de alta velocidad. Para este fin, contamos con el valioso apoyo técnico y logístico de ETECSA (Empresa de Telecomunicaciones de Cuba S.A.).

Nos enfrentamos a un desafío de diseño de red que requiere una solución óptima. Necesitamos interconectar todos los edificios principales de la UH con fibra óptica, creando una red robusta y eficiente. Cada posible conexión de fibra entre dos edificios tiene un costo de instalación asociado, que incluye desde los permisos internos y la mano de obra especializada de ETECSA hasta los materiales y las obras civiles necesarias.

Sin embargo, ETECSA ha establecido una restricción técnica fundamental que debemos respetar:

En cada edificio, la conexión de la fibra óptica se gestionará a través de un equipo de red central (un router o switch principal) que ellos nos proporcionan. Estos equipos tienen una capacidad limitada de puertos. Esto significa que un equipo en un edificio específico solo puede manejar un número máximo de conexiones de fibra óptica directas a otros edificios. Exceder este límite implicaría la necesidad de instalar equipos adicionales mucho más caros y complejos, o la implementación de soluciones de red alternativas que ETECSA no puede garantizar o que dispararían drásticamente el presupuesto del proyecto.

Nuestro objetivo principal es diseñar la red de fibra óptica que conecte todos nuestros edificios principales de la manera más económica posible. Esto implica seleccionar las rutas de fibra de tal forma que:

1. Todos los edificios estén interconectados a la red principal de la universidad, sin crear bucles innecesarios (buscamos una estructura de red eficiente).
2. Ningún equipo de red en ningún edificio exceda su capacidad máxima de conexiones directas (es decir, el número de cables de fibra que llegan o salen de un edificio no puede superar el límite de puertos del equipo de ETECSA).
3. El costo total de instalación de toda la red sea el mínimo posible.

Una planificación subóptima podría resultar en un sobrecosto significativo para la universidad, la necesidad de adquirir hardware de red adicional no previsto, o en una red ineficiente que no cumpla con las especificaciones técnicas y presupuestarias acordadas con ETECSA.


