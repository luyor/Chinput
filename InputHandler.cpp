#include "InputHandler.h"
#include <QDir>

InputHandler::InputHandler(void) :
	set()
{
	FILE *file = NULL;

    QString home_path = QDir::homePath();
    home_path = home_path.append("/Development/cpp/Chinput/input_set");
    file = fopen(home_path.toUtf8().constData(), "r");

	char s[3] = {}, t[7] = {};

	while (true) {
        fscanf(file, "%3s%7s", s, t);

		if (s[0] == '-') {
			break;
		}

		set.push_back(std::make_pair(t, s));
	}

	fclose(file);
}
const InputHandler::ResultVector InputHandler::get_result(const std::string &input) {
	std::vector<std::pair<std::string, std::string>>::iterator it = set.begin();

	std::vector<std::string> result;
    if (input.size() == 0) {
        return result;
    }

	while (it->first < input) {
		++it;
	}
	while (it != set.end() && it->first <= input + "{") {
		result.push_back(it->second);
		++it;
	}

	return result;
}
