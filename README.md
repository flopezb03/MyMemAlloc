# MyMemAlloc

Proyecto en C para escribir un __memory allocator__ muy simple. En este proyecto se redefinen las funciones `malloc()`, `free()`, `calloc()` y `realloc()`. Internamente se usa la llamada al sistema `sbrk()` para modificar el _program break_, que es un puntero que apunta al final del __heap__.

## Build
Compilación manual:
```
gcc -Wall -Wextra -fPIC -shared -Iinclude src/my_mem_alloc.c -o lib/my_mem_alloc.so
```
- [x] Makefile
- [ ] CMake

## Test
Se puede probar el funcionamiento usando:
 ```
 LD_PRELOAD=$PWD/lib/my_mem_alloc.so ls
 ```
Esto llamará al comando `ls` pero antes cambiará la variable de entorno `LD_PRELOAD` que cargará la libreria dinámica que se ha creado antes que el resto de librerías. Por lo tanto, `ls` usará las funciones implementadas en este proyecto.