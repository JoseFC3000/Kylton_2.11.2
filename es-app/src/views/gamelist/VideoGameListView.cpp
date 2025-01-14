#include "views/gamelist/VideoGameListView.h"

#include "animations/LambdaAnimation.h"
#ifdef _OMX_
#include "components/VideoPlayerComponent.h"
#endif
#include "components/VideoVlcComponent.h"
#include "utils/FileSystemUtil.h"
#include "views/ViewController.h"
#ifdef _OMX_
#include "Settings.h"
#endif

VideoGameListView::VideoGameListView(Window* window, FileData* root) :
	BasicGameListView(window, root),
	mDescContainer(window, DESCRIPTION_SCROLL_DELAY), mDescription(window),
	mThumbnail(window),
	mMarquee(window),
	mScreenshot(window),
	mImage(window),
	mImage1(window),
	mImage2(window),
	mVideo(nullptr),
	mVideoPlaying(false),

	mLblRating(window), mLblReleaseDate(window), mLblDeveloper(window), mLblPublisher(window), mLblFullSystem(window), mLblRegion(window), mLblControls(window),
	mLblFormat(window), mLblGenre(window), mLblPlayers(window), mLblComment(window), mLblFirstRelease(window), mLblFirstReleaseShow(window), mLblLastPlayed(window), mLblPlayCount(window),

	mRating(window), mReleaseDate(window), mDeveloper(window), mPublisher(window), mFullSystem(window), mRegion(window), mControls(window), mFormat(window),
	mGenre(window), mPlayers(window), mComment(window), mFirstRelease(window), mFirstReleaseShow(window), mLastPlayed(window), mPlayCount(window),
	mName(window)
{
	const float padding = 0.01f;

	// Create the correct type of video window
#ifdef _OMX_
	Utils::FileSystem::removeFile(getTitlePath());
	if (Settings::getInstance()->getBool("VideoOmxPlayer"))
		mVideo = new VideoPlayerComponent(window, "");
	else
		mVideo = new VideoVlcComponent(window, getTitlePath());
#else
	mVideo = new VideoVlcComponent(window, getTitlePath());
#endif

	mList.setPosition(mSize.x() * (0.50f + padding), mList.getPosition().y());
	mList.setSize(mSize.x() * (0.50f - padding), mList.getSize().y());
	mList.setAlignment(TextListComponent<FileData*>::ALIGN_LEFT);
	mList.setCursorChangedCallback([&](const CursorState& /*state*/) { updateInfoPanel(); });

	// Image
	// Default to off the screen
	mImage.setOrigin(0.5f, 0.5f);
	mImage.setPosition(2.0f, 2.0f);
	mImage.setMaxSize(mSize.x(), mSize.y());
	mImage.setDefaultZIndex(30);
	mImage.setVisible(false);
	addChild(&mImage);
	
	// Image 1
	// Default to off the screen
	mImage1.setOrigin(0.5f, 0.5f);
	mImage1.setPosition(2.0f, 2.0f);
	mImage1.setMaxSize(mSize.x(), mSize.y());
	mImage1.setDefaultZIndex(30);
	mImage1.setVisible(false);
	addChild(&mImage1);
		
	// Image 2
	// Default to off the screen
	mImage2.setOrigin(0.5f, 0.5f);
	mImage2.setPosition(2.0f, 2.0f);
	mImage2.setMaxSize(mSize.x(), mSize.y());
	mImage2.setDefaultZIndex(30);
	mImage2.setVisible(false);
	addChild(&mImage2);

	// Video
	mVideo->setOrigin(0.5f, 0.5f);
	mVideo->setPosition(mSize.x() * 0.25f, mSize.y() * 0.4f);
	mVideo->setSize(mSize.x() * (0.5f - 2*padding), mSize.y() * 0.4f);
	mVideo->setDefaultZIndex(30);
	addChild(mVideo);

	// Thumbnail
	// Default to off the screen
	mThumbnail.setOrigin(0.5f, 0.5f);
	mThumbnail.setPosition(2.0f, 2.0f);
	mThumbnail.setMaxSize(mSize.x(), mSize.y());
	mThumbnail.setDefaultZIndex(35);
	mThumbnail.setVisible(false);
	addChild(&mThumbnail);

	// Marquee
	// Default to off the screen
	mMarquee.setOrigin(0.5f, 0.5f);
	mMarquee.setPosition(2.0f, 2.0f);
	mMarquee.setMaxSize(mSize.x(), mSize.y());
	mMarquee.setDefaultZIndex(35);
	mMarquee.setVisible(false);
	addChild(&mMarquee);
		
	// Screenshot
	// Default to off the screen
	mScreenshot.setOrigin(0.5f, 0.5f);
	mScreenshot.setPosition(2.0f, 2.0f);
	mScreenshot.setMaxSize(mSize.x(), mSize.y());
	mScreenshot.setDefaultZIndex(35);
	mScreenshot.setVisible(false);
	addChild(&mScreenshot);

	// metadata labels + values
	mLblRating.setText("Rating: ");
	addChild(&mLblRating);
	addChild(&mRating);
	mLblReleaseDate.setText("Release Date: ");
	addChild(&mLblReleaseDate);
	addChild(&mReleaseDate);
	mLblDeveloper.setText("Developer: ");
	addChild(&mLblDeveloper);
	addChild(&mDeveloper);
	mLblPublisher.setText("Publisher: ");
	addChild(&mLblPublisher);
	addChild(&mPublisher);
	mLblFullSystem.setText("System: ");
	addChild(&mLblFullSystem);
	addChild(&mFullSystem);
	mLblRegion.setText("Region: ");
	addChild(&mLblRegion);
	addChild(&mRegion);
	mLblControls.setText("Controls: ");
	addChild(&mLblControls);
	addChild(&mControls);
	mLblFormat.setText("Format: ");
	addChild(&mLblFormat);
	addChild(&mFormat);
	mLblGenre.setText("Genre: ");
	addChild(&mLblGenre);
	addChild(&mGenre);
	mLblPlayers.setText("Players: ");
	addChild(&mLblPlayers);
	addChild(&mPlayers);
	mLblComment.setText("Comment: ");
	addChild(&mLblComment);
	addChild(&mComment);
	mLblFirstRelease.setText("First Release Date: ");
	addChild(&mLblFirstRelease);
	addChild(&mFirstRelease);
	mLblFirstReleaseShow.setText("First Release Date Show: ");
	addChild(&mLblFirstReleaseShow);
	addChild(&mFirstReleaseShow);
	mLblLastPlayed.setText("Last played: ");
	addChild(&mLblLastPlayed);
	mLastPlayed.setDisplayRelative(true);
	addChild(&mLastPlayed);
	mLblPlayCount.setText("Times played: ");
	addChild(&mLblPlayCount);
	addChild(&mPlayCount);

	mName.setPosition(mSize.x(), mSize.y());
	mName.setDefaultZIndex(40);
	mName.setColor(0xAAAAAAFF);
	mName.setFont(Font::get(FONT_SIZE_MEDIUM));
	mName.setHorizontalAlignment(ALIGN_CENTER);
	addChild(&mName);

	mDescContainer.setPosition(mSize.x() * padding, mSize.y() * 0.65f);
	mDescContainer.setSize(mSize.x() * (0.50f - 2*padding), mSize.y() - mDescContainer.getPosition().y());
	mDescContainer.setAutoScroll(true);
	mDescContainer.setDefaultZIndex(40);
	addChild(&mDescContainer);

	mDescription.setFont(Font::get(FONT_SIZE_SMALL));
	mDescription.setSize(mDescContainer.getSize().x(), 0);
	mDescContainer.addChild(&mDescription);

	initMDLabels();
	initMDValues();
}

