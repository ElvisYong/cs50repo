#include <stdio.h>
#include <cs50.h>

// spaces n-1
int main(void)
{
    int height_input;

    do
    {
        height_input = get_int("Height: ");
    }
    while(height_input < 1 || height_input > 8);

    // Loop rows
    for(int row = 1; row <= height_input; row++)
    {
        // Loop column spaces
        // First row needs 7 spaces thus height_input - row
        for(int spaces = height_input - row; spaces > 0; spaces--)
        {
            printf(" ");
        }

        // Column loop for left side hashes according to row
        for(int hashes = 1; hashes <= row; hashes++)
        {
            printf("#");
        }

         // Spaces between hashes
        printf("  ");

        // Column loop for right side hashes according to row
        for(int hashes = 1; hashes <= row; hashes++)
        {
            printf("#");
        }

        printf("\n");
    }
}