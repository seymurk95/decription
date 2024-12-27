#ifndef DECRYPT_CPP
#define DECRYPT_CPP


#include "decrypt.hpp"


DECR_CLASS_ENG::DECR_CLASS_ENG(const string& encrypted_text) : encrypted_text(encrypted_text) {}

void DECR_CLASS_ENG::decrypt(){

    this->decrypt_byfreq();
    this->get_decrypted_text_byfreq(true);

    user_mod(this);

}

void DECR_CLASS_ENG::decrypt_byfreq() {
        // Подсчёт частоты символов в зашифрованном тексте
        unordered_map<char, double> letter_freq_EncrText = calculate_freq();

        // Сортируем частоты для английского языка и зашифрованного текста
        vector<LetterFreq> sorted_ENG = sort_by_freq(EnglishLang_letter_freq);
        vector<LetterFreq> sorted_Encrypted = sort_by_freq(letter_freq_EncrText);

        // Создаём мапу для сопоставления букв
        letter_mapping_byfreq.clear();  // Очищаем старое значение
        for (size_t i = 0; i < sorted_Encrypted.size(); ++i) {
            letter_mapping_byfreq[sorted_Encrypted[i].letter] = sorted_ENG[i].letter;
        }

        // Расшифровка текста без изменений пользователя
        decrypted_text_byfreq = "";  // Очищаем старое значение
        for (char c : encrypted_text) {
            if (isalpha(c)) {
                char upper_char = toupper(c);
                decrypted_text_byfreq += letter_mapping_byfreq[upper_char];  // Заменяем на соответствующую букву
            } else {
                decrypted_text_byfreq += c;  // Если не буква (например, пробел), оставляем как есть
            }
        }


        decrypted_text_byusermod = decrypted_text_byfreq;
}

void DECR_CLASS_ENG::user_insert(char old_letter, char new_letter){

            // old_letter - Это буква полученная по Частотному Методу, но оказалась неправильно(неудачно) сопоставлена шифрованному тексту(то есть encrypted_text). Она не подошла по смыслу слов(а), и в какой-то степени счиатается полушифрованной xD

            old_letter = toupper(old_letter);
            new_letter = toupper(new_letter);


            letter_mapping_byusermod[old_letter] = new_letter;
}

void DECR_CLASS_ENG::decrypt_byusermod() {
        decrypted_text_byusermod = decrypted_text_byfreq;

        for (const auto& entry : letter_mapping_byusermod) {
            for (size_t i = 0; i < decrypted_text_byusermod.size(); ++i) {
                if (isalpha(decrypted_text_byusermod[i]) && toupper(decrypted_text_byusermod[i]) == entry.first) {
                    decrypted_text_byusermod[i] = entry.second;
                }
            }
        }
}

// Метод для получения расшифрованного текста
string DECR_CLASS_ENG::get_decrypted_text_byfreq(bool enable_output) const {
        if (enable_output) {
            cout << "\n\n\n----------------------------------------------[Decrypted Text by Frequence Algorithm BEGIN]----------------------------------------------:\n"
                 << decrypted_text_byfreq <<
                 "\n\n\n----------------------------------------------[Decrypted Text by Frequence Algorithm END]----------------------------------------------\n\n\n";
        }
        return decrypted_text_byfreq;
}

string DECR_CLASS_ENG::get_decrypted_text_byusermod(bool enable_output) const {
        if (enable_output) {
            cout << "\n\n\n----------------------------------------------[Decrypted Text by +User Insert BEGIN]----------------------------------------------:\n"
                 << decrypted_text_byusermod <<
                 "\n\n\n----------------------------------------------[Decrypted Text by +User Insert END]----------------------------------------------\n\n\n";
        }
        return decrypted_text_byusermod;
}

unordered_map<char, char> DECR_CLASS_ENG::get_letter_mapping_byfreq(bool enable_output) const{

        if(enable_output){
            for (const auto& entry : letter_mapping_byfreq) {
                cout << "Original: " << entry.first << " -> Mapped: " << entry.second << endl;
            }
        }

        return letter_mapping_byfreq;
}

