#include "DX11Device.h"
#include "DX11Resources.h"
#include "Resources/ConstantBuffer.h"
#include "Resources/Texture2D.h"

bool
DX11Device::LoadPreCompiledShader(const std::filesystem::path& filename, void** data, uint64* size)
{
    auto realFilename = m_shaderDir / filename;
    if (!std::filesystem::exists(realFilename)) {
        return false;
    }

    CREATEFILE2_EXTENDED_PARAMETERS extendedParams = {};
    extendedParams.dwSize                          = sizeof(CREATEFILE2_EXTENDED_PARAMETERS);
    extendedParams.dwFileAttributes                = FILE_ATTRIBUTE_NORMAL;
    extendedParams.dwFileFlags                     = FILE_FLAG_SEQUENTIAL_SCAN;
    extendedParams.dwSecurityQosFlags              = SECURITY_ANONYMOUS;
    extendedParams.lpSecurityAttributes            = nullptr;
    extendedParams.hTemplateFile                   = nullptr;

    Wrappers::FileHandle file(CreateFile2(realFilename.c_str(), GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING, &extendedParams));

    if (file.Get() == INVALID_HANDLE_VALUE) {
        return false;
    }

    FILE_STANDARD_INFO fileInfo = {};
    if (!GetFileInformationByHandleEx(file.Get(), FileStandardInfo, &fileInfo, sizeof(fileInfo))) {
        return false;
    }

    if (fileInfo.EndOfFile.HighPart != 0) {
        return false;
    }

    *data = reinterpret_cast<byte*>(malloc(fileInfo.EndOfFile.LowPart));
    *size = fileInfo.EndOfFile.LowPart;

    if (!ReadFile(file.Get(), *data, fileInfo.EndOfFile.LowPart, nullptr, nullptr)) {
        return false;
    }

    return true;
}

GpuVertexShader*
DX11Device::CreateVertexShader(const std::filesystem::path& filename)
{
    void*  data = nullptr;
    uint64 size = 0;
    if (!LoadPreCompiledShader(filename, &data, &size)) {
        return nullptr;
    }

    ID3D11VertexShader* vshader = nullptr;

    if (FAILED(m_d3d11Device->CreateVertexShader(data, size, nullptr, &vshader))) {
        SAFE_DELETE(data);
        return nullptr;
    }

    GpuVertexShader* result = new DX11VertexShader(this, vshader, data, size);

    SAFE_DELETE_ARRAY(data);

    return result;
}

GpuPixelShader*
DX11Device::CreatePixelShader(const std::filesystem::path& filename)
{
    void*  data = nullptr;
    uint64 size = 0;
    if (!LoadPreCompiledShader(filename, &data, &size)) {
        return nullptr;
    }

    ID3D11PixelShader* pshader = nullptr;

    if (FAILED(m_d3d11Device->CreatePixelShader(data, size, nullptr, &pshader))) {
        SAFE_DELETE(data);
        return nullptr;
    }

    GpuPixelShader* result = new DX11PixelShader(this, pshader);

    SAFE_DELETE_ARRAY(data);

    return result;
}

GpuDomainShader*
DX11Device::CreateDomainShader(const std::filesystem::path& filename)
{
    void*  data = nullptr;
    uint64 size = 0;
    if (!LoadPreCompiledShader(filename, &data, &size)) {
        return nullptr;
    }

    ID3D11DomainShader* dshader = nullptr;

    if (FAILED(m_d3d11Device->CreateDomainShader(data, size, nullptr, &dshader))) {
        SAFE_DELETE(data);
        return nullptr;
    }

    GpuDomainShader* result = new DX11DomainShader(this, dshader);

    SAFE_DELETE_ARRAY(data);

    return result;
}

