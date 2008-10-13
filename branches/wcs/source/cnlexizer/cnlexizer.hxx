#ifndef CNLEXIZER_HXX
#define CNLEXIZER_HXX

#include <stdexcept>
#include <cstring>
#include <vector>
#include <map>

#include "lexicon_factory.hxx"
#include "config_factory.hxx"
#include "processor.hxx"
#include "lex_token.hxx"

class CNLexizer {
private:

public:
	size_t process(char *t, const char *s);
	CNLexizer(const char *file);
	~CNLexizer()
	{
		std::map<std::string, Processor *>::iterator iter;

		for (iter = _processors.begin(); iter != _processors.end(); iter++)
			delete iter->second;

		delete _config;
	}

protected:
	IConfig *_config;
	static const char _stream_name_prefix[];
	std::vector<std::string> _streamline;
	std::vector<LexToken *> _lex_token[2];
	std::vector<LexToken *> *_in, *_out, *_swap;
	std::map<std::string, Processor *> _processors;
	std::wstring _result;

	void _process(const wchar_t *s);

	void _dump_process_queue()
	{
		size_t i, length = _in->size();
		LexToken *token;

		for (i = 0; i < length; i++) {
			token = (*_in)[i];
			std::wcout << "token = " << token->get_token() 
				<< ", attr = " << (int)token->get_attr() << std::endl;
		}
	}
};

#endif