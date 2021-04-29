#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INFINITY 9999999
#define MAX 41

///////////GRAFO///////////////////
int elArchivoExiste();
void borrarNuevoGrafo();

void leerArchivo(int grafo[MAX][MAX], int lineas[MAX][3]);
void crearNuevoArchivo(int grafo[MAX][MAX], int lineas[MAX][3]);
void imprimirGrafo(int grafo[MAX][MAX]);
//////FIN GRAFO//////////


void bienvenida();
int menuPrincipal();
void verId();
void intefazPersonal(int grafo[MAX][MAX], int lineas[MAX][3]);
int modificarTiempo(int grafo[MAX][MAX]);
void intefazUsuario(int grafo[MAX][MAX], int lineas[MAX][3]);
void buscarRuta(int grafo[MAX][MAX], int lineas[MAX][3]);
void dijkstra(int grafo[MAX][MAX], int origen, int destino);
void nombresEstaciones(int indice);
void nombresEstaciones(int indice);
void formatoMinutos(int tiempo);
/////////////GENERAL/////////////////////
int valInt(char aux[10]);//VALIDADOR DE ENTEROS
float valFloat(char aux[10]);
void pause();

int main()
{
	//OBTENER GRAFO
	int grafo[41][41];
	int lineas[41][3];
	int i, j;
	leerArchivo(grafo, lineas);
	bienvenida();
	system("cls");
	//crearNuevoArchivo(grafo, lineas);

	int opcion; 
	do {
		opcion = menuPrincipal();
		switch(opcion) {
			case 1://Intefaz personal
				system("cls");
				intefazPersonal(grafo, lineas);
				break;
			case 2://Interfaz usuario Metro
				system("cls");
				intefazUsuario(grafo, lineas);
				break;
			case 3://SALIR
				system("cls");
				break;
		}
		system("cls");
	} while(opcion != 3);
	
	system("cls");
	printf("\n\n\n\n \t\t\tFIN DEL PROGRAMA \n\n\n");
	pause();
	return 0;
}

//Bienvenida
void bienvenida()
{
	printf("\n\n\n\n");
	printf("\n\n\t\t\t BIENVENIDO AL METRO DE LA CIUDAD DE MEXICO\n\n\t\t\t");
	printf(" PRESIONE UNA TECLA PARA INICIAR: ");
	getch();
}

//MENU PRINCIPAL
int menuPrincipal() {
	printf("\n\n\t\t MENU PRINCIAL: \n");
	printf("\n 1) Personal administrativo");
	printf("\n 2) Usuario del metro");
	printf("\n 3) SALIR");
	char aux[10];
	int opcion;
	do {
		printf("\n\n Elija una opcion: ");
		fflush(stdin);
		gets(aux);
		opcion = valInt(aux);
	} while(opcion < 1 || opcion > 3);
	return opcion;
}

void verId() {
	printf("\n\n\t\tID DE LAS ESTACIONES\n");
	int i;
	for(i = 0; i < MAX; i++) {
		printf("\n\n ");
		nombresEstaciones(i+1);
		printf(" = %d", i + 1);
	}
	
	
}

void intefazPersonal(int grafo[41][41], int lineas[41][3]) {
	int opcion, cambios;	
	do {
		printf("\n\n\t\t INTERFAZ PARA EL PERSONAL ADMINISTRATIVO: \n");
		printf("\n 1) Modificar un tiempo ");
		printf("\n 2) Imprimir grafo ");
		printf("\n 3) Reiniciar grafo");
		printf("\n 4) Ver id de las estaciones");
		printf("\n 5) Regresar ");
		char aux[10];
		
		do {
			printf("\n\n Elija una opcion: ");
			fflush(stdin);
			gets(aux);
			opcion = valInt(aux);
		} while(opcion < 1 || opcion > 5);
		switch(opcion) {
			case 1://Mofificar un tiempo
				system("cls");
				cambios = modificarTiempo(grafo);
				if(cambios) {
					crearNuevoArchivo(grafo, lineas);
				}
				break;
			case 2://Imprimir grafo
				system("cls");
				imprimirGrafo(grafo);
				pause();
				break;
			case 3://REIniciar
				system("cls");
				borrarNuevoGrafo();
				leerArchivo(grafo, lineas);
				printf("\n\n EL GRAFO SE REINICIO");
				pause();
				break;
			case 4://VEr id
				system("cls");
				verId();
				pause();
				break;
			case 5://SALIR
				break;
		}
		system("cls");
	} while(opcion != 5);
	
	system("cls");

}


