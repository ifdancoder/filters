//
// Created by ifdancoder on 16.11.2025.
//

#ifndef FILTERS_CANNYFILTER_H
#define FILTERS_CANNYFILTER_H

#include "FilterDecorator.h"
#include <vector>

class CannyFilter : public FilterDecorator {
protected:
    double lowThreshold;
    double highThreshold;
    double sigma;

    static void computeGradients(const std::shared_ptr<Image>& image,
                         std::vector<std::vector<double>>& magnitude,
                         std::vector<std::vector<double>>& direction) ;

    static void nonMaximumSuppression(const std::vector<std::vector<double>>& magnitude,
                              const std::vector<std::vector<double>>& direction,
                              std::vector<std::vector<double>>& suppressed) ;

    void doubleThreshold(const std::vector<std::vector<double>>& suppressed,
                        std::vector<std::vector<int>>& edges) const;

    static void edgeTracking(std::vector<std::vector<int>>& edges) ;

public:
    explicit CannyFilter(std::shared_ptr<IImageSource> src,
                        double low = 40.0,
                        double high = 200.0,
                        double sigma = 1.4);

    [[nodiscard]] std::shared_ptr<Image> applyFilter(std::shared_ptr<Image> in) const override;
};

#endif //FILTERS_CANNYFILTER_H

