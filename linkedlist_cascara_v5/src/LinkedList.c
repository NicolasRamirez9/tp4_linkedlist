#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this;
    this = (LinkedList *)malloc(sizeof(LinkedList));
    if(this != NULL)
    {
        this->size=0;
        this->pFirstNode = NULL;
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
        returnAux = this->size;
    }
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* pNode = NULL;
    int i;

    if(this != NULL && nodeIndex >= 0 && nodeIndex < ll_len(this))
    {
        pNode = this->pFirstNode;
        if(pNode != NULL)
        {
            for(i=0; i<nodeIndex; i++)
            {
                pNode = pNode->pNextNode;
            }
        }
    }
    return pNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    Node* pNodoAnterior;
    Node* pNodoNuevo;

    if(this != NULL && nodeIndex >= 0 && nodeIndex <= ll_len(this))
    {
        pNodoNuevo = (Node*) malloc(sizeof(Node));
        if(pNodoNuevo != NULL)
        {
            pNodoNuevo->pElement = pElement;
            if(nodeIndex == 0)
            {
                if(this->pFirstNode == NULL) pNodoNuevo->pNextNode = NULL;
                if(this->pFirstNode != NULL)  pNodoNuevo->pNextNode = this->pFirstNode;
                this->pFirstNode = pNodoNuevo;
            }
            else
            {
                pNodoAnterior = getNode(this,nodeIndex-1);
                pNodoNuevo->pNextNode = pNodoAnterior->pNextNode;
                pNodoAnterior->pNextNode = pNodoNuevo;
            }
            this->size++;
            returnAux = 0;
        }
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex, void* pElement)
{
    return addNode(this, nodeIndex, pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int  ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int nodeIndex = ll_len(this);

    if(this != NULL)
    {
        if(!addNode(this, nodeIndex, pElement))
        {
            returnAux = 0;
        }
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna(NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* pNode;

    if(this != NULL && index >= 0)
    {
        pNode = getNode(this, index);

        if(pNode != NULL)
        {
            returnAux = pNode->pElement;
        }
    }
    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node *pNode;

    if(this != NULL && index >= 0)
    {
        pNode = getNode(this, index);

        if(pNode != NULL)
        {
            pNode->pElement = pElement;
            returnAux = 0;
        }
    }
    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* pNodoBorrar;
    Node* pNodoAnterior;

    if(this != NULL && index >= 0 && index < ll_len(this))
    {
        if(index == 0)
        {
            pNodoBorrar = this->pFirstNode;
            this->pFirstNode = pNodoBorrar->pNextNode;
        }
        else
        {
            pNodoAnterior = getNode(this,index-1);
            pNodoBorrar = getNode(this,index);

            pNodoAnterior->pNextNode = pNodoBorrar->pNextNode;
        }
        free(pNodoBorrar);
        this->size--;
        returnAux = 0;
    }

    return returnAux;
}

/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;

    if(this !=NULL)
    {
        for(int i=0; i<ll_len(this); i++)
        {
            ll_remove(this,i);
        }

        returnAux = 0;
    }

    return returnAux;
}

/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;

    if(this !=NULL)
    {
        ll_clear(this);
        free(this);

        returnAux = 0;
    }

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    Node* pNode;

    if(this !=NULL)
    {
        for(int i=0; i<ll_len(this); i++)
        {
            pNode = getNode(this,i);

            if(pNode!=NULL && pNode->pElement == pElement)
            {
                returnAux = i;
            }
        }
    }
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;

    if(this !=NULL)
    {
        if(this->size == 0)
        {
            returnAux = 1;
        }
        else
        {
            returnAux = 0;
        }
    }

    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;

    if(this !=NULL && index >= 0 && index <= ll_len(this))
    {
        if(addNode(this, index, pElement)==0)
        {
            returnAux = 0;
        }
    }
    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    void* pNode;

    if(this !=NULL && index >= 0 && index <= ll_len(this))
    {
        pNode = ll_get(this,index);

        if(pNode !=NULL)
        {
            ll_remove(this,index);
            returnAux = pNode;
        }
    }
    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this !=NULL)
    {
        if(ll_indexOf(this,pElement)==-1)
        {
            returnAux = 0;
        }
        else
        {
            returnAux = 1;
        }
    }

    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    void* pNodoAuxiliar;
    int cont = 0;

    if(this !=NULL && this2 !=NULL)
    {

        for(int i=0; i<ll_len(this2); i++)
        {

            pNodoAuxiliar = ll_get(this2,i);

            /* if(ll_contains(this,pNodoAuxiliar)==1)
             {
                 returnAux = 1;
             }
             else
             {
                 returnAux = 0;
                 break;
             }
            }*/
            if(ll_contains(this,pNodoAuxiliar)==1)
            {
                cont++;
            }
        }

        if(cont == ll_len(this2))
        {
            returnAux = 1;
        }
        else
        {
            returnAux = 0;
        }
    }

    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    LinkedList* this2;
    void* pNodoAuxiliar;

    if(this !=NULL && (from >=0 && from <= ll_len(this)) && (to > from && to <= ll_len(this)))
    {
        this2 = ll_newLinkedList();

        if(this2 !=NULL)
        {
            for(int i=from; i<to; i++)
            {
                pNodoAuxiliar = ll_get(this,i);

                ll_add(this2,pNodoAuxiliar);
            }
        }

        if(this2->size == (to-from))
        {
            cloneArray = this2;
        }
    }

    return cloneArray;
}

