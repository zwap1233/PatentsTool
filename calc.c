#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <wchar.h>

#define SIZE_ROW 2000

int parseRow(FILE *in, FILE *out);
int count(wchar_t *str);\

int main(int argc, char *argv[]){
    
    FILE* in;
    FILE* out;
    
    in = fopen("savedrecs.txt", "r,ccs=UTF16LE");
    out = fopen("out.txt", "w,ccs=UTF16LE");
    
    while(parseRow(in, out)){}
    
    fflush(in);
    fclose(in);
    fflush(out);
    fclose(out);
    
    return 0;
}

int parseRow(FILE *in, FILE *out){
    wchar_t  *rows[25];
    
    int i = 0;
    for(i = 0; i < 25; i++){
        rows[i] = malloc(SIZE_ROW*sizeof(wchar_t));
        memset(rows[i], 0, SIZE_ROW*sizeof(wchar_t));
    }
    
    int st = 0;
    int br = 0;
    int j,k;
    for(j = 0; j < 24; j++){
        for(k = 0; k < SIZE_ROW; k++){
            wchar_t c = fgetwc(in);
            if(feof(in)){
                //wprintf(L"End of line: %d, %lc\n", j, c);
                //rows[j][k] = L'\t';
                br = 1;
                st = 1;
                break;
            } else if(c == L'\n' || c == L'\r' || c == L'\0'){
                //wprintf(L"End of line: %d, %lc\n", j, c);
                //rows[j][k] = L'\t';
                br = 1;
                break;
            } else if(c == L'\t') {
                //wprintf(L"End of collomn: %d, %lc\n", j, c);
                //rows[j][k] = L'\t';
                break;
            } else {
                //wprintf(L"letter: %d, %d, %lc\n", j, k, c);
                rows[j][k] = c;
            }
        }
        
        //wprintf(L"Line:%ls\n", rows[j]);
        
        if(br){
            while(1){
                wchar_t c = fgetwc(in);
                if(c == L'\n' || c == L'\r' || c == L'\t' || c == L'\0'){
                } else {
                    ungetwc(c, in);
                    break;
                }
            }
            
            break;
        }
    }
    
    if(rows[0][0] == L'\n' || rows[0][0] == L'\r' || rows[0][0] == L'\0' || rows[0][0] == L'\t'){
        int l = 1;
        for(l = 1; l < 25; l++){
            free(rows[l]);
        }
        
        if(st){
            return 0;
        } else {
            return 1;
        }
    }
    
    int result = count(rows[17])*count(rows[0]);
    swprintf(rows[24], SIZE_ROW, L"%d", result);
    
    //wprintf(L"%ls", rows[0]);
    fwprintf(out, L"%ls", rows[0]);
    
    int l = 1;
    for(l = 1; l < 25; l++){
        //wprintf(L"\t%ls", rows[l]);
        fwprintf(out, L"\t%ls", rows[l]);
        free(rows[l]);
    }
    
    //wprintf(L"\n");
    fwprintf(out, L"\n");
    
    if(st){
        return 0;
    } else {
        return 1;
    }
}

int count(wchar_t *str){
    int res = 0;
    
    int i = 0;
    for(i = 0; i < SIZE_ROW; i++){
        if(str[i] == L'\0'){
            res++;
            break;
        } else if(str[i] == L';'){
            res++;
        }
    }
    
    return res;
}