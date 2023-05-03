#pragma once
template <class T>
class Option {
private:
	bool has_value_ = false;
	T value_;
public:
	Option() {}
	Option(T value) {
		this->value_ = value;
		this->has_value_ = true;
	}

	bool has_value() {
		return this->has_value_;
	}

	T value() {
		return this->value_;
	}

	T value_or(T default_value) {
		if (this->has_value()) {
			return this->value();
		}
		return default_value;
	}
};

