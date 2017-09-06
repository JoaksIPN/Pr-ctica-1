/*
AUTOR: Dominguez Moran Joaquín, García Ibañez Diego, Rosas Sánchez Paloma. Agosto 2017.
VERSIÓN: 1.0.

DESCRIPCIÓN: Programa que valida y evalua una expresión infija.

OBSERVACIONES: El programa utiliza 6 funciones para realizar las operaciones que poco a poco modifican la matriz original.

COMPILACIÓN: 
			Windows: gcc main.c TADPilaEst.c
			Linux: gcc main.c TADPilaEst.c -lm

EJECUCIÓN: 
			Windows: a.exe
			Linux: ./a.out
*/

//MACROS DEL PREPROCESADOR
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "TADPilaEst.h"
#include "TADPilaDin.h"
#include <math.h>

//DEFINICIONES
#define TAM 100			//Se define el numero de datos que se pueden ingresar





/*
**void ValidarParentesis (char array[TAM])**
DESCRIPCIÓN: Función que evalua una expresión para asegurar que los parentesis estan escritos de manera correcta.
ENTRADA: Un arreglo de tipo caracter de TAM 100
SALIDA: Impresión en pantalla si la expresión es correcta, sino un mensaje de error y sale del programa.
OBSERVACIONES: Se emplea la libreria TADPilaEst.h,TADPilaDin.h,stdio.h,stdlib.h,string.h.
*/

void
ValidarParentesis (char array[TAM])
{
  int i = 0;			//Se declara una variable de tipo entero y se inicializa en 0 
  int tamano;			//Se declara una variable de tipo entero
  float valor;			//Se declara variable de tipo flotante
  tamano = strlen (array);	//Medir el tamaño del arreglo
  elemento e;			//Se declara un elemento e
  pila palpila;			//Se declara una pila "palpila"
  Initialize (&palpila);	//Inicialización de la pila "palpila"
  for (i = 0; i < tamano; i++)	//Ciclo for que recorre cada caracter del arreglo
    {
      e.Char = array[i];
      if (array[i] == '(')	//Si el caracter es "(" introducirlo a la pila
	Push (&palpila, e);
      if (array[i] == ')')	//Si el caracter es ")" realizar un Pop a la pila
	{
	  if (Empty (&palpila))	//Si se intenta extraer un elemento y la pila es vacia Error
	    {
	      printf
		("Existen mas parentesis de los que cierran de los que abren. \n");
	      exit (1);
	    }

	  Pop (&palpila);

	}

    }

  if (!Empty (&palpila))	//Si al terminar de revisar la expresión  hay elementos en la pila 
    {
      printf
	("Existen mas parentesis de los que abren de los que cierran.\n");
      exit (1);
    }

  printf ("Expresion correcta.\n");	//Si la ejecución termina de manera correcta 


  Destroy (&palpila);		//Se destruye la pila.

}

/*
**char *Posfijo (char array[TAM])**
DESCRIPCIÓN: Función que pasa una expresión aritmética en posfijo a partir de la expresión infija.
ENTRADA: Un arreglo de tipo caracter de tamaño 100
SALIDA: Un arreglo con la expresión infija transformada en posfija
OBSERVACIONES:Se emplea la libreria TADPilaEst.h,TADPilaDin.h,stdio.h,stdlib.h,string.h. El arreglo de tipo caracter contiene letras mayusculas y ya están validados los parentesis.
*/