unordered_map<char, char> DECR_CLASS_ENG::get_letter_mapping_byusermod(bool enable_output) const{

        if(enable_output){
            for (const auto& entry : letter_mapping_byusermod) {
                cout << "Original: " << entry.first << " -> Mapped: " << entry.second << endl;
            }
        }

        return letter_mapping_byusermod;
}


unordered_map<char, double> DECR_CLASS_ENG::calculate_freq() {
        unordered_map<char, unsigned int> letter_count;
        unsigned int total_letters = 0;

        // Подсчёт частоты букв
        for (char c : encrypted_text) {
            if (isalpha(c)) {
                char upper_char = toupper(c);  // Переводим символ в верхний регистр
                letter_count[upper_char]++;
                total_letters++;
            }
        }

        // Преобразуем подсчитанные частоты в проценты
        unordered_map<char, double> letter_freq;
        for (const auto& entry : letter_count) {
            letter_freq[entry.first] = (double(entry.second) / total_letters) * 100;
        }

        return letter_freq;
    } // Вспомогательная функция для подсчёта частоты букв в тексте

vector<DECR_CLASS_ENG::LetterFreq> DECR_CLASS_ENG::sort_by_freq(const unordered_map<char, double>& letter_freq) {
        vector<DECR_CLASS_ENG::LetterFreq> sorted_freq;
        for (const auto& entry : letter_freq) {
            sorted_freq.push_back({entry.first, entry.second});
        }
        sort(sorted_freq.begin(), sorted_freq.end(), [](const DECR_CLASS_ENG::LetterFreq& a, const DECR_CLASS_ENG::LetterFreq& b) {
            return a.freq > b.freq;
        });
        return sorted_freq;
} // Вспомогательная функция для сортировки частот

// Инициализация статического поля для частот букв в английском языке
const unordered_map<char, double> DECR_CLASS_ENG::EnglishLang_letter_freq = {
    {'E', 12.70}, {'T', 9.06}, {'A', 8.17}, {'O', 7.51}, {'I', 6.97},
    {'N', 6.75}, {'S', 6.33}, {'R', 6.03}, {'H', 5.92}, {'D', 4.25},
    {'L', 4.03}, {'U', 3.64}, {'C', 3.33}, {'M', 3.01}, {'F', 2.23},
    {'P', 2.02}, {'G', 1.93}, {'Y', 1.77}, {'B', 1.49}, {'V', 0.98},
    {'K', 0.77}, {'X', 0.15}, {'J', 0.15}, {'Q', 0.10}, {'Z', 0.07},
    {'W', 2.36}
};


