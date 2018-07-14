#include "TextParser.h"
#include <string.h>
#include <ctype.h>
#include <malloc.h>
#include "Exception.h"
#include <stdio.h>
#include "TextParser.h"
#include "Error.h"

int parseTextAndAssignValues(char **line, VariableMapping *varTableMapping)
{
  char *temp = varTableMapping;

  if((*line) == NULL)
    return 1;

  if(varTableMapping == NULL)   // error if no table provided
  {
      throwSimpleError(ERR_TABLE_IS_MISSING,"ERR_TABLE_IS_MISSING");
  }
  else //table not null
  {
    if(parseAndCompare(line,"assign")) //check got "assign" or not
    {
      while(varTableMapping->name != NULL) // if name not NULL
      {
        if ((**line) == '\0')
          return 1;

        if(parseAndCompare(line,varTableMapping->name)) //find the name in table
        {
            if (parseAndCompare(line,"=")) // "=" was found)
  			    {
              *varTableMapping->storage = parseAndConvertToNum(line);    //find the relevant name and convert to num
               varTableMapping = temp;
            }
             else // error if no "="
               throwSimpleError(ERR_MALFORM_ASSIGN,"ERR_MALFORM_ASSIGN");
        }
        else
          varTableMapping++;
      }
      throwSimpleError(ERR_UNKNOWN_VARIABLE,"ERR_UNKNOWN_VARIABLE");
    }
    else  // error if no assign
      throwSimpleError(ERR_UNKNOWN_COMMAND,"ERR_UNKNOWN_COMMAND");
  }

}

int parseAndCompare(char **linePtr, char *cmpStr)
{
	int move = 0;

  while (isspace(**linePtr))
  {
		(*linePtr)++;             // ignore space
  	move++;                   // move pointer
  }

  while (isspace(*cmpStr))    // ignore space
	{
    	cmpStr++;
  }

	if (**linePtr == '\0')     // linePtr is NULL should
		return 1;		             // return 1

  else if ((**linePtr) == '\0' && *cmpStr == '\0')  // linePtr & cmpStr reach end or meet NULL
	  return 1;                                       // should return

	else if (**linePtr == '=')   // if "=" was found should return 1
	{
		(*linePtr)++;
		return 1;
	}

	else if (tolower(**linePtr) == tolower(*cmpStr))   // if two string are equal
	{
		while ((tolower(**linePtr) == tolower(*cmpStr)) && (**linePtr != '\0' || *cmpStr != '\0'))  // compare if equal//
		{
		  (*linePtr)++;
		  cmpStr++;
		  move++;
		}

    if (isspace(**linePtr) || **linePtr == '\0' || *cmpStr == '\0')
      return 1;
    else
    {
      (*linePtr) -= move;
      return 0;
    }
  }

  else
  {
    (*linePtr) -= move;
		return 0;
  }
}

int parseAndConvertToNum(char **linePtr)
{
	int dec = 0;
  int move = 0;

  while (isspace(**linePtr))
  {
    (*linePtr)++;
    move++;
  }

	while(**linePtr != '\0')
  {
      if (isdigit(**linePtr))
      {
        dec = dec * 10 + (**linePtr - '0');
  		  (*linePtr)++;
      }

      else
      {
        (*linePtr) -= move;
        throwSimpleError(ERR_NOT_A_NUMBER,"ERR_NOT_A_NUMBER");
      }

      while ((**linePtr) == ' ')
      {
        linePtr++;
        move++;
        return dec;
      }
	}
  return dec;
}
