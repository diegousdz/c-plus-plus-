#pragma once

class Program {
public:
    void RunGame();
    void RunEditor();
    Program(bool inEditorMode);
private:
    bool inEditorMode;
};
