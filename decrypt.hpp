
#ifndef DECRYPT_HPP
#define DECRYPT_HPP

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
using namespace std;

class DECR_CLASS_ENG{
    public:
        DECR_CLASS_ENG(const string& encrypted_text);

        void decrypt(); // -- Новое (это специально написал для фото(видео))

        void decrypt_byfreq();
        void user_insert(char old_letter, char new_letter);
        void decrypt_byusermod();


        string get_encrypted_text(bool enable_output = false) const;
        string get_decrypted_text_byfreq(bool enable_output = false) const;
        string get_decrypted_text_byusermod(bool enable_output = false) const;
        unordered_map<char, char> get_letter_mapping_byfreq(bool enable_output = false) const;
        unordered_map<char, char> get_letter_mapping_byusermod(bool enable_output = false) const;

    private:
        string encrypted_text;  // Зашифрованный текст
        string decrypted_text_byfreq; // Расшифрованный текст основанный на Частотном Методе (без изменений пользователя)
        string decrypted_text_byusermod; // Расшифрованный текст (с учётом изменений пользователя)
        unordered_map<char, char> letter_mapping_byfreq; // Мапа для сопоставления букв основаная на Частотном Методе
        unordered_map<char, char> letter_mapping_byusermod; // Мапа для сохранения изменений, сделанных пользователем
        static const unordered_map<char, double> EnglishLang_letter_freq; // Статическое константное поле для частот букв в английском языке

        // Структура для хранения данных о букве и её частоте
        struct LetterFreq {
            char letter;
            double freq;
        };


        unordered_map<char, double> calculate_freq(); // Вспомогательная функция для подсчёта частоты букв в тексте
        vector<LetterFreq> sort_by_freq(const unordered_map<char, double>& letter_freq); // Вспомогательная функция для сортировки частот
};


string _virtual_encryption_ENG(bool enable_output = false); //the most iconic encryption simulating function during the project development...

void user_mod(DECR_CLASS_ENG* pchiper);



class DECR_CLASS_RUS{
    public:
        DECR_CLASS_RUS(const wstring& encrypted_text);

        void decrypt();

        void decrypt_byfreq();
        void user_insert(wchar_t old_letter, wchar_t new_letter);
        void decrypt_byusermod();


        wstring get_encrypted_text(bool enable_output = false) const;
        wstring get_decrypted_text_byfreq(bool enable_output = false) const;
        wstring get_decrypted_text_byusermod(bool enable_output = false) const;
        unordered_map<wchar_t, wchar_t> get_letter_mapping_byfreq(bool enable_output = false) const;
        unordered_map<wchar_t, wchar_t> get_letter_mapping_byusermod(bool enable_output = false) const;


    private:
        wstring encrypted_text;  // Зашифрованный текст
        wstring decrypted_text_byfreq; // Расшифрованный текст основанный на Частотном Методе (без изменений пользователя)
        wstring decrypted_text_byusermod; // Расшифрованный текст (с учётом изменений пользователя)
        unordered_map<wchar_t, wchar_t> letter_mapping_byfreq; // Мапа для сопоставления букв основаная на Частотном Методе
        unordered_map<wchar_t, wchar_t> letter_mapping_byusermod; // Мапа для сохранения изменений, сделанных пользователем
        static const unordered_map<wchar_t, double> RussianLang_letter_freq; // Статическое константное поле для частот букв в русском языке

        // Структура для хранения данных о букве и её частоте
        struct LetterFreq {
            wchar_t letter;
            double freq;
        };


        unordered_map<wchar_t, double> calculate_freq(); // Вспомогательная функция для подсчёта частоты букв в тексте
        vector<LetterFreq> sort_by_freq(const unordered_map<wchar_t, double>& letter_freq); // Вспомогательная функция для сортировки частот
};

wstring _virtual_encryption_RUS(bool enable_output = false); // Trivia: the original text is just translated version of ENGLISH implementation

void user_mod(DECR_CLASS_RUS* pchiper);







#endif // DECRYPT_HPP




















































//string decrypt_ENG(const string encrypted_text, bool _enable__out_decrypted_text_1);





   // Метод для дорасшифровки с учётом изменений, сделанных пользователем
