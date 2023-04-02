// there's better solutions but I wanted to use threads

#include <thread>
#include <atomic>
#include <unordered_map>
#include <vector>

class Solution {
public:
    // Checks if a row is valid
    static void rowCheck(const std::vector<std::vector<char>>& board, std::atomic_bool& isCorrect, const unsigned short int ROW)
    {
        std::unordered_map<char, bool> digits;
        for (unsigned short int col = 0; isCorrect && col < 9; ++col)
        {
            char squareVal = board[ROW][col];
            if (squareVal != '.')
            {
                if (digits.find(squareVal) != digits.end())
                {
                    isCorrect = false;
                    return;
                }
                else
                {
                    digits[squareVal] = true;
                }
            }
        }
    }

    // Checks if a column is valid
    static void colCheck(const std::vector<std::vector<char>>& board, std::atomic_bool& isCorrect, const unsigned short int COL)
    {
        std::unordered_map<char, bool> digits;
        for (int row = 0; isCorrect && row < 9; ++row)
        {
            char squareVal = board[row][COL];
            if (squareVal != '.')
            {
                if (digits.find(squareVal) != digits.end())
                {
                    isCorrect = false;
                    return;
                }
                else
                {
                    digits[squareVal] = true;
                }
            }
        }
    }

    // Checks if a 3 x 3 sub-grid is valid
    static void gridCheck(const std::vector<std::vector<char>>& board, std::atomic_bool& isCorrect, const unsigned short int ROW_BEGIN, const unsigned short int COL_BEGIN)
    {
        std::unordered_map<char, bool> digits;
        for (unsigned short int i = 0; isCorrect && i < 9; ++i)
        {
            unsigned short int row = i / 3 + ROW_BEGIN;
            unsigned short int col = i % 3 + COL_BEGIN;
            char squareVal = board[row][col];

            if (squareVal != '.')
            {
                if (digits.find(squareVal) != digits.end())
                {
                    isCorrect = false;
                    return;
                }
                else
                {
                    digits[squareVal] = true;
                }
            }
        }
    }

    // Checks a row, column, and 3 x 3 sub-grid
    static void check(const std::vector<std::vector<char>>& board, std::atomic_bool& isCorrect, unsigned short int i)
    {
        int row = 3 * (i / 3);
        int col = 3 * (i % 3);

        gridCheck(board, isCorrect, row, col);
        rowCheck(board, isCorrect, i);
        colCheck(board, isCorrect, i);
    }
	
    // determines if a sudoku board is valid, implemented with threads
    bool isValidSudoku(std::vector<std::vector<char>>& board)
    {
        std::atomic_bool isCorrect = true;
        std::vector<std::thread*> tests;
        // Create 9 thread to check a row, column and square
        for (unsigned short int i = 0; isCorrect && i < 9; ++i)
        {
            std::thread* th = new std::thread(this->check, std::ref(board), std::ref(isCorrect), i);
            tests.push_back(th);
        }

        for (auto th : tests)
        {
            th->join();
            delete th;
            th = nullptr;
        }

        return isCorrect;
    }
};