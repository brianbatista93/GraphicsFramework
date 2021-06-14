#pragma once

struct IApplication
{
    virtual ~IApplication() {}

    virtual void TickFrame() = 0;

    virtual bool IsExiting() = 0;
};

template<class ApplicationType, class GraphicsType, class... ArgsType>
static IApplication*
CreateApplication(ArgsType&&... args)
{
    ApplicationType* app = new ApplicationType();

    if (!app->Create(new GraphicsType(), std::forward<ArgsType>(args)...)) {
        return nullptr;
    }

    return app;
}