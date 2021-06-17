#pragma once

#include "GraphicsResources.h"
#include "IGraphicsObject.h"

struct IGraphicsDevice : public IGraphicsObject
{
    virtual ~IGraphicsDevice() {}

    /**
	 * @brief Initialize the graphics device.
	 * Note that it is the full initialization including the swapchain.
	 * @See GetErrorMessage
	 * @return True if successfully initialized. False otherwise.
	*/
    virtual bool Initialize() = 0;

    /**
	 * @brief Shuts down and destroy all device related objects.
	*/
    virtual void Shutdown() = 0;

    /**
     * @brief Creates a new graphics surface.
    */
    virtual struct IGraphicsSurface* CreateSurface(void* windowHandle, uint32 width, uint32 height) = 0;

    virtual struct IGraphicsContext* CreateGraphicsContext() = 0;

    virtual GpuConstantBuffer* CreateConstantBuffer(uint32 elementsCount, uint32 elementStride, const void* data = nullptr) = 0;

    inline void SetShaderDir(const std::filesystem::path& dir) { m_shaderDir = std::filesystem::absolute(dir); }

    inline std::filesystem::path GetShaderDir() const { return m_shaderDir; }

    template<class ShaderType>
    ShaderType* CreateShader(const std::filesystem::path& filename)
    {
        return nullptr;
    }

    template<>
    GpuVertexShader* CreateShader<GpuVertexShader>(const std::filesystem::path& filename)
    {
        return CreateVertexShader(filename);
    }

    template<>
    GpuPixelShader* CreateShader<GpuPixelShader>(const std::filesystem::path& filename)
    {
        return CreatePixelShader(filename);
    }

    template<>
    GpuDomainShader* CreateShader<GpuDomainShader>(const std::filesystem::path& filename)
    {
        return CreateDomainShader(filename);
    }

    template<>
    GpuHullShader* CreateShader<GpuHullShader>(const std::filesystem::path& filename)
    {
        return CreateHullShader(filename);
    }

    template<>
    GpuGeometryShader* CreateShader<GpuGeometryShader>(const std::filesystem::path& filename)
    {
        return CreateGeometryShader(filename);
    }

    template<>
    GpuComputeShader* CreateShader<GpuComputeShader>(const std::filesystem::path& filename)
    {
        return CreateComputeShader(filename);
    }

    virtual GpuTexture2D* CreateTexture2D(uint32 width, uint32 height, EPixelFormat format, ETextureFlags flags) = 0;

  protected:
    virtual GpuVertexShader*   CreateVertexShader(const std::filesystem::path& filename)   = 0;
    virtual GpuPixelShader*    CreatePixelShader(const std::filesystem::path& filename)    = 0;
    virtual GpuDomainShader*   CreateDomainShader(const std::filesystem::path& filename)   = 0;
    virtual GpuHullShader*     CreateHullShader(const std::filesystem::path& filename)     = 0;
    virtual GpuGeometryShader* CreateGeometryShader(const std::filesystem::path& filename) = 0;
    virtual GpuComputeShader*  CreateComputeShader(const std::filesystem::path& filename)  = 0;

  protected:
    std::filesystem::path m_shaderDir;
};

extern IGraphicsDevice* gGraphicsDevice;