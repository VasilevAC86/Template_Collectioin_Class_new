#include<iostream>
#include<vector>
// Создание шаблонного связного списка

template<typename Type>
class LinkedList { // Класс "связанный список"
public:
	LinkedList() // Констр. по умолчанию
		:start_(nullptr), //: заполняет значения до того, как объект класса начнёт своё существование
		end_(nullptr),
		size_(0)
	{}
	// Параметрический конструктор (лист с уже созданными b-элементами). Надо создать столько элементов Node, сколько требует пользователь
	LinkedList(int i) :LinkedList() { // Делегация конструктору по умолчанию
		// Надо заполнить список пустыми точками, переданными пользователем
		if (n < 0)throw - 1; // Если пользователь прислал отриц. знач-е, работа конструктора завершиться с кодом -1		
		if (n == 0)return; // Коллекцию можно создать из нуля точек (коллекция пустая)
		Node* tmp{}; // для временного хранения вновь созданного элемента (точки)
		//------ первый вариант
		/*size_ = n;
		do{
			tmp = new Node;
			if (start_ == nullptr)
				start_ = tmp; 
			n -= 1;
		} while (n>0);*/ 
		//------ второй вариант
		int count{0}; // счётчик кол-ва добавленных точек, {} проверяют корректность типа данных, что в переменную передано именно число типа int
		tmp = new Node{};
		start_ = tmp; // 1-ая созданная точка - это начало
		end_ = tmp; // 1-ая созданная точка - это и конец
		count += 1; // посчитали созданную точку
		// Далее добавляем в список новые точки
		while (count < n) { // в n хранится значение от пользователя, сколько Node нужно
			tmp = new Node{}; // создаём новую точку (выделяем под неё место)
			end_->Next(tmp); // Устанавливаем значение последнему элементу (старому концу списка говорим, что новый конечный элемент существует)
			end_ = tmp; // Список запоминает, какой элемент считается последним 
			count += 1; // Считает, сколько Node создано
		}
		size_ = n;
	}
	LinkedList(const LinkedList& other):LinkedList() { // Конструктор копирования должен корректно скопировать данные из одного списка в другой.\
		 Делегируем работу конструктора копирования когструктору по умолчанию, чтобы заполнить поля нулями
		if (other.size() == 0) return; // Чтобы не копировать созданный по умолчанию пустой список
		start_ = new Node(other.strat_->Data()); // В начальную точку нового списка создали точку для переноса инф-ии
		end_ = start_;
		for (Node *current = other.strat_->Next(); current!=nullptr; current=current->Next()) { // Указатель на вторую точку в переданном списке, текущая точка не должна быть нулевым указателем
			//Node* tmp = new Node(other[i]); // медленно из-за квадратных скобок 
			Node* tmp = new Node(current->Data());
			end_->Next(tmp);
			end_ = tmp;
		}
		size_ = other.size_;
	}
	LinkedList(LinkedList&& other):LinkedList() { // можно не делать, но для оптимизации скорости работы программы полезно
		// тут не будет реализации конструктора от списка инициализации, внесём позже
		std::swap(start_, other.strat_);
		std::swap(end_, other.end_);
		std::swap(size_, other.size_);
	}
	~LinkedList() {
		Node* current = strat_; 
		while (current != nullptr) {
			Node *tmp = current->Next(); // Запомнили след.элемент за тем, который собираемся освобождать
			delete current; // Освобождаем память от точки
			current = tmp; // Делаем текущей точкой ту, которую мы запомнили
		}
	}

	void clear() { // Чиста списка под новые данные
		Node* current = strat_;
		while (current != nullptr) {
			Node* tmp = current->Next(); // Запомнили след.элемент за тем, который собираемся освобождать
			delete current; // Освобождаем память от точки
			current = tmp; // Делаем текущей точкой ту, которую мы запомнили
		}
		strat_ = nullptr;
		end_ = nullptr;
		size_ = 0;
	}

