#include <string>
#include "functions_test.h"
#include "HuffmanArchiver.h"
#include <iostream>
#include <fstream>

namespace TestFunctions {
    void invokeArchiver(const std::string& to_archive, const std::string& result, const std::string& temp) {
        std::ifstream to_archive_istream(to_archive);
        std::ofstream temp_ostream(temp);

        MyHuffmanArchiver::HuffmanArchiver archiver;
        archiver.encodeBuild(to_archive_istream);
        archiver.encodeWrite(temp_ostream);

        to_archive_istream.close();
        temp_ostream.close();

        std::ifstream temp_istream(temp);
        std::ofstream result_ostream(result);

        MyHuffmanArchiver::HuffmanArchiver dearchiver;
        dearchiver.decodeBuild(temp_istream);
        dearchiver.decodeWrite(result_ostream);

        temp_istream.close();
        result_ostream.close();
    }

    bool checkFiles(const std::string& model_file, const std::string& file) {
        std::ifstream model_file_istream(model_file);
        std::ifstream file_istream(file);

        const int BUFSIZE = 4096;
        char model_buf[BUFSIZE];
        char file_buf[BUFSIZE];

        file_istream.read(file_buf, BUFSIZE);
        model_file_istream.read(model_buf, BUFSIZE);

        while (model_file_istream.gcount()) {
            if (model_file_istream.gcount() != file_istream.gcount()) return false;

            for (int byte = 0; byte < model_file_istream.gcount(); byte++) {
                if (model_buf[byte] != file_buf[byte]) return false;
            }

            file_istream.read(file_buf, BUFSIZE);
            model_file_istream.read(model_buf, BUFSIZE);
        }

        if (model_file_istream.gcount() != file_istream.gcount()) return false;

        file_istream.close();
        model_file_istream.close();

        return true;
    }
}