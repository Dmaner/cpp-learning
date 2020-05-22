#include<iostream>
#include "fact.h"

int fact(int val){
    if (val < 2){
        return 1;
    }
    else{
        return val * fact(val-1);
    }
}