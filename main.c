/*
AUTOR: Dominguez Moran Joaqu�n, Garc�a Iba�ez Diego, Rosas S�nchez Paloma. Agosto 2017.
VERSI�N: 1.0.

DESCRIPCI�N: Programa que valida y evalua una expresi�n infija.

OBSERVACIONES: El programa utiliza 6 funciones para realizar las operaciones que poco a poco modifican la matriz original.

COMPILACI�N: 
			Windows: gcc main.c TADPilaEst.c
			Linux: gcc main.c TADPilaEst.c -lm

EJECUCI�N: 
			Windows: a.exe
			Linux: ./a
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



//DEFINICI�N DE FUNCIONES

/*
**void ValidarParentesis (char array[TAM])**
DESCRIPCI�N: Funci�n que evalua una expresi�n para asegurar que los parentesis estan escritos de manera correcta.
ENTRADA: Un arreglo de tipo caracter de TAM 100
SALIDA: Impresi�n en pantalla del resultado de la evaluaci�n
OBSERVACIONES: Se emplea la libreria TADPilaEst.h
*/

void
ValidarParentesis (char array[TAM])
{
  int i = 0;			//Se declara una variable de tipo entero y se inicializa en 0 
  int tamano;			//Se declara una variable de tipo entero
  float valor;			//Se declara variable de tipo flotante
  tamano = strlen (array);	//Medir el tama�o del arreglo
  elemento e;			//Se declara un elemento e
  pila palpila;			//Se declara una pila "palpila"
  Initialize (&palpila);	//Inicializaci�n de la pila "palpila"
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
		("Existen m�s parentesis de los que cierran de los que abren. \n");
	      exit (1);
	    }

	  Pop (&palpila);

	}

    }

  if (!Empty (&palpila))	//Si al terminar de revisar la expresión aún hay elementos en la pila Error
    {
      printf
	("Existen m�s parentesis de los que abren de los que cierran.\n");
      exit (1);
    }

  printf ("Expresion correcta.\n");	//Si la ejecuci�n termina de manera correcta


  Destroy (&palpila);		//Destruir los elementos de la pila
  
}

/*
**char *Posfijo (char array[TAM])**
DESCRIPCI�N: Funci�n que pasa una expresi�n aritm�tica en posfijo a partir de la expresi�n infija.
ENTRADA: Un arreglo de tipo caracter de TAM 100
SALIDA: Un arreglo con la expresi�n infija transformada en posfija
OBSERVACIONES: ****
*/

char *
Posfijo (char array[TAM])
{
  int i;			//Se declara una variable de tipo entero 
  int j = 0;			//Se declara e inicializa una variable de tipo entero
  int k = 0;			//Se declara e inicializa una variable de tipo entero
  int tamCadena;		//Se declara una variable de tipo entero
  char *resultado;		//Se declara variable de tipo apuntador
  elemento E, E1, E2;		//Se declara elemento E,E1,E2

  tamCadena = strlen (array);	////Medir el tama�o del arreglo

  pila posfijo;			//Se declara una pila "posfijo"
  Initialize (&posfijo);	//Inicializar pila "posfijo"

  resultado = (char *) malloc (1 * sizeof (char));



  for (i = 0; i < tamCadena; i++)	//Ciclo for que recorre cada caracter del arreglo
    {

      E.Char = array[i];

      //Si el elemento i del arreglo es un operando se agrega directamente a resultado


      if (E.Char >= (char) 65 && E.Char <= (char) 90)
	{

	  resultado = (char *) realloc (resultado, (j + 1) * sizeof (char));
	  resultado[j] = E.Char;
	  j++;


	}

      //Si el elemento i del arreglo es un parentesis que abre se agrega a la pila.
      if (E.Char == '(')
	{

	  Push (&posfijo, E);

	}

      //Si el elemento i del arreglo es un parentesis que cierra.

      if (E.Char == ')')
	{
	  if (Empty (&posfijo) == FALSE)
	    E1 = Top (&posfijo);
	  while (E1.Char != '(')
	    {
	      E2 = Pop (&posfijo);
	      resultado =
		(char *) realloc (resultado, (j + 1) * sizeof (char));
	      resultado[j] = E2.Char;
	      j++;


	      if (Empty (&posfijo) == FALSE)
		E1 = Top (&posfijo);

	    }
	  Pop (&posfijo);

	}


      if (E.Char == '+' || E.Char == '-')
	{
	  if (Empty (&posfijo) == FALSE)
	    E1 = Top (&posfijo);

	  if ('(' == E1.Char || Empty (&posfijo) == TRUE)
	    Push (&posfijo, E);

	  else
	    {

	      while (E1.Char != '(' && Empty (&posfijo) == FALSE)
		{
		  E2 = Pop (&posfijo);
		  resultado =
		    (char *) realloc (resultado, (j + 1) * sizeof (char));
		  resultado[j] = E2.Char;
		  j++;
		  if (Empty (&posfijo) == FALSE)
		    E1 = Top (&posfijo);

		}

	      Push (&posfijo, E);
	    }

	}



      if (E.Char == '*' || E.Char == '/')
	{

	  if (Empty (&posfijo) == FALSE)
	    E1 = Top (&posfijo);

	  if (('*' != E1.Char && '/' != E1.Char && '^' != E1.Char)
	      || Empty (&posfijo) == TRUE)
	    Push (&posfijo, E);

	  else
	    {


	      while (('*' == E1.Char || '/' == E1.Char || '^' == E1.Char)
		     && Empty (&posfijo) == FALSE)
		{
		  E2 = Pop (&posfijo);
		  resultado =
		    (char *) realloc (resultado, (j + 1) * sizeof (char));
		  resultado[j] = E2.Char;
		  j++;

		  if (Empty (&posfijo) == FALSE)
		    E1 = Top (&posfijo);

		}

	      Push (&posfijo, E);
	    }

	}

      if (E.Char == '^')
	{

	  if (Empty (&posfijo) == FALSE)
	    E1 = Top (&posfijo);
	  if ('^' != E1.Char || Empty (&posfijo) == TRUE)
	    Push (&posfijo, E);

	  else
	    {

	      while ('^' == E1.Char && Empty (&posfijo) == FALSE)
		{
		  E2 = Pop (&posfijo);
		  resultado =
		    (char *) realloc (resultado, (j + 1) * sizeof (char));
		  resultado[j] = E2.Char;
		  j++;

		  if (Empty (&posfijo) == FALSE)
		    E1 = Top (&posfijo);

		}

	      Push (&posfijo, E);
	    }

	}

    }


  if (Empty (&posfijo) == FALSE)
    {

      while (Empty (&posfijo) == FALSE)
	{
	  E2 = Pop (&posfijo);
	  resultado = (char *) realloc (resultado, (j + 1) * sizeof (char));
	  resultado[j] = E2.Char;
	  j++;

	}

    }

  Destroy (&posfijo);
  resultado[j] = '\0';


  return resultado;


}