void imprimirGrafo(int grafo[MAX][MAX]) {
	int i, j;
	printf("\n\n Estacion\t\t\tADYACENCIAS (TIEMPO)\n");
	for(i = 0; i < MAX; i++) {
		printf("\n%2d       ", i+1);
		for(j = 0; j < MAX; j++) {
			if(grafo[i][j] != 0 && grafo[i][j] != INFINITY) {
				printf("    --> %2d (%.4f)", j+1, (float)grafo[i][j] / 10000);
			}
		}
	}
}


int modificarTiempo(int grafo[MAX][MAX]) {
	int origen, destino, i;
	float tiempoActual, nuevoTiempo;
	char aux[10];
	printf("\n\n PARA MODIFICAR UN TIEMPO, LAS ESTACIONES DEBEN SER ADYACENTES:");

	do {
		printf("\n\n Elija la estacion de origen: ");
		fflush(stdin);
		gets(aux);
		origen = valInt(aux);
	} while(origen < 1 || origen > 41);
	
	do {
		printf("\n\n Elija la estacion de destino: ");
		fflush(stdin);
		gets(aux);
		destino = valInt(aux);
	} while(destino < 1 || destino > 41 || destino == origen);
	
	if(grafo[origen-1][destino-1] != INFINITY && grafo[origen-1][destino-1] != 0) {
		
		printf("\n\n Tiempo Actual de %d a %d = %.4f minutos", origen, destino, (float)grafo[origen - 1][destino - 1] / 10000);
		
		do {
			printf("\n\n Introduzca el nuevo tiempo: ");
			fflush(stdin);
			gets(aux);
			nuevoTiempo = valFloat(aux);
		} while(nuevoTiempo <= 0);
		
		//Modificael el tiempo
		grafo[origen - 1][destino - 1] = (int)(nuevoTiempo * 10000);
	
		printf("\n\n SE ACTUALIZO EL TIEMPO\n");
		
		pause();
		return 1;	
	} else {
		printf("\n\n\n\n ESOS DOS NODOS NO TIENEN CONEXION DIRECTA");
		pause();
		return 0;
	}	


}




void intefazUsuario(int grafo[MAX][MAX], int lineas[MAX][3]) {
	
	int opcion, cambios;	
	do {
		printf("\n\n\t\t INTERFAZ PARA EL USUARIO DEL METRO: \n");
		printf("\n 1) Buscar una ruta");
		printf("\n 2) Ver id de las estaciones ");
		printf("\n 3) Regresar");
		char aux[10];
		
		do {
			printf("\n\n Elija una opcion: ");
			fflush(stdin);
			gets(aux);
			opcion = valInt(aux);
		} while(opcion < 1 || opcion > 3);
		switch(opcion) {
			case 1://Mofificar un tiempo
				system("cls");
				buscarRuta(grafo, lineas);
				break;
			case 2://VER IDS
				system("cls");
				verId();
				pause();
				break;
			case 3:
				break;
		}
		system("cls");
	} while(opcion != 3);
		
	system("cls");
	
}



void buscarRuta(int grafo[MAX][MAX], int lineas[MAX][3]) {
	
	int origen, destino, i;
	char aux[10];
	printf("\n\n BUSCAR RUTA:\n");

	do {
		printf("\n Elija la estacion de origen [id]: ");
		fflush(stdin);
		gets(aux);
		origen = valInt(aux);
	} while(origen < 1 || origen > 41);
	
	do {
		printf("\n Elija la estacion de destino [id]: ");
		fflush(stdin);
		gets(aux);
		destino = valInt(aux);
	} while(destino < 1 || destino > 41 || destino == origen);
	
	dijkstra(grafo, origen -1, destino -1);
	
	pause();
	
}


