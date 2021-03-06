#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define TITLE                                   \
    printf(                                     \
        "Type 'h' for list of commands.\n"      \
        "______________________________\n\n"    \
    );  

#define STRING_LENGTH         35
#define PRETTIFIED_MAX_LENGTH (STRING_LENGTH + (STRING_LENGTH / 3))
#define CHARACTER_LENGTH      18

#define BASE_HEXADECIMAL      16
#define BASE_DECIMAL          10
#define BASE_OCTAL            8
#define BASE_BINARY           2
#define NUMBER_OF_BASES       4


const char digit_char_hex[] = "0123456789abcdefABCDEF";
const char digit_char_dec[] = "0123456789";
const char digit_char_oct[] = "01234567";
const char digit_char_bin[] = "01";

char *bases[NUMBER_OF_BASES] = { "HEX", "DEC", "OCT", "BIN" };

typedef unsigned char ubyte;

typedef enum _base {
    HEX,
    DEC,
    OCT,
    BIN
} base;

const ubyte base_numeric[] = { BASE_HEXADECIMAL, BASE_DECIMAL, BASE_OCTAL, BASE_BINARY };

#define PRINT_ERROR(...)                                            \
    printf(__VA_ARGS__);                                            \
    fflush(stdout);

#define PRINT_HELP                                                                                                                                                      \
    printf(                                                                                                                                                             \
        "-=-=-=-=-=-=-=-=-=-=-Standard Commands-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n"                                                                       \
                                                                                                                                                                        \
        "\"help\",  \"h\"                 - Displays commands  (what's shown right now)\n\n"                                                                            \
                                                                                                                                                                        \
        "\"clear\", \"cls\"               - Clears screen\n\n"                                                                                                          \
                                                                                                                                                                        \
        "\"quit\", \"q\"                  - Quits program\n\n"                                                                                                          \
                                                                                                                                                                        \
        "-=-=-=-=-=-=-=-=-=-=-Number Format-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n"                                                                       \
                                                                                                                                                                        \
        "\"0x[number]\"                 - Hexadecimal number  (base 16)\n\n"                                                                                            \
                                                                                                                                                                        \
        "\"[number]\"                   - Decimal number      (base 10)\n\n"                                                                                            \
                                                                                                                                                                        \
        "\"0o[number]\"                 - Octal number        (base 8)\n\n"                                                                                             \
                                                                                                                                                                        \
        "\"0b[number]\"                 - Binary number       (base 2)\n\n"                                                                                             \
                                                                                                                                                                        \
        "___________________________________________________________________________________\n\n"                                                                       \
                                                                                                                                                                        \
        "*This program does not support negative numbers.\n\n"                                                                                                          \
    );

#define PROCESS_CHAR(valid_set, this_char, base_enum) {             \
    if (strchr(valid_set, this_char)) {                             \
        input[i++] = tolower(this_char);                            \
        (*this_base) = base_enum;                                   \
    }                                                               \
    else {                                                          \
        input[0] = '\0';                                            \
        return 0;                                                   \
    }                                                               \
                                                                    \
    break;                                                          \
}

#define PRETTIFY_STR(space, include_comma) {                        \
    while ((*src) != '\0') {                                        \
        /* don't add a space/comma if last number, e.g.: 100,000 */ \
        if (!(count % (space + 1))) {                               \
            if (include_comma) {                                    \
                dest[i++] = ',';                                    \
            }                                                       \
            if (!(include_comma)) {                                 \
                dest[i++] = ' ';                                    \
            }                                                       \
            count = 1; /* reset count */                            \
        }                                                           \
        dest[i] = temp[length - c];                                 \
        i++;                                                        \
        c++;                                                        \
        count++;                                                    \
        src++;                                                      \
    }                                                               \
    dest[i] = '\0'; /* null-terminate string */                     \
    break;                                                          \
}

/* <max_length> must be one-based, including null-terminator (NOT like how <strlen()> returns) */
unsigned short get_input(char *dest, unsigned short max_length) {
    printf("> ");
    char character;
    unsigned short count = 0;
    while ((character = getchar()) != '\n') {
        if (count > (max_length - 2)) { /* -2 to change <length> to zero-based index and to leave room for null-terminator */
            PRINT_ERROR("Input exceeds maximum buffer, will be truncated to %d characters.\n", max_length)
            break;
        }
        dest[count] = character;
        count++;
    }
    dest[count] = '\0'; /* null-terminate string */
    printf("\n");
    fflush(stdout);

    /* will be one-based, not including null-terminator (like how <strlen()> returns) */
    return count;
}

