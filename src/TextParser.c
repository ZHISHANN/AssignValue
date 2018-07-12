#include "TextParser.h"
#include <string.h>
#include <ctype.h>
#include <malloc.h>
#include "Exception.h"
#include <stdio.h>

int parseTextAndAssignValues(char **line, VariableMapping *varTableMapping)
{
  if((*line) == NULL)
    return 1;

  else if(varTableMapping == NULL)   // error if no table provided
  {
    throwSimpleError(5,"ERR_TABLE_IS_MISSING");
  }

  else //table not null
  {
    //check got "assign" or not
    if(parseAndCompare(line,"assign"))
    {
      while(varTableMapping->name != '\0')
      {
        if(parseAndCompare(line,varTableMapping->name)) //find the name in table
        {
          if(parseAndCompare(line,"=")) // "=" was found
          {
			        *varTableMapping->storage = parseAndConvertToNum(line);    //find the relevant name and convert to num
              varTableMapping++;
          }
          else // error if no "="
            throwSimpleError(4,"ERR_MALFORM_ASSIGN");
        }
        else //name not found and continue find
          line++;
      }
      //Line is null should return 1
        return 1;
    }
    else  // error if no assign
      throwSimpleError(3,"ERR_UNKNOWN_COMMAND");
  }
}

int parseAndCompare(char **linePtr, char *cmpStr)
{
	int move = 0;

	if (**linePtr == '\0')     // linePtr is a blank space//
		return 1;		             // return 1

  else if ((**linePtr) == '\0' && *cmpStr == '\0')  // linePtr & cmpStr reach end
	  return 1;

	else if (isspace(*cmpStr))    // ignore space//
		cmpStr++;

	else if (isspace(**linePtr))
	{
		(*linePtr)++;             // ignore space//
		move++;                   // move pointer
	}

	else if (**linePtr == '=')  // if "=" was found should return 1//
	{
		(*linePtr)++;
		return 1;
	}

	else if (tolower(**linePtr) == tolower(*cmpStr))  // if not NULL//
	{
		while ((tolower(**linePtr) == tolower(*cmpStr)) && (**linePtr != '\0' || *cmpStr != '\0'))  // compare if equal//
		{
		  (*linePtr)++;
		  cmpStr++;
		  move++;
		}

    if (tolower(**linePtr) == tolower(*cmpStr) || isspace(**linePtr) || *cmpStr == '\0')
    {
      if (isspace(**linePtr) || **linePtr == '\0' || *cmpStr == '\0')
        return 1;
      else
        return 0;
    }
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

	while(**linePtr != '\0')
  {
		if (isspace(**linePtr))
		{
		  (*linePtr)++;
		}
    else if (isdigit(**linePtr) == 0)
      return 0;
		else
		{
		  dec = dec * 10 + (**linePtr - '0' );
		  (*linePtr)++;
		}
	}
  return dec;
}
