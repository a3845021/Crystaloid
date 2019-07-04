#include "AppDelegate.h"
#include "Crystaloid.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace cocos2d;

USING_NS_CC;

static Size designResolutionSize = Size(720, 1280);
static Size lowResolutionSize = Size(450, 800);
static Size mediumResolutionSize = Size(720, 1280);
static Size highResolutionSize = Size(1080, 1920);


AppDelegate::AppDelegate()
{
}


AppDelegate::~AppDelegate() 
{
    SimpleAudioEngine::end();
}


void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};
    GLView::setGLContextAttrs(glContextAttrs);
}


static int register_all_packages()
{
    return 0;
}


bool AppDelegate::applicationDidFinishLaunching() 
{
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();

    if(!glview) 
    {
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
            glview = GLViewImpl::createWithRect("Crystaloid", Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
        #else
            glview = GLViewImpl::create("Crystaloid");
        #endif
        director->setOpenGLView(glview);
    }

    director->setDisplayStats(false);
    director->setAnimationInterval(1.0f / 60);

	std::vector<std::string> paths;
	paths.push_back("sounds");    

	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::FIXED_WIDTH);
	auto frameSize = glview->getFrameSize();

	if (frameSize.height > mediumResolutionSize.height)
	{
		paths.push_back("pics/high");
		director->setContentScaleFactor(MIN(highResolutionSize.height / designResolutionSize.height, highResolutionSize.width / designResolutionSize.width));
	} 
    else if (frameSize.height > lowResolutionSize.height)
	{
		paths.push_back("pics/medium");
		director->setContentScaleFactor(MIN(mediumResolutionSize.height / designResolutionSize.height, mediumResolutionSize.width / designResolutionSize.width));
	}	
	else
	{
		paths.push_back("pics/low");
		director->setContentScaleFactor(MIN(lowResolutionSize.height / designResolutionSize.height, lowResolutionSize.width / designResolutionSize.width));
	}

	Device::setKeepScreenOn(true);
	
	FileUtils::getInstance()->setSearchPaths(paths);

	register_all_packages();

    auto scene = Crystaloid::createScene();
		
    director->runWithScene(scene);

    return true;
}


void AppDelegate::applicationDidEnterBackground() 
{
    Director::getInstance()->stopAnimation();

    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
}


void AppDelegate::applicationWillEnterForeground() 
{
    Director::getInstance()->startAnimation();

    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
}