/* <length> must be one-based, not including null-terminator (like how <strlen()> returns) */
unsigned short clean_input(char *input, unsigned short input_length, base *this_base) {
    unsigned short i = 0, c = 0;

    /* step 1: skip all leading spaces, including all non-alphanumeric characters */
    for (; c < input_length; c++) { 
        if (isalnum((int)input[c])) {
            break;
        }
    }
    
    /* step 2: either <c> is at the end of the string or it should be a number */
    if (c == input_length || !isdigit((int)input[c])) {
        input[0] = '\0';
        return 0;
    }
    input[i++] = input[c++];

    /* step 3: next character should either be representing the base or a number */
    char base_char[] = "XOBxob0123456789";
    char *base;    
    if ((c < input_length) && (base = strchr(base_char, input[c]))) {
        input[i++] = input[c++];
        for (; c < input_length; c++) {
            switch (*base) {
                case 'X':
                case 'x':
                    PROCESS_CHAR(digit_char_hex, input[c], HEX)
                case 'O':
                case 'o':
                    PROCESS_CHAR(digit_char_oct, input[c], OCT)
                case 'B':
                case 'b':
                    PROCESS_CHAR(digit_char_bin, input[c], BIN)
                default:
                    PROCESS_CHAR(digit_char_dec, input[c], DEC)
            }
        }
    }

    /*
    +2 for prefix -> FFFF FFFF                                  (hexadecimal)
    -> 999,999,999                                              (decimal)
    +2 for prefix -> 7 777 777 777                              (octal)
    +2 for prefix -> 1111 1111 1111 1111 1111 1111 1111 1111    (binary)
    */
    int max_length[NUMBER_OF_BASES] = { 8 + 2, 9, 10 + 2, 32 + 2 };
    if (i > max_length[(*this_base)]) {
        input[i] = '\0';
        return 0;
    }

    /* will be one-based, not including null-terminator (like how <strlen()> returns) */
    input[i]= '\0';
    return i;
}


/* <length> must be one-based, not including null-terminator (like how <strlen()> returns) */
ubyte to_decimal(char *src, unsigned short length, ubyte base_numeric, long *long_dest) {
    (*long_dest) = 0;
    for (unsigned short i = 0; i < length; i++) { /* this loop will ignore the null-terminator */
        char digit = src[(length - i) - 1];
        if (digit >= 'a' && digit <= 'f') { /* is a hexadecimal character */
            digit -= 39; /* -39 prepare for conversion to decimal via -'0' */
        }
        (*long_dest) += ((digit - '0')) * pow(base_numeric, i);
    }
    
    /* warning: this check will not work! */
    if ((*long_dest) >= LONG_MAX) {
        return 0; /* too big */
    }
    return 1; /* success */
}

/* <length> must be one-based, not including null-terminator (like how <strlen()> returns) */
/* optimization: this function could first check if <src> is already base decimal, however, it is assumed the caller already does this */
void to_base(long decimal, ubyte to_base_numeric, char *output) {
    ubyte valid_chars[] = "0123456789ABCDEF";
    unsigned short rem = 0;
    for (; decimal != 0; rem++) {
        output[rem] = valid_chars[decimal % to_base_numeric];
        decimal /= to_base_numeric;
    }

    /* reverse the array */
    unsigned short i = 0;
    for (; i < (rem / 2); i++) { /* /2 to meet in the middle */
        ubyte temp = output[i];
        output[i] = output[(rem - i) - 1];
        output[(rem - i) - 1] = temp;
    }
    output[rem] = '\0'; /* null-terminate string */
}

void prettify_string(char *src, unsigned short length, base this_base, char *dest) {
    char *temp = src;
    ubyte i = 0, c = 1, count = 1;
    switch (this_base) {
        case HEX:
            PRETTIFY_STR(4, 0)
        case DEC:
            PRETTIFY_STR(3, 1)
        case OCT:
            PRETTIFY_STR(3, 0)
        case BIN:
            PRETTIFY_STR(4, 0)
    }

    /* reverse <dest> */
    for (unsigned short c = 0; c < (i / 2); c++) { /* /2 to meet in the middle */
        char temp_char = dest[c];
        dest[c] = dest[(i - c) - 1];
        dest[(i - c) - 1] = temp_char;
    }
}


void print_output(char *converted, base this_base) {  
    printf("%s: %s\n", bases[this_base], converted);
    fflush(stdout);
}


int base_converter(void) {
    char input[STRING_LENGTH];
    unsigned short length = 0;

    TITLE
    while (1) {
        length = get_input(input, STRING_LENGTH);
        if (!strcmp(input, "q") || !strcmp(input, "quit")) {
            return 0; /* quit program */
        }
        if (!strcmp(input, "cls") || !strcmp(input, "clear")) {
            system("clear"); /* clear screen */
            TITLE
            continue;
        }
        if (!strcmp(input, "h") || !strcmp(input, "help")) {
            PRINT_HELP /* show help */
            continue;
        }

        base this_base = DEC; /* must set in case of one digit */
        length = clean_input(input, length, &this_base);
        if (!length) { /* either no input or invalid input given */
            PRINT_ERROR("Invalid input given.\n\n")
            continue;
        }
        ubyte this_base_numeric = base_numeric[this_base];
        /* <offset> needed to skip prefix ("0x", "0o", "0b") */
        ubyte offset = 0;
        long dec_number = 0;
        offset = (this_base != DEC) ? 2 : 0;
        if (!to_decimal(input + offset, length - offset, this_base_numeric, &(dec_number))) {
            PRINT_ERROR("Number exceeds minimum/maximum range.\n\n")
            continue;
        }
    
        /* convert to other bases */
        char converted[STRING_LENGTH]; /* maximum length of string */
        char dest[PRETTIFIED_MAX_LENGTH]; /* maximum length of string */
        for (ubyte i = 0; i < NUMBER_OF_BASES; i++) {
            ubyte base_value = base_numeric[i];
            to_base(dec_number, base_value, converted);
            prettify_string(converted, strlen(converted), i, dest);
            print_output(dest, i);
        }
        putchar('\n');
    }
    return 0;
}

int main(void) {
    return base_converter();
}