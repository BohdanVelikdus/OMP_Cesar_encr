
#include<iostream>
#include <omp.h>
#include <chrono>

int main(){
    std::string ToCode;
    char ch;
    try{
        std::cout << "Enter word to change: ";

        std::cin >> ToCode;
        std::cout <<"Enter char to crypt: ";

        std::cin >> ch;
    }catch(...){
        std::cout << "Unexpected input";
        return -1;
    }
    int count = ToCode.length() / 4;
    int rem = ToCode.length() % 4; 
    auto currentTime = std::chrono::system_clock::now();

    #pragma omp parallel num_threads(4)
    {
        int thread_id = omp_get_thread_num();
        int firstInd = thread_id * count;  
        int lastInd  = firstInd + count;
        if(thread_id == 3){
            lastInd += rem;
        }

        for(auto i = firstInd; i < lastInd; i++){
            if(std::islower(ToCode[i])){
                if(static_cast<int>(ToCode[i]) + (static_cast<int>(ch) - 96) > 122){
                    ToCode[i] = static_cast<char>(static_cast<int>(ToCode[i]) + (static_cast<int>(ch) - 96) - 27);
                }else{
                    ToCode[i] = static_cast<char>(static_cast<int>(ToCode[i]) + (static_cast<int>(ch) - 96));
                }           
            }else{
                if(static_cast<int>(ToCode[i]) + (static_cast<int>((ch)) - 64) > 90){
                    ToCode[i] = static_cast<char>(static_cast<int>(ToCode[i]) + (static_cast<int>(ch) - 64) - 26);
                }else{
                    ToCode[i] = static_cast<char>(static_cast<int>(ToCode[i]) + (static_cast<int>(ch) - 64));
                }
            }
        }
        #pragma omp barier
    }   
    auto endTime = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(endTime - currentTime);
    std::cout << "time elapsed microseconds: " << elapsed << "\nString: " << ToCode << std::endl;
    return 0;
}
