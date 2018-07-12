#include "TextParser.h"
#include <string.h>
#include <ctype.h>
#include <malloc.h>
#include "Exception.h"
#include <stdio.h>

int parseTextAndAssignValues(char *line, VariableMapping *varTableMapping)
{
  int *temp_line, i, *Line;
  temp_line = malloc(256);
  Line = (line + 6);

  if(*line == '\0')
    return 1;

  //error if no table provided
  if(varTableMapping == NULL)
  {
    throwSimpleError(5,"ERR_TABLE_IS_MISSING");
  }
  else //table not null
  {
    //check got "assign" or not
    for (i = 0; i <= 6 ; i++)
    {
      temp_line[i] = *line;
    }

    if(parseAndCompare(temp_line,"assign"))  //contain assign
    {
      if(*Line != NULL) //word after assign not null
      {
        if(parseAndCompare(Line,*varTableMapping->name)) //find the name in table
        {
          if(parseAndCompare(Line,"=")) //"=" was found
          {
            *varTableMapping->storage = parseAndConvertToNum(line);
          }
          else // no "="
            throwSimpleError(4,"ERR_MALFORM_ASSIGN");
        }
        else //name not found
          Line++;
      }
      else //Line is null
        return 1;
    }
    else  // no assign
      throwSimpleError(3,"ERR_UNKNOWN_COMMAND");
  }
}

int parseAndCompare(char **linePtr, char *cmpStr)
{
  int move = 0;

  /*if((**linePtr) == '=' && (*cmpStr) == '=')
  {
   (*linePtr)++;
   return 1;
  }*/

  while (**linePtr != '\0' || *cmpStr != '\0')
  {
    if (tolower(**linePtr) == tolower(*cmpStr))
    {
      (*linePtr)++;
      cmpStr++;
      move++;
    }
    else if (isspace(**linePtr))
    {
      (*linePtr)++;
      move++;
    }
    else if (isspace(*cmpStr))
    {
      cmpStr++;
      move++;
    }
    else
    {
      (*linePtr) -= move;
      return 0;
    }
  }
  return 1;
}

int parseAndConvertToNum(char **linePtr)
{
	int dec = 0;

	while(**linePtr != '\0')
  {
    if (isspace(**linePtr))
    {
      dec = dec * 10 + (**linePtr - '0' );
      (*linePtr)++;
    }
    else
    {
      dec = dec * 10 + (**linePtr - '0' );
      (*linePtr)++;
    }
	}
  return dec;
}

int LengthOfMsg(char *msg)
{
	int length = 0;

	while(msg[length] != '\0')
		length++;
		return length;
}