GpuHullShader*
DX11Device::CreateHullShader(const std::filesystem::path& filename)
{
    void*  data = nullptr;
    uint64 size = 0;
    if (!LoadPreCompiledShader(filename, &data, &size)) {
        return nullptr;
    }

    ID3D11HullShader* hshader = nullptr;

    if (FAILED(m_d3d11Device->CreateHullShader(data, size, nullptr, &hshader))) {
        SAFE_DELETE(data);
        return nullptr;
    }

    GpuHullShader* result = new DX11HullShader(this, hshader);

    SAFE_DELETE_ARRAY(data);

    return result;
}

GpuGeometryShader*
DX11Device::CreateGeometryShader(const std::filesystem::path& filename)
{
    void*  data = nullptr;
    uint64 size = 0;
    if (!LoadPreCompiledShader(filename, &data, &size)) {
        return nullptr;
    }

    ID3D11GeometryShader* gshader = nullptr;

    if (FAILED(m_d3d11Device->CreateGeometryShader(data, size, nullptr, &gshader))) {
        SAFE_DELETE(data);
        return nullptr;
    }

    GpuGeometryShader* result = new DX11GeometryShader(this, gshader);

    SAFE_DELETE_ARRAY(data);

    return result;
}

GpuComputeShader*
DX11Device::CreateComputeShader(const std::filesystem::path& filename)
{
    void*  data = nullptr;
    uint64 size = 0;
    if (!LoadPreCompiledShader(filename, &data, &size)) {
        return nullptr;
    }

    ID3D11ComputeShader* cshader = nullptr;

    if (FAILED(m_d3d11Device->CreateComputeShader(data, size, nullptr, &cshader))) {
        SAFE_DELETE(data);
        return nullptr;
    }

    GpuComputeShader* result = new DX11ComputeShader(this, cshader);

    SAFE_DELETE_ARRAY(data);

    return result;
}

void
DX11VertexShader::SetConstantBuffer(uint32 index, ConstantBuffer* buffer)
{
    DX11ConstantBuffer* dx11Buffer = dynamic_cast<DX11ConstantBuffer*>(buffer->GetGpuConstantBuffer());
    m_device->GetD3D11Context()->VSSetConstantBuffers(index, 1, dx11Buffer->GetD3D11Buffer().GetAddressOf());
}

void
DX11PixelShader::SetConstantBuffer(uint32 index, ConstantBuffer* buffer)
{
    DX11ConstantBuffer* dx11Buffer = dynamic_cast<DX11ConstantBuffer*>(buffer->GetGpuConstantBuffer());
    m_device->GetD3D11Context()->PSSetConstantBuffers(index, 1, dx11Buffer->GetD3D11Buffer().GetAddressOf());
}

void
DX11DomainShader::SetConstantBuffer(uint32 index, ConstantBuffer* buffer)
{
    DX11ConstantBuffer* dx11Buffer = dynamic_cast<DX11ConstantBuffer*>(buffer->GetGpuConstantBuffer());
    m_device->GetD3D11Context()->DSSetConstantBuffers(index, 1, dx11Buffer->GetD3D11Buffer().GetAddressOf());
}

void
DX11HullShader::SetConstantBuffer(uint32 index, ConstantBuffer* buffer)
{
    DX11ConstantBuffer* dx11Buffer = dynamic_cast<DX11ConstantBuffer*>(buffer->GetGpuConstantBuffer());
    m_device->GetD3D11Context()->HSSetConstantBuffers(index, 1, dx11Buffer->GetD3D11Buffer().GetAddressOf());
}

void
DX11GeometryShader::SetConstantBuffer(uint32 index, ConstantBuffer* buffer)
{
    DX11ConstantBuffer* dx11Buffer = dynamic_cast<DX11ConstantBuffer*>(buffer->GetGpuConstantBuffer());
    m_device->GetD3D11Context()->GSSetConstantBuffers(index, 1, dx11Buffer->GetD3D11Buffer().GetAddressOf());
}

