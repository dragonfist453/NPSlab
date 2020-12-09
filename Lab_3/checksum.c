#include<stdio.h>
unsigned int fields[10];

unsigned short checksum() {
    int i,sum = 0;
    printf("Enter IP header information in 16 bit words with space separation\n");
    for(i=0;i<9;i++) {
        scanf("%x", &fields[i]);
        sum = sum + (unsigned short)fields[i];
        while(sum>>16)
            sum = (sum & 0xFFFF) + (sum >> 16);
    }
    sum = ~sum;
    return (unsigned short)sum;
}

int main() {
    unsigned short result1, result2;

    //Sender's checksum
    result1 = checksum();
    printf("\nComputed checksum at sender is %x\n", result1);

    //Receiver's checksum
    result2 = checksum();
    printf("\nComputed checksum at receiver is %x\n", result2);

    if(result1 == result2)
        printf("All is good\n");
    else
        printf("Checksum failed\n");
    
    return 0;
}