VideoGameListView::~VideoGameListView()
{
	delete mVideo;
}

void VideoGameListView::onThemeChanged(const std::shared_ptr<ThemeData>& theme)
{
	BasicGameListView::onThemeChanged(theme);

	using namespace ThemeFlags;
	mThumbnail.applyTheme(theme, getName(), "md_thumbnail", POSITION | ThemeFlags::SIZE | Z_INDEX | ROTATION | VISIBLE);
	mMarquee.applyTheme(theme, getName(), "md_marquee", POSITION | ThemeFlags::SIZE | Z_INDEX | ROTATION | VISIBLE);
	mScreenshot.applyTheme(theme, getName(), "md_screenshot", POSITION | ThemeFlags::SIZE | Z_INDEX | ROTATION | VISIBLE);
	mImage.applyTheme(theme, getName(), "md_image", POSITION | ThemeFlags::SIZE | Z_INDEX | ROTATION | VISIBLE);
	mImage1.applyTheme(theme, getName(), "md_image1", POSITION | ThemeFlags::SIZE | Z_INDEX | ROTATION | VISIBLE);
	mImage2.applyTheme(theme, getName(), "md_image2", POSITION | ThemeFlags::SIZE | Z_INDEX | ROTATION | VISIBLE);
	mVideo->applyTheme(theme, getName(), "md_video", POSITION | ThemeFlags::SIZE | ThemeFlags::DELAY | Z_INDEX | ROTATION | VISIBLE);
	mName.applyTheme(theme, getName(), "md_name", ALL);

	initMDLabels();
	std::vector<TextComponent*> labels = getMDLabels();
	assert(labels.size() == 15);
	const char* lblElements[15] = {
		"md_lbl_rating", "md_lbl_releasedate", "md_lbl_developer", "md_lbl_publisher", "md_lbl_fullsystem", "md_lbl_region", "md_lbl_controls",
		"md_lbl_format", "md_lbl_genre", "md_lbl_players", "md_lbl_comment", "md_lbl_firstrelease", "md_lbl_firstreleaseshow", "md_lbl_lastplayed", "md_lbl_playcount"
	};

	for(unsigned int i = 0; i < labels.size(); i++)
	{
		labels[i]->applyTheme(theme, getName(), lblElements[i], ALL);
	}


	initMDValues();
	std::vector<GuiComponent*> values = getMDValues();
	assert(values.size() == 15);
	const char* valElements[15] = {
		"md_rating", "md_releasedate", "md_developer", "md_publisher", "md_fullsystem", "md_region", "md_controls",
		"md_format", "md_genre", "md_players", "md_comment", "md_firstrelease", "md_firstreleaseshow", "md_lastplayed", "md_playcount"
	};

	for(unsigned int i = 0; i < values.size(); i++)
	{
		values[i]->applyTheme(theme, getName(), valElements[i], ALL ^ ThemeFlags::TEXT);
	}

	mDescContainer.applyTheme(theme, getName(), "md_description", POSITION | ThemeFlags::SIZE | Z_INDEX | VISIBLE);
	mDescription.setSize(mDescContainer.getSize().x(), 0);
	mDescription.applyTheme(theme, getName(), "md_description", ALL ^ (POSITION | ThemeFlags::SIZE | ThemeFlags::ORIGIN | TEXT | ROTATION));

	sortChildren();
}

