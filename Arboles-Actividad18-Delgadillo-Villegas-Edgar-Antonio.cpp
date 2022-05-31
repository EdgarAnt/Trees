#include <iostream>
#include <stdlib.h>
#include <limits>
using namespace std;

void menu();

struct Nodo{
int id;
string nombre;
string dir;
string email;
struct Nodo *izq, *der;
};
typedef struct Nodo *Node;


int buscar2(Node arbol, int bus)
{
 Node algo;
 algo=arbol;
 int i=0;
 while(algo!=NULL)
      {
       if(bus < algo->id)
   {algo=algo->izq;
      i=i+1;}
       else
  if(bus > algo->id)
   { algo= algo->der;
      i=i+1;
      }
   else
   return i;
       }
 return -1;
}
Node buscar (Node &aux, int id, Node &padre)
{
    while(aux!=NULL && aux->id!=id)
    {
        padre = aux;
        if (id<aux->id)
            aux = aux->izq;
        else
            aux=aux->der;
    }
}

Node CreateNode(int id, string nombre, string dir, string email)
{
    Node newNode = new( Nodo);
    newNode->id = id;
    newNode->nombre = nombre;
    newNode->dir = dir;
    newNode->email = email;
    newNode->izq = NULL;
    newNode->der = NULL;
    return newNode; }


Node Min(Node &ptr)
{

    while(ptr->izq!=NULL)
        ptr = ptr -> izq;
    return ptr;
}
int readValidNumber(string mensaje)
{
    cout << mensaje;
    int x = 0;
    while(!(cin >> x)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "INVALIDO! "<<endl;
        cout << "Ingrese solo numeros."<<endl;
        cout << mensaje;
    }
    return x;
}

void add(Node &ptr, int id, string nombre, string dir, string email)
{

    if(ptr==NULL) {
    ptr = CreateNode(id, nombre, dir, email); }
    else if(id < ptr->id)
        add(ptr->izq, id, nombre, dir, email);
    else if(id > ptr->id)
        add(ptr->der, id, nombre, dir, email);

}

void borrar(Node &ptr, int id)
{
    Node padre = NULL;
    Node aux = ptr;
    if(ptr==NULL)
        return;

    buscar(aux,id, padre);

    if(aux->izq == NULL && aux->der==NULL)
    {

       if(aux != ptr)
       {
            if (padre->izq == aux)
            {
                padre -> izq = NULL;
            }
            else
            {
                padre->der = NULL;
            }

        }
        else{
            ptr =NULL;
        }
        free(aux);
    }
    else if(aux->izq && aux->der)
    {
        Node sucesor = Min(aux->der);
        int id=sucesor->id;
        string nombre = sucesor->nombre;
        string dir = sucesor->dir;
        string email =  sucesor ->email;
        borrar(ptr,sucesor->id);
        aux->id = id;
        aux->nombre = nombre;
        aux->dir = dir;
        aux->email=email;
    }
    else
    {
        Node hijo = NULL;
        if(aux->izq)
            hijo = aux ->izq;
        else
            hijo = aux -> der;
        if (aux!=ptr)
        {
            if (aux==padre->izq)
                padre->izq = hijo;
            else
                padre->der = hijo;
        }
        else
            ptr = hijo;
        free(aux);
    }
}
void preOrden(Node arbol)
{
     if(arbol!=NULL)
     {
          cout << arbol->id <<" ";
          preOrden(arbol->izq);
          preOrden(arbol->der);
     }
}

void enorden(Node arbol)
{if(arbol!=NULL)
  {enorden(arbol->izq);
   cout<<arbol->id<<" ";
   enorden(arbol->der);
  }
}
void postorden(Node arbol)
{if(arbol!=NULL)
 {postorden(arbol->izq);
  postorden(arbol->der);
  cout<<arbol->id<<" ";
 }
}

void mostrarArbol(Node ptr){
    if(ptr==NULL)
    return;
    mostrarArbol(ptr->der);
    cout<< "Nombre: "<<ptr->nombre <<endl;
    cout<< "ID: "<<ptr->id <<endl;
    cout<< "Direccion: "<<ptr->dir <<endl;
    cout<< "E-mail: "<<ptr->email <<endl;

    mostrarArbol(ptr->izq);
}
void Modificar(Node arbol){
Node temp = arbol;
Node jj = NULL;
int id,opc;
string nombreNew,direccionNew,emailNew;
id=readValidNumber("Ingrese ID a modificar: ");
buscar(temp, id, jj);
cout<<"Modificar: "<<endl;
cout<<"1) Nombre."<<endl;
cout<<"3) Direccion."<<endl;
cout<<"2) E-mail."<<endl;
opc=readValidNumber(" ");
if(opc==1){
    cout<<"Nombre: "<<endl;
    cin>>nombreNew;
    temp->nombre=nombreNew;
    }
if(opc==2){

    cout<<"Direccion: "<<endl;
    cin>>direccionNew;
    temp->dir=direccionNew;
    }
if(opc==3){
    cout<<"E-mail: "<<endl;
    cin>>emailNew;
    temp->email=emailNew;
    }
}


void menu()
{
    system("cls");
    Node arbol = NULL;
    int id, input,menu1 = 0,menu2=0,opc,r;
    string nombre, direccion, email;
    cout<< "----------------------------------------------------------------"<< endl;
    cout<< "                               MENU                             "<< endl;
    cout<< "----------------------------------------------------------------"<< endl;
    menu1=readValidNumber("Numero de nodos:  ");
    do{
        cout<< "E-mail: ";
        cin>> email;
        cout<< "Nombre: ";
        cin>> nombre;
        cout<< "Direccion: ";
        cin>> direccion;
        id=readValidNumber("ID: ");
        cout << endl;
        add(arbol,id, nombre,direccion,email);
        menu2++;
    }while(menu2<menu1);
    do{
        cout<<endl;
        cout<< "----------------------------------------------------------------"<< endl;
        cout<< "                               MENU                             "<< endl;
        cout<< "----------------------------------------------------------------"<< endl;
        cout<<"1) Eliminar"<<endl;
        cout<<"2) Modificar"<<endl;
        cout<<"3) postOrden"<<endl;
        cout<<"4) Buscar ID"<<endl;
        cout<<"5) preOrden"<<endl;
        cout<<"6) enOrden"<<endl;
        cout<<"7) Mostrar Arbol"<<endl;
        cout<<"8) Salir"<<endl;
        opc=readValidNumber(" ");
        switch(opc){

    case 1:
        id=readValidNumber("ID a eliminar: ");
        borrar(arbol,id);

        break;
    case 2:

        Modificar(arbol);
        break;
        break;
    case 3:
        postorden(arbol);
        cout<<endl;
        break;
    case 4:
        id=readValidNumber("ID a buscar: ");
        r=buscar2(arbol,id);
        if(r==1)
         cout<<id<<" Id valido"<<endl;

      else
        cout<<id<<" NO se encuentra"<<endl;
        cout<<"Elementos recorridos: "<<r<<endl;
        break;
    case 5:

        preOrden(arbol);
        cout<<endl;
    case 6:
        enorden(arbol);
        cout<<endl;
        break;
    case 7:
        cout<<"Arbol: "<<endl;
        mostrarArbol(arbol);
        break;
    case 8:
        break;
    }
    }while(opc!=8);
    system("pause");
}


int main(int argc, char** argv) {
    menu();
    return 0;

}