string _virtual_encryption_ENG(bool enable_output) {

    string text_to_encrypt = "In the fast-paced world of today, the ability to manage one’s time effectively has become more crucial than ever before. Whether you are a student, a working professional, or someone balancing both, mastering time management is key to ensuring productivity, reducing stress, and achieving personal and professional success.\
Time management is the process of planning and controlling how much time to spend on specific activities. Good time management allows individuals to complete more in a shorter period, which leads to more free time, and better opportunities in both personal and professional lives. When managed properly, time becomes a resource that works for you, rather than a constraint that holds you back.\
The benefits of time management are clear and undeniable. One of the most significant advantages is the increase in productivity. Effective time management enables individuals to focus on what matters most, ensuring that time is spent efficiently. By organizing tasks and setting priorities, people can minimize distractions, avoid procrastination, and concentrate on achieving goals.\
Another major benefit of time management is stress reduction. When you don’t manage your time effectively, you may find yourself rushing to meet deadlines or struggling to complete tasks. This often leads to feelings of overwhelm, anxiety, and burnout. However, when you have a clear plan and stick to it, you are able to work steadily without feeling pressured. Planning your time ahead of time helps you allocate enough time to each task, reducing the feeling of urgency and stress.\
Moreover, proper time management also fosters a sense of control. When individuals fail to manage their time, they may feel as though they are constantly reacting to circumstances, putting out fires, or dealing with tasks as they come. By taking charge of their schedules, people can take proactive steps toward their goals, rather than simply responding to external demands. This sense of control not only makes life more manageable but also helps individuals feel empowered to make choices about how they want to spend their time.\
One of the first steps to effective time management is setting clear, achievable goals. Whether they are short-term or long-term goals, understanding what you want to achieve and setting a clear roadmap to get there is essential. This can be done by breaking large tasks into smaller, more manageable actions, and scheduling specific times to work on each one. Setting deadlines for yourself also helps you stay on track and focused.\
In addition to setting goals, prioritizing tasks is another important element of time management. Not all tasks are created equal, and it’s essential to focus on the most important or urgent ones first. This means identifying high-priority tasks and addressing them before moving on to less critical activities. By doing this, individuals can ensure that they are making progress on what matters most, rather than getting bogged down in less important tasks.\
A common time management tool is the creation of to-do lists. These lists can be a simple and effective way to stay organized and on top of tasks. To-do lists allow you to write down everything you need to accomplish and check things off as you complete them. This provides a sense of accomplishment and keeps you motivated. However, it’s important not to overwhelm yourself by putting too many tasks on your list. Instead, focus on what can realistically be completed within a given time frame.\
Time blocking is another useful technique for managing time. This method involves scheduling specific blocks of time for certain tasks or activities. For example, you could dedicate a two-hour block in the morning to work on a project, followed by a one-hour block for answering emails, and then a break. Time blocking helps individuals stay focused on one task at a time, reduces multitasking, and prevents distractions. It is an effective strategy for improving productivity and ensuring that tasks are completed on time.\
Another key element of time management is learning how to say no. Many people find themselves overcommitted because they have difficulty turning down requests or offers. However, saying yes to too many things can lead to burnout and a lack of focus. By learning to say no when necessary, individuals can protect their time and energy for what truly matters to them.\
One of the biggest obstacles to effective time management is procrastination. Procrastination is the act of delaying or postponing tasks, often until the last minute. It is a common behavior that many people struggle with, but it can be overcome with a few simple strategies. One method is the Pomodoro Technique, which involves working for a set period of time (typically 25 minutes), followed by a short break. This creates a sense of urgency and helps individuals stay focused. Another strategy is breaking tasks into smaller steps, making them feel less overwhelming and easier to begin.\
While time management is essential for success, it’s also important to allow flexibility in your schedule. Life is unpredictable, and sometimes things don’t go as planned. While it’s important to stick to your goals and deadlines, it’s equally important to adapt to changes and unforeseen circumstances. Being flexible and adjusting your schedule when necessary will help you avoid unnecessary stress and stay on track even when things don’t go according to plan.\
In today’s digital age, technology has made time management easier than ever. There are countless apps, tools, and software that can help individuals stay organized and manage their time more effectively. For example, task management apps like Trello or Asana can help you keep track of projects and deadlines. Calendar apps such as Google Calendar or Outlook can be used to schedule events and appointments. Time-tracking tools like Toggl can help you monitor how much time you spend on various tasks, allowing you to identify areas where you can improve efficiency.\
Another helpful resource is the use of reminders and notifications. Setting alarms or reminders on your phone or computer can help you stay on top of important tasks and deadlines. These tools can help reduce the mental load of remembering everything, allowing you to focus on the task at hand without worrying about forgetting something.\
Ultimately, time management is about making intentional choices and recognizing that time is a finite resource. Everyone has the same 24 hours in a day, and how you choose to use that time can make a huge difference in your life. By prioritizing important tasks, setting clear goals, eliminating distractions, and using time management tools effectively, individuals can create a structured, balanced, and productive lifestyle. As a result, they can achieve success without sacrificing their mental health or well-being.\
In conclusion, time management is not a one-size-fits-all concept; it is a skill that can be tailored to each person’s unique needs and preferences. Whether you are aiming to improve productivity at work, manage your personal life more effectively, or simply find more time for relaxation and hobbies, the principles of time management are invaluable. The sooner you start implementing time management techniques into your life, the sooner you will experience the benefits of increased efficiency, reduced stress, and a greater sense of control over your time.";


  // Текст, который нужно зашифровать

    // Мапа для сопоставления букв английского алфавита с буквами шифра
    unordered_map<char, char> letter_mapping = {
        {'A', 'Q'}, {'B', 'W'}, {'C', 'E'}, {'D', 'R'}, {'E', 'T'},
        {'F', 'Y'}, {'G', 'U'}, {'H', 'I'}, {'I', 'O'}, {'J', 'P'},
        {'K', 'A'}, {'L', 'S'}, {'M', 'D'}, {'N', 'F'}, {'O', 'G'},
        {'P', 'H'}, {'Q', 'J'}, {'R', 'K'}, {'S', 'L'}, {'T', 'Z'},
        {'U', 'X'}, {'V', 'C'}, {'W', 'V'}, {'X', 'B'}, {'Y', 'N'},
        {'Z', 'M'}
    };

    // Шифруем текст с использованием мапы
    string encrypted_text = "";
    for (char c : text_to_encrypt) {
        if (isalpha(c)) {  // Если символ — буква
            char upper_char = toupper(c);  // Переводим в верхний регистр
            encrypted_text += letter_mapping[upper_char];  // Заменяем на шифрованную букву
        } else {
            encrypted_text += c;  // Если не буква (например, пробел), оставляем как есть
        }
    }

    // Выводим зашифрованный текст
    if(enable_output){
        cout << "\n\n\n----------------------------------------------[Virtual Encrypted Text BEGIN]----------------------------------------------:\n" << encrypted_text << "\n\n\n----------------------------------------------[Virtual Encrypted Text END]----------------------------------------------\n\n\n";
    }


    return encrypted_text;
}


