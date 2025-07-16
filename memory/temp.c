#include <stdio.h>
int main() {
char dna[] = "ATGCGATTACGATCAGCGATCG";
int gc = 0;
int at = 0;
int i;

for(i = 0; dna[i] != '\0'; i++) {
    if (dna[i] == 'G' || dna[i] == 'C') gc++;
    if (dna[i] == 'A' || dna[i] == 'T') at++;
}

double gc_percent = (double)gc / (gc + at) * 100.0;
printf("DNA sequence: %s\n", dna);
printf("GC-content: %.2f%%\n", gc_percent);

strcpy(dna, "GGCCATGATTTAGGGGCCC");
gc = 0;
at = 0;
for(i = 0; dna[i] != '\0'; i++) {
    if (dna[i] == 'G' || dna[i] == 'C') gc++;
    if (dna[i] == 'A' || dna[i] == 'T') at++;
}
gc_percent = (double)gc / (gc + at) * 100.0;
printf("New DNA: %s\nGC-content: %.2f%%\n", dna, gc_percent);

return 0; }
