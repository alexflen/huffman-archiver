#include "HuffmanArchiver.h"
#include "MyException.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main(int argc, char **argv) {
    std::vector<std::string> arguments;
    for (int i = 0; i < argc; i++) {
        arguments.emplace_back(argv[i]);
    }

    bool needCompress = false;
    std::string inputFileName = "", outputFileName = "";
    for (int argNum = 1; argNum < argc; argNum++) {
        if (arguments[argNum] == "-c") {
            needCompress = true;
        } else if (arguments[argNum] == "-f") {
            argNum++;
            if (argNum >= argc) {
                MyHuffmanArchiver::MyException exception("No input file specified");
                exception.print();
                return -1;
            }
            inputFileName = arguments[argNum];
        } else if (arguments[argNum] == "-o") {
            argNum++;
            if (argNum >= argc) {
                MyHuffmanArchiver::MyException exception("No output file specified");
                exception.print();
                return -1;
            }
            outputFileName = arguments[argNum];
        }
    }

    if (inputFileName == "") {
        MyHuffmanArchiver::MyException exception("No input file specified");
        exception.print();
        return -1;
    }

    if (outputFileName == "") {
        MyHuffmanArchiver::MyException exception("No output file specified");
        exception.print();
        return -1;
    }

    std::ifstream inputFile(inputFileName);
    if (inputFile.fail()) {
        MyHuffmanArchiver::MyException exception("Can't open the file to archive");
        exception.print();
        return -1;
    }

    inputFile.exceptions(std::ifstream::badbit);

    std::ofstream outputFile(outputFileName);
    if (outputFile.fail()) {
        MyHuffmanArchiver::MyException exception("Can't open the file to dearchive");
        exception.print();
        return -1;
    }

    outputFile.exceptions(std::ofstream::badbit);

    try {
        if (needCompress) {
            MyHuffmanArchiver::HuffmanArchiver archiver;
            archiver.encodeBuild(inputFile);
            archiver.encodeWrite(outputFile);

            std::cout << archiver.dataSize << std::endl;
            std::cout << archiver.compressedSize << std::endl;
            std::cout << archiver.additionalSize << std::endl;
        } else {
            MyHuffmanArchiver::HuffmanArchiver archiver;
            archiver.decodeBuild(inputFile);
            archiver.decodeWrite(outputFile);
            std::cout << archiver.compressedSize << std::endl;
            std::cout << archiver.dataSize << std::endl;
            std::cout << archiver.additionalSize << std::endl;
        }
    } catch (MyHuffmanArchiver::MyException &exception) {
        exception.print();
        return 1;
    }

    return 0;
}