void VideoGameListView::initMDLabels()
{
	std::vector<TextComponent*> components = getMDLabels();

	const unsigned int colCount = 2;
	const unsigned int rowCount = (int)(components.size() / 2);

	Vector3f start(mSize.x() * 0.01f, mSize.y() * 0.625f, 0.0f);

	const float colSize = (mSize.x() * 0.48f) / colCount;
	const float rowPadding = 0.01f * mSize.y();

	for(unsigned int i = 0; i < components.size(); i++)
	{
		const unsigned int row = i % rowCount;
		Vector3f pos(0.0f, 0.0f, 0.0f);
		if(row == 0)
		{
			pos = start + Vector3f(colSize * (i / rowCount), 0, 0);
		}else{
			// work from the last component
			GuiComponent* lc = components[i-1];
			pos = lc->getPosition() + Vector3f(0, lc->getSize().y() + rowPadding, 0);
		}

		components[i]->setFont(Font::get(FONT_SIZE_SMALL));
		components[i]->setPosition(pos);
		components[i]->setDefaultZIndex(40);
	}
}

void VideoGameListView::initMDValues()
{
	std::vector<TextComponent*> labels = getMDLabels();
	std::vector<GuiComponent*> values = getMDValues();

	std::shared_ptr<Font> defaultFont = Font::get(FONT_SIZE_SMALL);
	mRating.setSize(defaultFont->getHeight() * 5.0f, (float)defaultFont->getHeight());
	mReleaseDate.setFont(defaultFont);
	mDeveloper.setFont(defaultFont);
	mPublisher.setFont(defaultFont);
	mFullSystem.setFont(defaultFont);
	mRegion.setFont(defaultFont);
	mControls.setFont(defaultFont);
	mFormat.setFont(defaultFont);
	mGenre.setFont(defaultFont);
	mPlayers.setFont(defaultFont);
	mComment.setFont(defaultFont);
	mFirstRelease.setFont(defaultFont);
	mFirstReleaseShow.setFont(defaultFont);
	mLastPlayed.setFont(defaultFont);
	mPlayCount.setFont(defaultFont);

	float bottom = 0.0f;

	const float colSize = (mSize.x() * 0.48f) / 2;
	for(unsigned int i = 0; i < labels.size(); i++)
	{
		const float heightDiff = (labels[i]->getSize().y() - values[i]->getSize().y()) / 2;
		values[i]->setPosition(labels[i]->getPosition() + Vector3f(labels[i]->getSize().x(), heightDiff, 0));
		values[i]->setSize(colSize - labels[i]->getSize().x(), values[i]->getSize().y());
		values[i]->setDefaultZIndex(40);

		float testBot = values[i]->getPosition().y() + values[i]->getSize().y();
		if(testBot > bottom)
			bottom = testBot;
	}

	mDescContainer.setPosition(mDescContainer.getPosition().x(), bottom + mSize.y() * 0.01f);
	mDescContainer.setSize(mDescContainer.getSize().x(), mSize.y() - mDescContainer.getPosition().y());
}



