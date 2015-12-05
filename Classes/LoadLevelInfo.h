//
//  LoadLevelInfo.h
//  cs526
//
//  Created by Darren Cheng on 15/3/2.
//
//

#ifndef __cs526__LoadLevelInfo__
#define __cs526__LoadLevelInfo__

#include "cocos2d.h"
using namespace cocos2d;

class LoadLevelinfo: public Ref
{
public:
    
    ~LoadLevelinfo();
    static LoadLevelinfo * createLoadLevelinfo(const std::string& plistpath);
    
    bool initPlist(const std::string& plistpath);
    void readLevelInfo();
    void clearAll();
    
private:
    ValueMap resources;
    ValueMap levelInfo;
};
#endif /* defined(__cs526__LoadLevelInfo__) */
