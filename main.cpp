#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <set>
#include <unordered_set>
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
// Класс кредит
class BankCredit{
    std::string name;
    int sum;
    int percent;
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
    BankCredit(std::string name, int sum, int percent, currency curr){
        this->curr = curr;
        this->sum = sum;
        this->name = name;
        this->percent = percent;
    }
    // Оператор сравнения для сортировки
    bool operator < (const BankCredit& credit) const{
        return (percent < credit.percent);
    }
    // ==
    bool operator==(const BankCredit& credit) const {
        return sum == credit.sum && 
               percent == credit.percent && 
               name == credit.name &&
               curr == credit.curr;
    }
    // гетеры
    size_t Sum() const{return sum;}
    size_t Percent() const{return percent;}
    std::string Name() const{return name;}
    currency Currency() const{return curr;}
    // Описания дружественных методов для вывода и сохранения в файл
    friend std::ostream& operator<<(std::ostream&, const BankCredit& credit);
    friend std::ofstream& operator<<(std::ofstream& stream, const BankCredit& credit);
    friend void saveToFile(const std::string& filename, const std::vector<BankCredit>& credits);
    friend void saveToFile(const std::string& filename, const std::deque<BankCredit>& credits);
};
struct HashFunction {
    int operator()(const BankCredit& credit) const {
        int h1 = std::hash<std::string>{}(credit.Name());
        int h2 = std::hash<int>{}(credit.Sum());
        int h3 = std::hash<int>{}(credit.Percent());
        int h4 = std::hash<int>{}(static_cast<int>(credit.Currency()));
        return h1 + (h2 * 1) + (h3 * 2) + (h4 * 3);
    }
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
    out.open(filename, std::ios::out);
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
    out.open(filename, std::ios::out);
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
            int sum{std::stoul(line.substr(pos1+1, pos2))};

            auto pos3 = line.find(" ", pos2+1);
            int percent{std::stoul(line.substr(pos2+1, pos3))};

            std::string notParsedCurrency = line.substr(pos3+1);
            currency currency_code = parseCurrency(notParsedCurrency);

            BankCredit new_credit(name, sum, percent, currency_code);
            vec.push_back(new_credit);
        }
        in.close();
    }
}
int main(){
    BankCredit bc1 {"potreb", 200000, 1, currency::RUB};
    BankCredit bc2 {"ipoteka", 100000, 5, currency::USD};
    BankCredit bc3 {"ipoteka", 400000, 6, currency::GBP};
    BankCredit bc4 {"ipoteka", 500000, 7, currency::ILS};
    BankCredit bc5 {"ipoteka", 300000, 10, currency::TRY};
    std::unordered_set<BankCredit, HashFunction> mySet{bc1, bc2};
    mySet.insert(bc3);
    mySet.insert(bc4);
    mySet.insert(bc5);
    for (BankCredit n : mySet)
        std::cout << n << "\n";
    std::cout << std::endl;
}