#pragma once

template <typename T>
struct default_constructible_ref
{
	default_constructible_ref() = default;
	default_constructible_ref(T& ref) : _ref(&ref) {}
	default_constructible_ref(const default_constructible_ref& other) = default;
	default_constructible_ref& operator=(const default_constructible_ref& other) = default;

	operator bool() const {
		return _ref != nullptr;
	}

	T& get() {
		if (_ref)
			return *_ref;
		else
		{
			static T dummy;
			return dummy;
		}
	}

	const T& get() const {
		if (_ref)
			return *_ref;
		else
		{
			static const T dummy;
			return dummy;
		}
	}

private:
	T * _ref = nullptr;
};

template <typename T>
struct default_constructible_cref
{
	default_constructible_cref() = default;
	default_constructible_cref(const T& ref) : _ref(&ref) {}
	default_constructible_cref(const default_constructible_cref& other) = default;
	default_constructible_cref& operator=(const default_constructible_cref& other) = default;

	operator bool() const {
		return _ref != nullptr;
	}

	const T& get() const {
		if (_ref)
			return *_ref;
		else
		{
			static const T dummy;
			return dummy;
		}
	}

private:
	const T* _ref = nullptr;
};