void user_mod(DECR_CLASS_ENG* pchiper){

    char control_key;

    cout << "<user> do you want to change letter?(press y - to change, any key - to skip): ";
    cin >> control_key; cout<<"\n";

    if(control_key == 'y'){
        char old_letter, new_letter;

        cout<<"Enter the letter you want to replace: ";
        cin>>old_letter; cout<<"\n";

        cout<<"Enter the letter you want to replace with: ";
        cin>>new_letter; cout<<"\n";

        pchiper->user_insert(old_letter, new_letter);
        pchiper->decrypt_byusermod();
        pchiper->get_decrypted_text_byusermod(true);


        user_mod(pchiper);

    }

}





//-------------------------------------------------------------------------------------------------------------------------




DECR_CLASS_RUS::DECR_CLASS_RUS(const wstring& encrypted_text) : encrypted_text(encrypted_text) {}

void DECR_CLASS_RUS::decrypt(){

    this->decrypt_byfreq();
    this->get_decrypted_text_byfreq(true);

    user_mod(this);

}

void DECR_CLASS_RUS::decrypt_byfreq() {
        // Подсчёт частоты символов в зашифрованном тексте
        unordered_map<wchar_t, double> letter_freq_EncrText = calculate_freq();

        // Сортируем частоты для английского языка и зашифрованного текста
        vector<LetterFreq> sorted_ENG = sort_by_freq(RussianLang_letter_freq);
        vector<LetterFreq> sorted_Encrypted = sort_by_freq(letter_freq_EncrText);

        // Создаём мапу для сопоставления букв
        letter_mapping_byfreq.clear();  // Очищаем старое значение
        for (size_t i = 0; i < sorted_Encrypted.size(); ++i) {
            letter_mapping_byfreq[sorted_Encrypted[i].letter] = sorted_ENG[i].letter;
        }

        // Расшифровка текста без изменений пользователя
        decrypted_text_byfreq = L"";  // Очищаем старое значение
        for (wchar_t c : encrypted_text) {
            if (iswalpha(c)) {
                wchar_t upper_char = towupper(c);
                decrypted_text_byfreq += letter_mapping_byfreq[upper_char];  // Заменяем на соответствующую букву
            } else {
                decrypted_text_byfreq += c;  // Если не буква (например, пробел), оставляем как есть
            }
        }


        decrypted_text_byusermod = decrypted_text_byfreq;
}

