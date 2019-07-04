#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

using namespace cocos2d;


class  AppDelegate : private Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();
    virtual void initGLContextAttrs();
    virtual bool applicationDidFinishLaunching();
    virtual void applicationDidEnterBackground();
    virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_

