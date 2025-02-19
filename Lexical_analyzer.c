#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX_TOKEN_LEN 100
#define MAX_TOKENS    500

char keywordsTable[MAX_TOKENS][MAX_TOKEN_LEN];
int keywordsCount = 0;
char identifiersTable[MAX_TOKENS][MAX_TOKEN_LEN];
int identifiersCount = 0;
char mathOpsTable[MAX_TOKENS][MAX_TOKEN_LEN];
int mathOpsCount = 0;
char logicalOpsTable[MAX_TOKENS][MAX_TOKEN_LEN];
int logicalOpsCount = 0;
char numericalTable[MAX_TOKENS][MAX_TOKEN_LEN];
int numericalCount = 0;
char othersTable[MAX_TOKENS][MAX_TOKEN_LEN];
int othersCount = 0;

int tokenExists(char table[][MAX_TOKEN_LEN], int count, const char *token) {
    for (int i = 0; i < count; i++) {
        if (strcmp(table[i], token) == 0)
            return 1;
    }
    return 0;
}
void addToken(char table[][MAX_TOKEN_LEN], int *count, const char *token) {
    if (!tokenExists(table, *count, token)) {
        strcpy(table[*count], token);
        (*count)++;
    }
}
int isKeyword(const char *token) {
    return (strcmp(token, "int") == 0 || strcmp(token, "float") == 0 ||
            strcmp(token, "if") == 0 || strcmp(token, "else") == 0);
}
int isValidIdentifier(const char *token) {
    if (!isalpha(token[0]) && token[0] != '_')
        return 0;
    for (int i = 1; token[i] != '\0'; i++) {
        if (!isalnum(token[i]) && token[i] != '_')
            return 0;
    }
    return 1;
}
int isNumber(const char *token) {
    if (token[0] == '\0')
        return 0;
    int dotCount = 0, digitCount = 0;
    for (int i = 0; token[i] != '\0'; i++) {
        if (token[i] == '.') {
            if (dotCount == 1)
                return 0;
            dotCount++;
        } else if (isdigit(token[i])) {
            digitCount++;
        } else {
            return 0;
        }
    }
    return (digitCount > 0);
}
int isMathOperatorChar(char ch) {
    return (ch == '=' || ch == '-' || ch == '+');
}
int isLogicalOperatorChar(char ch) {
    return (ch == '<' || ch == '>');
}
int isOtherChar(char ch) {
    return (ch == ';' || ch == '(' || ch == ')' ||
            ch == '{' || ch == '}' || ch == ',');
}
void processTokenBuffer(char *buffer) {
    if (buffer[0] == '\0')
        return;
    if (isKeyword(buffer)) {
        addToken(keywordsTable, &keywordsCount, buffer);
    } else if (isNumber(buffer)) {
        addToken(numericalTable, &numericalCount, buffer);
    } else if (isValidIdentifier(buffer)) {
        addToken(identifiersTable, &identifiersCount, buffer);
    }
}
int main(void) {
    FILE *fp = fopen("input.txt", "r");
    if (!fp) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    char ch, tokenBuffer[MAX_TOKEN_LEN];
    int bufIndex = 0;
    while ((ch = fgetc(fp)) != EOF) {
        if (isspace(ch)) {
            tokenBuffer[bufIndex] = '\0';
            processTokenBuffer(tokenBuffer);
            bufIndex = 0;
            continue;
        }
        if (ch == '.') {
            if (bufIndex > 0 && isNumber(tokenBuffer)) {
                int nextChar = fgetc(fp);
                if (nextChar != EOF && isdigit((char)nextChar)) {
                    tokenBuffer[bufIndex++] = '.';
                    tokenBuffer[bufIndex++] = (char)nextChar;
                    continue;
                } else {
                    if (nextChar != EOF)
                        ungetc(nextChar, fp);
                    tokenBuffer[bufIndex] = '\0';
                    processTokenBuffer(tokenBuffer);
                    bufIndex = 0;
                    char op[2] = { '.', '\0' };
                    addToken(mathOpsTable, &mathOpsCount, op);
                    continue;
                }
            } else {
                tokenBuffer[bufIndex] = '\0';
                processTokenBuffer(tokenBuffer);
                bufIndex = 0;
                char op[2] = { '.', '\0' };
                addToken(mathOpsTable, &mathOpsCount, op);
                continue;
            }
        }
        if (isMathOperatorChar(ch) || isLogicalOperatorChar(ch) || isOtherChar(ch)) {
            tokenBuffer[bufIndex] = '\0';
            processTokenBuffer(tokenBuffer);
            bufIndex = 0;
            char op[2] = { ch, '\0' };
            if (isMathOperatorChar(ch))
                addToken(mathOpsTable, &mathOpsCount, op);
            else if (isLogicalOperatorChar(ch))
                addToken(logicalOpsTable, &logicalOpsCount, op);
            else if (isOtherChar(ch))
                addToken(othersTable, &othersCount, op);
            continue;
        }
        if (bufIndex < MAX_TOKEN_LEN - 1) {
            tokenBuffer[bufIndex++] = ch;
        }
    }
    tokenBuffer[bufIndex] = '\0';
    processTokenBuffer(tokenBuffer);
    fclose(fp);

    printf("Keywords: ");
    for (int i = 0; i < keywordsCount; i++) {
        printf("%s", keywordsTable[i]);
        if (i < keywordsCount - 1)
            printf(", ");
    }
    printf("\n");
    printf("Identifiers: ");
    for (int i = 0; i < identifiersCount; i++) {
        printf("%s", identifiersTable[i]);
        if (i < identifiersCount - 1)
            printf(", ");
    }
    printf("\n");
    printf("Math Operators: ");
    for (int i = 0; i < mathOpsCount; i++) {
        printf("%s", mathOpsTable[i]);
        if (i < mathOpsCount - 1)
            printf(", ");
    }
    printf("\n");
    printf("Logical Operators: ");
    for (int i = 0; i < logicalOpsCount; i++) {
        printf("%s", logicalOpsTable[i]);
        if (i < logicalOpsCount - 1)
            printf(", ");
    }
    printf("\n");
    printf("Numerical Values: ");
    for (int i = 0; i < numericalCount; i++) {
        printf("%s", numericalTable[i]);
        if (i < numericalCount - 1)
            printf(", ");
    }
    printf("\n");
    printf("Others: ");
    for (int i = 0; i < othersCount; i++) {
        printf("%s", othersTable[i]);
    }
    printf("\n");
    return 0;
}
