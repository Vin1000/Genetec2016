// OptimisationProblem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Directory.h"
#include "FileReader.h"
#include "FileWriter.h"
#include "HelperMethods.h"
#include "Logger.h"
#include "Statistics.h"
#include "Encoder.h"

#include <filesystem>
#include <iostream>

int main(int argc, char *argv[])
{
    using std::cout;
    using std::endl;

    std::string log;

    // Get starting time to evaluate performance of code
    auto start = std::chrono::system_clock::now().time_since_epoch();

    //////////////////////////////////////////////////////////
    // Start
	// TODO: remove this

	Logger::LineJump();
	Logger::LineJump();
	Logger::LineJump();
     Logger::Info("Start.");
     Logger::LineJump();


    // Argument checking: getting input path for files to process
    log = "Checking input arguments: ";
    std::string folderPath;
    std::string outputPath;
    char statChar;
	
	// TODO: Remove this if.
    if (argc < 4)
    {
        Logger::Info(log + "Missing argument FOLDER_PATH. Manual input required.");
        std::cout << "Please provide a folder path:";
        std::cin >> folderPath;

        std::cout << "Please provide a output path:";
        std::cin >> outputPath;

        std::cout << "Please provide a character:";
        std::cin >> statChar;
    }
    else
    {
        folderPath = argv[1];
        outputPath = argv[2];
        statChar = argv[3][0];
    }

    // Logger::Info("Input folder: " + folderPath);
    // Logger::Info("Output folder: " + outputPath);
    // Logger::LineJump();


    // Opens the directory to obtain file list
    Directory dir;
    STATUS_CODE status = dir.Open(folderPath.c_str());

    if (STATUS_CODE::OK == status)
    {
        Logger::Info("Folder opened successfully.");
    }
    else if (STATUS_CODE::INVALID_ARGUMENTS == status)
    {
        // Logger::Info("Invalid argument error.");
        return -1;
    }

    // Create statistic object which compute and store the stats for each file that is processed.
    Statistics stat(statChar);

    // Encode each file
    //Sort the directory files so that the stats output is ordered alphabetically
    auto files = Sort(dir.Files());
    for (auto file : files)
    {
        // Logger::Info("Encoding file: " + ws2s(file.Filename()));
        {
            FileReader fr;
            if (fr.Open(file.FullPath()))
            {
                std::string line;
                while (fr.ReadLine(line))
                {
                    FileWriter fw;
                    fw.Open(outputPath + ws2s(file.Filename()) + ".enc", true, true);

                    fw.Write(line);
                }
            }
            else
            {
                Logger::Info("Failed to open file: " + ws2s(file.FullPath()));
            }
        }
        {
            FileReader fr;
            if (fr.Open(s2ws(outputPath) + file.Filename() + s2ws(".enc")))
            {
                FileWriter fw;
                fw.Open(outputPath + "Statistics.txt",true);
                fw.Write(stat.ComputeFile(std::move(fr), file.Filename() + s2ws(".enc")));
            }
        }
    }

    // Logger::LineJump();
    // Logger::Info("Finished.");

    // Get end time to evaluate performance of code
    auto end = std::chrono::system_clock::now().time_since_epoch();

    // Log how long it took to process all files
    int runtime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    Logger::Info("Program ran for : " + std::to_string(runtime));

    return 0;
}

