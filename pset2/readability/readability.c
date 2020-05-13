#include <stdio.h>
#include <cs50.h>
#include <regex.h>
#include <string.h>
#include <math.h>

int match(regex_t *regex, char *input);

int main(void)
{
    string input = get_string("Text: ");


    regex_t regex;
    int letters = 0;
    int words = 0;
    int sentences = 0;

    const char* wordPattern = "[a-zA-Z0-9'_-]+";
    const char* sentencePattern = "[.!?]";

    int i = 0;
    // Count the number of letters
    while (input[i] != '\0')
    {
        // *input is the same as input[0]
        if ((input[i] >= 'A' && *input <= 'Z') || (input[i] >= 'a' && *input <= 'z'))
        {
            letters++;
        }
        i++;
    }

    int wordsRegex = regcomp(&regex, wordPattern, REG_EXTENDED | REG_ICASE);
    if(wordsRegex)
    {
        printf("Could not compile regex\n");
    }

    words = match(&regex, input);

    int sentencesRegex = regcomp(&regex, sentencePattern, REG_EXTENDED | REG_ICASE);
    if(sentencesRegex)
    {
        printf("Could not compile regex\n");
    }

    sentences = match(&regex, input);

    float L = ((float)letters / (float)words) * 100;
    float S = ((float)sentences / (float)words) * 100;

    int index = round((0.0588 * L) - (0.296 * S) - 15.8);

    if(index >= 16){
        printf("Grade 16+\n");
    }
    else if(index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %d\n", index);
    }

    regfree(&regex);
}

int match(regex_t *regex, char *input) {
    // we just need the whole string match in this example
    regmatch_t wholeMatch;

    // we store the eflags in a variable, so that we can make
    // ^ match the first time, but not for subsequent regexecs
    int matches = 0;
    size_t offset = 0;
    size_t length = strlen(input);

    while (regexec(regex, input + offset, 1, &wholeMatch, 0) == 0) {

        // increase the starting offset
        offset += wholeMatch.rm_eo;

        // a match can be a zero-length match, we must not fail
        // to advance the pointer, or we'd have an infinite loop!
        if (wholeMatch.rm_so == wholeMatch.rm_eo) {
            offset += 1;
        }

        // break the loop if we've consumed all characters. Note
        // that we run once for terminating null, to let
        // a zero-length match occur at the end of the string.
        if (offset > length) {
            break;
        }

        matches++;
    }

    return matches;
}