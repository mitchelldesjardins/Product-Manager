// Milestone 2
// Author: Mitchell Desjardins
// Email: mtdesjardins@myseneca.ca
// Student Number: 059863126
// Section Number: SJJ

#include <string.h>
#include "ErrorState.h"

namespace ama
{
	ErrorState::ErrorState(const char *errorMessage)
	{
		if (errorMessage == nullptr || errorMessage[0] == '\0') {
			c_Message = nullptr;
		}
		else {
			c_Message = new char[strlen(errorMessage)];
			strncpy(c_Message, errorMessage, strlen(errorMessage) + 1);
		}
	}

	ErrorState::~ErrorState()
	{
		delete[] c_Message;
		c_Message = nullptr;
	}
	ErrorState::operator bool() const {
		return c_Message != nullptr && c_Message[0] != '\0';
	}

	ErrorState& ErrorState::operator=(const char* pText) {
		if (this->c_Message != pText) {
			delete[] c_Message;
			if (pText != nullptr && pText[0] != '\0') {
				c_Message = new char[strlen(pText)];
				strncpy(c_Message, pText, strlen(pText));
			}
			else
				c_Message = nullptr;
		}
		return *this;
	}

	void ErrorState::message(const char* pText) {
		if (pText != nullptr && pText[0] != '\0') {
			delete[] c_Message;
			c_Message = new char[strlen(pText) + 1];
			strcpy(c_Message, pText);
		}
		else {
			c_Message = nullptr;
		}
	}

	const char* ErrorState::message()const {
		return c_Message;
	}

	std::ostream& operator<<(std::ostream& os, const ErrorState& text) {
		if (text.message() != nullptr)
		{
			os << text.message();
			return os;
		}
		else
		{
			return os;
		}
	}

}