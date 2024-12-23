#include "decrypt.cpp"
#include "decrypt.hpp"
#include <iostream>
int main(){

    char lang = '0';

    cout << "Select language: ";
    cin >> lang; cout<<endl;


    DECR_CLASS_ENG chiper(_virtual_encryption_ENG());

    switch(lang){
        case '0':

            chiper.decrypt_byfreq();
        chiper.get_decrypted_text_byfreq(true);

        chiper.user_insert('L', 'C');
        /*
        chiper.user_insert('C', 'D');
        chiper.user_insert('V', 'B');
        chiper.user_insert('W', 'U');
        chiper.user_insert('G', 'Y');
        chiper.user_insert('U', 'H');
        chiper.user_insert('D', 'M');
        */
        chiper.decrypt_byusermod();
        chiper.get_decrypted_text_byusermod(false);


        chiper.user_insert('V', 'B');
        chiper.decrypt_byusermod();
        chiper.get_decrypted_text_byusermod(false);


        chiper.user_insert('C', 'D');
        chiper.decrypt_byusermod();
        chiper.get_decrypted_text_byusermod(false);

        chiper.user_insert('W', 'U');
        chiper.decrypt_byusermod();
        chiper.get_decrypted_text_byusermod(false);

        chiper.user_insert('G', 'Y');
        chiper.decrypt_byusermod();
        chiper.get_decrypted_text_byusermod(false);

        chiper.user_insert('U', 'H');
        chiper.decrypt_byusermod();
        chiper.get_decrypted_text_byusermod(true);

        break;

        case '1':
            // encrypted_text = _virtual_encryption_RUS(true);
                // decrpyted_text_1 = decrypt_RUS(encrypted_text, true);
                    break;

        case '2':
            // encrypted_text = _virtual_encryption_AZE(true);
                // decrypted_text_1 = decrypt_AZE(encrypted_text, true);
                    break;

        default:
            cerr << "error. language isn't supported (available) or exist";
        return -1;
    }

}