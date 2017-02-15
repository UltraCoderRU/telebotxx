#ifndef TELEBOTXX_ATTACHMENT_HPP
#define TELEBOTXX_ATTACHMENT_HPP

#include <string>
#include <ctime>
#include <memory>
#include <vector>

namespace telebotxx {

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

	Attachment(Type type);
	Attachment(const Attachment&);
	Attachment(Attachment&&);
	virtual ~Attachment() = 0;

	Type getType() const;

	void swap(Attachment& other) noexcept;

private:
	Type attachmentType_;
};

using AttachmentPtr = std::shared_ptr<Attachment>;

class PhotoSize
{
public:
	PhotoSize();
	PhotoSize(const PhotoSize&);
	PhotoSize(PhotoSize&&);
	~PhotoSize();

	const std::string& getFileId() const;
	void setFileId(const std::string& fileId);

	int getWidth() const;
	void setWidth(int width);

	int getHeight() const;
	void setHeight(int height);

	int getFileSize() const;
	void setFileSize(int fileSize);

	void swap(PhotoSize& other) noexcept;

	const PhotoSize& operator=(PhotoSize other) noexcept;

private:
	std::string fileId_;
	int width_;
	int height_;
	int fileSize_;
};

using PhotoSizePtr = std::shared_ptr<PhotoSize>;

class PhotoSizeArray : public Attachment
{
public:
	PhotoSizeArray();
	PhotoSizeArray(const PhotoSizeArray&);
	PhotoSizeArray(PhotoSizeArray&&);
	~PhotoSizeArray();

	const std::vector<PhotoSize>& getArray() const;
	void setArray(const std::vector<PhotoSize>& array);

	void swap(PhotoSizeArray& other) noexcept;

	const PhotoSizeArray& operator=(PhotoSizeArray other) noexcept;

private:
	std::vector<PhotoSize> array_;
};

using PhotoSizeArrayPtr = std::shared_ptr<PhotoSizeArray>;

class Audio : public Attachment
{
public:
	Audio();
	Audio(const Audio&);
	Audio(Audio&&);
	~Audio();

	const std::string& getFileId() const;
	void setFileId(const std::string& fileId);

	int getDuration() const;
	void setDuration(int duration);

	const std::string& getPerformer() const;
	void setPerformer(const std::string& performer);

	const std::string& getTitle() const;
	void setTitle(const std::string& title);

	const std::string& getMimeType() const;
	void setMimeType(const std::string& mimeType);

	int getFileSize() const;
	void setFileSize(int fileSize);

	void swap(Audio& other) noexcept;

	const Audio& operator=(Audio other) noexcept;

private:
	std::string fileId_;
	int duration_;
	std::string performer_;
	std::string title_;
	std::string mimeType_;
	int fileSize_;
};

class Document : public Attachment
{
public:
	Document();
	Document(const Document&);
	Document(Document&&);
	~Document();

	const std::string& getFileId() const;
	void setFileId(const std::string& fileId);

	const PhotoSizePtr getThumb() const;
	void setThumb(const PhotoSizePtr& thumb);

	const std::string& getFileName() const;
	void setFileName(const std::string& fileName);

	const std::string& getMimeType() const;
	void setMimeType(const std::string& mimeType);

	int getFileSize() const;
	void setFileSize(int fileSize);

	void swap(Document& other) noexcept;

	const Document& operator=(Document other) noexcept;

private:
	std::string fileId_;
	PhotoSizePtr thumb_;
	std::string fileName_;
	std::string mimeType_;
	int fileSize_;
};

class Sticker : public Attachment
{
public:
	Sticker();
	Sticker(const Sticker&);
	Sticker(Sticker&&);
	~Sticker();

	const std::string& getFileId() const;
	void setFileId(const std::string& fileId);

	int getWidth() const;
	void setWidth(int width);

	int getHeight() const;
	void setHeight(int height);

	const PhotoSizePtr getThumb() const;
	void setThumb(const PhotoSizePtr& thumb);

	const std::string& getEmoji() const;
	void setEmoji(const std::string& emoji);

	int getFileSize() const;
	void setFileSize(int fileSize);

	void swap(Sticker& other) noexcept;

	const Sticker& operator=(Sticker other) noexcept;

private:
	std::string fileId_;
	int width_;
	int height_;
	PhotoSizePtr thumb_;
	std::string emoji_;
	int fileSize_;
};

void swap(PhotoSize& lhs, PhotoSize& rhs);
void swap(PhotoSizeArray& lhs, PhotoSizeArray& rhs);
void swap(Audio& lhs, Audio& rhs);
void swap(Document& lhs, Document& rhs);
void swap(Sticker& lhs, Sticker& rhs);

}

#endif // TELEBOTXX_ATTACHMENT_HPP