char *
Posfijo (char array[TAM])
{
  int i;			//Se declara una variable de tipo entero que  se usará como contador
  int j = 0;			//Se declara e inicializa una variable de tipo entero que  se usará como contador
  int tamCadena;		//Se declara una variable de tipo entero que guardara el tamaño de la cadena
  char *resultado;		//Se declara variable de tipo apuntador
  elemento E, E1, E2;		//Se declara elemento E,E1,E2

  tamCadena = strlen (array);	////Medir el tamaño del arreglo

  pila posfijo;			//Se declara una pila "posfijo"
  Initialize (&posfijo);	//Inicializar pila "posfijo"

  resultado = (char *) malloc (1 * sizeof (char));	//Asiganamos memoria.



  for (i = 0; i < tamCadena; i++)	//Ciclo que recorre cada caracter de la cadena.
    {

      E.Char = array[i];	//Aisganamos a un elemento de tipo caracter la posición i del arreglo.




      if (E.Char >= (char) 65 && E.Char <= (char) 90)	//Si el elemento E.Char del arreglo es un operando se agrega directamente a resultado
	{

	  resultado = (char *) realloc (resultado, (j + 1) * sizeof (char));
	  resultado[j] = E.Char;
	  j++;


	}


      if (E.Char == '(')	//Si el elemento E.Char del arreglo es un parentesis que abre se agrega a la pila.
	{

	  Push (&posfijo, E);

	}



      if (E.Char == ')')	//Si el elemento i del arreglo es un parentesis que cierra se desempilan elementos hasta encontrar un parentesis que abre.
	{
	  if (Empty (&posfijo) == FALSE)	//Se valida que la pila no se encuentre vacia.
	    E1 = Top (&posfijo);	//Se le asigna al elemento E1 el elemento que se encuentra en el tope.
	  while (E1.Char != '(')	//Si el tope es diferente de un parentesis que abre.
	    {
	      E2 = Pop (&posfijo);	//Se desempila un elemento
	      resultado =
		(char *) realloc (resultado, (j + 1) * sizeof (char));
	      resultado[j] = E2.Char;	//Se colocan los elementos desempilados en el arreglo a retornar
	      j++;


	      if (Empty (&posfijo) == FALSE)	//Se valida que la pila no se encuentre vacia.
		E1 = Top (&posfijo);	//Se le asigna al elemento E1 el elemento que se encuentra en el tope.

	    }
	  Pop (&posfijo);	//Se desempila el parentesis que abre

	}


      if (E.Char == '+' || E.Char == '-')	//Si es un operador de suma o resta.
	{
	  if (Empty (&posfijo) == FALSE)	//Se valida que la pila no se encuentre vacia.
	    E1 = Top (&posfijo);	//Se le asigna al elemento E1 el elemento que se encuentra en el tope.

	  if ('(' == E1.Char || Empty (&posfijo) == TRUE)	//Si el tope es diferente de un parentesis que cierra o la pila esta vacia se empila el operador.
	    Push (&posfijo, E);	//Se empila el operador.

	  else
	    {

	      while (E1.Char != '(' && Empty (&posfijo) == FALSE)	//Si el tope es diferente de un parentesis que abre y la pila no se encuentra vacia.
		{
		  E2 = Pop (&posfijo);	//Se desempila un elemento
		  resultado =
		    (char *) realloc (resultado, (j + 1) * sizeof (char));
		  resultado[j] = E2.Char;	//Se colocan los elementos desempilados en el arreglo a retornar
		  j++;
		  if (Empty (&posfijo) == FALSE)	//Se valida que la pila no se encuentre vacia.
		    E1 = Top (&posfijo);	//Se le asigna al elemento E1 el elemento que se encuentra en el tope

		}

	      Push (&posfijo, E);	//Se empila el operador.
	    }

	}



      if (E.Char == '*' || E.Char == '/')	//Si es un operador de multiplicación o división.
	{

	  if (Empty (&posfijo) == FALSE)	//Se valida que la pila no se encuentre vacia.
	    E1 = Top (&posfijo);	//Se le asigna al elemento E1 el elemento que se encuentra en el tope.

	  if (('*' != E1.Char && '/' != E1.Char && '^' != E1.Char) || Empty (&posfijo) == TRUE)	//Si el tope es diferente de un operador de menor o igual jerarqui la pila esta vacia se empila el operador.
	    Push (&posfijo, E);	//Se empila el operador.

	  else
	    {


	      while (('*' == E1.Char || '/' == E1.Char || '^' == E1.Char) && Empty (&posfijo) == FALSE)	//Si el tope es igual a un operador de igual o mayor jerarquia y la pila no se encuentra vacia.
		{
		  E2 = Pop (&posfijo);	//Se desempila un elemento
		  resultado =
		    (char *) realloc (resultado, (j + 1) * sizeof (char));
		  resultado[j] = E2.Char;	//Se colocan los elementos desempilados en el arreglo a retornar
		  j++;

		  if (Empty (&posfijo) == FALSE)	//Se valida que la pila no se encuentre vacia.
		    E1 = Top (&posfijo);	//Se le asigna al elemento E1 el elemento que se encuentra en el tope

		}

	      Push (&posfijo, E);	//Se empila el operador.
	    }

	}

      if (E.Char == '^')	//Si es un operador de potencia.
	{

	  if (Empty (&posfijo) == FALSE)	//Se valida que la pila no se encuentre vacia.
	    E1 = Top (&posfijo);	//Se le asigna al elemento E1 el elemento que se encuentra en el tope.
	  if ('^' != E1.Char || Empty (&posfijo) == TRUE)
	    Push (&posfijo, E);

	  else
	    {

	      while ('^' == E1.Char && Empty (&posfijo) == FALSE)	//Si el tope es igual a un operador de potencia.
		{
		  E2 = Pop (&posfijo);	//Se desempila un elemento
		  resultado =
		    (char *) realloc (resultado, (j + 1) * sizeof (char));
		  resultado[j] = E2.Char;	//Se colocan los elementos desempilados en el arreglo a retornar
		  j++;

		  if (Empty (&posfijo) == FALSE)	//Se valida que la pila no se encuentre vacia.
		    E1 = Top (&posfijo);	//Se le asigna al elemento E1 el elemento que se encuentra en el tope

		}

	      Push (&posfijo, E);	//Se empila el operador.
	    }

	}

    }


  if (Empty (&posfijo) == FALSE)	//Si al terminar el recorrido la pila no se encuentra vacía.
    {

      while (Empty (&posfijo) == FALSE)	//Se valida que la pila no se encuentre vacia.
	{
	  E2 = Pop (&posfijo);	//Se desempila un elemento
	  resultado = (char *) realloc (resultado, (j + 1) * sizeof (char));
	  resultado[j] = E2.Char;	//Se colocan los elementos en el arreglo a retornar
	  j++;

	}

    }

  Destroy (&posfijo);		//Se destruye la pila.
  resultado[j] = '\0';		//Se pone fin de cadena al arreglo


  return resultado;		//Se retorna la cadena que contiene la expresión en posfijo


}

