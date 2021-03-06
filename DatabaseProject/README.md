# База данни с числа и символни низове

**Описание на структурата на приложението:**

Реализираният проект поддържа работата с множество таблици. Всяка от тях се състои от произволен брой колони, всяка от които може да е от тип или цяло число, или символен низ. Всяка колона има име - символен низ. Таблиците в базата данни се съхраняват на диска.Предназначението на базата данни е за работа с малки по обем таблици. Не се налага ограничение върху дължината на редовете, защото данните от тип стринг се запазват в реалния си размер. Работата с големи по обем данни би довела до забавяне в изпълнението на командите.

Приложението поддържа команди за работа с таблици (CreateTable, DropTable, ListTables, TableInfo) и команди за работа с данните (Select, Remove, Insert), реализирани в класа Database.

За да се изпълни дадена команда, потребителят въвежда нейното име на екрана, като при грешка в синтаксиса ще бъде уведомен със съответното съобщение. За изход от програмата се въвежда командата Quit.

При създаване на таблица, името й се запазва в текстов файл с име TablesInfo.txt, който има за цел да улесни намирането на дадена таблица в базата данни. При прехване на таблица, името й се изтрива от файла.

Записите на всяка таблица се съхраняват в отделен бинарен файл с име <име_на_таблицата>.dat. В началото на този файл се записва информацията за типа и името на колоните, подадена като string. 
Информацията за колоните се извежда в програмата като при четене от файла данните за всяка колона се запазват в динамичен масив от структури на класа ColumnsInfo. Всяка структура има за член-данни името на колоната и нейния тип (int  или string). С цел подпомагане на реализирането на командите чрез директен достъп до всяка колона.

Записването на данни в таблицата се добавя след вече записания входен низ за колоните и се реализира като първо се записва индекс за всеки ред, който се генерира като пореден номер според броя на редовете(не е видим за потребителя, използва се за улесняване  на изпълнението на командите). След него се добавя всеки следващ елемент на реда в зависимост от неговия тип. Когато елемента е от тип string първо се записва дължината му, която е от тип unsigned int с големина 4 байта памет, след него се записва и самия символен низ. Елемент от тип int се записва директно във файла с големина също 4 байта.
При извеждане на ред в програмата, данните му се запазват в динамичен масив от указатели към абстрактен клас Column според типа на съответната колона. Класа Column е наследен от класове IntColunn и StringColumn, за да може да съхранява данни от различни типове, което подпомага филтрирането на реда при командата Select. Масивът е реализиран в класа RowData.

При създаването на всяка таблица се създава и бинарен файл с име <име_на_таблицата>_Info.dat, който има за цел да съхранява дължината на всеки добавен ред в таблицата. В него се записва и дължината на стринга с информацията за типа и името на колоните. Всеки размер е от тип int с големина 4 байта. Целта на този файл е да улесни извличането на ред от таблицата при реализацята на функциите за работа с данните.

Премахването на редове от таблицата се осъществява като се маркира съответния ред за изтрит. За изпълнението на тази команда се взимат данните от файла <име_на_таблицата>_Info.dat и се променя размера на съответния ред, отбелязан за изтриване (превръща се в отрицателно число). Реалното изтриване на данните от файла се осъществява чрез команда, въведена от потребителя.

Информация за дадена таблица се извежда като се представят броя на редовете в таблицата ( броя на елементите записани във файла с име <име_на_таблицата>_Info.dat) и размера на всички записи в таблицата ( сумата от положителните стойности на елементите от същия файл).

**Описание на командите, изпълнявани от реализираната база данни:**

***CreateTable:***

Cъздава нова таблица по подадено име и списък от имената и типовете на съставящите я колони като първо добавя името и във файла с име TablesInfo.txt , след което записва входния низ съдържащ информация за колоните към файла с име <име_на_таблицата>.dat. A неговата дължина бива записвана във файла <име_на_таблицата>_Info.dat.
 	Наличието на символа ‘,’ в името или колоната би довело до неправилно функциониране на програмата. Имена на колони нe могат да бъдат AND, OR и Remove, тъй като това са запазени думи.

***DropTable:***

Премахва таблица по нейното име.Осъществява се като първо премахне името на таблицата от файла TablesInfo.txt, след това изтрива  таблицата и създадения файл с име <име_на_таблицата>_Info.dat.

***ListTables:***

Извежда на екрана имената на всички налични таблици и техния брой, като за целта прочита всички записани имена от файла TablesInfo.txt.

***TableInfo:***

Извежда информация (схема и брой записи) за таблица по подадено име като за целта прочита символния низ с данните за колоните  от файла <име_на_таблицата>.dat и го изкарва на екрана.
 Броя на редовете се изчислява като се вземе броя на положителните стойности от файла с име <име_на_таблицата>_Info.dat., паметта заемана на диска се пресмята като се сумират всички положителнит стойности от същия файл. (това може да не са реалните стойности, тъй като редовете може да са маркирани като изтрити имайки отрицателна стойност, но не се премахват от таблицата докатo потребителя не въведе командата RemoveData) .
 В тази информация не се включва дължината на входния символен низ.

