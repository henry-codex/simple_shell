#include <stdio.h>
#include <stdbool.h>

/**
 * modusPonens - returns the result of modus ponens
 * @p: the value of p
 * @q: the value of q
 *
 * Return: true if the result is true, false otherwise
 */
bool modusPonens(int p, int q)
{
    return p && q;
}

/**
 * modusTollens - returns the result of modus tollens
 * @p: the value of p
 * @q: the value of q
 *
 * Return: true if the result is true, false otherwise
 */
bool modusTollens(int p, int q)
{
    return !q && !p;
}

/**
 * disjunctiveSyllogism - returns the result of disjunctive syllogism
 * @p: the value of p
 * @q: the value of q
 *
 * Return: true if the result is true, false otherwise
 */
bool disjunctiveSyllogism(int p, int q)
{
    return !p && q;
}

/**
 * addition - returns the result of addition
 * @p: the value of p
 *
 * Return: true if the result is true, false otherwise
 */
bool addition(int p)
{
    return p || !p;
}

/**
 * conditional - returns the result of a conditional
 * @p: the value of p
 * @q: the value of q
 *
 * Return: true if the result is true, false otherwise
 */
bool conditional(int p, int q)
{
    return !p || q;
}

/**
 * main - asks user for input and calls appropriate function
 *
 * Return: always 0
 */
int main(void)
{
    int p, q, choice;
    bool result;

    printf("Which rule do you want to use?\n");
    printf("1. Modus Ponens\n");
    printf("2. Modus Tollens\n");
    printf("3. Disjunctive Syllogism\n");
    printf("4. Addition\n");
    printf("5. Conditional\n");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            printf("Enter the values of p and q (separated by a space): ");
            scanf("%d %d", &p, &q);
            result = modusPonens(p, q);
            break;

        case 2:
            printf("Enter the values of p and q (separated by a space): ");
            scanf("%d %d", &p, &q);
            result = modusTollens(p, q);
            break;

        case 3:
            printf("Enter the values of p and q (separated by a space): ");
            scanf("%d %d", &p, &q);
            result = disjunctiveSyllogism(p, q);
            break;

        case 4:
            printf("Enter the value of p: ");
            scanf("%d", &p);
            result = addition(p);
            break;

        case 5:
            printf("Enter the values of p and q (separated by a space): ");
            scanf("%d %d", &p, &q);
            result = conditional(p, q);
            break;

        default:
            printf("Invalid choice. Please try again.\n");
            return 0;
    }

    printf("The result is %s.\n", result ? "true" : "false");
    return 0;
}

