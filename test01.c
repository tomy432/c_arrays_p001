#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Description:
An array A contains n≥1 positive integers in the locations A[1], A[2],... A[n]. 
The following program fragment prints the length of a shortest sequence of consecutive elements of A, 
A[i], A[i+1],...A[j] such that the sum of their values is ≥ M, a given positive number. 
It prints 'n+1', if no such sequence exists. 

Write an efficient algorithm for the following assumptions:
n is an integer within the range [1 ... 1000]
M is an integer within the range [1 ... 1000]
*/

int Get_Length_of_Shothest_Sequence(int *arr, int n, int M)
{
    int i = 0, j = 0;
    int sum = 0;
    
    // calculate initial sum >= M or until the end of array
    for( ; j < n ; )
    {
        if(arr[j] >= M)
            return 1;

        sum += arr[j];
        ++j;

        if(sum >= M)
        {
            break;
        }
    }

    // no sequence exists
    if(sum < M)
        return (n+1);

    int min_length = j;
    int length = min_length;
    //--j;

    while(j < n)
    {
        if(arr[j] >= M)
            return 1;
        
        sum += arr[j];
        length++;

        while(i < j)
        {
            if(sum - arr[i] >= M)
            {
                sum -= arr[i];
                --length;

                ++i;
            }
            else
            {
                break;
            }
        }

        if(length < min_length)
            min_length = length;

        ++j;
    }

    return min_length;
}

int (*funptr)(int *, int, int) = &Get_Length_of_Shothest_Sequence;


// valid for numbers with space between them
// manually inserted on each line
void driver_small_length(int M)
{
    // I. read the results
    char *filename = "small_length_results.txt";
    
    FILE *fptr = fopen(filename, "r");

    if(fptr == NULL)
    {
        printf("fptr: %s is NULL\n", filename);
        return;
    }

    int results_size = 100;
    int results_length = 0;
    int outputs[results_size];
    int out;

    while(fscanf(fptr, "%d", &out) !=  EOF)
    {
        outputs[results_length++] = out;
        //printf("outputs[%d] = %d\n", results_length, out);
    }

    fclose(fptr);

    // II. calculate the cases
    filename = "small_length.txt";
    
    fptr = fopen(filename, "r");

    if(fptr == NULL)
    {
        printf("fptr: %s is NULL\n", filename);
        return;
    }

    int buffer_length = 1024;
    char buffer[buffer_length];
    int vals[buffer_length];    // values of array on a single line
    int vals_length;
    int calculated[results_length];
    int calculated_index = 0;
    int val;
    char *p;
    
    // read every line
    while(fscanf(fptr, "%1024[^\n]\n", buffer) !=  EOF)
    {
        p =  buffer;
        //printf("%p, %s\n", buffer, buffer);   // display the array on the line
        //printf("%p, %s\n", p, p);
        
        vals_length = 0;

        // read every element from a line
        while(p[0] != '\0')
        {
            sscanf(p, "%d", &val);
            //printf("val: %d\n", val);
            vals[vals_length++] = val;

            while(p[0] != ' ')
            {
                //printf("%c", p[0]);
                if(p[0] == '\0')
                    break;

                ++p;
            }

            if(p[0] == '\0')
                    break;

            ++p;
        }

        // the array in the line is provided
        calculated[calculated_index++] = funptr(vals, vals_length, M);
    }

    fclose(fptr);

    // III. compare calculated cases to output results
    printf("\nResults for small length:\n");

    for(int i = 0; i < results_length; ++i)
    {
        printf("case %d: %s\n", i+1, (calculated[i] == outputs[i]) ? "pass" : "fail!");
    }
}

void fill_in_file_with_numbers(char* filename, int left_limit, int right_limit, int length, int step, int mode, int append)
{
    // if append = 0 => don't append; append = 1 => yes
    FILE *fptr;
    
    if(append == 0)
        fptr = fopen(filename, "w");
    else
        fptr = fopen(filename, "a");

    if(fptr == NULL)
    {
        printf("fptr: %s is NULL\n", filename);
        return;
    }

    // ascending
    if(mode == 0)
    {
        for(int i = left_limit; i <= right_limit; i = i + step)
        {
            fprintf(fptr, "%d ", i);
        }
    }
    // descending
    else if(mode == 1)
    {
        for(int i = right_limit; i >= left_limit; i = i - step)
        {
            fprintf(fptr, "%d ", i);
        }
    }
    // descending
    else if(mode == 2)
    {
        for(int i = 0; i < length; i++)
        {
            fprintf(fptr, "%d ", left_limit);
        }
    }
    // random
    else if(mode == 3)
    {
        int value;

        for(int i = 0; i < length; i++)
        {
            // random numbers: [left_limit - right_limit]
            value = left_limit + (rand() % (right_limit-left_limit+1) );
            fprintf(fptr, "%d ", value);
        }
    }

    fclose(fptr);
}