void dijkstra(int grafo[MAX][MAX], int origen, int destino) {
	int costo[MAX][MAX], distancia[MAX],pred[MAX];
	int visitado[MAX], cont, minDistancia, siguienteNodo, i , j, k, ruta[MAX], tamanioRuta = 0;
	
	//pred[] guarda el predecesor de cada vertice
	//cont almacena el número de vértices vistos en total
	//crea la matriz de costos
	for(i = 0; i < MAX; i++) {
		for(j = 0; j < MAX; j++) {
			costo[i][j] = grafo[i][j];
		}
	}
	
	//inicializa pred[],distancia[] y visitado[]
	for(i = 0; i < MAX; i++) {
		distancia[i] = costo[origen][i];
		pred[i] = origen;
		visitado[i] = 0;
	}
	
	distancia[origen] = 0;
	visitado[origen] = 1;
	cont = 1;
	
	while(cont < MAX - 1) {
		minDistancia = INFINITY;
		
		//siguienteNodo da el vertice más cercano
		for(i = 0; i < MAX; i++) {
			if(distancia[i] < minDistancia && !visitado[i]){
				minDistancia = distancia[i];
				siguienteNodo = i;
			}
		}
			
		//verifica si existe un mejor camino a través de siguienteNodo			
		visitado[siguienteNodo] = 1;
		for(i = 0; i < MAX; i++) {
			if(!visitado[i]) {
				if(minDistancia + costo[siguienteNodo][i] < distancia[i]) {
					distancia[i] = minDistancia + costo[siguienteNodo][i];
					pred[i] = siguienteNodo;
				}
			}
		}
		cont++;
	}
 
	//Imprime el camino y la distancia de cada vertice
	for( i = 0; i < MAX; i++) { 
		if(i != origen && i == destino) { //PARA QUE SOLO IMPRIMA LA RUTA DEL DESTINO
			printf("\n\n\n Tiempo estimado de ");
			nombresEstaciones(origen + 1);
			printf(" a ");
			nombresEstaciones(destino + 1);
			printf(" = ");
			//printf("%d",(int)round((float)(distancia[i]) / 10000)); 
			formatoMinutos(distancia[i]);
			//printf(" minutos");
			printf("\n\n Ruta = ");
			
			j = i;
			do {
				j = pred[j];
				ruta[tamanioRuta] = j;
				tamanioRuta++;
			}while(j != origen);
			for(k = tamanioRuta-1; k >= 0; k--) {
				printf(" ");
				nombresEstaciones(ruta[k] + 1);
				printf(" -->");
			}
			printf(" ");
			nombresEstaciones(i+1);
			
			printf("\n");
		}		
	}
}

//////////////////////////////////////////////ARCHIVOS//////////////////////////////////////////////////



void crearNuevoArchivo(int grafo[41][41], int lineas[41][3]) {
	FILE *nuevoGrafo;
	nuevoGrafo = fopen("nuevoGrafo.txt","wt");
	int i, j, conexiones;
	fprintf(nuevoGrafo,"ORIG(ID)  PERTENECE CONEXS    ID        PESO      \n");
	for(i = 0; i < MAX; i++) {
		conexiones = 0;
		for(j = 0; j < MAX; j++) {
			if(grafo[i][j] != 0 && grafo[i][j] != INFINITY) {
				conexiones++;
			}
		}
		
		fprintf(nuevoGrafo,"%2d        %d%d%d       %2d        ", i+1, lineas[i][0], lineas[i][1], lineas[i][2], conexiones);
		for(j = 0; j < MAX; j++) {
			if(grafo[i][j] != 0 && grafo[i][j] != INFINITY) {
				fprintf(nuevoGrafo,"%2d        %5d     ", j+1, grafo[i][j]);				
			}
		}
		if(i != 40)
			fprintf(nuevoGrafo,"\n");
	}

	fclose(nuevoGrafo);
	
	
}


void leerArchivo(int grafo[MAX][MAX], int lineas[MAX][3]) {
	FILE *estaciones;
	if(elArchivoExiste()) {
		estaciones = fopen("nuevoGrafo.txt","rt");
	} else {
		estaciones = fopen("estaciones.txt","rt");
	}	
	rewind(estaciones);
	char aux[11];
	int i, j;
	for(i = 0; i < 5; i++) {
		fgets(aux, 11, estaciones);
		//printf("%s|", aux);//Visualizar si funciona
	}
	fputs("\n",estaciones);
	int conexiones, id, peso;
	for(i = 0; i < MAX; i++) {
		fgets(aux, 11, estaciones);
		
		for(j = 0; j < 3; j++) {
			fgets(aux, 2, estaciones);
			lineas[i][j] = atoi(aux);
		}
		fgets(aux, 8, estaciones);
		fgets(aux, 11, estaciones);
		conexiones = atoi(aux);
		for(j = 0; j < MAX; j++) {
			grafo[i][j] = 0;
		}
		for(j = 0; j < conexiones; j++) {
			fgets(aux, 11, estaciones);
			id = atoi(aux);
			fgets(aux, 11, estaciones);
			grafo[i][id - 1] = atoi(aux);
		}	
		fputs("\n",estaciones);
		//printf("\n%d%d%d%10d", grafo[i].lineas[0], grafo[i].lineas[1], grafo[i].lineas[2], conexiones);
	}	
	
	//RELLENAR CON INFINITY
	for(i = 0; i < MAX; i++) {
		for(j = 0; j < MAX; j++) {
			if(grafo[i][j] == 0 && i != j) {
				grafo[i][j] = INFINITY;
			}
		}
	}
	
}


