//
// Created by ifdancoder on 19.10.2025.
//

#include "core/ImageManager.h"
#include "dotenv.h"
#include <memory>

#include <filesystem>

ImageManager::ImageManager() : denv(dotenv("./.env")) {
}

ImageManager &ImageManager::getInstance() {
    static ImageManager instance;
    return instance;
}

bool ImageManager::load(const std::string &filepath) {
    prepareDirByPath(filepath);

    std::string used_filepath = "./" + filepath;

    if (!std::filesystem::exists(used_filepath)) {
        std::cerr << "Ошибка: файл не существует: " << used_filepath << std::endl;
        return false;
    }

    if (!std::filesystem::is_regular_file(used_filepath)) {
        std::cerr << "Ошибка: путь ведет к директории, а не к файлу: " << used_filepath << std::endl;
        return false;
    }

    auto file_size = std::filesystem::file_size(used_filepath);
    if (file_size == 0) {
        std::cerr << "Ошибка: файл пустой: " << used_filepath << std::endl;
        return false;
    }

    std::cout << "Загрузка файла: " << used_filepath << " (размер: " << file_size << " байт)" << std::endl;

    sourceMatImg = cv::imread(used_filepath, cv::IMREAD_COLOR);

    Image tmp_image = Image(sourceMatImg);

    sourceImg = std::make_shared<BaseImage>(tmp_image);

    resultImg = sourceImg;

    if (sourceMatImg.empty()) {
        std::cerr << "Ошибка: не удалось загрузить изображение: " << used_filepath << std::endl;
        return false;
    }
    return true;
}

bool ImageManager::loadByEnv() {
    std::string envInputPath;

    const std::string inputPath = denv.get("INPUT_PATH");
    const std::string inputFile = denv.get("INPUT_FILE");

    if (!inputPath.empty()) {
        envInputPath += inputPath;
        envInputPath += "/";
    }

    if (!inputFile.empty()) {
        envInputPath += inputFile;
    } else {
        envInputPath += "input.jpeg";
    }

    return load(envInputPath);
}

bool ImageManager::prepareDirByPath(const std::string &path) {
    std::filesystem::path path_obj(path);
    std::string directory = path_obj.parent_path().string();

    if (prepareDir(directory)) {
        return true;
    }

    return false;
}

bool ImageManager::save(const std::string &outputPath) const {
    prepareDirByPath(outputPath);

    std::string used_filepath = "./" + outputPath;

    Image tmp_image = resultImg->getImage();

    cv::Mat image = tmp_image.toMat();

    if (image.empty()) {
        std::cerr << "Ошибка: нечего сохранять." << std::endl;
        return false;
    }
    if (!cv::imwrite(used_filepath, image)) {
        std::cerr << "Ошибка: не удалось сохранить изображение: " << used_filepath << std::endl;
        return false;
    }
    return true;
}

bool ImageManager::prepareDir(const std::string &dirPath) {
    try {
        if (std::filesystem::create_directory(dirPath)) {
            std::cout << "Папка создана: " << dirPath << std::endl;
        } else {
            std::cout << "Папка уже существует или не может быть создана" << std::endl;
        }

    } catch (const std::filesystem::filesystem_error& ex) {
        std::cerr << "Ошибка: " << ex.what() << std::endl;

        return false;
    }

    return true;
}

bool ImageManager::saveByEnv() const {
    std::string envOutputPath;

    const std::string outputPath = denv.get("OUTPUT_PATH");
    const std::string outputFile = denv.get("OUTPUT_FILE");

    if (!outputPath.empty()) {
        envOutputPath += outputPath;
        envOutputPath += "/";
    }

    if (!outputFile.empty()) {
        envOutputPath += outputFile;
    } else {
        envOutputPath += "output.jpeg";
    }

    return save(envOutputPath);
}
