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
int FechaCreacion;
bool Activo;
float TotalImporteCompras=0;
char eMail[50];
bool borrado = false;
};

struct Compra
{
int CompraID;
int FechaHora;
float Monto;
int UsuarioID;
int NroArticulo;
bool borrado = false;
};

struct Nodo
{
    Usuario info;
     Nodo *sgte;
};

struct NodoCompras
{
    Compra info;
    NodoCompras *sgte;
};


void cargarUsuario(Nodo *&lista);
void mostrarUsuario(Usuario u);
void buscar_ID(int id);
Usuario buscar_ID1(int id);
int buscar_Mail(char mail[]);
void desactivar_con_ID (Nodo *&listausuario, int id);
void borrador();
void InsertarSiguiente(Nodo *&n, Usuario x);
void InsertarSiguienteCompras(NodoCompras *&n, Compra x);
Nodo *BuscarNodoAnterior(Nodo *inicial, Nodo *anterior_a);
Nodo *ObtenerUltimo(Nodo *p);
NodoCompras *ObtenerUltimoCompras(NodoCompras *p);
void InsertarAlFinal(Nodo *&inicial, Usuario x);
void InsertarAlFinalCompras(NodoCompras *&inicial, Compra x);
void InsertarPrimero(Nodo *&inicial, Usuario x);
void InsertarOrdenado(Nodo *&inicial, Usuario x);
Nodo *ObtenerSiguiente(Nodo *n);
NodoCompras *ObtenerSiguienteCompras(NodoCompras *n);
void MostrarLista(Nodo *lista);
void MostrarListaCompras(NodoCompras *lista);
void OrdenarCompras(Usuario u);
void CargarCompra(Compra &c);
void MostrarCompra(Nodo *lista);
void InsertarCompraEnLista (NodoCompras *&n, Compra x);
void InsertarUsuarioEnLista (Nodo *&n, Usuario x);
void ProcesarLoteDeCompras(Nodo *ListaUsuario, NodoCompras *&ListaCompras);
void MostrarCompraCliente(int id);

void levantarUsuario(Nodo *&lista){
    FILE *f=NULL;
    Usuario u;
    f=fopen("clientes.bin","rb");
    if(f!=NULL){
        while(fread(&u,sizeof(Usuario),1,f)){
            InsertarAlFinal(lista,u);
        }

    }
    fclose(f);



}

void cargarUsuario(Nodo *&lista)
{
    Usuario u;
    cout << "ID: ";
    cin >> u.UsuarioID;
    fflush(stdin);
    cout << "Fecha: ";
    cin >> u.FechaCreacion;
    fflush(stdin);
    cout << "Activo (1-si / 2-no): ";
    int act;
    cin >> act;
    if(act == 1)
        u.Activo = true;
    else
        u.Activo = false;
          fflush(stdin);
    cout << "Correo: ";
    fgets(u.eMail, 50, stdin);
    fflush(stdin);
    InsertarAlFinal(lista,u);

}

void mostrarUsuario(Usuario u)
{
    cout << "==========================" << endl;
    cout << "ID: " << u.UsuarioID << endl;
    cout << "Fecha creacion: " << u.FechaCreacion<<endl;
    cout << "Activo: ";
    if(u.Activo == true)
        cout << "Si" << endl;
    else
        cout << "No" << endl;
    cout << "Total compras: " << u.TotalImporteCompras << endl;
    cout << "Correo: " << u.eMail << endl;
    cout << "==========================" << endl;

}
void mostrarTodosUsuarios(Nodo *lista)
{
    while(lista){
        mostrarUsuario(lista->info);
        lista=lista->sgte;
    }


}

void buscar_ID(int id, Nodo *lista)
{
    int buscado = 0;
    Nodo *aux = lista;
    while(aux)
    {
        if(id == aux->info.UsuarioID)
        {
            mostrarUsuario(aux->info);
            return;

        }
        aux = aux->sgte;
    }
//        return 1;
    return;
}


Usuario buscar_ID1(int id) // Devuelve el cliente
{
    FILE *f;
    int encontrado = 0;
    Usuario u;
    Usuario k;
    if(f = fopen("clientes.bin", "rb"))
    {
        while(fread(&u, sizeof(Usuario), 1, f) && !encontrado)
        {
            if(u.UsuarioID == id)
            {
                return u;
            }
        }
        fclose(f);
        }
    return k;
}