	// Чтобы не возникали ошибки работы с памятью:
	LinkedList& operator = (const LinkedList& other) { // присваивание копированием
		clear(); // Чистим список под новые данные
		if (other.size() == 0) return *this; 
		start_ = new Node(other.strat_->Data()); 
		end_ = start_;
		for (Node* current = other.strat_->Next(); current != nullptr; current = current->Next()) {
			
			Node* tmp = new Node(current->Data());
			end_->Next(tmp);
			end_ = tmp;
		}
		size_ = other.size_;
		return *this;
	}
	LinkedList& operator = (const LinkedList&& other) { // присваивание переносом временного объекта
		clear(); 
		std::swap(start_, other.strat_);
		std::swap(end_, other.end_);
		std::swap(size_, other.size_);
		return *this;
	}
	Type& operator[](int i) { // Оператор [] для доступа к хранящимся в списке элементам с возможностью их изменения
		int count{};
		Node* tmp = start_;
		while (count < 1)	{
			tmp = tmp->Next();
			count += 1;
		}
		return tmp->Data();
	}

	Type& at(int i) {
		if (i < 0 || i >= size_) throw - 1; // Если мы вышли за диапазон значений
		int count{};
		Node* tmp = start_;
		while (count < 1) {
			tmp = tmp->Next();
			count += 1;
		}
		return tmp->Data();
	}

	const Type& at(int i)const {
		if (i < 0 || i >= size_) throw - 1; // Если мы вышли за диапазон значений
		int count{};
		Node* tmp = start_;
		while (count < 1) {
			tmp = tmp->Next();
			count += 1;
		}
		return tmp->Data();
	}

	const Type& operator[](int i)const { // Чтобы мы могли иметь доступ к элементам в любом случае, не меняя их		
		int count{};
		Node* tmp = start_;
		while (count < 1) {
			tmp = tmp->Next();
			count += 1;
		}
		return tmp->Data();
	}
	// Методы доступа к элементам коллекции
	// Для удобства пользователя (чтобы было меньше букв, пишем метод at, который заменяет [])
	Type& at(int i); // метод at позволяет получать доступ к коллекциям, at может кидать исключения, [] исключений не кидают, [] делают то, что попросили
	const Type& at(int i)const;
	
	void push_back(const Type& obj); // Добавить данные в конец
	void push_front(const Type& obj); // Добавить данные в начало

	void pop_back(); // Уничтожить данные в конце списка (место хранение будет занулено, ячейка хранения будет уничтожена)
	void pop_front(); // Уничтожить данные в начале списка (место хранение будет занулено, ячейка хранения будет уничтожена)

	// Методы для задач работы с центром коллекции
	/*
	emplace/incert - методы добавления новых данных в произвольное место коллекции (emplace - создание нового из запчастей, incert - копия на базе существующего) 
	erise - метод уничтожения данных в произвольном месте коллекции
	*/
	int size()const { // Сколько в коллекции есть элементов (гэттэр поля size)
		return size_;
	}
	/*
	методы для прохода по коллекции "умными указателями" пока сознательно опустим
	*/
	
private:
	class Node{ // Вложенный класс (служебная подпрограмма, которая не касается класса LinkedList: Node отвечает за хранение, а LinkedList - за доступ)
	public:
		// При делегации мы вызываем конструктор по умолчанию хранимого типа данных. Данный синтаксис корректно отработает даже если прфмой вызов такого 
		// метода (например, конструктора встроенных типов) недоступен.
		Node():Node(Type()) {} // При создании должна хранить в себе данные (универсальное обращение конструктора к любому типу данных)		
		Node(const Type& data, Node *place=nullptr):data_(data),next_(place)
		{ }
		// Два метода доступа к данным (один позволит менять данные, другой нет)
		Type& Data() { // Кому будет передана ссылка, будет работать с инф-ей в data_ (Заполнение точки данными)
			return data_;
		}
		const Type& Data()const { // менять данные нельзя
			return data_;
		}
		Node* Next()const { // метод для предоставлении инф-ии о нахождении следующей точки в списке
			return next_;
		}
		void Next(Node* next) { // Установка нового значения для следующей точки
			next_ = next;
		}
	private:
		Type data_; // Хранение блока переданных Node данных, точка знает, что в ней лежит
		Node* next_; // Она должна знать, где находится следующая точка
	};
	Node* strat_; // Точка старта
	Node* end_; // Точка окончания списка
	int size_; // Размер списка
};

int main() {
	int arr[10];
	std::vector<int> vec(10);
	LinkedList<int> list;
	arr[5] = 34;
	vec[5] = 23;
	list[5] = 12;
	std::size(vec);
	std::size(list);
	// for (/*переменная для хранения элементов*/:/*коллекция, элементы которой нужно перебрать*/)
	/*for (int &e:arr) {
		std::cout << e << ' ';
	}
	for (auto &e : vec) {
		std::cout << e << ' ';
	}*/

	return 0;
}