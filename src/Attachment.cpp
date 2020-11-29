#include <telebotxx/Attachment.hpp>

namespace telebotxx {

PhotoSize::PhotoSize()
	: width_(-1),
	  height_(-1),
	  fileSize_(-1)
{
}

const std::string& PhotoSize::getFileId() const
{
	return fileId_;
}

void PhotoSize::setFileId(const std::string& fileId)
{
	fileId_ = fileId;
}

int PhotoSize::getWidth() const
{
	return width_;
}

void PhotoSize::setWidth(int width)
{
	width_ = width;
}

int PhotoSize::getHeight() const
{
	return height_;
}

void PhotoSize::setHeight(int height)
{
	height_ = height;
}

const std::optional<int>& PhotoSize::getFileSize() const
{
	return fileSize_;
}

void PhotoSize::setFileSize(std::optional<int> fileSize)
{
	fileSize_ = fileSize;
}

////////////////////////////////////////////////////////////////

Audio::Audio()
	: duration_(-1),
	  fileSize_(-1)
{
}

const std::string& Audio::getFileId() const
{
	return fileId_;
}

void Audio::setFileId(const std::string& fileId)
{
	fileId_ = fileId;
}

int Audio::getDuration() const
{
	return duration_;
}

void Audio::setDuration(int duration)
{
	duration_ = duration;
}

const std::optional<std::string>& Audio::getPerformer() const
{
	return performer_;
}

void Audio::setPerformer(std::optional<std::string> performer)
{
	performer_ = std::move(performer);
}

const std::optional<std::string>& Audio::getTitle() const
{
	return title_;
}

void Audio::setTitle(std::optional<std::string> title)
{
	title_ = title;
}

const std::optional<std::string>& Audio::getMimeType() const
{
	return mimeType_;
}

void Audio::setMimeType(std::optional<std::string> mimeType)
{
	mimeType_ = mimeType;
}

const std::optional<int>& Audio::getFileSize() const
{
	return fileSize_;
}

void Audio::setFileSize(std::optional<int> fileSize)
{
	fileSize_ = fileSize;
}

////////////////////////////////////////////////////////////////

Document::Document()
	: fileSize_(-1)
{
}

const std::string& Document::getFileId() const
{
	return fileId_;
}

void Document::setFileId(std::string fileId)
{
	fileId_ = fileId;
}

const std::optional<PhotoSize>& Document::getThumb() const
{
	return thumb_;
}

void Document::setThumb(std::optional<PhotoSize> thumb)
{
	thumb_ = thumb;
}

const std::optional<std::string>& Document::getFileName() const
{
	return fileName_;
}

void Document::setFileName(std::optional<std::string> fileName)
{
	fileName_ = fileName;
}

const std::optional<std::string>& Document::getMimeType() const
{
	return mimeType_;
}

void Document::setMimeType(std::optional<std::string> mimeType)
{
	mimeType_ = mimeType;
}

const std::optional<int>& Document::getFileSize() const
{
	return fileSize_;
}

void Document::setFileSize(std::optional<int> fileSize)
{
	fileSize_ = fileSize;
}

////////////////////////////////////////////////////////////////

Sticker::Sticker()
	: fileSize_(-1)
{
}

const std::string& Sticker::getFileId() const
{
	return fileId_;
}

void Sticker::setFileId(const std::string& fileId)
{
	fileId_ = fileId;
}

int Sticker::getWidth() const
{
	return width_;
}

void Sticker::setWidth(int width)
{
	width_ = width;
}

int Sticker::getHeight() const
{
	return height_;
}

void Sticker::setHeight(int height)
{
	height_ = height;
}

const std::optional<PhotoSize>& Sticker::getThumb() const
{
	return thumb_;
}

void Sticker::setThumb(std::optional<PhotoSize> thumb)
{
	thumb_ = thumb;
}

const std::optional<std::string>& Sticker::getEmoji() const
{
	return emoji_;
}

void Sticker::setEmoji(std::optional<std::string> emoji)
{
	emoji_ = emoji;
}

const std::optional<int>& Sticker::getFileSize() const
{
	return fileSize_;
}

void Sticker::setFileSize(std::optional<int> fileSize)
{
	fileSize_ = fileSize;
}

////////////////////////////////////////////////////////////////

Attachment::Attachment(PhotoSizeArray photos)
	: type_(Type::PhotoSizeArray), value_(std::move(photos))
{
}

Attachment::Attachment(Audio audio)
	: type_(Type::Audio), value_(std::move(audio))
{
}

Attachment::Attachment(Document document)
	: type_(Type::Document), value_(std::move(document))
{
}

Attachment::Attachment(Sticker sticker)
	: type_(Type::Sticker), value_(std::move(sticker))
{
}

Attachment::Type Attachment::getType() const
{
	return type_;
}

const PhotoSizeArray& Attachment::getPhotoSizeArray() const
{
	return std::get<PhotoSizeArray>(value_);
}

const Audio& Attachment::getAudio() const
{
	return std::get<Audio>(value_);;
}

const Document& Attachment::getDocument() const
{
	return std::get<Document>(value_);
}

const Sticker& Attachment::getSticker() const
{
	return std::get<Sticker>(value_);;
}

}
