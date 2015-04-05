#ifndef __INPUT_HANDLER_H__
#define __INPUT_HANDLER_H__

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

class InputHandler {
public:
    typedef std::vector<std::string> ResultVector;
	explicit InputHandler(void);

    const ResultVector get_result(const std::string &input);

private:
    std::vector<std::pair<std::string, std::string> > set;

};

#endif