void
DX11ComputeShader::SetConstantBuffer(uint32 index, ConstantBuffer* buffer)
{
    DX11ConstantBuffer* dx11Buffer = dynamic_cast<DX11ConstantBuffer*>(buffer->GetGpuConstantBuffer());
    m_device->GetD3D11Context()->CSSetConstantBuffers(index, 1, dx11Buffer->GetD3D11Buffer().GetAddressOf());
}

void
DX11VertexShader::SetTexture2D(uint32 index, Texture2D* tex2D)
{
    assert(HAS_FLAG(tex2D->GetFlags(), TEXTURE_FLAG_SHADER_RESOURCE));
    DX11Texture2D* dx11Tex2D = dynamic_cast<DX11Texture2D*>(tex2D->GetGpuTexture2D());
    m_device->GetD3D11Context()->VSSetShaderResources(index, 1, dx11Tex2D->GetDx11SRV().GetAddressOf());
}

void
DX11PixelShader::SetTexture2D(uint32 index, Texture2D* tex2D)
{
    assert(HAS_FLAG(tex2D->GetFlags(), TEXTURE_FLAG_SHADER_RESOURCE));
    DX11Texture2D* dx11Tex2D = dynamic_cast<DX11Texture2D*>(tex2D->GetGpuTexture2D());
    m_device->GetD3D11Context()->PSSetShaderResources(index, 1, dx11Tex2D->GetDx11SRV().GetAddressOf());
}

void
DX11DomainShader::SetTexture2D(uint32 index, Texture2D* tex2D)
{
    assert(HAS_FLAG(tex2D->GetFlags(), TEXTURE_FLAG_SHADER_RESOURCE));
    DX11Texture2D* dx11Tex2D = dynamic_cast<DX11Texture2D*>(tex2D->GetGpuTexture2D());
    m_device->GetD3D11Context()->DSSetShaderResources(index, 1, dx11Tex2D->GetDx11SRV().GetAddressOf());
}

void
DX11HullShader::SetTexture2D(uint32 index, Texture2D* tex2D)
{
    assert(HAS_FLAG(tex2D->GetFlags(), TEXTURE_FLAG_SHADER_RESOURCE));
    DX11Texture2D* dx11Tex2D = dynamic_cast<DX11Texture2D*>(tex2D->GetGpuTexture2D());
    m_device->GetD3D11Context()->HSSetShaderResources(index, 1, dx11Tex2D->GetDx11SRV().GetAddressOf());
}

void
DX11GeometryShader::SetTexture2D(uint32 index, Texture2D* tex2D)
{
    assert(HAS_FLAG(tex2D->GetFlags(), TEXTURE_FLAG_SHADER_RESOURCE));
    DX11Texture2D* dx11Tex2D = dynamic_cast<DX11Texture2D*>(tex2D->GetGpuTexture2D());
    m_device->GetD3D11Context()->GSSetShaderResources(index, 1, dx11Tex2D->GetDx11SRV().GetAddressOf());
}

void
DX11ComputeShader::SetTexture2D(uint32 index, Texture2D* tex2D)
{
    assert(HAS_FLAG(tex2D->GetFlags(), TEXTURE_FLAG_SHADER_RESOURCE));
    DX11Texture2D* dx11Tex2D = dynamic_cast<DX11Texture2D*>(tex2D->GetGpuTexture2D());
    m_device->GetD3D11Context()->CSSetShaderResources(index, 1, dx11Tex2D->GetDx11SRV().GetAddressOf());
}

void
DX11ComputeShader::SetUAV(uint32 index, Texture2D* tex2D)
{
    assert(HAS_FLAG(tex2D->GetFlags(), TEXTURE_FLAG_UNORDERED_ACCESS));
    DX11Texture2D* dx11Tex2D = dynamic_cast<DX11Texture2D*>(tex2D->GetGpuTexture2D());
    m_device->GetD3D11Context()->CSSetUnorderedAccessViews(index, 1, dx11Tex2D->GetDx11UAV().GetAddressOf(), NULL);
}
