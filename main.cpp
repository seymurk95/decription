#include "decrypt.hpp"



int main(void){

    setlocale(LC_ALL, "Russian"); 


    DECR_CLASS_ENG chiper_eng(_virtual_encryption_ENG(false));
    DECR_CLASS_RUS chiper_ru26_12_2024_22_08(_virtual_encryption_RUS(false));


    

    char lang = '0';

    cout << "Select language(press  0 - english, 1 - russian, 2 - azerbaijan): ";
    cin >> lang; cout<<"\n";


    

    switch(lang){
        case '0':   
            chiper_eng.get_encrypted_text(true);
            chiper_eng.decrypt();
            user_mod(&chiper_eng);

            /*
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
            
            */


            break;
        
        case '1':
            chiper_ru26_12_2024_22_08.get_encrypted_text(true);
            chiper_ru26_12_2024_22_08.decrypt();
            user_mod(&chiper_ru26_12_2024_22_08);
            
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
