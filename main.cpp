#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

struct Student {
    string name;
    int rollNumber;
    vector<int> grades;

    double calculateAverage() const {
        if (grades.empty()) return 0.0;
        int sum = 0;
        for (int grade : grades) {
            sum += grade;
        }
        return static_cast<double>(sum) / grades.size();
    }
};

void saveToFile(const vector<Student>& students, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return;
    }
    for (const auto& student : students) {
        file << student.name << " " << student.rollNumber;
        for (int grade : student.grades) {
            file << " " << grade;
        }
        file << endl;
    }
    file.close();
}

void loadFromFile(vector<Student>& students, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return;
    }
    students.clear();
    Student student;
    while (file >> student.name >> student.rollNumber) {
        student.grades.clear();
        int grade;
        while (file.peek() != '\n' && file >> grade) {
            student.grades.push_back(grade);
        }
        students.push_back(student);
    }
    file.close();
}

void addStudent(vector<Student>& students) {
    Student student;
    cout << "Введите имя студента: ";
    cin >> student.name;
    cout << "Введите номер списка: ";
    while (!(cin >> student.rollNumber)) {
        cout << "Ошибка! Введите корректный номер: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Введите количество предметов: ";
    int numSubjects;
    while (!(cin >> numSubjects) || numSubjects <= 0) {
        cout << "Ошибка! Введите корректное число предметов: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    student.grades.resize(numSubjects);
    for (int i = 0; i < numSubjects; ++i) {
        cout << "Введите оценку по предмету " << i + 1 << ": ";
        while (!(cin >> student.grades[i]) || student.grades[i] < 0 || student.grades[i] > 100) {
            cout << "Ошибка! Введите корректную оценку (0-100): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    students.push_back(student);
}

void editStudent(vector<Student>& students) {
    int rollNumber;
    cout << "Введите номер списка студента для редактирования: ";
    cin >> rollNumber;
    for (auto& student : students) {
        if (student.rollNumber == rollNumber) {
            cout << "Введите новое имя: ";
            cin >> student.name;
            cout << "Введите новые оценки (кол-во предметов: " << student.grades.size() << "):\n";
            for (auto& grade : student.grades) {
                cout << "Оценка: ";
                cin >> grade;
            }
            return;
        }
    }
    cout << "Студент не найден!" << endl;
}

void deleteStudent(vector<Student>& students) {
    int rollNumber;
    cout << "Введите номер списка студента для удаления: ";
    cin >> rollNumber;
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->rollNumber == rollNumber) {
            students.erase(it);
            cout << "Студент удален." << endl;
            return;
        }
    }
    cout << "Студент не найден!" << endl;
}

void displayStudents(const vector<Student>& students) {
    cout << "\nСписок студентов:\n";
    for (const auto& student : students) {
        cout << "Имя: " << student.name << ", Номер списка: " << student.rollNumber
             << ", Средний балл: " << fixed << setprecision(2) << student.calculateAverage() << endl;
    }
}

int main() {
    vector<Student> students;
    string filename = "students.txt";
    loadFromFile(students, filename);

    while (true) {
        cout << "\nМеню:\n";
        cout << "1. Добавить студента\n";
        cout << "2. Показать всех студентов\n";
        cout << "3. Редактировать студента\n";
        cout << "4. Удалить студента\n";
        cout << "5. Сохранить и выйти\n";
        cout << "Выберите опцию: ";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                addStudent(students);
                break;
            case 2:
                displayStudents(students);
                break;
            case 3:
                editStudent(students);
                break;
            case 4:
                deleteStudent(students);
                break;
            case 5:
                saveToFile(students, filename);
                cout << "Данные сохранены. Выход.\n";
                return 0;
            default:
                cout << "Неверный ввод. Попробуйте снова." << endl;
        }
    }
}
