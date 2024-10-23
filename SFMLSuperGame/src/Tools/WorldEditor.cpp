#include "WorldEditor.h"

GameEditor::GameEditor(int screenHeight)
{
    tileMapHeight = screenHeight;
}



void GameEditor::InitializeGameEditor()
{
    
}

void GameEditor::ExitGameEditor()
{
    // Deallocating memory to prevent memory leak
    delete[] moduleWidth;
    delete[] moduleHeight;

    // Setting to nullptr to ensure correct clean of space memory otherwise we might get garbage
    moduleWidth = nullptr;
    moduleHeight = nullptr;
}

