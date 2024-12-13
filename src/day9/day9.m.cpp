
#include <iostream>
#include <vector>
#include <cstdint>
#include <map>
#include <ranges>
#include <algorithm>
#include <format>
#include <cassert>
#include <filesystem>
#include <fstream>


using BlocksAmount = int8_t;
using FileId = uint32_t;
using CheckSum = uint64_t;
using FilesInfo = std::map<FileId, BlocksAmount>;

std::string loadFile(std::filesystem::path path)
{
	std::ifstream file(path, std::ios::in | std::ios::binary);
	if(!file)
	{
		throw std::runtime_error(std::format("Failed to open file {}.", path.string()));
	}

	return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}


std::vector<BlocksAmount> getInput(std::filesystem::path path){
	const auto str = loadFile(path);
    std::vector<BlocksAmount> output;
    output.reserve(str.size());
    for (auto c : str){
        output.push_back(c-'0');
    }
    return output;
}

std::pair<CheckSum, size_t> updateCheckSum(CheckSum checkSum, size_t checkSumIndex, BlocksAmount fileBlock, FileId forwardFileId) {
    for (auto i : std::views::iota(checkSumIndex, checkSumIndex + fileBlock)){
        auto add = i * forwardFileId;
        assert(std::numeric_limits<uint64_t>::max() - add >= checkSum);
        checkSum += i * forwardFileId;
    }
    
    return {checkSum, checkSumIndex+ fileBlock};
}

std::vector<std::pair<FileId, BlocksAmount>> imitateSwap(BlocksAmount emptyBlocks, FilesInfo* files){
    std::vector<std::pair<FileId, BlocksAmount>> filledWith;
    while (emptyBlocks != 0){
        auto fileIt = files->rbegin();
        if (fileIt == files->rend()) break;
        
        const auto [latestId, fileBlocks] = *fileIt;
        const auto usedBlocks = std::min<BlocksAmount>(emptyBlocks, fileBlocks);
        filledWith.emplace_back(latestId, usedBlocks);
        
        emptyBlocks = std::max<BlocksAmount>(0, emptyBlocks - fileBlocks);
        fileIt->second -= usedBlocks; 
        if (fileIt->second <= 0){
            files->erase(latestId);
        }
    }
    return filledWith;
}

std::vector<std::pair<FileId, BlocksAmount>> imitateSwap2(BlocksAmount emptyBlocks, FilesInfo* files){
    std::vector<std::pair<FileId, BlocksAmount>> filledWith;
    while (emptyBlocks != 0){
        auto fileIt = files->rbegin();
        while (fileIt != files->rend() && fileIt->second > emptyBlocks) ++fileIt;
        if (fileIt == files->rend()) break;

        
        const auto [latestId, fileBlocks] = *fileIt;
        const auto usedBlocks = std::min<BlocksAmount>(emptyBlocks, fileBlocks);
        filledWith.emplace_back(latestId, usedBlocks);
        
        emptyBlocks = std::max<BlocksAmount>(0, emptyBlocks - fileBlocks);
        fileIt->second -= usedBlocks; 
        if (fileIt->second <= 0){
            files->erase(latestId);
        }
    }
    return filledWith;
}

uint64_t solve1(const std::vector<BlocksAmount>& input, std::map<FileId, BlocksAmount> files){
    auto checkSumIndex = 0;
    auto forwardFileId = 0;
    CheckSum checkSum=0;
    
    for (auto i = 1; !files.empty(); i+=2){
        BlocksAmount emptyBlocks = i <input.size() ? input[i]:0;
        if (!files.contains(forwardFileId)) break;

        BlocksAmount fileBlocks = files[forwardFileId];
        std::tie(checkSum, checkSumIndex) = updateCheckSum(checkSum, checkSumIndex, fileBlocks, forwardFileId);
        files.erase(forwardFileId);
        
        forwardFileId++;
        
        const auto fillers = imitateSwap(emptyBlocks, &files);
        for (const auto& [fillerId, fillerBlocks] : fillers){
            std::tie(checkSum, checkSumIndex) = updateCheckSum(checkSum, checkSumIndex, fillerBlocks, fillerId);
        }
    }
    return checkSum;
}

uint64_t solve2(const std::vector<BlocksAmount>& input, const std::map<FileId, BlocksAmount>& filesOrig){
    auto files = filesOrig;
    auto checkSumIndex = 0;
    FileId forwardFileId = 0;
    CheckSum checkSum=0;
    
    for (auto i = 1; i < input.size() && !files.empty(); i+=2){
        BlocksAmount emptyBlocks = input[i];
        if (files.contains(forwardFileId)){
            BlocksAmount fileBlocks = files[forwardFileId];
            std::tie(checkSum, checkSumIndex) = updateCheckSum(checkSum, checkSumIndex, fileBlocks, forwardFileId);
            files.erase(forwardFileId);
        }
        else {
            checkSumIndex += filesOrig.at(forwardFileId);
        }
        
        forwardFileId++;
        
        const auto fillers = imitateSwap2(emptyBlocks, &files);
        for (const auto& [fillerId, fillerBlocks] : fillers){
            std::tie(checkSum, checkSumIndex) = updateCheckSum(checkSum, checkSumIndex, fillerBlocks, fillerId);
            emptyBlocks -= fillerBlocks;
        }
        checkSumIndex += emptyBlocks;
    }
    return checkSum;
}

int main()
{
    const auto input = getInput("/home/vladlev/projects/AOC24/inputs/day9.txt");
    std::map<FileId, BlocksAmount> files;
    for (const auto [id, blocks] : input | std::views::stride(2) | std::views::enumerate){
        files[id] = blocks;
    }
    
    std::cout << "checksum " << solve1(input, files) << std::endl;
    std::cout << "checksum2\n" << solve2(input, files) << std::endl;

    return 0;
}