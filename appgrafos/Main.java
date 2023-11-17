package appgrafos;
import java.util.Scanner;

public class Main{

	static{
       	 System.loadLibrary("grafos");
    	}

	public static void main(String[] args){

	JavaGrafos grafo = new JavaGrafos();
	Scanner sc = new Scanner(System.in);

	String cursos = "[\n"
                + "  {\n"
                + "    \"id\": 1006428216,\n"
                + "    \"nombre\": \"Santiago Diaz Franki\",\n"
                + "    \"asignatura\": \"MatemÃ¡ticas\",\n"
                + "    \"cantEstudiantes\": 30,\n"
                + "    \"dia\": 1,\n"
                + "    \"totalHoras\": 4,\n"
                + "    \"bloquePreferido\": 1,\n"
                + "    \"asignado\": 0\n"
                + "  },\n"
                + "  {\n"
                + "    \"id\": 1006428217,\n"
                + "    \"nombre\": \"Juan Perez\",\n"
                + "    \"asignatura\": \"Fisica\",\n"
                + "    \"cantEstudiantes\": 25,\n"
                + "    \"dia\": 1,\n"
                + "    \"totalHoras\": 2,\n"
                + "    \"bloquePreferido\": 1,\n"
                + "    \"asignado\": 0\n"
                + "  },\n"
                + "  {\n"
                + "    \"id\": 1006428218,\n"
                + "    \"nombre\": \"Arnulfo Castrillo\",\n"
                + "    \"asignatura\": \"Programacion\",\n"
                + "    \"cantEstudiantes\": 27,\n"
                + "    \"dia\": 1,\n"
                + "    \"totalHoras\": 2,\n"
                + "    \"bloquePreferido\": 1,\n"
                + "    \"asignado\": 0\n"
                + "  },\n"
                + "  {\n"
                + "    \"id\": 1006428219,\n"
                + "    \"nombre\": \"Juan Carlos Guitierrez\",\n"
                + "    \"asignatura\": \"Analisis Numerico\",\n"
                + "    \"cantEstudiantes\": 30,\n"
                + "    \"dia\": 1,\n"
                + "    \"totalHoras\": 2,\n"
                + "    \"bloquePreferido\": 1,\n"
                + "    \"asignado\": 0\n"
                + "  }\n"
                + "]";
        
        String salas = "[\n"
                + "    {\n"
                + "        \"id\": 101,\n"
                + "        \"nombre\": \"Sala A\",\n"
                + "        \"cantEstudiantes\": 30\n"
                + "    },\n"
                + "    {\n"
                + "        \"id\": 102,\n"
                + "        \"nombre\": \"Sala B\",\n"
                + "        \"cantEstudiantes\": 25\n"
                + "    },\n"
                + "    {\n"
                + "        \"id\": 103,\n"
                + "        \"nombre\": \"Sala C\",\n"
                + "        \"cantEstudiantes\": 30\n"
                + "    }\n"
                + "]";

        /*String curso;
        String salas;

        System.out.println("Ingrese el  JSON de Curso: ");
        curso= sc.nextLine();

        System.out.println("Ingrese el  JSON de Salas: ");
        salas= sc.nextLine();*/

	grafo.asignamientoSalas(cursos, salas);

	}

}
