#include <iostream>
#include <vector>
#include "Block.h"

unsigned long difficulty = 1;

bool isChainValid(std::vector<Block> &block_chain)
{
    std::string hash_target(new char[difficulty]);
    hash_target.replace(hash_target.begin(), hash_target.end(), '\0', '0');

    for (int i = 1; i < block_chain.size(); i++)
    {
        Block current_block = block_chain[i];
        Block previous_block = block_chain[i - 1];

        if (current_block.get_hash() != current_block.calculate_hash())
        {
            std::cout << "Current Hashes not equal" << std::endl;
            return false;
        }

        if (previous_block.get_hash() != current_block.get_previous_hash())
        {
            std::cout << "Previous Hashes not equal" << std::endl;
            return false;
        }

        if (current_block.get_hash().substr(0, difficulty) != hash_target)
        {
            std::cout << "This block hasn't been mined" << std::endl;
            return false;
        }
    }

    return true;
}

int main()
{
    Block first_block("This is the first block", "0");
    std::cout << "Trying to Mine block 1..." << std::endl;
    first_block.mine_block(difficulty);

    Block second_block("This is the first block", first_block.get_hash());
    std::cout << "Trying to Mine block 2..." << std::endl;
    second_block.mine_block(difficulty);

    Block third_block("This is the first block", second_block.get_hash());
    std::cout << "Trying to Mine block 3..." << std::endl;
    third_block.mine_block(difficulty);

    std::vector<Block> block_chain;
    block_chain.push_back(first_block);
    block_chain.push_back(second_block);
    block_chain.push_back(third_block);

    std::cout << std::endl;
    std::cout << "Chain is valid? " << isChainValid(block_chain) << std::endl;
    return 0;
}
