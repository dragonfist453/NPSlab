#include <math.h> 
#include <stdio.h> 

int code[32]; 

int ham_calc(int position, int c_l) 
{ 
    int count = 0, i, j; 
    i = position - 1; 

    while (i < c_l) { 
        for (j = i; j < i + position; j++) { 
            if (code[j] == 1) 
                count++; 
        } 
        i = i + 2 * position; 
    } 
  
    if (count % 2 == 0) 
        return 0; 
    else
        return 1; 
} 
  
void solve(int input[], int n) 
{ 
    int i, p_n = 0, c_l, j, k; 
    i = 0; 
  
    while (n > (int)pow(2, i) - (i + 1)) { 
        p_n++; 
        i++; 
    } 
  
    c_l = p_n + n; 
    j = k = 0; 
  
    for (i = 0; i < c_l; i++) { 
        if (i == ((int)pow(2, k) - 1)) { 
            code[i] = 0; 
            k++; 
        } 
        else { 
            code[i] = input[j]; 
            j++; 
        } 
    } 
  
    for (i = 0; i < p_n; i++) { 
        int position = (int)pow(2, i); 
        int value = ham_calc(position, c_l); 
        code[position - 1] = value; 
    } 

    printf("\nThe generated Code Word is: "); 
    for (i = 0; i < c_l; i++) { 
        printf("%d", code[i]); 
    } 
    printf("\n");
} 
  
int main() 
{ 
    int input[32], N, i; 
    printf("Input length of the input: ");
    scanf("%d", &N);

    printf("Enter input with each bit separated by a space\n");
    for(i=0;i<N;i++) {
        scanf("%d", &input[i]);
    }

    solve(input, N); 
    return 0;
} 