//    void decrypt_byusermod() {
        // Начинаем с расшифрованного текста, который уже был получен в decrypt_byfreq()
        //decrypted_text_byusermod = decrypted_text_byfreq;

        // Применяем изменения из мапы letter_mapping_byusermod
        // Если в Тексте расшифрованном по Частотному Анализу встречается буква которая была неудачно сопостовлена изначально шифрованному тексту, заменяем её на ту которую ввёл пользователь. И ЕЩЁ ОЧЕНЬ ВАЖНАЯ ОГОВОРКА!: Мы для поиска неучано сопостовленной буквы обязательно должны проходится по расшифрованному тексту основанному на Частотном Анализе!, а изменения(то есть замену) вводит в decrypted_text_byusemod. Если же мы пройдёмся по decrypted_text_byusermod всё будет хорошо если мы пользователь будет делать 1-ну единственную замену. Начиная со 2-ой и далее запросах на замену. Та первая замена на новую букву которую ввёл пользователь будет конфликтовать со старой буквой которая не нуждается в замене и стоит на своём месте и при дальнейших запросах на замену программа будет заменять и старые и новые что конечно неправильно по алгоритму!. Нам нужно что бы замена осуществлялась для [Неудачно сопоставленных букв при Частотном Анализе] --> [На те которые указал пользователь].
                /* - Это неправильная реализация тут старые и новые меняются

                for (const auto& entry : letter_mapping_byusermod) {
                   for (size_t i = 0; i < decrypted_text_byfreq.size(); ++i) {
                        // Если в расшифрованном тексте встречается буква, заменяем её
                        if (toupper(decrypted_text_byusermod[i]) == entry.first) {
                            decrypted_text_byusermod[i] = entry.second;
                        }
                    }
                }
                */

    /*
        for (const auto& entry : letter_mapping_byusermod) {
            for (size_t i = 0; i < decrypted_text_byfreq.size(); ++i) {
                // Если в расшифрованном тексте встречается буква, заменяем её
                if (toupper(decrypted_text_byfreq[i]) == entry.first) {
                    decrypted_text_byusermod[i] = entry.second;
                }
            }
        }
    */


//    }


/*
    void decrypt_byusermod() {
    // Начинаем с расшифрованного текста, полученного после частотного анализа
    decrypted_text_byusermod = decrypted_text_byfreq;

    // Мапа для отслеживания, были ли буквы уже заменены на правильные
    unordered_map<char, bool> is_replaced_correctly;

    // Применяем изменения из мапы letter_mapping_byusermod
    // Применяем только те замены, которые ещё не были сделаны
    for (const auto& entry : letter_mapping_byusermod) {
        for (size_t i = 0; i < decrypted_text_byusermod.size(); ++i) {
            // Проверяем, если буква в расшифрованном тексте совпадает с буквой, которую мы хотим заменить
            if (isalpha(decrypted_text_byusermod[i]) && toupper(decrypted_text_byusermod[i]) == entry.first) {
                // Если буква ещё не была заменена ранее, производим замену
                if (is_replaced_correctly.find(entry.first) == is_replaced_correctly.end()) {
                    decrypted_text_byusermod[i] = entry.second;
                    is_replaced_correctly[entry.first] = true;  // Помечаем, что эта буква была заменена
                }
            }
        }
    }
}
*/



/*
            chiper.decrypt_byfreq();
            chiper.get_decrypted_text_byfreq(true);

            chiper.user_insert('L', 'C');

            chiper.user_insert('C', 'D');
            chiper.user_insert('V', 'B');
            chiper.user_insert('W', 'U');
            chiper.user_insert('G', 'Y');
            chiper.user_insert('U', 'H');
            chiper.user_insert('D', 'M');

            chiper.decrypt_byusermod();
            chiper.get_decrypted_text_byusermod(true);


            chiper.user_insert('V', 'B');
            chiper.decrypt_byusermod();
            chiper.get_decrypted_text_byusermod(true);


            chiper.user_insert('C', 'D');
            chiper.decrypt_byusermod();
            chiper.get_decrypted_text_byusermod(true);

            chiper.user_insert('W', 'U');
            chiper.decrypt_byusermod();
            chiper.get_decrypted_text_byusermod(true);

            chiper.user_insert('G', 'Y');
            chiper.decrypt_byusermod();
            chiper.get_decrypted_text_byusermod(true);

            chiper.user_insert('U', 'H');
            chiper.decrypt_byusermod();
            chiper.get_decrypted_text_byusermod(true);


*/


/*
    #include "decrypt.hpp"


int main(void){

    char lang = '0';



    cout << "Select language: ";
    cin >> lang; cout<<endl;





    DECR_CLASS_ENG chiper(_virtual_encryption_ENG());



    switch(lang){
        case '0':

            chiper.decrypt_byfreq();
            chiper.get_decrypted_text_byfreq(true);

            chiper.user_insert('L', 'C');

            chiper.user_insert('C', 'D');
            chiper.user_insert('V', 'B');
            chiper.user_insert('W', 'U');
            chiper.user_insert('G', 'Y');
            chiper.user_insert('U', 'H');
            chiper.user_insert('D', 'M');

            chiper.decrypt_byusermod();
            chiper.get_decrypted_text_byusermod(true);


            chiper.user_insert('V', 'B');
            chiper.decrypt_byusermod();
            chiper.get_decrypted_text_byusermod(true);


            chiper.user_insert('C', 'D');
            chiper.decrypt_byusermod();
            chiper.get_decrypted_text_byusermod(true);

            chiper.user_insert('W', 'U');
            chiper.decrypt_byusermod();
            chiper.get_decrypted_text_byusermod(true);

            chiper.user_insert('G', 'Y');
            chiper.decrypt_byusermod();
            chiper.get_decrypted_text_byusermod(true);

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

*/
