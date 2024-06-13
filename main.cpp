/*
Тест
Какой результат выполнения следующих программ? Не нужно запускать/выполнять следующий код, вы должны определить
результат без помощи своих IDE.

a) В результате выполнения программы выведется "A", т.к. в классе нет метода getName, и виртуальные функции
проверяют только 2 класса: класс ссылки и класс на который она указывает.

#include <iostream>
class A
{
public:
 virtual const char* getName() { return "A"; }
};

class B: public A
{
public:
 virtual const char* getName() { return "B"; }
};

class C: public B
{
public:
 // Примечание: Здесь нет метода getName()
};

class D: public C
{
public:
 virtual const char* getName() { return "D"; }
};

int main()
{
 C c;
 A &rParent = c;
 std::cout << rParent.getName() << '\n';

 return 0;
}

---------------------------------------------------------------------------------------------------------------
b) В результате выполнения программы выведется "C".

#include <iostream>

class A
{
public:
 virtual const char* getName() { return "A"; }
};

class B: public A
{
public:
 virtual const char* getName() { return "B"; }
};

class C: public B
{
public:
 virtual const char* getName() { return "C"; }
};

class D: public C
{
public:
 virtual const char* getName() { return "D"; }
};

int main()
{
 C c;
 B &rParent = c; // примечание: rParent на этот раз класса B
 std::cout << rParent.getName() << '\n';

 return 0;
}

---------------------------------------------------------------------------------------------------------------
c) В результате выполнения программы выведется "A", т.к. материнский класс A не поддерживает виртуальные функции.

#include <iostream>

class A
{
public:
 const char* getName() { return "A"; } // примечание: Нет ключевого слова virtual
};

class B: public A
{
public:
 virtual const char* getName() { return "B"; }
};
class C: public B
{
public:
 virtual const char* getName() { return "C"; }
};

class D: public C
{
public:
 virtual const char* getName() { return "D"; }
};

int main()
{
 C c;
 A &rParent = c;
 std::cout << rParent.getName() << '\n';

 return 0;
}

---------------------------------------------------------------------------------------------------------------
d)В результате выполнения программы выведется "С", т.к. getName в A виртуальная, а слово "virtual" в
дочерних классах можно не писать для того чтобы функция getName в них была "virtual".

#include <iostream>

class A
{
public:
 virtual const char* getName() { return "A"; }
};

class B: public A
{
public:
 const char* getName() { return "B"; } // примечание: Нет ключевого слова virtual
};

class C: public B
{
public:
 const char* getName() { return "C"; } // примечание: Нет ключевого слова virtual
};

class D: public C
{
public:
 const char* getName() { return "D"; } // примечание: Нет ключевого слова virtual
};

int main()
{
 C c;
 B &rParent = c; // примечание: rParent на этот раз класса B
 std::cout << rParent.getName() << '\n';

 return 0;
}

---------------------------------------------------------------------------------------------------------------
e)В результате выполнения программы выведется "С". Т.к. константность перегрузке не мешает.

#include <iostream>

class A
{
public:
 virtual const char* getName() const { return "A"; } // примечание: Метод является const
};

class B: public A
{
public:
 virtual const char* getName() { return "B"; }
};

class C: public B
{
public:
 virtual const char* getName() { return "C"; }
};

class D: public C
{
public:
 virtual const char* getName() { return "D"; }
};

int main()
{
 C c;
 A &rParent = c;
 std::cout << rParent.getName() << '\n';

 return 0;
}

---------------------------------------------------------------------------------------------------------------
f) Ошибка компиляции? Нарушено правило, о котором говорили в уроке. Вызывать виртуальные функции в конструкторах
и деструкторах запрещено.

#include <iostream>

class A
{
public:
 A() { std::cout << getName(); } // обратите внимание на наличие конструктора

 virtual const char* getName() { return "A"; }
};

class B : public A
{
public:
 virtual const char* getName() { return "B"; }
};

class C : public B
{
public:
 virtual const char* getName() { return "C"; }
};

class D : public C
{
public:
 virtual const char* getName() { return "D"; }
};

int main()
{
 C c;

 return 0;
}

*/