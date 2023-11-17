#include <jni.h>
/*
 * Class:     appgrafos_JavaGrafos
 * Method:    asignamientoSalas
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <cjson/cJSON.h>

// Estructura del curso (Informacion de la persona que reservara la sala)
typedef struct
{

    int ID;                // Cedula de profesor (Para identificar)
    char *Nombre;          // Nombre de profesor
    char *Asignatura;      // Asignatura de profesor,
    int TamañoCurso;       // Nuevo miembro para el tamaño de curso
    int Dia;               // Dia que el profesor desea dar sus clases
    int CantidadHoras;     // Cantidad de horas totales del curso del profesor
    int BloquePreferencia; // Bloque horario del profesor
    int asignado;          // Identificador para no repetir ciclos (Posibilidad de eliminar esta variable)

} Curso;

// Estructura de salas (Toda la informacion de las salas que se reservaran)
typedef struct
{

    int ID;               // Identificador de la sala a la que se desea acceder
    char *Nombre;         // Nombre de la sala
    int CapacidadAlumnos; // Capacidad de alumnos de la sala

} Sala;

// Estructura de asignacion de salas con respecto a profesores (Informacion de identificacion de la asignacion con ID de profesor e ID de sala y su bloque horario)
typedef struct
{

    int ID_profesor;    // Identificador de profesor asignado
    int ID_sala;        // Identificador de sala asignada
    int BloqueAsignado; // Bloque horario asignado a dicha sala y profesor
    int DiaAsignado;    // Dia asignado para el profesor y la sala

} Asignacion;
JNIEXPORT void JNICALL Java_appgrafos_JavaGrafos_asignamientoSalas
  (JNIEnv * env, jobject obj, jstring JsonCurso, jstring JsonSala){
  // Convertir jstring a char para jsonCursos
    const char *jsonCurso = (*env)->GetStringUTFChars(env, JsonCurso, NULL);

    // Convertir jstring a char para jsonSalas
    const char *jsonSala = (*env)->GetStringUTFChars(env, JsonSala, NULL);

    cJSON *json_1 = cJSON_Parse(jsonCurso);
    cJSON *json_2 = cJSON_Parse(jsonSala);

    int numCursos = cJSON_GetArraySize(json_1);
    Curso *cursos = (Curso *)malloc(numCursos * sizeof(Curso));
    for (int i = 0; i < numCursos; i++)
    {
        // Obtener el objeto actual
        cJSON *objetoJSON = cJSON_GetArrayItem(json_1, i);
        // Obtener valores del objeto JSON
        int id = cJSON_GetObjectItem(objetoJSON, "id")->valueint;
        char *nombre = cJSON_GetObjectItem(objetoJSON, "nombre")->valuestring;
        char *asignatura = cJSON_GetObjectItem(objetoJSON, "asignatura")->valuestring;
        int cantEstudiantes = cJSON_GetObjectItem(objetoJSON, "cantEstudiantes")->valueint; //******
        int dia = cJSON_GetObjectItem(objetoJSON, "dia")->valueint;
        int totalHoras = cJSON_GetObjectItem(objetoJSON, "totalHoras")->valueint;
        int bloquePreferido = cJSON_GetObjectItem(objetoJSON, "bloquePreferido")->valueint;
        int asignado = cJSON_GetObjectItem(objetoJSON, "asignado")->valueint;

        // Asignar valores al objeto en el array dinámico
        cursos[i].ID = id;
        cursos[i].Nombre = strdup(nombre);
        cursos[i].Asignatura = asignatura;
        cursos[i].TamañoCurso = cantEstudiantes;
        cursos[i].Dia = dia;
        cursos[i].CantidadHoras = totalHoras;
        cursos[i].BloquePreferencia = bloquePreferido;
        cursos[i].asignado = asignado;
    }

    int numSalas = cJSON_GetArraySize(json_2);
    Sala *salas = (Sala *)malloc(numSalas * sizeof(Sala));
    for (int k = 0; k < numSalas; k++)
    {
        // Obtener el objeto actual
        cJSON *objetoJSON = cJSON_GetArrayItem(json_2, k);

        // Obtener valores del objeto JSON
        int id = cJSON_GetObjectItem(objetoJSON, "id")->valueint;
        char *nombre = cJSON_GetObjectItem(objetoJSON, "nombre")->valuestring;
        int cantEstudiantes = cJSON_GetObjectItem(objetoJSON, "cantEstudiantes")->valueint;

        // Asignar valores al objeto en el array dinámico
        salas[k].ID = id;
        salas[k].Nombre = strdup(nombre);
        salas[k].CapacidadAlumnos = cantEstudiantes;
    }

    int numAsignaciones = 0;
    Asignacion *asignaciones = NULL;
    asignaciones = (Asignacion *)malloc(sizeof(Asignacion));

    for (int i = 0; i < numCursos; i++)
    {
        bool permitido = true;
        for (int j = 0; j < numSalas; j++)
        {
            if (cursos[i].TamañoCurso <= salas[j].CapacidadAlumnos)
            {

                for (int k = 0; k <= numAsignaciones; k++)
                {
                    if (cursos[i].Dia == asignaciones[k].DiaAsignado)
                    {

                        if (asignaciones[k].BloqueAsignado == cursos[i].BloquePreferencia)
                        {
                            permitido = false;
                        }
                    }
                }

                if (permitido)
                {
                    asignaciones[numAsignaciones].ID_profesor = cursos[i].ID;
                    asignaciones[numAsignaciones].ID_sala = salas[j].ID;
                    asignaciones[numAsignaciones].DiaAsignado = cursos[i].Dia;
                    asignaciones[numAsignaciones].BloqueAsignado = cursos[i].BloquePreferencia;
                    numAsignaciones++;
                    asignaciones = (Asignacion *)realloc(asignaciones, (numAsignaciones + 1) * sizeof(Asignacion));
                }
            }
        }
    }

    for (int i = 0; i < numAsignaciones; i++)
    {
        printf("Asignacion %d:\n", i + 1);
        printf("ID del profesor: %d\n", asignaciones[i].ID_profesor);
        printf("ID de la sala: %d\n", asignaciones[i].ID_sala);
        printf("Bloque asignado: %d\n", asignaciones[i].BloqueAsignado);
        printf("Dia asignado: %d\n\n", asignaciones[i].DiaAsignado);
    }
}

