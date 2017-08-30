#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADPilaEst.h"

#define TAM 100

void
ValidarParentesis (char array[TAM])
{
  int i = 0;
  int tamano;
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
		("Existen más parentesis de los que cierran de los que abren");
	      exit (1);
	    }
	  Pop (&palpila);

	}

    }

  if (!Empty (&palpila))
    {
      printf ("Existen más parentesis de los que abren de los que cierran");
      exit (1);
    }

  printf ("Expresion correcta");
  exit (0);



}

int
main (void)
{

  char cadena[TAM];

  scanf ("%s", cadena);

  ValidarParentesis (cadena);

}
