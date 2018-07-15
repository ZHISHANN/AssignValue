#include "TextParser.h"
#include <string.h>
#include <ctype.h>
#include <malloc.h>
#include "Exception.h"
#include <stdio.h>
#include "TextParser.h"
#include "Error.h"

/**********************************************************************
* check the content in line , if NULL return 1                        *
* check the table , if empty return error msg                         *
* if table not empty , compare and fnd the word "assign" of line      *
* if "assign" was not found return error msg                          *
* if "assign" was found , check for the content in varTableMapping    *
* if the content of line does not appear in table , return error msg  *
* if the content of both condition was match , chack for the "=" sign *
* if "=" was found , convert the content of line into number          *
* if "=" was not found , return error msg                             *
**********************************************************************/

int parseTextAndAssignValues(char **line, VariableMapping *varTableMapping)
{
  char *temp = varTableMapping;

  if((*line) == NULL)
    return 1;

  if(varTableMapping == NULL)   // error if no table provided
  {
      throwSimpleError(ERR_TABLE_IS_MISSING,"ERR : Table was not found/missing.");
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
            if (parseAndCompare(line,"=")) // "=" was found
  			    {
              *varTableMapping->storage = parseAndConvertToNum(line);    //find the relevant name and convert to num
               varTableMapping = temp;                                   // start over again to search the name
            }
             else // error if no "="
               throwSimpleError(ERR_MALFORM_ASSIGN,"ERR : The = sign was not found/missing.");
        }
        else  // increase pointer to continue search name in table
          varTableMapping++;
      }  // error if the content od line does not match to table
      throwSimpleError(ERR_UNKNOWN_VARIABLE,"ERR : The variable was not found/given in the table provided.");
    }
    else  // error if no "assign"
      throwSimpleError(ERR_UNKNOWN_COMMAND,"ERR : The word assign was not found/missing.");
  }

}

int parseAndCompare(char **linePtr, char *cmpStr)
{
	int move = 0;

  while (isspace(**linePtr))
  {
		(*linePtr)++;             // ignore space
  	move++;                   // increase pointer
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
		while ((tolower(**linePtr) == tolower(*cmpStr)) && (**linePtr != '\0' || *cmpStr != '\0'))
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
    (*linePtr)++;              // ignore the space
    move++;                    // increase pointer
  }

	while(**linePtr != '\0')       // if contain content
  {
      if (isdigit(**linePtr))   // if the content was a number
      {
        dec = dec * 10 + (**linePtr - '0');
  		  (*linePtr)++;
      }

      else  // the content not a number
      {
        (*linePtr) -= move;
        throwSimpleError(ERR_NOT_A_NUMBER,"ERR : %s was not a number.");
      }

      while ((**linePtr) == ' ')  // ignore space
      {
        linePtr++;
        move++;
        return dec;
      }
	}  // return the calculated value
  return dec;
}
