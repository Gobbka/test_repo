#include "Windows.h"

// Number 1
template<typename T>
class SmartPointer
{
	T* _object;
public:

	SmartPointer(T*object){ _object = new T(); }

	SmartPointer(T& object)
	{
		_object = new T();
		*_object = object;
	}

	SmartPointer()
	{
		_object = new T();
	}

	~SmartPointer()
	{
		delete _object;
	}

	T* operator->()
	{
		return _object;
	}

	T operator* ()
	{
		return *_object;
	}
};

// NUMBER 2

template<typename T>
class List;

template<typename T>
class Iterator
{
	T* _ptr;
public:
	Iterator(T* pointer)
	{
		_ptr = pointer;
	}

	bool operator!=(Iterator<T>& iterator)
	{
		return _ptr != iterator._ptr;
	}

	bool valid()
	{
		return _ptr == nullptr;
	}

	void operator++()
	{
		_ptr++;
	}

	void operator--()
	{
		_ptr--;
	}

	T operator* ()
	{
		return *_ptr;
	}
};

template<typename T>
class List
{
	unsigned _version;

	unsigned _allocated;
	unsigned _size;

	T** _list;
private:
	bool alloc_more()
	{
		auto need_to_alloc = (_allocated / 50 + 1) * 50;
		auto** new_list = new T * [need_to_alloc];
		memcpy((void*)new_list, (void*)_list, _size);

		delete[] _list;
		_list = new_list;
		_allocated = need_to_alloc;

		return true;
	}
public:
	auto version() const { return _version; }
	auto ptr() const { return _list; }

	List()
	{
		_version = 0;
		_list = new T*[50];
		_size = 0;
		_allocated = 50;
	}

	Iterator<T*> begin()
	{
		return Iterator<T*>(_list);
	}

	Iterator<T*> end()
	{
		return Iterator<T*>(_list+_size);
	}

	void insert(const T& element)
	{
		_size + 1 > _allocated && alloc_more();

		auto* p_element = new T();
		*p_element = element;
		_list[_size] = p_element;
		
		_size++;
	}

	void erase(const T&element)
	{
		for(auto i = _size;i-->0;)
		{
			if(element == *_list[i])
			{
				memcpy(_list, _list, (i) * sizeof(T));
				memcpy(_list + i,_list + i + 1,(_size - i - 1) * sizeof(T));

				delete _list[i];
				_size--;
			}
		}
	}
};

// NUMBER 3

template<typename TKey, typename TValue>
struct Pair
{
	TKey key;
	TValue value;

	Pair(TKey key,TValue value)
	{
		this->key = key;
		this->value = value;
	}

	bool operator==(Pair&cmp)
	{
		return cmp.key == key && cmp.value == value;
	}
};

template<typename Key,typename Value>
class Map
{
	List<Pair<Key, Value>> _pairs;

public:
	Map()
	{
		
	}

	void erase(Key key)
	{
		for (auto pair : _pairs)
			if (pair->key == key)
			{
				_pairs.erase(pair);
				return;
			}
	}

	void insert(Key key,Value value)
	{
		auto exist_pair = find(key);

		if(exist_pair.valid())
		{
			exist_pair->value = value;
		}else
		{
			_pairs.insert(Pair<Key, Value>(key, value));
		}

	}

	Iterator<Pair<Key, Value>> find(Key key)
	{
		for(auto pair : _pairs)
			if (pair->key == key)
				return Iterator<Pair<Key, Value>>(pair);
		return Iterator<Pair<Key, Value>>(nullptr);
	}

	Iterator<Pair<Key, Value>> find(Value value)
	{
		for (auto pair : _pairs)
			if (pair->value == value)
				return Iterator<Pair<Key, Value>>(pair);
		return Iterator<Pair<Key, Value>>(nullptr);
	}

	Iterator<Pair<Key, Value>> begin()
	{
		return _pairs.begin();
	}

	Iterator<Pair<Key, Value>> end()
	{
		return _pairs.end();
	}
};

// NUMBER 4

template<typename Key,typename Value>
class Set : Map<Key,Value>
{
public:
	void insert(Key key,Value value)
	{
		auto exist_pair = Map::find(value);
		if(!exist_pair.valid())
		{
			Map::insert(key, value);
		}
	}
};

int main()
{

}
