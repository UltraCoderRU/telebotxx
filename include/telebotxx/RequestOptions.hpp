#ifndef TELEBOTXX_REQUEST_OPTIONS_HPP
#define TELEBOTXX_REQUEST_OPTIONS_HPP

#include <string>
#include <vector>

namespace telebotxx {

class ChatId
{
public:
	ChatId(int);
	ChatId(const std::string&);
	ChatId(const ChatId&);
	ChatId(ChatId&&);
	~ChatId();

	enum class Type { Id, Username };
	Type getType() const;
	const int getId() const;
	const std::string getUsername() const;
private:
	Type type_;
	union
	{
		int id_;
		std::string username_;
	};
};

using Text = std::string;
using Caption = std::string;

enum class ParseMode
{
	Plain,
	Markdown,
	Html
};

class DisableWebPagePreview
{
public:
	DisableWebPagePreview(bool disabled = true);
	bool value() const;
private:
	bool disable_;
};

class DisableNotification
{
public:
	DisableNotification(bool disabled = true);
	bool value() const;
private:
	bool disable_;
};

class ReplyTo
{
public:
	explicit ReplyTo(int id);
	int value() const;
private:
	int id_;
};

class Buffer
{
public:
	Buffer(const char *buffer, std::size_t size, const std::string& filename);
	explicit Buffer(const std::vector<char>& data, const std::string& filename);
	const char *data() const;
	const std::size_t size() const;
	const std::string filename() const;
private:
	const char *data_;
	std::size_t size_;
	std::string filename_;
};

class File
{
public:
	explicit File(const std::string& filename);
	const std::string& getFilename() const;
private:
	std::string filename_;
};

class Url
{
public:
	explicit Url(const std::string& url);
	const std::string& getUrl() const;
private:
	std::string url_;
};

class Photo
{
public:
	explicit Photo(int id);
	explicit Photo(const Buffer&);
	explicit Photo(const File&);
	explicit Photo(const Url&);
	Photo(const Photo&);
	Photo(Photo&&);
	~Photo();

	enum class Type	{ Id, Buffer, File, Url };
	Type getType() const;

	int getId() const;
	const Buffer& getBuffer() const;
	const File& getFile() const;
	const Url& getUrl() const;

private:
	Type type_;
	union
	{
		int id_;
		Buffer buffer_;
		File file_;
		Url url_;
	};
};

}

#endif // TELEBOTXX_REQUEST_OPTIONS_HPP