void DECR_CLASS_RUS::user_insert(wchar_t old_letter, wchar_t new_letter){

            // old_letter - Это буква полученная по Частотному Методу, но оказалась неправильно(неудачно) сопоставлена шифрованному тексту(то есть encrypted_text). Она не подошла по смыслу слов(а), и в какой-то степени счиатается полушифрованной xD

            old_letter = towupper(old_letter);
            new_letter = towupper(new_letter);


            letter_mapping_byusermod[old_letter] = new_letter;
}

void DECR_CLASS_RUS::decrypt_byusermod() {
        decrypted_text_byusermod = decrypted_text_byfreq;

        for (const auto& entry : letter_mapping_byusermod) {
            for (size_t i = 0; i < decrypted_text_byusermod.size(); ++i) {
                if (iswalpha(decrypted_text_byusermod[i]) && towupper(decrypted_text_byusermod[i]) == entry.first) {
                    decrypted_text_byusermod[i] = entry.second;
                }
            }
        }
}

// Метод для получения расшифрованного текста
wstring DECR_CLASS_RUS::get_decrypted_text_byfreq(bool enable_output) const {
        if (enable_output) {
            wcout << "\n\n\n----------------------------------------------[Decrypted Text by Frequence Algorithm BEGIN]----------------------------------------------:\n"
                 << decrypted_text_byfreq <<
                 "\n\n\n----------------------------------------------[Decrypted Text by Frequence Algorithm END]----------------------------------------------\n\n\n";
        }
        return decrypted_text_byfreq;
}

wstring DECR_CLASS_RUS::get_decrypted_text_byusermod(bool enable_output) const {
        if (enable_output) {
            wcout << "\n\n\n----------------------------------------------[Decrypted Text by +User Insert BEGIN]----------------------------------------------:\n"
                 << decrypted_text_byusermod <<
                 "\n\n\n----------------------------------------------[Decrypted Text by +User Insert END]----------------------------------------------\n\n\n";
        }
        return decrypted_text_byusermod;
}

unordered_map<wchar_t, wchar_t> DECR_CLASS_RUS::get_letter_mapping_byfreq(bool enable_output) const{

        if(enable_output){
            for (const auto& entry : letter_mapping_byfreq) {
                wcout << "Original: " << entry.first << " -> Mapped: " << entry.second << endl;
            }
        }

        return letter_mapping_byfreq;
}

unordered_map<wchar_t, wchar_t> DECR_CLASS_RUS::get_letter_mapping_byusermod(bool enable_output) const{

        if(enable_output){
            for (const auto& entry : letter_mapping_byusermod) {
                wcout << "Original: " << entry.first << " -> Mapped: " << entry.second << endl;
            }
        }

        return letter_mapping_byusermod;
}


unordered_map<wchar_t, double> DECR_CLASS_RUS::calculate_freq() {
        unordered_map<wchar_t, unsigned int> letter_count;
        unsigned int total_letters = 0;

        // Подсчёт частоты букв
        for (wchar_t c : encrypted_text) {
            if (iswalpha(c)) {
                wchar_t upper_char = towupper(c);  // Переводим символ в верхний регистр
                letter_count[upper_char]++;
                total_letters++;
            }
        }

        // Преобразуем подсчитанные частоты в проценты
        unordered_map<wchar_t, double> letter_freq;
        for (const auto& entry : letter_count) {
            letter_freq[entry.first] = (double(entry.second) / total_letters) * 100;
        }

        return letter_freq;
    } // Вспомогательная функция для подсчёта частоты букв в тексте