///////////////////////////////////////////////////////////////////////////////////////////


float
EvalPosfijo (char array[TAM])
{

  int i;
  int k = 0;
  int tamCadena;
  int val_posicion = 0;
  float resultado = 0.0f;
  float res_final = 0.0f;
  float valor = 0.0f;
  float valor_variable[27];
  elemento E, E1, E2, E3, E4, Res;

  pila valores;
  Initialize (&valores);

  tamCadena = strlen (array);

  while (k <= 27)
    {
      valor_variable[k] = '\0';
      k++;
    }

  for (i = 0; i < tamCadena; i++)
    {

      E.Char = array[i];
      E1.Float;
      E2.Float;

      if (E.Char >= (char) 65 && E.Char <= (char) 90)
	{
	  val_posicion = (int) E.Char;

	  if (valor_variable[val_posicion - 65] == '\0')
	    {
	      printf ("Insertar el valor de la variable %c:", val_posicion);
	      scanf ("%f", &valor);
	      valor_variable[val_posicion - 65] = valor;
	      valor = 0.0f;
	    }



	  E4.Float = valor_variable[val_posicion - 65];
	  Push (&valores, E4);

	}

      if (E.Char == '^')
	{
	  E1 = Pop (&valores);
	  E2 = Pop (&valores);
	  resultado = pow (E2.Float, E1.Float);
	  E3.Float = resultado;
	  Push (&valores, E3);
	}

      if (E.Char == '*')
	{
	  E1 = Pop (&valores);
	  E2 = Pop (&valores);
	  resultado = (E1.Float * E2.Float);
	  E3.Float = resultado;
	  Push (&valores, E3);
	}

      if (E.Char == '/')
	{
	  E1 = Pop (&valores);
	  E2 = Pop (&valores);
	  resultado = (E1.Float / E2.Float);
	  E3.Float = resultado;
	  Push (&valores, E3);
	}

      if (E.Char == '+')
	{
	  E1 = Pop (&valores);
	  E2 = Pop (&valores);
	  resultado = (E1.Float + E2.Float);
	  E3.Float = resultado;
	  Push (&valores, E3);
	}
      if (E.Char == '-')
	{
	  E1 = Pop (&valores);
	  E2 = Pop (&valores);
	  resultado = (E1.Float - E2.Float);
	  E3.Float = resultado;
	  Push (&valores, E3);
	}




    }

  Res.Float;
  Res = Pop (&valores);

  res_final = Res.Float;

  Destroy (&valores);
  return res_final;


}

//PRINCIPAL

int
main (void)
{
  char cadena[TAM];		//Se declara un arreglo de tipo caracter y de tama�o definido arriba (TAM 100)
  char *cadena_posfijo = '\0';	//Se declara Variable de tipo apuntador a caracter que recibe el arreglo que retorna la funci�n posfijo
  float resultado;		//Se declara una variable de tipo entero 

  printf ("<<<<<<<<<<<<<Bienvenido>>>>>>>>>>>>>:\n");	//Impresi�n en pantalla
  printf ("Inserte una expresi�n aritmetica:\n");	//Impresi�n en pantalla


  scanf ("%s", cadena);		//Captura la expresi�n y la guarda en el arreglo de tipo caracter declarado anteriormente

  ValidarParentesis (cadena);	//Se llama a la primer funci�n teniendo como entrada la cadena ingresada por el usuario

  cadena_posfijo = Posfijo (cadena);	//Variable de tipo caracter que llama a nuestra segunda funci�n (posfijo) 
  printf ("Expresi�n en posfijo:\t %s \n", cadena_posfijo);	//Impresi�n en pantalla del resultado del arreglo resultante de la funci�n que se llamo en la linea anterior

  resultado = EvalPosfijo (cadena_posfijo);	//Variable de tipo flotante que llama a nuestra tercera funci�n, tomando como entrada para esta, el arreglo retornado por la funci�n posfijo y sustituyendo los valores de las variables dadas por el usuario
  printf ("Evaluaci�n: \t %f \n", resultado);	//Impresi�n en pantalla del resultado de la operaci�n aritmetica.
}