///////////////////////////////////////////////////////////////////////////////////////////


/*
**EvalPosfijo (char array[TAM])**
DESCRIPCIÓN: Función que evalua una expresión en posfijo.
ENTRADA: Un arreglo de tipo caracter de TAM 100
SALIDA: Un flotante que contiene el resultado de la evaluación en posfijo.
OBSERVACIONES: Se emplea la libreria TADPilaEst.h,TADPilaDin.h,stdio.h,stdlib.h,string.h, math.h.Solicita el valor de las varibales.
*/

float
EvalPosfijo (char array[TAM])
{

  int i;			//Se declara una variable de tipo entero que  se usará como contador                    
  int k = 0;			//Se declara e inicializa una variable de tipo entero que  se usará como contador
  int tamCadena;		//Se declara una variable de tipo entero que  se usará para almacenar la longitud de la cadena.
  int val_posicion = 0;		//Se declara una variable de tipo entero que  se usará para almacenar la posición de un arreglo.
  float resultado = 0.0f;	//Se declara una variable e inicializa de tipo flotante que  se usará para almacenar el resultado al aplicar un operador, 
  float res_final = 0.0f;	//Se declara una variable e inicializa de tipo flotante que  se usará para almacenar el resultado de la evaluación-
  float valor = 0.0f;		//Se declara una variable e inicializa de tipo flotante que  se usará para almacenar el valor de la varibale.
  float valor_variable[27];	//Se declara una arreglo de logitud 27 de tipo flotante que  se usará para alamcenar el valor de las varibales
  elemento E, E1, E2, E3, E4, Res;	//Se declaran 6 elementos

  pila valores;			//Se crea una pila.
  Initialize (&valores);	//Se inicializa una pila.

  tamCadena = strlen (array);	//Se obtiene la longitud de la cadena.

  while (k <= 27)		//Se limpia el arreglo donde se almacenaran los valores de las variables.
    {
      valor_variable[k] = '\0';
      k++;
    }

  for (i = 0; i < tamCadena; i++)	//Ciclo que recorre cada caracter de la cadena.
    {

      E.Char = array[i];	//Se aigana al elemento E la posición i del arreglo.
      E1.Float;
      E2.Float;

      if (E.Char >= (char) 65 && E.Char <= (char) 90)	//Si el elemento E.Char del arreglo es un operando
	{
	  val_posicion = (int) E.Char;	//Se asigna el valor en codigo ascci a val_posición.

	  if (valor_variable[val_posicion - 65] == '\0')	//Si la posición del arreglo que almacena el valor de las variables està vacio.
	    {
	      printf ("Insertar el valor de la variable %c:", val_posicion);	//Se solicita al usuario final el valor de la variable.
	      scanf ("%f", &valor);	//Se almcena en la variable valor.
	      valor_variable[val_posicion - 65] = valor;	//La posición del arreglo que almacena el valor de las variables se le asigana el valor de la varibale.
	      valor = 0.0f;	//Se limpia la variable valor.
	    }



	  E4.Float = valor_variable[val_posicion - 65];	//Se le asigana a un elemento el valor de la posición del arreglo que almacena el valor de las varibales.
	  Push (&valores, E4);	//Se empila el elemento.

	}

      if (E.Char == '^')	//Si el operador es una potencia.
	{
	  E1 = Pop (&valores);	//Se desempila un elemento.
	  E2 = Pop (&valores);	//Se desempila un elemento.
	  resultado = pow (E2.Float, E1.Float);	//Se realiza la operación potencia.
	  E3.Float = resultado;	//Se le asigna a E4 el valor del resultado de la operación.
	  Push (&valores, E3);	//Se empila el resultado.
	}

      if (E.Char == '*')
	{
	  E1 = Pop (&valores);	//Se desempila un elemento.
	  E2 = Pop (&valores);	//Se desempila un elemento.
	  resultado = (E1.Float * E2.Float);	//Se realiza la operación multiplicación.
	  E3.Float = resultado;	//Se le asigna a E4 el valor del resultado de la operación.
	  Push (&valores, E3);	//Se empila el resultado.
	}

      if (E.Char == '/')
	{
	  E1 = Pop (&valores);	//Se desempila un elemento.
	  E2 = Pop (&valores);	//Se desempila un elemento.
	  resultado = (E1.Float / E2.Float);	//Se realiza la operación división.
	  E3.Float = resultado;	//Se le asigna a E4 el valor del resultado de la operación.
	  Push (&valores, E3);	//Se empila el resultado.
	}

      if (E.Char == '+')
	{
	  E1 = Pop (&valores);	//Se desempila un elemento.
	  E2 = Pop (&valores);	//Se desempila un elemento.
	  resultado = (E1.Float + E2.Float);	//Se realiza la operación suma.
	  E3.Float = resultado;	//Se le asigna a E4 el valor del resultado de la operación.
	  Push (&valores, E3);	//Se empila el resultado.
	}
      if (E.Char == '-')
	{
	  E1 = Pop (&valores);	//Se desempila un elemento.
	  E2 = Pop (&valores);	//Se desempila un elemento.
	  resultado = (E1.Float - E2.Float);	//Se realiza la operación resta.
	  E3.Float = resultado;	//Se le asigna a E4 el valor del resultado de la operación.
	  Push (&valores, E3);	//Se empila el resultado.
	}




    }

  Res.Float;
  Res = Pop (&valores);		//Se le asigna al elemento Res el resultado final de la evaluación.

  res_final = Res.Float;	//Se le asigana el resultado final a una variable.

  Destroy (&valores);		//Se destruye la pila.
  return res_final;		//Se retorna el resultado final de la evalaución.


}

