#pragma once
#include<string>

class Array {
private:
	char* result;
	unsigned int length;
	unsigned int capacity;
public:
	Array() : result(nullptr), length(0), capacity(1){};
	Array& copy_from_string(std::string const& init) {
		for (char cur : init) {
			if (length == capacity-1) {
				resize(capacity);
				capacity *= 2;
			}
			result[length] = cur;
			++length;
		}
		return *this;
	}
	~Array() {
		delete[] result;
	}
	unsigned int get_length() const {
		return length;
	}
	char& operator[](unsigned int i) const {
		return result[i];
	}

	void resize(unsigned int capacity) {
		capacity*=2;
		char* copy = new char[capacity];
		for (size_t i = 0; i < length; ++i) {
			copy[i] = result[i];
		}
		for (size_t i = length; i < capacity; ++i) {
			copy[i] = 0;
		}
		delete[] result;
		result = copy;
		copy = nullptr;
		delete[] copy;
	}

	Array& push_begin(unsigned int symbol) {
		char* for_adding = new char[length+1];
		for_adding[0] = symbol + '0';
		for (size_t i = 0; i < length; ++i) {
			for_adding[i + 1] = result[i];
		}
		++length;
		delete[] result;
		result = for_adding;
		for_adding = nullptr;
		delete[] for_adding;
		return *this;
	}

	Array& push_end(unsigned int symbol) {
		char* for_adding = new char[length+1];
		for (size_t i = 0; i < length; ++i){
			for_adding[i] = result[i];
		}
		for_adding[length] = symbol + '0';
		++length;
		delete[] result;
		result = for_adding;
		for_adding = nullptr;
		delete[] for_adding;
		return *this;
	}

	Array& insert(unsigned int symbol, unsigned int pos) {
		char* for_adding=new char[length];
		for (size_t i = 0; i < pos; ++i) {
			for_adding[i] = result[i];
		}
		for_adding[pos] = (char)(symbol + '0');
		for (size_t i = pos+1; i < length; ++i) {
			for_adding[i] = result[i];
		}
		delete[] result;
		result = for_adding;
		for_adding = nullptr;
		delete[] for_adding;
		return *this;
	}

	std::string to_string() {
		std::string res;
		size_t i = 0;
		while (result[i] == '0') ++i;
		while (i < length && result[i] != '0') {
			res += result[i];
			++i;
		}
		return res;
	}
};
