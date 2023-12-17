#pragma once
#include <iostream>
#include <stdexcept>

/*
* @brief Структура для реализации класса List, в которой хранится информации об элементе, а также ссылки на предыдущий и следующий элементы.
*/
template <typename T>
struct Element {
	T data;
	Element* previous;
	Element* next;
	Element() : data(), previous(nullptr), next(nullptr) {};
};

/*
* @brief Класс List. Представляется из себя двусвязный циклический список.
*/
template <typename T>
class List {
private:
	Element<T>* head;
	Element<T>* tail;
	size_t size;
public:

	/*
	* @breif Конструктор по умолчанию.
	*/
	List();

	/*
	* @brief Метод, позволяющий получить размер списка.
	* @return Размер списка.
	*/
	size_t getSize() const;

	/*
	* @brief Метод, позволяющий добавить элемент в конец списка.
	* @param newData - информация о новом элементе
	*/
	void pushBack(T newData);

	/*
	* @brief Метод, позволяющий добавить элемент в начало списка.
	* @param newData - информация о новом элементе.
	*/
	void pushFront(T newData);

	/*
	* @brief Метод, позволяющий получить информацию о первом элементе списка.
	* @return Информация о первом элементе.
	*/
	T getFront() const;

	/*
	* @brief Метод, позволяющий получить информацию о последнем элементе списка.
	* @return Информация о последнем элементе.
	*/
	T getBack() const;

	/*
	* @brief Метод, удаляющий первый элемент списка.
	*/
	void popFront();

	/*
	* @brief Метод, удаляющий последний элемент списка.
	*/
	void popBack();

	/*
	* @brief Метод, удаляющий элемент списка по ключу.
	* @param position - ключ (позиция элемента в списке).
	*/
	void deleteELement(size_t position);

	/*
	* @brief Метод, позволяющий вставить элемент в список.
	* @param data - информация об элементе (его размер).
	* @param position - позиция, на которую нужно элемент поставить.
	*/
	void insertElement(T data, size_t position);

	/*
	* @brief Метод, позволяющий получить данные об элементе списка.
	* @param position - позиция элемента в списке.
	* @return Информация об элементе - его размер.
	*/
	T getElement(size_t position) const;

	/*
	* @brief Метод, удаляющий все элементы списка.
	*/
	void deleteAll();

	/*
	* @brief Конструктор копирования.
	*/
	List(const List& other);

	/*
	* @brief Оператор копирования.
	*/
	List& operator = (const List& other);

	/*
	* @brief Конструктор перемещения.
	*/
	List(List&& other) noexcept;

	/*
	* @brief Оператор перемещения
	*/
	List& operator = (List&& other) noexcept;

	/*
	* @brief Деструктор
	*/
	~List();
};


template <typename T>
List<T>::List() : head(nullptr), tail(nullptr), size(0) {};

template <typename T>
List<T>::List(const List& other) : List()
{
	Element<T>* temp = other.head;
	for(size_t i = 0; i < other.getSize(); i++)
	{
		this->pushBack(temp->data);
		temp = temp->next;
	}
	this->size = other.size;
}

template <typename T>
List<T>& List<T>::operator = (const List& other) {
	if (this == &other)
		return *this;
	List<T> copy(other);
	std::swap(this->tail, copy.tail);
	std::swap(this->head, copy.head);
	std::swap(this->size, copy.size);

	return *this;
}

template <typename T>
size_t List<T>::getSize() const{
	return this->size;
}

template <typename T>
void List<T>::pushBack(T newData) {
	Element<T>* temp = new Element<T>();
	temp->data = newData;
	if (this->getSize() == 0) {
		temp->previous = temp;
		temp->next = temp;
		this->head = temp;
		this->tail = temp;
	}
	else if (this->getSize() == 1) {
		temp->previous = this->head;
		temp->next = this->head;
		this->tail = temp;
		this->head->next = temp;
		this->head->previous = temp;
	} else {
		temp->previous = this->tail;
		temp->next = this->head;
		tail->next = temp;
		this->tail = temp;
		this->head->previous = this->tail;
	}
	++this->size;
}

