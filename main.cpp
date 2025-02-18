#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

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
    cin >> student.rollNumber;
    cout << "Введите количество предметов: ";
    int numSubjects;
    cin >> numSubjects;
    student.grades.resize(numSubjects);
    for (int i = 0; i < numSubjects; ++i) {
        cout << "Введите оценку по предмету " << i + 1 << ": ";
        cin >> student.grades[i];
    }
    students.push_back(student);
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
        cout << "3. Сохранить и выйти\n";
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
                saveToFile(students, filename);
                cout << "Данные сохранены. Выход.\n";
                return 0;
            default:
                cout << "Неверный ввод. Попробуйте снова." << endl;
        }
    }
}