int buscar_Mail(char mail[], Nodo *lista)
{
    Nodo *aux = lista;
    while(aux)
    {
        if(strcmp(mail, aux->info.eMail) == 0)
            mostrarUsuario(aux->info);
        aux = aux->sgte;
    }
    return 0;
}
void desactivar_con_ID (Nodo *&listausuario, int id)
{
    Nodo *aux = NULL;
    aux=listausuario;
        while(listausuario){
        if(id==listausuario->info.UsuarioID){
            listausuario->info.Activo=false;
        }
        listausuario=listausuario->sgte;

        }

       listausuario=aux;
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

void InsertarSiguiente(Nodo *&n, Usuario x)
{
    Nodo *nuevo = new Nodo();
    nuevo -> info = x;
    if(n)
    {
        nuevo -> sgte = n -> sgte;
        n -> sgte = nuevo;
    }
    else
    {
        nuevo -> sgte = n;
        n = nuevo;
    }
    return;
}
void InsertarSiguienteCompras(NodoCompras *&n, Compra x)
{
    NodoCompras *nuevo = new NodoCompras();
    nuevo -> info = x;
    if(n)
    {
        nuevo -> sgte = n -> sgte;
        n -> sgte = nuevo;
    }
    else
    {
        nuevo -> sgte = n;
        n = nuevo;
    }
    return;
}

Nodo *BuscarNodoAnterior(Nodo *inicial, Nodo *anterior_a)
{
    Nodo *p = NULL;
    if(inicial != anterior_a)
    {
        p = inicial;
        while(p && (p -> sgte != anterior_a))
        {
            p = p -> sgte;
        }
        return p;
    }
    else
        return NULL;
}

Nodo *ObtenerUltimo(Nodo *p)
{
    if(p)
    {
        while(p -> sgte)
        {
            p = p -> sgte;
        }
    }
    return p;
}
NodoCompras *ObtenerUltimoCompras(NodoCompras *p)
{
    if(p)
    {
        while(p -> sgte)
        {
            p = p -> sgte;
        }
    }
    return p;
}

void InsertarAlFinal(Nodo *&inicial, Usuario x)
{
    Nodo *aux;
    aux = ObtenerUltimo(inicial);
    if(aux)
        InsertarSiguiente(aux, x);
    else
        InsertarSiguiente(inicial, x);
    return;
}
void InsertarAlFinalCompras(NodoCompras *&inicial, Compra x)
{
    NodoCompras *aux;
    aux = ObtenerUltimoCompras(inicial);
    if(aux)
        InsertarSiguienteCompras(aux, x);
    else
        InsertarSiguienteCompras(inicial, x);
    return;
}
void InsertarPrimero(Nodo *&inicial, Usuario x)
{
    Nodo *nuevo = new Nodo();
    Nodo *aux = inicial;
    nuevo->info = x;
    inicial = nuevo;
    nuevo->sgte = aux;
    return;
}

void InsertarOrdenado(Nodo *&inicial, Usuario x)
{
    Nodo *anterior = NULL;
    Nodo *aux = inicial;
    while(aux && aux->info.TotalImporteCompras < x.TotalImporteCompras)
    {
        aux = aux->sgte;
    }
    if(aux && aux!=inicial)
    {
        anterior = BuscarNodoAnterior(inicial, aux);
        InsertarSiguiente(anterior, x);
    }
    else
    {
        if(aux == NULL)
            InsertarAlFinal(inicial, x);
        else if(aux == inicial)
            InsertarPrimero(inicial, x);
    }
    return;
}

Nodo *ObtenerSiguiente(Nodo *n)
{
    if(n)
        return n -> sgte;
    else
        return NULL;
}
NodoCompras *ObtenerSiguienteCompras(NodoCompras *n)
{
    if(n)
        return n -> sgte;
    else
        return NULL;
}


void MostrarLista(Nodo *lista)
{
    while(lista)
    {
        mostrarUsuario(lista->info);
        lista = ObtenerSiguiente(lista);
    }
}

void OrdenarCompras(Usuario u)
{
    FILE *f = NULL;
    Nodo *lista = NULL;
    if(f = fopen("clientes.bin", "r"))
    {
        fread(&u, sizeof(Usuario), 1, f);
        while(!feof(f))
        {
            InsertarOrdenado(lista, u);
            fread(&u, sizeof(Usuario), 1, f);
        }
    fclose(f);
    }

    MostrarLista(lista);
    return;
}

void CargarCompra(Compra &c)
{
    cout << "ID compra: ";
    cin >> c.CompraID;
    fflush(stdin);
    cout << "Fecha: ";
    cin>>c.FechaHora;
    fflush(stdin);
    cout << "Monto: ";
    cin >> c.Monto;
    fflush(stdin);
    cout << "ID usuario: ";
    cin >> c.UsuarioID;
    fflush(stdin);
    cout << "Numero de articulo: ";
    cin >> c.NroArticulo;
    fflush(stdin);
    return;
}

void MostrarCompra(NodoCompras *lista)
{
    while(lista)
    {
        cout << "==========================" << endl;
        cout << "ID Usuario: " << lista->info.UsuarioID << endl;
        cout << "ID Compra: " <<lista->info.CompraID<< endl;
        cout << "Fecha y Hora: " << lista->info.FechaHora << endl;
        cout << "Monto: " << lista->info.Monto << endl;
        cout << "Nro. Articulo: " << lista->info.NroArticulo << endl;
        cout << "==========================" << endl;
        lista = lista->sgte;
    }
}
void MostrarUnaCompra(Compra c){

        cout << "==========================" << endl;
        cout << "ID Usuario: " << c.UsuarioID << endl;
        cout << "ID Compra: " <<c.CompraID<< endl;
        cout << "Fecha y Hora: " << c.FechaHora << endl;
        cout << "Monto: " << c.Monto << endl;
        cout << "Nro. Articulo: " << c.NroArticulo << endl;
        cout << "==========================" << endl;

}

void InsertarCompraEnLista (NodoCompras *&n, Compra x)
{
    NodoCompras *nuevo= new NodoCompras();
    nuevo->info=x;
    if (n!=NULL)
    {
        nuevo->sgte= n->sgte;
        n->sgte = nuevo;
    }
    else
    {
        nuevo->sgte= n;
        n= nuevo;
    }

    return;
}

void InsertarUsuarioEnLista (Nodo *&n, Usuario x)
{
    Nodo *nuevo= new Nodo();
    nuevo->info=x;
    if (n!=NULL)
    {
        nuevo->sgte= n->sgte;
        n->sgte = nuevo;
    }
    else
    {
        nuevo->sgte= n;
        n= nuevo;
    }

    return;
}

void ProcesarLoteDeCompras(Nodo *ListaUsuario, NodoCompras *&ListaCompras)
{

    char ruta[50];
    char opcion;
    Compra compr;
    NodoCompras *Paux_compra;
    FILE *f=NULL;
    FILE *procesados = NULL;
    do{
    cout<<"Ingrese la ruta :"<<endl;
    cin>>ruta;
    procesados = fopen("procesados.bin","ab");
    f = fopen(ruta, "rb");

     if (f != NULL) //pude abrir el archivo
        {
            cout<<"entro en el archivo"<< endl;

            while (fread(&compr, sizeof(Compra), 1, f)){
                    InsertarAlFinalCompras(ListaCompras,compr);
                    fwrite(&compr,sizeof(Compra),1,procesados);

            }
            fclose(f);
            fclose(procesados);

        }
        else
        cout << "No se pudo abrir el archivo." << endl;
        cout << "Desea ingresar otro lote de compras(Y/N): ";
        cin >> opcion;


        }while(opcion == 'Y' || opcion == 'y');


    Paux_compra = ListaCompras;

    while(ListaUsuario){

    ListaUsuario->info.TotalImporteCompras=0;

     while(Paux_compra){

       if(Paux_compra->info.UsuarioID==ListaUsuario->info.UsuarioID){

        ListaUsuario->info.TotalImporteCompras = ListaUsuario->info.TotalImporteCompras + Paux_compra->info.Monto;


       }
        Paux_compra=Paux_compra->sgte;
     }

        ListaUsuario = ListaUsuario->sgte;
        Paux_compra = ListaCompras;

     }
     char opcion2;

    cout << "Desea mostrar las compras(Y/N): ";
    cin >> opcion2;


    if(opcion2 == 'Y' || opcion2 == 'y'){
        MostrarCompra(ListaCompras);
    }

    FILE *w = NULL;
    Compra x;
    w = fopen("compras.bin", "ab");
    if(w != NULL)
    {
        x.UsuarioID = 0;
        x.NroArticulo = 0;
        x.Monto = 0;
        x.FechaHora = 0;
        x.CompraID = 0;
        x.borrado = false;
        fwrite(&x, sizeof(Compra), 1, w);
        fclose(w);
    }

 }

void ordenarLista(Nodo *lista)
{

    Nodo *nueva = NULL;
    while(lista)
    {
        if(lista->info.Activo == true)
        {
            InsertarOrdenado(nueva, lista->info);
        }
        lista = lista->sgte;
    }
    MostrarLista(nueva);
}

void MostrarCompraCliente(int id){

    FILE *f=NULL;
    NodoCompras *lista=NULL;
    Compra c;
    f=fopen("procesados.bin","rb");
    if(f!=NULL){
        while(fread(&c,sizeof(Compra),1,f)){
            InsertarAlFinalCompras(lista,c);
        }

    }
    fclose(f);

    NodoCompras *aux=lista;
    while(aux){

        if(aux->info.UsuarioID==id){
            MostrarUnaCompra(aux->info);

        }
       aux = aux->sgte;

    }



}

cargarUsuarioArchivo(Usuario &u){
 cout << "ID: ";
    cin >> u.UsuarioID;
    fflush(stdin);
    cout << "Fecha: ";
    cin >>u.FechaCreacion;
    fflush(stdin);
    cout << "Activo (1-si / 2-no): ";
    int act;
    cin >> act;
    if(act == 1)
        u.Activo = true;
    else
        u.Activo = false;
    fflush(stdin);
    cout << "Correo: ";
    fgets(u.eMail, 50, stdin);
    fflush(stdin);


}

int main()
{
    FILE *clientes = NULL;
    FILE *comp = NULL;
    FILE *compras = NULL;
    FILE *procesados = NULL;
    NodoCompras *ListaCompras=NULL;
    Nodo         *ListaUsuario=NULL;
    NodoCompras *comprasProcesadas = NULL;
    Usuario u;
    Compra c;
    int pos = 0;
    int tam = 0;
    int idbusq, menubusq, idborrar;
    char mailbusq[50];
    int opcion;
    do
    {
        cout << "Elija una opcion" << endl;
        //1 bien
        cout << "1 - Levantar clientes del archivo Clientes.bin." << endl;
        //2 bien
        cout << "2 - Cargar un nuevo cliente." << endl;
        //3 bien
        cout << "3 - Desactivar un usuario existente" << endl;
        //4 bien
        cout << "4 - Buscar un cliente por ID o por mail."<< endl;
        //5 REVISAR
        cout << "5 - Listar todos los clientes activos ordenados por total del importe." <<endl;
        //6, Bien
        cout << "6 - Procesar un lote de compras." <<endl;
        //7 Bien
        cout << "7 - Mostrar por pantalla todas las compras realizadas de un cliente dado (desde el archivo procesados.bin)." <<endl;

        // 8 y 9 son las del reporte en html.
        cout << "8 - Mostrar todas las compras realizadas entre dos fechas en un reporte escrito en formato html. También mostrar el total de las compras " <<endl;
        cout << "9 - Mostrar el mismo reporte que el punto 8 en formato CSV " <<endl;
        cout << "10 - Finalizar jornada." <<endl;
        cout << "11 - Cargar datos en Clientes.bin." <<endl;
        cout << "12 - Cargar lote de compras" << endl;
        cout << "13 - mostrar usuarios" << endl;
        cout << "14 - Cargar nuevos usuarios en el archivo clientes" << endl;
        cout << "esc - Salir" << endl;
        cin >> opcion;
        switch(opcion)
        {
            case 1:
              levantarUsuario(ListaUsuario);


            break;

            case 2:

               cargarUsuario(ListaUsuario);

                break;
            case 3:
                    cout << "ID del usuario a borrar: ";
                    cin >> idborrar;
                   desactivar_con_ID (ListaUsuario,idborrar);


                break;
                case 4:
                    cout << "1- Buscar por ID" << endl;
                    cout << "2- Buscar por mail" << endl;
                    cin >> menubusq;
                    if(menubusq == 1)
                    {
                        cout << "ID buscado: ";
                        cin >> idbusq;
                        buscar_ID(idbusq, ListaUsuario);
                    }
                    if(menubusq == 2)
                    {
                        cout << "Mail buscado: ";
                        fflush(stdin);
                        fgets(mailbusq, 50, stdin);
                        buscar_Mail(mailbusq, ListaUsuario);
                    }
                break;

                case 5:
                ordenarLista(ListaUsuario);
                break;

                case 6:
                    ProcesarLoteDeCompras(ListaUsuario, ListaCompras);
                break;

                case 7:
                        cout << "ID buscado: ";
                        cin >> idbusq;
                        MostrarCompraCliente(idbusq);
                break;

               case 8:

                break;

                 case 9:

                break;

                 case 10:

                break;
                 case 12:
                    compras = fopen("compras.bin", "ab");
                    if(compras != NULL)
                    {
                        CargarCompra(c);
                        fwrite(&c, sizeof(Compra), 1, compras);
                        fclose(compras);
                    }
                break;

                 case 13:
                    mostrarTodosUsuarios(ListaUsuario);
                break;
                 case 14:
                clientes = fopen("clientes.bin", "ab");
                if(clientes != NULL)
                {
                    cargarUsuarioArchivo(u);
                    fwrite(&u, sizeof(Usuario), 1, clientes);
                    fclose(clientes);
                }

                    break;
        }


    }while (opcion!= 27);
    getch();
    return 0;
}
