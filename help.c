#include "Base.c"
void PrincipalHelp()
{
    printf("Integrantes: Maykol Luis Martinez Rodriguez y\n");
    printf("Manuel Alejandro Gamboa Hernandez\n");
    printf("\n");
    printf("Funcionalidades: \n");
    printf("basic: funcionalidades basicas (3 puntos)");
    printf("multi-pipe: multiples tuberias (1 punto)\n");
    printf("help: ayuda (1 punto)\n");
    printf("\n");
    printf("Comandos built-in: \n");
    printf("cd: cambia de directorios\n");
    printf("pwd: muestra el path del directorio en que se encuentra\n");
    printf("exit: termina la ejecucion del shell\n");
    printf("help: muestra esta ayuda\n");
    printf("\n");
    printf("Total: 5.0\n");
}

void BasicHelp()
{
    printf("Nuesto shell cumple las condiciones basicas establecidas \n(o eso espero\n");
    printf("Para ejecutar comandos de la consola se usan fork y exec,\n");
    printf("luego de procesar la entranda y obeter los datos necesarios,\n");
    printf("se le pasan el comando y los argumentos cediendo el control del\n");
    printf("programa.\n");
    printf("Se ha comprobado que funciona con ls, pwd y teoricamente, la mayoria\n");
    printf("de los comandos de la consola\n");
    printf("Los operadores direccionales funcionan cambiando la entrada y salida\n");
    printf("estandar, se han comprobado casos como: \n");
    printf("cat file1 > file2\n");
    printf("cat file1 >> file2\n");
    printf("cat < file\n");
    printf("sort < file\n");
    printf("Las tuberias funcionan de manera similar a la funcion anterior,\n");
    printf("la se cambia la salida estandar de la primera instruccion, se almacena\n");
    printf("y luego se copia a la entrada estandar de la instruccion siguiente\n");
    printf("Se ha probado con: \n");
    printf("cat file.txt | more\n");
}

void MultiPipeHelp()
{
    printf("Segun la estructura del trabajo no habria mucha diferencia entre\n");
    printf("pipe unico o multi-pipe, basicamente la salida estandar de cada \n");
    printf("instruccion se almacena y se pasa como la entrada estandar de la\n");
    printf("siguiente hasta llegar a la ultima, esto se hace con dup2\n");
}
void HelpHelp()
{
    printf("Ofrece informacion basica del programa\n");
    printf("No hay mucho, que explicar, primera vez en mi vida que pongo \n");
    printf("tantos printf seguidos, supongo que habia formas mas elegantes de\n");
    printf("hacerlo pero si algo puede hacerse simple que sea simple\n");
}



