#include <iostream>

class Log {
public:
	const int logLevelError = 0;
	const int logLevelWarning = 1;
	const int logLevelInfo = 2;
private:
	int m_logLevel = logLevelInfo;
public:
	void SetLevel(int level) {
		m_logLevel = level;
	};

	void Warn(const char* message) {
		std::cout << message << std::endl;
	}
};

int main() {
	Log log;
	log.SetLevel(logLevelWarning);
	log.Warn("Hello!");
	std::cin.get();
}