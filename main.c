#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "TADPilaEst.h"
#include "TADPilaDin.h"
#include <math.h>

#define TAM 100

void
ValidarParentesis (char array[TAM])
{
  int i = 0;
  int tamano;
  float valor;
  tamano = strlen (array);
  elemento e;
  pila palpila;
  Initialize (&palpila);
  for (i = 0; i < tamano; i++)
    {
      e.Char = array[i];
      if (array[i] == '(')
	Push (&palpila, e);
      if (array[i] == ')')
	{
	  if (Empty (&palpila))
	    {

	      printf
		("Existen más parentesis de los que cierran de los que abren. \n");
	      exit (1);

	    }
	  Pop (&palpila);

	}

    }

  if (!Empty (&palpila))
    {
      printf
	("Existen más parentesis de los que abren de los que cierran.\n");
      exit (1);
    }

  printf ("Expresion correcta.\n");

	
  Destroy(&palpila);

}

char *
Posfijo (char array[TAM])
{
  int i;
  int j = 0;
  int k = 0;
  int tamCadena;
  char *resultado;
  elemento E, E1, E2;

  tamCadena = strlen (array);

  pila posfijo;
  Initialize (&posfijo);
  
  resultado=(char*)malloc(1*sizeof(char));



  for (i = 0; i < tamCadena; i++)
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

  Destroy(&posfijo);
  resultado[j] = '\0';
	

  return resultado;


}

float
EvalPosfijo (char array[TAM])
{

  int i;
  int k = 0;
  int tamCadena;
  int val_posicion = 0;
  float resultado=0.0f;
  float res_final=0.0f;
  float valor=0.0f;
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
 	      valor=0.0f;
	    }
	  


	  E4.Float = valor_variable[val_posicion - 65];
	  Push (&valores, E4);

	}

      if (E.Char == '^')
	{
	  E1 = Pop (&valores);
	  E2 = Pop (&valores);
	  resultado = pow (E2.Float,E1.Float);
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

  Destroy(&valores);
  return res_final;


}

int
main (void)
{


  char cadena[TAM];
  char *cadena_posfijo='\0';
  float resultado;

  printf ("<<<<<<<<<<<<<Bienvenido>>>>>>>>>>>>>:\n");
  printf ("Inserte una expresión aritmetica:\n");


  scanf ("%s", cadena);

  ValidarParentesis (cadena);

  cadena_posfijo = Posfijo (cadena);
  printf ("Expresión en posfijo:\t %s \n", cadena_posfijo);

  resultado = EvalPosfijo (cadena_posfijo);
  printf ("Evaluación: \t %f \n", resultado);




}
