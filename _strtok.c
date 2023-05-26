#include "shell.h"

/**
 * _strtok - Tokenize a string.
 * @string: The string to be tokenized.
 * @delimiter: The token delimiter.
 * @whichFunc: Which comparison function to use (0 for _strcmpd, 1 for _strcmps).
 *
 * Return: A character pointer to the current delimited token.
 */
char *_strtok(char *string, const char *delimiter, int whichFunc)
{
static char *save;
char *newToken = NULL;
int index = 0, (*compareFunc)(char *, const char *), location, inQuotes = 0;

compareFunc = (whichFunc == 0) ? _strcmpd : _strcmps;
location = (whichFunc) ? _strlen(delimiter) - 1 : 0;

if (!string || !*string)
{
if (!save || !*save)
return (NULL);

while (inQuotes || (compareFunc(save + index, delimiter) != 1 && *(save + index) != '\0'))
{
if (*(save + index) == '\'' || *(save + index) == '\"')
inQuotes = !inQuotes;
index++;
}

if (*(save + index) == '\0')
{
newToken = save;
save = NULL;
return (newToken);
}

newToken = save;
*(save + index) = '\0';
save = save + index + location + 1;
return (newToken);
}

while (inQuotes || (compareFunc(string + index, delimiter) != 1 && *(string + index) != '\0'))
{
if (*(string + index) == '\'' || *(string + index) == '\"')
inQuotes = !inQuotes;
index++;
}

if (*(string + index) == '\0')
{
save = NULL;
return (string);
}

save = string + index + location + 1;
*(string + index) = '\0';
return (string);
}