void generate_file_input_for_driver_medium_length()
{
    char *filename = "medium_length_01.txt";
    int left_limit = 0;
    int right_limit = 50;
    int length = 40;
    int step = 1;
    int mode = 0;
    int append = 0;

    // [0 - 50]
    fill_in_file_with_numbers(filename, left_limit, right_limit, length, step, mode, append);

    filename = "medium_length_02.txt";
    mode = 1;
    // [50 - 0]
    fill_in_file_with_numbers(filename, left_limit, right_limit, length, step, mode, append);

    filename = "medium_length_03.txt";
    mode = 2;
    left_limit = 3;

    // [left_limit * length]
    fill_in_file_with_numbers(filename, left_limit, right_limit, length, step, mode, append);

    filename = "medium_length_04.txt";
    mode = 3;
    left_limit = 0;
    right_limit = 20;
    // [random 0-20 * 40]
    fill_in_file_with_numbers(filename, left_limit, right_limit, length, step, mode, append);

    filename = "medium_length_05.txt";
    mode = 3;
    left_limit = 0;
    right_limit = 3;
    // [random 0-3 * 40]
    fill_in_file_with_numbers(filename, left_limit, right_limit, length, step, mode, append);

    filename = "medium_length_06.txt";
    mode = 2;
    left_limit = 1;
    length = 8;
    // [1 * 8]
    fill_in_file_with_numbers(filename, left_limit, right_limit, length, step, mode, append);

    filename = "medium_length_07.txt";
    mode = 2;
    left_limit = 1;
    length = 7;
    // [1 * 7]
    fill_in_file_with_numbers(filename, left_limit, right_limit, length, step, mode, append);
}

int calculate_funptr(char * filename, int M)
{
    int result;

    FILE *fptr = fopen(filename, "r");

    if(fptr == NULL)
    {
        printf("fptr: %s is NULL\n", filename);
        return 0;
    }

    int results_size = 100;
    int results_length = 0;
    int outputs[results_size];
    int out;

    while(fscanf(fptr, "%d", &out) !=  EOF)
    {
        outputs[results_length++] = out;
        //printf("outputs[%d] = %d\n", results_length, out);
    }

    fclose(fptr);

    result = funptr(outputs, results_length, M);

    return result;
}

void driver_medium_length(int M)
{
    char* filename0 = "medium_length_results.txt";

    FILE *fptr = fopen(filename0, "r");

    if(fptr == NULL)
    {
        printf("fptr: %s is NULL\n", filename0);
        return;
    }

    int results_size = 100;
    int results_length = 0;
    int outputs[results_size];
    int out;

    while(fscanf(fptr, "%d", &out) !=  EOF)
    {
        outputs[results_length++] = out;
    }

    fclose(fptr);

    // find "medium_length_xx.txt" files and calculate the funptr(vals, vals_length, M);
    char filename[21] = "medium_length_00.txt";

    printf("\nResults for medium length:\n");

    for(int i = 1; i <= 7; ++i)
    {
        filename[15] = (char)('0' + i);
        //printf("%d = %s\n", i, filename);

        // compare 
        if(calculate_funptr(filename, M) == outputs[i-1])
        {
            printf("case %d: %s\n", i, "pass");
        }
        else
        {
            printf("case %d: %s\n", i, "fail!");
        }
    }
}

void driver(int M)
{
    //printf("\ndriver()\n");

    // Tests
    // Small length: one file, multiple lines, one array per line
    driver_small_length(M);

    // Medium length: one array per file
    driver_medium_length(M);

    // Big length: one array per file
}


int main()
{   
    int generate_files = 0;
    
    if(generate_files)
    {
        generate_file_input_for_driver_medium_length();
    }

    int M = 8;
    driver(M);

    return 0;
}
