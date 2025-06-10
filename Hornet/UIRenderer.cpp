#include "UIRenderer.h"
#include "ObjectManager.h"
#include "HtCamera.h"

void UIRenderer::Initialise(int lives, int launches, int currentLevel)
{
    m_lives = lives;
    m_launches = launches;
    m_currentLevel = currentLevel;
    displayHint = true;
    SetDrawDepth(10);
}

void UIRenderer::Render()
{
    if (ObjectManager::instance.GetCurrentScene() > 0) {
        DisplayLaunches();
        DisplayLives();
        if (m_currentLevel == 1 && displayHint) {
            DisplayTip();
        }
        if (isCheating) {
            DisplayCheats();
        }
    }
}

void UIRenderer::Update(double frametime)
{
}

void UIRenderer::DisplayLaunches()
{
    HtGraphics::instance.WriteTextAligned(
        static_cast<int>(HtCamera::instance.GetRightOfCameraArea()) - 400,
        static_cast<int>(HtCamera::instance.GetTopOfCameraArea()),
        "Launches: ",
        HtGraphics::WHITE,
        0,
        1.25
    );
    HtGraphics::instance.WriteIntAligned(
        static_cast<int>(HtCamera::instance.GetRightOfCameraArea()) - 120,
        static_cast<int>(HtCamera::instance.GetTopOfCameraArea()),
        m_launches,
        HtGraphics::WHITE,
        0,
        1.25
    );
}

void UIRenderer::DisplayLives()
{
    Colour textColour = HtGraphics::WHITE;
    if (m_lives <= 1) {
        textColour = HtGraphics::RED;
    }
    HtGraphics::instance.WriteTextAligned(
        static_cast<int>(HtCamera::instance.GetLeftOfCameraArea()),
        static_cast<int>(HtCamera::instance.GetTopOfCameraArea()),
        "Lives: ",
        HtGraphics::WHITE,
        0,
        1.25
    );
    HtGraphics::instance.WriteIntAligned(
        static_cast<int>(HtCamera::instance.GetLeftOfCameraArea()) + 170,
        static_cast<int>(HtCamera::instance.GetTopOfCameraArea()),
        m_lives,
        textColour,
        0,
        1.25
    );
}

void UIRenderer::DisplayTip()
{
    HtGraphics::instance.WriteTextCentered(
        HtCamera::instance.GetCameraCentre(Vector2D(0,0)),
        "Left click and drag the mouse to aim and release to launch",
        HtGraphics::WHITE,
        0,
        0.0,
        2.0
    );
    HtGraphics::instance.WriteTextCentered(
        Vector2D(HtCamera::instance.GetCameraCentre(Vector2D(0, 0)).XValue, HtCamera::instance.GetCameraCentre(Vector2D(0, 0)).YValue - 200),
        "Reach the finish line to complete the level",
        HtGraphics::WHITE,
        0,
        0.0,
        2.0
    );
}

void UIRenderer::SetLives(int lives)
{
    m_lives = lives;
}

void UIRenderer::SetLaunches(int launches)
{
    m_launches = launches;
}

void UIRenderer::SetLevel(int level)
{
    m_currentLevel = level;
}

void UIRenderer::SetDisplayHint(bool display)
{
    displayHint = display;
}

void UIRenderer::SetCheatsEnabled(bool enable)
{
    isCheating = enable;
}

void UIRenderer::DisplayCheats()
{
    HtGraphics::instance.WriteTextAligned(
        static_cast<int>(HtCamera::instance.GetLeftOfCameraArea()),
        static_cast<int>(HtCamera::instance.GetTopOfCameraArea() - 100),
        "Cheats Enabled",
        HtGraphics::WHITE,
        0,
        1.25
    );
}

