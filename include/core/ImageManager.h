//
// Created by ifdancoder on 19.10.2025.
//

#ifndef FILTERS_IMAGEMANAGER_H
#define FILTERS_IMAGEMANAGER_H

#include <dotenv.h>
#include <memory>
#include "IImageSource.h"
#include <opencv2/opencv.hpp>

#include "filters/BaseImage.h"


class ImageManager {
    ImageManager();

protected:
    dotenv denv;

    cv::Mat sourceMatImg;

    std::shared_ptr<BaseImage> sourceImg;

    std::shared_ptr<IImageSource> resultImg;

public:
    static ImageManager &getInstance();

    bool load(const std::string &filepath);
    bool loadByEnv();

    static bool prepareDirByPath(const std::string &path);
    static bool prepareDir(const std::string &dirPath);

    bool save(const std::string &outputPath) const;
    bool saveByEnv() const;

    template<typename FilterType, typename ... Args>
    std::shared_ptr<IImageSource> applyFilter(Args &&...args) {
        resultImg = std::make_shared<FilterType>(resultImg, std::forward<Args>(args)...);
        return resultImg;
    }
};

#endif //FILTERS_IMAGEMANAGER_H
