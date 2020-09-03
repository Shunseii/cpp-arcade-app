#ifndef __FILECOMMANDLOADER_H__
#define __FILECOMMANDLOADER_H__

#include <functional>
#include <vector>
#include <string>
#include <stdint.h>

class Color;
class Vec2D;

struct ParseFuncParams {
	std::string line;
	size_t delimitPos;
	uint32_t lineNum;
};

using ParseFunc = std::function<void(const ParseFuncParams& params)>;

enum CommandType {
	COMMAND_ONE_LINE = 0,
	COMMAND_MULTI_LINE
};

struct Command {
	CommandType commandType = COMMAND_ONE_LINE;
	std::string command = "";
	ParseFunc parseFunc = nullptr;
};

class FileCommandLoader {
	private:
		std::vector<Command> mCommands;

	public:
		void AddCommand(const Command&);
		bool LoadFile(const std::string& filePath);
		
		static Color ReadColor(const ParseFuncParams& params);
		static Vec2D ReadSize(const ParseFuncParams& params);
		static int ReadInt(const ParseFuncParams& params);
		static std::string ReadString(const ParseFuncParams& params);
		static char ReadChar(const ParseFuncParams& params);
};

#endif /* __FILECOMMANDLOADER_H__ */
