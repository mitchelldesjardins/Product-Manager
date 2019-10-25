// Milestone 2
// Author: Mitchell Desjardins
// Email: mtdesjardins@myseneca.ca
// Student Number: 059863126
// Section Number: SJJ

#ifndef AMA_ERRORSTATE_H
#define AMA_ERRORSTATE_H
#include <iostream>

namespace ama
{
	class ErrorState {
		char* c_Message;
	public:
		explicit ErrorState(const char* errorMessage = nullptr);
		ErrorState(const ErrorState&) = delete;
		ErrorState& operator=(const ErrorState&) = delete;
		~ErrorState();
		operator bool() const;
		ErrorState& operator=(const char* pText);
		void message(const char* pText);
		const char*  message() const;
	};
	std::ostream& operator<<(std::ostream& os, const ErrorState& text);
}

#endif