//PRINCIPAL

int
main (void)
{
  char cadena[TAM];		//Se declara un arreglo de tipo caracter y de tamaño definido arriba (TAM 100)
  char *cadena_posfijo = '\0';	//Se declara Variable de tipo apuntador a caracter que recibe el arreglo que retorna la función posfijo
  float resultado;		//Se declara una variable de tipo entero 

  printf ("<<<<<<<<<<<<<Bienvenido>>>>>>>>>>>>>:\n");	//Impresión en pantalla
  printf ("Inserte una expresion aritmetica:\n");	//Impresión en pantalla


  scanf ("%s", cadena);		//Captura la expresión y la guarda en el arreglo de tipo caracter declarado anteriormente

  ValidarParentesis (cadena);	//Se llama a la primer función teniendo como entrada la cadena ingresada por el usuario

  cadena_posfijo = Posfijo (cadena);	//Variable de tipo caracter que llama a nuestra segunda función (posfijo) 
  printf ("Expresion en posfijo:\t %s \n", cadena_posfijo);	//Impresión en pantalla del resultado del arreglo resultante de la función que se llamo en la linea anterior

  resultado = EvalPosfijo (cadena_posfijo);	//Variable de tipo flotante que llama a nuestra tercera función, tomando como entrada para esta, el arreglo retornado por la función posfijo y sustituyendo los valores de las variables dadas por el usuario
  printf ("Evaluacion: \t %f \n", resultado);	//Impresión en pantalla del resultado de la operación aritmetica.
}
