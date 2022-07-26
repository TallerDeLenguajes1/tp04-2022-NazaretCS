#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>


typedef struct Tarea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}Tarea;

int SolicitarCantidadTareas();
void CargarTareas( Tarea **ArregloTareas, int CantTareas);
void MostrarTarea(Tarea Tarea);
int ConsultarTareas(Tarea **ArregloTareas, Tarea **ArregloTareasRealizadas, int CantTareas);
void MostrarTareasPendientesYRealizadas(Tarea **ArregloTareas, Tarea **ArregloTareasRealizadas, int CantTareas, int realizadas);
void BuscaTareaPalabra(Tarea **ArregloTareas, Tarea **ArregloTarasRealizadas, int CantTareas, int realizadas, char *busqueda);
void BuscarTareaID(Tarea **ArregloTareas, Tarea **ArregloTareasRealizadas, int CantTareas, int realizadas);

int main(void){
    int CantTareas, realizadas;
    Tarea **ArregloTareas, **ArregloTareasRealizadas; 


    CantTareas = SolicitarCantidadTareas();
    ArregloTareas = (Tarea **) malloc(CantTareas * sizeof(Tarea*));

    CargarTareas(ArregloTareas, CantTareas);


    printf("\n\nMostrado de las Tareas A realizarse:\n");
    for (int i = 0; i < CantTareas; i++)
    {
        MostrarTarea(*ArregloTareas[i]);
    }
    printf("\nFin del mostrado de Tareas.\n\n");
    
    ArregloTareasRealizadas = (Tarea **) malloc(CantTareas * sizeof(Tarea*));  //Genera arreglo del mismo tamaño que el anterior, donde se almacenaran las tareas ya realizadas
    
    realizadas = ConsultarTareas(ArregloTareas, ArregloTareasRealizadas, CantTareas);

    BuscaTareaPalabra(ArregloTareas, ArregloTareasRealizadas, CantTareas, realizadas, "Contar");

    LiberarMemoria(ArregloTareas, CantTareas);
    LiberarMemoria(ArregloTareasRealizadas, realizadas);
    return 0;
}



//Funcion para pedir la cantidad de tareas, corrovorando que no sea un numero negativo.
int SolicitarCantidadTareas(){
    int CantTareas;
    do
    {   
        printf("Ingrese la Cantdad de tareas que desea cargar: \n");
        scanf("%d",&CantTareas);
        if (CantTareas<0)
        {
            printf("el numero ingresao no puede ser negativo, por favor intentelo nuevamente...\n");
        }
        
    } while (CantTareas<0);
    return CantTareas;
}

void CargarTareas( Tarea **ArregloTareas, int CantTareas){

    char *buff = (char *) malloc(sizeof(char)*100);

    for (int i = 0; i < CantTareas; i++)
    {
        ArregloTareas[i] = (Tarea *) malloc(sizeof(Tarea)); //Almaceno un espacio de memoria dinamica para los elementos de cada tarea

        ArregloTareas[i]->TareaID = i+1;

        printf("Ingrese una descripcion de la tarea: \n");
        gets(buff);
        ArregloTareas[i]->Descripcion = (char *) malloc((strlen(buff))+1 ); //Almaceno un espacio en memoria para guardar la descripcion de la tarea
        strcpy(ArregloTareas[i]->Descripcion, buff);

        ArregloTareas[i]->Duracion = rand() % (100 -10 ) + 10;

    }
    free(buff);
    
}

void MostrarTarea(Tarea Tarea){
    printf("Mostrado de la Tarea: %d ---------\n", Tarea.TareaID);
    printf(" ID: %d\n",Tarea.TareaID);
    printf("Descripcion de La Tare: ");
    puts(Tarea.Descripcion);
    printf("Duracion de la Tarea: %d \n", Tarea.Duracion);
} 

