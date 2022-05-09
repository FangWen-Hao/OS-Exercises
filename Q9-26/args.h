/*!
    @header Argument Parsing
    Functions for getting arguments from the command line. Below are some usage
    examples.

*/

#include <string.h>
#include <stdlib.h>
#include <assert.h>

const char * usage_instructions =
  "Usage:\n\
      Q9-26\n\
  \n\
      Default mode: Prints the number of page by default for a fixed reference string\n\
      and 1 to 7 page frames.\n\
      Reference string: 1 2 3 4 2 1 5 6 2 1 2 3 7 6 3 2 1 2 3 6.\n\
  ----------------\n\
      Q9-26 -npf 8\n\
      Run against the fixed reference string using 8 page frames.\n\
      Argument must be > 0.\n\
  ----------------\n\
      Q9-26 -npf 9 -rand\n\
      Use 9 page frames against a randomly generated reference string. The random\n\
      reference string contains only page numbers in the range 0 to 9. The random\n\
      reference string length is 20 by default. If -npf is not specified 7\n\
      is the default.\n\
  ----------------\n\
      Q9-26 -npf 10 -rand -rsl 31\n\
      Use 10 page frames against a randomly generated reference string. The random\n\
      reference string contains only page numbers in the range 0 to 9. The random\n\
      reference string length is set to 31. If -npf is not specified 7\n\
      is the default.\n\
  ----------------\n\
      Q9-26 -npf 11 -rs '1 2 3 4 5 1 2 3 6'\n\
      Use 11 page frames against the reference string specified by the -rs\n\
      argument. The single quotes are required.\n";

/*!

    @function get_positive_arg

    @discussion Gets an argument that is a positive integer.

    @param argc    The usual argc argument to main().

    @param argv    The usual argv argument to main().

    @param pi    Pointer to an int in which to return the value of the command
    line argument.

    @param arg_name    The name of the command line argument e.g. -npf

    @result Less than 0 if an error occurred in which case the program should
    bail. 0 if the argument was not present, pi is untouched. 1 if the argument
    was present and its value was valid.
*/
int get_positive_arg(const int argc, char**  argv, int * const pi, const char * const arg_name) {
    int arg_name_count;
    int i;
    char *endptr = NULL;
    int arg_length;

    if(argc < 0 || argv == NULL || pi == NULL || arg_name == NULL) {
        assert(0);
        return -1;
    }

    arg_name_count = 0;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], arg_name) == 0) {
            arg_name_count = 1;
            break;

        }
    }

    if(!arg_name_count) {
        return 0;
    }

    i++;

    if(i >= argc) {
        // A value is required.
        return -2;
    }

    if(strlen(argv[i]) <= 0) {
        // Again, a value is required.
        return -3;
    }

    arg_length = strtol(argv[i], &endptr, 10);

    if(endptr != NULL && *endptr != '\0') {
        // Arg. value contained non-integer character.
        return -4;
    }

    if(arg_length <= 0) {
        // Arg. value should be positive integer.
        return -5;
    }

    *pi = arg_length;

    return 1;
}

/*!

    @function get_boolean_arg

    @discussion Gets a boolean argument i.e. an argument that is either present
    or not, and has no associated value.

    @param argc    The usual argc argument to main().

    @param argv    The usual argv argument to main().

    @param b       Pointer to an int, set to the argument number if the argument
                   was present, the argument number is always greater than or
                   equal to 1, if the argument was present, or 0 if not present.
                   The pointer is not touched if an error occurred.

    @param arg_name    The name of the command line argument e.g. -rand

    @result Less than 0 if an error occurred in which case the program should
    bail. 0 if the argument was not present. 1 if the argument was present.
*/
int get_boolean_arg(const int argc, char** argv, int * const b, const char * const arg_name) {
    int i;

    if(argc < 0 || argv == NULL || arg_name == NULL) {
        assert(0);
        return -1;
    }

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], arg_name) == 0) {
            *b = i;
            return 1;
        }
    }

    *b = 0;
    return 0;
}
