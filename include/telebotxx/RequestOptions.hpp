#ifndef TELEBOTXX_REQUEST_OPTIONS_HPP
#define TELEBOTXX_REQUEST_OPTIONS_HPP

#include <string>

namespace telebotxx
{
	class ChatId
	{
	public:
		ChatId(int);
		ChatId(const std::string&);
		ChatId(const ChatId&);
		ChatId(ChatId&&);
		~ChatId();

		enum class Type	{ Id, Username };
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
		explicit Photo(const File&);
		explicit Photo(const Url&);
		Photo(const Photo&);
		Photo(Photo&&);
		~Photo();

		enum class Type { File, Url, Id };
		Type getType() const;

	private:
		Type type_;
		union
		{
			int id_;
			File file_;
			Url url_;
		};
	};
}

#endif // TELEBOTXX_REQUEST_OPTIONS_HPP