vector<DECR_CLASS_RUS::LetterFreq> DECR_CLASS_RUS::sort_by_freq(const unordered_map<wchar_t, double>& letter_freq) {
        vector<DECR_CLASS_RUS::LetterFreq> sorted_freq;
        for (const auto& entry : letter_freq) {
            sorted_freq.push_back({entry.first, entry.second});
        }
        sort(sorted_freq.begin(), sorted_freq.end(), [](const DECR_CLASS_RUS::LetterFreq& a, const DECR_CLASS_RUS::LetterFreq& b) {
            return a.freq > b.freq;
        });
        return sorted_freq;
} // Вспомогательная функция для сортировки частот

// Инициализация статического поля для частот букв в английском языке
const unordered_map<wchar_t, double> DECR_CLASS_RUS::RussianLang_letter_freq = {
        {L'О', 10.97}, {L'Е', 8.45}, {L'А', 8.01},
        {L'И', 7.35}, {L'Н', 6.70}, {L'Т', 6.26},
        {L'С', 5.49}, {L'Р', 5.26}, {L'В', 4.72},
        {L'Л', 4.20}, {L'К', 3.49}, {L'М', 3.30},
        {L'Д', 3.14}, {L'П', 2.81}, {L'У', 2.63},
        {L'Я', 2.10}, {L'З', 1.94}, {L'Б', 1.58},
        {L'Ы', 1.54}, {L'Г', 1.47}, {L'Ч', 1.46},
        {L'Й', 1.24}, {L'Х', 1.23}, {L'Ш', 0.92},
        {L'Э', 0.87}, {L'Ю', 0.68}, {L'Ж', 0.59},
        {L'Ц', 0.46}, {L'Щ', 0.31}, {L'Ф', 0.23},
        {L'Ь', 0.20}, {L'Ъ', 0.03}, {L'Ё', 0.04}
};


