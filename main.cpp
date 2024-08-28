/*
Тест
Задание №1

Если в вашем классе есть умный указатель в качестве члена вашего класса, то почему вы должны стараться
                                                                          избегать динамического выделения объектов этого класса?

 Динамическое выделение обьектов этого класса грозит тем, что обьекты класса могут быть не обработаны
   корректно. Т.е. могут быть не удалены. Что в свою очередь приведет к утечке памяти.

 Задание №2
 Измените следующую программу, заменив обычный указатель на умный указатель std::unique_ptr, где это необходимо:
 Программа приведена ниже.
     */


#include <iostream>
#include <memory>


   class Fraction
{
private:
 int m_numerator = 0;
 int m_denominator = 1;

public:
 Fraction(int numerator = 0, int denominator = 1) :
     m_numerator(numerator), m_denominator(denominator)
 {

 }

 friend std::ostream& operator<<(std::ostream& out, const Fraction &f1)
 {
   out << f1.m_numerator << "/" << f1.m_denominator;
   return out;
 }
};


void printFraction(std::unique_ptr<Fraction> ptr)
{
 if (ptr)
   std::cout << *ptr;
}


int main()
{

 std::unique_ptr<Fraction> ptr = std::make_unique<Fraction>(7,9);

 printFraction(std::move(ptr));

 return EXIT_SUCCESS;
}