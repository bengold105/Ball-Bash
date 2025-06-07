#include "UIRenderer.h"
#include "ObjectManager.h"
#include "HtCamera.h"

void UIRenderer::Initialise(int lives, int launches, int currentLevel)
{
    m_lives = lives;
    m_launches = launches;
    m_currentLevel = currentLevel;
    SetDrawDepth(10);
}

void UIRenderer::Render()
{
    if (ObjectManager::instance.GetCurrentScene() > 0) {
        DisplayLaunches();
        DisplayLives();
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
}

void UIRenderer::setLives(int lives)
{
    m_lives = lives;
}

void UIRenderer::setLaunches(int launches)
{
    m_launches = launches;
}

void UIRenderer::setLevel(int level)
{
    m_currentLevel = level;
}

