#include <iostream>
#include <stdio.h>
#include <conio.h>
#ifdef _WIN32
#include<windows.h>
#endif
using namespace std;


struct Usuario
{
int UsuarioID;
string FechaCreacion;
bool Activo;
float TotalImporteCompras;
string eMail;
};

struct Compra
{
int CompraID;
char FechaHora;
float Monto;
int UsuarioID;
int NroArticulo;
};

void limpiar_pantalla()
{
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}
void Crear_Archivo()
{
    FILE *archivo;
    archivo = fopen("clientes.bin", "a");
    if(archivo == NULL)
        cout << "Error";
    fclose(archivo);
}

void cargarUsuario(Usuario &u)
{
    cout << "ID: ";
    cin >> u.UsuarioID;
    cout << "Fecha: ";
    cin >> u.FechaCreacion;
    cout << "Activo (1-si / 2-no): ";
    int act;
    cin >> act;
    if(act == 1)
        u.Activo = true;
    else
        u.Activo = false;
    cout << "Total compras: ";
    cin >> u.TotalImporteCompras;
    cout << "Correo: ";
    cin >> u.eMail;
}

void mostrarUsuario(Usuario u)
{
    cout << "******************************** "<<endl;
    cout << "ID: " << u.UsuarioID << endl;
    cout << "Fecha creacion: " << u.FechaCreacion << endl;
    cout << "Activo: ";
    if(u.Activo == true)
        cout << "Si" << endl;
    else
        cout << "No" << endl;
    cout << "Total compras: " << u.TotalImporteCompras << endl;
    cout << "Correo: " << u.eMail << endl;
    cout << "******************************** "<<endl;

}

int busquedaID(Usuario u[], int tam, int id)
{
    int buscado = -1;
    for(int i = 0; i < tam; i++)
    {
      if(u[i].UsuarioID == id)
        buscado = i;
    }
    return buscado;
}

int busquedaMail(Usuario u[], int tam, string mail)
{
    int buscado = -1;
    for(int i = 0; i < tam; i++)
    {
      if(u[i].eMail == mail)
        buscado = i;
    }
    return buscado;
}
int borrarID (Usuario u[], int tam, int idborr)
{



    }




int main()
{
    Crear_Archivo();
    FILE *clientes;
    Usuario usuar[100];
    int pos = 0;
    int tam = 0;
    int idbusq, menubusq,idborr,mailborr;
    string mailbusq;
    char opcion;
    do
    {

        cout << "Elija una opcion" << endl;
        cout << "1 - Mostrar los clientes del archivo Clientes.bin." << endl;
        cout << "2 - Cargar un nuevo cliente." << endl;
        cout << "3 - Desactivar un usuario existente" << endl;
        cout << "4 - Buscar un cliente por ID o por mail."<< endl;
        cout << "5 - Listar todos los clientes activos ordenados por total del importe." <<endl;
        cout << "6 - Procesar un lote de compras." <<endl;
        cout << "7 - Mostrar por pantalla todas las compras realizadas de un cliente dado (desde el archivo procesados.bin)." <<endl;
        cout << "8 - Mostrar todas las compras realizadas entre dos fechas en un reporte escrito en formato html. También mostrar el total de las compras " <<endl;
        cout << "9 - Mostrar el mismo reporte que el punto 8 en formato CSV " <<endl;
        cout << "10 - Finalizar jornada." <<endl;
        cout << "11 - Cargar datos en Clientes.bin." <<endl;

        cout << "esc - Salir" << endl;

        do
        {
            opcion= getch();
        }
        while (opcion!='1' && opcion!='2' && opcion!='3' && opcion!='4' && opcion!=27);
        switch(opcion)
        {
            case '1':
        limpiar_pantalla();
        // LISTAR EL ARCHIVO CON LOS ALUMNOS
        clientes = fopen("clientes.bin", "r+b");
        if(clientes != NULL)
            {
                while(fread(&usuar, sizeof(Usuario), 1, clientes))
                    {
                        for(int j = 0; j<tam; j++)
                            {
                                mostrarUsuario(usuar[j]);
                            }
                            fclose(clientes);
                    }
                    }

                    break;

            case '2':
                limpiar_pantalla();
                cargarUsuario(usuar[pos]);
                tam++;
                pos++;
                clientes = fopen("clientes.bin", "wb");
                if(clientes != NULL)
                    {
                        fwrite(&usuar, sizeof(Usuario), 1, clientes);
                        fclose(clientes);
                    }
                limpiar_pantalla();
                break;
            case '3':
                clientes = fopen("clientes.bin", "rb");
                        if(clientes != NULL)
                            {
                                while(fread(&usuar, sizeof(Usuario), 1, clientes))
                                {
                                    cout << "1- Borrar por ID" << endl;
                                    cout << "2- Borrar por mail" << endl;
                                    cin >> menubusq;
                                    if(menubusq == 1)
                                    {
                                        cout << "******************************** "<<endl;
                                        cout << "ID a borrar: ";
                                        cin >> idborr;


                                       cout << "******************************** "<<endl;
                                    }
                                    if(menubusq == 2)
                                    {
                                        cout << "******************************** "<<endl;
                                        cout << "Mail buscado: "<<endl;
                                        cin >> mailborr;

                                        cout << "******************************** "<<endl;
                                    }
                                }
                                fclose(clientes);
                            }
        break;
                break;

            case '4':
                        clientes = fopen("clientes.bin", "rb");
                        if(clientes != NULL)
                            {
                                while(fread(&usuar, sizeof(Usuario), 1, clientes))
                                {
                                    cout << "1- Busqueda por ID" << endl;
                                    cout << "2- Busqueda por mail" << endl;
                                    cin >> menubusq;
                                    if(menubusq == 1)
                                    {
                                        cout << "******************************** "<<endl;
                                        cout << "ID buscado: ";
                                        cin >> idbusq;
                                        mostrarUsuario(usuar[busquedaID(usuar, tam, idbusq)]);
                                       cout << "******************************** "<<endl;
                                    }
                                    if(menubusq == 2)
                                    {
                                        cout << "******************************** "<<endl;
                                        cout << "Mail buscado: "<<endl;
                                        cin >> mailbusq;
                                        mostrarUsuario(usuar[busquedaMail(usuar, tam, mailbusq)]);
                                        cout << "******************************** "<<endl;
                                    }
                                }
                                fclose(clientes);
                            }
                break;

             case '5':

                break;

              case '6':

                break;

                case '7':

                break;

               case '8':

                break;

                 case '9':

                break;

                 case '10':

                break;




        }


    }while (opcion!= 27);
    getch();
    return 0;
}
