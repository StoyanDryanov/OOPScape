#include "Board.h"

#include <fstream>
#include <iostream>

bool Board::load(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Cannot open level file '" << filename << "'\n";
        return false;
    }

    file >> m_size;
    file.ignore();

    if (m_size < 2 || m_size > 64)
    {
        std::cerr << "Error: Invalid board size " << m_size << ". Must be between 2 and 64.\n";
        return false;
    }

    m_grid.clear();
    m_enemyStarts.clear();

    int countS = 0;
    int countF = 0;

    for (int row = 0; row < m_size; row++)
    {
        std::string line;
        if (!std::getline(file, line))
        {
            std::cerr << "Error: Expected " << m_size << " rows but got " << row << ".\n";
            return false;
        }

        if ((int)line.size() < m_size)
            line.append(m_size - line.size(), ' ');

        if ((int)line.size() > m_size)
        {
            std::cerr << "Error: Row " << row << " has " << line.size()
                << " characters, expected " << m_size << ".\n";
            return false;
        }

        for (int col = 0; col < m_size; col++)
        {
            char c = line[col];
            if (c != '*' && c != ' ' && c != 'S' && c != 'F' && c != 'E' && c != 'P')
            {
                std::cerr << "Error: Invalid character '" << c
                    << "' at row " << row << ", col " << col << ".\n";
                return false;
            }

            if (c == 'S') { countS++; m_heroStart = { col, row }; }
            else if (c == 'F') { countF++; m_exitPos = { col, row }; }
            else if (c == 'E') { m_enemyStarts.push_back({ col, row }); }
        }

        m_grid.push_back(line);
    }

    if (countS != 1)
    {
        std::cerr << "Error: Level must have exactly one 'S', found " << countS << ".\n";
        return false;
    }
    if (countF != 1)
    {
        std::cerr << "Error: Level must have exactly one 'F', found " << countF << ".\n";
        return false;
    }

    return true;
}

bool Board::isWalkable(int x, int y) const
{
    if (x < 0 || y < 0 || x >= m_size || y >= m_size)
        return false;

    return m_grid[y][x] != '*';
}

char Board::getCell(int x, int y) const
{
    if (x < 0 || y < 0 || x >= m_size || y >= m_size)
        return '*';

    return m_grid[y][x];
}

void Board::setCell(int x, int y, char c)
{
    if (x < 0 || y < 0 || x >= m_size || y >= m_size)
        return;

    m_grid[y][x] = c;
}

int Board::getSize() const
{
    return m_size;
}