void VideoGameListView::updateInfoPanel()
{
	FileData* file = (mList.size() == 0 || mList.isScrolling()) ? NULL : mList.getSelected();

	bool fadingOut;
	if(file == NULL)
	{
		mVideo->setVideo("");
		mVideo->setImage("");
		mVideoPlaying = false;
		//mMarquee.setImage("");
		//mDescription.setText("");
		fadingOut = true;

	}else{
		if (!mVideo->setVideo(file->getVideoPath()))
		{
			mVideo->setDefaultVideo();
		}
		mVideoPlaying = true;

		mVideo->setImage(file->getThumbnailPath());
		mThumbnail.setImage(file->getThumbnailPath());
		mMarquee.setImage(file->getMarqueePath());
		mScreenshot.setImage(file->getScreenshotPath());
		mImage.setImage(file->getImagePath());
		mImage1.setImage(file->getImage1Path());
		mImage2.setImage(file->getImage2Path());

		mDescription.setText(file->metadata.get("desc"));
		mDescContainer.reset();

		mRating.setValue(file->metadata.get("rating"));
		mReleaseDate.setValue(file->metadata.get("releasedate"));
		mDeveloper.setValue(file->metadata.get("developer"));
		mPublisher.setValue(file->metadata.get("publisher"));
		mFullSystem.setValue(file->metadata.get("fullsystem"));
		mRegion.setValue(file->metadata.get("region"));
		mControls.setValue(file->metadata.get("controls"));
		mFormat.setValue(file->metadata.get("format"));
		mGenre.setValue(file->metadata.get("genre"));
		mPlayers.setValue(file->metadata.get("players"));
		mComment.setValue(file->metadata.get("comment"));
		mFirstRelease.setValue(file->metadata.get("firstrelease"));
		mFirstReleaseShow.setValue(file->metadata.get("firstreleaseshow"));
		mName.setValue(file->metadata.get("name"));

		if(file->getType() == GAME)
		{
			mLastPlayed.setValue(file->metadata.get("lastplayed"));
			mPlayCount.setValue(file->metadata.get("playcount"));
		}

		fadingOut = false;
	}

	std::vector<GuiComponent*> comps = getMDValues();
	comps.push_back(&mThumbnail);
	comps.push_back(&mMarquee);
	comps.push_back(&mScreenshot);
	comps.push_back(mVideo);
	comps.push_back(&mDescription);
	comps.push_back(&mImage);
	comps.push_back(&mImage1);
	comps.push_back(&mImage2);
	comps.push_back(&mName);
	std::vector<TextComponent*> labels = getMDLabels();
	comps.insert(comps.cend(), labels.cbegin(), labels.cend());

	for(auto it = comps.cbegin(); it != comps.cend(); it++)
	{
		GuiComponent* comp = *it;
		// an animation is playing
		//   then animate if reverse != fadingOut
		// an animation is not playing
		//   then animate if opacity != our target opacity
		if((comp->isAnimationPlaying(0) && comp->isAnimationReversed(0) != fadingOut) ||
			(!comp->isAnimationPlaying(0) && comp->getOpacity() != (fadingOut ? 0 : 255)))
		{
			auto func = [comp](float t)
			{
				comp->setOpacity((unsigned char)(Math::lerp(0.0f, 1.0f, t)*255));
			};
			comp->setAnimation(new LambdaAnimation(func, 150), 0, nullptr, fadingOut);
		}
	}
}

