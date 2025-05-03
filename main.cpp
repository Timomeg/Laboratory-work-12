#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
// Перечисление для валют
enum class currency{
    RUB,
    USD,
    EUR,
    AUD,
    GBP,
    ILS,
    TRY,
    JPY
};
class BankCredit{
    std::string name;
    size_t sum;
    size_t percent;
    currency curr;
public:
    // Дефолтный конструктор 
    BankCredit(){
        name = "";
        sum = 0;
        percent = 0;
        curr = currency::USD;
    }
    // Констуктор копирования
    // В констукторе перемещения нет смысла, так как все поля класса занимают фиксированное кол-во памяти
    BankCredit(std::string name, size_t sum, size_t percent, currency curr){
        this->curr = curr;
        this->sum = sum;
        this->name = name;
        this->percent = percent;
    }
    // Оператор сравнения для сортировки
    bool operator < (const BankCredit& credit1) const{
        return (percent < credit1.percent);
    }
    // Описания дружественных методов для вывода и сохранения в файл
    friend std::ostream& operator<<(std::ostream&, const BankCredit& credit);
    friend std::ofstream& operator<<(std::ofstream& stream, const BankCredit& credit);
    friend void saveToFile(const std::string& filename, const std::vector<BankCredit>& credits);
    friend void saveToFile(const std::string& filename, const std::deque<BankCredit>& credits);
};

// Перевод валюты в строку для вывода в терминал
std::ostream& operator<<(std::ostream& stream, const currency& curr){
    switch(curr) {
        case currency::USD: stream << "USD"; break;
        case currency::EUR: stream << "EUR"; break;
        case currency::GBP: stream << "GBP"; break;
        case currency::RUB: stream << "RUB"; break;
        case currency::TRY: stream << "TRY"; break;
        case currency::AUD: stream << "AUD"; break;
        case currency::JPY: stream << "JPY"; break;
        case currency::ILS: stream << "ILS"; break;
    }
    return stream;
}
// Перевод валюты в строку для вывода в файл
std::ofstream& operator<<(std::ofstream& stream, const currency& curr){
    switch(curr) {
        case currency::USD: stream << "USD"; break;
        case currency::EUR: stream << "EUR"; break;
        case currency::GBP: stream << "GBP"; break;
        case currency::RUB: stream << "RUB"; break;
        case currency::TRY: stream << "TRY"; break;
        case currency::AUD: stream << "AUD"; break;
        case currency::JPY: stream << "JPY"; break;
        case currency::ILS: stream << "ILS"; break;
    }
    return stream;
}
// Вывод данных о кредите в терминал
std::ostream& operator<<(std::ostream& stream, const BankCredit& credit){
    stream << credit.name << " " << credit.sum << " "  << credit.percent << " "  << credit.curr;
    return stream;
}
// Вывод данных о кредите в терминал
std::ofstream& operator<<(std::ofstream& stream, const BankCredit& credit){
    stream << credit.name << " " << credit.sum << " "  << credit.percent << " "  << credit.curr;
    return stream;
}
// Сохранение в файл вектора кредитов
void saveToFile(const std::string& filename, const std::vector<BankCredit>& credits){
    std::ofstream out;
    out.open(filename, std::ios::app);
    if (out.is_open()){
        for (size_t i {}; i < credits.size(); i++) {
            out << credits[i].name << " " << credits[i].sum << " "  << credits[i].percent << " "  << credits[i].curr << "\n";
        }
        out.close();
    }
}
// Сохранение двухсвязного списка кредитов
void saveToFile(const std::string& filename, const std::deque<BankCredit>& credits){
    std::ofstream out;
    out.open(filename, std::ios::app);
    if (out.is_open()){
        for (size_t i {}; i < credits.size(); i++){
            out << credits[i].name << " " << credits[i].sum << " "  << credits[i].percent << " "  << credits[i].curr << "\n";
        }
        out.close();
    }
}
// Перевод строки в объект перечисления
currency parseCurrency(const std::string& input){
    if (input == " USD"){
        return currency::USD;
    }
    if (input == " EUR"){
        return currency::EUR;
    }
    if (input == " ILS"){
        return currency::ILS;
    }
    if (input == " GBP"){
        return currency::GBP;
    }
    if (input == " AUD"){
        return currency::AUD;
    }
    if (input == " TRY"){
        return currency::TRY;
    }
    if (input == " JPY"){
        return currency::JPY;
    }
    return currency::RUB;
}
// Загрузка из файла 
void loadFromFile(const std::string& filename, std::vector<BankCredit>& vec){

    std::ifstream in;
    in.open(filename, std::ios::in);
    if (in.is_open()){
        std::string line;

        while(std::getline(in, line)){

            auto pos1 = line.find(" ");
            std::string name = line.substr(0, pos1);

            auto pos2 = line.find(" ", pos1+1);
            size_t sum{std::stoul(line.substr(pos1+1, pos2))};

            auto pos3 = line.find(" ", pos2+1);
            size_t percent{std::stoul(line.substr(pos2+1, pos3))};

            std::string notParsedCurrency = line.substr(pos3+1);
            currency currency_code = parseCurrency(notParsedCurrency);

            BankCredit new_credit(name, sum, percent, currency_code);
            vec.push_back(new_credit);
        }
        in.close();
    }
}
int main(){
}