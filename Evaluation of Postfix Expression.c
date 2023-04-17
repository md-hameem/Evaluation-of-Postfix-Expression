#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAX_STACK_SIZE 100

int stack[MAX_STACK_SIZE];
int top = -1;

// Function to push a value onto the stack
void push(int value);

// Function to pop a value from the stack
int pop();

// Function to evaluate a postfix expression and return the result
int evaluatePostfix(char *expr);

// Main function to run evaluation on hardcoded postfix expression
int main() {
    char expr[] = "77+44*/";
    int result = evaluatePostfix(expr);
    
    if(result != -1) {
        printf("For the value: (%s), the result for postfix is %d\n", expr, result);
    } else {
        fprintf(stderr, "Stack error, please try again.\n");
        return 1;
    }
    
    return 0;
}

void push(int value) {
    if (top >= MAX_STACK_SIZE - 1) {
        fprintf(stderr, "Stack overflow\n");
        exit(1);
    }
    stack[++top] = value;
}

int pop() {
    if (top < 0) {
        fprintf(stderr, "Stack underflow\n");
        exit(1);
    }
    return stack[top--];
}

int evaluatePostfix(char *expr) {
    int i, operand1, operand2, result;
    
    for (i = 0; expr[i] != '\0'; i++) {
        if (isdigit(expr[i])) {
            // If the character is a digit, convert it to an integer and push it onto the stack
            push(expr[i] - '0');
        } else {
            // If the character is an operator, pop two operands from the stack, perform the operation, and push the result onto the stack
            operand2 = pop();
            operand1 = pop();
            if(expr[i] == '+') {
                result = operand1 + operand2;
            } else if(expr[i] == '-') {
                result = operand1 - operand2;
            } else if(expr[i] == '*') {
                result = operand1 * operand2;
            } else if(expr[i] == '/') {
                result = operand1 / operand2;
            } else {
                fprintf(stderr, "Invalid operator: %c\n", expr[i]);
                exit(1);
            }
            push(result);
        }
    }
    
    // Pop the final result from the stack and return it
    return pop();
}