void VideoGameListView::launch(FileData* game)
{
	float screenWidth = (float) Renderer::getScreenWidth();
	float screenHeight = (float) Renderer::getScreenHeight();

	Vector3f target(screenWidth / 2.0f, screenHeight / 2.0f, 0);

	if(mMarquee.hasImage() &&
		(mMarquee.getPosition().x() < screenWidth && mMarquee.getPosition().x() > 0.0f &&
		 mMarquee.getPosition().y() < screenHeight && mMarquee.getPosition().y() > 0.0f))
	{
		target = Vector3f(mMarquee.getCenter().x(), mMarquee.getCenter().y(), 0);
	}
	else if(mScreenshot.hasImage() &&
		(mScreenshot.getPosition().x() < screenWidth && mScreenshot.getPosition().x() > 0.0f &&
		 mScreenshot.getPosition().y() < screenHeight && mScreenshot.getPosition().y() > 0.0f))
	{
		target = Vector3f(mScreenshot.getCenter().x(), mScreenshot.getCenter().y(), 0);
	}
	else if(mThumbnail.hasImage() &&
		(mThumbnail.getPosition().x() < screenWidth && mThumbnail.getPosition().x() > 2.0f &&
		 mThumbnail.getPosition().y() < screenHeight && mThumbnail.getPosition().y() > 2.0f))
	{
		target = Vector3f(mThumbnail.getCenter().x(), mThumbnail.getCenter().y(), 0);
	}
	else if(mImage.hasImage() &&
		(mImage.getPosition().x() < screenWidth && mImage.getPosition().x() > 2.0f &&
		 mImage.getPosition().y() < screenHeight && mImage.getPosition().y() > 2.0f))
	{
		target = Vector3f(mImage.getCenter().x(), mImage.getCenter().y(), 0);
	}
	else if(mImage1.hasImage() &&
		(mImage1.getPosition().x() < screenWidth && mImage1.getPosition().x() > 2.0f &&
		 mImage1.getPosition().y() < screenHeight && mImage1.getPosition().y() > 2.0f))
	{
		target = Vector3f(mImage1.getCenter().x(), mImage1.getCenter().y(), 0);
	}
	else if(mImage2.hasImage() &&
		(mImage2.getPosition().x() < screenWidth && mImage2.getPosition().x() > 2.0f &&
		 mImage2.getPosition().y() < screenHeight && mImage2.getPosition().y() > 2.0f))
	{
		target = Vector3f(mImage2.getCenter().x(), mImage2.getCenter().y(), 0);
	}
	else if(mHeaderImage.hasImage() &&
		(mHeaderImage.getPosition().x() < screenWidth && mHeaderImage.getPosition().x() > 0.0f &&
		 mHeaderImage.getPosition().y() < screenHeight && mHeaderImage.getPosition().y() > 0.0f))
	{
		target = Vector3f(mHeaderImage.getCenter().x(), mHeaderImage.getCenter().y(), 0);
	}
	else if(mVideo->getPosition().x() < screenWidth && mVideo->getPosition().x() > 0.0f &&
		 mVideo->getPosition().y() < screenHeight && mVideo->getPosition().y() > 0.0f)
	{
		target = Vector3f(mVideo->getCenter().x(), mVideo->getCenter().y(), 0);
	}

	ViewController::get()->launch(game, target);
}

std::vector<TextComponent*> VideoGameListView::getMDLabels()
{
	std::vector<TextComponent*> ret;
	ret.push_back(&mLblRating);
	ret.push_back(&mLblReleaseDate);
	ret.push_back(&mLblDeveloper);
	ret.push_back(&mLblPublisher);
	ret.push_back(&mLblFullSystem);
	ret.push_back(&mLblRegion);
	ret.push_back(&mLblControls);
	ret.push_back(&mLblFormat);
	ret.push_back(&mLblGenre);
	ret.push_back(&mLblPlayers);
	ret.push_back(&mLblComment);
	ret.push_back(&mLblFirstRelease);
	ret.push_back(&mLblFirstReleaseShow);
	ret.push_back(&mLblLastPlayed);
	ret.push_back(&mLblPlayCount);
	return ret;
}

std::vector<GuiComponent*> VideoGameListView::getMDValues()
{
	std::vector<GuiComponent*> ret;
	ret.push_back(&mRating);
	ret.push_back(&mReleaseDate);
	ret.push_back(&mDeveloper);
	ret.push_back(&mPublisher);
	ret.push_back(&mFullSystem);
	ret.push_back(&mRegion);
	ret.push_back(&mControls);
	ret.push_back(&mFormat);
	ret.push_back(&mGenre);
	ret.push_back(&mPlayers);
	ret.push_back(&mComment);
	ret.push_back(&mFirstRelease);
	ret.push_back(&mFirstReleaseShow);
	ret.push_back(&mLastPlayed);
	ret.push_back(&mPlayCount);
	return ret;
}

void VideoGameListView::update(int deltaTime)
{
	BasicGameListView::update(deltaTime);
	mVideo->update(deltaTime);
}

void VideoGameListView::onShow()
{
	GuiComponent::onShow();
	updateInfoPanel();
}

void VideoGameListView::onFocusLost() {
	mDescContainer.reset();
	mList.stopScrolling(true);
}
