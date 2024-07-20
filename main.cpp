/*
Тест

Какие из следующих стейтментов, обозначенные буквами, не скомпилируются:
   int main()
{
 int x;

 // Ссылки l-value
 int &ref1 = x; // A                           -ok
 int &ref2 = 7; // B                           -not ok

 const int &ref3 = x; // C                     -ok
 const int &ref4 = 7; // D                     -ok

 // Ссылки r-value
 int &&ref5 = x; // E                          -not ok
 int &&ref6 = 7; // F                          -ok

 const int &&ref7 = x; // G                    -not ok
 const int &&ref8 = 7; // H                    -ok

 return 0;
}
*/