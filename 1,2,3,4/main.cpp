#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
using namespace std;


struct Usuario
{
int UsuarioID;
char FechaCreacion[50];
bool Activo;
float TotalImporteCompras;
char eMail[50];
bool borrado = false;
};

struct Compra
{
int CompraID;
char FechaHora;
float Monto;
int UsuarioID;
int NroArticulo;
};

void cargarUsuario(Usuario &u)
{
    cout << "ID: ";
    cin >> u.UsuarioID;
    fflush(stdin);
    cout << "Fecha: ";
    fgets(u.FechaCreacion, 50, stdin);
    fflush(stdin);
    cout << "Activo (1-si / 2-no): ";
    int act;
    cin >> act;
    if(act == 1)
        u.Activo = true;
    else
        u.Activo = false;
    cout << "Total compras: ";
    cin >> u.TotalImporteCompras;
    fflush(stdin);
    cout << "Correo: ";
    fgets(u.eMail, 50, stdin);
    fflush(stdin);
}

void mostrarUsuario(Usuario u)
{
    cout << "==========================" << endl;
    cout << "ID: " << u.UsuarioID << endl;
    cout << "Fecha creacion: " << u.FechaCreacion;
    cout << "Activo: ";
    if(u.Activo == true)
        cout << "Si" << endl;
    else
        cout << "No" << endl;
    cout << "Total compras: " << u.TotalImporteCompras << endl;
    cout << "Correo: " << u.eMail << endl;
    cout << "==========================" << endl;
}

void buscar_ID(int id)
{
    FILE *f;
    int encontrado = 0;
    Usuario u;
    if(f = fopen("clientes.bin", "rb"))
    {
        while(fread(&u, sizeof(Usuario), 1, f) && !encontrado)
        {
            if(u.UsuarioID == id)
            {
                encontrado = 1;
                cout << "==========================" << endl;
                cout << "ID: " << u.UsuarioID << endl;
                cout << "Fecha creacion: " << u.FechaCreacion;
                cout << "Activo: ";
                if(u.Activo == true)
                    cout << "Si" << endl;
                else
                    cout << "No" << endl;
                cout << "Total compras: " << u.TotalImporteCompras << endl;
                cout << "Correo: " << u.eMail << endl;
                cout << "==========================" << endl;

            }
        }
        fclose(f);
//        return 1;
    }
    return;
}

int buscar_Mail(char mail[])
{
    FILE *f;
    int encontrado =0;
    Usuario u;
    if (f=fopen("clientes.bin","rb"))
    {
        while(fread(&u,sizeof(Usuario),1,f) && !encontrado)
        {
            if (strcmp(mail, u.eMail)==0)
            {
                encontrado = 1;
                cout << "==========================" << endl;
                cout << "ID: " << u.UsuarioID << endl;
                cout << "Fecha creacion: " << u.FechaCreacion;
                cout << "Activo: ";
                if(u.Activo == true)
                    cout << "Si" << endl;
                else
                    cout << "No" << endl;
                cout << "Total compras: " << u.TotalImporteCompras << endl;
                cout << "Correo: " << u.eMail << endl;
                cout << "==========================" << endl;
            }
        }
        if (!encontrado)
            cout << "No se encontro la persona buscada" << endl;
        fclose(f);
        return 1;
    }
    return 0;
}

int borrarConID (int id)
{
    FILE *f;
    int encontrado =0;
    Usuario u;
    if (f=fopen("clientes.bin","rb+"))
    {
        while(!encontrado && fread(&u,sizeof(Usuario),1,f))
        {
            if (u.UsuarioID == id)
            {
                encontrado = 1;
                u.borrado = 1;
                fseek(f,(-1)*sizeof(Usuario), SEEK_CUR);
                fwrite(&u,sizeof(Usuario),1,f);
            }
        }
        if (!encontrado)
            cout << "No se encontro la persona a borrar." << endl;
        fclose(f);
        return 1;
    }
    return 0;
}

void borrador()
{
    FILE *faux;
    FILE *f;
    Usuario u;
    faux = fopen("auxiliar","wb");
    if (f=fopen("clientes.bin","rb+"))
    {
        while(fread(&u,sizeof(Usuario),1,f))
        {
            if (!u.borrado)
            {
                fwrite(&u, sizeof(Usuario),1,faux);
            }
        }
        fclose(f);
    }
    fclose(faux);
    if (!remove("clientes.bin"))
    {
        if(!rename("auxiliar","clientes.bin"))
            cout << "Archivo renombrado exitosamente" << endl;
        else
            cout << "No se pudo renombrar el archivo" << endl;
    }
    else
        cout << "No se pudo borrar el viejo archivo" << endl;
    return;
}

int main()
{
    FILE *clientes = NULL;
    Usuario u;
    int pos = 0;
    int tam = 0;
    int idbusq, menubusq, idborrar;
    char mailbusq[50];
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
                clientes = fopen("clientes.bin", "rb");
                if(clientes != NULL)
                {
                    while(fread(&u, sizeof(Usuario), 1, clientes))
                    {
                        mostrarUsuario(u);
                    }
                    fclose(clientes);
                }

            break;

            case '2':
                clientes = fopen("clientes.bin", "ab");
                if(clientes != NULL)
                {
                    cargarUsuario(u);
                    fwrite(&u, sizeof(Usuario), 1, clientes);
                    fclose(clientes);
                }

                break;
            case '3':
                    cout << "ID del usuario a borrar: ";
                    cin >> idborrar;
                    borrarConID(idborrar);
                    borrador();
                break;
            case '4':
                    cout << "1- Buscar por ID" << endl;
                    cout << "2- Buscar por mail" << endl;
                    cin >> menubusq;
                    if(menubusq == 1)
                    {
                        cout << "ID buscado: ";
                        cin >> idbusq;
                        buscar_ID(idbusq);
                    }
                    if(menubusq == 2)
                    {
                        cout << "Mail buscado: ";
                        fflush(stdin);
                        fgets(mailbusq, 50, stdin);
                        buscar_Mail(mailbusq);
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
