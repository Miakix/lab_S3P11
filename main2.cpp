#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Структура для хранения данных студента
struct Student {
    string name;
    int age;
    double grade;
    int course;       // Номер курса
    string faculty;   // Факультет
    string group;     // Номер группы

    // Метод для вывода информации о студенте
    string toString() const {
        return "Имя: " +  name + ", Возраст: " + to_string(age) + ", Средний балл: " + to_string(grade) + ", Курс: " + to_string(course) + ", Факультет: " + faculty + ", Группа: " + group;
    }
};

// Функция для чтения данных из файла
bool readData(const string& filename, vector<Student>& students) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла." << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Student student;
        getline(ss, student.name, ',');
        ss >> student.age;
        ss.ignore(1, ','); // игнорируем запятую
        ss >> student.grade;
        ss.ignore(1, ','); // игнорируем запятую
        ss >> student.course;
        ss.ignore(1, ','); // игнорируем запятую
        getline(ss, student.faculty, ',');
        getline(ss, student.group);
        students.push_back(student);
    }

    file.close();
    return true;
}

// Функция для просмотра данных
void viewData(const vector<Student>& students) {
    cout << "Список студентов:" << endl;
    for (size_t i = 0; i < students.size(); ++i) {
        cout << i + 1 << ": " << students[i].toString() << endl;
    }
}

// Функция для редактирования данных
void editData(vector<Student>& students) {
    int index;
    cout << "Введите номер студента для редактирования: ";
    cin >> index;
    if (index < 1 || index > students.size()) {
        cout << "Некорректный номер." << endl;
        return;
    }

    Student& student = students[index - 1];
    cout << "Введите новое имя (текущее: " << student.name << "): ";
    cin.ignore();
    getline(cin, student.name);
    cout << "Введите новый возраст (текущий: " << student.age << "): ";
    cin >> student.age;
    cout << "Введите новую оценку (текущая: " << student.grade << "): ";
    cin >> student.grade;
    cout << "Введите новый номер курса (текущий: " << student.course << "): ";
    cin >> student.course;
    cout << "Введите новый факультет (текущий: " << student.faculty << "): ";
    cin.ignore();
    getline(cin, student.faculty);
    cout << "Введите новый номер группы (текущий: " << student.group << "): ";
    getline(cin, student.group);
}

// Функция для добавления нового студента
void addStudent(vector<Student>& students) {
    Student newStudent;
    cout << "Введите имя: ";
    cin.ignore();
    getline(cin, newStudent.name);
    cout << "Введите возраст: ";
    cin >> newStudent.age;
    cout << "Введите оценку: ";
    cin >> newStudent.grade;
    cout << "Введите номер курса: ";
    cin >> newStudent.course;
    cout << "Введите факультет: ";
    cin.ignore();
    getline(cin, newStudent.faculty);
    cout << "Введите номер группы: ";
    getline(cin, newStudent.group);
    students.push_back(newStudent);
}

// Функция для удаления студента
void deleteStudent(vector<Student>& students) {
    int index;
    cout << "Введите номер студента для удаления: ";
    cin >> index;
    if (index < 1 || index > students.size()) {
        cout << "Некорректный номер." << endl;
        return;
    }
    students.erase(students.begin() + (index - 1));
    cout << "Студент удален." << endl;
}

// Функция для вычисления средней оценки
void calculateAverageGrade(const vector<Student>& students) {
    if (students.empty()) {
        cout << "Нет студентов для вычисления средней оценки." << endl;
        return;
    }

    double sum = 0.0;
    for (const auto& student : students) {
        sum += student.grade;
    }
    double average = sum / students.size();
    cout << "Средняя оценка: " << average << endl;
}

// Функция для сохранения данных в файл
void saveData(const string& filename, const vector<Student>& students) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла для записи." << endl;
        return;
    }

    for (const auto& student : students) {
        file << student.name << "," << student.age << "," << student.grade << "," << student.course << "," << student.faculty << "," << student.group << endl;
    }

    file.close();
}

int main() {
    vector<Student> students;
    bool dataLoaded = false;
    int choice;

    do {
        cout << "\nМеню:\n"
             << "1. Просмотр данных\n"
             << "2. Корректировка данных\n"
             << "3. Добавление студента\n"
             << "4. Удаление студента\n"
             << "5. Вычисление средней оценки\n"
             << "6. Сохранение данных в новый файл\n"
             << "0. Выход\n"
             << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (!dataLoaded) {
                    if (readData("1.txt", students)) {
                        dataLoaded = true;
                        cout << "Данные успешно загружены." << endl;
                    }
                } else {
                    cout << "Данные уже загружены." << endl;
                }
                viewData(students);
                break;
            case 2:
                editData(students);
                break;
            case 3:
                addStudent(students);
                break;
            case 4:
                deleteStudent(students);
                break;
            case 5:
                calculateAverageGrade(students);
                break;
            case 6: {
                string filename;
                cout << "Введите имя нового файла: ";
                cin >> filename;
                saveData(filename, students);
                break;
            }
            case 0:
                cout << "Выход из программы." << endl;
                break;
            default:
                cout << "Некорректный выбор. Попробуйте еще раз." << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}