int ConsultarTareas(Tarea **ArregloTareas, Tarea **ArregloTareasRealizadas, int CantTareas){
    
    int respuesta=2, realizdas=0;

    for (int i = 0; i < CantTareas; i++)
    {
        MostrarTarea(*ArregloTareas[i]);
        do
        {
            printf("\n Si la tarea Mostrada ya fue realizada por favor ingrese  1, en caso contrario ingrese 0\n\n");
            scanf("%d",respuesta);
            if (respuesta != 1 || respuesta != 0)
            {
                printf("El valor ingresado no corresponde con lo solicitado, por favor intentelo nuevamente\n");
            }
            
        } while (respuesta != 1 && respuesta != 0);
        
        if (respuesta == 1)
        {
            ArregloTareasRealizadas[realizdas] = ArregloTareas[i];
            ArregloTareas[i] = NULL;  //Como paso la tarea realizada a un nuevo arreglo, coloco en la posicion donde se encontraba esta un NULL
            realizdas++;
        }
        

    }
    return realizdas;   
}


void MostrarTareasPendientesYRealizadas(Tarea **ArregloTareas, Tarea **ArregloTareasRealizadas, int CantTareas, int realizadas){

    printf("\n\nTareas Realizadadas\n");
    for (int i = 0; i < realizadas; i++)
    {
        MostrarTarea(*ArregloTareasRealizadas[i]);
    }

    printf("\n\nTareas Incompletas\n");
    for (int i = 0; i < CantTareas; i++)
    {
        if (ArregloTareas[i] != NULL)
        {
            MostrarTarea(*ArregloTareas[i]);
        }        
    }
}


void BuscaTareaPalabra(Tarea **ArregloTareas, Tarea **ArregloTarasRealizadas, int CantTareas, int realizadas, char *busqueda)
{

    for(int j = 0; j < CantTareas; j++)
    {
        if(ArregloTareas[j]!=NULL && strstr(ArregloTareas[j]->Descripcion,busqueda)!=NULL)
        {
            MostrarTarea(*ArregloTareas[j]);
            printf("\n Estado de la Tarea: Incompleta\n");
        }
    }

    for(int i = 0; i < realizadas; i++)
    {
        if(strstr(ArregloTarasRealizadas[i]->Descripcion,busqueda)!=NULL)
        {
            MostrarTarea(*ArregloTarasRealizadas[i]);
            printf("\n Estado de la Tarea: Completada\n");
        }
    }
}

void BuscarTareaID(Tarea **ArregloTareas, Tarea **ArregloTareasRealizadas, int CantTareas, int realizadas){

    int buscar=-1;

    do
    {
        printf("\nIngrese el ID de la Tarea que desea uvicar: \n");
        scanf("%d",&buscar);
        if (buscar<=0 && buscar>CantTareas)
        {
            printf("El valor ingresado no se encuentra en el rango de tareas existentes... Por favor intente nuevamente\n");
        }
        
    } while (buscar<=0 && buscar>CantTareas);   
    

    for (int i = 0; i < realizadas; i++)
    {        
        if (ArregloTareasRealizadas[i]->TareaID == buscar)
        {
            printf("\nTarea Localizada:\n\n");
            MostrarTarea(*ArregloTareasRealizadas[i]);
            printf("\nEstado de la Tarea: Realizada\n");
        }
    }

    for (int j = 0; j < CantTareas; j++)
    {        
        if (ArregloTareas[j]->TareaID == buscar && ArregloTareas[j] != NULL) 
        {
            printf("\nTarea Localizada:\n\n");
            MostrarTarea(*ArregloTareas[j]);
            printf("\nEstado de la Tarea: No Realizada\n");
        }
    }
}


void LiberarMemoria(Tarea **ArregloTareas, int cantidad)
{
    for(int i=0; i < cantidad; i++)
    {
        if (ArregloTareas[i]!=NULL)
        {
            free(ArregloTareas[i]->Descripcion); 
        }
        free(ArregloTareas[i]);
    }
    free(ArregloTareas);
}