#include <RmlUi/Core.h>
//#include <RmlUi/Debugger.h>

#include "../external/RmlUi_Backend.h"

#include <iostream>
#include <filesystem>

int main(int argc, char** argv)
{
    constexpr int WINDOW_WIDTH  = 1280;
    constexpr int WINDOW_HEIGHT = 720;

    // ------------------------------------------------------------
    // Initialize backend (SDL + OpenGL 3)
    // ------------------------------------------------------------
    if (!Backend::Initialize(
            "RememberProgramGo_deeper",
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            true   // resizable
        ))
    {
        std::cerr << "Backend::Initialize failed\n";
        return -1;
    }

    // ------------------------------------------------------------
    // Install backend interfaces BEFORE Initialise
    // ------------------------------------------------------------
    Rml::SetSystemInterface(Backend::GetSystemInterface());
    Rml::SetRenderInterface(Backend::GetRenderInterface());

    if (!Rml::Initialise())
    {
        std::cerr << "Rml::Initialise failed\n";
        Backend::Shutdown();
        return -1;
    }

    // ------------------------------------------------------------
    // Create RmlUi context
    // ------------------------------------------------------------
    Rml::Context* context = Rml::CreateContext(
        "main",
        Rml::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT)
    );

    if (!context)
    {
        std::cerr << "CreateContext failed\n";
        Rml::Shutdown();
        Backend::Shutdown();
        return -1;
    }

    //Rml::Debugger::Initialise(context);

    // ------------------------------------------------------------
    // Debug working directory
    // ------------------------------------------------------------
    std::cout << "Working directory: "
              << std::filesystem::current_path() << std::endl;

    // ------------------------------------------------------------
    // Load fonts
    // ------------------------------------------------------------
    Rml::LoadFontFace("assets/fonts/LatoLatin-Regular.ttf");
    Rml::LoadFontFace("assets/fonts/NotoEmoji-VariableFont_wght.ttf", true);

    // ------------------------------------------------------------
    // Load document
    // ------------------------------------------------------------
    Rml::ElementDocument* doc =
        context->LoadDocument("assets/ui/main.rml");

    if (!doc)
    {
        std::cerr << "Failed to load main_menu.rml\n";
        Rml::Shutdown();
        Backend::Shutdown();
        return -1;
    }

    doc->Show();
    std::cout << "Initialized DOM\n";

    // ------------------------------------------------------------
    // Main loop
    // ------------------------------------------------------------
    bool running = true;
    while (running)
    {
        running = Backend::ProcessEvents(context);

        if (!running)
            break;

        context->Update();

        Backend::BeginFrame();
        context->Render();
        Backend::PresentFrame();
    }

    // ------------------------------------------------------------
    // Shutdown
    // ------------------------------------------------------------
    Rml::Shutdown();
    Backend::Shutdown();

    return 0;
}