template <typename T>
void List<T>::pushFront(T newData) {
	Element<T>* temp = new Element<T>();
	temp->data = newData;
	if (this->getSize() == 0) {
		temp->next = temp;
		temp->previous = temp;
		this->head = temp;
		this->tail = temp;
	}
	else if (this->getSize() == 1) {
		temp->previous = this->tail;
		temp->next = this->tail;
		this->head = temp;
		this->tail->next = temp;
		this->tail->previous = temp;
	} else {
		temp->next = this->head;
		temp->previous = this->tail;
		head->previous = temp;
		this->head = temp;
		this->tail->next = this->head;
	}
	++this->size;
}

template <typename T>
T List<T>::getFront() const {
	return this->head->data;
}

template <typename T>
T List<T>::getBack() const {
	return this->tail->data;
}

template <typename T>
void List<T>::popBack() {
	if (this->getSize() == 0)
		throw std::logic_error("Нельзя удалять элементы в пустом листе");
	if (this->getSize() == 1) {
		delete this->tail;
		this->head = nullptr;
		this->tail = nullptr;
		--this->size;
		return;
	}
	else if (this->getSize() == 2) {
		delete this->tail;
		this->head->next = this->tail;
		this->tail = this->head;
		--this->size;
		return;
	}
	auto temp = this->tail;
	this->tail = this->tail->previous;
	this->tail->next = this->head;
	this->head->previous = this->tail;
	delete temp;
	--this->size;
}

template <typename T>
void List<T>::popFront() {
	if (this->getSize() == 0)
		throw std::logic_error("Нельзя удалять элементы в пустом листе");
	if (this->getSize() == 1) {
		delete this->head;
		this->head = nullptr;
		this->tail = nullptr;
		--this->size;
		return;
	}
	else if (this->getSize() == 2) {
		delete this->head;
		this->tail->previous = nullptr;
		this->head = this->tail;
		--this->size;
		return;
	}
	auto temp = this->head;
	this->head = this->head->next;
	this->head->previous = this->tail;
	this->tail->next = this->head;
	delete temp;
	--this->size;
}

template <typename T>
void List<T>::deleteELement(size_t position) {
	if (position >= this->getSize())
		throw std::out_of_range("Позиция больше размера списка");
	if (position == 0) {
		this->popFront();
		return;
	}
	else if (position == this->getSize() - 1) {
		this->popBack();
		return;
	}
	auto temp = this->head;
	for (size_t i = 0; i < position; i++)
	{
		temp = temp->next;
	}
	temp->previous->next = temp->next;
	temp->next->previous = temp->previous;
	delete temp;
	--this->size;
}

template <typename T>
void List<T>::insertElement(T data, size_t position) {
	if (position > this->getSize())
		throw std::out_of_range("Позиция больше размера списка");
	if (position == 0) {
		this->pushFront(data);
		return;
	}
	else if (position == this->getSize()) {
		this->pushBack(data);
		return;
	}
	auto insert = this->head;
	for (size_t i = 0; i < position; i++)
	{
		insert = insert->next;
	}
	Element<T>* temp = new Element<T>();
	temp->data = data;
	if (insert->previous != nullptr && this->getSize() != 1)
		insert->previous->next = temp;
	temp->next = insert;
	temp->previous = insert->previous;
	insert->previous = temp;

	++this->size;
}

template <typename T>
T List<T>::getElement(size_t position) const{
	if (position >= this->getSize())
		throw std::out_of_range("Позиция больше размера списка");
	auto get = this->head;
	for (size_t i = 0; i < position; i++)
	{
		get = get->next;
	}
	return get->data;
}

template <typename T>
void List<T>::deleteAll() {
	while (this->getSize() != 0)
		this->popBack();
}

template <typename T>
List<T>::~List() {
	this->deleteAll();
}


template <typename T>
List<T>::List(List&& other) noexcept : List() {
	*this = other;
}

template <typename T>
List<T>& List<T>::operator = (List&& other) noexcept {
	std::swap(this->tail, other.tail);
	std::swap(this->head, other.head);
	std::swap(this->size, other.size);
	return *this;
}

template <typename T>
std::ostream& operator << (std::ostream& os, const List<T>& list) {
	for (size_t i = 0; i < list.getSize(); i++)
	{
		os << list.getElement(i) << " ";
	}
	return os;
}