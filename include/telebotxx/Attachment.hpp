#ifndef TELEBOTXX_ATTACHMENT_HPP
#define TELEBOTXX_ATTACHMENT_HPP

#include <string>
#include <vector>
#include <memory>
#include <variant>
#include <optional>

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

	const std::optional<int>& getFileSize() const;
	void setFileSize(std::optional<int> fileSize);

private:
	std::string fileId_;
	int width_;
	int height_;
	std::optional<int> fileSize_;
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

	const std::optional<std::string>& getPerformer() const;
	void setPerformer(std::optional<std::string> performer);

	const std::optional<std::string>& getTitle() const;
	void setTitle(std::optional<std::string> title);

	const std::optional<std::string>& getMimeType() const;
	void setMimeType(std::optional<std::string> mimeType);

	const std::optional<int>& getFileSize() const;
	void setFileSize(std::optional<int> fileSize);

private:
	std::string fileId_;
	int duration_;
	std::optional<std::string> performer_;
	std::optional<std::string> title_;
	std::optional<std::string> mimeType_;
	std::optional<int> fileSize_;
};

class Document
{
public:
	Document();

	const std::string& getFileId() const;
	void setFileId(std::string fileId);

	const std::optional<PhotoSize>& getThumb() const;
	void setThumb(std::optional<PhotoSize> thumb);

	const std::optional<std::string>& getFileName() const;
	void setFileName(std::optional<std::string> fileName);

	const std::optional<std::string>& getMimeType() const;
	void setMimeType(std::optional<std::string> mimeType);

	const std::optional<int>& getFileSize() const;
	void setFileSize(std::optional<int> fileSize);

private:
	std::string fileId_;
	std::optional<PhotoSize> thumb_;
	std::optional<std::string> fileName_;
	std::optional<std::string> mimeType_;
	std::optional<int> fileSize_;
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

	const std::optional<PhotoSize>& getThumb() const;
	void setThumb(std::optional<PhotoSize> thumb);

	const std::optional<std::string>& getEmoji() const;
	void setEmoji(std::optional<std::string> emoji);

	const std::optional<int>& getFileSize() const;
	void setFileSize(std::optional<int> fileSize);

private:
	std::string fileId_;
	int width_;
	int height_;
	std::optional<PhotoSize> thumb_;
	std::optional<std::string> emoji_;
	std::optional<int> fileSize_;
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
	std::variant<PhotoSizeArray, Audio, Document, Sticker> value_;
};

}

#endif // TELEBOTXX_ATTACHMENT_HPP
