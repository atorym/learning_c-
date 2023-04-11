/*
Задание
Напишите программу, которая просит у пользователя ввести его имя, фамилию и возраст. В результате,
укажите пользователю, сколько лет он прожил на каждую букву из его имени и фамилии (чтобы было проще,
учитывайте также пробелы).
Например:

Enter your full name: Tom Cats
Enter your age: 45
You've lived 5.625 years for each letter in your name.
*/

#include <iostream>
#include <string>

int main() {
  {
    using namespace std;
    cout << "Enter your full name\n";
    string name;
    getline(cin, name);
    cout << "Enter your age\n";
    int age;
    cin >> age;
    cout << "Your name is " << name << ", in your name " << name.length() - 1 << " characters.\n"
         << "You've lived " << static_cast<double>(age) / (name.length() - 1.0) << " years for each letter in your name.";
  }
  return EXIT_SUCCESS;
}