Следните функции са за работа с данните се изпълнявят като се създаде обект на класа Table. Този клас има за член-данни името на таблицата, обект на класа ColumnsInfo и динамичен масив rowsSizeArr, в който в началото на изпълнението на функцията ще бъдат зареждани стойностите от файла <име_на_таблицата>_Info.dat.
При създаване на обект на класа, информацията за типа и имената на колоните се извлича в класа ColumnsInfo от файла с име <име_на_таблицата>.dat

***Insert:***

  Добавя един или повече нови редове в таблица чрез вътрешна функция на вече създадения обект на класа Table. 
При записването на всеки ред се генерира пореден индекс за реда, който се образува от текущата дължина на масива rowsSizeArr. При записване на ред в таблицата, неговата дължина се изчислява и се добавя към масива rowsSizeArr, който накрая на командата бива записван наново във файла <име_на_таблицата>_Info.dat.

***Select:***

Филтрира записите от дадена таблица чрез вътрешна функция на вече създадения обект на  класа Table.
Изпълнението на тази команда е разделено на две части, при наличие на ORDER BY и когато не е посочено.
Стойностите на имената на колоните, операторите за сравнение и логическите оператори се съхраняват в структурата от данни опашка. Нейните свойства я правят подходяща за обработването на информация, тъй като операцията по премахване винаги извлича първия добавен елемент и има сложност О(1).
При наличие на повече от един логически оператор, потребителят трябва да огради съответни израз в скоби (), с цел правилното определяне на приоритета на операциите.
В случай че потребителя не е задал условието за сортиране, във функцията на класа Table се подава създадената опашка. Таблицата се обхожда като се прочита последователно всеки ред от файла с име <име_на_таблицата>.dat, стойностите му се добавят в масива oт класа RowData, преди оценяването на реда се проверява дали неговия размер от масива rowsSizeArr има положителна стойност, в противен случай редът не може да бъде достъпен , защото е маркиран за изтрит. След това се оценява реда, като за целта резултата от всяко сравнение и съответните логически операции се запазват в структурата от данни стек. Избрана е следната структура за обработването на израза, поради свойството да извлича последния добавен елемент със сложност на тази операция О(1). В случай, че реда удовлетворява условието, неговите стойности се изкарват на екрана. 
Ако заявката поддържа ORDER BY след като се провери дали реда изпълнява условието, неговия индекс и колоната  по която трябва да се сортира се добавят съответно в два динамични масива. След като се обходи цялата таблица, масивите се сортират. Избраният алгоритъм за сортиране е по Метода на мехурчето, защото е стабилен и гарантира правилната подредба на елементите. След изпълнение на сортировката, индексите на  редовете са вече подредени и стойностите на даден ред се извеждат на екрана като се прочитат от файла <име_на_таблицата>.dat. 

***Remove:***

Премахва определени редове от таблица чрез вътрешна функция на вече създадения обект на  класа Table.
Стойностите на имената на колоните, операторите за сравнение и логическите оператори се съхраняват в структурата от данни опашка. Нейните свойства я правят подходяща за обработването на информация, тъй като операцията по премахване винаги извлича първия добавен елемент и има сложност О(1).
При наличие на повече от един логически оператор, потребителят трябва да огради съответни израз в скоби (), с цел правилното определяне на приоритета на операциите.
Таблицага се обхожда като се прочита последователно всеки ред от файла с име <име_на_таблицата>.dat, стойностите му се добавят в масива oт класа RowData, преди оценяването на реда се проверява дали неговия размер от масива rowsSizeArr има положителна стойност, в противен случай редът не може да бъде достъпен , защото е маркиран за изтрит. След това се оценява реда, като за целта резултата от всяко сравнение и съответните логически операции се запазват в структурата от данни стек. Избрана е следната структура за обработването на израза, поради свойството да извлича последния добавен елемент със сложност на тази операция О(1).
Aко прочетения ред отговаря на условията, то неговата дължина от от масива rowsSizeArr се преобразува в отрицателно число и по този начин се маркира, че реда е обозначен за изтриване. Накрая на изпълнението на командата, всички стойности от масива rowsSizeArr се записват наново във файла  <име_на_таблицата>_Info.dat. 

***RemoveData:***

Премахва всички редове от таблицата, които са маркирани като изтрити. Премахването на ред се осъществява, като всички редове освен обозначените за изтриване се записват в нов временен файл, който се преименува като <име_на_таблицата>.dat, a предишния файл с това име се изтрива. При записването на ред в новия файл се гарантира и промяната на неговия индекс. Стойностите от файла <име_на_таблицата>_Info.dat, които са отрицателни се изтриват от масива, в който са заредени и след това се записват отново във файла.

**Описание на синтаксиса на командите:**

```
CreateTable <име_на_таблица> (<име_на_колона>:<тип_на_колона>, <име_на_колона>:<тип_на_колона>...)
DropTable <име_на_таблица> 
ListTables   
TableInfo <име_на_таблица>  
Select <име_на_колона> FROM <име_на_таблица> WHERE <израз> 
(Select * FROM <име_на_таблица> WHERE <израз>)    
Select <име_на_колона> FROM <име_на_таблица> WHERE <израз> ORDER BY <име_на_колона> 
(Select * FROM <име_на_таблица> WHERE <израз> ORDER BY <име_на_колона>)
Insert INTO <име_на_таблица> {(<стойност>, <стойност>...), (<стойност>, <стойност>...), ...}    
Remove FROM <име_на_таблица> WHERE <израз>  
RemoveData <име_на_таблица>   
```