/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;

    if(this !=NULL)
    {
        cloneArray = ll_subList(this,0,this->size);
    }

    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
    int i;
    int flagSwap;
    void* this1;
    void* this2;
    int retOrderValue;

    if(this != NULL && ll_len(this) > 0 && pFunc != NULL && (order == 1 || order == 0))
    {
        do
        {
            flagSwap = 0;
            for(i=0;i<ll_len(this);i++)
            {
                this1 =ll_get(this,i);
                this2 = ll_get(this,i+1);
                if(this1 != NULL && this2 != NULL)
                {
                    retOrderValue = pFunc(this1 , this2);
                    if((order == 0 &&retOrderValue == -1) || (retOrderValue == 1 && order == 1))
                    {   //Orden ascendente
                        flagSwap = 1;
                        ll_set(this,i,this2);
                        ll_set(this,i+1,this1);
                    }
                }
            }
        }while(flagSwap == 1);
        returnAux = 0;
    }
    return returnAux;
}

int ll_map(LinkedList* this,int (*pFunc)(void*))
{
    int returnAux = -1;
    int i;

    if(this != NULL && pFunc != NULL)
    {
        returnAux = 0;

        for(i=0; i<ll_len(this); i++)
        {
            pFunc(ll_get(this,i));
        }
    }
     return returnAux;
}

LinkedList* ll_filter (LinkedList* this, int (*pFunc)(void*))
{
    int i;
    void* pElemento;

    LinkedList* newList=NULL;

    if (this!= NULL && pFunc != NULL)
    {
        newList = ll_newLinkedList();

        for (i=0; i<ll_len(this); i++)
        {
            pElemento = ll_get(this,i);

            if(pFunc(pElemento) == 1)
            {
                ll_add(newList,pElemento);
            }
        }
    }
    return newList;
}

int ll_reduce (LinkedList* this, int (*pFunc)(void*))
{
    int returnAux = -1;
    int i;
    int size = ll_len(this);
    void* pElemento;

    if (this!= NULL && pFunc != NULL)
    {
        for (i=0; i<size; i++)
        {
            pElemento = ll_get(this,i);

            if(pFunc(pElemento)==1)
            {
                ll_remove(this,i);
                i--;
                size--;
            }
        }
        returnAux=0;
    }
    return returnAux;
}