int elArchivoExiste() {
	FILE *nuevoGrafo;
	nuevoGrafo = fopen("nuevoGrafo.txt","rt");
	int existe;
	if(nuevoGrafo == NULL) {
		existe = 0;

	} else {
		fseek( nuevoGrafo, 0, SEEK_END );
		if(ftell(nuevoGrafo) == 0){ 
			existe = 0;
		} else {
			existe = 1;
		}
	}
	fclose(nuevoGrafo);	
	return existe;
}


void borrarNuevoGrafo() {
	FILE *nuevoGrafo;
	nuevoGrafo = fopen("nuevoGrafo.txt","wt");
	fclose(nuevoGrafo);
}


///////////////////////////////////////////////VALIDACIONES///////////////////////////////////////////////////////////////

//Funcion para validar enteros
int valInt(char aux[10]) {
	int i, n, lon, flag=1;
	lon=strlen(aux);
	for(i=0;i<lon;i++)
	{
		if(isdigit(aux[i]))
			flag=1;
		else
			flag=0;
		if(flag==0)
			break;
	}
	if (lon==0)
		flag=0;
	if(flag==1)
		n=atoi(aux);
	else if(flag==0)
		n=-1;
	return n;
}

//Funcion para validar flotantes
float valFloat(char aux[10]) {
	int i, lon, flag, punto=0;
	float n;
	lon=strlen(aux);
	for(i=0;i<lon;i++)
	{
		if(isdigit(aux[i])||aux[i]=='.')
		{
			flag=1;
			if(aux[i]=='.')
				punto++;
		}
		else
			flag=0;
		if(flag==0||punto>1)
		{
			flag=0;
			break;
		}
	}
	if(lon==0)
		flag==0;
	if(flag==1)
		n=atof(aux);
	else if(flag==0)
		n=-1;
	return n;
}


//Funcion de pausa
void pause() {
	printf("\n\n Presiones una tecla para continuar: ");
	getch();
	fflush(stdin);
}



void nombresEstaciones(int indice) {
	switch(indice) {
		case 1:
			printf("Cuahutemoc");
			break;
		case 2:
			printf("Balderas");
			break;
		case 3:
			printf("Salto de Agua");
			break;
		case 4:
			printf("Isabel la Catolica");
			break;
		case 5:
			printf("Pino Suarez");
			break;
		case 6:
			printf("Merced");
			break;
		case 7:
			printf("Candelaria");
			break;
		case 8:
			printf("San Lazaro");
			break;
		case 9:
			printf("Moctezuma");
			break;
		case 10:
			printf("Revolucion");
			break;
		case 11:
			printf("Hidalgo");
			break;
		case 12:
			printf("Bellas Artes");
			break;
		case 13:
			printf("Allende");
			break;
		case 14:
			printf("Zocalo");
			break;
		case 15:
			printf("San Antonio Abad");
			break;
		case 16:
			printf("Chabacano");
			break;
		case 17:
			printf("Viaducto");
			break;
		case 18:
			printf("Chilpancingo");
			break;
		case 19:
			printf("Centro Medico");
			break;
		case 20:
			printf("Lazaro Cardenas");
			break;			
		case 21:
			printf("Jamaica");
			break;
		case 22:
			printf("Mixiuhca");
			break;
		case 23:
			printf("Canal del Norte");
			break;
		case 24:
			printf("Morelos");
			break;
		case 25:
			printf("Fray Servando");
			break;
		case 26:
			printf("Santa Anita");
			break;
		case 27:
			printf("Buena Vista");
			break;
		case 28:
			printf("Guerrero");
			break;
		case 29:
			printf("Garibaldi");
			break;
		case 30:
			printf("Lagunilla");
			break;
		case 31:
			printf("Tepito");
			break;
		case 32:
			printf("Flores Magon");
			break;
		case 33:
			printf("Juarez");
			break;
		case 34:
			printf("Ni%cos Heroes", 164);
			break;
		case 35:
			printf("Hospital General");
			break;
		case 36:
			printf("Etiopia");
			break;
		case 37:
			printf("San Juan de Letran");
			break;
		case 38:
			printf("Doctores");
			break;
		case 39:
			printf("Obrera");
			break;
		case 40:
			printf("La Viga");
			break;
		case 41:
			printf("Coyuya");
			break;			
	}
}



void formatoMinutos(int tiempo) {
	
	int minutos, segundos;
	float segundosDecima;
	minutos = tiempo / 10000;
	
	segundosDecima = ((float)tiempo / 10000) - minutos;
	segundos = segundosDecima * 60;
	
	printf("%d minutos %d segundos: ", minutos, segundos);
	
}
