#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// States for email
typedef enum {
    email_start,
    email_local,
    email_dom,
    email_dot,
    email_valid
} EmailState;

// States for web
typedef enum {
    web_start,
    web_www,
    web_dom,
    web_valid
} WebState;

// Function to validate email
bool isEmail(const char *str) {
    EmailState state = email_start;
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        switch (state) {
            case email_start:
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
                    || (c >= '0' && c <= '9')) {
                    state = email_local; // Local part starts here
                } else {
                    return false;
                }
                break;

            case email_local:
                if (c == '@') {
                    state = email_dom; // Transition to domain after '@'
                } else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
                           || (c >= '0' && c <= '9') || c == '.' || c == '_') {
                    // Stay in local part
                } else {
                    return false;
                }
                break;

            case email_dom:
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                    // Stay in domain part
                } else if (c == '.') {
                    state = email_dot; // Expecting a top-level domain next
                } else {
                    return false;
                }
                break;

            case email_dot:
                if ((c >= 'a' && c <= 'z')) {
                    state = email_valid; // Final valid state
                } else {
                    return false;
                }
                break;

            case email_valid:
                if ((c >= 'a' && c <= 'z') || c == '.') {
                    // Stay in valid state
                } else {
                    return false;
                }
                break;
        }
    }
    return state == email_valid;
}


// Function to validate web address
bool isWeb(const char *str) {
    WebState state = web_start;
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        switch (state) {
            case web_start:
                if (strncmp(str, "www.", 4) == 0) {
                    state = web_www;
                    i += 3;
                } else {
                    return false;
                }
                break;

            case web_www:
                if ((c >= 'a' && c <= 'z')) {
                    state = web_dom;
                } else {
                    return false;
                }
                break;

            case web_dom:
                if ((c >= 'a' && c <= 'z')) {
                    // Stay in domain
                } else if (c == '.') {
                    state = web_valid;
                } else {
                    return false;
                }
                break;

            case web_valid:
                if ((c >= 'a' && c <= 'z')) {
                    // Stay in valid
                } else {
                    return false;
                }
                break;
        }
    }
    return state == web_valid;
}
int main() {
    int n;
    printf("Enter the number of inputs: ");
    scanf("%d", &n);

    char inputs[n][100];
    getchar(); // Consume newline character after scanf
    // Collect all inputs
    for (int i = 0; i < n; i++) {
        fgets(inputs[i], sizeof(inputs[i]), stdin);
        inputs[i][strcspn(inputs[i], "\n")] = '\0';
    }
    // Process and display results
    for (int i = 0; i < n; i++) {
            printf("\n");
        if (isEmail(inputs[i])) {
            printf("Email, %d\n", i + 1);
        } else if (isWeb(inputs[i])) {
            printf("Web, %d\n", i + 1);
        }
    }
    return 0;
}
