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
