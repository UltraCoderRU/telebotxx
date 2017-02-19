#ifndef TELEBOTXX_ATTACHMENT_HPP
#define TELEBOTXX_ATTACHMENT_HPP

#include "Optional.hpp"

#include <string>
#include <vector>
#include <memory>
#include <boost/variant/variant.hpp>

namespace telebotxx {

class PhotoSize
{
public:
	PhotoSize();

	const std::string& getFileId() const;
	void setFileId(const std::string& fileId);

	int getWidth() const;
	void setWidth(int width);

	int getHeight() const;
	void setHeight(int height);

	const optional<int>& getFileSize() const;
	void setFileSize(optional<int> fileSize);

private:
	std::string fileId_;
	int width_;
	int height_;
	optional<int> fileSize_;
};

using PhotoSizeArray = std::vector<PhotoSize>;

class Audio
{
public:
	Audio();

	const std::string& getFileId() const;
	void setFileId(const std::string& fileId);

	int getDuration() const;
	void setDuration(int duration);

	const optional<std::string>& getPerformer() const;
	void setPerformer(optional<std::string> performer);

	const optional<std::string>& getTitle() const;
	void setTitle(optional<std::string> title);

	const optional<std::string>& getMimeType() const;
	void setMimeType(optional<std::string> mimeType);

	const optional<int>& getFileSize() const;
	void setFileSize(optional<int> fileSize);

private:
	std::string fileId_;
	int duration_;
	optional<std::string> performer_;
	optional<std::string> title_;
	optional<std::string> mimeType_;
	optional<int> fileSize_;
};

class Document
{
public:
	Document();

	const std::string& getFileId() const;
	void setFileId(std::string fileId);

	const optional<PhotoSize>& getThumb() const;
	void setThumb(optional<PhotoSize> thumb);

	const optional<std::string>& getFileName() const;
	void setFileName(optional<std::string> fileName);

	const optional<std::string>& getMimeType() const;
	void setMimeType(optional<std::string> mimeType);

	const optional<int>& getFileSize() const;
	void setFileSize(optional<int> fileSize);

private:
	std::string fileId_;
	optional<PhotoSize> thumb_;
	optional<std::string> fileName_;
	optional<std::string> mimeType_;
	optional<int> fileSize_;
};

class Sticker
{
public:
	Sticker();

	const std::string& getFileId() const;
	void setFileId(const std::string& fileId);

	int getWidth() const;
	void setWidth(int width);

	int getHeight() const;
	void setHeight(int height);

	const optional<PhotoSize>& getThumb() const;
	void setThumb(optional<PhotoSize> thumb);

	const optional<std::string>& getEmoji() const;
	void setEmoji(optional<std::string> emoji);

	const optional<int>& getFileSize() const;
	void setFileSize(optional<int> fileSize);

private:
	std::string fileId_;
	int width_;
	int height_;
	optional<PhotoSize> thumb_;
	optional<std::string> emoji_;
	optional<int> fileSize_;
};

class Attachment
{
public:
	enum class Type
	{
		Audio,
		Document,
		Game,
		PhotoSizeArray,
		Sticker,
		Video,
		Voice,
		Contact,
		Location,
		Venue
	};

	Attachment(PhotoSizeArray);
	Attachment(Audio);
	Attachment(Document);
	Attachment(Sticker);

	Type getType() const;

	const PhotoSizeArray& getPhotoSizeArray() const;
	const Audio& getAudio() const;
	const Document& getDocument() const;
	const Sticker& getSticker() const;

private:
	Type type_;
	boost::variant<PhotoSizeArray, Audio, Document, Sticker> value_;
};

}

#endif // TELEBOTXX_ATTACHMENT_HPP
