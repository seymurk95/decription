#ifndef DECRYPT_HPP
#define DECRYPT_HPP

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>

// Структура для хранения данных о букве и её частоте
struct LetterFreq {
    char letter;
    double freq;
};

// Класс для расшифровки текста на основе частот букв
class DECR_CLASS_ENG {
public:
    // Конструктор, принимающий зашифрованный текст
    DECR_CLASS_ENG(const std::string& encrypted_text);

    // Основная функция для расшифровки текста
    void decrypt_byfreq();

    // Метод для пользовательского сопоставления букв
    void user_insert(char old_letter, char new_letter);

    // Метод для расшифровки текста с учетом изменений пользователя
    void decrypt_byusermod();

    // Получение расшифрованного текста по Частотному Методу
    std::string get_decrypted_text_byfreq(bool enable_output = false) const;

    // Получение расшифрованного текста с учетом изменений пользователя
    std::string get_decrypted_text_byusermod(bool enable_output = false) const;

    // Получение мапы соответствий для Частотного Метода
    std::unordered_map<char, char> get_letter_mapping_byfreq(bool enable_output = false) const;

    // Получение мапы соответствий с учетом изменений пользователя
    std::unordered_map<char, char> get_letter_mapping_byusermod(bool enable_output = false) const;

private:
    std::string encrypted_text;  // Зашифрованный текст

    std::string decrypted_text_byfreq;  // Расшифрованный текст по Частотному Методу

    std::string decrypted_text_byusermod;  // Расшифрованный текст с учетом изменений пользователя

    std::unordered_map<char, char> letter_mapping_byfreq;  // Мапа для Частотного Метода

    std::unordered_map<char, char> letter_mapping_byusermod;  // Мапа для изменений пользователя

    static const std::unordered_map<char, double> EnglishLang_letter_freq;  // Частоты букв для английского языка

    // Вспомогательная функция для подсчёта частоты букв в тексте
    std::unordered_map<char, double> calculate_freq();

    // Вспомогательная функция для сортировки частот
    std::vector<LetterFreq> sort_by_freq(const std::unordered_map<char, double>& letter_freq);
};

// Функция для создания виртуального зашифрованного текста на английском языке
std::string _virtual_encryption_ENG(bool enable_output = false);

#endif // DECRYPT_HPP
