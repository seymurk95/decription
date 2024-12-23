#ifndef DECRYPT_CPP
#define DECRYPT_CPP

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include "decrypt.hpp"

using namespace std;

// Реализация методов класса DECR_CLASS_ENG

// Конструктор
DECR_CLASS_ENG::DECR_CLASS_ENG(const string& encrypted_text) : encrypted_text(encrypted_text) {}

// Основная функция для расшифровки текста по частотному методу
void DECR_CLASS_ENG::decrypt_byfreq() {
    auto letter_freq_EncrText = calculate_freq();

    // Сортируем частоты для английского языка и зашифрованного текста
    auto sorted_ENG = sort_by_freq(EnglishLang_letter_freq);
    auto sorted_Encrypted = sort_by_freq(letter_freq_EncrText);

    // Создаём мапу для сопоставления букв
    letter_mapping_byfreq.clear();
    for (size_t i = 0; i < sorted_Encrypted.size(); ++i) {
        letter_mapping_byfreq[sorted_Encrypted[i].letter] = sorted_ENG[i].letter;
    }

    // Расшифровка текста
    decrypted_text_byfreq.clear();
    for (char c : encrypted_text) {
        if (isalpha(c)) {
            char upper_char = toupper(c);
            decrypted_text_byfreq += letter_mapping_byfreq[upper_char];
        } else {
            decrypted_text_byfreq += c;
        }
    }

    decrypted_text_byusermod = decrypted_text_byfreq;
}

// Метод для пользовательского сопоставления букв
void DECR_CLASS_ENG::user_insert(char old_letter, char new_letter) {
    old_letter = toupper(old_letter);
    new_letter = toupper(new_letter);
    letter_mapping_byusermod[old_letter] = new_letter;
}

// Метод для расшифровки текста с учётом изменений пользователя
void DECR_CLASS_ENG::decrypt_byusermod() {
    decrypted_text_byusermod = decrypted_text_byfreq;

    for (const auto& entry : letter_mapping_byusermod) {
        for (char& c : decrypted_text_byusermod) {
            if (isalpha(c) && toupper(c) == entry.first) {
                c = entry.second;
            }
        }
    }
}

// Получение расшифрованного текста по частотному методу
string DECR_CLASS_ENG::get_decrypted_text_byfreq(bool enable_output) const {
    if (enable_output) {
        cout << "\n\n[Decrypted Text by Frequency Method]:\n" << decrypted_text_byfreq << "\n\n";
    }
    return decrypted_text_byfreq;
}

// Получение расшифрованного текста с учётом изменений пользователя
string DECR_CLASS_ENG::get_decrypted_text_byusermod(bool enable_output) const {
    if (enable_output) {
        cout << "\n\n[Decrypted Text by User Modifications]:\n" << decrypted_text_byusermod << "\n\n";
    }
    return decrypted_text_byusermod;
}

// Получение мапы соответствий для частотного метода
unordered_map<char, char> DECR_CLASS_ENG::get_letter_mapping_byfreq(bool enable_output) const {
    if (enable_output) {
        cout << "\n[Frequency Mapping]:\n";
        for (const auto& entry : letter_mapping_byfreq) {
            cout << "Original: " << entry.first << " -> Mapped: " << entry.second << endl;
        }
    }
    return letter_mapping_byfreq;
}

// Получение мапы соответствий с учётом изменений пользователя
unordered_map<char, char> DECR_CLASS_ENG::get_letter_mapping_byusermod(bool enable_output) const {
    if (enable_output) {
        cout << "\n[User Mapping Modifications]:\n";
        for (const auto& entry : letter_mapping_byusermod) {
            cout << "Original: " << entry.first << " -> Mapped: " << entry.second << endl;
        }
    }
    return letter_mapping_byusermod;
}

// Вспомогательная функция для подсчёта частоты букв в тексте
unordered_map<char, double> DECR_CLASS_ENG::calculate_freq() {
    unordered_map<char, unsigned int> letter_count;
    unsigned int total_letters = 0;

    for (char c : encrypted_text) {
        if (isalpha(c)) {
            char upper_char = toupper(c);
            letter_count[upper_char]++;
            total_letters++;
        }
    }

    unordered_map<char, double> letter_freq;
    for (const auto& entry : letter_count) {
        letter_freq[entry.first] = (static_cast<double>(entry.second) / total_letters) * 100;
    }

    return letter_freq;
}

// Вспомогательная функция для сортировки частот
vector<LetterFreq> DECR_CLASS_ENG::sort_by_freq(const unordered_map<char, double>& letter_freq) {
    vector<LetterFreq> sorted_freq;
    for (const auto& entry : letter_freq) {
        sorted_freq.push_back({entry.first, entry.second});
    }

    sort(sorted_freq.begin(), sorted_freq.end(), [](const LetterFreq& a, const LetterFreq& b) {
        return a.freq > b.freq;
    });

    return sorted_freq;
}

// Инициализация статического поля для частот букв в английском языке
const unordered_map<char, double> DECR_CLASS_ENG::EnglishLang_letter_freq = {
    {'E', 12.70}, {'T', 9.06}, {'A', 8.17}, {'O', 7.51}, {'I', 6.97},
    {'N', 6.75}, {'S', 6.33}, {'R', 6.03}, {'H', 5.92}, {'D', 4.25},
    {'L', 4.03}, {'U', 3.64}, {'C', 3.33}, {'M', 3.01}, {'F', 2.23},
    {'P', 2.02}, {'G', 1.93}, {'Y', 1.77}, {'B', 1.49}, {'V', 0.98},
    {'K', 0.77}, {'X', 0.15}, {'J', 0.15}, {'Q', 0.10}, {'Z', 0.07},
    {'W', 2.36}
};

// Виртуальное шифрование текста на английском языке
string _virtual_encryption_ENG(bool enable_output) {
    string text_to_encrypt = "This is an example of encrypted text for testing purposes.";
    if (enable_output) {
        cout << "[Virtual Encrypted Text]:\n" << text_to_encrypt << "\n";
    }
    return text_to_encrypt;
}

#endif // DECRYPT_CPP
