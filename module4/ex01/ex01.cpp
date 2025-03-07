#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <exception>

class FileNotFoundException : public std::exception {
public:
    const char* what() const noexcept override {
        return "File could not be opened.";
    }
};

// File class - represents a file, opened for reading and appending
// if the file does not exist, it will be created (so FileNotFound... not really)
// (if the persimission don't match, then it won't be able to open the file)
class File {
private:
    std::string filename;
    std::unique_ptr<std::fstream> fileStream;

public:
    File(const std::string& fname) : filename(fname), fileStream(std::make_unique<std::fstream>()) {
        fileStream->open(filename, std::ios::in | std::ios::app);
        if (!fileStream->is_open()) {
            throw FileNotFoundException();
        }
    }

    void write(const std::string& data) {
        if (!fileStream || !fileStream->is_open()) {
            throw std::runtime_error("Write operation failed: file not open.");
        }
        std::cout << "write to " << filename << std::endl; 
        (*fileStream) << data << std::endl;
        if (fileStream->fail()) {
            throw std::runtime_error("Write operation failed.");
        }
    }

    void read() {
        if (!fileStream || !fileStream->is_open()) {
            throw std::runtime_error("Read operation failed: file not open.");
        }
        std::cout << "read from " << filename << std::endl;
        fileStream->seekg(0);
        std::string line;
        while (std::getline(*fileStream, line)) {
            std::cout << line << std::endl;
        }
        fileStream->clear();
    }

    void close() {
        if (fileStream) {
            fileStream->close();
        }
    }

    const std::string& getFilename() const {
        return filename;
    }

    ~File() {
        close();
    }
};

// a utility function to play around with File
void openFile(const std::string& filename) {
    std::exception_ptr exPtr;
    try {
        File file(filename);
        file.write("Example content");
        file.read();
    } catch (...) {
        exPtr = std::current_exception();
    }
    if (exPtr) {
        try {
            std::rethrow_exception(exPtr);
        } catch (const std::exception& e) {
            std::cerr << "Exception caught: " << e.what() << std::endl;
        }
    }
}

// FileManager class - collection of Files. Add, get, remove
class FileManager {
private:
    std::vector<std::shared_ptr<File>> files;

public:
    void addFile(const std::string& filename) {
        try {
            std::shared_ptr<File> file = std::make_shared<File>(filename);
            files.push_back(file);
        } catch (const FileNotFoundException& e) {
            std::cerr << "Error adding file: " << e.what() << std::endl;
        }
    }

    std::shared_ptr<File> getFile(const std::string& filename) {
        for (const auto& file : files) {
            if (file->getFilename() == filename) {
                return file;
            }
        }
        return nullptr;
    }

    void removeFile(const std::string& filename) {
        for (size_t i = 0; i < files.size(); i++) {
            if (files[i]->getFilename() == filename) {
                std::cout << "  " << filename << ": " << files[i].use_count() << std::endl;
                files.erase(files.begin() + i);
            }
        }
    }
};

int main() { 
    openFile("example.txt");
    
    FileManager fileManager;
    fileManager.addFile("testfile.txt");
    
    std::shared_ptr<File> file = fileManager.getFile("testfile.txt");
    if (file) {
        file->write("New content added via FileManager.");
        file->read();
    }
    
    fileManager.removeFile("testfile.txt");

    std::cout << "use the file again: " << std::endl;

    if (file) {
        file->write("New content added via FileManager after remove.");
        file->read();
    }
    
    return 0;
}

