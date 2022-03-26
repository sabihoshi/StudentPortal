#pragma once

#include <functional>
#include <vector>

template <typename T>
struct Node
{
	explicit Node(T item) : Item(item) {}

	T Item;
	Node* Next = nullptr;
};

template <typename T>
struct LinkedList
{
	Node<T>* Head = nullptr;
	Node<T>* Tail = nullptr;

	/**
	 * \brief Adds a new item to the linked list
	 * \param add The item to add
	 */
	void Add(T add)
	{
		Add(new Node<T>(add));
	}

	/**
	 * \brief Adds a new item to the linked list
	 * \param add The node to add
	 */
	void Add(Node<T>* add)
	{
		if (Head == nullptr)
		{
			Head = add;
			Tail = Head;
		}
		else
			Tail = Tail->Next = add;
	}

	/**
	 * \brief Deletes an item in the linked list based on its index
	 * \param index The index of the item to delete
	 */
	T* Delete(const int index)
	{
		auto current = Head;
		for (int i = 0; i < index - 1; i++)
		{
			current = current->Next;
		}

		auto removed = current->Next;

		if (current->Next->Next)
			current->Next = current->Next->Next;
		else
			current->Next = nullptr;

		return &removed->Item;
	}

	/**
	 * \brief Filters items in the linked list based on a bool predicate
	 * \param f The functor predicate to use
	 * \return An item that matches the predicate
	 */
	std::vector<T> Where(std::function<bool(T&)> f)
	{
		std::vector<T> result;
		for (auto current = Head; current; current = current->Next)
		{
			if (f(current->Item))
				result.push_back(current->Item);
		}
		return result;
	}

	/**
	 * \brief Finds an item in the linked list based on a bool predicate
	 * \param f The functor predicate to use
	 * \return An item that matches the predicate
	 */
	T* Find(std::function<bool(T&)> f)
	{
		for (auto current = Head; current; current = current->Next)
		{
			if (f(current->Item)) return &current->Item;
		}

		return nullptr;
	}

	/**
	 * \brief Finds the index of an item in the linked list based on a bool predicate
	 * \param f The functor predicate to use
	 * \return The item of the item that matches the predicate
	 */
	int IndexOf(std::function<bool(T&)> f)
	{
		int index = 0;
		for (auto current = Head; current; current = current->Next )
		{
			if (f(current->Item))
				return index;

			index++;
		}

		return -1;
	}

	/**
	 * \brief Deletes the first item in the linked list based on a bool predicate
	 * \param f The functor predicate to use
	 */
	T* Delete(std::function<bool(T&)> f)
	{
		const int index = IndexOf(f);
		return index == -1 ? nullptr : Delete(index);
	}

	std::vector<T> ToVector()
	{
		std::vector<T> list;
		for (auto current = Head; current; current = current->Next)
		{
			list.push_back(current->Item);
		}
		return list;
	}
};
