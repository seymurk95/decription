
#include "decrypt.hpp"



int main(void){

    char lang;

    cout << "Enter language(0 - english, 1 - russian,  2 - azerbaijan): ";
    cin >> lang; cout << "\n";

    DECR_CLASS_ENG chiper_eng(_virtual_encryption_ENG(false));
    DECR_CLASS_RUS chiper_rus( _virtual_encryption_RUS(true));

    setlocale(LC_ALL, "Russian");

    switch(lang) {

        case '0':
            chiper_eng.decrypt();
        break;

        case '1':
            chiper_rus.decrypt();
        break;

        case '2':

            break;

        default:
            cerr << "error. language is not supported(available) or exist\n";
        break;
    }












}




