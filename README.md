_Este proyecto ha sido creado como parte del currículo de 42 por dansanc3, S4nxez._

# Philosophers (Dining Philosophers) — Proyecto 42

## Descripción

Este repositorio contiene una implementación en C del clásico problema de los
"dining philosophers" (filósofos comensales) usando `pthread` y `mutex`. El
objetivo del proyecto es coordinar la concurrencia entre varios hilos (filósofos)
que comparten recursos limitados (tenedores) evitando condiciones de carrera y
deadlocks, y detectando la inanición (muertes) según parámetros temporales.

Breve visión general:

- Cada filósofo es un hilo que repite el ciclo: tomar tenedores → comer →
  dormir → pensar.
- Los tenedores están protegidos por `pthread_mutex_t`.
- Hay un detector de muerte por filósofo que vigila `time_to_die`.
- El programa soporta un parámetro opcional para limitar el número de comidas.

## Instrucciones

Requisitos mínimos:

- Compilador `gcc` en un entorno POSIX (se recomienda WSL en Windows)
- `make` (opcional, se incluye `Makefile`)

Compilar (desde la raíz del repo):

```bash
make
```

Si no dispone de `make` puede compilar manualmente:

```bash
gcc -Wall -Wextra -Werror -g3 -Iinclude/ src/*.c -lpthread -o philo
```

Ejecutar:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [max_meals]
```

Parámetros:

- `number_of_philosophers` — número de filósofos (máx. 200 por validación)
- `time_to_die` — tiempo en ms antes de que un filósofo muera sin comer
- `time_to_eat` — tiempo en ms que tarda en comer
- `time_to_sleep` — tiempo en ms que tarda en dormir
- `max_meals` — (opcional) número de veces que cada filósofo debe comer; si
  se especifica termina cuando todos lo hayan cumplido

Recomendación (Windows): ejecutar desde WSL para disponer de pthreads y un
entorno POSIX compatible.

Ejemplo:

```bash
./philo 4 410 200 200
./philo 4 410 200 200 7   # termina cuando cada filósofo coma 7 veces
```

## Recursos

Referencias y lecturas recomendadas sobre el problema y concurrencia:

- Artículo clásico: Dijkstra, "Dining Philosophers Problem" (1971)
- Pthreads documentation: https://man7.org/linux/man-pages/man7/pthread.7.html
- Tutoriales sobre concurrencia en C y mutexes

Uso de IA en el proyecto:

- Se ha utilizado asistencia de IA (ChatGPT) para análisis, depuración y
  refactorizaciones mínimas con el objetivo de corregir bugs de sincronización
  y adaptar el código para pasar la normativa de estilo (Norminette). La IA se
  usó para: revisar el flujo de ejecución, proponer cambios para evitar
  condiciones de carrera, implementar una función de `ft_usleep` más precisa y
  refactorizar la inicialización de estructuras para reducir parámetros de
  funciones. Ninguna parte crítica del algoritmo (la lógica de toma/soltado de
  tenedores y la detección de muerte) fue alterada conceptualmente; los
  cambios fueron mínimos y documentados en los comentarios de los commits.

## Estructura del proyecto

```text
. /
├── Makefile
├── README.md
├── include/
│   └── philo.h
├── src/
│   ├── ft_atoi.c
│   ├── is_number.c
│   ├── main.c
│   ├── main_helpers.c
│   ├── forks.c
│   ├── philo_functions.c
│   ├── starving.c
│   ├── utils.c
│   └── clean.c
└── obj/
```

## Estado actual

- ✅ Compilación en WSL con `gcc` (`-lpthread`)
- ✅ Detección de muerte y conteo de comidas (opcional)
- ✅ Pruebas manuales de casos críticos (pares/impares) realizadas
- ✅ Formateo y normas: Norminette pasada

Si desea que actualice o añada más documentación (por ejemplo pasos de
debugging, ejemplos de logs o cómo ejecutar con `valgrind`), dime qué prefieres
incluir y lo añado.