wstring _virtual_encryption_RUS(bool enable_output) {

    wstring text_to_encrypt = L"В современном быстро меняющемся мире способность эффективно управлять своим временем стала важнее, чем когда-либо прежде. Независимо от того, являетесь ли вы студентом, работающим специалистом или тем, кто совмещает и то, и другое, овладение тайм-менеджментом является ключом к обеспечению производительности, снижению стресса и достижению личного и профессионального успеха.\
Управление временем — это процесс планирования и контроля того, сколько времени тратить на определенные действия. Хорошее управление временем позволяет людям успевать больше за более короткий период, что приводит к большему количеству свободного времени и лучшим возможностям как в личной, так и в профессиональной жизни. При правильном управлении время становится ресурсом, который работает на вас, а не ограничением, которое вас сдерживает.\
Преимущества управления временем очевидны и неоспоримы. Одним из самых значительных преимуществ является повышение производительности. Эффективное управление временем позволяет людям сосредоточиться на том, что важнее всего, гарантируя эффективное использование времени. Организуя задачи и устанавливая приоритеты, люди могут свести к минимуму отвлекающие факторы, избегать промедления и концентрироваться на достижении целей.\
Еще одним важным преимуществом управления временем является снижение стресса. Если вы не управляете своим временем эффективно, вы можете обнаружить, что торопитесь уложиться в сроки или изо всех сил пытаетесь выполнить задачи. Это часто приводит к чувству подавленности, беспокойства и выгорания. Однако, если у вас есть четкий план и вы его придерживаетесь, вы можете работать стабильно, не чувствуя давления. Планирование своего времени заранее помогает вам выделить достаточно времени на каждую задачу, уменьшая чувство срочности и стресса.\
Более того, правильное управление временем также способствует ощущению контроля. Когда люди не управляют своим временем, они могут чувствовать, что они постоянно реагируют на обстоятельства, тушат пожары или решают задачи по мере их поступления. Взяв на себя ответственность за свои графики, люди могут предпринимать проактивные шаги к своим целям, а не просто реагировать на внешние требования. Это чувство контроля не только делает жизнь более управляемой, но и помогает людям чувствовать себя уполномоченными делать выбор относительно того, как они хотят проводить свое время.\
Один из первых шагов к эффективному управлению временем — это постановка четких, достижимых целей. Независимо от того, краткосрочные это цели или долгосрочные, понимание того, чего вы хотите достичь, и установление четкого плана действий для их достижения имеет важное значение. Это можно сделать, разбив большие задачи на более мелкие, более управляемые действия и запланировав определенное время для работы над каждым из них. Установка для себя крайних сроков также помогает вам оставаться на пути и быть сосредоточенным.\
Помимо постановки целей, еще одним важным элементом управления временем является расстановка приоритетов в задачах. Не все задачи созданы равными, и важно сначала сосредоточиться на самых важных или срочных. Это означает определение высокоприоритетных задач и их решение, прежде чем переходить к менее важным действиям. Делая это, люди могут гарантировать, что они добиваются прогресса в том, что наиболее важно, а не увязают в менее важных задачах.\
Обычный инструмент управления временем — создание списков дел. Эти списки могут быть простым и эффективным способом оставаться организованными и контролировать задачи. Списки дел позволяют вам записывать все, что вам нужно выполнить, и вычеркивать пункты по мере их выполнения. Это дает чувство выполненного долга и поддерживает мотивацию. Однако важно не перегружать себя, помещая в свой список слишком много задач. Вместо этого сосредоточьтесь на том, что реально можно выполнить в заданные сроки.\
Блокировка времени — еще один полезный метод управления временем. Этот метод подразумевает планирование определенных блоков времени для определенных задач или занятий. Например, вы можете выделить двухчасовой блок утром для работы над проектом, затем часовой блок для ответа на электронные письма, а затем перерыв. Блокировка времени помогает людям сосредоточиться на одной задаче за раз, снижает многозадачность и предотвращает отвлечения. Это эффективная стратегия повышения производительности и обеспечения своевременного выполнения задач.\
Еще один ключевой элемент управления временем — научиться говорить «нет». Многие люди считают себя слишком занятыми, потому что им трудно отклонять просьбы или предложения. Однако, говоря «да» слишком многим вещам, можно выгореть и потерять концентрацию. Научившись говорить «нет», когда это необходимо, люди могут сохранить свое время и энергию для того, что для них действительно важно.\
Одним из самых больших препятствий для эффективного управления временем является прокрастинация. Прокрастинация — это процесс откладывания или откладывания задач, часто до последней минуты. Это распространенное поведение, с которым борются многие люди, но его можно преодолеть с помощью нескольких простых стратегий. Один из методов — метод Pomodoro, который подразумевает работу в течение определенного периода времени (обычно 25 минут), за которым следует короткий перерыв. Это создает ощущение срочности и помогает людям оставаться сосредоточенными. Другая стратегия — разбить задачи на более мелкие этапы, что делает их менее подавляющими и облегчает начало.\
Хотя управление временем необходимо для успеха, также важно допускать гибкость в своем расписании. Жизнь непредсказуема, и иногда все идет не так, как планировалось. Хотя важно придерживаться своих целей и сроков, не менее важно адаптироваться к изменениям и непредвиденным обстоятельствам. Гибкость и корректировка своего расписания при необходимости помогут вам избежать ненужного стресса и оставаться на верном пути, даже если все идет не по плану.\
В современный цифровой век технологии сделали управление временем проще, чем когда-либо. Существует бесчисленное множество приложений, инструментов и программного обеспечения, которые могут помочь людям оставаться организованными и управлять своим временем более эффективно. Например, приложения для управления задачами, такие как Trello или Asana, могут помочь вам отслеживать проекты и сроки. Приложения-календари, такие как Google Calendar или Outlook, можно использовать для планирования мероприятий и встреч. Инструменты отслеживания времени, такие как Toggl, могут помочь вам контролировать, сколько времени вы тратите на различные задачи, позволяя вам определять области, в которых вы можете повысить эффективность.\
Еще один полезный ресурс — использование напоминаний и уведомлений. Установка будильников или напоминаний на телефоне или компьютере может помочь вам оставаться в курсе важных задач и сроков. Эти инструменты могут помочь снизить умственную нагрузку от запоминания всего, позволяя вам сосредоточиться на текущей задаче, не беспокоясь о том, что вы что-то забудете.\
В конечном счете, управление временем заключается в принятии осознанного выбора и признании того, что время — это конечный ресурс. У всех людей 24 часа в сутках, и то, как вы решите использовать это время, может иметь огромное значение в вашей жизни. Расставляя приоритеты для важных задач, устанавливая четкие цели, устраняя отвлекающие факторы и эффективно используя инструменты управления временем, люди могут создать структурированный, сбалансированный и продуктивный образ жизни. В результате они могут добиться успеха, не жертвуя своим психическим здоровьем или благополучием.\
В заключение следует сказать, что управление временем — это не универсальная концепция; это навык, который можно адаптировать к уникальным потребностям и предпочтениям каждого человека. Независимо от того, хотите ли вы повысить производительность на работе, более эффективно управлять личной жизнью или просто найти больше времени для отдыха и хобби, принципы управления временем бесценны. Чем раньше вы начнете внедрять методы управления временем в свою жизнь, тем скорее вы почувствуете преимущества повышения эффективности, снижения стресса и большего чувства контроля над своим временем.";


  // Текст, который нужно зашифровать

    // Мапа для сопоставления букв русского алфавита с буквами шифра
    unordered_map<wchar_t, wchar_t> letter_mapping = {
            {L'А', L'К'}, {L'Б', L'Е'}, {L'В', L'Н'}, {L'Г', L'Р'}, {L'Д', L'С'},
            {L'Е', L'Т'}, {L'Ё', L'И'}, {L'Ж', L'О'}, {L'З', L'П'}, {L'И', L'Ш'},
            {L'Й', L'У'}, {L'К', L'Ф'}, {L'Л', L'Х'}, {L'М', L'Ц'}, {L'Н', L'Ч'},
            {L'О', L'Ж'}, {L'П', L'З'}, {L'Р', L'Я'}, {L'С', L'Л'}, {L'Т', L'В'},
            {L'У', L'Д'}, {L'Ф', L'М'}, {L'Х', L'Г'}, {L'Ц', L'Б'}, {L'Ч', L'Ь'},
            {L'Ш', L'Ы'}, {L'Щ', L'Э'}, {L'Ы', L'Ю'}, {L'Э', L'Я'}, {L'Ю', L'А'},
            {L'Я', L'Ё'}, {L'Ь', L'Ж'}, {L'Ъ', L'Й'}
    };



    // Шифруем текст с использованием мапы
    wstring encrypted_text = L"";
    for (wchar_t c : text_to_encrypt) {
        if (iswalpha(c)) {  // Если символ — буква
            wchar_t upper_char = towupper(c);  // Переводим в верхний регистр
            encrypted_text += letter_mapping[upper_char];  // Заменяем на шифрованную букву
        } else {
            encrypted_text += c;  // Если не буква (например, пробел), оставляем как есть
        }
    }

    // Выводим зашифрованный текст
    if(enable_output){
        wcout << "\n\n\n----------------------------------------------[Virtual Encrypted Text BEGIN]----------------------------------------------:\n" << encrypted_text << "\n\n\n----------------------------------------------[Virtual Encrypted Text END]----------------------------------------------\n\n\n";
    }


    return encrypted_text;
}

void user_mod(DECR_CLASS_RUS* pchiper){

    char control_key;

    cout << "<user> do you want to change letter?(press y - to change, any key - to skip): ";
    cin >> control_key; cout<<"\n";

    if(control_key == 'y'){
        char old_letter, new_letter;

        cout<<"Enter the letter you want to replace: ";
        cin>>old_letter; cout<<"\n";

        cout<<"Enter the letter you want to replace with: ";
        cin>>new_letter; cout<<"\n";

        pchiper->user_insert(old_letter, new_letter);
        pchiper->decrypt_byusermod();
        pchiper->get_decrypted_text_byusermod(true);


        user_mod(pchiper);

    }

}




#endif // DECRYPT_CPP
