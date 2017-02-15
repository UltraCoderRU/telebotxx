#include <telebotxx/Attachment.hpp>

namespace telebotxx {

Attachment::Attachment(Type type)
	: attachmentType_(type)
{
}

Attachment::Attachment(const Attachment&) = default;

Attachment::Attachment(Attachment&&) = default;

Attachment::~Attachment() = default;

Attachment::Type Attachment::getType() const
{
	return attachmentType_;
}

void Attachment::swap(Attachment& other) noexcept
{
	std::swap(attachmentType_, other.attachmentType_);
}

////////////////////////////////////////////////////////////////

PhotoSize::PhotoSize()
	: width_(-1),
	  height_(-1),
	  fileSize_(-1)
{
}

PhotoSize::PhotoSize(const PhotoSize&) = default;

PhotoSize::PhotoSize(PhotoSize&&) = default;

PhotoSize::~PhotoSize() = default;

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

int PhotoSize::getFileSize() const
{
	return fileSize_;
}

void PhotoSize::setFileSize(int fileSize)
{
	fileSize_ = fileSize;
}

void PhotoSize::swap(PhotoSize& other) noexcept
{
	using std::swap;
	swap(fileId_, other.fileId_);
	swap(width_, other.width_);
	swap(height_, other.height_);
	swap(fileSize_, other.fileSize_);
}

const PhotoSize& PhotoSize::operator=(PhotoSize other) noexcept
{
	swap(other);
	return *this;
}

////////////////////////////////////////////////////////////////

PhotoSizeArray::PhotoSizeArray()
	: Attachment(Attachment::Type::PhotoSizeArray)
{
}

PhotoSizeArray::PhotoSizeArray(const PhotoSizeArray&) = default;

PhotoSizeArray::PhotoSizeArray(PhotoSizeArray&&) = default;

PhotoSizeArray::~PhotoSizeArray() = default;

const std::vector<PhotoSize>& PhotoSizeArray::getArray() const
{
	return array_;
}

void PhotoSizeArray::setArray(const std::vector<PhotoSize>& array)
{
	array_ = array;
}

void PhotoSizeArray::swap(PhotoSizeArray& other) noexcept
{
	using std::swap;
	swap(array_, other.array_);
}

const PhotoSizeArray& PhotoSizeArray::operator=(PhotoSizeArray other) noexcept
{
	swap(other);
	return *this;
}

////////////////////////////////////////////////////////////////

Audio::Audio()
	: Attachment(Type::Audio),
	  duration_(-1),
	  fileSize_(-1)
{
}

Audio::Audio(const Audio&) = default;

Audio::Audio(Audio&&) = default;

Audio::~Audio() = default;

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

const std::string& Audio::getPerformer() const
{
	return performer_;
}

void Audio::setPerformer(const std::string& performer)
{
	performer_ = performer;
}

const std::string& Audio::getTitle() const
{
	return title_;
}

void Audio::setTitle(const std::string& title)
{
	title_ = title;
}

const std::string& Audio::getMimeType() const
{
	return mimeType_;
}

void Audio::setMimeType(const std::string& mimeType)
{
	mimeType_ = mimeType;
}

int Audio::getFileSize() const
{
	return fileSize_;
}

void Audio::setFileSize(int fileSize)
{
	fileSize_ = fileSize;
}

void Audio::swap(Audio& other) noexcept
{
	Attachment::swap(other);
	using std::swap;
	swap(fileId_, other.fileId_);
	swap(duration_, other.duration_);
	swap(performer_, other.performer_);
	swap(title_, other.title_);
	swap(mimeType_, other.mimeType_);
	swap(fileSize_, other.fileSize_);
}

const Audio& Audio::operator=(Audio other) noexcept
{
	swap(other);
	return *this;
}

////////////////////////////////////////////////////////////////

Document::Document()
	: Attachment(Type::Document),
	  fileSize_(-1)
{
}

Document::Document(const Document&) = default;

Document::Document(Document&&) = default;

Document::~Document() = default;

const std::string& Document::getFileId() const
{
	return fileId_;
}

void Document::setFileId(const std::string& fileId)
{
	fileId_ = fileId;
}

const PhotoSizePtr Document::getThumb() const
{
	return thumb_;
}

void Document::setThumb(const PhotoSizePtr& thumb)
{
	thumb_ = thumb;
}

const std::string& Document::getFileName() const
{
	return fileName_;
}

void Document::setFileName(const std::string& fileName)
{
	fileName_ = fileName;
}

const std::string& Document::getMimeType() const
{
	return mimeType_;
}

void Document::setMimeType(const std::string& mimeType)
{
	mimeType_ = mimeType;
}

int Document::getFileSize() const
{
	return fileSize_;
}

void Document::setFileSize(int fileSize)
{
	fileSize_ = fileSize;
}

void Document::swap(Document& other) noexcept
{
	Attachment::swap(other);
	using std::swap;
	swap(fileId_, other.fileId_);
	swap(thumb_, other.thumb_);
	swap(fileName_, other.fileName_);
	swap(mimeType_, other.mimeType_);
	swap(fileSize_, other.fileSize_);
}

const Document& Document::operator=(Document other) noexcept
{
	swap(other);
	return *this;
}

////////////////////////////////////////////////////////////////

Sticker::Sticker()
	: Attachment(Type::Sticker),
	  fileSize_(-1)
{
}

Sticker::Sticker(const Sticker&) = default;

Sticker::Sticker(Sticker&&) = default;

Sticker::~Sticker() = default;

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

const PhotoSizePtr Sticker::getThumb() const
{
	return thumb_;
}

void Sticker::setThumb(const PhotoSizePtr& thumb)
{
	thumb_ = thumb;
}

const std::string& Sticker::getEmoji() const
{
	return emoji_;
}

void Sticker::setEmoji(const std::string& emoji)
{
	emoji_ = emoji;
}

int Sticker::getFileSize() const
{
	return fileSize_;
}

void Sticker::setFileSize(int fileSize)
{
	fileSize_ = fileSize;
}

void Sticker::swap(Sticker& other) noexcept
{
	Attachment::swap(other);
	using std::swap;
	swap(fileId_, other.fileId_);
	swap(width_, other.width_);
	swap(height_, other.height_);
	swap(thumb_, other.thumb_);
	swap(emoji_, other.emoji_);
	swap(fileSize_, other.fileSize_);
}

const Sticker& Sticker::operator=(Sticker other) noexcept
{
	swap(other);
	return *this;
}

////////////////////////////////////////////////////////////////

void swap(PhotoSize& lhs, PhotoSize& rhs)
{
	lhs.swap(rhs);
}

void swap(PhotoSizeArray& lhs, PhotoSizeArray& rhs)
{
	lhs.swap(rhs);
}

void swap(Audio& lhs, Audio& rhs)
{
	lhs.swap(rhs);
}

void swap(Document& lhs, Document& rhs)
{
	lhs.swap(rhs);
}

void swap(Sticker& lhs, Sticker& rhs)
{
	lhs.swap(rhs);
}

}
